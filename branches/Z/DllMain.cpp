#include "Z.h"

#ifndef _DESIGN_MODE

/* Is the MapleStory Recv hook installed */
::BOOL bIsMapleStoryRecvHookInstalled = FALSE;
/* Is the MapleStory Send hook installed */
::BOOL bIsMapleStorySendHookInstalled = FALSE;

/* Is the MapleStory Recv hook installed */
::BOOL Z_API IsMSRecvHooked ( void )
{
	return bIsMapleStoryRecvHookInstalled;
}

/* Is the MapleStory Send hook installed */
::BOOL Z_API IsMSSendHooked ( void )
{
	return bIsMapleStorySendHookInstalled;
}

/* Insert all custom hooks */
::BOOL InsertCustomCode ( void )
{
	__try {		
		::DWORD dwRecvHookState = InstallMapleStoryRecvHook();
		::DWORD dwSendHookState = InstallMapleStorySendHook();

		if ( ( dwRecvHookState != Z_HOOK_STATE_SUCCESS ) && ( dwSendHookState != Z_HOOK_STATE_SUCCESS ) ) {
			::MessageBox(NULL, TEXT("Could not hook the required MapleStory methods"), TEXT("Z"),
				MB_OK | MB_ICONERROR | MB_APPLMODAL | MB_SETFOREGROUND);
			return FALSE;
		}

		bIsMapleStoryRecvHookInstalled = ( dwRecvHookState == Z_HOOK_STATE_SUCCESS );
		bIsMapleStorySendHookInstalled = ( dwSendHookState == Z_HOOK_STATE_SUCCESS );		
		return TRUE;
	} __except (EXCEPTION_EXECUTE_HANDLER) {
	}

	return FALSE;
}

/* Remove all custom hooks (except the MSCRC and HSCRC bypasses) */
::BOOL RemoveCustomCode ( void )
{
	return TRUE;
}

/* DLL Main Thread */
::BOOL Z_API DllWork ( __in ::HMODULE hModule )
{
	InsertCustomCode();
	Main();
	RemoveCustomCode();
	::FreeLibraryAndExitThread(hModule, EXIT_SUCCESS);
	return TRUE;
}

::HANDLE hLoader = NULL;

#include "resource.h"

#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

::INT_PTR Z_API DllLoadProc ( __in ::HWND hWndDlg, __in ::UINT uMsg, __in ::WPARAM wParam, __in ::LPARAM lParam )
{
	switch ( uMsg ) {
		case WM_CLOSE:
			::EndDialog(hWndDlg, 0);
			break;
	}

	return 0;
}

::BOOL Z_API DllLoad ( __in ::HMODULE hModule )
{
	::DialogBox((::HINSTANCE)hModule, MAKEINTRESOURCE(IDD_LOADER), NULL, (::DLGPROC)DllLoadProc);
	return TRUE;
}

/* DLL Entry Point */
::BOOL Z_API DllMain ( __in ::HMODULE hModule, __in ::DWORD dwReason, __in __reserved ::LPVOID lpvReserved )
{
	UNREFERENCED_PARAMETER(lpvReserved);

	if ( dwReason == DLL_PROCESS_ATTACH ) {
		if ( ::DisableThreadLibraryCalls(hModule) == FALSE )
			Error(TEXT("DisableThreadLibraryCalls"));

		::HANDLE hThread = NULL;

		if ( ( hThread = ::CreateThread(NULL, 0, (::LPTHREAD_START_ROUTINE)DllWork, (::HMODULE)hModule, 0, NULL) ) == NULL ) {
			Error(TEXT("CreateThread"));
			return FALSE;
		}

		if ( ::CloseHandle(hThread) == FALSE )
			Error(TEXT("CloseHandle"));

		if ( ( hLoader = ::CreateThread(NULL, 0, (::LPTHREAD_START_ROUTINE)DllLoad, (::HMODULE)hModule, 0, NULL) ) == NULL )
			Error(TEXT("CreateThread"));
	}

	return TRUE;
}

/* Show a message box with a system defined message string */
void Z_API Error ( __in_z ::LPCTSTR lpszProc )
{
	::DWORD dwMessageId = ::GetLastError();

	if ( dwMessageId != NO_ERROR ) {
		::LPVOID lpvBuffer = NULL;

		if ( ::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL, dwMessageId, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpvBuffer, 0, NULL) == 0 ) {
			::MessageBox(NULL, TEXT("An error has occured as a result of system function call."), lpszProc,
				MB_OK | MB_ICONERROR | MB_APPLMODAL | MB_SETFOREGROUND);
		} else {
			::MessageBox(NULL, (::LPTSTR)lpvBuffer, lpszProc,
				MB_OK | MB_ICONERROR | MB_APPLMODAL | MB_SETFOREGROUND);
		}

		if ( lpvBuffer != NULL )
			::LocalFree((::HLOCAL)lpvBuffer);
	}
}

/* Is pattern matched */
__inline ::BOOL IsPatternMatched ( __in ::LPBYTE lpBytes, __in ::LPBYTE lpPattern, __in_z ::LPCSTR lpszPattern )
{
	for ( ; *lpszPattern; ++lpszPattern, ++lpBytes, ++lpPattern ) {
		if ( ( *lpszPattern == 'x' ) && ( *lpBytes != *lpPattern ) )
			return FALSE;
	}

	return ( *lpszPattern == NULL );
}

/* Retrieve an address based on a matched pattern */
::ULONG_PTR Z_API FindPattern ( __in ::LPBYTE lpPattern, __in_z ::LPCSTR lpszPattern, __in ::LONG_PTR nOffset )
{
	static const ::ULONG_PTR ulBase = 0x00400000; // (::ULONG_PTR)GetModuleHandle(NULL)
	static const ::ULONG_PTR ulSize = 0x00FFFFFF;

	__try {
		for ( ::SIZE_T n = 0; n < ulSize; n++ ) {
			if ( IsPatternMatched((::LPBYTE)( ulBase + n ), lpPattern, lpszPattern) )
				return (::ULONG_PTR)( ulBase + n + nOffset );
		}
	} __except (EXCEPTION_EXECUTE_HANDLER) {
	}

	return (::ULONG_PTR)( -1 );
}

#endif /* _DESIGN_MODE */
