#include "Z.h"

/* MapleStory Send object address  */
extern ULONG_PTR ulMSSendObject;
/* MapleStory Send method address */
extern ULONG_PTR ulMSSendMethod;

extern ULONG_PTR ulMSRecvMethod;

#include "Z_CLI.h"
#include "Z_GUI.h"

using namespace Z;
using namespace System::Diagnostics;
using namespace System::Globalization;
using namespace System::IO;
using namespace System::Text;
using namespace System::Text::RegularExpressions;
using namespace System::Threading;

::DWORD dwSelectedStream = Z_PACKET_STREAM_SEND;

/* Lock-out certain features based on installed hooks */
void ZApplication::InitializeProtections ( void )
{
	this->m_itmViewRecvToolStripMenuItem->Enabled = ( IsMSRecvHooked() == TRUE );

	if ( this->m_itmViewRecvToolStripMenuItem->Enabled != true )
		this->m_tbPackets->TabPages->RemoveAt(0);

	this->m_itmViewSentToolStripMenuItem->Enabled = ( IsMSSendHooked() == TRUE );

	if ( this->m_itmViewRecvToolStripMenuItem->Enabled != true )
		this->m_tbPackets->TabPages->RemoveAt(1);
}

/* Append the necessary collection items to the menus */
void ZApplication::InitializeCollections ( void )
{
	int zero = 0;
	this->m_itmFavoritesToolStripMenuItem->Tag = zero;

	this->m_itmCollectionsToolStripMenuItem->DropDownItems
		->Add(gcnew ToolStripSeparator());

	ToolStripMenuItem^ item;

	for ( int index = 2; index < Z_COLLECTION_COUNT + 2; index++ ) {
		/* Main Menu > Collections Menu */
		item      = gcnew ToolStripMenuItem(String::Format("Collection {0}", ( index - 1 )));
		item->Tag = index;

		this->m_itmCollectionsToolStripMenuItem->DropDownItems->Add(item);

		/* Right-Click > Collect Menu */
		item       = gcnew ToolStripMenuItem(String::Format("Collection {0}", ( index - 1 )));
		item->Tag = index;

		this->m_itmCollectToolStripMenuItem->DropDownItems->Add(item);
	}
}

void ZApplication::OnLoad ( EventArgs^ e )
{
	__super::OnLoad(e);

	if ( ::SetProcessWorkingSetSize(::GetCurrentProcess(), (::SIZE_T)( -1 ), (::SIZE_T)( -1 )) != TRUE )
		Error(TEXT("SetProcessWorkingSetSize"));
}

void ZApplication::OnClosing ( CancelEventArgs^ e )
{
	__super::OnClosing(e);

	if ( this->m_itmSystemTrayIconToolStripMenuItem->Checked ) {
		e->Cancel = this->m_itmMinimizeOnCloseToolStripMenuItem->Checked;

		if ( e->Cancel != false )
			this->Hide();
	}

	if ( ::SetProcessWorkingSetSize(::GetCurrentProcess(), (::SIZE_T)( -1 ), (::SIZE_T)( -1 )) != TRUE )
		Error(TEXT("SetProcessWorkingSetSize"));
}

void ZApplication::OnClosed ( EventArgs^ e )
{
	__super::OnClosed(e);

	ZContext::G->Templates->ExportFile(Path::Combine(Application::UserAppDataPath, L"Z.t"));
}

extern ::HANDLE hLoader;

void ZApplication::OnShown ( EventArgs ^e )
{
	__super::OnShown(e);

	if ( hLoader != NULL )
		::TerminateThread(hLoader, EXIT_SUCCESS);

	if ( File::Exists(Path::Combine(Application::UserAppDataPath, L"Z.t")) )
		ZContext::G->Templates->ImportFile(Path::Combine(Application::UserAppDataPath, L"Z.t"));
}

/* Append a menu item object to the Insert context menu */
void ZApplication::AppendInsertMenuItem ( String^ name )
{
	if ( this->m_ctxTextMenu->InvokeRequired ) {
		this->m_ctxTextMenu->Invoke(gcnew AppendInsertMenuItemCaller(this, &ZApplication::AppendInsertMenuItem), gcnew array<Object^>{ name });
	} else {
		ToolStripMenuItem^ item = gcnew ToolStripMenuItem(name);
		item->Name = name;

		this->m_itmValueToolStripMenuItem->DropDownItems->Add(item);
	}
}

/* Remove a menu item object from the Insert context menu */
void ZApplication::RemoveInsertMenuItem ( String^ name )
{
	if ( this->m_ctxTextMenu->InvokeRequired ) {
		this->m_ctxTextMenu->Invoke(gcnew RemoveInsertMenuItemCaller(this, &ZApplication::RemoveInsertMenuItem), gcnew array<Object^>{ name });
	} else {
		int index = this->m_itmValueToolStripMenuItem->DropDownItems->IndexOfKey(name);

		if ( index != ( -1 ) )
			this->m_itmValueToolStripMenuItem->DropDownItems->RemoveAt(index);
	}
}

/* Remove all menu items from the Insert context menu */
void ZApplication::ClearInsertMenu ( void )
{
	if ( this->m_ctxTextMenu->InvokeRequired ) {
		this->m_ctxTextMenu->Invoke(gcnew ClearInsertMenuCaller(this, &ZApplication::ClearInsertMenu));
	} else {
		this->m_itmValueToolStripMenuItem->DropDownItems->Clear();
	}
}

/* Apply a template to the items of the recv and sent lists */
void ZApplication::ApplyTemplate ( ZTemplate^ t )
{
	if ( this->m_lstRecvList->Items->Count > 0 ) {
		for each ( ListViewItem^ listViewItem in this->m_lstRecvList->Items ) {
			if ( t->IsMatch(listViewItem->SubItems[L"Packet"]->Text) && t->RecvPackets ) {
				listViewItem->SubItems[L"Code"]->ForeColor = t->ForeColor;
				listViewItem->SubItems[L"Code"]->BackColor = t->BackColor;
				listViewItem->SubItems[L"Code"]->Font      = this->m_lstRecvList->Font;
				listViewItem->SubItems[L"Code"]->Text      = t->Alias;

				if ( t->Colorize ) {
					listViewItem->SubItems[L"Size"]->ForeColor = t->ForeColor;
					listViewItem->SubItems[L"Size"]->BackColor = t->BackColor;
					listViewItem->SubItems[L"Data"]->ForeColor = t->ForeColor;
					listViewItem->SubItems[L"Data"]->BackColor = t->BackColor;
				} else {
					listViewItem->SubItems[L"Size"]->ForeColor = this->m_lstRecvList->ForeColor;
					listViewItem->SubItems[L"Size"]->BackColor = this->m_lstRecvList->BackColor;
					listViewItem->SubItems[L"Data"]->ForeColor = this->m_lstRecvList->ForeColor;
					listViewItem->SubItems[L"Data"]->BackColor = this->m_lstRecvList->BackColor;
				}

				if ( t->NoFormat ) {
					listViewItem->SubItems["Data"]->Text = listViewItem->SubItems[L"Packet2"]->Text;
				} else {
					listViewItem->SubItems["Data"]->Text = listViewItem->SubItems[L"Format"]->Text;
				}
			}
		}
	}

	if ( this->m_lstSendList->Items->Count > 0 ) {
		for each ( ListViewItem^ listViewItem in this->m_lstSendList->Items ) {
			if ( t->IsMatch(listViewItem->SubItems[L"Packet"]->Text) && t->SendPackets ) {
				listViewItem->SubItems[L"Code"]->ForeColor = t->ForeColor;
				listViewItem->SubItems[L"Code"]->BackColor = t->BackColor;
				listViewItem->SubItems[L"Code"]->Font      = this->m_lstSendList->Font;
				listViewItem->SubItems[L"Code"]->Text      = t->Alias;

				if ( t->Colorize ) {
					listViewItem->SubItems[L"Size"]->ForeColor = t->ForeColor;
					listViewItem->SubItems[L"Size"]->BackColor = t->BackColor;
					listViewItem->SubItems[L"Data"]->ForeColor = t->ForeColor;
					listViewItem->SubItems[L"Data"]->BackColor = t->BackColor;
				} else {
					listViewItem->SubItems[L"Size"]->ForeColor = this->m_lstSendList->ForeColor;
					listViewItem->SubItems[L"Size"]->BackColor = this->m_lstSendList->BackColor;
					listViewItem->SubItems[L"Data"]->ForeColor = this->m_lstSendList->ForeColor;
					listViewItem->SubItems[L"Data"]->BackColor = this->m_lstSendList->BackColor;
				}

				if ( t->NoFormat ) {
					listViewItem->SubItems["Data"]->Text = listViewItem->SubItems[L"Packet2"]->Text;
				} else {
					listViewItem->SubItems["Data"]->Text = listViewItem->SubItems[L"Format"]->Text;
				}
			}
		}
	}
}

