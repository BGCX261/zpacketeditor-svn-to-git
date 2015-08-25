#include "Z.h"
#include "Z_CLI.h"
#include "Z_GUI.h"

using namespace Z;
using namespace System::Globalization;
using namespace System::IO;
using namespace System::Text;

/* Find memeory based on a byte pattern */
::ULONG_PTR FindPatternCLI ( String^ rawBytes, String^ mask, int offset )
{
	::DWORD	 dwOffset  = 0;
	::DWORD  dwLength  = ( rawBytes->Length / 2 );
	::LPBYTE lpPattern = new ::BYTE [ dwLength ];

	for ( int i = 0; ( dwOffset < dwLength ) && ( ( i + 1 ) < rawBytes->Length ); dwOffset++, i += 2 )
		lpPattern[dwOffset] = Byte::Parse(rawBytes->Substring(i, 2), NumberStyles::HexNumber, CultureInfo::InvariantCulture);

	::LPSTR lpszPattern = new ::CHAR [ mask->Length + 1 ];

	for ( int i = 0; i < mask->Length; i++ )
		lpszPattern[i] = (::CHAR)__toascii(mask[i]);

	lpszPattern[mask->Length] = '\0';

	::ULONG_PTR retval = FindPattern(lpPattern, lpszPattern, (::LONG_PTR)offset);
	delete [] lpPattern;
	delete [] lpszPattern;
	return retval;
}

/* Get the value of a integer field */
::ULONG_PTR ZMemoryManager::GetFieldValue ( String^ fieldNameOrValue )
{
	if ( String::IsNullOrEmpty(fieldNameOrValue) )
		return (::ULONG_PTR)( -1 );

	if ( fieldNameOrValue->StartsWith(L"@", StringComparison::InvariantCultureIgnoreCase) ) {
		fieldNameOrValue = fieldNameOrValue->Substring(1);

		if ( this->m_lstPointerList->Items->ContainsKey(fieldNameOrValue) )
			return this->GetFieldValue(this->m_lstPointerList->Items[fieldNameOrValue]->SubItems[L"Value"]->Text);
	} else {
		int i32;

		if ( Int32::TryParse(fieldNameOrValue, NumberStyles::Integer, CultureInfo::InvariantCulture, i32) )
			return i32;
	}

	return (::ULONG_PTR)( -1 );
}

/* Get the current value of a pointer in the tracker table */
int ZMemoryManager::GetValue ( String^ ptrName )
{
	::ULONG_PTR ulValue = GetPtrValue(
		(::PULONG_PTR)(this->GetFieldValue(this->m_lstPointerList->Items[ptrName]->SubItems[L"Base"]->Text)),
		static_cast<::LONG_PTR>(this->GetFieldValue(this->m_lstPointerList->Items[ptrName]->SubItems[L"Offset"]->Text)));

	if ( ulValue == (::ULONG_PTR)(-1) )
		return (-1);

	return static_cast<int>(ulValue);
}

