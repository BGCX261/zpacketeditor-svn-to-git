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
#include "Windows.h"

/* Display a system-formatted error message */
void Error ( __in_z ::LPCTSTR lpszProc )
{
#if _DEBUG
	/* Get the last error code set by the system */
	::DWORD dwMessageId = ::GetLastError();

	/* If an error did occur... */
	if ( dwMessageId != NO_ERROR ) {
		::LPVOID lpvBuffer = NULL;

		/*
		 * Get the error message for the specified erro code from the
		 * system's message table.
		 */
		if ( ::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL, dwMessageId, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpvBuffer, 0, NULL) == 0 ) {
			/*
			 * If we failed to get get the system's message then
			 * display a generalized error message
			 */
			::MessageBox(NULL, TEXT("An error has occured as a result of system function call."), lpszProc,
				MB_OK | MB_ICONERROR | MB_APPLMODAL | MB_SETFOREGROUND);
		} else {
			::MessageBox(NULL, (::LPTSTR)lpvBuffer, lpszProc,
				MB_OK | MB_ICONERROR | MB_APPLMODAL | MB_SETFOREGROUND);
		}

		/* Release the memory allocated by FormatMessage */
		if ( lpvBuffer != NULL )
			::LocalFree((::HLOCAL)lpvBuffer);
	}
#endif /* _DEBUG */
}

/* Create a hook for the MapleStory recv function */
extern bool CreateRecvHook ( void );
/* Create a hook for the MapleStory send function */
extern bool CreateSendHook ( void );
/* Managed code entry point */
extern void Main ( void );

bool bIsRecvHooked = false;
bool bIsSendHooked = false;

/* Our initial program thread */
::BOOL WINAPI DllWork ( __in ::HMODULE hModule )
{
	bIsRecvHooked = CreateRecvHook();
	bIsSendHooked = CreateSendHook();

	/*
	 * If we were able to hook either the MapleStory
	 * receive or send function then create the UI.
	 */
	if ( bIsRecvHooked || bIsSendHooked ) {
		Main();
	} else {
		/* Display an error message if we were unable to hook the I/O routines. */
		::MessageBox(NULL, TEXT("Could not hook the required MapleStory functions"), TEXT("Z Packet Editor"),
			MB_OK | MB_ICONERROR | MB_APPLMODAL | MB_SETFOREGROUND);
	}

	::FreeLibraryAndExitThread(hModule, EXIT_SUCCESS);
	return TRUE;
}

/* DLL entry point */
::BOOL WINAPI DllMain ( __in ::HMODULE hModule, __in ::DWORD dwReason, __in __reserved ::LPVOID lpvReserved )
{
	UNREFERENCED_PARAMETER(lpvReserved);

	/* 
	 * Handle DLL_PROCESS_ATTACH; this is handled when
	 * the DLL is first linked to (inject) in the game's
	 * process.
	 */
	if ( dwReason == DLL_PROCESS_ATTACH ) {
		/*
		 * Remove ourselves from the notification list for
		 * the process's thread-related events.
		 */
		if ( ::DisableThreadLibraryCalls(hModule) == FALSE )
			Error(TEXT("DisableThreadLibraryCalls"));

		::HANDLE hThread = NULL;

		/* Create our initial program thread */
		if ( ( hThread = ::CreateThread(NULL, 0, (::LPTHREAD_START_ROUTINE)DllWork, (::HMODULE)hModule, 0, NULL) ) == NULL ) {
			Error(TEXT("CreateThread"));
			return FALSE;
		}

		/* Close our handle to the created thread. */
		if ( ::CloseHandle(hThread) == FALSE )
			Error(TEXT("CloseHandle"));
	}

	return TRUE;
}