void ZApplication::ResetTemplate ( void )
{
	System::Drawing::Font^ font = (gcnew System::Drawing::Font(FontFamily::GenericMonospace, 8.25f, FontStyle::Regular, GraphicsUnit::Point));
	ZTemplate^ t = nullptr;

	if ( this->m_lstRecvList->Items->Count > 0 ) {
		for each ( ListViewItem^ listViewItem in this->m_lstRecvList->Items ) {
			if ( ( t = ZContext::G->Templates->GetTemplate(listViewItem->SubItems[L"Packet"]->Text, Z_PACKET_STREAM_RECEIVE) ) != nullptr ) {
				listViewItem->SubItems[L"Code"]->ForeColor = t->ForeColor;
				listViewItem->SubItems[L"Code"]->BackColor = t->BackColor;
				listViewItem->SubItems[L"Code"]->Font      = this->m_lstRecvList->Font;
				listViewItem->SubItems[L"Code"]->Text      = t->Alias;

				if ( t->Colorize ) {
					listViewItem->SubItems[L"Size"]->ForeColor = t->ForeColor;
					listViewItem->SubItems[L"Size"]->BackColor = t->BackColor;
					listViewItem->SubItems[L"Data"]->ForeColor = t->ForeColor;
					listViewItem->SubItems[L"Data"]->BackColor = t->BackColor;
				} else {
					listViewItem->SubItems[L"Size"]->ForeColor = this->m_lstRecvList->ForeColor;
					listViewItem->SubItems[L"Size"]->BackColor = this->m_lstRecvList->BackColor;
					listViewItem->SubItems[L"Data"]->ForeColor = this->m_lstRecvList->ForeColor;
					listViewItem->SubItems[L"Data"]->BackColor = this->m_lstRecvList->BackColor;
				}

				if ( t->NoFormat ) {
					listViewItem->SubItems["Data"]->Text = listViewItem->SubItems[L"Packet2"]->Text;
				} else {
					listViewItem->SubItems["Data"]->Text = listViewItem->SubItems[L"Format"]->Text;
				}
			} else {
				listViewItem->SubItems[L"Size"]->ForeColor = this->m_lstRecvList->ForeColor;
				listViewItem->SubItems[L"Size"]->BackColor = this->m_lstRecvList->BackColor;
				listViewItem->SubItems[L"Code"]->ForeColor = this->m_lstRecvList->ForeColor;
				listViewItem->SubItems[L"Code"]->BackColor = this->m_lstRecvList->BackColor;
				listViewItem->SubItems[L"Code"]->Text      = ((::WORD)(listViewItem->SubItems[L"Code"]->Tag)).ToString(L"X4")->Insert(2, L" ");
				listViewItem->SubItems[L"Code"]->Font      = font;
				listViewItem->SubItems[L"Data"]->ForeColor = this->m_lstRecvList->ForeColor;
				listViewItem->SubItems[L"Data"]->BackColor = this->m_lstRecvList->BackColor;
				listViewItem->SubItems[L"Data"]->Text       = listViewItem->SubItems[L"Format"]->Text;
			}
		}
	}

	if ( this->m_lstSendList->Items->Count > 0 ) {
		for each ( ListViewItem^ listViewItem in this->m_lstSendList->Items ) {
			if ( ( t = ZContext::G->Templates->GetTemplate(listViewItem->SubItems[L"Packet"]->Text, Z_PACKET_STREAM_RECEIVE) ) != nullptr ) {
				listViewItem->SubItems[L"Code"]->ForeColor = t->ForeColor;
				listViewItem->SubItems[L"Code"]->BackColor = t->BackColor;
				listViewItem->SubItems[L"Code"]->Font      = this->m_lstSendList->Font;
				listViewItem->SubItems[L"Code"]->Text      = t->Alias;

				if ( t->Colorize ) {
					listViewItem->SubItems[L"Size"]->ForeColor = t->ForeColor;
					listViewItem->SubItems[L"Size"]->BackColor = t->BackColor;
					listViewItem->SubItems[L"Data"]->ForeColor = t->ForeColor;
					listViewItem->SubItems[L"Data"]->BackColor = t->BackColor;
				} else {
					listViewItem->SubItems[L"Size"]->ForeColor = this->m_lstSendList->ForeColor;
					listViewItem->SubItems[L"Size"]->BackColor = this->m_lstSendList->BackColor;
					listViewItem->SubItems[L"Data"]->ForeColor = this->m_lstSendList->ForeColor;
					listViewItem->SubItems[L"Data"]->BackColor = this->m_lstSendList->BackColor;
				}

				if ( t->NoFormat ) {
					listViewItem->SubItems["Data"]->Text = listViewItem->SubItems[L"Packet2"]->Text;
				} else {
					listViewItem->SubItems["Data"]->Text = listViewItem->SubItems[L"Format"]->Text;
				}
			} else {
				listViewItem->SubItems[L"Size"]->ForeColor = this->m_lstSendList->ForeColor;
				listViewItem->SubItems[L"Size"]->BackColor = this->m_lstSendList->BackColor;
				listViewItem->SubItems[L"Code"]->ForeColor = this->m_lstSendList->ForeColor;
				listViewItem->SubItems[L"Code"]->BackColor = this->m_lstSendList->BackColor;
				listViewItem->SubItems[L"Code"]->Text      = ((::WORD)(listViewItem->SubItems[L"Code"]->Tag)).ToString(L"X4")->Insert(2, L" ");
				listViewItem->SubItems[L"Code"]->Font      = font;
				listViewItem->SubItems[L"Data"]->ForeColor = this->m_lstSendList->ForeColor;
				listViewItem->SubItems[L"Data"]->BackColor = this->m_lstSendList->BackColor;
				listViewItem->SubItems[L"Data"]->Text       = listViewItem->SubItems[L"Format"]->Text;
			}
		}
	}
}

/* Set the text of the last focused packet field */
void ZApplication::SetPacketText ( String^ text )
{
	switch ( dwSelectedStream ) {
		case Z_PACKET_STREAM_RECEIVE:
			SetRecvPacketText(text);
			break;
		case Z_PACKET_STREAM_SEND:
			SetSendPacketText(text);
			break;
	}
}

/* Append a ListViewItem object to the received packets list */
void ZApplication::AppendRecvListItem ( ListViewItem^ listViewItem )
{
	if ( this->InvokeRequired ) {
		this->Invoke(gcnew AppendItemCaller(this, &ZApplication::AppendRecvListItem), gcnew array<Object^>{ listViewItem });
	} else {
		if ( this->m_lstRecvList->Items->Count > Z_RECV_BUFFER_LENGTH )
			this->m_lstRecvList->Items->RemoveAt(0);

		this->m_lstRecvList->Items->Add(listViewItem);

		if ( this->m_itmFollowItemsToolStripMenuItem->Checked ) {
			if ( this->m_lstRecvList->SelectedIndices->Count > 0 ) {
				this->m_lstRecvList->EnsureVisible(this->m_lstRecvList->SelectedIndices[0]);
			} else {
				this->m_lstRecvList->EnsureVisible(this->m_lstRecvList->Items->Count - 1);
			}
		}
	}
}

/* Set the text of the receive input field */
void ZApplication::SetRecvPacketText ( String^ text )
{
	if ( this->InvokeRequired ) {
		this->Invoke(gcnew SetPacketTextCaller(this, &ZApplication::SetRecvPacketText), gcnew array<Object^>{ text });
	} else {
		this->m_txtRecvPacket->Text = text;
	}
}

/* Append a ListViewItem object to the sent packets list */
void ZApplication::AppendSendListItem ( ListViewItem^ listViewItem )
{
	if ( this->InvokeRequired ) {
		this->Invoke(gcnew AppendItemCaller(this, &ZApplication::AppendSendListItem), gcnew array<Object^>{ listViewItem });
	} else {
		if ( this->m_lstSendList->Items->Count > Z_SEND_BUFFER_LENGTH )
			this->m_lstSendList->Items->RemoveAt(0);

		this->m_lstSendList->Items->Add(listViewItem);

		if ( this->m_itmFollowItemsToolStripMenuItem->Checked ) {
			if ( this->m_lstSendList->SelectedIndices->Count > 0 ) {
				this->m_lstSendList->EnsureVisible(this->m_lstSendList->SelectedIndices[0]);
			} else {
				this->m_lstSendList->EnsureVisible(this->m_lstSendList->Items->Count - 1);
			}
		}
	}
}

