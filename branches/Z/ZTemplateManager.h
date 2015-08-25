#ifndef __ZTemplateManager_h__
#define __ZTemplateManager_h__

#pragma once

#include "Z.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Drawing;
using namespace System::Windows::Forms;

namespace Z
{
	ref class ZTemplate;

	ref class ZTemplateCollection;

	ref class ZTemplateManager : public System::Windows::Forms::Form
	{
		delegate void CreateNewCaller ( String^ cmdBytes, String^ rawBytes );

	private:
		static String^ RecvFlag     = gcnew String(L"r");
		static String^ SendFlag     = gcnew String(L"s");
		static String^ NoFormatFlag = gcnew String(L"n");
		static String^ ColorizeFlag = gcnew String(L"f");

	private:
		ZTemplateCollection^ m_Collection;

	public:
		/* Constructor */
		ZTemplateManager ( void )
		{
			InitializeComponent();
			Initialize();
		}

		/* Dispose */
		~ZTemplateManager ( void )
		{
			if ( components )
				delete components;
		}
	
	private:
		void Initialize ( void );

	public:
		/* Import template definitions from a file */
		void ImportFile ( String^ fileName );
		/* Export settings to a file */
		void ExportFile ( String^ fileName );
		
	public:
		/* Get template for the specified bytes */
		ZTemplate^ GetTemplate ( String^ rawBytes, ::DWORD dwStream );
		/* Create a new template from a foreign window */
		void CreateTemplate ( String^ rawBytes );

	private: System::Windows::Forms::MenuStrip^  m_mbrStrip;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmTemplatesToolStripMenuItem;
	public: 

	private: System::Windows::Forms::ToolStripMenuItem^  m_itmImportToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  m_sprTemplatesMenuToolStripSeparator1;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmExportToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmExportAsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  m_itmTemplatesMenuToolStripSeparator2;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmClearToolStripMenuItem;
	private: System::Windows::Forms::SplitContainer^  m_splContainer;
	private: System::Windows::Forms::GroupBox^  m_ctrContainer;


	private: System::Windows::Forms::CheckBox^  m_chxSend;

	private: System::Windows::Forms::CheckBox^  m_chxRecv;
	private: System::Windows::Forms::CheckBox^  m_chxColorize;



	private: System::Windows::Forms::CheckBox^  m_chxNoFormat;

	private: System::Windows::Forms::Label^  m_lblAlias;
	private: System::Windows::Forms::Label^  m_lblPattern;
	private: System::Windows::Forms::TextBox^  m_txtPattern;
	private: System::Windows::Forms::Label^  m_lblTextColor;
	private: System::Windows::Forms::Label^  m_lblBackground;






	private: System::Windows::Forms::Label^  m_btnForeColor;


	private: System::Windows::Forms::Label^  m_btnBackColor;
	private: System::Windows::Forms::TextBox^  m_txtAlias;


	private: System::Windows::Forms::ListView^  m_lstTemplateList;


	private: System::Windows::Forms::ColumnHeader^  m_hdrName;
	private: System::Windows::Forms::ColumnHeader^  m_hdrFlags;
	private: System::Windows::Forms::ColumnHeader^  m_hdrBackColor;
	private: System::Windows::Forms::ColumnHeader^  m_hdrForeColor;
	private: System::Windows::Forms::ColumnHeader^  m_hdrPattern;
	private: System::Windows::Forms::ContextMenuStrip^  m_ctxItemMenu;


	private: System::Windows::Forms::ToolStripSeparator^  m_sprItemMenuToolStripSeparator1;



	private: System::Windows::Forms::ToolStripMenuItem^  m_itmRecvToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmSendToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmNoFormatToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  m_itmColorizeToolStripMenuItem;







	private: System::Windows::Forms::ToolStripMenuItem^  m_itmSetForegroundColorToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmSetBackgroundColorToolStripMenuItem;


	private: System::Windows::Forms::Button^  m_btnCreate;
	private: System::Windows::Forms::ToolTip^  m_ttpToolTip;

#pragma region Windows Form Designer generated code
	private:
		System::ComponentModel::IContainer^ components;

		void InitializeComponent ( void )
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ZTemplateManager::typeid));
			this->m_mbrStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->m_itmTemplatesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmImportToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_sprTemplatesMenuToolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->m_itmExportToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmExportAsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmTemplatesMenuToolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->m_itmClearToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_splContainer = (gcnew System::Windows::Forms::SplitContainer());
			this->m_ctrContainer = (gcnew System::Windows::Forms::GroupBox());
			this->m_btnCreate = (gcnew System::Windows::Forms::Button());
			this->m_chxSend = (gcnew System::Windows::Forms::CheckBox());
			this->m_chxRecv = (gcnew System::Windows::Forms::CheckBox());
			this->m_chxColorize = (gcnew System::Windows::Forms::CheckBox());
			this->m_chxNoFormat = (gcnew System::Windows::Forms::CheckBox());
			this->m_lblAlias = (gcnew System::Windows::Forms::Label());
			this->m_lblPattern = (gcnew System::Windows::Forms::Label());
			this->m_txtPattern = (gcnew System::Windows::Forms::TextBox());
			this->m_lblTextColor = (gcnew System::Windows::Forms::Label());
			this->m_lblBackground = (gcnew System::Windows::Forms::Label());
			this->m_btnForeColor = (gcnew System::Windows::Forms::Label());
			this->m_btnBackColor = (gcnew System::Windows::Forms::Label());
			this->m_txtAlias = (gcnew System::Windows::Forms::TextBox());
			this->m_lstTemplateList = (gcnew System::Windows::Forms::ListView());
			this->m_hdrName = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_hdrFlags = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_hdrForeColor = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_hdrBackColor = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_hdrPattern = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_ctxItemMenu = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->m_itmRecvToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmSendToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmNoFormatToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmColorizeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_sprItemMenuToolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->m_itmSetForegroundColorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmSetBackgroundColorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_ttpToolTip = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->m_mbrStrip->SuspendLayout();
			this->m_splContainer->Panel1->SuspendLayout();
			this->m_splContainer->Panel2->SuspendLayout();
			this->m_splContainer->SuspendLayout();
			this->m_ctrContainer->SuspendLayout();
			this->m_ctxItemMenu->SuspendLayout();
			this->SuspendLayout();
			// 
			// m_mbrStrip
			// 
			this->m_mbrStrip->BackColor = System::Drawing::SystemColors::Control;
			this->m_mbrStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->m_itmTemplatesToolStripMenuItem});
			this->m_mbrStrip->Location = System::Drawing::Point(0, 0);
			this->m_mbrStrip->Name = L"m_mbrStrip";
			this->m_mbrStrip->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
			this->m_mbrStrip->Size = System::Drawing::Size(500, 24);
			this->m_mbrStrip->TabIndex = 0;
			// 
			// m_itmTemplatesToolStripMenuItem
			// 
			this->m_itmTemplatesToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {this->m_itmImportToolStripMenuItem, 
				this->m_sprTemplatesMenuToolStripSeparator1, this->m_itmExportToolStripMenuItem, this->m_itmExportAsToolStripMenuItem, this->m_itmTemplatesMenuToolStripSeparator2, 
				this->m_itmClearToolStripMenuItem});
			this->m_itmTemplatesToolStripMenuItem->Name = L"m_itmTemplatesToolStripMenuItem";
			this->m_itmTemplatesToolStripMenuItem->Size = System::Drawing::Size(78, 20);
			this->m_itmTemplatesToolStripMenuItem->Text = L"&Templates";
			// 
			// m_itmImportToolStripMenuItem
			// 
			this->m_itmImportToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_itmImportToolStripMenuItem.Image")));
			this->m_itmImportToolStripMenuItem->Name = L"m_itmImportToolStripMenuItem";
			this->m_itmImportToolStripMenuItem->Size = System::Drawing::Size(167, 22);
			this->m_itmImportToolStripMenuItem->Text = L"Import";
			this->m_itmImportToolStripMenuItem->ToolTipText = L"Import template definitions from a file";
			this->m_itmImportToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZTemplateManager::OnImportClick);
			// 
			// m_sprTemplatesMenuToolStripSeparator1
			// 
			this->m_sprTemplatesMenuToolStripSeparator1->Name = L"m_sprTemplatesMenuToolStripSeparator1";
			this->m_sprTemplatesMenuToolStripSeparator1->Size = System::Drawing::Size(164, 6);
			// 
			// m_itmExportToolStripMenuItem
			// 
			this->m_itmExportToolStripMenuItem->Enabled = false;
			this->m_itmExportToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_itmExportToolStripMenuItem.Image")));
			this->m_itmExportToolStripMenuItem->Name = L"m_itmExportToolStripMenuItem";
			this->m_itmExportToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::S));
			this->m_itmExportToolStripMenuItem->Size = System::Drawing::Size(167, 22);
			this->m_itmExportToolStripMenuItem->Text = L"Export";
			this->m_itmExportToolStripMenuItem->ToolTipText = L"Export template definitions to a file";
			this->m_itmExportToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZTemplateManager::OnExportClick);
			// 
			// m_itmExportAsToolStripMenuItem
			// 
			this->m_itmExportAsToolStripMenuItem->Enabled = false;
			this->m_itmExportAsToolStripMenuItem->Name = L"m_itmExportAsToolStripMenuItem";
			this->m_itmExportAsToolStripMenuItem->Size = System::Drawing::Size(167, 22);
			this->m_itmExportAsToolStripMenuItem->Text = L"Export As";
			this->m_itmExportAsToolStripMenuItem->ToolTipText = L"Export template definitions to a file";
			this->m_itmExportAsToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZTemplateManager::OnExportAsClick);
			// 
			// m_itmTemplatesMenuToolStripSeparator2
			// 
			this->m_itmTemplatesMenuToolStripSeparator2->Name = L"m_itmTemplatesMenuToolStripSeparator2";
			this->m_itmTemplatesMenuToolStripSeparator2->Size = System::Drawing::Size(164, 6);
			// 
			// m_itmClearToolStripMenuItem
			// 
			this->m_itmClearToolStripMenuItem->Enabled = false;
			this->m_itmClearToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_itmClearToolStripMenuItem.Image")));
			this->m_itmClearToolStripMenuItem->Name = L"m_itmClearToolStripMenuItem";
			this->m_itmClearToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::U));
			this->m_itmClearToolStripMenuItem->Size = System::Drawing::Size(167, 22);
			this->m_itmClearToolStripMenuItem->Text = L"Clear";
			this->m_itmClearToolStripMenuItem->ToolTipText = L"Remove all all template definitions";
			this->m_itmClearToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZTemplateManager::OnClearClick);
			// 
			// m_splContainer
			// 
			this->m_splContainer->Dock = System::Windows::Forms::DockStyle::Fill;
			this->m_splContainer->FixedPanel = System::Windows::Forms::FixedPanel::Panel1;
			this->m_splContainer->IsSplitterFixed = true;
			this->m_splContainer->Location = System::Drawing::Point(0, 24);
			this->m_splContainer->Margin = System::Windows::Forms::Padding(0);
			this->m_splContainer->Name = L"m_splContainer";
			this->m_splContainer->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// m_splContainer.Panel1
			// 
			this->m_splContainer->Panel1->Controls->Add(this->m_ctrContainer);
			this->m_splContainer->Panel1->Padding = System::Windows::Forms::Padding(4);
			// 
			// m_splContainer.Panel2
			// 
			this->m_splContainer->Panel2->Controls->Add(this->m_lstTemplateList);
			this->m_splContainer->Panel2->Padding = System::Windows::Forms::Padding(4);
			this->m_splContainer->Size = System::Drawing::Size(500, 426);
			this->m_splContainer->SplitterDistance = 78;
			this->m_splContainer->SplitterWidth = 1;
			this->m_splContainer->TabIndex = 0;
			this->m_splContainer->TabStop = false;
			// 
			// m_ctrContainer
			// 
			this->m_ctrContainer->Controls->Add(this->m_btnCreate);
			this->m_ctrContainer->Controls->Add(this->m_chxSend);
			this->m_ctrContainer->Controls->Add(this->m_chxRecv);
			this->m_ctrContainer->Controls->Add(this->m_chxColorize);
			this->m_ctrContainer->Controls->Add(this->m_chxNoFormat);
			this->m_ctrContainer->Controls->Add(this->m_lblAlias);
			this->m_ctrContainer->Controls->Add(this->m_lblPattern);
			this->m_ctrContainer->Controls->Add(this->m_txtPattern);
			this->m_ctrContainer->Controls->Add(this->m_lblTextColor);
			this->m_ctrContainer->Controls->Add(this->m_lblBackground);
			this->m_ctrContainer->Controls->Add(this->m_btnForeColor);
			this->m_ctrContainer->Controls->Add(this->m_btnBackColor);
			this->m_ctrContainer->Controls->Add(this->m_txtAlias);
			this->m_ctrContainer->Dock = System::Windows::Forms::DockStyle::Fill;
			this->m_ctrContainer->Location = System::Drawing::Point(4, 4);
			this->m_ctrContainer->Margin = System::Windows::Forms::Padding(0);
			this->m_ctrContainer->Name = L"m_ctrContainer";
			this->m_ctrContainer->Padding = System::Windows::Forms::Padding(4);
			this->m_ctrContainer->Size = System::Drawing::Size(492, 70);
			this->m_ctrContainer->TabIndex = 0;
			this->m_ctrContainer->TabStop = false;
			this->m_ctrContainer->Text = L"Create A New Template";
			// 
			// m_btnCreate
			// 
			this->m_btnCreate->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->m_btnCreate->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_btnCreate.Image")));
			this->m_btnCreate->Location = System::Drawing::Point(413, 40);
			this->m_btnCreate->Margin = System::Windows::Forms::Padding(0);
			this->m_btnCreate->Name = L"m_btnCreate";
			this->m_btnCreate->Size = System::Drawing::Size(75, 25);
			this->m_btnCreate->TabIndex = 3;
			this->m_btnCreate->Text = L"Create";
			this->m_btnCreate->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->m_ttpToolTip->SetToolTip(this->m_btnCreate, L"Create a template");
			this->m_btnCreate->UseVisualStyleBackColor = true;
			this->m_btnCreate->Click += gcnew System::EventHandler(this, &ZTemplateManager::OnCreateClick);
			// 
			// m_chxSend
			// 
			this->m_chxSend->Checked = true;
			this->m_chxSend->CheckState = System::Windows::Forms::CheckState::Checked;
			this->m_chxSend->Cursor = System::Windows::Forms::Cursors::Default;
			this->m_chxSend->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->m_chxSend->Location = System::Drawing::Point(60, 15);
			this->m_chxSend->Margin = System::Windows::Forms::Padding(0);
			this->m_chxSend->Name = L"m_chxSend";
			this->m_chxSend->Size = System::Drawing::Size(60, 21);
			this->m_chxSend->TabIndex = 0;
			this->m_chxSend->TabStop = false;
			this->m_chxSend->Text = L"Send";
			this->m_ttpToolTip->SetToolTip(this->m_chxSend, L"Apply this template to packets sent to the server");
			this->m_chxSend->UseVisualStyleBackColor = true;
			// 
			// m_chxRecv
			// 
			this->m_chxRecv->Checked = true;
			this->m_chxRecv->CheckState = System::Windows::Forms::CheckState::Checked;
			this->m_chxRecv->Cursor = System::Windows::Forms::Cursors::Default;
			this->m_chxRecv->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->m_chxRecv->Location = System::Drawing::Point(5, 15);
			this->m_chxRecv->Margin = System::Windows::Forms::Padding(0);
			this->m_chxRecv->Name = L"m_chxRecv";
			this->m_chxRecv->Size = System::Drawing::Size(60, 21);
			this->m_chxRecv->TabIndex = 0;
			this->m_chxRecv->TabStop = false;
			this->m_chxRecv->Text = L"Recv";
			this->m_ttpToolTip->SetToolTip(this->m_chxRecv, L"Apply this template to packets received from the server");
			this->m_chxRecv->UseVisualStyleBackColor = true;
			// 
			// m_chxColorize
			// 
			this->m_chxColorize->Cursor = System::Windows::Forms::Cursors::Default;
			this->m_chxColorize->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->m_chxColorize->Location = System::Drawing::Point(120, 43);
			this->m_chxColorize->Margin = System::Windows::Forms::Padding(0);
			this->m_chxColorize->Name = L"m_chxColorize";
			this->m_chxColorize->Size = System::Drawing::Size(115, 21);
			this->m_chxColorize->TabIndex = 0;
			this->m_chxColorize->TabStop = false;
			this->m_chxColorize->Text = L"Color All Fields";
			this->m_ttpToolTip->SetToolTip(this->m_chxColorize, L"Color all fields when display packet data");
			this->m_chxColorize->UseVisualStyleBackColor = true;
			// 
			// m_chxNoFormat
			// 
			this->m_chxNoFormat->Cursor = System::Windows::Forms::Cursors::Default;
			this->m_chxNoFormat->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->m_chxNoFormat->Location = System::Drawing::Point(5, 43);
			this->m_chxNoFormat->Margin = System::Windows::Forms::Padding(0);
			this->m_chxNoFormat->Name = L"m_chxNoFormat";
			this->m_chxNoFormat->Size = System::Drawing::Size(110, 21);
			this->m_chxNoFormat->TabIndex = 0;
			this->m_chxNoFormat->TabStop = false;
			this->m_chxNoFormat->Text = L"Do Not Format";
			this->m_ttpToolTip->SetToolTip(this->m_chxNoFormat, L"Do not parse packet byte code");
			this->m_chxNoFormat->UseVisualStyleBackColor = true;
			// 
			// m_lblAlias
			// 
			this->m_lblAlias->Location = System::Drawing::Point(115, 15);
			this->m_lblAlias->Margin = System::Windows::Forms::Padding(0);
			this->m_lblAlias->Name = L"m_lblAlias";
			this->m_lblAlias->Padding = System::Windows::Forms::Padding(2, 0, 0, 0);
			this->m_lblAlias->Size = System::Drawing::Size(45, 21);
			this->m_lblAlias->TabIndex = 8;
			this->m_lblAlias->Text = L"Alias";
			this->m_lblAlias->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// m_lblPattern
			// 
			this->m_lblPattern->Location = System::Drawing::Point(275, 15);
			this->m_lblPattern->Margin = System::Windows::Forms::Padding(0);
			this->m_lblPattern->Name = L"m_lblPattern";
			this->m_lblPattern->Padding = System::Windows::Forms::Padding(2, 0, 0, 0);
			this->m_lblPattern->Size = System::Drawing::Size(50, 21);
			this->m_lblPattern->TabIndex = 7;
			this->m_lblPattern->Text = L"Pattern";
			this->m_lblPattern->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// m_txtPattern
			// 
			this->m_txtPattern->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->m_txtPattern->Location = System::Drawing::Point(325, 15);
			this->m_txtPattern->Margin = System::Windows::Forms::Padding(0);
			this->m_txtPattern->MaxLength = 128;
			this->m_txtPattern->Name = L"m_txtPattern";
			this->m_txtPattern->Size = System::Drawing::Size(163, 21);
			this->m_txtPattern->TabIndex = 2;
			this->m_txtPattern->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->m_ttpToolTip->SetToolTip(this->m_txtPattern, L"The Z pattern used to match this pattern");
			this->m_txtPattern->Leave += gcnew System::EventHandler(this, &ZTemplateManager::OnPatternLeave);
			// 
			// m_lblTextColor
			// 
			this->m_lblTextColor->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->m_lblTextColor->Location = System::Drawing::Point(240, 43);
			this->m_lblTextColor->Margin = System::Windows::Forms::Padding(0);
			this->m_lblTextColor->Name = L"m_lblTextColor";
			this->m_lblTextColor->Size = System::Drawing::Size(40, 21);
			this->m_lblTextColor->TabIndex = 5;
			this->m_lblTextColor->Text = L"Text";
			this->m_lblTextColor->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// m_lblBackground
			// 
			this->m_lblBackground->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->m_lblBackground->Location = System::Drawing::Point(308, 43);
			this->m_lblBackground->Margin = System::Windows::Forms::Padding(0);
			this->m_lblBackground->Name = L"m_lblBackground";
			this->m_lblBackground->Size = System::Drawing::Size(75, 21);
			this->m_lblBackground->TabIndex = 4;
			this->m_lblBackground->Text = L"Background";
			this->m_lblBackground->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// m_btnForeColor
			// 
			this->m_btnForeColor->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->m_btnForeColor->BackColor = System::Drawing::SystemColors::WindowText;
			this->m_btnForeColor->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->m_btnForeColor->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->m_btnForeColor->Location = System::Drawing::Point(283, 43);
			this->m_btnForeColor->Margin = System::Windows::Forms::Padding(0);
			this->m_btnForeColor->Name = L"m_btnForeColor";
			this->m_btnForeColor->Size = System::Drawing::Size(21, 21);
			this->m_btnForeColor->TabIndex = 0;
			this->m_btnForeColor->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->m_ttpToolTip->SetToolTip(this->m_btnForeColor, L"Click here to set the text color for displaying packet data");
			this->m_btnForeColor->Click += gcnew System::EventHandler(this, &ZTemplateManager::OnForeColorClick);
			// 
			// m_btnBackColor
			// 
			this->m_btnBackColor->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->m_btnBackColor->BackColor = System::Drawing::SystemColors::Window;
			this->m_btnBackColor->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->m_btnBackColor->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->m_btnBackColor->Location = System::Drawing::Point(383, 43);
			this->m_btnBackColor->Margin = System::Windows::Forms::Padding(0);
			this->m_btnBackColor->Name = L"m_btnBackColor";
			this->m_btnBackColor->Size = System::Drawing::Size(21, 21);
			this->m_btnBackColor->TabIndex = 0;
			this->m_btnBackColor->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->m_ttpToolTip->SetToolTip(this->m_btnBackColor, L"Set the background color for displaying packet data");
			this->m_btnBackColor->Click += gcnew System::EventHandler(this, &ZTemplateManager::OnBackColorClick);
			// 
			// m_txtAlias
			// 
			this->m_txtAlias->Location = System::Drawing::Point(160, 15);
			this->m_txtAlias->Margin = System::Windows::Forms::Padding(0);
			this->m_txtAlias->MaxLength = 128;
			this->m_txtAlias->Name = L"m_txtAlias";
			this->m_txtAlias->Size = System::Drawing::Size(110, 21);
			this->m_txtAlias->TabIndex = 1;
			this->m_txtAlias->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->m_ttpToolTip->SetToolTip(this->m_txtAlias, L"Set the alias used to identify this packet ([_0-9a-zA-Z] only)");
			this->m_txtAlias->Leave += gcnew System::EventHandler(this, &ZTemplateManager::OnAliasLeave);
			// 
			// m_lstTemplateList
			// 
			this->m_lstTemplateList->CheckBoxes = true;
			this->m_lstTemplateList->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(5) {this->m_hdrName, 
				this->m_hdrFlags, this->m_hdrForeColor, this->m_hdrBackColor, this->m_hdrPattern});
			this->m_lstTemplateList->ContextMenuStrip = this->m_ctxItemMenu;
			this->m_lstTemplateList->Dock = System::Windows::Forms::DockStyle::Fill;
			this->m_lstTemplateList->FullRowSelect = true;
			this->m_lstTemplateList->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->m_lstTemplateList->Location = System::Drawing::Point(4, 4);
			this->m_lstTemplateList->Margin = System::Windows::Forms::Padding(0);
			this->m_lstTemplateList->Name = L"m_lstTemplateList";
			this->m_lstTemplateList->Size = System::Drawing::Size(492, 339);
			this->m_lstTemplateList->TabIndex = 0;
			this->m_lstTemplateList->UseCompatibleStateImageBehavior = false;
			this->m_lstTemplateList->View = System::Windows::Forms::View::Details;
			this->m_lstTemplateList->ItemChecked += gcnew System::Windows::Forms::ItemCheckedEventHandler(this, &ZTemplateManager::OnTemplateListItemChecked);
			this->m_lstTemplateList->ItemMouseHover += gcnew System::Windows::Forms::ListViewItemMouseHoverEventHandler(this, &ZTemplateManager::OnTemplateListItemMouseHover);
			// 
			// m_hdrName
			// 
			this->m_hdrName->Text = L"Alias";
			this->m_hdrName->Width = 80;
			// 
			// m_hdrFlags
			// 
			this->m_hdrFlags->Text = L"Flags";
			this->m_hdrFlags->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->m_hdrFlags->Width = 75;
			// 
			// m_hdrForeColor
			// 
			this->m_hdrForeColor->Text = L"Foreground";
			this->m_hdrForeColor->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->m_hdrForeColor->Width = 90;
			// 
			// m_hdrBackColor
			// 
			this->m_hdrBackColor->Text = L"Background";
			this->m_hdrBackColor->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->m_hdrBackColor->Width = 90;
			// 
			// m_hdrPattern
			// 
			this->m_hdrPattern->Text = L"Pattern";
			this->m_hdrPattern->Width = 134;
			// 
			// m_ctxItemMenu
			// 
			this->m_ctxItemMenu->BackColor = System::Drawing::SystemColors::Menu;
			this->m_ctxItemMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {this->m_itmRecvToolStripMenuItem, 
				this->m_itmSendToolStripMenuItem, this->m_itmNoFormatToolStripMenuItem, this->m_itmColorizeToolStripMenuItem, this->m_sprItemMenuToolStripSeparator1, 
				this->m_itmSetForegroundColorToolStripMenuItem, this->m_itmSetBackgroundColorToolStripMenuItem});
			this->m_ctxItemMenu->Name = L"m_ctxItemMenu";
			this->m_ctxItemMenu->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
			this->m_ctxItemMenu->Size = System::Drawing::Size(240, 142);
			this->m_ctxItemMenu->Opening += gcnew System::ComponentModel::CancelEventHandler(this, &ZTemplateManager::OnItemMenuOpening);
			// 
			// m_itmRecvToolStripMenuItem
			// 
			this->m_itmRecvToolStripMenuItem->CheckOnClick = true;
			this->m_itmRecvToolStripMenuItem->Name = L"m_itmRecvToolStripMenuItem";
			this->m_itmRecvToolStripMenuItem->Size = System::Drawing::Size(239, 22);
			this->m_itmRecvToolStripMenuItem->Text = L"Apply To Received Packets";
			this->m_itmRecvToolStripMenuItem->ToolTipText = L"Apply this template to received packets";
			this->m_itmRecvToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZTemplateManager::OnRecvClick);
			// 
			// m_itmSendToolStripMenuItem
			// 
			this->m_itmSendToolStripMenuItem->CheckOnClick = true;
			this->m_itmSendToolStripMenuItem->Name = L"m_itmSendToolStripMenuItem";
			this->m_itmSendToolStripMenuItem->Size = System::Drawing::Size(239, 22);
			this->m_itmSendToolStripMenuItem->Text = L"Apply To Sent Packets";
			this->m_itmSendToolStripMenuItem->ToolTipText = L"Apply this template to sent packets";
			this->m_itmSendToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZTemplateManager::OnSendClick);
			// 
			// m_itmNoFormatToolStripMenuItem
			// 
			this->m_itmNoFormatToolStripMenuItem->CheckOnClick = true;
			this->m_itmNoFormatToolStripMenuItem->Name = L"m_itmNoFormatToolStripMenuItem";
			this->m_itmNoFormatToolStripMenuItem->Size = System::Drawing::Size(239, 22);
			this->m_itmNoFormatToolStripMenuItem->Text = L"Do Not Format Byte Code";
			this->m_itmNoFormatToolStripMenuItem->ToolTipText = L"Do not format packet byte code";
			this->m_itmNoFormatToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZTemplateManager::OnNoFormatClick);
			// 
			// m_itmColorizeToolStripMenuItem
			// 
			this->m_itmColorizeToolStripMenuItem->CheckOnClick = true;
			this->m_itmColorizeToolStripMenuItem->Name = L"m_itmColorizeToolStripMenuItem";
			this->m_itmColorizeToolStripMenuItem->Size = System::Drawing::Size(239, 22);
			this->m_itmColorizeToolStripMenuItem->Text = L"Color All Fields";
			this->m_itmColorizeToolStripMenuItem->ToolTipText = L"Apply template color to all fields";
			this->m_itmColorizeToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZTemplateManager::OnColorizeClick);
			// 
			// m_sprItemMenuToolStripSeparator1
			// 
			this->m_sprItemMenuToolStripSeparator1->Name = L"m_sprItemMenuToolStripSeparator1";
			this->m_sprItemMenuToolStripSeparator1->Size = System::Drawing::Size(236, 6);
			// 
			// m_itmSetForegroundColorToolStripMenuItem
			// 
			this->m_itmSetForegroundColorToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_itmSetForegroundColorToolStripMenuItem.Image")));
			this->m_itmSetForegroundColorToolStripMenuItem->Name = L"m_itmSetForegroundColorToolStripMenuItem";
			this->m_itmSetForegroundColorToolStripMenuItem->Size = System::Drawing::Size(239, 22);
			this->m_itmSetForegroundColorToolStripMenuItem->Text = L"Set Text Color";
			this->m_itmSetForegroundColorToolStripMenuItem->ToolTipText = L"Set the background color for this template";
			this->m_itmSetForegroundColorToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZTemplateManager::OnSetForeColorClick);
			// 
			// m_itmSetBackgroundColorToolStripMenuItem
			// 
			this->m_itmSetBackgroundColorToolStripMenuItem->Name = L"m_itmSetBackgroundColorToolStripMenuItem";
			this->m_itmSetBackgroundColorToolStripMenuItem->Size = System::Drawing::Size(239, 22);
			this->m_itmSetBackgroundColorToolStripMenuItem->Text = L"Set Background Color";
			this->m_itmSetBackgroundColorToolStripMenuItem->ToolTipText = L"Set the background color for this template";
			this->m_itmSetBackgroundColorToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZTemplateManager::OnSetBackColorClick);
			// 
			// m_ttpToolTip
			// 
			this->m_ttpToolTip->AutomaticDelay = 250;
			// 
			// ZTemplateManager
			// 
			this->ClientSize = System::Drawing::Size(500, 450);
			this->Controls->Add(this->m_splContainer);
			this->Controls->Add(this->m_mbrStrip);
			this->Font = (gcnew System::Drawing::Font(L"Verdana", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->MainMenuStrip = this->m_mbrStrip;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->MinimumSize = System::Drawing::Size(506, 475);
			this->Name = L"ZTemplateManager";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->Text = L"Z - Template Manager";
			this->m_mbrStrip->ResumeLayout(false);
			this->m_mbrStrip->PerformLayout();
			this->m_splContainer->Panel1->ResumeLayout(false);
			this->m_splContainer->Panel2->ResumeLayout(false);
			this->m_splContainer->ResumeLayout(false);
			this->m_ctrContainer->ResumeLayout(false);
			this->m_ctrContainer->PerformLayout();
			this->m_ctxItemMenu->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

void OnImportClick ( Object^  sender, EventArgs^  e );
		 
void OnExportClick ( Object^  sender, EventArgs^  e );
		 
void OnExportAsClick ( Object^  sender, EventArgs^  e );
		 
void OnClearClick ( Object^  sender, EventArgs^  e );
		 
void OnAliasLeave ( Object^  sender, EventArgs^  e );
		 
void OnPatternLeave ( Object^  sender, EventArgs^  e );
		 
void OnForeColorClick ( Object^  sender, EventArgs^  e );
		 
void OnBackColorClick ( Object^  sender, EventArgs^  e );
		 
void OnCreateClick ( Object^  sender, EventArgs^  e );
		 
void OnTemplateListItemMouseHover ( Object^  sender, ListViewItemMouseHoverEventArgs^  e );
		 
void OnTemplateListItemChecked ( Object^  sender, ItemCheckedEventArgs^  e );
		 
void OnRecvClick ( Object^  sender, EventArgs^  e );
		 
void OnSendClick ( Object^  sender, EventArgs^  e );
		 
void OnNoFormatClick ( Object^  sender, EventArgs^  e );
		 
void OnColorizeClick ( Object^  sender, EventArgs^  e );
		 
void OnSetForeColorClick ( Object^  sender, EventArgs^  e );
		 
void OnSetBackColorClick ( Object^  sender, EventArgs^  e );
		 
void OnItemMenuOpening ( Object^  sender, CancelEventArgs^  e );
		 
};
}

#endif /* __ZTemplateManager_h__ */
