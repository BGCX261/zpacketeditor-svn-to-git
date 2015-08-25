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
#include "ZPEPacket.h"

/* Is pattern matched */
__inline bool IsPatternMatched ( __in ::LPBYTE lpBytes, __in ::LPBYTE lpPattern, __in_z ::LPCSTR lpszPattern )
{
	/*
	 * Iterate over the array lpBytes using lpszPattern to determine
	 * when the end of the pattern is reached.
	 */
	for ( ; *lpszPattern; ++lpszPattern, ++lpBytes, ++lpPattern ) {
		/*
		 * If the current position in the pattern is not a wildcard
		 * determine if it is a match against the current byte in
		 * the pattern.
		 */
		if ( ( *lpszPattern != '?' ) && ( *lpBytes != *lpPattern ) )
			return false;
	}

	/* The pattern has been found if we've reached the end of lpszPattern */
	return ( *lpszPattern == NULL );
}

/* An invalid address in memory */
#define INVALID_ADDRESS (::DWORD)( -1 )

/* Retrieve an address based on a matched pattern */
::DWORD FindPattern ( __in ::LPBYTE lpPattern, __in_z ::LPCSTR lpszPattern, __in ::INT nOffset )
{
	/*
	 * Base address to begin searching from.
	 *
	 * This function is commonly used in many hacks for
	 * MapleStory, and it is commonly redundant. I've modified
	 * the FindPattern code so that it pragmatically uses
	 * the base loading address of the process (GetModuleHandle).
	 */
	static const ::DWORD dwBase = (::DWORD)GetModuleHandle(NULL);
	/*
	 * The number of bytes to search through.
	 * Though 0x00FFFFFF may seem like a large number, it really
	 * doesn't matter. The iteration of the process memory occurs
	 * at such a high speed that even if the full area of memory
	 * were searched it would take only milliseconds.
	 */
	static const ::DWORD dwSize = 0x00FFFFFF;

	/*
	 * We execute the search inside a try,except block so that
	 * we can fail gracefully in the case that an exception is
	 * thrown.
	 */
	__try {
		for ( ::DWORD n = 0; n < dwSize; n++ ) {
			/* Test the bytes at offset n, against our pattern */
			if ( IsPatternMatched((::LPBYTE)( dwBase + n ), lpPattern, lpszPattern) )
				return (::DWORD)( dwBase + n + nOffset );
		}
	} __except (EXCEPTION_EXECUTE_HANDLER) {
	}

	/* No address found. */
	return INVALID_ADDRESS;
}

/*
 * Create a function hook that hooks the function at address dwSource
 * to the function at address dwTarget. If dwNops is a value greater
 * than 0, a series of NOP (0x90) opcodes are written to the end
 */
__inline bool Hook ( __in ::DWORD dwSource, __in ::DWORD dwTarget, __in ::DWORD dwNops, __in bool bJump )
{
	/*
	 * Install function hook inside a try,except block so
	 * that we can fail gracefully in case this causes an
	 * exception.
	 */
	__try {
		/*
		 * Verify that dwSource is not a function that
		 * was previously hooked
		 */
		if ( bJump && ( *(::LPBYTE)dwSource == 0xE9 ) )
			return false;

		/* Unused, but contains the access of the area of memory prior to our call */
		::DWORD flOldProtect;

		if ( ::VirtualProtect((::LPVOID)dwSource, dwNops + 5, PAGE_EXECUTE_READWRITE, & flOldProtect) == FALSE ) {
			Error(TEXT("VirtualProtect"));
			return false;
		}

		/* Rewrite the first opcode as either a CALL or JMP instruction */
		*(::LPBYTE)dwSource = bJump ? 0xE9 : 0xE8;
		/* Set the jump adress to dwTarget */
		*(::LPDWORD)( dwSource + 1 ) = ( (::INT)dwTarget - (::INT)dwSource ) - 5;

		/*
		 * If dwNops is greater than 0, then we write a series of
		 * NOP opcodes to the end of the hook
		 */
		if ( dwNops > 0 ) {
			for ( ::DWORD i = 0; i < dwNops; i++ )
				*(::LPBYTE)( dwSource + i + 5 ) = 0x90;
		}

		/* A function hook has successfully been created */
		return true;
	} __except (EXCEPTION_EXECUTE_HANDLER) {
	}

	/* Failed to create a function hook */
	return false;
}

/*
 * This variable is just a buffer that stores a pointer
 * to MapleStory's received packet.
 *
 * Be careful when handling it since any changes made to
 * the object pointed at by it, are reflected in the game's
 * copy of the same packet.
 */
PACKET* pRecvPacket;

/* An event handler of sorts. This is called inside our hook */
void RecvPacketEvent ( void )
{
	/* Create a new ZPEPacket object */
	ZPEPacket* pPacket = new ZPEPacket(pRecvPacket, ZPE_PACKET_ATTRIBUTE_RECV);

	/* Send this packet to the UI */
	pPacket->Dispatch();
	/* Delete the packet object (this does not delete the actual packet) */
	delete pPacket;
}

/* Our MapleStory receive hook */
void __declspec(naked) WINAPI NewMapleStoryRecv ( void )
{
	/* Using eax as a place holder, we use the value in
	 * the EBP register and subtract 12 from it to get the
	 * address of the pointer for the received packet.
	 */
	__asm
	{
		push eax
		mov  eax,ebp
		sub  eax,0x0C
		mov  [pRecvPacket],eax
		pop  eax
		pushad
		call RecvPacketEvent
		popad
		pop  esi
		pop  ebx
		leave
		ret  0x04
	}
}

