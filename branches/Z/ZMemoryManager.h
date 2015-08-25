#ifndef __ZMemoryManager_h__
#define __ZMemoryManager_h__

#pragma once

#include "Z.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::Text::RegularExpressions;

namespace Z
{
	ref class ZMemoryManager : public System::Windows::Forms::Form
	{
		delegate void OnTickCaller ( Object^ sender, EventArgs^ e );

		/* Invalid pointer name pattern: [^_0-9a-zA-Z] */
		static Regex^ InvalidCharsExpr = gcnew Regex(L"[^_0-9a-zA-Z]",
			RegexOptions::Compiled | RegexOptions::CultureInvariant | RegexOptions::IgnoreCase);
		/* Valid base and offset pattern: ^((?:@[_0-9a-zA-Z]+)|(?:(?:[0-9a-fA-F]{2})+)|(?:[\-\+]?\d+))$ */
		static Regex^ IntegerValueExpr = gcnew Regex(L"^((?:@[_0-9a-zA-Z]+)|(?:(?:[0-9a-fA-F]{2})+)|(?:[\\-\\+]?\\d+))$",
			RegexOptions::Compiled | RegexOptions::CultureInvariant | RegexOptions::IgnoreCase);
		/* Valid Array-of-bytes pattern: ^(?:(?<ptr>(?:[0-9a-fA-F]{2}|\?)+)(?<off>[\-\+]\d+)?)$  */
		static Regex^ ArrayOfBytesExpr = gcnew Regex(L"(?:(?<ptr>(?:[0-9a-fA-F]{2}|\\?)+)(?<off>[\\-\\+]\\d+)?)",
			RegexOptions::Compiled | RegexOptions::CultureInvariant | RegexOptions::IgnoreCase | RegexOptions::Singleline);
		/* Hexadecimal byte values */
		static Regex^ ByteValuesExpr = gcnew Regex(L"[0-9a-fA-F]{2}",
			RegexOptions::Compiled | RegexOptions::CultureInvariant | RegexOptions::IgnoreCase);
		/* Wildcard byte values */
		static Regex^ WildValuesExpr = gcnew Regex(L"\\?",
			RegexOptions::Compiled | RegexOptions::CultureInvariant | RegexOptions::IgnoreCase);

	public:
		/* Constructor */
		ZMemoryManager ( void )
		{
			InitializeComponent();

			this->m_lstTypeList->SelectedIndex = 0;
		}

		/* Dispose */
		~ZMemoryManager ( void )
		{
			if ( components )
				delete components;
		}

	public:
		/* Get the current value of a pointer in the tracker table */
		int GetValue ( String^ ptrName );

	private:
		::ULONG_PTR GetFieldValue ( String^ fieldNameOrValue );

	private:
		void OnImportClick ( Object^ sender, EventArgs^ e );
		
		void OnExportClick ( Object^ sender, EventArgs^ e );
		
		void OnExportAsClick ( Object^ sender, EventArgs^ e );
		
		void OnClearClick ( Object^ sender, EventArgs^ e );
		
		void OnNameLeave ( Object^ sender, EventArgs^ e );
		
		void OnTypeListSelectedIndexChanged ( Object^ sender, EventArgs^ e );
		
		void OnHexNumberCheckedChanged ( Object^ sender, EventArgs^ e );
		
		void OnValueLeave ( Object^ sender, EventArgs^ e );
		
		void OnArrayLeave ( Object^ sender, EventArgs^ e );
		
		void OnFindClick ( Object^ sender, EventArgs^ e );
		
		void OnTrackClick ( Object^ sender, EventArgs^ e );
		
		void OnPointerListItemMouseHover ( Object^ sender, ListViewItemMouseHoverEventArgs^ e );
		
		void OnPointerListItemSelectionChanged ( Object^ sender, ListViewItemSelectionChangedEventArgs^ e );

		void OnToolTipPopup ( Object^ sender, PopupEventArgs^ e );

		void OnTick ( Object^ sender, EventArgs^ e );


	private: System::Windows::Forms::MenuStrip^  m_mbrStrip;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmTablesToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmImportToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmExportToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmExportAsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmClearToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  m_itmTablesMenuToolStripSeparator1;

	private: System::Windows::Forms::ToolStripSeparator^  m_itmTablesMenuToolStripSeparator2;
	public: 







	private: System::Windows::Forms::SplitContainer^  m_splContainer;
	private: System::Windows::Forms::GroupBox^  m_ctrContainer;
	private: System::Windows::Forms::Button^  m_btnTrack;

	private: System::Windows::Forms::Button^  m_btnFind;

	private: System::Windows::Forms::TextBox^  m_txtValue;

	private: System::Windows::Forms::Label^  m_lblValue;
	private: System::Windows::Forms::CheckBox^  m_chxHexNumber;
	private: System::Windows::Forms::ComboBox^  m_lstTypeList;
	private: System::Windows::Forms::TextBox^  m_txtOffset;




	private: System::Windows::Forms::Label^  m_lblType;
	private: System::Windows::Forms::Label^  m_lblOffset;
	private: System::Windows::Forms::TextBox^  m_txtPattern;



	private: System::Windows::Forms::TextBox^  m_txtBase;

	private: System::Windows::Forms::TextBox^  m_txtName;

	private: System::Windows::Forms::Label^  m_lblArray;

	private: System::Windows::Forms::Label^  m_lblBase;

	private: System::Windows::Forms::Label^  m_lblName;
	private: System::Windows::Forms::ListView^  m_lstPointerList;


	private: System::Windows::Forms::ColumnHeader^  m_hdrName;
	private: System::Windows::Forms::ColumnHeader^  m_hdrBase;
	private: System::Windows::Forms::ColumnHeader^  m_hdrOffset;
	private: System::Windows::Forms::ColumnHeader^  m_hdrValue;
	private: System::Windows::Forms::ColumnHeader^  m_hdrPattern;
	private: System::Windows::Forms::ToolTip^  m_ttpToolTip;

	private: System::Windows::Forms::Timer^ m_tmrTimer;

#pragma region Windows Form Designer generated code
	private:
		System::ComponentModel::IContainer^ components;

		void InitializeComponent ( void )
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ZMemoryManager::typeid));
			this->m_mbrStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->m_itmTablesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmImportToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmTablesMenuToolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->m_itmExportToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmExportAsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmTablesMenuToolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->m_itmClearToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_splContainer = (gcnew System::Windows::Forms::SplitContainer());
			this->m_ctrContainer = (gcnew System::Windows::Forms::GroupBox());
			this->m_btnTrack = (gcnew System::Windows::Forms::Button());
			this->m_btnFind = (gcnew System::Windows::Forms::Button());
			this->m_txtValue = (gcnew System::Windows::Forms::TextBox());
			this->m_lblValue = (gcnew System::Windows::Forms::Label());
			this->m_chxHexNumber = (gcnew System::Windows::Forms::CheckBox());
			this->m_lstTypeList = (gcnew System::Windows::Forms::ComboBox());
			this->m_txtOffset = (gcnew System::Windows::Forms::TextBox());
			this->m_lblType = (gcnew System::Windows::Forms::Label());
			this->m_lblOffset = (gcnew System::Windows::Forms::Label());
			this->m_txtPattern = (gcnew System::Windows::Forms::TextBox());
			this->m_txtBase = (gcnew System::Windows::Forms::TextBox());
			this->m_txtName = (gcnew System::Windows::Forms::TextBox());
			this->m_lblArray = (gcnew System::Windows::Forms::Label());
			this->m_lblBase = (gcnew System::Windows::Forms::Label());
			this->m_lblName = (gcnew System::Windows::Forms::Label());
			this->m_lstPointerList = (gcnew System::Windows::Forms::ListView());
			this->m_hdrPattern = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_hdrName = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_hdrBase = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_hdrOffset = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_hdrValue = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_ttpToolTip = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->m_tmrTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->m_mbrStrip->SuspendLayout();
			this->m_splContainer->Panel1->SuspendLayout();
			this->m_splContainer->Panel2->SuspendLayout();
			this->m_splContainer->SuspendLayout();
			this->m_ctrContainer->SuspendLayout();
			this->SuspendLayout();
			// 
			// m_mbrStrip
			// 
			this->m_mbrStrip->BackColor = System::Drawing::SystemColors::Control;
			this->m_mbrStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->m_itmTablesToolStripMenuItem});
			this->m_mbrStrip->Location = System::Drawing::Point(0, 0);
			this->m_mbrStrip->Name = L"m_mbrStrip";
			this->m_mbrStrip->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
			this->m_mbrStrip->Size = System::Drawing::Size(498, 24);
			this->m_mbrStrip->TabIndex = 0;
			// 
			// m_itmTablesToolStripMenuItem
			// 
			this->m_itmTablesToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {this->m_itmImportToolStripMenuItem, 
				this->m_itmTablesMenuToolStripSeparator1, this->m_itmExportToolStripMenuItem, this->m_itmExportAsToolStripMenuItem, this->m_itmTablesMenuToolStripSeparator2, 
				this->m_itmClearToolStripMenuItem});
			this->m_itmTablesToolStripMenuItem->Name = L"m_itmTablesToolStripMenuItem";
			this->m_itmTablesToolStripMenuItem->Size = System::Drawing::Size(56, 20);
			this->m_itmTablesToolStripMenuItem->Text = L"&Tables";
			// 
			// m_itmImportToolStripMenuItem
			// 
			this->m_itmImportToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_itmImportToolStripMenuItem.Image")));
			this->m_itmImportToolStripMenuItem->Name = L"m_itmImportToolStripMenuItem";
			this->m_itmImportToolStripMenuItem->Size = System::Drawing::Size(140, 22);
			this->m_itmImportToolStripMenuItem->Text = L"Import";
			this->m_itmImportToolStripMenuItem->ToolTipText = L"Import a table of pointer definitions from a file";
			this->m_itmImportToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZMemoryManager::OnImportClick);
			// 
			// m_itmTablesMenuToolStripSeparator1
			// 
			this->m_itmTablesMenuToolStripSeparator1->Name = L"m_itmTablesMenuToolStripSeparator1";
			this->m_itmTablesMenuToolStripSeparator1->Size = System::Drawing::Size(137, 6);
			// 
			// m_itmExportToolStripMenuItem
			// 
			this->m_itmExportToolStripMenuItem->Enabled = false;
			this->m_itmExportToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_itmExportToolStripMenuItem.Image")));
			this->m_itmExportToolStripMenuItem->Name = L"m_itmExportToolStripMenuItem";
			this->m_itmExportToolStripMenuItem->Size = System::Drawing::Size(140, 22);
			this->m_itmExportToolStripMenuItem->Text = L"Export";
			this->m_itmExportToolStripMenuItem->ToolTipText = L"Export pointer definitions to a file";
			this->m_itmExportToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZMemoryManager::OnExportClick);
			// 
			// m_itmExportAsToolStripMenuItem
			// 
			this->m_itmExportAsToolStripMenuItem->Enabled = false;
			this->m_itmExportAsToolStripMenuItem->Name = L"m_itmExportAsToolStripMenuItem";
			this->m_itmExportAsToolStripMenuItem->Size = System::Drawing::Size(140, 22);
			this->m_itmExportAsToolStripMenuItem->Text = L"Export As";
			this->m_itmExportAsToolStripMenuItem->ToolTipText = L"Export pointer definitions to a file";
			this->m_itmExportAsToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZMemoryManager::OnExportAsClick);
			// 
			// m_itmTablesMenuToolStripSeparator2
			// 
			this->m_itmTablesMenuToolStripSeparator2->Name = L"m_itmTablesMenuToolStripSeparator2";
			this->m_itmTablesMenuToolStripSeparator2->Size = System::Drawing::Size(137, 6);
			// 
			// m_itmClearToolStripMenuItem
			// 
			this->m_itmClearToolStripMenuItem->Enabled = false;
			this->m_itmClearToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_itmClearToolStripMenuItem.Image")));
			this->m_itmClearToolStripMenuItem->Name = L"m_itmClearToolStripMenuItem";
			this->m_itmClearToolStripMenuItem->Size = System::Drawing::Size(140, 22);
			this->m_itmClearToolStripMenuItem->Text = L"Clear";
			this->m_itmClearToolStripMenuItem->ToolTipText = L"Remove all pointer definitions from the table";
			this->m_itmClearToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZMemoryManager::OnClearClick);
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
			this->m_splContainer->Panel2->Controls->Add(this->m_lstPointerList);
			this->m_splContainer->Panel2->Padding = System::Windows::Forms::Padding(4);
			this->m_splContainer->Size = System::Drawing::Size(498, 424);
			this->m_splContainer->SplitterDistance = 108;
			this->m_splContainer->TabIndex = 0;
			this->m_splContainer->TabStop = false;
			// 
			// m_ctrContainer
			// 
			this->m_ctrContainer->Controls->Add(this->m_btnTrack);
			this->m_ctrContainer->Controls->Add(this->m_btnFind);
			this->m_ctrContainer->Controls->Add(this->m_txtValue);
			this->m_ctrContainer->Controls->Add(this->m_lblValue);
			this->m_ctrContainer->Controls->Add(this->m_chxHexNumber);
			this->m_ctrContainer->Controls->Add(this->m_lstTypeList);
			this->m_ctrContainer->Controls->Add(this->m_txtOffset);
			this->m_ctrContainer->Controls->Add(this->m_lblType);
			this->m_ctrContainer->Controls->Add(this->m_lblOffset);
			this->m_ctrContainer->Controls->Add(this->m_txtPattern);
			this->m_ctrContainer->Controls->Add(this->m_txtBase);
			this->m_ctrContainer->Controls->Add(this->m_txtName);
			this->m_ctrContainer->Controls->Add(this->m_lblArray);
			this->m_ctrContainer->Controls->Add(this->m_lblBase);
			this->m_ctrContainer->Controls->Add(this->m_lblName);
			this->m_ctrContainer->Dock = System::Windows::Forms::DockStyle::Fill;
			this->m_ctrContainer->Location = System::Drawing::Point(4, 4);
			this->m_ctrContainer->Margin = System::Windows::Forms::Padding(0);
			this->m_ctrContainer->Name = L"m_ctrContainer";
			this->m_ctrContainer->Padding = System::Windows::Forms::Padding(4);
			this->m_ctrContainer->Size = System::Drawing::Size(490, 100);
			this->m_ctrContainer->TabIndex = 0;
			this->m_ctrContainer->TabStop = false;
			this->m_ctrContainer->Text = L"Create A New Pointer";
			// 
			// m_btnTrack
			// 
			this->m_btnTrack->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->m_btnTrack->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_btnTrack.Image")));
			this->m_btnTrack->Location = System::Drawing::Point(413, 70);
			this->m_btnTrack->Margin = System::Windows::Forms::Padding(0);
			this->m_btnTrack->Name = L"m_btnTrack";
			this->m_btnTrack->Size = System::Drawing::Size(72, 25);
			this->m_btnTrack->TabIndex = 7;
			this->m_btnTrack->Text = L"Track";
			this->m_btnTrack->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->m_ttpToolTip->SetToolTip(this->m_btnTrack, L"Track this pointer definition");
			this->m_btnTrack->UseVisualStyleBackColor = true;
			this->m_btnTrack->Click += gcnew System::EventHandler(this, &ZMemoryManager::OnTrackClick);
			// 
			// m_btnFind
			// 
			this->m_btnFind->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->m_btnFind->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_btnFind.Image")));
			this->m_btnFind->Location = System::Drawing::Point(340, 70);
			this->m_btnFind->Margin = System::Windows::Forms::Padding(0);
			this->m_btnFind->Name = L"m_btnFind";
			this->m_btnFind->Size = System::Drawing::Size(72, 25);
			this->m_btnFind->TabIndex = 6;
			this->m_btnFind->Text = L"Find";
			this->m_btnFind->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->m_ttpToolTip->SetToolTip(this->m_btnFind, L"Locate the value of this pointer definition");
			this->m_btnFind->UseVisualStyleBackColor = true;
			this->m_btnFind->Click += gcnew System::EventHandler(this, &ZMemoryManager::OnFindClick);
			// 
			// m_txtValue
			// 
			this->m_txtValue->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->m_txtValue->BackColor = System::Drawing::SystemColors::Window;
			this->m_txtValue->Location = System::Drawing::Point(374, 45);
			this->m_txtValue->Margin = System::Windows::Forms::Padding(0);
			this->m_txtValue->MaxLength = 32;
			this->m_txtValue->Name = L"m_txtValue";
			this->m_txtValue->ReadOnly = true;
			this->m_txtValue->Size = System::Drawing::Size(111, 21);
			this->m_txtValue->TabIndex = 0;
			this->m_txtValue->TabStop = false;
			this->m_txtValue->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->m_ttpToolTip->SetToolTip(this->m_txtValue, L"The value of this pointer");
			// 
			// m_lblValue
			// 
			this->m_lblValue->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->m_lblValue->Location = System::Drawing::Point(324, 45);
			this->m_lblValue->Margin = System::Windows::Forms::Padding(0);
			this->m_lblValue->Name = L"m_lblValue";
			this->m_lblValue->Size = System::Drawing::Size(47, 21);
			this->m_lblValue->TabIndex = 0;
			this->m_lblValue->Text = L"Value";
			this->m_lblValue->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// m_chxHexNumber
			// 
			this->m_chxHexNumber->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->m_chxHexNumber->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->m_chxHexNumber->Location = System::Drawing::Point(329, 20);
			this->m_chxHexNumber->Margin = System::Windows::Forms::Padding(0);
			this->m_chxHexNumber->Name = L"m_chxHexNumber";
			this->m_chxHexNumber->Size = System::Drawing::Size(152, 21);
			this->m_chxHexNumber->TabIndex = 0;
			this->m_chxHexNumber->TabStop = false;
			this->m_chxHexNumber->Text = L"Use base-16 format";
			this->m_ttpToolTip->SetToolTip(this->m_chxHexNumber, L"Display the pointer value in hexdecimal format");
			this->m_chxHexNumber->UseVisualStyleBackColor = true;
			this->m_chxHexNumber->CheckedChanged += gcnew System::EventHandler(this, &ZMemoryManager::OnHexNumberCheckedChanged);
			// 
			// m_lstTypeList
			// 
			this->m_lstTypeList->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->m_lstTypeList->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->m_lstTypeList->FormattingEnabled = true;
			this->m_lstTypeList->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"Static Address", L"Array Of Bytes"});
			this->m_lstTypeList->Location = System::Drawing::Point(214, 20);
			this->m_lstTypeList->Margin = System::Windows::Forms::Padding(0);
			this->m_lstTypeList->Name = L"m_lstTypeList";
			this->m_lstTypeList->Size = System::Drawing::Size(107, 21);
			this->m_lstTypeList->TabIndex = 2;
			this->m_ttpToolTip->SetToolTip(this->m_lstTypeList, L"Select the type of pointer to define");
			this->m_lstTypeList->SelectedIndexChanged += gcnew System::EventHandler(this, &ZMemoryManager::OnTypeListSelectedIndexChanged);
			// 
			// m_txtOffset
			// 
			this->m_txtOffset->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->m_txtOffset->Location = System::Drawing::Point(214, 45);
			this->m_txtOffset->Margin = System::Windows::Forms::Padding(0);
			this->m_txtOffset->Name = L"m_txtOffset";
			this->m_txtOffset->Size = System::Drawing::Size(107, 21);
			this->m_txtOffset->TabIndex = 4;
			this->m_txtOffset->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->m_ttpToolTip->SetToolTip(this->m_txtOffset, L"The offset from the address");
			this->m_txtOffset->Leave += gcnew System::EventHandler(this, &ZMemoryManager::OnValueLeave);
			// 
			// m_lblType
			// 
			this->m_lblType->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->m_lblType->Location = System::Drawing::Point(164, 20);
			this->m_lblType->Margin = System::Windows::Forms::Padding(0);
			this->m_lblType->Name = L"m_lblType";
			this->m_lblType->Size = System::Drawing::Size(50, 21);
			this->m_lblType->TabIndex = 0;
			this->m_lblType->Text = L"Type";
			this->m_lblType->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// m_lblOffset
			// 
			this->m_lblOffset->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->m_lblOffset->Location = System::Drawing::Point(164, 45);
			this->m_lblOffset->Margin = System::Windows::Forms::Padding(0);
			this->m_lblOffset->Name = L"m_lblOffset";
			this->m_lblOffset->Size = System::Drawing::Size(50, 21);
			this->m_lblOffset->TabIndex = 0;
			this->m_lblOffset->Text = L"Offset";
			this->m_lblOffset->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// m_txtPattern
			// 
			this->m_txtPattern->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->m_txtPattern->Location = System::Drawing::Point(55, 73);
			this->m_txtPattern->Margin = System::Windows::Forms::Padding(0);
			this->m_txtPattern->Name = L"m_txtPattern";
			this->m_txtPattern->Size = System::Drawing::Size(268, 21);
			this->m_txtPattern->TabIndex = 5;
			this->m_ttpToolTip->SetToolTip(this->m_txtPattern, L"An array bytes used to find this pointer\'s address");
			this->m_txtPattern->Leave += gcnew System::EventHandler(this, &ZMemoryManager::OnArrayLeave);
			// 
			// m_txtBase
			// 
			this->m_txtBase->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->m_txtBase->Location = System::Drawing::Point(55, 45);
			this->m_txtBase->Margin = System::Windows::Forms::Padding(0);
			this->m_txtBase->Name = L"m_txtBase";
			this->m_txtBase->Size = System::Drawing::Size(108, 21);
			this->m_txtBase->TabIndex = 3;
			this->m_txtBase->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->m_ttpToolTip->SetToolTip(this->m_txtBase, L"The address this pointer is based on");
			this->m_txtBase->Leave += gcnew System::EventHandler(this, &ZMemoryManager::OnValueLeave);
			// 
			// m_txtName
			// 
			this->m_txtName->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->m_txtName->Location = System::Drawing::Point(55, 20);
			this->m_txtName->Margin = System::Windows::Forms::Padding(0);
			this->m_txtName->MaxLength = 128;
			this->m_txtName->Name = L"m_txtName";
			this->m_txtName->Size = System::Drawing::Size(108, 21);
			this->m_txtName->TabIndex = 1;
			this->m_txtName->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->m_ttpToolTip->SetToolTip(this->m_txtName, L"Type the name of the pointer definition ([_0-9a-zA-Z] only).");
			this->m_txtName->Leave += gcnew System::EventHandler(this, &ZMemoryManager::OnNameLeave);
			// 
			// m_lblArray
			// 
			this->m_lblArray->Location = System::Drawing::Point(5, 70);
			this->m_lblArray->Margin = System::Windows::Forms::Padding(0);
			this->m_lblArray->Name = L"m_lblArray";
			this->m_lblArray->Size = System::Drawing::Size(50, 21);
			this->m_lblArray->TabIndex = 0;
			this->m_lblArray->Text = L"Array";
			this->m_lblArray->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// m_lblBase
			// 
			this->m_lblBase->Location = System::Drawing::Point(5, 45);
			this->m_lblBase->Margin = System::Windows::Forms::Padding(0);
			this->m_lblBase->Name = L"m_lblBase";
			this->m_lblBase->Size = System::Drawing::Size(50, 21);
			this->m_lblBase->TabIndex = 0;
			this->m_lblBase->Text = L"Base";
			this->m_lblBase->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// m_lblName
			// 
			this->m_lblName->Location = System::Drawing::Point(5, 20);
			this->m_lblName->Margin = System::Windows::Forms::Padding(0);
			this->m_lblName->Name = L"m_lblName";
			this->m_lblName->Size = System::Drawing::Size(50, 21);
			this->m_lblName->TabIndex = 0;
			this->m_lblName->Text = L"Name";
			this->m_lblName->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// m_lstPointerList
			// 
			this->m_lstPointerList->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(5) {this->m_hdrPattern, 
				this->m_hdrName, this->m_hdrBase, this->m_hdrOffset, this->m_hdrValue});
			this->m_lstPointerList->Dock = System::Windows::Forms::DockStyle::Fill;
			this->m_lstPointerList->FullRowSelect = true;
			this->m_lstPointerList->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->m_lstPointerList->Location = System::Drawing::Point(4, 4);
			this->m_lstPointerList->Margin = System::Windows::Forms::Padding(0);
			this->m_lstPointerList->Name = L"m_lstPointerList";
			this->m_lstPointerList->Size = System::Drawing::Size(490, 304);
			this->m_lstPointerList->TabIndex = 0;
			this->m_lstPointerList->UseCompatibleStateImageBehavior = false;
			this->m_lstPointerList->View = System::Windows::Forms::View::Details;
			this->m_lstPointerList->ItemMouseHover += gcnew System::Windows::Forms::ListViewItemMouseHoverEventHandler(this, &ZMemoryManager::OnPointerListItemMouseHover);
			this->m_lstPointerList->ItemSelectionChanged += gcnew System::Windows::Forms::ListViewItemSelectionChangedEventHandler(this, &ZMemoryManager::OnPointerListItemSelectionChanged);
			// 
			// m_hdrPattern
			// 
			this->m_hdrPattern->Text = L"";
			this->m_hdrPattern->Width = 0;
			// 
			// m_hdrName
			// 
			this->m_hdrName->Text = L"Name";
			this->m_hdrName->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->m_hdrName->Width = 110;
			// 
			// m_hdrBase
			// 
			this->m_hdrBase->Text = L"Base Address";
			this->m_hdrBase->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->m_hdrBase->Width = 110;
			// 
			// m_hdrOffset
			// 
			this->m_hdrOffset->Text = L"Offset";
			this->m_hdrOffset->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->m_hdrOffset->Width = 110;
			// 
			// m_hdrValue
			// 
			this->m_hdrValue->Text = L"Value";
			this->m_hdrValue->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->m_hdrValue->Width = 110;
			// 
			// m_ttpToolTip
			// 
			this->m_ttpToolTip->AutomaticDelay = 250;
			this->m_ttpToolTip->Popup += gcnew System::Windows::Forms::PopupEventHandler(this, &ZMemoryManager::OnToolTipPopup);
			// 
			// m_tmrTimer
			// 
			this->m_tmrTimer->Interval = 75;
			this->m_tmrTimer->Tick += gcnew System::EventHandler(this, &ZMemoryManager::OnTick);
			// 
			// ZMemoryManager
			// 
			this->ClientSize = System::Drawing::Size(498, 448);
			this->Controls->Add(this->m_splContainer);
			this->Controls->Add(this->m_mbrStrip);
			this->Font = (gcnew System::Drawing::Font(L"Verdana", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->MainMenuStrip = this->m_mbrStrip;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->MinimumSize = System::Drawing::Size(506, 475);
			this->Name = L"ZMemoryManager";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->Text = L"Z - Memory Tracker";
			this->m_mbrStrip->ResumeLayout(false);
			this->m_mbrStrip->PerformLayout();
			this->m_splContainer->Panel1->ResumeLayout(false);
			this->m_splContainer->Panel2->ResumeLayout(false);
			this->m_splContainer->ResumeLayout(false);
			this->m_ctrContainer->ResumeLayout(false);
			this->m_ctrContainer->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		
		



};
}

#endif /* __ZMemoryManager_h__ */