/* Set the text of the receive input field */
void ZApplication::SetSendPacketText ( String^ text )
{
	if ( this->InvokeRequired ) {
		this->Invoke(gcnew SetPacketTextCaller(this, &ZApplication::SetSendPacketText), gcnew array<Object^>{ text });
	} else {
		this->m_txtSendPacket->Text = text;
	}
}

/* Number of packets received total */
extern volatile ::UINT64 PacketsRecv;
/* Number of packets sent total */
extern volatile ::UINT64 PacketsSent;
/* Number of bytes received total */
extern volatile ::UINT64 BytesRecv;
/* Number of bytes sent total */
extern volatile ::UINT64 BytesSent;

/* Get the standard measurement for the byte count */
String^ GetByteCount ( __in ::UINT64 bytes )
{
	if ( bytes >= TEBIBYTE_UNIT ) {
		return String::Format(L"{0:F2} TiB", ( (double)bytes / TEBIBYTE_UNIT ));
	} else if ( bytes >= GIBIBYTE_UNIT ) {
		return String::Format(L"{0:F2} GiB", ( (double)bytes / GIBIBYTE_UNIT ));
	} else if ( bytes >= MEBIBYTE_UNIT ) {
		return String::Format(L"{0:F2} MiB", ( (double)bytes / MEBIBYTE_UNIT ));
	} else if ( bytes >= KIBIBYTE_UNIT ) {
		return String::Format(L"{0:F2} KiB", ( (double)bytes / KIBIBYTE_UNIT ));
	} else {
		return String::Format(L"{0} bytes", bytes);
	}
}
/* Append a ListViewItem object to the sent packets list */
void ZApplication::AppendHistoryListItem ( ListViewItem^ listViewItem )
{
	if ( this->InvokeRequired ) {
		this->Invoke(gcnew AppendItemCaller(this, &ZApplication::AppendHistoryListItem), gcnew array<Object^>{ listViewItem });
	} else {
		if ( this->m_lstBothList->Items->Count > Z_HISTORY_BUFFER_LENGTH )
			this->m_lstBothList->Items->RemoveAt(0);

		this->m_lstBothList->Items->Add(listViewItem);

		if ( this->m_itmFollowItemsToolStripMenuItem->Checked ) {
			if ( this->m_lstBothList->SelectedIndices->Count > 0 ) {
				this->m_lstBothList->EnsureVisible(this->m_lstBothList->SelectedIndices[0]);
			} else {
				this->m_lstBothList->EnsureVisible(this->m_lstBothList->Items->Count - 1);
			}
		}
	}

	this->m_lblCounter->Text = String::Format(L"{0:N0} Received ({1}),  {2:N0} Sent ({3})",
		PacketsRecv, GetByteCount(BytesRecv), PacketsSent, GetByteCount(BytesSent));
}

void ZApplication::OnMemoryClick ( Object^ sender, EventArgs^ e )
{
	if ( ZContext::G->Memory->Visible != true )
		ZContext::G->Memory->Show(this);
}

void ZApplication::OnQuitGameClick ( Object^ sender, EventArgs^ e )
{
}

void ZApplication::OnExitGameClick ( Object^ sender, EventArgs^ e )
{
	extern ::BOOL bExitProcess;
	bExitProcess = TRUE;

	this->m_itmMinimizeOnCloseToolStripMenuItem->Checked = false;

	this->Close();
}

void ZApplication::OnExitClick ( Object^ sender, EventArgs^ e )
{
	this->m_itmMinimizeOnCloseToolStripMenuItem->Checked = false;

	this->Close();
}

void ZApplication::OnViewRecvClick ( Object^ sender, EventArgs^ e )
{
	this->m_tbPackets->SelectTab(0);
}

void ZApplication::OnViewSentClick ( Object^ sender, EventArgs^ e )
{
	this->m_tbPackets->SelectTab(1);
}

void ZApplication::OnTemplatesClick ( Object^ sender, EventArgs^ e )
{
	if ( ZContext::G->Templates->Visible != true )
		ZContext::G->Templates->Show(this);
}

void ZApplication::OnBuilderClick ( Object^ sender, EventArgs^ e )
{
	if ( ZContext::G->PacketBuilder->Visible != true )
		ZContext::G->PacketBuilder->Show(this);
}

void ZApplication::OnHistoryClick ( Object^ sender, EventArgs^ e )
{
	this->m_tbPackets->SelectTab(2);
}

void ZApplication::OnBlockedRecvClick ( Object^ sender, EventArgs^ e )
{
	if ( ZContext::G->BlockedRecvPatterns->Visible != true )
		ZContext::G->BlockedRecvPatterns->Show(this);
}

void ZApplication::OnIgnoredRecvClick ( Object^ sender, EventArgs^ e )
{
	if ( ZContext::G->IgnoredRecvPatterns->Visible != true )
		ZContext::G->IgnoredRecvPatterns->Show(this);
}

void ZApplication::OnBlockedSendClick ( Object^ sender, EventArgs^ e )
{
	if ( ZContext::G->BlockedSendPatterns->Visible != true )
		ZContext::G->BlockedSendPatterns->Show(this);
}

void ZApplication::OnIgnoredSendClick ( Object^ sender, EventArgs^ e )
{
	if ( ZContext::G->IgnoredSendPatterns->Visible != true )
		ZContext::G->IgnoredSendPatterns->Show(this);
}

void ZApplication::OnCustomClick ( Object^ sender, EventArgs^ e )
{
	if ( ZContext::G->UserCreatedPatterns->Visible != true )
		ZContext::G->UserCreatedPatterns->Show(this);
}

void ZApplication::OnCollectionsDropDrownItemClicked ( Object^ sender, ToolStripItemClickedEventArgs^ e )
{
	if ( ZContext::G->Collections[((int)(e->ClickedItem->Tag))]->Visible != true )
		ZContext::G->Collections[((int)(e->ClickedItem->Tag))]->Show(this);
}

void ZApplication::OnExecuteClick ( Object^ sender, EventArgs^ e )
{
}

void ZApplication::OnFloodControlClick ( Object^ sender, EventArgs^ e )
{
	if ( ZContext::G->FloodControl->Visible != true )
		ZContext::G->FloodControl->Show(this);
}

void PageLink ( Object^ obj )
{
	String^ href;

	if ( ( href = dynamic_cast<String^>(obj) ) != nullptr )
		Process::Start(href);
}

void ZApplication::OnHelpDropDownItemClicked ( Object^ sender, ToolStripItemClickedEventArgs^ e )
{
	if ( String::Equals(e->ClickedItem->Name, L"m_itmAboutToolStripMenuItem", StringComparison::InvariantCultureIgnoreCase) ) {
		if ( ZContext::G->About->Visible != true )
			ZContext::G->About->ShowDialog(this);
	} else if ( String::Equals(e->ClickedItem->Name, L"m_itmCreditsToolStripMenuItem", StringComparison::InvariantCultureIgnoreCase) ) {
		::MessageBox((::HWND)(::LPVOID)(this->Handle), TEXT("This program was created by The Nullz and made possible through Internet resources, code snippets\r\nand helpful tips from other coders.\r\n\r\nSpecial Thanks To:\r\n    nimo1993, Irwin, and most of all Waffle\r\n"),
			TEXT("Z - The Credits"), MB_OK | MB_APPLMODAL | MB_SETFOREGROUND);
	} else {
		String^ href;

		if ( String::Equals(e->ClickedItem->Name, L"m_itmWikiToolStripMenuItem", StringComparison::InvariantCultureIgnoreCase) ) {
			href = L"http://code.google.com/p/zpacketeditor/wiki";
		} else if ( String::Equals(e->ClickedItem->Name, L"m_itmTutorialToolStripMenuItem", StringComparison::InvariantCultureIgnoreCase) ) {
			href = L"http://code.google.com/p/zpacketeditor/wiki/Tutorial";
		} else if ( String::Equals(e->ClickedItem->Name, L"m_itmGameKillerToolStripMenuItem", StringComparison::InvariantCultureIgnoreCase) ) {
			href = L"http://www.gamekiller.net/index.php?referrerid=179202";
		}

		ThreadPool::QueueUserWorkItem(gcnew WaitCallback(&PageLink), gcnew array<Object^>{ href });
	}
}

void ZApplication::OnListItemMouseHover ( Object^ sender, ListViewItemMouseHoverEventArgs^ e )
{
	this->m_ttpToolTip->Show(e->Item->ToolTipText, e->Item->ListView);
}

