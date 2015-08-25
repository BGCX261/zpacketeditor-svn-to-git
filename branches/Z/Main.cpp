#include "Z.h"
#include "Z_CLI.h"
#include "Z_GUI.h"

::BOOL bExitProcess = FALSE;

void Z_EXIT ExitProcessFast ( void )
{
	if ( ::TerminateProcess(::GetCurrentProcess(), EXIT_SUCCESS) == FALSE )
		::ExitProcess(EXIT_SUCCESS);
}

#ifndef _DESIGN_MODE

void Main ( void )
{
	using namespace Z;
	using namespace System::Windows::Forms;

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew ZContext(gcnew ZApplication));
	Application::Exit();

	if ( bExitProcess )
		ExitProcessFast();
}

#endif