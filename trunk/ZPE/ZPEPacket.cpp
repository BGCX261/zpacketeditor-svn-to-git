/********************************************************************
 *                                                                  *
 * Copyright (c) 2010 R. "The Nullz" Aiken <itsthenullz@gmail.com>. *
 *                                                                  *
 * Use of the code is allowed under the Artistic License 2.0 terms, *
 * as specified in the LICENSE file distributed with this code, or  *
 * available from:                                                  *
 *     http://www.opensource.org/licenses/artistic-license-2.0.php  *
 *                                                                  *
 ********************************************************************/
#include "ZPE.h"
#include "ZPEPacket.h"
#include "ZPEWindow.h"
#include "ZPEContext.h"

/*
 * This file must be compiled with the /CLR and /EHa flags
 * set so that this file will be compiled as managed code.
 */

/* Enter into native code */
#pragma managed(push, off)

/*
 * Constructor
 *
 * Create a ZPE packet object for a packet structure, lpvPacket,
 * with the initial attributes, dwInitialAttributes already set
 */
ZPEPacket::ZPEPacket ( __in ::LPVOID lpvPacket, __in ::DWORD dwInitialAttributes )
{
	this->dwReturn     = ( -1 );
	this->dwAttributes = dwInitialAttributes;

	/*
	 * Determine the pointer type based on the initial attributes and
	 * set the pointer to the packet and it's return address accordingly.
	 */
	switch ( dwInitialAttributes ) {
		case ZPE_PACKET_ATTRIBUTE_RECV:
			this->ppPacket = (PACKET*)lpvPacket;
			break;
		case ZPE_PACKET_ATTRIBUTE_SEND:
			this->ppPacket = ((SEND_PACKET*)lpvPacket)->ppPacket;
			/* Only sent packets have a return address attached */
			this->dwReturn = ((SEND_PACKET*)lpvPacket)->dwReturn;
			break;
	}

	/*
	 * If the length of an opcode is equal to the length of
	 * the whole packet then the packet is empty.
	 */
	if ( this->ppPacket->dwLength == MAPLE_OPCODE_LENGTH ) {
		this->dwAttributes |= ZPE_PACKET_ATTRIBUTE_EMPTY;
	} else {
		/*
		 * If none of the bytes in the packet after the opcode are a
		 * non-zero value then the packet contains only NULL data.
		 */
		bool isNull = true;

		for ( ::DWORD i = MAPLE_OPCODE_LENGTH; i < this->ppPacket->dwLength; i++ ) {
			if ( this->ppPacket->lpBytes[i] != 0 )
				isNull = false;
		}

		if ( isNull )
			this->dwAttributes |= ZPE_PACKET_ATTRIBUTE_NULL;
	}
}

#include <ctype.h>

/* Locate string data inside the byte code of this packet
 *
 * FindString iterates over the byte of the packet and returns
 * the index of the first character in the located string and
 * stores the length of that string in lpwLength. If no string
 * is found (-1) is returned.
 */
::DWORD ZPEPacket::FindString ( __inout ::LPDWORD lpdwOffset, __out ::LPWORD lpwLength )
{
	/*
	 * Starting from the offset there must be at least
	 * 3 bytes for the length and at minimum 1 char.
	 */
	if ( ( *lpdwOffset + 3 ) < this->ppPacket->dwLength ) {
		/* This is the length we expect the string to be */
		::WORD wLength = *(::LPWORD)( this->ppPacket->lpBytes + *lpdwOffset );

		/* If that value is greater than 0, then proceed */
		if ( wLength > 0 ) {
			::DWORD dwIndex;

			/*
			 * Iterate over the bytes that follow the length, and if they all
			 * represent printable characters then this is a string.
			 */
			for ( dwIndex = *lpdwOffset + 2, *lpwLength = 0; ( *lpwLength <= wLength ) && ( ( dwIndex + wLength ) < this->ppPacket->dwLength ); *lpwLength += 1 ) {
				if ( isprint(this->ppPacket->lpBytes[dwIndex + *lpwLength]) == 0 )
					break;
			}

			/*
			 * If we've found a string of the correct length, we return the offset
			 * in the lpdwOffset argument, and its length in lpwLength.
			 */
			if ( *lpwLength == wLength ) {
				*lpdwOffset = ( dwIndex + *lpwLength - 1 );
				return dwIndex;
			}
		}
	}

	/* No string was found */
	return (::DWORD)( -1 );
}

