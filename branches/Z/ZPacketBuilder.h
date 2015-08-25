#ifndef __ZPacketBuilder_h__
#define __ZPacketBuilder_h__

#pragma once

#include "Z.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Drawing;
using namespace System::Windows::Forms;

namespace Z
{
	ref class ZPacketBuilder : public System::Windows::Forms::Form
	{
		/* Append a menu item object to the Insert context menu   */
		delegate void AppendInsertMenuItemCaller ( String^ name );
		/* Remove a menu item object from the Insert context menu */
		delegate void RemoveInsertMenuItemCaller ( String^ name );
		/* Remove all menu items from the Insert context menu     */
		delegate void ClearInsertMenuCaller ( void );

	private:
		/* Random number generator */
		static Random^ Randomize = gcnew Random;

	public:
		/* Constructor */
		ZPacketBuilder ( void )
		{
			InitializeComponent();
		}

		/* Dispose */
		~ZPacketBuilder ( void )
		{
			if ( components )
				delete components;
		}


	public:
		/* Append a menu item object to the Insert context menu */
		void AppendInsertMenuItem ( String^ name );
		/* Remove a menu item object from the Insert context menu */
		void RemoveInsertMenuItem ( String^ name );
		/* Remove all menu items from the Insert context menu */
		void ClearInsertMenu ( void );

	private:
		void OnPacketTextChanged ( Object^ sender, EventArgs^ e );

		void OnClearClick ( Object^ sender, EventArgs^ e );

		void OnCopyClick ( Object^ sender, EventArgs^ e );

		void OnSendClick ( Object^ sender, EventArgs^ e );

		void OnCutTextClick ( Object^ sender, EventArgs^ e );

		void OnCopyTextClick ( Object^ sender, EventArgs^ e );

		void OnPasteTextClick ( Object^ sender, EventArgs^ e );

		void OnRandByteClick ( Object^ sender, EventArgs^ e );

		void OnRandInt16Click ( Object^ sender, EventArgs^ e );

		void OnRandInt32Click ( Object^ sender, EventArgs^ e );

		void OnRandAsciiClick ( Object^ sender, EventArgs^ e );

		void OnRandStringClick ( Object^ sender, EventArgs^ e );

		void OnPointerDropDownItemClicked ( Object^ sender, ToolStripItemClickedEventArgs^ e );

		void OnPacketMenuOpening ( Object^ sender, CancelEventArgs^ e );

	private:
			System::Windows::Forms::SplitContainer^ m_splContainer;
			System::Windows::Forms::TabControl^ m_tbInput;
			System::Windows::Forms::TabPage^ m_tbpPacket;
			System::Windows::Forms::TabPage^ m_tbpStream;
			System::Windows::Forms::Label^ m_lblText;
			System::Windows::Forms::Button^ m_btnClear;
			System::Windows::Forms::ToolTip^ m_ttpToolTip;
			System::Windows::Forms::Button^ m_btnCopy;
			System::Windows::Forms::Button^ m_btnSend;
			System::Windows::Forms::ImageList^ m_lstTabImages;
			System::Windows::Forms::TextBox^ m_txtPacket;
			System::Windows::Forms::TextBox^ m_txtStream;
			System::Windows::Forms::ContextMenuStrip^ m_ctxPacketMenu;
			System::Windows::Forms::ToolStripMenuItem^ m_itmInsertToolStripMenuItem;
			System::Windows::Forms::ToolStripMenuItem^ m_itmRandomToolStripMenuItem;
			System::Windows::Forms::ToolStripMenuItem^ m_itmByteToolStripMenuItem;
			System::Windows::Forms::ToolStripMenuItem^ m_itmInt16ToolStripMenuItem;
			System::Windows::Forms::ToolStripMenuItem^ m_itmInt32ToolStripMenuItem;
			System::Windows::Forms::ToolStripMenuItem^ m_itmAsciiToolStripMenuItem;
			System::Windows::Forms::ToolStripMenuItem^ m_itmStringToolStripMenuItem;
			System::Windows::Forms::ToolStripSeparator^ m_sprRandomMenuToolStripSeparator1;
			System::Windows::Forms::ToolStripMenuItem^ m_itmPointerToolStripMenuItem;
			System::Windows::Forms::ToolStripMenuItem^ m_itmCutToolStripMenuItem;
			System::Windows::Forms::ToolStripMenuItem^ m_itmCopyToolStripMenuItem;
			System::Windows::Forms::ToolStripMenuItem^ m_itmPasteToolStripMenuItem;
			System::Windows::Forms::ToolStripSeparator^ m_sprPacketMenuToolStripSeparator1;

#pragma region Windows Form Designer generated code
	private:
		System::ComponentModel::IContainer^ components;

		void InitializeComponent ( void )
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ZPacketBuilder::typeid));
			this->m_splContainer = (gcnew System::Windows::Forms::SplitContainer());
			this->m_tbInput = (gcnew System::Windows::Forms::TabControl());
			this->m_tbpPacket = (gcnew System::Windows::Forms::TabPage());
			this->m_txtPacket = (gcnew System::Windows::Forms::TextBox());
			this->m_ctxPacketMenu = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->m_itmInsertToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmRandomToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmByteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmInt16ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmInt32ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_sprRandomMenuToolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->m_itmAsciiToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmStringToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmPointerToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_sprPacketMenuToolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->m_itmCutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmCopyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmPasteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_tbpStream = (gcnew System::Windows::Forms::TabPage());
			this->m_txtStream = (gcnew System::Windows::Forms::TextBox());
			this->m_lstTabImages = (gcnew System::Windows::Forms::ImageList(this->components));
			this->m_btnSend = (gcnew System::Windows::Forms::Button());
			this->m_btnCopy = (gcnew System::Windows::Forms::Button());
			this->m_btnClear = (gcnew System::Windows::Forms::Button());
			this->m_lblText = (gcnew System::Windows::Forms::Label());
			this->m_ttpToolTip = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->m_splContainer->Panel1->SuspendLayout();
			this->m_splContainer->Panel2->SuspendLayout();
			this->m_splContainer->SuspendLayout();
			this->m_tbInput->SuspendLayout();
			this->m_tbpPacket->SuspendLayout();
			this->m_ctxPacketMenu->SuspendLayout();
			this->m_tbpStream->SuspendLayout();
			this->SuspendLayout();
			// 
			// m_splContainer
			// 
			this->m_splContainer->Dock = System::Windows::Forms::DockStyle::Fill;
			this->m_splContainer->FixedPanel = System::Windows::Forms::FixedPanel::Panel2;
			this->m_splContainer->IsSplitterFixed = true;
			this->m_splContainer->Location = System::Drawing::Point(4, 4);
			this->m_splContainer->Margin = System::Windows::Forms::Padding(0);
			this->m_splContainer->Name = L"m_splContainer";
			this->m_splContainer->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// m_splContainer.Panel1
			// 
			this->m_splContainer->Panel1->Controls->Add(this->m_tbInput);
			// 
			// m_splContainer.Panel2
			// 
			this->m_splContainer->Panel2->Controls->Add(this->m_btnSend);
			this->m_splContainer->Panel2->Controls->Add(this->m_btnCopy);
			this->m_splContainer->Panel2->Controls->Add(this->m_btnClear);
			this->m_splContainer->Panel2->Controls->Add(this->m_lblText);
			this->m_splContainer->Size = System::Drawing::Size(490, 440);
			this->m_splContainer->SplitterDistance = 408;
			this->m_splContainer->SplitterWidth = 1;
			this->m_splContainer->TabIndex = 0;
			// 
			// m_tbInput
			// 
			this->m_tbInput->Controls->Add(this->m_tbpPacket);
			this->m_tbInput->Controls->Add(this->m_tbpStream);
			this->m_tbInput->Dock = System::Windows::Forms::DockStyle::Fill;
			this->m_tbInput->HotTrack = true;
			this->m_tbInput->ImageList = this->m_lstTabImages;
			this->m_tbInput->Location = System::Drawing::Point(0, 0);
			this->m_tbInput->Margin = System::Windows::Forms::Padding(0);
			this->m_tbInput->Name = L"m_tbInput";
			this->m_tbInput->SelectedIndex = 0;
			this->m_tbInput->ShowToolTips = true;
			this->m_tbInput->Size = System::Drawing::Size(490, 408);
			this->m_tbInput->TabIndex = 0;
			this->m_tbInput->TabStop = false;
			// 
			// m_tbpPacket
			// 
			this->m_tbpPacket->BackColor = System::Drawing::Color::White;
			this->m_tbpPacket->Controls->Add(this->m_txtPacket);
			this->m_tbpPacket->ImageIndex = 0;
			this->m_tbpPacket->Location = System::Drawing::Point(4, 23);
			this->m_tbpPacket->Margin = System::Windows::Forms::Padding(0);
			this->m_tbpPacket->Name = L"m_tbpPacket";
			this->m_tbpPacket->Padding = System::Windows::Forms::Padding(4);
			this->m_tbpPacket->Size = System::Drawing::Size(482, 381);
			this->m_tbpPacket->TabIndex = 0;
			this->m_tbpPacket->Text = L"MapleStory Packet";
			this->m_tbpPacket->ToolTipText = L"Create your custom packet here in literal format";
			// 
			// m_txtPacket
			// 
			this->m_txtPacket->ContextMenuStrip = this->m_ctxPacketMenu;
			this->m_txtPacket->Dock = System::Windows::Forms::DockStyle::Fill;
			this->m_txtPacket->Location = System::Drawing::Point(4, 4);
			this->m_txtPacket->Margin = System::Windows::Forms::Padding(0);
			this->m_txtPacket->MaxLength = 0;
			this->m_txtPacket->Multiline = true;
			this->m_txtPacket->Name = L"m_txtPacket";
			this->m_txtPacket->Size = System::Drawing::Size(474, 373);
			this->m_txtPacket->TabIndex = 1;
			this->m_txtPacket->TextChanged += gcnew System::EventHandler(this, &ZPacketBuilder::OnPacketTextChanged);
			// 
			// m_ctxPacketMenu
			// 
			this->m_ctxPacketMenu->BackColor = System::Drawing::SystemColors::Menu;
			this->m_ctxPacketMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->m_itmInsertToolStripMenuItem, 
				this->m_sprPacketMenuToolStripSeparator1, this->m_itmCutToolStripMenuItem, this->m_itmCopyToolStripMenuItem, this->m_itmPasteToolStripMenuItem});
			this->m_ctxPacketMenu->Name = L"m_ctxPacketMenu";
			this->m_ctxPacketMenu->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
			this->m_ctxPacketMenu->Size = System::Drawing::Size(120, 98);
			this->m_ctxPacketMenu->Opening += gcnew System::ComponentModel::CancelEventHandler(this, &ZPacketBuilder::OnPacketMenuOpening);
			// 
			// m_itmInsertToolStripMenuItem
			// 
			this->m_itmInsertToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->m_itmRandomToolStripMenuItem, 
				this->m_itmPointerToolStripMenuItem});
			this->m_itmInsertToolStripMenuItem->Name = L"m_itmInsertToolStripMenuItem";
			this->m_itmInsertToolStripMenuItem->Size = System::Drawing::Size(119, 22);
			this->m_itmInsertToolStripMenuItem->Text = L"Insert";
			// 
			// m_itmRandomToolStripMenuItem
			// 
			this->m_itmRandomToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {this->m_itmByteToolStripMenuItem, 
				this->m_itmInt16ToolStripMenuItem, this->m_itmInt32ToolStripMenuItem, this->m_sprRandomMenuToolStripSeparator1, this->m_itmAsciiToolStripMenuItem, 
				this->m_itmStringToolStripMenuItem});
			this->m_itmRandomToolStripMenuItem->Name = L"m_itmRandomToolStripMenuItem";
			this->m_itmRandomToolStripMenuItem->Size = System::Drawing::Size(132, 22);
			this->m_itmRandomToolStripMenuItem->Text = L"Random";
			// 
			// m_itmByteToolStripMenuItem
			// 
			this->m_itmByteToolStripMenuItem->Name = L"m_itmByteToolStripMenuItem";
			this->m_itmByteToolStripMenuItem->Size = System::Drawing::Size(164, 22);
			this->m_itmByteToolStripMenuItem->Text = L"Byte";
			this->m_itmByteToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZPacketBuilder::OnRandByteClick);
			// 
			// m_itmInt16ToolStripMenuItem
			// 
			this->m_itmInt16ToolStripMenuItem->Name = L"m_itmInt16ToolStripMenuItem";
			this->m_itmInt16ToolStripMenuItem->Size = System::Drawing::Size(164, 22);
			this->m_itmInt16ToolStripMenuItem->Text = L"16-bit Integer";
			this->m_itmInt16ToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZPacketBuilder::OnRandInt16Click);
			// 
			// m_itmInt32ToolStripMenuItem
			// 
			this->m_itmInt32ToolStripMenuItem->Name = L"m_itmInt32ToolStripMenuItem";
			this->m_itmInt32ToolStripMenuItem->Size = System::Drawing::Size(164, 22);
			this->m_itmInt32ToolStripMenuItem->Text = L"32-bit Integer";
			this->m_itmInt32ToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZPacketBuilder::OnRandInt32Click);
			// 
			// m_sprRandomMenuToolStripSeparator1
			// 
			this->m_sprRandomMenuToolStripSeparator1->Name = L"m_sprRandomMenuToolStripSeparator1";
			this->m_sprRandomMenuToolStripSeparator1->Size = System::Drawing::Size(161, 6);
			// 
			// m_itmAsciiToolStripMenuItem
			// 
			this->m_itmAsciiToolStripMenuItem->Name = L"m_itmAsciiToolStripMenuItem";
			this->m_itmAsciiToolStripMenuItem->Size = System::Drawing::Size(164, 22);
			this->m_itmAsciiToolStripMenuItem->Text = L"ASCII";
			this->m_itmAsciiToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZPacketBuilder::OnRandAsciiClick);
			// 
			// m_itmStringToolStripMenuItem
			// 
			this->m_itmStringToolStripMenuItem->Name = L"m_itmStringToolStripMenuItem";
			this->m_itmStringToolStripMenuItem->Size = System::Drawing::Size(164, 22);
			this->m_itmStringToolStripMenuItem->Text = L"String";
			this->m_itmStringToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZPacketBuilder::OnRandStringClick);
			// 
			// m_itmPointerToolStripMenuItem
			// 
			this->m_itmPointerToolStripMenuItem->Name = L"m_itmPointerToolStripMenuItem";
			this->m_itmPointerToolStripMenuItem->Size = System::Drawing::Size(132, 22);
			this->m_itmPointerToolStripMenuItem->Text = L"Pointer";
			this->m_itmPointerToolStripMenuItem->DropDownItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &ZPacketBuilder::OnPointerDropDownItemClicked);
			// 
			// m_sprPacketMenuToolStripSeparator1
			// 
			this->m_sprPacketMenuToolStripSeparator1->Name = L"m_sprPacketMenuToolStripSeparator1";
			this->m_sprPacketMenuToolStripSeparator1->Size = System::Drawing::Size(116, 6);
			// 
			// m_itmCutToolStripMenuItem
			// 
			this->m_itmCutToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_itmCutToolStripMenuItem.Image")));
			this->m_itmCutToolStripMenuItem->Name = L"m_itmCutToolStripMenuItem";
			this->m_itmCutToolStripMenuItem->Size = System::Drawing::Size(119, 22);
			this->m_itmCutToolStripMenuItem->Text = L"Cut";
			this->m_itmCutToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZPacketBuilder::OnCutTextClick);
			// 
			// m_itmCopyToolStripMenuItem
			// 
			this->m_itmCopyToolStripMenuItem->Name = L"m_itmCopyToolStripMenuItem";
			this->m_itmCopyToolStripMenuItem->Size = System::Drawing::Size(119, 22);
			this->m_itmCopyToolStripMenuItem->Text = L"Copy";
			this->m_itmCopyToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZPacketBuilder::OnCopyTextClick);
			// 
			// m_itmPasteToolStripMenuItem
			// 
			this->m_itmPasteToolStripMenuItem->Name = L"m_itmPasteToolStripMenuItem";
			this->m_itmPasteToolStripMenuItem->Size = System::Drawing::Size(119, 22);
			this->m_itmPasteToolStripMenuItem->Text = L"Paste";
			this->m_itmPasteToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZPacketBuilder::OnPasteTextClick);
			// 
			// m_tbpStream
			// 
			this->m_tbpStream->BackColor = System::Drawing::Color::White;
			this->m_tbpStream->Controls->Add(this->m_txtStream);
			this->m_tbpStream->ImageIndex = 1;
			this->m_tbpStream->Location = System::Drawing::Point(4, 23);
			this->m_tbpStream->Margin = System::Windows::Forms::Padding(0);
			this->m_tbpStream->Name = L"m_tbpStream";
			this->m_tbpStream->Padding = System::Windows::Forms::Padding(2);
			this->m_tbpStream->Size = System::Drawing::Size(482, 377);
			this->m_tbpStream->TabIndex = 1;
			this->m_tbpStream->Text = L"Byte Code";
			this->m_tbpStream->ToolTipText = L"View the generated byte code for you custom packet";
			// 
			// m_txtStream
			// 
			this->m_txtStream->BackColor = System::Drawing::SystemColors::Window;
			this->m_txtStream->Dock = System::Windows::Forms::DockStyle::Fill;
			this->m_txtStream->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->m_txtStream->Location = System::Drawing::Point(2, 2);
			this->m_txtStream->Margin = System::Windows::Forms::Padding(0);
			this->m_txtStream->MaxLength = 0;
			this->m_txtStream->Multiline = true;
			this->m_txtStream->Name = L"m_txtStream";
			this->m_txtStream->ReadOnly = true;
			this->m_txtStream->Size = System::Drawing::Size(478, 373);
			this->m_txtStream->TabIndex = 1;
			// 
			// m_lstTabImages
			// 
			this->m_lstTabImages->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"m_lstTabImages.ImageStream")));
			this->m_lstTabImages->TransparentColor = System::Drawing::Color::Transparent;
			this->m_lstTabImages->Images->SetKeyName(0, L"brush.png");
			this->m_lstTabImages->Images->SetKeyName(1, L"save.png");
			// 
			// m_btnSend
			// 
			this->m_btnSend->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->m_btnSend->Enabled = false;
			this->m_btnSend->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_btnSend.Image")));
			this->m_btnSend->Location = System::Drawing::Point(418, 3);
			this->m_btnSend->Margin = System::Windows::Forms::Padding(0);
			this->m_btnSend->Name = L"m_btnSend";
			this->m_btnSend->Size = System::Drawing::Size(70, 25);
			this->m_btnSend->TabIndex = 0;
			this->m_btnSend->TabStop = false;
			this->m_btnSend->Text = L"Send";
			this->m_btnSend->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->m_ttpToolTip->SetToolTip(this->m_btnSend, L"Send this packet to the MapleStory game client");
			this->m_btnSend->UseVisualStyleBackColor = true;
			this->m_btnSend->Click += gcnew System::EventHandler(this, &ZPacketBuilder::OnSendClick);
			// 
			// m_btnCopy
			// 
			this->m_btnCopy->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->m_btnCopy->Enabled = false;
			this->m_btnCopy->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_btnCopy.Image")));
			this->m_btnCopy->Location = System::Drawing::Point(343, 3);
			this->m_btnCopy->Margin = System::Windows::Forms::Padding(0);
			this->m_btnCopy->Name = L"m_btnCopy";
			this->m_btnCopy->Size = System::Drawing::Size(75, 25);
			this->m_btnCopy->TabIndex = 0;
			this->m_btnCopy->TabStop = false;
			this->m_btnCopy->Text = L"Copy";
			this->m_btnCopy->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->m_ttpToolTip->SetToolTip(this->m_btnCopy, L"Copy the packet byte code to the input field");
			this->m_btnCopy->UseVisualStyleBackColor = true;
			this->m_btnCopy->Click += gcnew System::EventHandler(this, &ZPacketBuilder::OnCopyClick);
			// 
			// m_btnClear
			// 
			this->m_btnClear->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->m_btnClear->Enabled = false;
			this->m_btnClear->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_btnClear.Image")));
			this->m_btnClear->Location = System::Drawing::Point(268, 3);
			this->m_btnClear->Margin = System::Windows::Forms::Padding(0);
			this->m_btnClear->Name = L"m_btnClear";
			this->m_btnClear->Size = System::Drawing::Size(75, 25);
			this->m_btnClear->TabIndex = 0;
			this->m_btnClear->TabStop = false;
			this->m_btnClear->Text = L"Clear";
			this->m_btnClear->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->m_ttpToolTip->SetToolTip(this->m_btnClear, L"Clear the builder of all data");
			this->m_btnClear->UseVisualStyleBackColor = true;
			this->m_btnClear->Click += gcnew System::EventHandler(this, &ZPacketBuilder::OnClearClick);
			// 
			// m_lblText
			// 
			this->m_lblText->ForeColor = System::Drawing::Color::Gray;
			this->m_lblText->Location = System::Drawing::Point(5, 3);
			this->m_lblText->Margin = System::Windows::Forms::Padding(0);
			this->m_lblText->Name = L"m_lblText";
			this->m_lblText->Padding = System::Windows::Forms::Padding(5, 0, 0, 0);
			this->m_lblText->Size = System::Drawing::Size(260, 25);
			this->m_lblText->TabIndex = 0;
			this->m_lblText->Text = L"Create your packet in literal format above.";
			this->m_lblText->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// ZPacketBuilder
			// 
			this->ClientSize = System::Drawing::Size(498, 448);
			this->Controls->Add(this->m_splContainer);
			this->Font = (gcnew System::Drawing::Font(L"Verdana", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->MinimumSize = System::Drawing::Size(506, 475);
			this->Name = L"ZPacketBuilder";
			this->Padding = System::Windows::Forms::Padding(4);
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->Text = L"Z - Packet Builder";
			this->m_splContainer->Panel1->ResumeLayout(false);
			this->m_splContainer->Panel2->ResumeLayout(false);
			this->m_splContainer->ResumeLayout(false);
			this->m_tbInput->ResumeLayout(false);
			this->m_tbpPacket->ResumeLayout(false);
			this->m_tbpPacket->PerformLayout();
			this->m_ctxPacketMenu->ResumeLayout(false);
			this->m_tbpStream->ResumeLayout(false);
			this->m_tbpStream->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion



};
}

#endif /* __ZPacketBuilder_h__ */
