#include "Z.h"
#include "Z_CLI.h"
#include "Z_GUI.h"

using namespace Z;
using namespace System::Globalization;
using namespace System::Text;

/* Append a menu item object to the Insert context menu */
void ZPacketBuilder::AppendInsertMenuItem ( String^ name )
{
	if ( this->m_ctxPacketMenu->InvokeRequired ) {
		this->m_ctxPacketMenu->Invoke(gcnew AppendInsertMenuItemCaller(this, &ZPacketBuilder::AppendInsertMenuItem), gcnew array<Object^>{ name });
	} else {
		ToolStripMenuItem^ item = gcnew ToolStripMenuItem(name);
		item->Name = name;

		this->m_itmPointerToolStripMenuItem->DropDownItems->Add(item);
	}
}

/* Remove a menu item object from the Insert context menu */
void ZPacketBuilder::RemoveInsertMenuItem ( String^ name )
{
	if ( this->m_ctxPacketMenu->InvokeRequired ) {
		this->m_ctxPacketMenu->Invoke(gcnew RemoveInsertMenuItemCaller(this, &ZPacketBuilder::RemoveInsertMenuItem), gcnew array<Object^>{ name });
	} else {
		int index = this->m_itmPointerToolStripMenuItem->DropDownItems->IndexOfKey(name);

		if ( index != ( -1 ) )
			this->m_itmPointerToolStripMenuItem->DropDownItems->RemoveAt(index);
	}
}

/* Remove all menu items from the Insert context menu */
void ZPacketBuilder::ClearInsertMenu ( void )
{
	if ( this->m_ctxPacketMenu->InvokeRequired ) {
		this->m_ctxPacketMenu->Invoke(gcnew ClearInsertMenuCaller(this, &ZPacketBuilder::ClearInsertMenu));
	} else {
		this->m_itmPointerToolStripMenuItem->DropDownItems->Clear();
	}
}

void ZPacketBuilder::OnClearClick ( Object^ sender, EventArgs^ e )
{
	this->m_txtPacket->Clear();
	this->m_txtStream->Clear();
}

void ZPacketBuilder::OnCopyClick ( Object^ sender, EventArgs^ e )
{
	if ( this->m_txtPacket->TextLength > 0 ) {
		if ( ((bool)(this->m_txtStream->Tag)) ) {
			ZContext::G->Application->SetSendPacketText(this->m_txtStream->Text);
		} else {
			::MessageBox((::HWND)(::LPVOID)(this->Handle), TEXT("Could not copy this packet to the input field because it is not valid.\r\nPlease correct the issue and try again."),
				TEXT("Application Error"), MB_OK | MB_ICONWARNING | MB_APPLMODAL | MB_SETFOREGROUND);
		}
	}
}

void ZPacketBuilder::OnSendClick ( Object^ sender, EventArgs^ e )
{
	if ( this->m_txtPacket->TextLength > 0 ) {
		if ( ((bool)(this->m_txtStream->Tag)) ) {
			this->m_txtPacket->Enabled = false;
			this->m_btnSend->Enabled   = false;

			try {
				String^  rawBytes = this->m_txtStream->Text->Replace(L" ", String::Empty);
				::DWORD	 dwOffset = 0;
				::DWORD  dwLength = ( rawBytes->Length / 2 );
				::LPBYTE lpBytes  = new ::BYTE [ dwLength ];				

				for ( int j = 0; ( dwOffset < dwLength ) && ( ( j + 1 ) < rawBytes->Length ); dwOffset++, j += 2 )
					lpBytes[dwOffset] = Byte::Parse(rawBytes->Substring(j, 2), NumberStyles::HexNumber, CultureInfo::InvariantCulture);

				try {
					SendPacket(lpBytes, dwLength);
				} catch ( Exception^ ) {
				} finally {
					delete [] lpBytes;
				}
			} finally {
				this->m_txtPacket->Enabled = true;
				this->m_btnSend->Enabled   = true;		
			}
		} else {
			::MessageBox((::HWND)(::LPVOID)(this->Handle), TEXT("Could not send this packet to the input field because it is not valid.\r\nPlease correct the issue and try again."),
				TEXT("Application Error"), MB_OK | MB_ICONWARNING | MB_APPLMODAL | MB_SETFOREGROUND);
		}
	}
}

void ZPacketBuilder::OnPacketTextChanged ( Object^ sender, System::EventArgs^ e )
{
	this->m_btnClear->Enabled = ( this->m_txtPacket->TextLength > 0 );
	this->m_txtStream->Tag    = false;
	this->m_btnCopy->Enabled  = false;
	this->m_btnSend->Enabled  = false;

	if ( this->m_txtPacket->TextLength > 0 ) {
		String^ s = ZParser::GetByteCode(this->m_txtPacket->Text);

		if ( s == nullptr ) {
			this->m_txtStream->Text = L"Could not generate the byte code for the user input because the packet is in an invalid format";
		} else {
			this->m_txtStream->Text = Regex::Replace(s, L"[0-9a-fA-F]{2}", L" $0", RegexOptions::CultureInvariant)->Trim();
			this->m_txtStream->Tag  = true;
			this->m_btnCopy->Enabled = true;
			this->m_btnSend->Enabled = true;
		}
	} else {
		this->m_txtStream->Text = String::Empty;
	}
}

