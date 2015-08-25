#include "Z.h"
#include "Z_CLI.h"
#include "Z_GUI.h"

using namespace Z;
using namespace System::Globalization;
using namespace System::IO;
using namespace System::Text;

/* Clear all items in this collection */
void ZCollection::ClearItems ( void )
{
	if ( this->m_lstPacketList->InvokeRequired ) {
		this->m_lstPacketList->Invoke(gcnew ClearItemsCaller(this, &ZCollection::ClearItems));
	} else {
		this->m_lstPacketList->Items->Clear();

		this->m_lblStatus->Text = String::Empty;
	}
}

/* Append a new ListViewItem */
void ZCollection::AppendItem ( ListViewItem^ listViewItem )
{
	if ( this->m_lstPacketList->InvokeRequired ) {
		this->m_lstPacketList->Invoke(gcnew AppendItemCaller(this, &ZCollection::AppendItem), gcnew array<Object^>{ listViewItem });
	} else {
		this->m_lstPacketList->Items->Add(listViewItem);

		this->m_lblStatus->Text = String::Format(L"{0} Packets", this->m_lstPacketList->Items->Count);

		this->m_itmExportToolStripMenuItem->Enabled   = ( this->m_lstPacketList->Items->Count > 0 );
		this->m_itmExportAsToolStripMenuItem->Enabled = ( this->m_lstPacketList->Items->Count > 0 );
		this->m_itmClearToolStripMenuItem->Enabled    = ( this->m_lstPacketList->Items->Count > 0 );
	}
}

void ZCollection::OnExportClick ( Object^ sender, EventArgs^ e )
{
	SaveFileDialog^ dialog               = gcnew SaveFileDialog;
	dialog->AddExtension                 = true;
	dialog->AutoUpgradeEnabled           = true;
	dialog->DefaultExt                   = L"zpl";
	dialog->DereferenceLinks             = true;
	dialog->FileName                     = String::Format(L"Z-{0}.zpl", DateTime::Now.ToString(L"s", CultureInfo::InvariantCulture))->Replace(L":", L"-");
	dialog->Filter                       = L"Z Packet Collections (*.zpl)|*.zpl|All files (*.*)|*.*";
	dialog->InitialDirectory             = Environment::GetFolderPath(Environment::SpecialFolder::MyDocuments);
	dialog->OverwritePrompt              = true;
	dialog->RestoreDirectory             = true;
	dialog->SupportMultiDottedExtensions = true;

	try {
		if ( dialog->ShowDialog(this) == ::DialogResult::OK ) {	
			StreamWriter^ sw = gcnew StreamWriter(dialog->FileName, false, Encoding::UTF8);

			try {
				for each ( ListViewItem^ listViewItem in this->m_lstPacketList->Items ) {
					switch ( listViewItem->StateImageIndex ) {
						case 0:
							sw->Write(L"<< ");
							break;
						case 1:
							sw->Write(L">> ");
							break;
					}

					sw->WriteLine(listViewItem->SubItems[L"Packet2"]->Text);
				}
			} finally {
				sw->Flush();
				sw->Close();
			}
		}
	} finally {
		delete (IDisposable^)dialog;
	}
}

void ZCollection::OnExportAsClick ( Object^ sender, EventArgs^ e )
{
	SaveFileDialog^ dialog               = gcnew SaveFileDialog;
	dialog->AddExtension                 = true;
	dialog->AutoUpgradeEnabled           = true;
	dialog->DefaultExt                   = L"zpl";
	dialog->DereferenceLinks             = true;
	dialog->FileName                     = String::Format(L"Z-{0}.zpl", DateTime::Now.ToString(L"s", CultureInfo::InvariantCulture))->Replace(L":", L"-");
	dialog->Filter                       = L"Z Packet Collections (*.zpl)|*.zpl|All files (*.*)|*.*";
	dialog->InitialDirectory             = Environment::GetFolderPath(Environment::SpecialFolder::MyDocuments);
	dialog->OverwritePrompt              = true;
	dialog->RestoreDirectory             = true;
	dialog->SupportMultiDottedExtensions = true;

	try {
		if ( dialog->ShowDialog(this) == ::DialogResult::OK ) {	
			StreamWriter^ sw = gcnew StreamWriter(dialog->FileName, false, Encoding::UTF8);

			try {
				for each ( ListViewItem^ listViewItem in this->m_lstPacketList->Items ) {
					switch ( listViewItem->StateImageIndex ) {
						case 0:
							sw->Write(L"<< ");
							break;
						case 1:
							sw->Write(L">> ");
							break;
					}

					sw->WriteLine(listViewItem->SubItems[L"Packet2"]->Text);
				}
			} finally {
				sw->Flush();
				sw->Close();
			}
		}
	} finally {
		delete (IDisposable^)dialog;
	}
}

void ZCollection::OnClearClick ( Object^ sender, EventArgs^ e )
{
	if ( this->m_lstPacketList->Items->Count > 0 ) {
		if ( this->m_lstPacketList->SelectedIndices->Count > 0 ) {
			do {
				this->m_lblStatus->Text = String::Format(L"{0} Packets", this->m_lstPacketList->Items->Count);

				this->m_lstPacketList->Items->RemoveAt(this->m_lstPacketList->SelectedIndices[0]);
			} while ( this->m_lstPacketList->SelectedIndices->Count > 0 );
		} else {
			this->m_lblStatus->Text = String::Empty;
			
			this->m_lstPacketList->Items->Clear();			
		}
	}

	this->m_itmExportToolStripMenuItem->Enabled   = ( this->m_lstPacketList->Items->Count > 0 );
	this->m_itmExportAsToolStripMenuItem->Enabled = ( this->m_lstPacketList->Items->Count > 0 );
	this->m_itmClearToolStripMenuItem->Enabled    = ( this->m_lstPacketList->Items->Count > 0 );
}

void ZCollection::OnListItemMouseHover ( Object^ sender, ListViewItemMouseHoverEventArgs^ e )
{
	this->m_ttpToolTip->Show(e->Item->ToolTipText, e->Item->ListView);
}

void ZCollection::OnListItemActivate ( Object^ sender, EventArgs^ e )
{
	if ( this->m_lstPacketList->SelectedIndices->Count > 0 )
		ZContext::G->Application->SetPacketText(dynamic_cast<String^>(this->m_lstPacketList->Items[this->m_lstPacketList->SelectedIndices[0]]->Tag));
}

void ZCollection::OnToolTipPopup ( Object^ sender, PopupEventArgs^ e )
{
	System::Drawing::Size size = e->ToolTipSize;
	size.Width = Math::Min(size.Width, 300);
	e->ToolTipSize = size;
}

void ZCollection::OnListItemSelectionChanged ( Object^  sender, ListViewItemSelectionChangedEventArgs^ e )
{
	if ( e->IsSelected ) {
		switch ( e->Item->StateImageIndex ) {
			case Z_PACKET_STREAM_RECEIVE:
				ZContext::G->Application->SetRecvPacketText(e->Item->SubItems[L"Format2"]->Text);
				break;
			case Z_PACKET_STREAM_SEND:
				ZContext::G->Application->SetSendPacketText(e->Item->SubItems[L"Format2"]->Text);
				break;
		}
	}
}
