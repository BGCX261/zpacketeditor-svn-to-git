#ifndef __ZPatternManager_h__
#define __ZPatternManager_h__

#pragma once

#include "Z.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Drawing;
using namespace System::Windows::Forms;

namespace Z
{
	ref class ZPattern;

	ref class ZPatternCollection;

	ref class ZPatternManager : public System::Windows::Forms::Form
	{
		delegate ZPattern^ CreatePatternCaller ( String^ pattern );

	private:
		ZPatternCollection^ m_Collection;

	public:
		/* Constructor */
		ZPatternManager ( String^ title )
		{
			InitializeComponent();
			Initialize(title);
		}

		/* Dispose */
		~ZPatternManager ( void )
		{
			if ( components )
				delete components;
		}

	private:
		void Initialize ( String^ title );

	public:
		/* Add a pattern to the collection */
		ZPattern^ CreatePattern ( String^ pattern );
		/* Match bytes against a pattern in the list */
		bool IsMatch ( String^ rawBytes );

	private:
		void OnListColumnClick ( Object^ sender, ColumnClickEventArgs^ e );

		void OnListItemActivate ( Object^ sender, EventArgs^ e );

		void OnListItemMouseHover ( Object^ sender, ListViewItemMouseHoverEventArgs^ e );

		void OnListItemChecked ( Object^ sender, ItemCheckedEventArgs^ e );

		void OnClearClick ( Object^ sender, EventArgs^ e );

		void OnToolTipPopup ( Object^ sender, PopupEventArgs^ e);

	private: System::Windows::Forms::SplitContainer^  m_splContainer;
	public: 
	private: System::Windows::Forms::ListView^  m_lstPatternList;
	private: System::Windows::Forms::ColumnHeader^  m_hdrPattern;
	private: System::Windows::Forms::Button^  m_btnClear;
	private: System::Windows::Forms::Label^  m_lblText;
	private: System::Windows::Forms::ToolTip^  m_ttpToolTip;

#pragma region Windows Form Designer generated code
	private:
		System::ComponentModel::IContainer^ components;

		void InitializeComponent ( void )
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ZPatternManager::typeid));
			this->m_splContainer = (gcnew System::Windows::Forms::SplitContainer());
			this->m_lstPatternList = (gcnew System::Windows::Forms::ListView());
			this->m_hdrPattern = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_btnClear = (gcnew System::Windows::Forms::Button());
			this->m_lblText = (gcnew System::Windows::Forms::Label());
			this->m_ttpToolTip = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->m_splContainer->Panel1->SuspendLayout();
			this->m_splContainer->Panel2->SuspendLayout();
			this->m_splContainer->SuspendLayout();
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
			this->m_splContainer->Panel1->Controls->Add(this->m_lstPatternList);
			this->m_splContainer->Panel1->Padding = System::Windows::Forms::Padding(1);
			// 
			// m_splContainer.Panel2
			// 
			this->m_splContainer->Panel2->Controls->Add(this->m_btnClear);
			this->m_splContainer->Panel2->Controls->Add(this->m_lblText);
			this->m_splContainer->Panel2->Padding = System::Windows::Forms::Padding(1);
			this->m_splContainer->Size = System::Drawing::Size(492, 442);
			this->m_splContainer->SplitterDistance = 410;
			this->m_splContainer->SplitterWidth = 1;
			this->m_splContainer->TabIndex = 0;
			// 
			// m_lstPatternList
			// 
			this->m_lstPatternList->CheckBoxes = true;
			this->m_lstPatternList->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(1) {this->m_hdrPattern});
			this->m_lstPatternList->Dock = System::Windows::Forms::DockStyle::Fill;
			this->m_lstPatternList->FullRowSelect = true;
			this->m_lstPatternList->Location = System::Drawing::Point(1, 1);
			this->m_lstPatternList->Margin = System::Windows::Forms::Padding(0);
			this->m_lstPatternList->MultiSelect = false;
			this->m_lstPatternList->Name = L"m_lstPatternList";
			this->m_lstPatternList->Size = System::Drawing::Size(490, 408);
			this->m_lstPatternList->TabIndex = 0;
			this->m_lstPatternList->UseCompatibleStateImageBehavior = false;
			this->m_lstPatternList->View = System::Windows::Forms::View::Details;
			this->m_lstPatternList->ItemActivate += gcnew System::EventHandler(this, &ZPatternManager::OnListItemActivate);
			this->m_lstPatternList->ItemChecked += gcnew System::Windows::Forms::ItemCheckedEventHandler(this, &ZPatternManager::OnListItemChecked);
			this->m_lstPatternList->ItemMouseHover += gcnew System::Windows::Forms::ListViewItemMouseHoverEventHandler(this, &ZPatternManager::OnListItemMouseHover);
			this->m_lstPatternList->ColumnClick += gcnew System::Windows::Forms::ColumnClickEventHandler(this, &ZPatternManager::OnListColumnClick);
			// 
			// m_hdrPattern
			// 
			this->m_hdrPattern->Text = L"Pattern";
			this->m_hdrPattern->Width = 465;
			// 
			// m_btnClear
			// 
			this->m_btnClear->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->m_btnClear->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_btnClear.Image")));
			this->m_btnClear->Location = System::Drawing::Point(415, 4);
			this->m_btnClear->Margin = System::Windows::Forms::Padding(0);
			this->m_btnClear->Name = L"m_btnClear";
			this->m_btnClear->Size = System::Drawing::Size(75, 25);
			this->m_btnClear->TabIndex = 1;
			this->m_btnClear->Text = L"Clear";
			this->m_btnClear->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->m_ttpToolTip->SetToolTip(this->m_btnClear, L"Remove all patterns from this collection");
			this->m_btnClear->UseVisualStyleBackColor = true;
			this->m_btnClear->Click += gcnew System::EventHandler(this, &ZPatternManager::OnClearClick);
			// 
			// m_lblText
			// 
			this->m_lblText->ForeColor = System::Drawing::Color::Gray;
			this->m_lblText->Location = System::Drawing::Point(5, 5);
			this->m_lblText->Margin = System::Windows::Forms::Padding(0);
			this->m_lblText->Name = L"m_lblText";
			this->m_lblText->Size = System::Drawing::Size(315, 25);
			this->m_lblText->TabIndex = 0;
			this->m_lblText->Text = L"You can enable or disable your patterns above.";
			this->m_lblText->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// m_ttpToolTip
			// 
			this->m_ttpToolTip->AutomaticDelay = 250;
			this->m_ttpToolTip->Popup += gcnew System::Windows::Forms::PopupEventHandler(this, &ZPatternManager::OnToolTipPopup);
			// 
			// ZPatternManager
			// 
			this->ClientSize = System::Drawing::Size(500, 450);
			this->Controls->Add(this->m_splContainer);
			this->Font = (gcnew System::Drawing::Font(L"Verdana", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->MinimumSize = System::Drawing::Size(506, 475);
			this->Name = L"ZPatternManager";
			this->Padding = System::Windows::Forms::Padding(4);
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->m_splContainer->Panel1->ResumeLayout(false);
			this->m_splContainer->Panel2->ResumeLayout(false);
			this->m_splContainer->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

	};
}

#endif /* __ZPatternManager_h__ */
