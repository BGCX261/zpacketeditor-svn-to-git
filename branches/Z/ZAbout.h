#ifndef __ZAbout_h__
#define __ZAbout_h__

#pragma once

#include "Z.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Drawing;
using namespace System::Windows::Forms;

namespace Z
{
	ref class ZAbout : public System::Windows::Forms::Form
	{
	public:
		/* Constructor */
		ZAbout ( void )
		{
			InitializeComponent();
		}

		/* Dispose */
		~ZAbout ( void )
		{
			if ( components )
				delete components;
		}

	private:
		/* Get assembly title string */
		static String^ GetAssemblyTitle ( void );
		/* Get version string */
		static String^ GetAssemblyVersion ( void );
		/* Get copyright string */
		static String^ GetAssemblyCopyright ( void );

	protected:
		virtual void OnLoad ( EventArgs^ e ) override;

	private: System::Windows::Forms::Label^  m_lblImage;
	private: System::Windows::Forms::Label^  m_lblVersion;
	private: System::Windows::Forms::Label^  m_lblCopyright;
	private: System::Windows::Forms::Label^  m_lblText;

#pragma region Windows Form Designer generated code
	private:
		System::ComponentModel::IContainer^ components;

		void InitializeComponent ( void )
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ZAbout::typeid));
			this->m_lblImage = (gcnew System::Windows::Forms::Label());
			this->m_lblVersion = (gcnew System::Windows::Forms::Label());
			this->m_lblCopyright = (gcnew System::Windows::Forms::Label());
			this->m_lblText = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// m_lblImage
			// 
			this->m_lblImage->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_lblImage.Image")));
			this->m_lblImage->Location = System::Drawing::Point(5, 5);
			this->m_lblImage->Margin = System::Windows::Forms::Padding(0);
			this->m_lblImage->Name = L"m_lblImage";
			this->m_lblImage->Size = System::Drawing::Size(160, 215);
			this->m_lblImage->TabIndex = 0;
			this->m_lblImage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// m_lblVersion
			// 
			this->m_lblVersion->Location = System::Drawing::Point(165, 5);
			this->m_lblVersion->Margin = System::Windows::Forms::Padding(0);
			this->m_lblVersion->Name = L"m_lblVersion";
			this->m_lblVersion->Padding = System::Windows::Forms::Padding(2);
			this->m_lblVersion->Size = System::Drawing::Size(325, 20);
			this->m_lblVersion->TabIndex = 1;
			this->m_lblVersion->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// m_lblCopyright
			// 
			this->m_lblCopyright->Location = System::Drawing::Point(165, 28);
			this->m_lblCopyright->Margin = System::Windows::Forms::Padding(0);
			this->m_lblCopyright->Name = L"m_lblCopyright";
			this->m_lblCopyright->Padding = System::Windows::Forms::Padding(2);
			this->m_lblCopyright->Size = System::Drawing::Size(325, 20);
			this->m_lblCopyright->TabIndex = 2;
			this->m_lblCopyright->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// m_lblText
			// 
			this->m_lblText->Location = System::Drawing::Point(165, 50);
			this->m_lblText->Margin = System::Windows::Forms::Padding(0);
			this->m_lblText->Name = L"m_lblText";
			this->m_lblText->Padding = System::Windows::Forms::Padding(2);
			this->m_lblText->Size = System::Drawing::Size(325, 165);
			this->m_lblText->TabIndex = 3;
			this->m_lblText->Text = resources->GetString(L"m_lblText.Text");
			this->m_lblText->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// ZAbout
			// 
			this->ClientSize = System::Drawing::Size(494, 220);
			this->Controls->Add(this->m_lblText);
			this->Controls->Add(this->m_lblCopyright);
			this->Controls->Add(this->m_lblVersion);
			this->Controls->Add(this->m_lblImage);
			this->Font = (gcnew System::Drawing::Font(L"Verdana", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"ZAbout";
			this->Padding = System::Windows::Forms::Padding(4);
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"About Z";
			this->TopMost = true;
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}

#endif /* __ZAbout_h__ */
