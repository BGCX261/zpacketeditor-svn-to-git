#include "Z.h"
#include "Z_CLI.h"
#include "Z_GUI.h"

using namespace Z;
using namespace System::Collections;
using namespace System::Globalization;
using namespace System::Text;
using namespace System::Threading;

bool bRandom;
int  nDelay;
int  nLimit;
int  nCount;

void ZFloodControl::OnClosed ( EventArgs^ e )
{
	if ( this->m_thrThread != nullptr ) {
		try {
			this->m_thrThread->Abort();
		} catch ( Exception^ ) {
		}
	}

	__super::OnClosed(e);	
}

void ZFloodControl::OnTabSelecting ( Object^ sender, TabControlCancelEventArgs^ e )
{
	if ( e->TabPageIndex > 0 )
		e->Cancel = true;
}

void ZFloodControl::OnSetPacketLimitCheckedChanged ( Object^ sender, EventArgs^ e )
{
	this->m_nbrLimited->Enabled = this->m_chxSetPacketLimit->Checked;
}

delegate void SetStatusTextCaller ( String^ text );

void ZFloodControl::SetStatusText ( String^ text )
{
	if ( this->m_lblStatus->InvokeRequired ) {
		this->m_lblStatus->Invoke(gcnew SetStatusTextCaller(this, &ZFloodControl::SetStatusText), gcnew array<Object^>{ text });
	} else {
		this->m_lblStatus->Text = text;
	}

	if ( bRandom != true )
		this->m_pbrWork->PerformStep();
}

delegate void Caller ( void );

void ZFloodControl::CreateFlood ( void )
{
	if ( this->InvokeRequired ) {
		this->Invoke(gcnew Caller(this, &ZFloodControl::CreateFlood));
	} else {
		this->m_nbrInterval->Enabled = false;
		this->m_rdiCounter->Enabled  = false;
		this->m_rdiRandom->Enabled   = false;
		this->m_chxSetPacketLimit->Enabled = false;
		this->m_nbrLimited->Enabled  = false;
		this->m_txtPackets->Enabled  = false;
		this->m_pbrWork->Value       = 0;
		this->m_btnStart->Text       = L"Abort";
		this->m_btnStart->Tag        = true;

		bRandom = this->m_rdiRandom->Checked;
		nDelay  = ((int)(this->m_nbrInterval->Value));
		nLimit  = ( -1 );
		nCount  = 0;

		if ( this->m_chxSetPacketLimit->Checked ) {
			nLimit = ((int)(this->m_nbrLimited->Value));
			this->m_pbrWork->Style  = ProgressBarStyle::Continuous;
			this->m_pbrWork->Maximum = nLimit;
		} else {
			this->m_pbrWork->Style = ProgressBarStyle::Marquee;
			this->m_pbrWork->Value = 10;
		}
	}
}

void ZFloodControl::FinishFlood ( void )
{
	if ( this->InvokeRequired ) {
		this->Invoke(gcnew Caller(this, &ZFloodControl::FinishFlood));
	} else {
		this->m_Collection->Clear();

		this->m_nbrInterval->Enabled = true;
		this->m_rdiCounter->Enabled  = true;
		this->m_rdiRandom->Enabled   = true;
		this->m_chxSetPacketLimit->Enabled = true;
		this->m_nbrLimited->Enabled  = true;
		this->m_txtPackets->Enabled  = true;
		this->m_pbrWork->Value = 0;
		this->m_pbrWork->Style = ProgressBarStyle::Continuous;
		this->m_btnStart->Text = L"Start";
		this->m_btnStart->Tag  = false;
	}
}

void ZFloodControl::OnStartClick ( Object^ sender, EventArgs^ e )
{
	if ( this->m_btnStart->Tag == nullptr )
		this->m_btnStart->Tag = false;

	if ( ((bool)(this->m_btnStart->Tag)) ) {
		if ( this->m_thrThread != nullptr ) {
			try {
				this->m_thrThread->Abort();
			} catch ( Exception^ ) {
			}

			this->m_thrThread = nullptr;
		}		
	} else {
		if ( this->m_txtPackets->Lines->Length > 0 ) {
			this->m_Collection->Clear();

			for each ( String^ line in this->m_txtPackets->Lines ) {
				if ( line->Length > 0 )
					this->m_Collection->Add(ZParser::GetByteCode(line));
			}

			if ( this->m_Collection->Contains(nullptr) ) {
				::MessageBox((::HWND)(::LPVOID)(this->Handle), TEXT("The packet input field must contain one or more packets in valid format"),
					TEXT("Z - Flood Control"), MB_OK | MB_ICONWARNING | MB_APPLMODAL | MB_SETFOREGROUND);
			} else {
				this->m_thrThread = gcnew Thread(gcnew ThreadStart(this, &ZFloodControl::FloodPackets));
				this->m_thrThread->IsBackground = true;

				this->m_thrThread->Start();
			}
		}
	}
}

String^ GetElapsedTime ( TimeSpan ts )
{
	StringBuilder^ sb = gcnew StringBuilder;

	if ( ts.Days > 0 )
		sb->AppendFormat(( ( ts.Hours > 1 ) ? L"{0} days, " : L"{0} day, " ), ts.Days);

	if ( ( ts.Days > 0 ) || ( ts.Hours > 0 ) )
		sb->AppendFormat(( ( ts.Hours > 1 ) ? L"{0} hrs, " : L"{0} hr, " ), ts.Hours);

	if ( ( ts.Days > 0 ) || ( ts.Hours > 0 ) || ( ts.Minutes > 0 ) )
		sb->AppendFormat(( ( ts.Minutes > 1 ) ? L"{0} mins, " : L"{0} min, " ), ts.Minutes);

	sb->AppendFormat("{0} s", ts.Seconds);
	return sb->ToString();
}

void ZFloodControl::FloodPackets ( void )
{
	Random^ r = gcnew Random;

	::DWORD	 dwOffset = 0;
	::DWORD  dwLength = 0;
	::LPBYTE lpBytes  = NULL;
	String^  rawBytes = nullptr;
	Stopwatch^ timer = Stopwatch::StartNew();

	this->CreateFlood();

	try {
		do {
			for ( int n = ( bRandom ? r->Next(0, this->m_Collection->Count) : 0 ); n < this->m_Collection->Count ; Thread::Sleep(nDelay) ) {
				this->SetStatusText(GetElapsedTime(timer->Elapsed));

				rawBytes = this->m_Collection[n];
				dwOffset = 0;
				dwLength = ( rawBytes->Length / 2 );
				lpBytes  = new ::BYTE [ dwLength ];

				for ( int i = 0; ( dwOffset < dwLength ) && ( ( i + 1 ) < rawBytes->Length ); dwOffset++, i += 2 )
					lpBytes[dwOffset] = Byte::Parse(rawBytes->Substring(i, 2), NumberStyles::HexNumber, CultureInfo::InvariantCulture);

				try {
					SendPacket(lpBytes, dwLength);
				} finally {
					delete [] lpBytes;
				}	

				if ( nLimit >= 0 )
					this->m_pbrWork->Invoke(gcnew Caller(this->m_pbrWork, &ProgressBar::PerformStep));

				n = ( bRandom ? r->Next(0, this->m_Collection->Count) : ( n + 1 ) );
			}
		} while ( ( nLimit < 0 ) || ( nCount++ < nLimit ) );
	} catch ( ThreadAbortException^ ) {
		Thread::ResetAbort();
	} finally {
		this->FinishFlood();
	}
}
