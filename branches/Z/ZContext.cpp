#include "Z.h"
#include "Z_CLI.h"
#include "Z_GUI.h"

using namespace Z;
using namespace System::IO;

/* Constructor */
ZContext::ZContext ( ZApplication^ window ) : ApplicationContext(window)
{
	this->Application = window;

	/* Z- Memory Manager */
	this->Memory = gcnew ZMemoryManager;
	this->AttachChild(this->Memory);	
	/* Z - Template Manager */
	this->Templates = gcnew ZTemplateManager;
	this->AttachChild(this->Templates);	
	/* Z- Packet Builder */
	this->PacketBuilder = gcnew ZPacketBuilder;
	this->AttachChild(this->PacketBuilder);	
	/* Blocked received packets */
	this->BlockedRecvPatterns = gcnew ZPatternManager(L"Blocked Packets (recv)");
	this->AttachChild(this->BlockedRecvPatterns);
	/* Ignored received packets */
	this->IgnoredRecvPatterns = gcnew ZPatternManager(L"Ignored Packets (recv)");
	this->AttachChild(this->IgnoredRecvPatterns);	
	/* Blocked sent packets */
	this->BlockedSendPatterns = gcnew ZPatternManager(L"Blocked Packets (send)");
	this->AttachChild(this->BlockedSendPatterns);	
	/* Ignored sent packets */
	this->IgnoredSendPatterns = gcnew ZPatternManager(L"Ignored Packets (send)");
	this->AttachChild(this->IgnoredSendPatterns);
	/* Common used patterns */
	this->UserCreatedPatterns = gcnew ZPatternManager(L"Custom");
	this->AttachChild(this->UserCreatedPatterns);

	this->Collections = gcnew array<ZCollection^>(Z_COLLECTION_COUNT + 2);
	/* Favorites */
	this->Collections[0] = gcnew ZCollection(L"Favorites");
	/* Filter Results */
	this->Collections[1] = gcnew ZCollection(L"Filter Results");

	for ( int i = 2; i < this->Collections->Length; i++ )
		this->Collections[i] = gcnew ZCollection(String::Format("Group {0}", ( i - 1 )));

	for ( int i = 0; i < this->Collections->Length; i++ )
		this->AttachChild(this->Collections[i]);

	/* Packet Floods */
	this->FloodControl = gcnew ZFloodControl;
	this->AttachChild(this->FloodControl);	
	/* Help > About */
	this->About = gcnew ZAbout;
	this->AttachChild(this->About);

	G = this;
}

/* Destructor */
ZContext::~ZContext ( void )
{
	this->MainForm->Close();
}

/* Child form is first shown  */
void ZContext::FormShownEvent ( Object^ sender, EventArgs^ e )
{
	if ( ::SetProcessWorkingSetSize(::GetCurrentProcess(), (::SIZE_T)( -1 ), (::SIZE_T)( -1 )) != TRUE )
		Error(TEXT("SetProcessWorkingSetSize"));
}

/* Child form is being closed */
void ZContext::FormCloseEvent ( Object^ sender, CancelEventArgs^ e )
{
	Form^ form = nullptr;

	if ( ( form = dynamic_cast<Form^>(sender) ) != nullptr )
		form->Hide();

	e->Cancel = true;
}

/* Attach a child form to the MainForm and attach the required event handlers */
void ZContext::AttachChild ( Form^ form )
{
	form->Owner    = this->MainForm;
	form->Closing += gcnew CancelEventHandler(&ZContext::FormCloseEvent);
	form->Shown   += gcnew EventHandler(&ZContext::FormShownEvent);
}
