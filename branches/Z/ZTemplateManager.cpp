#include "Z.h"
#include "Z_CLI.h"
#include "Z_GUI.h"

using namespace Z;
using namespace System::Globalization;
using namespace System::IO;
using namespace System::Text;

void ZTemplateManager::Initialize ( void )
{
	this->m_Collection = gcnew ZTemplateCollection;
}

void ZTemplateManager::ImportFile ( String^ fileName )
{
	array<String^>^ lines;
	array<String^>^ split;
	int iColor;
	Color backColor;
	Color foreColor;
	ListViewItem^ listViewItem;

	lines = File::ReadAllLines(fileName, Encoding::UTF8);

	for ( int n = 0; n < lines->Length; n++ ) {
		split = lines[n]->Split(gcnew array<::WCHAR>{ L':' }, 5, StringSplitOptions::RemoveEmptyEntries);

		if ( split->Length != 5 )
			return;

		listViewItem          = gcnew ListViewItem(split[0]);
		listViewItem->Checked = true;

		listViewItem->SubItems->Add(split[1]->Replace(L",,", ",")->Trim(gcnew array<::WCHAR>{ L',' }))
			->Name = L"Flags";

		if ( Int32::TryParse(split[2], NumberStyles::HexNumber, CultureInfo::InvariantCulture, iColor) != true )
			return;

		foreColor = Color::FromArgb(iColor);

		listViewItem->SubItems->Add(String::Format(L"#{0:X2}{1:X2}{2:X2}", foreColor.R, foreColor.G, foreColor.B))
			->Name = L"ForeColor";
		listViewItem->SubItems[L"ForeColor"]->Tag = foreColor;

		if ( Int32::TryParse(split[3], NumberStyles::HexNumber, CultureInfo::InvariantCulture, iColor) != true )
			return;

		backColor = Color::FromArgb(iColor);

		listViewItem->SubItems->Add(String::Format(L"#{0:X2}{1:X2}{2:X2}", backColor.R, backColor.G, backColor.B))
			->Name = L"BackColor";
		listViewItem->SubItems[L"BackColor"]->Tag = backColor;

		if ( ZPattern::IsValidPattern(split[4]) != true )
			return;

		listViewItem->SubItems->Add(split[4])->Name = L"Pattern";

		ZTemplate^ t   = gcnew ZTemplate(split[0], backColor, foreColor, split[4]);
		t->RecvPackets = split[1]->Contains(RecvFlag);
		t->SendPackets = split[1]->Contains(SendFlag);
		t->NoFormat    = split[1]->Contains(NoFormatFlag);
		t->Colorize    = split[1]->Contains(ColorizeFlag);

		listViewItem->Tag = this->m_Collection->Add(t);

		this->m_lstTemplateList->Items->Add(listViewItem);

		this->m_itmExportToolStripMenuItem->Enabled   = ( this->m_lstTemplateList->Items->Count > 0 );
		this->m_itmExportAsToolStripMenuItem->Enabled = ( this->m_lstTemplateList->Items->Count > 0 );
		this->m_itmClearToolStripMenuItem->Enabled    = ( this->m_lstTemplateList->Items->Count > 0 );

		ZContext::G->Application->ApplyTemplate(t);
	}				
}

void ZTemplateManager::ExportFile ( String^ fileName )
{
	StreamWriter^ sw = gcnew StreamWriter(fileName, false, Encoding::UTF8);

	try {
		for each ( ListViewItem^ listViewItem in this->m_lstTemplateList->Items ) {
			sw->Write("{0}:{1}", listViewItem->Text, listViewItem->SubItems[L"Flags"]->Text);
			sw->Write(":{0:X8}", ( ((Color)(listViewItem->SubItems[L"ForeColor"]->Tag)).ToArgb() & 0x00FFFFFF ));
			sw->Write(":{0:X8}", ( ((Color)(listViewItem->SubItems[L"BackColor"]->Tag)).ToArgb() & 0x00FFFFFF ));
			sw->Write(":{0}", listViewItem->SubItems[L"Pattern"]->Text);
			sw->WriteLine();
		}
	} finally {
		sw->Flush();
		sw->Close();
	}
}

ZTemplate^ ZTemplateManager::GetTemplate ( String^ rawBytes, ::DWORD dwStream )
{
	if ( String::IsNullOrEmpty(rawBytes) )
		return nullptr;

	int index = ( -1 );

	if ( ( index = this->m_Collection->IsMatch(rawBytes, dwStream) ) != ( -1 ) )
		return this->m_Collection[index];

	return nullptr;
}