/* Block this packet (by setting it's opcode to (-1) and nullifying it's data) */
bool ZPEPacket::Block ( void )
{
	/*
	 * Packets can be blocked by modifying their opcode to
	 * the casted value of ( -1 ).
	 */
	switch ( MAPLE_OPCODE_LENGTH ) {
		case 1:
			*(::LPBYTE)(this->ppPacket->lpBytes) = ( -1 );
			break;
		case 2:
			*(::LPWORD)(this->ppPacket->lpBytes) = ( -1 );
			break;
	}

	/* For good measure we can also nullify it's data */
	for ( ::DWORD i = MAPLE_OPCODE_LENGTH; i < this->ppPacket->dwLength; i++ )
		this->ppPacket->lpBytes[i] = 0;

	return true;
}	


/* Exit native code */
#pragma managed(pop)

/* Is this packet going to be dispatched to the UI */
bool ZPEPacket::IsIgnored ( void )
{
	using namespace System::Windows::Forms;
	using namespace ZPE;

	return (
		( this->IsRecv() && ( ( ZPEContext::G->RecvPackets->IgnoreNull && this->IsNull() ) || ( ZPEContext::G->RecvPackets->IgnoreEmpty && this->IsEmpty() ) ) ) ||
		( this->IsSend() && ( ( ZPEContext::G->SendPackets->IgnoreNull && this->IsNull() ) || ( ZPEContext::G->SendPackets->IgnoreEmpty && this->IsEmpty() ) ) )
	);
}

/* Dispatch this packet to the user interface */
bool ZPEPacket::Dispatch ( void )
{
	using namespace System;
	using namespace System::Drawing;
	using namespace System::Windows::Forms;
	using namespace System::Text;
	using namespace ZPE;

	/* Will this packet be posted to the UI for viewing. */
	if ( this->IsIgnored() )
		return false;

	/* Packet byte data as in string format */
	String^ packet = nullptr;
	/* Packet data formatted with parsed strings */
	String^ format = nullptr;

	StringBuilder^ sb = gcnew StringBuilder(( int )( ( this->ppPacket->dwLength * 2 ) + this->ppPacket->dwLength ));

	for ( ::DWORD i = 0; i < this->ppPacket->dwLength; i++ ) {
		sb->AppendFormat(L"{0:X2}", this->ppPacket->lpBytes[i]);

		if ( i < ( this->ppPacket->dwLength - 1 ) )
			sb->Append(L" ");
	}

	packet = sb->ToString();
	/* Reset the StringBuilder */
	sb->Length = 0;

	/* Variable that contains the length of a parsed string */
	::WORD wLength;

	if ( this->IsEmpty() ) {
		sb->Append(L"<no data>");
	} else {
		for ( ::DWORD dwOffset = MAPLE_OPCODE_LENGTH, dwIndex = ( -1 ); dwOffset < this->ppPacket->dwLength; dwOffset++ ) {
			if ( ( dwIndex = this->FindString(&dwOffset, &wLength) ) != (::DWORD)( -1 ) ) {
				sb->AppendFormat(L"\"{0}\"", gcnew String((::LPSTR)( this->ppPacket->lpBytes + dwIndex ), 0, wLength));
			} else {
				sb->AppendFormat(L"{0:X2}", this->ppPacket->lpBytes[dwOffset]);
			}

			if ( dwOffset < ( this->ppPacket->dwLength - 1 ) )
				sb->Append(L" ");
		}
	}
	
	format = sb->ToString();

	ListViewItem^ listViewItem = gcnew ListViewItem(packet);
	listViewItem->Font         = (gcnew System::Drawing::Font(FontFamily::GenericMonospace, 8.75F, GraphicsUnit::Point));
	listViewItem->ToolTipText  = packet;

	/* If the tooltip would be over 255 characters in length, truncate */
	if ( listViewItem->ToolTipText->Length > 255 )
		listViewItem->ToolTipText = String::Concat(listViewItem->ToolTipText->Substring(0, 255), L"...");

	/* Size column */
	listViewItem->SubItems->Add(this->ppPacket->dwLength.ToString(L"N0"));
	/* Code column: Opcode display as 4 hexadecimal digits */
	listViewItem->SubItems->Add(this->ppPacket->pMessage->Opcode.ToString(L"X4"));
	/* Data column: Formatted packet data */
	listViewItem->SubItems->Add(format);

	if ( this->IsRecv() )
		ZPEContext::G->RecvPackets->AddItem(listViewItem);

	if ( this->IsSend() )
		ZPEContext::G->SendPackets->AddItem(listViewItem);

	/* We'll return true when a packet is blocked, and false otherwise. */
	return false;
}