void ZApplication::OnRecvListItemSelectionChanged ( Object^ sender, ListViewItemSelectionChangedEventArgs^ e )
{
	if ( e->IsSelected ) {
		this->m_txtRecvPacket->Text = e->Item->SubItems[L"Format2"]->Text;
		this->m_txtRecvPacket->Tag  = e->Item->SubItems[L"Packet2"]->Text;
		this->m_itmFormattedToolStripMenuItem->Checked = true;
		this->m_itmFormattedToolStripMenuItem->Enabled = true;

		this->m_btnFilterRecv->Enabled = ZPattern::IsValidPattern(this->m_txtRecvPacket->Text);
		this->m_btnIgnoreRecv->Enabled = this->m_btnFilterRecv->Enabled;
		this->m_btnBlockRecv->Enabled  = this->m_btnFilterRecv->Enabled;
	}
}

void ZApplication::OnRecvPacketEnter ( Object^ sender, EventArgs^ e )
{
	dwSelectedStream = Z_PACKET_STREAM_RECEIVE;
}

void ZApplication::OnGetRecvPacketClick ( Object^ sender, EventArgs^ e )
{
}

/* Ignore received packets that contain only NULL data */
extern volatile bool IgnoreNullRecvPackets;
/* Ignore received packets that contain only a command */
extern volatile bool IgnoreEmptyRecvPackets;

void ZApplication::OnFilterNullRecvCheckedChanged ( Object^ sender, EventArgs^ e )
{
	IgnoreNullRecvPackets = this->m_chxFilterNullRecv->Checked;
}

void ZApplication::OnFilterEmptyRecvCheckedChanged ( Object^ sender, EventArgs^ e )
{
	IgnoreEmptyRecvPackets = this->m_chxFilterEmptyRecv->Checked;
}

void ZApplication::OnInjectRecvClick ( Object^ sender, EventArgs^ e )
{

}

void ZApplication::OnFilterRecvClick ( Object^ sender, EventArgs^ e )
{
	ZPattern^ pattern = ZContext::G->UserCreatedPatterns->CreatePattern(this->m_txtRecvPacket->Text);

	this->m_txtRecvPacket->Clear();
	ZContext::G->Collections[1]->ClearItems();	

	if ( ZContext::G->Collections[1]->Visible != true )
		ZContext::G->Collections[1]->Show(this);

	for each ( ListViewItem^ listViewItem in this->m_lstRecvList->Items ) {
		if ( pattern->IsMatch(listViewItem->SubItems[L"Packet"]->Text) ) {
			ListViewItem^ newListViewItem = gcnew ListViewItem;
			newListViewItem->StateImageIndex         = listViewItem->StateImageIndex;
			newListViewItem->ToolTipText             = listViewItem->ToolTipText;
			newListViewItem->Tag                     = listViewItem->Tag;
			newListViewItem->UseItemStyleForSubItems = listViewItem->UseItemStyleForSubItems;

			newListViewItem->SubItems->Add(listViewItem->SubItems[L"Size"]->Text)
				->Name = L"Size";
			newListViewItem->SubItems[L"Size"]->Tag  = listViewItem->SubItems[L"Size"]->Tag;

			System::Drawing::Font^ font = (gcnew System::Drawing::Font(FontFamily::GenericMonospace,
				8.25f, FontStyle::Regular, GraphicsUnit::Point));

			newListViewItem->SubItems->Add(((::WORD)(listViewItem->SubItems[L"Code"]->Tag)).ToString(L"X4")->Insert(2, L" "))
				->Name = L"Code";	
			newListViewItem->SubItems[L"Code"]->Font = font;
			newListViewItem->SubItems[L"Code"]->Tag  = listViewItem->SubItems[L"Code"]->Tag;

			newListViewItem->SubItems->Add(listViewItem->SubItems[L"Format"]->Text)
				->Name = L"Data";
			newListViewItem->SubItems[L"Data"]->Font = font;

			newListViewItem->SubItems->Add(listViewItem->SubItems[L"Packet"]->Text)->Name = L"Packet";
			newListViewItem->SubItems->Add(listViewItem->SubItems[L"Packet2"]->Text)->Name = L"Packet2";
			newListViewItem->SubItems->Add(listViewItem->SubItems[L"Format"]->Text)->Name = L"Format";
			newListViewItem->SubItems->Add(listViewItem->SubItems[L"Format2"]->Text)->Name = L"Format2";

			ZContext::G->Collections[1]->AppendItem(newListViewItem);
		}
	}
}

void ZApplication::OnIgnoreRecvClick ( Object^ sender, EventArgs^ e )
{
	if ( ZPattern::IsValidPattern(this->m_txtRecvPacket->Text) ) {
		ZContext::G->IgnoredRecvPatterns->CreatePattern(this->m_txtRecvPacket->Text);
		this->m_txtRecvPacket->Clear();
	} else {
		::MessageBox((::HWND)(::LPVOID)(this->Handle), TEXT("You must supply a valid Z pattern definition before this template can be created."),
			TEXT("Z - The Packet Inspector"), MB_OK | MB_ICONWARNING | MB_APPLMODAL | MB_SETFOREGROUND);
	}
}

void ZApplication::OnBlockRecvClick ( Object^ sender, EventArgs^ e )
{
	if ( ZPattern::IsValidPattern(this->m_txtRecvPacket->Text) ) {
		ZContext::G->BlockedRecvPatterns->CreatePattern(this->m_txtRecvPacket->Text);
		this->m_txtRecvPacket->Clear();
	} else {
		::MessageBox((::HWND)(::LPVOID)(this->Handle), TEXT("You must supply a valid Z pattern definition before this template can be created."),
			TEXT("Z - The Packet Inspector"), MB_OK | MB_ICONWARNING | MB_APPLMODAL | MB_SETFOREGROUND);
	}
}

void ZApplication::OnSendPacketEnter ( Object^ sender, EventArgs^ e )
{
	dwSelectedStream = Z_PACKET_STREAM_SEND;
}

void ZApplication::OnGetSendPacketClick ( Object^ sender, EventArgs^ e )
{
}

/* Ignore sent packets that contain only NULL data */
extern volatile bool IgnoreNullSendPackets;
/* Ignore sent packets that contain only a command */
extern volatile bool IgnoreEmptySendPackets;

void ZApplication::OnFilterNullSendCheckedChanged ( Object^ sender, EventArgs^ e )
{
	IgnoreNullSendPackets = this->m_chxFilterNullSend->Checked;
}

void ZApplication::OnFilterEmptyCheckedChanged ( Object^ sender, EventArgs^ e )
{
	IgnoreEmptySendPackets = this->m_chxFilterEmptySend->Checked;
}

void ZApplication::OnInjectSendClick ( Object^ sender, EventArgs^ e )
{
	String^ rawBytes = ZParser::GetByteCode(this->m_txtSendPacket->Text);

	if ( String::IsNullOrEmpty(rawBytes) ) {
		::MessageBox((::HWND)(::LPVOID)(this->Handle), TEXT("You must input a valid Z packet definition in the input field"),
			TEXT("Z - The Packet Inspector"), MB_OK | MB_ICONWARNING | MB_APPLMODAL | MB_SETFOREGROUND);
	} else {
		::DWORD	 dwOffset = 0;
		::DWORD  dwLength = ( rawBytes->Length / 2 );
		::LPBYTE lpBytes  = new ::BYTE [ dwLength ];

		for ( int i = 0; ( dwOffset < dwLength ) && ( ( i + 1 ) < rawBytes->Length ); dwOffset++, i += 2 )
			lpBytes[dwOffset] = Byte::Parse(rawBytes->Substring(i, 2), NumberStyles::HexNumber, CultureInfo::InvariantCulture);

		try {
			SendPacket(lpBytes, dwLength);
		} catch ( Exception^ ) {
		} finally {
			delete [] lpBytes;
		}
	}
}