void ZTemplateManager::CreateTemplate ( String^ rawBytes )
{
	this->m_chxRecv->Checked = true;
	this->m_chxSend->Checked = true;

	this->m_txtAlias->Clear();
	this->m_txtPattern->Clear();

	this->m_chxNoFormat->Checked    = false;
	this->m_chxColorize->Checked    = false;
	this->m_btnForeColor->BackColor = SystemColors::WindowText;
	this->m_btnBackColor->BackColor = SystemColors::Window;		

	this->m_txtPattern->Text = rawBytes;
}

void ZTemplateManager::OnImportClick ( Object^ sender, EventArgs^ e )
{
	OpenFileDialog^ dialog               = gcnew OpenFileDialog;
	dialog->AddExtension                 = true;
	dialog->AutoUpgradeEnabled           = true;
	dialog->CheckFileExists              = true;
	dialog->CheckPathExists              = true;
	dialog->DefaultExt                   = Z_TMPL_FILE_EXT;
	dialog->DereferenceLinks             = true;
	dialog->Filter                       = Z_TMPL_FILTER;
	dialog->InitialDirectory             = Environment::GetFolderPath(Environment::SpecialFolder::MyDocuments);
	dialog->Multiselect                  = true;
	dialog->RestoreDirectory             = true;
	dialog->SupportMultiDottedExtensions = true;

	try {
		if ( dialog->ShowDialog(this) == ::DialogResult::OK ) {
			for each ( String^ fileName in dialog->FileNames )
				this->ImportFile(fileName);
		}
	} finally {
		delete (IDisposable^)dialog;
	}
}

void ZTemplateManager::OnExportClick ( Object^ sender, EventArgs^ e )
{
	SaveFileDialog^ dialog               = gcnew SaveFileDialog;
	dialog->AddExtension                 = true;
	dialog->AutoUpgradeEnabled           = true;
	dialog->DefaultExt                   = Z_TMPL_FILE_EXT;
	dialog->DereferenceLinks             = true;
	dialog->FileName                     = String::Format(L"Z-{0}", DateTime::Now.ToString(L"s", CultureInfo::InvariantCulture))->Replace(L":", L"-");
	dialog->Filter                       = Z_TMPL_FILTER;
	dialog->InitialDirectory             = Environment::GetFolderPath(Environment::SpecialFolder::MyDocuments);
	dialog->RestoreDirectory             = true;
	dialog->SupportMultiDottedExtensions = true;

	try {
		if ( dialog->ShowDialog(this) == ::DialogResult::OK )
			this->ExportFile(dialog->FileName);
	} finally {
		delete (IDisposable^)dialog;
	}
}

void ZTemplateManager::OnExportAsClick ( Object^ sender, EventArgs^ e )
{
	SaveFileDialog^ dialog               = gcnew SaveFileDialog;
	dialog->AddExtension                 = true;
	dialog->AutoUpgradeEnabled           = true;
	dialog->DefaultExt                   = Z_TMPL_FILE_EXT;
	dialog->DereferenceLinks             = true;
	dialog->Filter                       = Z_TMPL_FILTER;
	dialog->InitialDirectory             = Environment::GetFolderPath(Environment::SpecialFolder::MyDocuments);
	dialog->RestoreDirectory             = true;
	dialog->SupportMultiDottedExtensions = true;

	try {
		if ( dialog->ShowDialog(this) == ::DialogResult::OK )
			this->ExportFile(dialog->FileName);
	} finally {
		delete (IDisposable^)dialog;
	}
}

void ZTemplateManager::OnClearClick ( Object^ sender, EventArgs^ e )
{
	if ( this->m_lstTemplateList->SelectedIndices->Count > 0 ) {
		do {
			this->m_Collection->Remove((int)(this->m_lstTemplateList->Items[this->m_lstTemplateList->SelectedIndices[0]]->Tag));
			this->m_lstTemplateList->Items->RemoveAt(this->m_lstTemplateList->SelectedIndices[0]);
		} while ( this->m_lstTemplateList->SelectedIndices->Count > 0 );
	} else {
		this->m_Collection->Clear();
		this->m_lstTemplateList->Items->Clear();
	}

	this->m_itmExportToolStripMenuItem->Enabled   = ( this->m_lstTemplateList->Items->Count > 0 );
	this->m_itmExportAsToolStripMenuItem->Enabled = ( this->m_lstTemplateList->Items->Count > 0 );
	this->m_itmClearToolStripMenuItem->Enabled    = ( this->m_lstTemplateList->Items->Count > 0 );

	ZContext::G->Application->ResetTemplate();
}

