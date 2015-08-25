#include "Z.h"
#include "Z_CLI.h"
#include "Z_GUI.h"

#pragma managed(push, off)

/* Constructor */
ZPacket::ZPacket ( __in ::LPVOID lpvPacket, __in ::DWORD dwPacketType )
{
	this->dwReturn     = (::DWORD)( -1 );
	this->dwPacketType = dwPacketType;

	switch ( this->dwPacketType ) {
		case Z_PACKET_STREAM_RECEIVE:
			this->ppPacket = (PZ_PACKET)lpvPacket;
			break;

		case Z_PACKET_STREAM_SEND:
			this->ppPacket = ((PZ_SEND_PACKET)lpvPacket)->ppPacket;
			this->dwReturn = ((PZ_SEND_PACKET)lpvPacket)->dwReturn;
			break;
	}

	if ( GetMapleStoryRegion() == this->ppPacket->dwLength ) {
		this->dwPacketType |= Z_PACKET_TYPE_EMPTY;
	} else if ( this->ppPacket->dwLength < 1 ) {
		this->dwPacketType |= Z_PACKET_TYPE_NULL;
	} else {
		bool bIsNull = true;

		for ( ::DWORD dwOffset = GetMapleStoryRegion(); dwOffset < this->ppPacket->dwLength; dwOffset++ ) {
			if ( this->ppPacket->lpBytes[dwOffset] != 0 ) {
				bIsNull = false;
				break;
			}
		}

		if ( bIsNull )
			this->dwPacketType |= Z_PACKET_TYPE_NULL;
	}
}
/* Dispose */
ZPacket::~ZPacket ( void )
{
	this->ppPacket = NULL;
}

/* Block a packet from being processed */
bool ZPacket::Block ( void )
{
	switch ( GetMapleStoryRegion() ) {
		case MAPLESTORY_REGION_GLOBAL:
			this->ppPacket->ppGMSPacket->Command = (::WORD)( -1 );
			break;
		case MAPLESTORY_REGION_EUROPE:
			this->ppPacket->ppEMSPacket->Command = (::BYTE)( -1 );
			break;
	}

	/* Nullify packet data */
	for ( ::DWORD i = GetMapleStoryRegion(); i < this->ppPacket->dwLength; i++ )
		this->ppPacket->lpBytes[i] = 0;

	return true;
}

/* Find string inside packet data */
bool IsString ( __in_bcount(dwLength) ::LPBYTE lpBytes, __in ::DWORD dwOffset, __in ::DWORD dwLength, __out ::PDWORD pdwIndex, __out ::LPWORD pwCount )
{
	if ( ( dwOffset + 1 ) >= dwLength )
		return false;

	::WORD wCount = 0;

	/* Get the first word value at this offset */
	if ( ( wCount = *(::LPWORD)( lpBytes + dwOffset ) ) < 1 )
		return false;

	/* Locate string inside packet data and return its length */
	for ( *pdwIndex = dwOffset + 2, *pwCount = 0; ( *pwCount <= wCount ) && ( ( *pdwIndex + *pwCount ) < dwLength ); *pwCount += 1 ) {
		if ( isprint(lpBytes[*pdwIndex + *pwCount]) == 0 )
			break;
	}

	/* Return true if *pdwCount is equal to the first byte */
	return ( *pwCount == wCount );
}

#pragma managed(pop)