bool CreateRecvHook ( void )
{
	/* MapleStory's recv function (AoB) */
	::LPCSTR lpszPattern = "\x5F\x5E\x5B\xC9\xC2\x04\x00\xB8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x83\xEC\x00\x53\x56\x57\x33";

	__try {
		/* The address of the MapleStory recv function */
		::DWORD dwMapleStoryRecv = FindPattern((::LPBYTE)lpszPattern, "xxxxxxxx???xx???xxx?xxxx", 1);

		if ( dwMapleStoryRecv == INVALID_ADDRESS )
			return false;

		/* Install our hook */
		return Hook(dwMapleStoryRecv, (::DWORD)NewMapleStoryRecv, 0, true);
	} __except (EXCEPTION_EXECUTE_HANDLER) {
	}

	return false;
}

/*
 * The address of the class that contains MapleStory's
 * send function.
 *
 * This is only needed for sending packets, not for hooking
 * the function that send's them. This value is actually just
 * the first argument pushed on the stack when send is called
 * because that function uses C++'s __thiscall calling convention.
 */
::DWORD dwMapleStorySendClass  = INVALID_ADDRESS;
/* The address of the MapleStory's send function */
::DWORD dwMapleStorySend       = INVALID_ADDRESS;
/* The address of the MapleStory's send function (the original send) */
::DWORD dwMapleStorySendReturn = INVALID_ADDRESS;

/*
 * This variable is just a buffer that stores a pointer
 * to MapleStory's sent packet.
 *
 * Be careful when handling it since any changes made to
 * the object pointed at by it, are reflected in the game's
 * copy of the same packet.
 */
SEND_PACKET* pSendPacket;

/* An event handler of sorts. This is called inside our hook */
bool SendPacketEvent ( void )
{
	/* Create a ZPEPacket object */
	ZPEPacket* pPacket = new ZPEPacket(pSendPacket, ZPE_PACKET_ATTRIBUTE_SEND);
	/* Send this packet to the UI */
	bool retval = pPacket->Dispatch();
	
	/* Delete the packet object (this does not delete the actual packet) */
	delete pPacket;
	/* Return true if the packet was blocked */
	return retval;
}

/* Our MapleStory send hook */
void __declspec(naked) WINAPI NewMapleStorySend ( void )
{
	/*
	 * Store the value in the ESP register as the address of the
	 * object pointed at by pSendPacket. Then we jump to the address
	 * of the original MapleStory send call.
	 */
	__asm
	{
		mov [pSendPacket],esp
		pushad
		call SendPacketEvent
		popad
		jmp  dword ptr [dwMapleStorySendReturn]
	}
}

bool CreateSendHook ( void )
{
	/* MapleStory Send Class AoB  */
	static ::LPCSTR lpszSendClassPattern  = "\x8B\x0D\x00\x00\x00\x00\x83\x65\x00\x00\x8D\x45\x00\x50\xE8\x00\x00\x00\x00\x83\x4D\x00\x00\x8D\x4D\x00\xC7\x46";
	/* MapleStory Send Method AoB */
	static ::LPCSTR lpszSendMethodPattern = "\xB8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x51\x56\x57\x8B\xF9\x8D\x77\x00\x8B\xCE\x89\x00\x00\xE8\x00\x00\x00\x00\x8B\x47";
	
	__try {
		dwMapleStorySend = FindPattern((::LPBYTE)lpszSendMethodPattern, "x???xx???xxxxxxxx?xxx??x????xx", 0);

		if ( dwMapleStorySend == INVALID_ADDRESS )
			return false;

		dwMapleStorySendReturn = dwMapleStorySend + 5;
		dwMapleStorySendClass  = FindPattern((::LPBYTE)lpszSendClassPattern, "xx????xx??xx?xx????xx??xx?xx", 2);

		if ( dwMapleStorySendClass != INVALID_ADDRESS )
			dwMapleStorySendClass = *(::PDWORD)dwMapleStorySendClass;

		return Hook(dwMapleStorySend, (::DWORD)NewMapleStorySend, 0, true);
	} __except (EXCEPTION_EXECUTE_HANDLER) {
	}

	return false;
}

/* MapleStory Send method signature */
typedef ::DWORD ( WINAPI *PFNSENDPACKET ) ( __in PACKET* ppPacket );

::DWORD WINAPI SendPacket ( __in_bcount(dwLength) ::LPBYTE lpBytes, __in ::DWORD dwLength )
{
	/*
	 * This creates a function pointer to the MapleStory send function.
	 * If you want to intercept the packets that are injected then this
	 * should point to dwMapleStorySend; if you don't want to intercept
	 * packets that you inject then this should point to the original
	 * send function (dwMapleStorySendReturn).
	 */
	static const PFNSENDPACKET pfnSendPacket = (PFNSENDPACKET)dwMapleStorySend;

	/* The packet structure */
	PACKET pPacket;

	/* Clear all the bytes */
	ZeroMemory(&pPacket, sizeof(PACKET));

	pPacket.lpBytes  = lpBytes;
	pPacket.dwLength = dwLength;

	__try {
		/* We move the address of the class containing the send function
		 * into the ECX register so that it is passed at the *this pointer
		 * when the call is made. See documentation on the __thiscall calling
		 * convention for more information.
		 */
		__asm
		{
			mov ecx,dwMapleStorySendClass
			mov ecx,[ecx]
		}
		/* Call the MapleStory send function with our packet as the argument */
		pfnSendPacket(&pPacket);
	} __except (EXCEPTION_EXECUTE_HANDLER) {
	}
}