void ZApplication::OnFilterSendClick ( Object^ sender, EventArgs^ e )
{
	ZPattern^ pattern  = ZContext::G->UserCreatedPatterns->CreatePattern(this->m_txtSendPacket->Text);

	this->m_txtSendPacket->Clear();
	ZContext::G->Collections[1]->ClearItems();	

	if ( ZContext::G->Collections[1]->Visible != true )
		ZContext::G->Collections[1]->Show(this);

	for each ( ListViewItem^ listViewItem in this->m_lstSendList->Items ) {
		if ( pattern->IsMatch(listViewItem->SubItems[L"Packet"]->Text) ) {
			ListViewItem^ newListViewItem            = gcnew ListViewItem;
			newListViewItem->StateImageIndex         = listViewItem->StateImageIndex;
			newListViewItem->ToolTipText             = listViewItem->ToolTipText;
			newListViewItem->Tag                     = listViewItem->Tag;
			newListViewItem->UseItemStyleForSubItems = listViewItem->UseItemStyleForSubItems;

			newListViewItem->SubItems->Add(listViewItem->SubItems[L"Size"]->Text)
				->Name = L"Size";
			newListViewItem->SubItems[L"Size"]->Tag  = listViewItem->SubItems[L"Size"]->Tag;

			System::Drawing::Font^ font = (gcnew System::Drawing::Font(FontFamily::GenericMonospace,
				8.25f, FontStyle::Regular, GraphicsUnit::Point));

			newListViewItem->SubItems->Add(((::WORD)(listViewItem->SubItems[L"Code"]->Tag)).ToString(L"X4")->Insert(2, L" "))
				->Name = L"Code";	
			newListViewItem->SubItems[L"Code"]->Font = font;
			newListViewItem->SubItems[L"Code"]->Tag  = listViewItem->SubItems[L"Code"]->Tag;

			newListViewItem->SubItems->Add(listViewItem->SubItems[L"Format"]->Text)
				->Name = L"Data";
			newListViewItem->SubItems[L"Data"]->Font = font;

			newListViewItem->SubItems->Add(listViewItem->SubItems[L"Packet"]->Text)->Name = L"Packet";
			newListViewItem->SubItems->Add(listViewItem->SubItems[L"Packet2"]->Text)->Name = L"Packet2";
			newListViewItem->SubItems->Add(listViewItem->SubItems[L"Format"]->Text)->Name = L"Format";
			newListViewItem->SubItems->Add(listViewItem->SubItems[L"Format2"]->Text)->Name = L"Format2";

			ZContext::G->Collections[1]->AppendItem(newListViewItem);
		}
	}	
}

void ZApplication::OnIgnoreSendClick ( Object^ sender, EventArgs^ e )
{
	if ( ZPattern::IsValidPattern(this->m_txtSendPacket->Text) ) {
		ZContext::G->IgnoredSendPatterns->CreatePattern(this->m_txtSendPacket->Text);
		this->m_txtSendPacket->Clear();
	} else {
		::MessageBox((::HWND)(::LPVOID)(this->Handle), TEXT("You must supply a valid Z pattern definition before this template can be created."),
			TEXT("Z - The Packet Inspector"), MB_OK | MB_ICONWARNING | MB_APPLMODAL | MB_SETFOREGROUND);
	}
}

void ZApplication::OnBlockSendClick ( Object^ sender, EventArgs^ e )
{
	if ( ZPattern::IsValidPattern(this->m_txtSendPacket->Text) ) {
		ZContext::G->BlockedSendPatterns->CreatePattern(this->m_txtSendPacket->Text);
		this->m_txtSendPacket->Clear();
	} else {
		::MessageBox((::HWND)(::LPVOID)(this->Handle), TEXT("You must supply a valid Z pattern definition before this template can be created."),
			TEXT("Z - The Packet Inspector"), MB_OK | MB_ICONWARNING | MB_APPLMODAL | MB_SETFOREGROUND);
	}
}

void ZApplication::OnSendListItemSelectionChanged ( Object^ sender, ListViewItemSelectionChangedEventArgs^ e )
{
	if ( e->IsSelected ) {
		this->m_txtSendPacket->Text = e->Item->SubItems[L"Format2"]->Text;
		this->m_txtSendPacket->Tag  = e->Item->SubItems[L"Packet2"]->Text;
		this->m_itmFormattedToolStripMenuItem->Checked = true;
		this->m_itmFormattedToolStripMenuItem->Enabled = true;

		this->m_btnInjectSend->Enabled = ( this->m_txtSendPacket->TextLength > 0 );
		this->m_btnFilterSend->Enabled = ZPattern::IsValidPattern(this->m_txtSendPacket->Text);
		this->m_btnIgnoreSend->Enabled = this->m_btnFilterSend->Enabled;
		this->m_btnBlockSend->Enabled  = this->m_btnFilterSend->Enabled;
	}
}

void ZApplication::OnBothListItemSelectionChanged ( Object^ sender, ListViewItemSelectionChangedEventArgs^ e )
{
}

void ZApplication::OnCreateTemplateClick ( Object^ sender, EventArgs^ e )
{
	String^ rawBytes;

	if ( this->m_lstRecvList->Focused ) {
		if ( this->m_lstRecvList->FocusedItem != nullptr )
			rawBytes = this->m_lstRecvList->FocusedItem->SubItems[L"Format2"]->Text;
	} else if ( this->m_lstSendList->Focused ) {
		if ( this->m_lstSendList->FocusedItem != nullptr )
			rawBytes = this->m_lstSendList->FocusedItem->SubItems[L"Format2"]->Text;
	} else if ( this->m_lstBothList->Focused ) {
		if ( this->m_lstBothList->FocusedItem != nullptr )
			rawBytes = this->m_lstBothList->FocusedItem->SubItems[L"Format2"]->Text;
	}

	ZContext::G->Templates->CreateTemplate(rawBytes);

	if ( ZContext::G->Templates->Visible != true )
		ZContext::G->Templates->Show(this);
}

void ZApplication::OnAppendFavoritesClick ( Object^ sender, EventArgs^ e )
{
	ListViewItem^ listViewItem = nullptr;

	if ( this->m_lstRecvList->Focused ) {
		listViewItem = this->m_lstRecvList->FocusedItem;
	} else if ( this->m_lstSendList->Focused ) {
		listViewItem = this->m_lstSendList->FocusedItem;
	} else if ( this->m_lstBothList->Focused ) {
		listViewItem = this->m_lstBothList->FocusedItem;
	}

	if ( listViewItem != nullptr ) {
		ListViewItem^ newListViewItem            = gcnew ListViewItem;
		newListViewItem->StateImageIndex         = listViewItem->StateImageIndex;
		newListViewItem->ToolTipText             = listViewItem->ToolTipText;
		newListViewItem->Tag                     = listViewItem->Tag;
		newListViewItem->UseItemStyleForSubItems = listViewItem->UseItemStyleForSubItems;

		newListViewItem->SubItems->Add(listViewItem->SubItems[L"Size"]->Text)
			->Name = L"Size";
		newListViewItem->SubItems[L"Size"]->Tag  = listViewItem->SubItems[L"Size"]->Tag;

		System::Drawing::Font^ font = (gcnew System::Drawing::Font(FontFamily::GenericMonospace,
			8.25f, FontStyle::Regular, GraphicsUnit::Point));

		newListViewItem->SubItems->Add(((::WORD)(listViewItem->SubItems[L"Code"]->Tag)).ToString(L"X4")->Insert(2, L" "))
			->Name = L"Code";	
		newListViewItem->SubItems[L"Code"]->Font = font;
		newListViewItem->SubItems[L"Code"]->Tag  = listViewItem->SubItems[L"Code"]->Tag;

		newListViewItem->SubItems->Add(listViewItem->SubItems[L"Format"]->Text)
			->Name = L"Data";
		newListViewItem->SubItems[L"Data"]->Font = font;

		newListViewItem->SubItems->Add(listViewItem->SubItems[L"Packet"]->Text)->Name = L"Packet";
		newListViewItem->SubItems->Add(listViewItem->SubItems[L"Packet2"]->Text)->Name = L"Packet2";
		newListViewItem->SubItems->Add(listViewItem->SubItems[L"Format"]->Text)->Name = L"Format";
		newListViewItem->SubItems->Add(listViewItem->SubItems[L"Format2"]->Text)->Name = L"Format2";

		ZContext::G->Collections[0]->AppendItem(newListViewItem);

		if ( ZContext::G->Collections[0]->Visible != true )
			ZContext::G->Collections[0]->Show(this);
	}
}

