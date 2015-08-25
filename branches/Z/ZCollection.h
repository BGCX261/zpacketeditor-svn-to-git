#ifndef __ZCollection_h__
#define __ZCollection_h__

#pragma once

#include "Z.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Drawing;
using namespace System::Windows::Forms;

namespace Z
{
	ref class ZCollection : public System::Windows::Forms::Form
	{
		delegate void AppendItemCaller ( ListViewItem^ listViewItem );

		delegate void ClearItemsCaller ( void );

	public:
		/* Constructor */
		ZCollection ( String^ title )
		{
			InitializeComponent();

			this->Text = String::Format(L"Z - Packet Collection - {0}", title);
		}

		/* Dispose */
		~ZCollection ( void )
		{
			if ( components )
				delete components;
		}

	public:
		/* Add a new packet item to this collection */
		void AppendItem ( ListViewItem^ listViewItem );

		/* Clear the collection */
		void ClearItems ( void );

	private:
		void OnExportClick ( Object^ sender, EventArgs^  e);

		void OnExportAsClick ( Object^ sender, EventArgs^  e);

		void OnClearClick ( Object^ sender, EventArgs^  e);

		void OnListItemActivate ( Object^ sender, EventArgs^  e);

		void OnListItemMouseHover ( Object^ sender, ListViewItemMouseHoverEventArgs^ e );

		void OnToolTipPopup ( Object^ sender, PopupEventArgs^ e );

	private: System::Windows::Forms::MenuStrip^  m_mbrStrip;

	private: System::Windows::Forms::ToolStripMenuItem^  m_itmCollectionToolStripMenuItem;


	private: System::Windows::Forms::ToolStripMenuItem^  m_itmExportToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmExportAsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  m_sprCollectionMenuToolStripSeparator1;

	private: System::Windows::Forms::ToolStripMenuItem^  m_itmClearToolStripMenuItem;
	private: System::Windows::Forms::StatusStrip^  m_sbrStrip;
	private: System::Windows::Forms::ToolStripStatusLabel^  m_lblStatus;
	private: System::Windows::Forms::Panel^  m_pnlContainer;
	private: System::Windows::Forms::ListView^  m_lstPacketList;
	private: System::Windows::Forms::ColumnHeader^  m_hdrSize;
	private: System::Windows::Forms::ColumnHeader^  m_hdrCode;
	private: System::Windows::Forms::ColumnHeader^  m_hdrPacket;
	private: System::Windows::Forms::ColumnHeader^  m_hdrImage;
	private: System::Windows::Forms::ImageList^  m_lstPacketImages;
	private: System::Windows::Forms::ToolTip^  m_ttpToolTip;



#pragma region Windows Form Designer generated code
	private:
		System::ComponentModel::IContainer^ components;

		void InitializeComponent ( void )
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ZCollection::typeid));
			this->m_mbrStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->m_itmCollectionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmExportToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmExportAsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_sprCollectionMenuToolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->m_itmClearToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_sbrStrip = (gcnew System::Windows::Forms::StatusStrip());
			this->m_lblStatus = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->m_pnlContainer = (gcnew System::Windows::Forms::Panel());
			this->m_lstPacketList = (gcnew System::Windows::Forms::ListView());
			this->m_hdrImage = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_hdrSize = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_hdrCode = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_hdrPacket = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_lstPacketImages = (gcnew System::Windows::Forms::ImageList(this->components));
			this->m_ttpToolTip = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->m_mbrStrip->SuspendLayout();
			this->m_sbrStrip->SuspendLayout();
			this->m_pnlContainer->SuspendLayout();
			this->SuspendLayout();
			// 
			// m_mbrStrip
			// 
			this->m_mbrStrip->BackColor = System::Drawing::SystemColors::Control;
			this->m_mbrStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->m_itmCollectionToolStripMenuItem});
			this->m_mbrStrip->Location = System::Drawing::Point(0, 0);
			this->m_mbrStrip->Name = L"m_mbrStrip";
			this->m_mbrStrip->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
			this->m_mbrStrip->Size = System::Drawing::Size(498, 24);
			this->m_mbrStrip->TabIndex = 0;
			// 
			// m_itmCollectionToolStripMenuItem
			// 
			this->m_itmCollectionToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->m_itmExportToolStripMenuItem, 
				this->m_itmExportAsToolStripMenuItem, this->m_sprCollectionMenuToolStripSeparator1, this->m_itmClearToolStripMenuItem});
			this->m_itmCollectionToolStripMenuItem->Name = L"m_itmCollectionToolStripMenuItem";
			this->m_itmCollectionToolStripMenuItem->Size = System::Drawing::Size(75, 20);
			this->m_itmCollectionToolStripMenuItem->Text = L"&Collection";
			// 
			// m_itmExportToolStripMenuItem
			// 
			this->m_itmExportToolStripMenuItem->Enabled = false;
			this->m_itmExportToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_itmExportToolStripMenuItem.Image")));
			this->m_itmExportToolStripMenuItem->Name = L"m_itmExportToolStripMenuItem";
			this->m_itmExportToolStripMenuItem->Size = System::Drawing::Size(140, 22);
			this->m_itmExportToolStripMenuItem->Text = L"Export";
			this->m_itmExportToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZCollection::OnExportClick);
			// 
			// m_itmExportAsToolStripMenuItem
			// 
			this->m_itmExportAsToolStripMenuItem->Enabled = false;
			this->m_itmExportAsToolStripMenuItem->Name = L"m_itmExportAsToolStripMenuItem";
			this->m_itmExportAsToolStripMenuItem->Size = System::Drawing::Size(140, 22);
			this->m_itmExportAsToolStripMenuItem->Text = L"Export As";
			this->m_itmExportAsToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZCollection::OnExportAsClick);
			// 
			// m_sprCollectionMenuToolStripSeparator1
			// 
			this->m_sprCollectionMenuToolStripSeparator1->Name = L"m_sprCollectionMenuToolStripSeparator1";
			this->m_sprCollectionMenuToolStripSeparator1->Size = System::Drawing::Size(137, 6);
			// 
			// m_itmClearToolStripMenuItem
			// 
			this->m_itmClearToolStripMenuItem->Enabled = false;
			this->m_itmClearToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_itmClearToolStripMenuItem.Image")));
			this->m_itmClearToolStripMenuItem->Name = L"m_itmClearToolStripMenuItem";
			this->m_itmClearToolStripMenuItem->Size = System::Drawing::Size(140, 22);
			this->m_itmClearToolStripMenuItem->Text = L"Clear";
			this->m_itmClearToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZCollection::OnClearClick);
			// 
			// m_sbrStrip
			// 
			this->m_sbrStrip->AutoSize = false;
			this->m_sbrStrip->BackColor = System::Drawing::SystemColors::Control;
			this->m_sbrStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->m_lblStatus});
			this->m_sbrStrip->Location = System::Drawing::Point(0, 423);
			this->m_sbrStrip->Name = L"m_sbrStrip";
			this->m_sbrStrip->Size = System::Drawing::Size(498, 25);
			this->m_sbrStrip->SizingGrip = false;
			this->m_sbrStrip->TabIndex = 0;
			// 
			// m_lblStatus
			// 
			this->m_lblStatus->Name = L"m_lblStatus";
			this->m_lblStatus->Size = System::Drawing::Size(483, 20);
			this->m_lblStatus->Spring = true;
			this->m_lblStatus->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// m_pnlContainer
			// 
			this->m_pnlContainer->Controls->Add(this->m_lstPacketList);
			this->m_pnlContainer->Dock = System::Windows::Forms::DockStyle::Fill;
			this->m_pnlContainer->Location = System::Drawing::Point(0, 24);
			this->m_pnlContainer->Margin = System::Windows::Forms::Padding(0);
			this->m_pnlContainer->Name = L"m_pnlContainer";
			this->m_pnlContainer->Padding = System::Windows::Forms::Padding(4);
			this->m_pnlContainer->Size = System::Drawing::Size(498, 399);
			this->m_pnlContainer->TabIndex = 0;
			// 
			// m_lstPacketList
			// 
			this->m_lstPacketList->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {this->m_hdrImage, 
				this->m_hdrSize, this->m_hdrCode, this->m_hdrPacket});
			this->m_lstPacketList->Dock = System::Windows::Forms::DockStyle::Fill;
			this->m_lstPacketList->FullRowSelect = true;
			this->m_lstPacketList->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->m_lstPacketList->Location = System::Drawing::Point(4, 4);
			this->m_lstPacketList->Margin = System::Windows::Forms::Padding(0);
			this->m_lstPacketList->Name = L"m_lstPacketList";
			this->m_lstPacketList->Size = System::Drawing::Size(490, 391);
			this->m_lstPacketList->StateImageList = this->m_lstPacketImages;
			this->m_lstPacketList->TabIndex = 0;
			this->m_lstPacketList->UseCompatibleStateImageBehavior = false;
			this->m_lstPacketList->View = System::Windows::Forms::View::Details;
			this->m_lstPacketList->ItemActivate += gcnew System::EventHandler(this, &ZCollection::OnListItemActivate);
			this->m_lstPacketList->ItemMouseHover += gcnew System::Windows::Forms::ListViewItemMouseHoverEventHandler(this, &ZCollection::OnListItemMouseHover);
			this->m_lstPacketList->ItemSelectionChanged += gcnew System::Windows::Forms::ListViewItemSelectionChangedEventHandler(this, &ZCollection::OnListItemSelectionChanged);
			// 
			// m_hdrImage
			// 
			this->m_hdrImage->Text = L" ";
			this->m_hdrImage->Width = 20;
			// 
			// m_hdrSize
			// 
			this->m_hdrSize->Text = L"Size";
			this->m_hdrSize->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->m_hdrSize->Width = 55;
			// 
			// m_hdrCode
			// 
			this->m_hdrCode->Text = L"Code";
			this->m_hdrCode->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->m_hdrCode->Width = 65;
			// 
			// m_hdrPacket
			// 
			this->m_hdrPacket->Text = L"Data";
			this->m_hdrPacket->Width = 330;
			// 
			// m_lstPacketImages
			// 
			this->m_lstPacketImages->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"m_lstPacketImages.ImageStream")));
			this->m_lstPacketImages->TransparentColor = System::Drawing::Color::Transparent;
			this->m_lstPacketImages->Images->SetKeyName(0, L"green_arrow_down.png");
			this->m_lstPacketImages->Images->SetKeyName(1, L"blue_arrow_down.png");
			// 
			// m_ttpToolTip
			// 
			this->m_ttpToolTip->AutomaticDelay = 250;
			this->m_ttpToolTip->Popup += gcnew System::Windows::Forms::PopupEventHandler(this, &ZCollection::OnToolTipPopup);
			// 
			// ZCollection
			// 
			this->ClientSize = System::Drawing::Size(498, 448);
			this->Controls->Add(this->m_pnlContainer);
			this->Controls->Add(this->m_sbrStrip);
			this->Controls->Add(this->m_mbrStrip);
			this->Font = (gcnew System::Drawing::Font(L"Verdana", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->MainMenuStrip = this->m_mbrStrip;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->MinimumSize = System::Drawing::Size(506, 475);
			this->Name = L"ZCollection";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->m_mbrStrip->ResumeLayout(false);
			this->m_mbrStrip->PerformLayout();
			this->m_sbrStrip->ResumeLayout(false);
			this->m_sbrStrip->PerformLayout();
			this->m_pnlContainer->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	void OnListItemSelectionChanged ( Object^ sender, ListViewItemSelectionChangedEventArgs^ e );
};
}


#endif /* __ZCollection_h__ */