void ZTemplateManager::OnAliasLeave ( Object^ sender, EventArgs^ e )
{
	if ( ZTemplate::IsValidAlias(this->m_txtAlias->Text) != true ) {
		::MessageBox((::HWND)(::LPVOID)(this->Handle), TEXT("You must supply a valid Z pattern definition before this template can be created."),
			TEXT("Z - Template Manager"), MB_OK | MB_ICONWARNING | MB_APPLMODAL | MB_SETFOREGROUND);
	}
}

void ZTemplateManager::OnPatternLeave ( Object^ sender, EventArgs^ e )
{
	if ( ZPattern::IsValidPattern(this->m_txtPattern->Text) != true ) {
		::MessageBox((::HWND)(::LPVOID)(this->Handle), TEXT("You must supply a valid Z pattern definition before this template can be created."),
			TEXT("Z - Template Manager"), MB_OK | MB_ICONWARNING | MB_APPLMODAL | MB_SETFOREGROUND);
	}
}

void ZTemplateManager::OnForeColorClick ( Object^ sender, EventArgs^ e )
{
	ColorDialog^ dialog   = gcnew ColorDialog;
	dialog->AllowFullOpen = true;
	dialog->AnyColor      = true;
	dialog->Color         = this->m_btnForeColor->BackColor;
	dialog->FullOpen      = true;

	try {
		if ( dialog->ShowDialog(this) == ::DialogResult::OK )
			this->m_btnForeColor->BackColor = dialog->Color;
	} finally {
		delete (IDisposable^)dialog;
	}
}

void ZTemplateManager::OnBackColorClick ( Object^ sender, EventArgs^ e )
{
	ColorDialog^ dialog   = gcnew ColorDialog;
	dialog->AllowFullOpen = true;
	dialog->AnyColor      = true;
	dialog->Color         = this->m_btnBackColor->BackColor;
	dialog->FullOpen      = true;

	try {
		if ( dialog->ShowDialog(this) == ::DialogResult::OK )
			this->m_btnBackColor->BackColor = dialog->Color;
	} finally {
		delete (IDisposable^)dialog;
	}
}

void ZTemplateManager::OnCreateClick ( Object^ sender, EventArgs^ e )
{
	if ( ZTemplate::IsValidAlias(this->m_txtAlias->Text) != true ) {
		::MessageBox((::HWND)(::LPVOID)(this->Handle), TEXT("You must supply a valid Z pattern definition before this template can be created."),
			TEXT("Z - Template Manager"), MB_OK | MB_ICONWARNING | MB_APPLMODAL | MB_SETFOREGROUND);
		return;
	}

	if ( ZPattern::IsValidPattern(this->m_txtPattern->Text) != true ) {
		::MessageBox((::HWND)(::LPVOID)(this->Handle), TEXT("You must supply a valid Z pattern definition before this template can be created."),
			TEXT("Z - Template Manager"), MB_OK | MB_ICONWARNING | MB_APPLMODAL | MB_SETFOREGROUND);
		return;
	}

	this->m_ctrContainer->Enabled = false;

	ListViewItem^ listViewItem = gcnew ListViewItem(this->m_txtAlias->Text);
	listViewItem->Checked      = true;

	array<String^>^ flags = gcnew array<String^>(4);
	flags[0] = this->m_chxRecv->Checked ? RecvFlag : nullptr;
	flags[1] = this->m_chxSend->Checked ? SendFlag : nullptr;
	flags[2] = this->m_chxNoFormat->Checked ? NoFormatFlag : nullptr;
	flags[3] = this->m_chxColorize->Checked ? ColorizeFlag : nullptr;	

	listViewItem->SubItems->Add(String::Join(L",", flags)->Replace(L",,", ",")->Trim(gcnew array<::WCHAR>{ L',' }))
		->Name = L"Flags";
	listViewItem->SubItems->Add(String::Format(L"#{0:X2}{1:X2}{2:X2}",
		this->m_btnForeColor->BackColor.R, this->m_btnForeColor->BackColor.G, this->m_btnForeColor->BackColor.B))
		->Name = L"ForeColor";
	listViewItem->SubItems[L"ForeColor"]->Tag = this->m_btnForeColor->BackColor;
	listViewItem->SubItems->Add(String::Format(L"#{0:X2}{1:X2}{2:X2}",
		this->m_btnBackColor->BackColor.R, this->m_btnBackColor->BackColor.G, this->m_btnBackColor->BackColor.B))
		->Name = L"BackColor";
	listViewItem->SubItems[L"BackColor"]->Tag = this->m_btnBackColor->BackColor;
	listViewItem->SubItems->Add(this->m_txtPattern->Text)
		->Name = L"Pattern";

	ZTemplate^ _template = gcnew ZTemplate(this->m_txtAlias->Text, this->m_btnBackColor->BackColor, this->m_btnForeColor->BackColor, this->m_txtPattern->Text);
	_template->RecvPackets = this->m_chxRecv->Checked;
	_template->SendPackets = this->m_chxSend->Checked;
	_template->NoFormat    = this->m_chxNoFormat->Checked;
	_template->Colorize    = this->m_chxColorize->Checked;

	listViewItem->Tag = this->m_Collection->Add(_template);

	this->m_lstTemplateList->Items->Add(listViewItem);
	ZContext::G->Application->ApplyTemplate(_template);

	this->m_chxRecv->Checked = true;
	this->m_chxSend->Checked = true;

	this->m_txtAlias->Clear();
	this->m_txtPattern->Clear();

	this->m_chxNoFormat->Checked = false;
	this->m_chxColorize->Checked = false;
	this->m_btnForeColor->BackColor = SystemColors::WindowText;
	this->m_btnBackColor->BackColor = SystemColors::Window;		
	this->m_ctrContainer->Enabled = true;

	this->m_itmExportToolStripMenuItem->Enabled   = ( this->m_lstTemplateList->Items->Count > 0 );
	this->m_itmExportAsToolStripMenuItem->Enabled = ( this->m_lstTemplateList->Items->Count > 0 );
	this->m_itmClearToolStripMenuItem->Enabled    = ( this->m_lstTemplateList->Items->Count > 0 );
}