void ZApplication::OnCollectDropDownItemClicked ( Object^ sender, ToolStripItemClickedEventArgs^ e )
{
	ListViewItem^ listViewItem = nullptr;

	if ( this->m_lstRecvList->Focused ) {
		listViewItem = this->m_lstRecvList->FocusedItem;
	} else if ( this->m_lstSendList->Focused ) {
		listViewItem = this->m_lstSendList->FocusedItem;
	} else if ( this->m_lstBothList->Focused ) {
		listViewItem = this->m_lstBothList->FocusedItem;
	}

	if ( listViewItem != nullptr ) {
		ListViewItem^ newListViewItem            = gcnew ListViewItem;
		newListViewItem->StateImageIndex         = listViewItem->StateImageIndex;
		newListViewItem->ToolTipText             = listViewItem->ToolTipText;
		newListViewItem->Tag                     = listViewItem->Tag;
		newListViewItem->UseItemStyleForSubItems = listViewItem->UseItemStyleForSubItems;

		newListViewItem->SubItems->Add(listViewItem->SubItems[L"Size"]->Text)
			->Name = L"Size";
		newListViewItem->SubItems[L"Size"]->Tag  = listViewItem->SubItems[L"Size"]->Tag;

		System::Drawing::Font^ font = (gcnew System::Drawing::Font(FontFamily::GenericMonospace,
			8.25f, FontStyle::Regular, GraphicsUnit::Point));

		newListViewItem->SubItems->Add(((::WORD)(listViewItem->SubItems[L"Code"]->Tag)).ToString(L"X4")->Insert(2, L" "))
			->Name = L"Code";	
		newListViewItem->SubItems[L"Code"]->Font = font;
		newListViewItem->SubItems[L"Code"]->Tag  = listViewItem->SubItems[L"Code"]->Tag;

		newListViewItem->SubItems->Add(listViewItem->SubItems[L"Format"]->Text)
			->Name = L"Data";
		newListViewItem->SubItems[L"Data"]->Font = font;

		newListViewItem->SubItems->Add(listViewItem->SubItems[L"Packet"]->Text)->Name = L"Packet";
		newListViewItem->SubItems->Add(listViewItem->SubItems[L"Packet2"]->Text)->Name = L"Packet2";
		newListViewItem->SubItems->Add(listViewItem->SubItems[L"Format"]->Text)->Name = L"Format";
		newListViewItem->SubItems->Add(listViewItem->SubItems[L"Format2"]->Text)->Name = L"Format2";

		ZContext::G->Collections[((int)(e->ClickedItem->Tag))]->AppendItem(newListViewItem);

		if ( ZContext::G->Collections[((int)(e->ClickedItem->Tag))]->Visible != true )
			ZContext::G->Collections[((int)(e->ClickedItem->Tag))]->Show(this);
	}
}

void ZApplication::OnRemoveItemClick ( Object^ sender, EventArgs^ e )
{
	if ( this->m_lstRecvList->Focused ) {
		if ( this->m_lstRecvList->FocusedItem != nullptr )
			this->m_lstRecvList->Items->RemoveAt(this->m_lstBothList->FocusedItem->Index);
	} else if ( this->m_lstSendList->Focused ) {
		if ( this->m_lstSendList->FocusedItem != nullptr )
			this->m_lstSendList->Items->RemoveAt(this->m_lstBothList->FocusedItem->Index);
	} else if ( this->m_lstBothList->Focused ) {
		if ( this->m_lstBothList->FocusedItem != nullptr )
			this->m_lstBothList->Items->RemoveAt(this->m_lstBothList->FocusedItem->Index);
	}
}

void ZApplication::OnClearItemsClick ( Object^ sender, EventArgs^ e )
{
	if ( this->m_lstRecvList->Focused ) {
		this->m_lstRecvList->Items->Clear();
	} else if ( this->m_lstSendList->Focused ) {
		this->m_lstSendList->Items->Clear();
	} else if ( this->m_lstBothList->Focused ) {
		this->m_lstBothList->Items->Clear();
	}
}

void ZApplication::OnItemMenuOpening ( Object^ sender, CancelEventArgs^ e )
{
	e->Cancel = (
		( this->m_lstRecvList->Focused && ( this->m_lstRecvList->FocusedItem == nullptr ) ) ||
		( this->m_lstSendList->Focused && ( this->m_lstSendList->FocusedItem == nullptr ) ) ||
		( this->m_lstBothList->Focused && ( this->m_lstBothList->FocusedItem == nullptr ) )
		);
}

void ZApplication::OnTextFormatClick ( Object^ sender, EventArgs^ e )
{
	if ( this->m_txtRecvPacket->Focused ) {
		String^ s = this->m_txtRecvPacket->Text;
		this->m_txtRecvPacket->Text = dynamic_cast<String^>(this->m_txtRecvPacket->Tag);
		this->m_txtRecvPacket->Tag  = s;
		this->m_itmFormattedToolStripMenuItem->Enabled = true;
	} else if ( this->m_txtSendPacket->Focused ) {
		String^ s = this->m_txtSendPacket->Text;
		this->m_txtSendPacket->Text = dynamic_cast<String^>(this->m_txtSendPacket->Tag);
		this->m_txtSendPacket->Tag  = s;
		this->m_itmFormattedToolStripMenuItem->Enabled = true;
	}
}

void ZApplication::OnTextCutClick ( Object^ sender, EventArgs^ e )
{
	if ( this->m_txtRecvPacket->Focused ) {
		this->m_txtRecvPacket->Cut();
	} else if ( this->m_txtSendPacket->Focused ) {
		this->m_txtSendPacket->Cut();
	}
}

void ZApplication::OnTextCopyClick ( Object^ sender, EventArgs^ e )
{
	if ( this->m_txtRecvPacket->Focused ) {
		this->m_txtRecvPacket->Copy();
	} else if ( this->m_txtSendPacket->Focused ) {
		this->m_txtSendPacket->Copy();
	}
}

void ZApplication::OnTextPasteClick ( Object^ sender, EventArgs^ e )
{
	if ( this->m_txtRecvPacket->Focused ) {
		this->m_txtRecvPacket->Paste();
	} else if ( this->m_txtSendPacket->Focused ) {
		this->m_txtSendPacket->Paste();
	}
}


void ZApplication::OnValueDropDownItemClicked ( Object^ sender, ToolStripItemClickedEventArgs^ e )
{
	int value = ZContext::G->Memory->GetValue(e->ClickedItem->Name);

	if ( value != ( -1 ) ) {
		String^ s = String::Format(L"#{0}", value);

		if ( this->m_txtRecvPacket->Focused ) {
			int index = this->m_txtRecvPacket->SelectionStart;
			this->m_txtRecvPacket->Text = this->m_txtRecvPacket->Text->Insert(this->m_txtRecvPacket->SelectionStart, s);
			this->m_txtRecvPacket->SelectionStart = index + s->Length;
		} else if ( this->m_txtSendPacket->Focused ) {
			int index = this->m_txtSendPacket->SelectionStart;
			this->m_txtSendPacket->Text = this->m_txtSendPacket->Text->Insert(this->m_txtSendPacket->SelectionStart, s);
			this->m_txtSendPacket->SelectionStart = index + s->Length;
		}
	}
}

void ZApplication::OnTextMenuOpening ( Object^ sender, CancelEventArgs^ e )
{
	TextBox^ textbox;

	if ( this->m_txtRecvPacket->Focused ) {
		textbox = this->m_txtRecvPacket;
	} else if ( this->m_txtSendPacket->Focused ) {
		textbox = this->m_txtSendPacket;
	} else {
		switch ( dwSelectedStream ) {
			case Z_PACKET_STREAM_RECEIVE:
				this->m_txtRecvPacket->Focus();
				textbox = this->m_txtRecvPacket;
				break;
			case Z_PACKET_STREAM_SEND:
				this->m_txtSendPacket->Focus();
				textbox = this->m_txtSendPacket;
				break;
		}
	}

	this->m_itmToInt16ToolStripMenuItem->Enabled  = ( String::IsNullOrEmpty(textbox->SelectedText) != true );
	this->m_itmToInt32ToolStripMenuItem->Enabled  = ( String::IsNullOrEmpty(textbox->SelectedText) != true );
	this->m_itmToAsciiToolStripMenuItem->Enabled  = ( String::IsNullOrEmpty(textbox->SelectedText) != true );
	this->m_itmToStringToolStripMenuItem->Enabled = ( String::IsNullOrEmpty(textbox->SelectedText) != true );
	this->m_itmCutToolStripMenuItem->Enabled      = ( String::IsNullOrEmpty(textbox->SelectedText) != true );
	this->m_itmCopyToolStripMenuItem->Enabled     = ( String::IsNullOrEmpty(textbox->SelectedText) != true );
	this->m_itmPasteToolStripMenuItem->Enabled    = ( ::IsClipboardFormatAvailable(CF_TEXT) || ::IsClipboardFormatAvailable(CF_UNICODETEXT) );
}

