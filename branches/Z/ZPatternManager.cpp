#include "Z.h"
#include "Z_CLI.h"
#include "Z_GUI.h"

using namespace Z;
using namespace System;
using namespace System::Globalization;
using namespace System::Text;
using namespace System::Text::RegularExpressions;

void ZPatternManager::Initialize ( String^ title )
{
	this->m_Collection = gcnew ZPatternCollection;
	this->Text = String::Format(L"Z - Pattern Manager - {0}", title);
}

ZPattern^ ZPatternManager::CreatePattern ( String^ pattern )
{
	if ( this->m_lstPatternList->InvokeRequired ) {
		return dynamic_cast<ZPattern^>(this->m_lstPatternList->Invoke(gcnew CreatePatternCaller(this, &ZPatternManager::CreatePattern), gcnew array<Object^>{ pattern }));
	} else {
		for each ( ListViewItem^ listViewItem in this->m_lstPatternList->Items ) {
			if ( String::Equals(pattern, listViewItem->Text, StringComparison::InvariantCultureIgnoreCase) )
				return this->m_Collection[(int)(listViewItem->Tag)];
		}

		ListViewItem^ listViewItem = gcnew ListViewItem(pattern);
		listViewItem->Checked      = true;

		ZPattern^ newPattern = gcnew ZPattern(pattern);
		listViewItem->Tag = this->m_Collection->Add(newPattern);

		this->m_lstPatternList->Items->Add(listViewItem);
		return newPattern;
	}
}

/* Match bytes against a pattern in the list */
bool ZPatternManager::IsMatch ( String^ rawBytes )
{
	return ( this->m_Collection->IsMatch(rawBytes) != ( -1 ) );
}

void ZPatternManager::OnListColumnClick ( Object^ sender, ColumnClickEventArgs^ e )
{
	if ( e->Column == 0 ) {
		if ( this->m_lstPatternList->Columns[0]->Tag == nullptr )
			this->m_lstPatternList->Columns[0]->Tag = false;

		for each ( ListViewItem^ listViewItem in this->m_lstPatternList->Items ) 
			listViewItem->Checked = ((bool)(this->m_lstPatternList->Columns[0]->Tag)) ? false : true;

		this->m_lstPatternList->Columns[0]->Tag = ((bool)(this->m_lstPatternList->Columns[0]->Tag)) ? false : true;
	}
}

void ZPatternManager::OnListItemActivate ( Object^ sender, EventArgs^ e )
{
	if ( this->m_lstPatternList->SelectedIndices->Count > 0 )
		ZContext::G->Application->SetPacketText(this->m_lstPatternList->Items[this->m_lstPatternList->SelectedIndices[0]]->Text);
}

void ZPatternManager::OnListItemChecked ( Object^ sender, ItemCheckedEventArgs^ e )
{
	this->m_Collection[((int)(e->Item->Tag))]->Enabled = e->Item->Checked;
}

void ZPatternManager::OnClearClick ( Object^ sender, EventArgs^ e )
{
	if ( this->m_lstPatternList->Items->Count > 0 ) {
		if ( this->m_lstPatternList->SelectedIndices->Count > 0 ) {
			ListViewItem^ listViewItem;

			do {
				listViewItem = this->m_lstPatternList->Items[this->m_lstPatternList->SelectedIndices[0]];

				this->m_Collection->Remove((int)(listViewItem->Tag));
				this->m_lstPatternList->Items->RemoveAt(this->m_lstPatternList->SelectedIndices[0]);
			} while ( this->m_lstPatternList->SelectedIndices->Count > 0 );
		} else {
			this->m_Collection->Clear();
			this->m_lstPatternList->Items->Clear();
		}
	}
}

void ZPatternManager::OnListItemMouseHover ( Object^ sender, ListViewItemMouseHoverEventArgs^ e )
{
	this->m_ttpToolTip->Show(e->Item->Text, e->Item->ListView);
}

void ZPatternManager::OnToolTipPopup ( Object^ sender, PopupEventArgs^ e )
{
	System::Drawing::Size size = e->ToolTipSize;
	size.Width = Math::Min(size.Width, 300);
	e->ToolTipSize = size;
}