void ZTemplateManager::OnTemplateListItemMouseHover ( Object^ sender, ListViewItemMouseHoverEventArgs^ e )
{
	this->m_ttpToolTip->Show(e->Item->SubItems[L"Pattern"]->Text, e->Item->ListView);
}

void ZTemplateManager::OnTemplateListItemChecked ( Object^ sender, ItemCheckedEventArgs^ e )
{
	this->m_Collection[((int)(e->Item->Tag))]->Enabled = e->Item->Checked;
}

void ZTemplateManager::OnRecvClick ( Object^ sender, EventArgs^ e )
{
	ListViewItem^ item   = this->m_lstTemplateList->FocusedItem;

	ZTemplate^ _template   = this->m_Collection[((int)(item->Tag))];
	_template->RecvPackets = this->m_itmRecvToolStripMenuItem->Checked;

	array<String^>^ flags = gcnew array<String^>(4);
	flags[0] = _template->RecvPackets ? RecvFlag : nullptr;
	flags[1] = _template->SendPackets ? SendFlag : nullptr;
	flags[2] = _template->NoFormat    ? NoFormatFlag : nullptr;
	flags[3] = _template->Colorize    ? ColorizeFlag : nullptr;	

	item->SubItems[L"Flags"]->Text = String::Join(L",", flags)->Replace(L",,", ",")->Trim(gcnew array<::WCHAR>{ L',' });

	ZContext::G->Application->ApplyTemplate(_template);
}

void ZTemplateManager::OnSendClick ( Object^ sender, EventArgs^ e )
{
	ListViewItem^ item   = this->m_lstTemplateList->FocusedItem;

	ZTemplate^ _template   = this->m_Collection[((int)(item->Tag))];
	_template->SendPackets = this->m_itmSendToolStripMenuItem->Checked;

	array<String^>^ flags = gcnew array<String^>(4);
	flags[0] = _template->RecvPackets ? RecvFlag : nullptr;
	flags[1] = _template->SendPackets ? SendFlag : nullptr;
	flags[2] = _template->NoFormat    ? NoFormatFlag : nullptr;
	flags[3] = _template->Colorize    ? ColorizeFlag : nullptr;	

	item->SubItems[L"Flags"]->Text = String::Join(L",", flags)->Replace(L",,", ",")->Trim(gcnew array<::WCHAR>{ L',' });

	ZContext::G->Application->ApplyTemplate(_template);
}

void ZTemplateManager::OnNoFormatClick ( Object^ sender, EventArgs^ e )
{
	ListViewItem^ item   = this->m_lstTemplateList->FocusedItem;

	ZTemplate^ _template = this->m_Collection[((int)(item->Tag))];
	_template->NoFormat  = this->m_itmNoFormatToolStripMenuItem->Checked;

	array<String^>^ flags = gcnew array<String^>(4);
	flags[0] = _template->RecvPackets ? RecvFlag : nullptr;
	flags[1] = _template->SendPackets ? SendFlag : nullptr;
	flags[2] = _template->NoFormat    ? NoFormatFlag : nullptr;
	flags[3] = _template->Colorize    ? ColorizeFlag : nullptr;	

	item->SubItems[L"Flags"]->Text = String::Join(L",", flags)->Replace(L",,", ",")->Trim(gcnew array<::WCHAR>{ L',' });

	ZContext::G->Application->ApplyTemplate(_template);
}

