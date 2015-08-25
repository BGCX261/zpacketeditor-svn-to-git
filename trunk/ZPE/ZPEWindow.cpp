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
#include "ZPEWindow.h"

/*
 * This file must be compiled with the /CLR and /EHa flags
 * set so that this file will be compiled as managed code.
 */

/* Localize the application namespace */
using namespace ZPE;

/*
 * Delegate type used to make adding items to the list 
 * a thread-safe operation. Protecting us from errors.
 */
delegate void AddItemCaller ( ListViewItem^ listViewItem );

/* Add a new item to the packet list */
void ZPEWindow::AddItem ( ListViewItem^ listViewItem )
{
	/*
	 * Check the InvokeRequired member to determine if
	 * this function needs to be called in the same
	 * thread of operation as the control. Doing this
	 * prevents certain thread-related exceptions from
	 * being thrown.
	 */
	if ( this->m_lstPacketList->InvokeRequired ) {
		this->m_lstPacketList->Invoke(gcnew AddItemCaller(this, &ZPEWindow::AddItem), gcnew array<Object^>{ listViewItem });	
	} else {
		/*
		 * If the packet list contains more than 8,192 packets
		 * we trim the first item to make sure that the list
		 * does not exceed that size.
		 */
		if ( this->m_lstPacketList->Items->Count > 8192 )
			this->m_lstPacketList->Items->RemoveAt(0);

		/* Add the new item to the packet list */
		this->m_lstPacketList->Items->Add(listViewItem);
	}
}

/* When an item is hovered over */
void ZPEWindow::OnItemMouseHover ( Object^ sender, ListViewItemMouseHoverEventArgs^ e )
{
	/* Show a tooltip for list item */
	this->m_ttpToolTip->Show(e->Item->ToolTipText, e->Item->ListView);
}

/*
 * When a new item is selected in the packet list display it
 * inside the packet TextBox control.
 */
void ZPEWindow::OnItemSelectionChanged ( Object^ sender, ListViewItemSelectionChangedEventArgs^ e )
{
	/*
	 * If the item is being selected then display it's byte code in the
	 * packet TextBox control  with spaces separating bytes.
	 */
	if ( e->IsSelected )
		this->m_txtPacket->Text = e->Item->Text;
}

/*
 * When the copy button is clicked, copy the byte code from the
 * packet TextBox to the system clipboard.
 */
void ZPEWindow::OnCopyClick ( Object^ sender, EventArgs^ e )
{
	/* If there is a packet displayed then copy it to the clipboard. */
	if ( this->m_txtPacket->TextLength > 0 )
		this->m_txtPacket->Copy();
}

/* When the Ignore null packets option is checked */
void ZPEWindow::OnIgnoreNullCheckedChanged ( Object^ sender, EventArgs^ e)
{
	this->IgnoreNull = this->m_chxIgnoreNull->Checked;
}

/* When the Ignore empty packets option is checked */
void ZPEWindow::OnIgnoreEmptyCheckedChanged ( Object^ sender, EventArgs^ e )
{
	this->IgnoreEmpty = this->m_chxIgnoreEmpty->Checked;
}

/* When the tooltip pops-up */
void ZPEWindow::OnToolTipPopup ( Object^ sender, PopupEventArgs^ e )
{
	/*
  	 * Truncate the width of the ToolTip window so that
	 * it does not exceed 350 pixels
	 */
	System::Drawing::Size newSize;
	newSize.Width  = Math::Min(e->ToolTipSize.Width, 350);
	e->ToolTipSize = newSize;
}