void ZPacketBuilder::OnCutTextClick ( Object^ sender, EventArgs^ e )
{
	if ( this->m_txtPacket->TextLength > 0 )
		this->m_txtPacket->Cut();
}

void ZPacketBuilder::OnCopyTextClick ( Object^ sender, EventArgs^ e )
{
	if ( this->m_txtPacket->TextLength > 0 )
		this->m_txtPacket->Copy();
}

void ZPacketBuilder::OnPasteTextClick ( Object^ sender, EventArgs^ e )
{
	if ( ::IsClipboardFormatAvailable(CF_TEXT) || ::IsClipboardFormatAvailable(CF_UNICODETEXT) )
		this->m_txtPacket->Paste();
}

void ZPacketBuilder::OnRandByteClick ( Object^ sender, EventArgs^ e )
{
	array<::BYTE>^ bytes = gcnew array<::BYTE>(1);

	Randomize->NextBytes(bytes);

	String^ s = String::Concat(L"#", bytes[0].ToString());

	if ( this->m_txtPacket->Focused ) {
		int index = this->m_txtPacket->SelectionStart;
		this->m_txtPacket->Text = this->m_txtPacket->Text->Insert(this->m_txtPacket->SelectionStart, s);
		this->m_txtPacket->SelectionStart = index + s->Length;
	}
}

void ZPacketBuilder::OnRandInt16Click ( Object^ sender, EventArgs^ e )
{
	array<::BYTE>^ bytes = gcnew array<::BYTE>(2);

	Randomize->NextBytes(bytes);

	String^ s = String::Concat(L"#", BitConverter::ToInt16(bytes,0).ToString());

	if ( this->m_txtPacket->Focused ) {
		int index = this->m_txtPacket->SelectionStart;
		this->m_txtPacket->Text = this->m_txtPacket->Text->Insert(this->m_txtPacket->SelectionStart, s);
		this->m_txtPacket->SelectionStart = index + s->Length;
	}
}

void ZPacketBuilder::OnRandInt32Click ( Object^ sender, EventArgs^ e )
{
	array<::BYTE>^ bytes = gcnew array<::BYTE>(4);

	Randomize->NextBytes(bytes);

	String^ s = String::Concat(L"#", BitConverter::ToInt32(bytes,0).ToString());

	if ( this->m_txtPacket->Focused ) {
		int index = this->m_txtPacket->SelectionStart;
		this->m_txtPacket->Text = this->m_txtPacket->Text->Insert(this->m_txtPacket->SelectionStart, s);
		this->m_txtPacket->SelectionStart = index + s->Length;
	}
}

void ZPacketBuilder::OnRandAsciiClick ( Object^ sender, EventArgs^ e )
{
	int chr;

	do {
		chr = Randomize->Next(0x20, 0x7F);
	} while ( chr == 0x22 );

	String^ s = String::Concat(L"'", (::WCHAR)chr, L"'");

	if ( this->m_txtPacket->Focused ) {
		int index = this->m_txtPacket->SelectionStart;
		this->m_txtPacket->Text = this->m_txtPacket->Text->Insert(this->m_txtPacket->SelectionStart, s);
		this->m_txtPacket->SelectionStart = index + s->Length;
	}
}

void ZPacketBuilder::OnRandStringClick ( Object^ sender, EventArgs^ e )
{
	using namespace System::Text;

	int length = Randomize->Next(4, 64);
	StringBuilder^ sb = gcnew StringBuilder(length);

	for ( int i = 0, j = 0; i < length; i++ ) {
		do {
			j = Randomize->Next(0x20, 0x7F);
		} while ( j == 0x22 );

		sb->Append((::WCHAR)j);
	}

	String^ s = String::Format(L"\"{0}\"", sb->ToString());

	if ( this->m_txtPacket->Focused ) {
		int index = this->m_txtPacket->SelectionStart;
		this->m_txtPacket->Text = this->m_txtPacket->Text->Insert(this->m_txtPacket->SelectionStart, s);
		this->m_txtPacket->SelectionStart = index + s->Length;
	}
}

void ZPacketBuilder::OnPointerDropDownItemClicked ( Object^ sender, ToolStripItemClickedEventArgs^ e )
{
	if ( this->m_txtPacket->Focused ) {
		int value = ZContext::G->Memory->GetValue(e->ClickedItem->Name);

		if ( value != ( -1 ) ) {
			String^ s = String::Format(L"#{0}", value);
			int index = this->m_txtPacket->SelectionStart;
			this->m_txtPacket->Text = this->m_txtPacket->Text->Insert(this->m_txtPacket->SelectionStart, s);
			this->m_txtPacket->SelectionStart = index + s->Length;
		}
	}
}

void ZPacketBuilder::OnPacketMenuOpening ( Object^ sender, CancelEventArgs^ e )
{
	this->m_txtPacket->Focus();
}