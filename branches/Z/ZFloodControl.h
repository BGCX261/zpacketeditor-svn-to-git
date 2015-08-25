#ifndef __ZFloodControl_h__
#define __ZFloodControl_h__

#pragma once

#include "Z.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::ComponentModel;
using namespace System::Diagnostics;
using namespace System::Drawing;
using namespace System::Threading;
using namespace System::Windows::Forms;

namespace Z
{
	ref class ZFloodControl : public System::Windows::Forms::Form
	{
	public:
		/* Constructor */
		ZFloodControl ( void )
		{
			InitializeComponent();

			this->m_Collection = gcnew List<String^>;
		}

		/* Dispose */
		~ZFloodControl ( void )
		{
			if ( components )
				delete components;
		}

	private:
		Thread^ m_thrThread;
		List<String^>^ m_Collection;

	private:
		void CreateFlood ( void );

		void FinishFlood ( void );

		void FloodPackets ( void );

		void SetStatusText ( String^ text );

	protected:
		virtual void OnClosed ( EventArgs^ e ) override;


	private: System::Windows::Forms::TabControl^  m_tbContainer;
	private: System::Windows::Forms::TabPage^  m_tbpPacketFlood;
	private: System::Windows::Forms::TabPage^  m_tbpProtector;
	private: System::Windows::Forms::ImageList^  m_lstTabImages;
	private: System::Windows::Forms::ProgressBar^  m_pbrWork;
	private: System::Windows::Forms::Button^  m_btnStart;
	private: System::Windows::Forms::TextBox^  m_txtPackets;
	private: System::Windows::Forms::NumericUpDown^  m_nbrLimited;

	private: System::Windows::Forms::Label^  m_lblPackets;
	private: System::Windows::Forms::RadioButton^  m_rdiRandom;
	private: System::Windows::Forms::RadioButton^  m_rdiCounter;
	private: System::Windows::Forms::Label^  m_lblSeries;
	private: System::Windows::Forms::CheckBox^  m_chxSetPacketLimit;
	private: System::Windows::Forms::Label^  m_lblMilliseconds;
	private: System::Windows::Forms::Label^  m_lblEvery;
	private: System::Windows::Forms::NumericUpDown^  m_nbrInterval;
	private: System::Windows::Forms::Label^  m_lblStatus;
	private: System::Windows::Forms::ToolTip^  m_ttpToolTip;

	
#pragma region Windows Form Designer generated code

	private:
		System::ComponentModel::IContainer^ components;

		void InitializeComponent ( void )
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ZFloodControl::typeid));
			this->m_tbContainer = (gcnew System::Windows::Forms::TabControl());
			this->m_tbpPacketFlood = (gcnew System::Windows::Forms::TabPage());
			this->m_lblStatus = (gcnew System::Windows::Forms::Label());
			this->m_pbrWork = (gcnew System::Windows::Forms::ProgressBar());
			this->m_btnStart = (gcnew System::Windows::Forms::Button());
			this->m_txtPackets = (gcnew System::Windows::Forms::TextBox());
			this->m_nbrLimited = (gcnew System::Windows::Forms::NumericUpDown());
			this->m_lblPackets = (gcnew System::Windows::Forms::Label());
			this->m_rdiRandom = (gcnew System::Windows::Forms::RadioButton());
			this->m_rdiCounter = (gcnew System::Windows::Forms::RadioButton());
			this->m_lblSeries = (gcnew System::Windows::Forms::Label());
			this->m_chxSetPacketLimit = (gcnew System::Windows::Forms::CheckBox());
			this->m_lblMilliseconds = (gcnew System::Windows::Forms::Label());
			this->m_nbrInterval = (gcnew System::Windows::Forms::NumericUpDown());
			this->m_lblEvery = (gcnew System::Windows::Forms::Label());
			this->m_tbpProtector = (gcnew System::Windows::Forms::TabPage());
			this->m_lstTabImages = (gcnew System::Windows::Forms::ImageList(this->components));
			this->m_ttpToolTip = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->m_tbContainer->SuspendLayout();
			this->m_tbpPacketFlood->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->m_nbrLimited))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->m_nbrInterval))->BeginInit();
			this->SuspendLayout();
			// 
			// m_tbContainer
			// 
			this->m_tbContainer->Controls->Add(this->m_tbpPacketFlood);
			this->m_tbContainer->Controls->Add(this->m_tbpProtector);
			this->m_tbContainer->Dock = System::Windows::Forms::DockStyle::Fill;
			this->m_tbContainer->ImageList = this->m_lstTabImages;
			this->m_tbContainer->Location = System::Drawing::Point(4, 4);
			this->m_tbContainer->Margin = System::Windows::Forms::Padding(0);
			this->m_tbContainer->Name = L"m_tbContainer";
			this->m_tbContainer->SelectedIndex = 0;
			this->m_tbContainer->Size = System::Drawing::Size(490, 440);
			this->m_tbContainer->TabIndex = 0;
			this->m_tbContainer->Selecting += gcnew System::Windows::Forms::TabControlCancelEventHandler(this, &ZFloodControl::OnTabSelecting);
			// 
			// m_tbpPacketFlood
			// 
			this->m_tbpPacketFlood->BackColor = System::Drawing::Color::White;
			this->m_tbpPacketFlood->Controls->Add(this->m_lblStatus);
			this->m_tbpPacketFlood->Controls->Add(this->m_pbrWork);
			this->m_tbpPacketFlood->Controls->Add(this->m_btnStart);
			this->m_tbpPacketFlood->Controls->Add(this->m_txtPackets);
			this->m_tbpPacketFlood->Controls->Add(this->m_nbrLimited);
			this->m_tbpPacketFlood->Controls->Add(this->m_lblPackets);
			this->m_tbpPacketFlood->Controls->Add(this->m_rdiRandom);
			this->m_tbpPacketFlood->Controls->Add(this->m_rdiCounter);
			this->m_tbpPacketFlood->Controls->Add(this->m_lblSeries);
			this->m_tbpPacketFlood->Controls->Add(this->m_chxSetPacketLimit);
			this->m_tbpPacketFlood->Controls->Add(this->m_lblMilliseconds);
			this->m_tbpPacketFlood->Controls->Add(this->m_nbrInterval);
			this->m_tbpPacketFlood->Controls->Add(this->m_lblEvery);
			this->m_tbpPacketFlood->ImageIndex = 0;
			this->m_tbpPacketFlood->Location = System::Drawing::Point(4, 23);
			this->m_tbpPacketFlood->Margin = System::Windows::Forms::Padding(0);
			this->m_tbpPacketFlood->Name = L"m_tbpPacketFlood";
			this->m_tbpPacketFlood->Padding = System::Windows::Forms::Padding(4);
			this->m_tbpPacketFlood->Size = System::Drawing::Size(482, 413);
			this->m_tbpPacketFlood->TabIndex = 0;
			this->m_tbpPacketFlood->Text = L"Packet Flood";
			this->m_tbpPacketFlood->ToolTipText = L"Create a packet flood";
			// 
			// m_lblStatus
			// 
			this->m_lblStatus->Location = System::Drawing::Point(5, 387);
			this->m_lblStatus->Margin = System::Windows::Forms::Padding(0);
			this->m_lblStatus->Name = L"m_lblStatus";
			this->m_lblStatus->Size = System::Drawing::Size(395, 21);
			this->m_lblStatus->TabIndex = 0;
			this->m_lblStatus->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// m_pbrWork
			// 
			this->m_pbrWork->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->m_pbrWork->Location = System::Drawing::Point(280, 38);
			this->m_pbrWork->Margin = System::Windows::Forms::Padding(0);
			this->m_pbrWork->Name = L"m_pbrWork";
			this->m_pbrWork->Size = System::Drawing::Size(193, 15);
			this->m_pbrWork->Step = 1;
			this->m_pbrWork->Style = System::Windows::Forms::ProgressBarStyle::Continuous;
			this->m_pbrWork->TabIndex = 0;
			// 
			// m_btnStart
			// 
			this->m_btnStart->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->m_btnStart->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_btnStart.Image")));
			this->m_btnStart->Location = System::Drawing::Point(403, 385);
			this->m_btnStart->Margin = System::Windows::Forms::Padding(0);
			this->m_btnStart->Name = L"m_btnStart";
			this->m_btnStart->Size = System::Drawing::Size(75, 25);
			this->m_btnStart->TabIndex = 0;
			this->m_btnStart->TabStop = false;
			this->m_btnStart->Text = L"Start";
			this->m_btnStart->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->m_ttpToolTip->SetToolTip(this->m_btnStart, L"Click here to start the flood");
			this->m_btnStart->UseVisualStyleBackColor = true;
			this->m_btnStart->Click += gcnew System::EventHandler(this, &ZFloodControl::OnStartClick);
			// 
			// m_txtPackets
			// 
			this->m_txtPackets->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->m_txtPackets->Location = System::Drawing::Point(5, 65);
			this->m_txtPackets->Margin = System::Windows::Forms::Padding(0);
			this->m_txtPackets->MaxLength = 0;
			this->m_txtPackets->Multiline = true;
			this->m_txtPackets->Name = L"m_txtPackets";
			this->m_txtPackets->Size = System::Drawing::Size(472, 315);
			this->m_txtPackets->TabIndex = 0;
			this->m_txtPackets->TabStop = false;
			// 
			// m_nbrLimited
			// 
			this->m_nbrLimited->Enabled = false;
			this->m_nbrLimited->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, 0});
			this->m_nbrLimited->Location = System::Drawing::Point(135, 35);
			this->m_nbrLimited->Margin = System::Windows::Forms::Padding(0);
			this->m_nbrLimited->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1000000000, 0, 0, 0});
			this->m_nbrLimited->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, 0});
			this->m_nbrLimited->Name = L"m_nbrLimited";
			this->m_nbrLimited->Size = System::Drawing::Size(85, 21);
			this->m_nbrLimited->TabIndex = 0;
			this->m_nbrLimited->TabStop = false;
			this->m_nbrLimited->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->m_nbrLimited->ThousandsSeparator = true;
			this->m_ttpToolTip->SetToolTip(this->m_nbrLimited, L"Number of total packets to send");
			this->m_nbrLimited->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {500000, 0, 0, 0});
			// 
			// m_lblPackets
			// 
			this->m_lblPackets->Location = System::Drawing::Point(220, 35);
			this->m_lblPackets->Margin = System::Windows::Forms::Padding(0);
			this->m_lblPackets->Name = L"m_lblPackets";
			this->m_lblPackets->Size = System::Drawing::Size(60, 21);
			this->m_lblPackets->TabIndex = 6;
			this->m_lblPackets->Text = L"packets";
			this->m_lblPackets->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// m_rdiRandom
			// 
			this->m_rdiRandom->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->m_rdiRandom->Location = System::Drawing::Point(383, 5);
			this->m_rdiRandom->Margin = System::Windows::Forms::Padding(0);
			this->m_rdiRandom->Name = L"m_rdiRandom";
			this->m_rdiRandom->Size = System::Drawing::Size(95, 21);
			this->m_rdiRandom->TabIndex = 0;
			this->m_rdiRandom->Text = L"Randomized";
			this->m_ttpToolTip->SetToolTip(this->m_rdiRandom, L"Packets will be sent in a randomized order");
			this->m_rdiRandom->UseVisualStyleBackColor = true;
			// 
			// m_rdiCounter
			// 
			this->m_rdiCounter->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->m_rdiCounter->Checked = true;
			this->m_rdiCounter->Location = System::Drawing::Point(283, 5);
			this->m_rdiCounter->Margin = System::Windows::Forms::Padding(0);
			this->m_rdiCounter->Name = L"m_rdiCounter";
			this->m_rdiCounter->Size = System::Drawing::Size(95, 21);
			this->m_rdiCounter->TabIndex = 0;
			this->m_rdiCounter->TabStop = true;
			this->m_rdiCounter->Text = L"Incremental";
			this->m_ttpToolTip->SetToolTip(this->m_rdiCounter, L"Packets will be sent in the order they appear in the input field");
			this->m_rdiCounter->UseVisualStyleBackColor = true;
			// 
			// m_lblSeries
			// 
			this->m_lblSeries->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->m_lblSeries->Location = System::Drawing::Point(223, 5);
			this->m_lblSeries->Margin = System::Windows::Forms::Padding(0);
			this->m_lblSeries->Name = L"m_lblSeries";
			this->m_lblSeries->Size = System::Drawing::Size(60, 21);
			this->m_lblSeries->TabIndex = 3;
			this->m_lblSeries->Text = L"Series";
			this->m_lblSeries->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// m_chxSetPacketLimit
			// 
			this->m_chxSetPacketLimit->Location = System::Drawing::Point(10, 35);
			this->m_chxSetPacketLimit->Margin = System::Windows::Forms::Padding(0);
			this->m_chxSetPacketLimit->Name = L"m_chxSetPacketLimit";
			this->m_chxSetPacketLimit->Size = System::Drawing::Size(125, 21);
			this->m_chxSetPacketLimit->TabIndex = 0;
			this->m_chxSetPacketLimit->TabStop = false;
			this->m_chxSetPacketLimit->Text = L"Set Packet Limit";
			this->m_ttpToolTip->SetToolTip(this->m_chxSetPacketLimit, L"Enable a packet limit on the flood");
			this->m_chxSetPacketLimit->UseVisualStyleBackColor = true;
			this->m_chxSetPacketLimit->CheckedChanged += gcnew System::EventHandler(this, &ZFloodControl::OnSetPacketLimitCheckedChanged);
			// 
			// m_lblMilliseconds
			// 
			this->m_lblMilliseconds->Location = System::Drawing::Point(135, 5);
			this->m_lblMilliseconds->Margin = System::Windows::Forms::Padding(0);
			this->m_lblMilliseconds->Name = L"m_lblMilliseconds";
			this->m_lblMilliseconds->Size = System::Drawing::Size(80, 21);
			this->m_lblMilliseconds->TabIndex = 0;
			this->m_lblMilliseconds->Text = L"milliseconds";
			this->m_lblMilliseconds->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// m_nbrInterval
			// 
			this->m_nbrInterval->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, 0});
			this->m_nbrInterval->Location = System::Drawing::Point(50, 5);
			this->m_nbrInterval->Margin = System::Windows::Forms::Padding(0);
			this->m_nbrInterval->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {3600000, 0, 0, 0});
			this->m_nbrInterval->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, 0});
			this->m_nbrInterval->Name = L"m_nbrInterval";
			this->m_nbrInterval->Size = System::Drawing::Size(85, 21);
			this->m_nbrInterval->TabIndex = 0;
			this->m_nbrInterval->TabStop = false;
			this->m_nbrInterval->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->m_ttpToolTip->SetToolTip(this->m_nbrInterval, L"Packet will be sent at this interval");
			this->m_nbrInterval->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, 0});
			// 
			// m_lblEvery
			// 
			this->m_lblEvery->Location = System::Drawing::Point(5, 5);
			this->m_lblEvery->Margin = System::Windows::Forms::Padding(0);
			this->m_lblEvery->Name = L"m_lblEvery";
			this->m_lblEvery->Size = System::Drawing::Size(45, 21);
			this->m_lblEvery->TabIndex = 0;
			this->m_lblEvery->Text = L"Every";
			this->m_lblEvery->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// m_tbpProtector
			// 
			this->m_tbpProtector->BackColor = System::Drawing::Color::White;
			this->m_tbpProtector->ImageIndex = 1;
			this->m_tbpProtector->Location = System::Drawing::Point(4, 23);
			this->m_tbpProtector->Name = L"m_tbpProtector";
			this->m_tbpProtector->Padding = System::Windows::Forms::Padding(3);
			this->m_tbpProtector->Size = System::Drawing::Size(482, 413);
			this->m_tbpProtector->TabIndex = 1;
			this->m_tbpProtector->Text = L"Spam Protection";
			this->m_tbpProtector->ToolTipText = L"Protect yourself from packet floods (not available)";
			// 
			// m_lstTabImages
			// 
			this->m_lstTabImages->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"m_lstTabImages.ImageStream")));
			this->m_lstTabImages->TransparentColor = System::Drawing::Color::Transparent;
			this->m_lstTabImages->Images->SetKeyName(0, L"cloud_comment.png");
			this->m_lstTabImages->Images->SetKeyName(1, L"protection.png");
			// 
			// ZFloodControl
			// 
			this->ClientSize = System::Drawing::Size(498, 448);
			this->Controls->Add(this->m_tbContainer);
			this->Font = (gcnew System::Drawing::Font(L"Verdana", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->MinimumSize = System::Drawing::Size(506, 475);
			this->Name = L"ZFloodControl";
			this->Padding = System::Windows::Forms::Padding(4);
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->Text = L"Z - Flood Control";
			this->m_tbContainer->ResumeLayout(false);
			this->m_tbpPacketFlood->ResumeLayout(false);
			this->m_tbpPacketFlood->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->m_nbrLimited))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->m_nbrInterval))->EndInit();
			this->ResumeLayout(false);

		}

#pragma endregion
	
	void OnTabSelecting ( Object^ sender, TabControlCancelEventArgs^ e );
	
	void OnSetPacketLimitCheckedChanged ( Object^ sender, EventArgs^ e );
	
	void OnStartClick ( Object^  sender, EventArgs^ e );
};
}

#endif /* __ZFloodControl_h__ */
