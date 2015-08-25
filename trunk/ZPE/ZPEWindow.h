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
#ifndef __ZPEWindow_h__
#define __ZPEWindow_h__

/* Tell the compiler to reference this header file only once */
#pragma once

/*
* You can include native C++ header files in Managed C++/CLI
* header files as long as they appear before the first line
* of managed code
*/
#include "ZPE.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Drawing;
using namespace System::Windows::Forms;

/* When creating a Managed C++ Windows Form class it is
* important to contain that class inside a namespace so
* that the designer can accurately create and store resources
*/
namespace ZPE
{
	/* Z Packet Editor window */
	ref class ZPEWindow : public System::Windows::Forms::Form
	{		
	public:
		/* Constructor */
		ZPEWindow ( String^ title )
		{
			/* Calling this initialize all of our UI controls */
			InitializeComponent();

			/* Set the title of the window */
			this->Text = String::Format("Z Packet Editor - {0}", title);
		}

		/* Destructor
		*
		* In Managed C++/CLI the destructor takes on a different
		* role than it does in native C++. This destructor is actually
		* just a synonym for the IDisposable method Dispose(bool).
		*/
		~ZPEWindow ( void )
		{
			/*
			* If we have contained objects then they will be
			* released when this window itself is dstroyed.
			*/
			if ( components )
				delete components;
		}

	public:
		/* Is this window logging packets that contain NULL data */
		property bool IgnoreNull;
		/* Is this window logging empty packets */
		property bool IgnoreEmpty;

	public:
		/* Add new item to the packet list */
		void AddItem ( ListViewItem^ listViewItem );

	private:
		/* Occurs when an item is hovered over */
		void OnItemMouseHover ( Object^ sender, ListViewItemMouseHoverEventArgs^ e );
		/* Occurs when an item is selected or unselected in the packet list */
		void OnItemSelectionChanged ( Object^  sender, ListViewItemSelectionChangedEventArgs^ e );
		/* Occurs when the Copy button click */
		void OnCopyClick ( Object^ sender, EventArgs^ e);
		/* Occurs when the Ignore null packets option is checked */
		void OnIgnoreNullCheckedChanged ( Object^ sender, EventArgs^ e);
		/* Occurs when the Ignore empty packets option is checked */
		void OnIgnoreEmptyCheckedChanged ( Object^ sender, EventArgs^ e );
		/* Occurs when the tooltip pops-up */
		void OnToolTipPopup ( Object^ sender, PopupEventArgs^ e );

	private:
		System::Windows::Forms::ListView^     m_lstPacketList;
		System::Windows::Forms::ColumnHeader^ m_hdrPacket;
		System::Windows::Forms::ColumnHeader^ m_hdrSize;
		System::Windows::Forms::ColumnHeader^ m_hdrCode;
		System::Windows::Forms::ColumnHeader^ m_hdrData;		
		System::Windows::Forms::Label^        m_lblPacket;
		System::Windows::Forms::TextBox^      m_txtPacket;
		System::Windows::Forms::Button^       m_btnCopy;
		System::Windows::Forms::CheckBox^     m_chxIgnoreNull;
		System::Windows::Forms::CheckBox^     m_chxIgnoreEmpty;
		System::Windows::Forms::ToolTip^      m_ttpToolTip;

	/* Windows Forms designer code */
	private:
		System::ComponentModel::IContainer^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent ( void )
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ZPEWindow::typeid));
			this->m_lstPacketList = (gcnew System::Windows::Forms::ListView());
			this->m_hdrPacket = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_hdrSize = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_hdrCode = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_hdrData = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_ttpToolTip = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->m_btnCopy = (gcnew System::Windows::Forms::Button());
			this->m_chxIgnoreNull = (gcnew System::Windows::Forms::CheckBox());
			this->m_chxIgnoreEmpty = (gcnew System::Windows::Forms::CheckBox());
			this->m_lblPacket = (gcnew System::Windows::Forms::Label());
			this->m_txtPacket = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// m_lstPacketList
			// 
			this->m_lstPacketList->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->m_lstPacketList->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {this->m_hdrPacket, 
				this->m_hdrSize, this->m_hdrCode, this->m_hdrData});
			this->m_lstPacketList->FullRowSelect = true;
			this->m_lstPacketList->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->m_lstPacketList->Location = System::Drawing::Point(4, 4);
			this->m_lstPacketList->Margin = System::Windows::Forms::Padding(0);
			this->m_lstPacketList->Name = L"m_lstPacketList";
			this->m_lstPacketList->Size = System::Drawing::Size(492, 392);
			this->m_lstPacketList->TabIndex = 0;
			this->m_lstPacketList->UseCompatibleStateImageBehavior = false;
			this->m_lstPacketList->View = System::Windows::Forms::View::Details;
			this->m_lstPacketList->ItemMouseHover += gcnew System::Windows::Forms::ListViewItemMouseHoverEventHandler(this, &ZPEWindow::OnItemMouseHover);
			this->m_lstPacketList->ItemSelectionChanged += gcnew System::Windows::Forms::ListViewItemSelectionChangedEventHandler(this, &ZPEWindow::OnItemSelectionChanged);
			// 
			// m_hdrPacket
			// 
			this->m_hdrPacket->Text = L"";
			this->m_hdrPacket->Width = 0;
			// 
			// m_hdrSize
			// 
			this->m_hdrSize->Text = L"Size";
			this->m_hdrSize->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->m_hdrSize->Width = 45;
			// 
			// m_hdrCode
			// 
			this->m_hdrCode->Text = L"Opcode";
			this->m_hdrCode->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->m_hdrCode->Width = 75;
			// 
			// m_hdrData
			// 
			this->m_hdrData->Text = L"Data";
			this->m_hdrData->Width = 345;
			// 
			// m_ttpToolTip
			// 
			this->m_ttpToolTip->AutomaticDelay = 250;
			this->m_ttpToolTip->Popup += gcnew System::Windows::Forms::PopupEventHandler(this, &ZPEWindow::OnToolTipPopup);
			// 
			// m_btnCopy
			// 
			this->m_btnCopy->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->m_btnCopy->Location = System::Drawing::Point(437, 400);
			this->m_btnCopy->Margin = System::Windows::Forms::Padding(0);
			this->m_btnCopy->Name = L"m_btnCopy";
			this->m_btnCopy->Size = System::Drawing::Size(59, 25);
			this->m_btnCopy->TabIndex = 0;
			this->m_btnCopy->TabStop = false;
			this->m_btnCopy->Text = L"Copy";
			this->m_ttpToolTip->SetToolTip(this->m_btnCopy, L"Copy this packet to the clipboard");
			this->m_btnCopy->UseVisualStyleBackColor = true;
			this->m_btnCopy->Click += gcnew System::EventHandler(this, &ZPEWindow::OnCopyClick);
			// 
			// m_chxIgnoreNull
			// 
			this->m_chxIgnoreNull->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->m_chxIgnoreNull->Location = System::Drawing::Point(7, 431);
			this->m_chxIgnoreNull->Margin = System::Windows::Forms::Padding(0);
			this->m_chxIgnoreNull->Name = L"m_chxIgnoreNull";
			this->m_chxIgnoreNull->Padding = System::Windows::Forms::Padding(5, 0, 0, 0);
			this->m_chxIgnoreNull->Size = System::Drawing::Size(149, 21);
			this->m_chxIgnoreNull->TabIndex = 0;
			this->m_chxIgnoreNull->TabStop = false;
			this->m_chxIgnoreNull->Text = L"Ignore NULL packets";
			this->m_ttpToolTip->SetToolTip(this->m_chxIgnoreNull, L"Don\'t display packets that contain only null data");
			this->m_chxIgnoreNull->UseVisualStyleBackColor = true;
			this->m_chxIgnoreNull->CheckedChanged += gcnew System::EventHandler(this, &ZPEWindow::OnIgnoreNullCheckedChanged);
			// 
			// m_chxIgnoreEmpty
			// 
			this->m_chxIgnoreEmpty->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->m_chxIgnoreEmpty->Location = System::Drawing::Point(156, 430);
			this->m_chxIgnoreEmpty->Margin = System::Windows::Forms::Padding(0);
			this->m_chxIgnoreEmpty->Name = L"m_chxIgnoreEmpty";
			this->m_chxIgnoreEmpty->Padding = System::Windows::Forms::Padding(5, 0, 0, 0);
			this->m_chxIgnoreEmpty->Size = System::Drawing::Size(160, 21);
			this->m_chxIgnoreEmpty->TabIndex = 0;
			this->m_chxIgnoreEmpty->TabStop = false;
			this->m_chxIgnoreEmpty->Text = L"Ignore empty packets";
			this->m_ttpToolTip->SetToolTip(this->m_chxIgnoreEmpty, L"Don\'t display empty packets");
			this->m_chxIgnoreEmpty->UseVisualStyleBackColor = true;
			this->m_chxIgnoreEmpty->CheckedChanged += gcnew System::EventHandler(this, &ZPEWindow::OnIgnoreEmptyCheckedChanged);
			// 
			// m_lblPacket
			// 
			this->m_lblPacket->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->m_lblPacket->Location = System::Drawing::Point(4, 400);
			this->m_lblPacket->Margin = System::Windows::Forms::Padding(0);
			this->m_lblPacket->Name = L"m_lblPacket";
			this->m_lblPacket->Size = System::Drawing::Size(50, 25);
			this->m_lblPacket->TabIndex = 1;
			this->m_lblPacket->Text = L"Packet";
			this->m_lblPacket->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// m_txtPacket
			// 
			this->m_txtPacket->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->m_txtPacket->BackColor = System::Drawing::SystemColors::Window;
			this->m_txtPacket->Location = System::Drawing::Point(60, 403);
			this->m_txtPacket->Margin = System::Windows::Forms::Padding(0);
			this->m_txtPacket->MaxLength = 0;
			this->m_txtPacket->Name = L"m_txtPacket";
			this->m_txtPacket->ReadOnly = true;
			this->m_txtPacket->Size = System::Drawing::Size(375, 21);
			this->m_txtPacket->TabIndex = 2;
			// 
			// ZPEWindow
			// 
			this->ClientSize = System::Drawing::Size(500, 455);
			this->Controls->Add(this->m_chxIgnoreEmpty);
			this->Controls->Add(this->m_chxIgnoreNull);
			this->Controls->Add(this->m_btnCopy);
			this->Controls->Add(this->m_txtPacket);
			this->Controls->Add(this->m_lblPacket);
			this->Controls->Add(this->m_lstPacketList);
			this->Font = (gcnew System::Drawing::Font(L"Verdana", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MinimumSize = System::Drawing::Size(516, 490);
			this->Name = L"ZPEWindow";
			this->Padding = System::Windows::Forms::Padding(4);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	};
}

#endif /* __ZPEWindow_h__ */