void ZMemoryManager::OnImportClick ( Object^ sender, EventArgs^ e )
{
	OpenFileDialog^ dialog               = gcnew OpenFileDialog;
	dialog->AddExtension                 = true;
	dialog->AutoUpgradeEnabled           = true;
	dialog->CheckFileExists              = true;
	dialog->CheckPathExists              = true;
	dialog->DefaultExt                   = L"zmm";
	dialog->DereferenceLinks             = true;
	dialog->Filter                       = L"Z Memory Manager (*.zmm)|*.zmm|All files (*.*)|*.*";
	dialog->InitialDirectory             = Environment::GetFolderPath(Environment::SpecialFolder::MyDocuments);
	dialog->Multiselect                  = true;
	dialog->RestoreDirectory             = true;
	dialog->SupportMultiDottedExtensions = true;

	try {
		if ( dialog->ShowDialog(this) == ::DialogResult::OK ) {
			for each ( String^ fileName in dialog->FileNames ) {
				for each ( String^ line in File::ReadAllLines(fileName, Encoding::UTF8) ) {
					array<String^>^ split = line->Split(gcnew array<::WCHAR>{ L':' }, 4, StringSplitOptions::None);

					if ( split->Length == 4 ) {
						if ( ( split[0]->Length > 0 ) && ( ArrayOfBytesExpr->IsMatch(split[0]) != true ) )
							continue;

						if ( ( split[2]->Length > 0 ) && ( IntegerValueExpr->IsMatch(split[2]) != true ) )
							continue;

						if ( ( split[3]->Length > 0 ) && ( IntegerValueExpr->IsMatch(split[3]) != true ) )
							continue;

						ListViewItem^ listViewItem = gcnew ListViewItem(split[0]);
						listViewItem->Name = split[1];
						listViewItem->Tag  = String::IsNullOrEmpty(split[0]);

						listViewItem->SubItems->Add(split[1])->Name = L"Name";
						listViewItem->SubItems->Add(split[2])->Name = L"Base";
						listViewItem->SubItems->Add(split[3])->Name = L"Offset";
						listViewItem->SubItems->Add(String::Empty)->Name = L"Value";

						this->m_lstPointerList->Items->Add(listViewItem);

						if ( String::IsNullOrEmpty(listViewItem->Text) ) {
							ZContext::G->Application->AppendInsertMenuItem(listViewItem->SubItems[L"Name"]->Text);
							ZContext::G->PacketBuilder->AppendInsertMenuItem(listViewItem->SubItems[L"Name"]->Text);
						}
					}
				}
			}
		}
	} finally {
		delete (IDisposable^)dialog;
	}

	this->m_itmExportToolStripMenuItem->Enabled   = ( this->m_lstPointerList->Items->Count > 0 );
	this->m_itmExportAsToolStripMenuItem->Enabled = ( this->m_lstPointerList->Items->Count > 0 );
	this->m_itmClearToolStripMenuItem->Enabled    = ( this->m_lstPointerList->Items->Count > 0 );
	this->m_tmrTimer->Enabled = ( this->m_lstPointerList->Items->Count > 0 );
}