/*
* Serialize the packet data to a string containing only
* the hexa-decimal byte values for the packet data
*/
String^ GetBytes ( __in_bcount(dwLength) ::LPBYTE lpBytes, __in ::DWORD dwLength, bool spaced )
{
	using namespace System;
	using namespace System::Text;

	StringBuilder^ sb;

	if ( spaced ) {
		sb = gcnew StringBuilder((int)( ( dwLength * 2 ) + ( dwLength - 1 ) ));
	} else {
		sb = gcnew StringBuilder((int)( dwLength * 2 ));
	}

	for ( ::DWORD i = 0; i < dwLength; i++ ) {
		sb->Append(lpBytes[i].ToString(L"X2"));

		if ( spaced && ( i < ( dwLength - 1 ) ) )
			sb->Append(L" ");
	}

	return sb->ToString();
}
/*
* Serialize the packet data to a string containing only
* the hexa-decimal byte values for the packet data
*/
String^ GetBytes ( __in_bcount(dwLength) ::LPBYTE lpBytes, __in ::DWORD dwLength )
{
	return GetBytes(lpBytes, dwLength, false);
}
/* Format the packet byte data so that strings are readily visible */
String^ FormatPacket ( __in_bcount(dwLength) ::LPBYTE lpBytes, __in ::DWORD dwLength, __in bool prefix )
{
	using namespace System;
	using namespace System::Text;

	StringBuilder^ sb = gcnew StringBuilder((int)( ( dwLength * 2 ) - ( dwLength - 1 ) ));

	if ( prefix ) {
		switch ( GetMapleStoryRegion() ) {
			case MAPLESTORY_REGION_GLOBAL:
				sb->AppendFormat(L"@{0}", (*(::LPWORD)lpBytes).ToString(L"X4"));
				break;
			case MAPLESTORY_REGION_EUROPE:
				sb->AppendFormat(L"@{0}", (*(::LPBYTE)lpBytes).ToString(L"X4"));
				break;
		}
	}

	if ( GetMapleStoryRegion() < dwLength ) {
		::WORD wCount;

		for (::DWORD dwOffset = GetMapleStoryRegion(), dwIndex; dwOffset < dwLength; dwOffset++ ) {
			sb->Append(L" ");

			if ( IsString(lpBytes, dwOffset, dwLength, &dwIndex, &wCount) ) {
				sb->Append(L"\"");
				sb->Append(gcnew String((::LPSTR)( lpBytes + dwIndex ), 0, (int)wCount));
				sb->Append(L"\"");

				dwOffset = dwIndex + wCount - 1;
			} else {
				sb->Append(lpBytes[dwOffset].ToString(L"X2"));
			}
		}
	}

	return sb->ToString();
}
/* Format the packet byte data so that strings are readily visible */
String^ FormatPacket ( __in_bcount(dwLength) ::LPBYTE lpBytes, __in ::DWORD dwLength )
{
	return FormatPacket(lpBytes, dwLength, false);
}

/* Number of packets received total */
volatile ::UINT64 PacketsRecv = 0;
/* Number of packets sent total */
volatile ::UINT64 PacketsSent = 0;
/* Number of bytes received total */
volatile ::UINT64 BytesRecv   = 0;
/* Number of bytes sent total */
volatile ::UINT64 BytesSent   = 0;
/* Ignore received packets that contain only NULL data */
volatile bool IgnoreNullRecvPackets  = false;
/* Ignore received packets that contain only a command */
volatile bool IgnoreEmptyRecvPackets = false;
/* Ignore sent packets that contain only NULL data */
volatile bool IgnoreNullSendPackets  = false;
/* Ignore sent packets that contain only a command */
volatile bool IgnoreEmptySendPackets = false;