void ZTemplateManager::OnColorizeClick ( Object^ sender, EventArgs^ e )
{
	ListViewItem^ item   = this->m_lstTemplateList->FocusedItem;

	ZTemplate^ _template = this->m_Collection[((int)(item->Tag))];
	_template->Colorize  = this->m_itmColorizeToolStripMenuItem->Checked;

	array<String^>^ flags = gcnew array<String^>(4);
	flags[0] = _template->RecvPackets ? RecvFlag : nullptr;
	flags[1] = _template->SendPackets ? SendFlag : nullptr;
	flags[2] = _template->NoFormat    ? NoFormatFlag : nullptr;
	flags[3] = _template->Colorize    ? ColorizeFlag : nullptr;	

	item->SubItems[L"Flags"]->Text = String::Join(L",", flags)->Replace(L",,", ",")->Trim(gcnew array<::WCHAR>{ L',' });

	ZContext::G->Application->ApplyTemplate(_template);
}

void ZTemplateManager::OnSetForeColorClick ( Object^ sender, EventArgs^ e )
{
	ListViewItem^ item    = this->m_lstTemplateList->FocusedItem;
	ColorDialog^  dialog  = gcnew ColorDialog;
	dialog->AllowFullOpen = true;
	dialog->AnyColor      = true;
	dialog->Color         = ((Color)(item->SubItems[L"ForeColor"]->Tag));
	dialog->FullOpen      = true;

	try {
		if ( dialog->ShowDialog(this) == ::DialogResult::OK ) {
			item->SubItems[L"ForeColor"]->Text = String::Format(L"#{0:X2}{1:X2}{2:X2}",
				dialog->Color.R, dialog->Color.G, dialog->Color.B);
			item->SubItems[L"ForeColor"]->Tag  = dialog->Color;
			this->m_Collection[((int)(item->Tag))]->ForeColor = dialog->Color;
		}
	} finally {
		delete (IDisposable^)dialog;
	}

	ZContext::G->Application->ApplyTemplate(this->m_Collection[((int)(item->Tag))]);
}

void ZTemplateManager::OnSetBackColorClick ( Object^ sender, EventArgs^ e )
{
	ListViewItem^ item    = this->m_lstTemplateList->FocusedItem;
	ColorDialog^  dialog  = gcnew ColorDialog;
	dialog->AllowFullOpen = true;
	dialog->AnyColor      = true;
	dialog->Color         = ((Color)(item->SubItems[L"BackColor"]->Tag));
	dialog->FullOpen      = true;

	try {
		if ( dialog->ShowDialog(this) == ::DialogResult::OK ) {
			item->SubItems[L"BackColor"]->Text = String::Format(L"#{0:X2}{1:X2}{2:X2}",
				dialog->Color.R, dialog->Color.G, dialog->Color.B);
			item->SubItems[L"BackColor"]->Tag  = dialog->Color;
			this->m_Collection[((int)(item->Tag))]->BackColor = dialog->Color;
		}
	} finally {
		delete (IDisposable^)dialog;
	}

	ZContext::G->Application->ApplyTemplate(this->m_Collection[((int)(item->Tag))]);
}

void ZTemplateManager::OnItemMenuOpening ( Object^ sender, CancelEventArgs^ e )
{
	e->Cancel = ( ( this->m_lstTemplateList->Focused != true ) || ( this->m_lstTemplateList->FocusedItem == nullptr ) );

	if ( e->Cancel != true ) {
		ListViewItem^ item = this->m_lstTemplateList->FocusedItem;
		this->m_itmRecvToolStripMenuItem->Checked = item->SubItems[L"Flags"]->Text->Contains(RecvFlag);
		this->m_itmSendToolStripMenuItem->Checked = item->SubItems[L"Flags"]->Text->Contains(SendFlag);
		this->m_itmNoFormatToolStripMenuItem->Checked = item->SubItems[L"Flags"]->Text->Contains(NoFormatFlag);
		this->m_itmColorizeToolStripMenuItem->Checked = item->SubItems[L"Flags"]->Text->Contains(ColorizeFlag);
	}
}