void ZMemoryManager::OnExportClick ( Object^ sender, EventArgs^ e )
{
	SaveFileDialog^ dialog               = gcnew SaveFileDialog;
	dialog->AddExtension                 = true;
	dialog->AutoUpgradeEnabled           = true;
	dialog->DefaultExt                   = L"zmm";
	dialog->DereferenceLinks             = true;
	dialog->FileName                     = String::Format(L"Z-{0}.zmm", DateTime::Now.ToString(L"s", CultureInfo::InvariantCulture))->Replace(L":", L"-");
	dialog->Filter                       = L"Z Memory Manager (*.zmm)|*.zmm|All files (*.*)|*.*";
	dialog->InitialDirectory             = Environment::GetFolderPath(Environment::SpecialFolder::MyDocuments);
	dialog->OverwritePrompt              = true;
	dialog->RestoreDirectory             = true;
	dialog->SupportMultiDottedExtensions = true;

	try {
		if ( dialog->ShowDialog(this) == ::DialogResult::OK ) {
			StreamWriter^ sw = gcnew StreamWriter(dialog->FileName, false, Encoding::UTF8);

			try {
				/* [Pattern]:[Name]:[Base]:[Offset] */
				for each ( ListViewItem^ listViewItem in this->m_lstPointerList->Items ) {
					if ( String::IsNullOrEmpty(listViewItem->Text) ) {
						sw->Write(L"*");
					} else {
						sw->Write(listViewItem->Text);
					}

					sw->Write(L":{0}", listViewItem->SubItems[L"Name"]->Text);
					sw->Write(L":{0}", listViewItem->SubItems[L"Base"]->Text);
					sw->Write(L":{0}", listViewItem->SubItems[L"Offset"]->Text);
					sw->WriteLine();
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

void ZMemoryManager::OnExportAsClick ( Object^ sender, EventArgs^ e )
{
	SaveFileDialog^ dialog               = gcnew SaveFileDialog;
	dialog->AddExtension                 = true;
	dialog->AutoUpgradeEnabled           = true;
	dialog->DefaultExt                   = L"zmm";
	dialog->DereferenceLinks             = true;
	dialog->FileName                     = String::Format(L"Z-{0}.zmm", DateTime::Now.ToString(L"s"));
	dialog->Filter                       = L"Z Memory Manager (*.zmm)|*.zmm|All files (*.*)|*.*";
	dialog->InitialDirectory             = Environment::GetFolderPath(Environment::SpecialFolder::MyDocuments);
	dialog->OverwritePrompt              = true;
	dialog->RestoreDirectory             = true;
	dialog->SupportMultiDottedExtensions = true;

	try {
		if ( dialog->ShowDialog(this) == ::DialogResult::OK ) {
			StreamWriter^ sw = gcnew StreamWriter(dialog->FileName, false, Encoding::UTF8);

			try {
				/* [Pattern]:[Name]:[Base]:[Offset] */
				for each ( ListViewItem^ listViewItem in this->m_lstPointerList->Items ) {
					if ( String::IsNullOrEmpty(listViewItem->Text) != true )
						sw->Write(listViewItem->Text);

					sw->Write(L":{0}", listViewItem->SubItems[L"Name"]->Text);
					sw->Write(L":{0}", listViewItem->SubItems[L"Base"]->Text);
					sw->Write(L":{0}", listViewItem->SubItems[L"Offset"]->Text);
					sw->WriteLine();
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

void ZMemoryManager::OnClearClick ( Object^ sender, EventArgs^ e )
{
	if ( this->m_lstPointerList->SelectedIndices->Count > 0 ) {
		ListViewItem^ listViewItem;

		do {
			listViewItem = this->m_lstPointerList->Items[this->m_lstPointerList->SelectedIndices[0]];

			/* Remove this pointer from the Insert menu */
			ZContext::G->Application->RemoveInsertMenuItem(listViewItem->Name);
			/* Remove this pointer from the Insert menu */
			ZContext::G->PacketBuilder->RemoveInsertMenuItem(listViewItem->Name);

			this->m_lstPointerList->Items->RemoveAt(this->m_lstPointerList->SelectedIndices[0]);
		} while ( this->m_lstPointerList->SelectedIndices->Count > 0 ); 
	} else {
		/* Clear all items from the Insert menu */
		ZContext::G->Application->ClearInsertMenu();
		/* Clear all items from the Insert menu */
		ZContext::G->PacketBuilder->ClearInsertMenu();

		this->m_lstPointerList->Items->Clear();
	}

	this->m_itmExportToolStripMenuItem->Enabled   = ( this->m_lstPointerList->Items->Count > 0 );
	this->m_itmExportAsToolStripMenuItem->Enabled = ( this->m_lstPointerList->Items->Count > 0 );
	this->m_itmClearToolStripMenuItem->Enabled    = ( this->m_lstPointerList->Items->Count > 0 );
	this->m_tmrTimer->Enabled = ( this->m_lstPointerList->Items->Count > 0 );
}

void ZMemoryManager::OnTypeListSelectedIndexChanged ( Object^ sender, EventArgs^ e )
{
	switch ( this->m_lstTypeList->SelectedIndex ) {
		case 0: /* Static Address */
			this->m_txtPattern->Text    = String::Empty;
			this->m_txtPattern->Enabled = false;
			this->m_txtBase->Text       = String::Empty;
			this->m_txtBase->Enabled    = true;
			this->m_txtOffset->Text     = String::Empty;
			this->m_txtOffset->Enabled  = true;
			break;
		case 1: /* Array of Bytes */
			this->m_txtPattern->Text    = String::Empty;
			this->m_txtPattern->Enabled = true;
			this->m_txtBase->Text       = String::Empty;
			this->m_txtBase->Enabled    = false;
			this->m_txtOffset->Text     = String::Empty;
			this->m_txtOffset->Enabled  = false;
			this->m_btnTrack->Enabled   = false;
			break;
	}

	this->m_txtValue->Text = L"?";
}

void ZMemoryManager::OnNameLeave ( Object^ sender, EventArgs^ e )
{
	TextBox^ textbox = nullptr;

	if ( ( textbox = dynamic_cast<TextBox^>(sender) ) == nullptr )
		return;

	if ( textbox->TextLength > 0 ) {
		if ( InvalidCharsExpr->IsMatch(textbox->Text) ) {
			::MessageBox((::HWND)(::LPVOID)(this->Handle), TEXT("Invalid characters detected in the Name field"),
				TEXT("Z - Memory Manager"), MB_OK | MB_ICONWARNING | MB_APPLMODAL | MB_SETFOREGROUND);
		}
	}
}

void ZMemoryManager::OnHexNumberCheckedChanged ( Object^ sender, EventArgs^ e )
{

}

void ZMemoryManager::OnValueLeave ( Object^ sender, EventArgs^ e )
{
	TextBox^ textbox = nullptr;

	if ( ( textbox = dynamic_cast<TextBox^>(sender) ) == nullptr )
		return;

	if ( textbox->TextLength > 0 ) {
		if ( IntegerValueExpr->IsMatch(textbox->Text) != true ) {
			::MessageBox((::HWND)(::LPVOID)(this->Handle), TEXT("An integer field must contain either a reference or a 32-bit integer value."),
				TEXT("Z - Memory Manager"), MB_OK | MB_ICONWARNING | MB_APPLMODAL | MB_SETFOREGROUND);
		}
	}
}

void ZMemoryManager::OnArrayLeave ( Object^ sender, EventArgs^ e )
{
	TextBox^ textbox = nullptr;

	if ( ( textbox = dynamic_cast<TextBox^>(sender) ) == nullptr )
		return;

	if ( textbox->TextLength > 0 ) {
		if ( ArrayOfBytesExpr->IsMatch(textbox->Text->Replace(L" ", String::Empty)) != true ) {
			::MessageBox((::HWND)(::LPVOID)(this->Handle), TEXT("An array of bytes can contain only hexadecimal characters and question marks."),
				TEXT("Z - Memory Manager"), MB_OK | MB_ICONWARNING | MB_APPLMODAL | MB_SETFOREGROUND);
		}
	}
}

void ZMemoryManager::OnFindClick ( Object^ sender, EventArgs^ e )
{
	this->m_ctrContainer->Enabled = false;

	::ULONG_PTR ulValue = (::ULONG_PTR)( -1 );

	switch ( this->m_lstTypeList->SelectedIndex ) {
		case 0: /* Static Address */
			if ( ( IntegerValueExpr->IsMatch(this->m_txtBase->Text) != true ) || ( IntegerValueExpr->IsMatch(this->m_txtOffset->Text) != true ) ) {
				::MessageBox((::HWND)(::LPVOID)(this->Handle), TEXT("You must supply valid values for all fields in order to locate memory data"),
					TEXT("Z - Memory Manager"), MB_OK | MB_ICONWARNING | MB_APPLMODAL | MB_SETFOREGROUND);
			}

			ulValue = GetPtrValue((::PULONG_PTR)(this->GetFieldValue(this->m_txtBase->Text)), static_cast<::LONG_PTR>(this->GetFieldValue(this->m_txtOffset->Text)));

			if ( ulValue == (::ULONG_PTR)( -1 ) ) {
				this->m_txtValue->Text = L"?";
			} else {
				int i32_s = static_cast<int>((::DWORD)ulValue);
				this->m_txtValue->Tag  = i32_s;
				this->m_txtValue->Text = this->m_chxHexNumber->Checked ? i32_s.ToString(L"X8") : i32_s.ToString(L"N0");
			}

			break;
		case 1: /* Array Of Bytes */
			Match^ match = Match::Empty;

			if ( ( match = ArrayOfBytesExpr->Match(this->m_txtPattern->Text->Replace(L" ", String::Empty)) ) == Match::Empty ) {
				::MessageBox((::HWND)(::LPVOID)(this->Handle), TEXT("You must supply valid values for all fields in order to locate memory data"),
					TEXT("Application Error"), MB_OK | MB_ICONWARNING | MB_APPLMODAL | MB_SETFOREGROUND);
			} else {
				int offset = 0;

				if ( match->Groups[L"off"]->Success ) {
					if ( Int32::TryParse(match->Groups[L"off"]->Value, NumberStyles::Integer, CultureInfo::InvariantCulture, offset) != true ) {
						::MessageBox((::HWND)(::LPVOID)(this->Handle), TEXT("You must supply valid values for all fields in order to locate memory data"),
							TEXT("Application Error"), MB_OK | MB_ICONWARNING | MB_APPLMODAL | MB_SETFOREGROUND);
						break;
					}
				}

				String^ rawBytes = WildValuesExpr->Replace(match->Groups[L"ptr"]->Value, L"00");
				String^ charMask = ByteValuesExpr->Replace(match->Groups[L"ptr"]->Value, L"x");
				ulValue = FindPatternCLI(rawBytes, charMask, offset);

				if ( ulValue == (::ULONG_PTR)( -1 ) ) {
					this->m_txtValue->Text = L"?";
				} else {
					int i32_v = static_cast<int>(*(::PDWORD)ulValue);
					this->m_txtValue->Tag  = i32_v;
					this->m_txtValue->Text = this->m_chxHexNumber->Checked ? i32_v.ToString(L"X8") : i32_v.ToString(L"N0");
				}
			}

			break;
	}

	this->m_btnTrack->Enabled     = ( this->m_txtValue->Tag != nullptr );
	this->m_ctrContainer->Enabled = true;
}

void ZMemoryManager::OnTrackClick ( Object^ sender, EventArgs^ e )
{
	if ( InvalidCharsExpr->IsMatch(this->m_txtName->Text) ) {
		::MessageBox((::HWND)(::LPVOID)(this->Handle), TEXT("You must supply valid values for all fields in order to create a tracker"),
			TEXT("Application Error"), MB_OK | MB_ICONWARNING | MB_APPLMODAL | MB_SETFOREGROUND);
	}

	switch ( this->m_lstTypeList->SelectedIndex ) {
		case 0: /* Static Address */
			this->m_txtPattern->Text = String::Empty;

			if ( ( IntegerValueExpr->IsMatch(this->m_txtBase->Text) != true ) || ( IntegerValueExpr->IsMatch(this->m_txtOffset->Text) != true ) ) {
				::MessageBox((::HWND)(::LPVOID)(this->Handle), TEXT("You must supply valid values for all fields in order to create a tracker"),
					TEXT("Application Error"), MB_OK | MB_ICONWARNING | MB_APPLMODAL | MB_SETFOREGROUND);
			}

			break;
		case 1: /* Array Of Bytes */
			this->m_txtBase->Text   = String::Empty;
			this->m_txtOffset->Text = String::Empty;

			if ( ArrayOfBytesExpr->IsMatch(this->m_txtPattern->Text) != true ) {
				::MessageBox((::HWND)(::LPVOID)(this->Handle), TEXT("You must supply valid values for all fields in order to create a tracker"),
					TEXT("Application Error"), MB_OK | MB_ICONWARNING | MB_APPLMODAL | MB_SETFOREGROUND);
			}

			break;
	}

	ListViewItem^ listViewItem = gcnew ListViewItem(this->m_txtPattern->Text);
	listViewItem->Name = this->m_txtName->Text;
	listViewItem->Tag  = ( this->m_lstTypeList->SelectedIndex == 0 );

	listViewItem->SubItems->Add(String::Format(L"@{0}", this->m_txtName->Text))
		->Name = L"Name";
	listViewItem->SubItems->Add(this->m_txtBase->Text)
		->Name = L"Base";
	listViewItem->SubItems->Add(this->m_txtOffset->Text)
		->Name = L"Offset";
	listViewItem->SubItems->Add(String::Empty)
		->Name = L"Value";

	this->m_lstPointerList->Items->Add(listViewItem);

	if ( ((bool)(listViewItem->Tag)) ) {
		ZContext::G->Application->AppendInsertMenuItem(listViewItem->Name);
		ZContext::G->PacketBuilder->AppendInsertMenuItem(listViewItem->Name);
	}

	this->m_txtName->Text              = String::Empty;
	this->m_lstTypeList->SelectedIndex = 0;
	/* Enable/disable menu items */
	this->m_itmExportToolStripMenuItem->Enabled   = ( this->m_lstPointerList->Items->Count > 0 );
	this->m_itmExportAsToolStripMenuItem->Enabled = ( this->m_lstPointerList->Items->Count > 0 );
	this->m_itmClearToolStripMenuItem->Enabled    = ( this->m_lstPointerList->Items->Count > 0 );
	/* Monitor variables */
	this->m_tmrTimer->Enabled = ( this->m_lstPointerList->Items->Count > 0 );
}

void ZMemoryManager::OnPointerListItemMouseHover ( Object^ sender, ListViewItemMouseHoverEventArgs^ e )
{
	this->m_ttpToolTip->Show(e->Item->ToolTipText, e->Item->ListView);
}

void ZMemoryManager::OnPointerListItemSelectionChanged ( Object^ sender, ListViewItemSelectionChangedEventArgs^ e )
{
	if ( e->IsSelected ) {
		this->m_txtName->Text = e->Item->Name;
		this->m_lstTypeList->SelectedIndex = String::IsNullOrEmpty(e->Item->Text) ? 1 : 0;

		switch ( this->m_lstTypeList->SelectedIndex ) {
			case 0: /* Static Address */
				this->m_txtPattern->Text = String::Empty;
				this->m_txtBase->Text    = e->Item->SubItems[L"Base"]->Text;
				this->m_txtOffset->Text  = e->Item->SubItems[L"Offset"]->Text;				
				break;
			case 1: /* Array Of Bytes */
				this->m_txtPattern->Text = e->Item->Text;
				this->m_txtBase->Text    = String::Empty;
				this->m_txtOffset->Text  = String::Empty;
				break;
		}

		if ( ((bool)(e->Item->Tag)) ) {
			int iValue = this->GetValue(e->Item->Name);

			if ( iValue == ( -1 ) ) {
				this->m_txtValue->Text = L"?";
			} else {
				this->m_txtValue->Tag = iValue;

				if ( this->m_chxHexNumber->Checked ) {
					this->m_txtValue->Text = iValue.ToString(L"X8");
				} else {
					this->m_txtValue->Text = iValue.ToString(L"N0");
				}
			}
		} else {
			this->m_txtValue->Text = e->Item->SubItems[L"Value"]->Text;
		}
	}
}

void ZMemoryManager::OnToolTipPopup ( Object^ sender, PopupEventArgs^ e )
{
	System::Drawing::Size size = e->ToolTipSize;
	size.Width = Math::Min(size.Width, 300);
	e->ToolTipSize = size;
}

void ZMemoryManager::OnTick ( Object^ sender, EventArgs^ e )
{
	if ( this->m_lstPointerList->InvokeRequired ) {
		this->Invoke(gcnew OnTickCaller(this, &ZMemoryManager::OnTick), gcnew array<Object^>{ sender, e });
	} else {
		if ( this->m_lstPointerList->Items->Count > 0 ) {
			for each ( ListViewItem^ listViewItem in this->m_lstPointerList->Items ) {
				if ( ((bool)(listViewItem->Tag)) )
					listViewItem->SubItems[L"Value"]->Text = this->GetValue(listViewItem->Name).ToString(L"N0");
			}
		}
	}
}