void ZApplication::OnPacketTextChanged ( Object^ sender, EventArgs^ e )
{
	if ( this->m_txtRecvPacket->Focused ) {
		this->m_btnFilterRecv->Enabled = ZPattern::IsValidPattern(this->m_txtRecvPacket->Text);
		this->m_btnIgnoreRecv->Enabled = this->m_btnFilterRecv->Enabled;
		this->m_btnBlockRecv->Enabled  = this->m_btnFilterRecv->Enabled;
		this->m_itmFormattedToolStripMenuItem->Enabled = false;
	} else if ( this->m_txtSendPacket->Focused ) {
		this->m_btnInjectSend->Enabled = ( this->m_txtSendPacket->TextLength > 0 );
		this->m_btnFilterSend->Enabled = ZPattern::IsValidPattern(this->m_txtSendPacket->Text);
		this->m_btnIgnoreSend->Enabled = this->m_btnFilterSend->Enabled;
		this->m_btnBlockSend->Enabled  = this->m_btnFilterSend->Enabled;
		this->m_itmFormattedToolStripMenuItem->Enabled = false;
	}
}

void ZApplication::OnListColumnWidthChanging ( Object^ sender, ColumnWidthChangingEventArgs^ e )
{
	e->Cancel = ( e->ColumnIndex < 3 );	
}

void ZApplication::OnSystemTrayClick ( Object^ sender, EventArgs^ e )
{
	if ( this->Visible ) {
		this->Hide();
	} else {
		this->Show();
		::SetForegroundWindow((::HWND)(::LPVOID)(this->Handle));
	}
}

void ZApplication::OnToolTipPopup ( Object^ sender, PopupEventArgs^ e )
{
	System::Drawing::Size newSize = e->ToolTipSize;
	newSize.Width  = Math::Min(newSize.Width, 300);
	e->ToolTipSize = newSize;
}

void ZApplication::OnToIn16Click ( Object^ sender, EventArgs^ e )
{
	String^ result;

	if ( this->m_txtRecvPacket->Focused ) {
		if ( String::IsNullOrEmpty(this->m_txtRecvPacket->SelectedText) != true )
			result = ZParser::GetLiteral(this->m_txtRecvPacket->SelectedText, Z_LITERAL_TYPE_INT16);
	} else if ( this->m_txtSendPacket->Focused ) {
		if ( String::IsNullOrEmpty(this->m_txtSendPacket->SelectedText) != true )
			result = ZParser::GetLiteral(this->m_txtSendPacket->SelectedText, Z_LITERAL_TYPE_INT16);
	}

	if ( result == nullptr ) {
		::MessageBox((::HWND)(::LPVOID)(this->Handle), TEXT("Only a valid series of 2 bytes can be transformed into a 16-bit integer"),
			TEXT("Z - The Packet Inspector"), MB_OK | MB_ICONWARNING | MB_APPLMODAL | MB_SETFOREGROUND);
	} else {
		int index;

		if ( this->m_txtRecvPacket->Focused ) {
			index = this->m_txtRecvPacket->SelectionStart;
			this->m_txtRecvPacket->Text = this->m_txtRecvPacket->Text->Remove(index, this->m_txtRecvPacket->SelectionLength);
			this->m_txtRecvPacket->Text = this->m_txtRecvPacket->Text->Insert(index, result);
			this->m_txtRecvPacket->SelectionStart = index + result->Length;
		} else if ( this->m_txtSendPacket->Focused ) {
			index = this->m_txtSendPacket->SelectionStart;
			this->m_txtSendPacket->Text = this->m_txtSendPacket->Text->Remove(index, this->m_txtSendPacket->SelectionLength);
			this->m_txtSendPacket->Text = this->m_txtSendPacket->Text->Insert(index, result);
			this->m_txtSendPacket->SelectionStart = index + result->Length;
		}
	}
}

void ZApplication::OnToInt32Click ( Object^ sender, EventArgs^ e )
{
	String^ result;

	if ( this->m_txtRecvPacket->Focused ) {
		if ( String::IsNullOrEmpty(this->m_txtRecvPacket->SelectedText) != true )
			result = ZParser::GetLiteral(this->m_txtRecvPacket->SelectedText, Z_LITERAL_TYPE_INT32);
	} else if ( this->m_txtSendPacket->Focused ) {
		if ( String::IsNullOrEmpty(this->m_txtSendPacket->SelectedText) != true )
			result = ZParser::GetLiteral(this->m_txtSendPacket->SelectedText, Z_LITERAL_TYPE_INT32);
	}

	if ( result == nullptr ) {
		::MessageBox((::HWND)(::LPVOID)(this->Handle), TEXT("Only a valid series of 4 bytes can be transformed into a 32-bit integer"),
			TEXT("Z - The Packet Inspector"), MB_OK | MB_ICONWARNING | MB_APPLMODAL | MB_SETFOREGROUND);
	} else {
		int index;

		if ( this->m_txtRecvPacket->Focused ) {
			index = this->m_txtRecvPacket->SelectionStart;
			this->m_txtRecvPacket->Text = this->m_txtRecvPacket->Text->Remove(index, this->m_txtRecvPacket->SelectionLength);
			this->m_txtRecvPacket->Text = this->m_txtRecvPacket->Text->Insert(index, result);
			this->m_txtRecvPacket->SelectionStart = index + result->Length;
		} else if ( this->m_txtSendPacket->Focused ) {
			index = this->m_txtSendPacket->SelectionStart;
			this->m_txtSendPacket->Text = this->m_txtSendPacket->Text->Remove(index, this->m_txtSendPacket->SelectionLength);
			this->m_txtSendPacket->Text = this->m_txtSendPacket->Text->Insert(index, result);
			this->m_txtSendPacket->SelectionStart = index + result->Length;
		}
	}
}

void ZApplication::OnToAsciiClick ( Object^ sender, EventArgs^ e )
{
	String^ result;

	if ( this->m_txtRecvPacket->Focused ) {
		if ( String::IsNullOrEmpty(this->m_txtRecvPacket->SelectedText) != true )
			result = ZParser::GetLiteral(this->m_txtRecvPacket->SelectedText, Z_LITERAL_TYPE_CHAR);
	} else if ( this->m_txtSendPacket->Focused ) {
		if ( String::IsNullOrEmpty(this->m_txtSendPacket->SelectedText) != true )
			result = ZParser::GetLiteral(this->m_txtSendPacket->SelectedText, Z_LITERAL_TYPE_CHAR);
	}

	if ( result == nullptr ) {
		::MessageBox((::HWND)(::LPVOID)(this->Handle), TEXT("Only a valid byte between 0x20 and 0x7F can be transformed into a ASCII character"),
			TEXT("Z - The Packet Inspector"), MB_OK | MB_ICONWARNING | MB_APPLMODAL | MB_SETFOREGROUND);
	} else {
		int index;

		if ( this->m_txtRecvPacket->Focused ) {
			index = this->m_txtRecvPacket->SelectionStart;
			this->m_txtRecvPacket->Text = this->m_txtRecvPacket->Text->Remove(index, this->m_txtRecvPacket->SelectionLength);
			this->m_txtRecvPacket->Text = this->m_txtRecvPacket->Text->Insert(index, result);
			this->m_txtRecvPacket->SelectionStart = index + result->Length;
		} else if ( this->m_txtSendPacket->Focused ) {
			index = this->m_txtSendPacket->SelectionStart;
			this->m_txtSendPacket->Text = this->m_txtSendPacket->Text->Remove(index, this->m_txtSendPacket->SelectionLength);
			this->m_txtSendPacket->Text = this->m_txtSendPacket->Text->Insert(index, result);
			this->m_txtSendPacket->SelectionStart = index + result->Length;
		}
	}
}

void ZApplication::OnToStringClick ( Object^ sender, EventArgs^ e )
{
	String^ result;

	if ( this->m_txtRecvPacket->Focused ) {
		if ( String::IsNullOrEmpty(this->m_txtRecvPacket->SelectedText) != true )
			result = ZParser::GetLiteral(this->m_txtRecvPacket->SelectedText, Z_LITERAL_TYPE_STRING);
	} else if ( this->m_txtSendPacket->Focused ) {
		if ( String::IsNullOrEmpty(this->m_txtSendPacket->SelectedText) != true )
			result = ZParser::GetLiteral(this->m_txtSendPacket->SelectedText, Z_LITERAL_TYPE_STRING);
	}

	if ( result == nullptr ) {
		::MessageBox((::HWND)(::LPVOID)(this->Handle), TEXT("Only a valid  series of bytes between 0x20 and 0x7F can be transformed into a string"),
			TEXT("Z - The Packet Inspector"), MB_OK | MB_ICONWARNING | MB_APPLMODAL | MB_SETFOREGROUND);
	} else {
		int index;

		if ( this->m_txtRecvPacket->Focused ) {
			index = this->m_txtRecvPacket->SelectionStart;
			this->m_txtRecvPacket->Text = this->m_txtRecvPacket->Text->Remove(index, this->m_txtRecvPacket->SelectionLength);
			this->m_txtRecvPacket->Text = this->m_txtRecvPacket->Text->Insert(index, result);
			this->m_txtRecvPacket->SelectionStart = index + result->Length;
		} else if ( this->m_txtSendPacket->Focused ) {
			index = this->m_txtSendPacket->SelectionStart;
			this->m_txtSendPacket->Text = this->m_txtSendPacket->Text->Remove(index, this->m_txtSendPacket->SelectionLength);
			this->m_txtSendPacket->Text = this->m_txtSendPacket->Text->Insert(index, result);
			this->m_txtSendPacket->SelectionStart = index + result->Length;
		}
	}
}