/* Dispatch this packet */
bool ZPacket::Dispatch ( void )
{
	using namespace Z;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Drawing;
	using namespace System::Windows::Forms;

	/* Is this packet blocked */
	bool ignored = false;
	/* Is this packet ignored */
	bool blocked = false;
	/* Serialize packet */
	String^ rawBytes = GetBytes(this->ppPacket->lpBytes, this->ppPacket->dwLength, false);
	
	/* Determine if this packet is blocked or ignored, or neither */
	switch ( this->GetStream() ) {
		case Z_PACKET_STREAM_RECEIVE:
			PacketsRecv++;
			BytesRecv += this->ppPacket->dwLength;

			if ( blocked = ZContext::G->BlockedRecvPatterns->IsMatch(rawBytes) )
				break;

			if ( ( IgnoreNullRecvPackets && this->IsNull() ) || ( IgnoreEmptyRecvPackets && this->IsEmpty() ) || ZContext::G->IgnoredRecvPatterns->IsMatch(rawBytes) )
				ignored = true;

			break;
		case Z_PACKET_STREAM_SEND:
			if ( blocked = ZContext::G->BlockedSendPatterns->IsMatch(rawBytes) )
				break;

			if ( ( IgnoreNullSendPackets && this->IsNull() ) || ( IgnoreEmptySendPackets && this->IsEmpty() ) || ZContext::G->IgnoredSendPatterns->IsMatch(rawBytes) )
				ignored = true;

			break;
	}

	if ( blocked )
		return this->Block();

	if ( this->GetStream() == Z_PACKET_STREAM_SEND ) {
		PacketsSent++;
		BytesSent += this->ppPacket->dwLength;
	}

	String^ rawBytesWithSpaces = GetBytes(this->ppPacket->lpBytes, this->ppPacket->dwLength, true);
	String^ strBytes           = FormatPacket(this->ppPacket->lpBytes, this->ppPacket->dwLength, false);
	String^ strBytesWithPrefix = FormatPacket(this->ppPacket->lpBytes, this->ppPacket->dwLength, true);
	String^ toolTipText        = rawBytesWithSpaces;

	if ( toolTipText->Length > 128 )
		toolTipText = String::Concat(toolTipText->Substring(0, 128), L"...");

	if ( this->GetStream() == Z_PACKET_STREAM_SEND ) {
		toolTipText = String::Format(L"[return: {0:X8}]{1}{1}{2}",
			this->dwReturn, Environment::NewLine, toolTipText);
	}

	/* Packet list item */
	ListViewItem^ listViewItem            = gcnew ListViewItem;
	listViewItem->StateImageIndex         = this->GetStream();
	listViewItem->ToolTipText             = toolTipText;
	listViewItem->UseItemStyleForSubItems = false;
	/* Packet size (in bytes) */
	listViewItem->SubItems->Add(this->ppPacket->dwLength.ToString(L"N0"))
		->Name = L"Size";
	listViewItem->SubItems[L"Size"]->Tag = this->ppPacket->dwLength;
	/* Packet code */
	listViewItem->SubItems->Add(this->GetCommand().ToString(L"X4")->Insert(2, L" "))
		->Name = L"Code";
	listViewItem->SubItems[L"Code"]->Tag  = this->GetCommand();

	listViewItem->SubItems->Add(strBytes)
		->Name = L"Data";
	listViewItem->SubItems[L"Data"]->Font = gcnew Font(FontFamily::GenericMonospace, 8.25f, FontStyle::Regular, GraphicsUnit::Point);
	listViewItem->SubItems->Add(rawBytes)
		->Name = L"Packet";
	listViewItem->SubItems->Add(rawBytesWithSpaces)
		->Name = L"Packet2";
	listViewItem->SubItems->Add(strBytes)
		->Name = L"Format";
	listViewItem->SubItems->Add(strBytesWithPrefix)
		->Name = L"Format2";

	ZTemplate^ t = nullptr;

	if ( ( t = ZContext::G->Templates->GetTemplate(rawBytes, this->GetStream()) ) != nullptr ) {
		listViewItem->SubItems[L"Code"]->ForeColor = t->ForeColor;
		listViewItem->SubItems[L"Code"]->BackColor = t->BackColor;
		listViewItem->SubItems[L"Code"]->Text      = t->Alias;

		if ( t->Colorize ) {
			listViewItem->SubItems[L"Size"]->ForeColor = t->ForeColor;
			listViewItem->SubItems[L"Size"]->BackColor = t->BackColor;
			listViewItem->SubItems[L"Data"]->ForeColor = t->ForeColor;
			listViewItem->SubItems[L"Data"]->BackColor = t->BackColor;
		}
		
		if ( t->NoFormat ) {
			listViewItem->SubItems[L"Data"]->Text = listViewItem->SubItems[L"Packet2"]->Text;
		} else {
			listViewItem->SubItems[L"Data"]->Text = listViewItem->SubItems[L"Format"]->Text;
		}
	} else {
		listViewItem->SubItems[L"Code"]->Font = gcnew Font(FontFamily::GenericMonospace, 8.25f, FontStyle::Regular, GraphicsUnit::Point);
	}

	if ( ignored != true ) {
		switch ( this->GetStream() ) {
			case Z_PACKET_STREAM_RECEIVE:
				ZContext::G->Application->AppendRecvListItem(listViewItem);
				break;
			case Z_PACKET_STREAM_SEND:
				ZContext::G->Application->AppendSendListItem(listViewItem);
				break;
		}
	}

	listViewItem                          = gcnew ListViewItem;
	listViewItem->StateImageIndex         = this->GetStream();
	listViewItem->ToolTipText             = toolTipText;
	listViewItem->UseItemStyleForSubItems = false;
	/* Packet size (in bytes) */
	listViewItem->SubItems->Add(this->ppPacket->dwLength.ToString(L"N0"))
		->Name = L"Size";
	listViewItem->SubItems[L"Size"]->Tag = this->ppPacket->dwLength;
	/* Packet code */
	listViewItem->SubItems->Add(this->GetCommand().ToString(L"X4")->Insert(2, L" "))
		->Name = L"Code";
	listViewItem->SubItems[L"Code"]->Font = gcnew Font(FontFamily::GenericMonospace, 8.25f, FontStyle::Regular, GraphicsUnit::Point);
	listViewItem->SubItems[L"Code"]->Tag  = this->GetCommand();

	listViewItem->SubItems->Add(strBytes)
		->Name = L"Data";
	listViewItem->SubItems[L"Data"]->Font = gcnew Font(FontFamily::GenericMonospace, 8.25f, FontStyle::Regular, GraphicsUnit::Point);
	listViewItem->SubItems->Add(rawBytes)
		->Name = L"Packet";
	listViewItem->SubItems->Add(rawBytesWithSpaces)
		->Name = L"Packet2";
	listViewItem->SubItems->Add(strBytes)
		->Name = L"Format";
	listViewItem->SubItems->Add(strBytesWithPrefix)
		->Name = L"Format2";

	ZContext::G->Application->AppendHistoryListItem(listViewItem);
	return false;
}