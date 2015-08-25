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
#include "ZPE.h"
#include "ZPEWindow.h"
#include "ZPEContext.h"

/*
 * This file must be compiled with the /CLR and /EHa flags
 * set so that this file will be compiled as managed code.
 */

/* Localize the application namespace */
using namespace ZPE;

/*
* Managed code entry point; this is reached from DllMain
* through our main application thread that was created there.
*/
void Main ( void )
{
	/* Enable use of the visual styles on our UI controls */
	Application::EnableVisualStyles();
	/* Do not render text differently based on culture */
	Application::SetCompatibleTextRenderingDefault(false);
	/* 
	 * Initialize a new instance of our application context
	 * that will create and display the UI windows, and begin
	 * the message processing loop for each.
	 */
	Application::Run(gcnew ZPEContext);
	/* Exit the application UI thread. */
	Application::Exit();
}

/* Is the recv function hooked */
extern bool bIsRecvHooked;
/* Is the send function hooked */
extern bool bIsSendHooked;

ZPEContext::ZPEContext ( void )
{
	/*
	 * Create the windows for displaying packets that
	 * were received from MapleStory.
	 */
	if ( bIsRecvHooked ) {
		this->RecvPackets = gcnew ZPEWindow(L"Received Packets");
		this->RecvPackets->Closed += gcnew EventHandler(this, &ZPEContext::OnFormClosed);
		this->Count++;
	}

	/*
	 * Create the windows for displaying packets that
	 * were sent to MapleStory.
	 */
	if ( bIsSendHooked ) {
		this->SendPackets = gcnew ZPEWindow(L"Sent Packets");
		this->SendPackets->Closed += gcnew EventHandler(this, &ZPEContext::OnFormClosed);
		this->Count++;
	}

	/* Show the UI */
	this->RecvPackets->Show();
	this->SendPackets->Show();
	/* Set the singleton variable to this instance */
	G = this;
}

void ZPEContext::OnFormClosed ( Object^ sender, EventArgs^ e )
{
	/* Reduce the counter by 1 */
	this->Count -= 1;

	/*
	 * Both the received packets and sent packets windows
	 * have been closed, so we'll exit our UI thread.
	 */
	if ( this->Count < 1 )
		this->ExitThread();
}