void ZApplication::OnAlwaysOnTopClick ( Object^ sender, EventArgs^ e )
{
	this->TopMost = this->m_itmAlwaysOnTopToolStripMenuItem->Checked;
}		 
void ZApplication::OnTransparentClick ( Object^ sender, EventArgs^ e )
{
	this->Opacity = this->m_itmTransparentToolStripMenuItem->Checked ? 0.85 : 1.0;

	for each ( Form^ form in this->OwnedForms )
		form->Opacity = this->Opacity;
}

void ZApplication::OnTopLevelWindowClick ( Object^ sender, EventArgs^ e )
{
	if ( this->m_itmSystemTrayIconToolStripMenuItem->Checked != true ) {
		this->m_itmSystemTrayIconToolStripMenuItem->Checked = ( this->m_itmTopLevelWindowToolStripMenuItem->Checked != true );
		this->m_ntiSystemTray->Visible = this->m_itmSystemTrayIconToolStripMenuItem->Checked;
	}

	this->ShowInTaskbar = this->m_itmTopLevelWindowToolStripMenuItem->Checked;
}

void ZApplication::OnSystemTrayIconClick ( Object^ sender, EventArgs^ e )
{
	if ( this->m_itmTopLevelWindowToolStripMenuItem->Checked != true ) {
		this->m_itmTopLevelWindowToolStripMenuItem->Checked = ( this->m_itmSystemTrayIconToolStripMenuItem->Checked != true );
		this->ShowInTaskbar = this->m_itmTopLevelWindowToolStripMenuItem->Checked;
	}

	this->m_ntiSystemTray->Visible = this->m_itmSystemTrayIconToolStripMenuItem->Checked;
}

void ZApplication::OnMinimizeOnCloseClick ( Object^ sender, EventArgs^ e )
{
	if ( this->m_itmMinimizeOnCloseToolStripMenuItem->Checked ) {
		this->m_itmSystemTrayIconToolStripMenuItem->Checked = true;
		this->m_ntiSystemTray->Visible = this->m_itmSystemTrayIconToolStripMenuItem->Checked;
	}
}

void ZApplication::OnHideBannerAdClick ( Object^ sender, EventArgs^ e )
{
	this->m_splConatiner->Panel2Collapsed = this->m_itmHideBannerAdToolStripMenuItem->Checked;
}

void ZApplication::OnRecvPacketMouseDoubleClick ( Object^ sender, MouseEventArgs^ e )
{
	if ( String::IsNullOrEmpty(this->m_txtRecvPacket->SelectedText) ) {
		this->m_txtRecvPacket->Clear();
	} else {
		this->m_txtRecvPacket->SelectAll();
	}
}

void ZApplication::OnSendPacketMouseDoubleClick ( Object^ sender, MouseEventArgs^ e )
{
	if ( String::IsNullOrEmpty(this->m_txtSendPacket->SelectedText) ) {
		this->m_txtSendPacket->Clear();
	} else {
		this->m_txtSendPacket->SelectAll();
	}
}

void ZApplication::OnRandomByteClick ( Object^ sender, EventArgs^ e )
{
	array<::BYTE>^ bytes = gcnew array<::BYTE>(1);

	Randomize->NextBytes(bytes);

	String^ s = String::Concat(L"#", bytes[0].ToString());

	if ( this->m_txtRecvPacket->Focused ) {
		int index = this->m_txtRecvPacket->SelectionStart;
		this->m_txtRecvPacket->Text = this->m_txtRecvPacket->Text->Insert(this->m_txtRecvPacket->SelectionStart, s);
		this->m_txtRecvPacket->SelectionStart = index + s->Length;
	} else if ( this->m_txtSendPacket->Focused ) {
		int index = this->m_txtSendPacket->SelectionStart;
		this->m_txtSendPacket->Text = this->m_txtSendPacket->Text->Insert(this->m_txtSendPacket->SelectionStart, s);
		this->m_txtSendPacket->SelectionStart = index + s->Length;
	}
}

void ZApplication::OnRandomInt16Click ( Object^ sender, EventArgs^ e )
{
	array<::BYTE>^ bytes = gcnew array<::BYTE>(2);

	Randomize->NextBytes(bytes);

	String^ s = String::Concat(L"#", BitConverter::ToInt16(bytes,0).ToString());

	if ( this->m_txtRecvPacket->Focused ) {
		int index = this->m_txtRecvPacket->SelectionStart;
		this->m_txtRecvPacket->Text = this->m_txtRecvPacket->Text->Insert(this->m_txtRecvPacket->SelectionStart, s);
		this->m_txtRecvPacket->SelectionStart = index + s->Length;
	} else if ( this->m_txtSendPacket->Focused ) {
		int index = this->m_txtSendPacket->SelectionStart;
		this->m_txtSendPacket->Text = this->m_txtSendPacket->Text->Insert(this->m_txtSendPacket->SelectionStart, s);
		this->m_txtSendPacket->SelectionStart = index + s->Length;
	}
}

void ZApplication::OnRandomInt32Click ( Object^ sender, EventArgs^ e )
{
	array<::BYTE>^ bytes = gcnew array<::BYTE>(4);

	Randomize->NextBytes(bytes);

	String^ s = String::Concat(L"#", BitConverter::ToInt32(bytes,0).ToString());

	if ( this->m_txtRecvPacket->Focused ) {
		int index = this->m_txtRecvPacket->SelectionStart;
		this->m_txtRecvPacket->Text = this->m_txtRecvPacket->Text->Insert(this->m_txtRecvPacket->SelectionStart, s);
		this->m_txtRecvPacket->SelectionStart = index + s->Length;
	} else if ( this->m_txtSendPacket->Focused ) {
		int index = this->m_txtSendPacket->SelectionStart;
		this->m_txtSendPacket->Text = this->m_txtSendPacket->Text->Insert(this->m_txtSendPacket->SelectionStart, s);
		this->m_txtSendPacket->SelectionStart = index + s->Length;
	}
}

void ZApplication::OnRandomAsciiClick ( Object^ sender, EventArgs^ e )
{
	int chr;

	do {
		chr = Randomize->Next(0x20, 0x7F);
	} while ( chr == 0x22 );

	String^ s = String::Concat(L"'", (::WCHAR)chr, L"'");

	if ( this->m_txtRecvPacket->Focused ) {
		int index = this->m_txtRecvPacket->SelectionStart;
		this->m_txtRecvPacket->Text = this->m_txtRecvPacket->Text->Insert(this->m_txtRecvPacket->SelectionStart, s);
		this->m_txtRecvPacket->SelectionStart = index + s->Length;
	} else if ( this->m_txtSendPacket->Focused ) {
		int index = this->m_txtSendPacket->SelectionStart;
		this->m_txtSendPacket->Text = this->m_txtSendPacket->Text->Insert(this->m_txtSendPacket->SelectionStart, s);
		this->m_txtSendPacket->SelectionStart = index + s->Length;
	}
}

void ZApplication::OnRandomStringClick ( Object^ sender, EventArgs^ e )
{
	int length = Randomize->Next(4, 64);
	StringBuilder^ sb = gcnew StringBuilder(length);

	for ( int i = 0, j = 0; i < length; i++ ) {
		do {
			j = Randomize->Next(0x20, 0x7F);
		} while ( j == 0x22 );

		sb->Append((::WCHAR)j);
	}

	String^ s = String::Format(L"\"{0}\"", sb->ToString());

	if ( this->m_txtRecvPacket->Focused ) {
		int index = this->m_txtRecvPacket->SelectionStart;
		this->m_txtRecvPacket->Text = this->m_txtRecvPacket->Text->Insert(this->m_txtRecvPacket->SelectionStart, s);
		this->m_txtRecvPacket->SelectionStart = index + s->Length;
	} else if ( this->m_txtSendPacket->Focused ) {
		int index = this->m_txtSendPacket->SelectionStart;
		this->m_txtSendPacket->Text = this->m_txtSendPacket->Text->Insert(this->m_txtSendPacket->SelectionStart, s);
		this->m_txtSendPacket->SelectionStart = index + s->Length;
	}
}