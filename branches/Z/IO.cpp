#include "Z.h"

/* Received packet */
PZ_PACKET ppRecvPacket;

/* Recv event handler */
void RecvPacketEvent ( void )
{
	ZPacket* packet = new ZPacket(ppRecvPacket, Z_PACKET_STREAM_RECEIVE);

	packet->Dispatch();
	delete packet;
}

/* MapleStory Recv hook */
void __declspec(naked) MSRecvHook ( void )
{
	__asm
	{
		lea    ebx,[ebp-0x0C]
		mov    ppRecvPacket,ebx
		pushad
		call   RecvPacketEvent
		popad
		pop    ebx
		leave
		ret    4
	}
}

/* MapleStory Recv method address */
ULONG_PTR ulMSRecvMethod;

/* Install the MapleStory Recv hook */
DWORD Z_API InstallMapleStoryRecvHook ( void )
{
	__try {
		/* 3b 2a d1 e9 58 ff ff ff 3b 8a ? ? ? ? 88 16 */
		ulMSRecvMethod = FindPattern((LPBYTE)"\x3B\x2A\xD1\xE9\x58\xFF\xFF\xFF\x3B\x8A\x00\x00\x00\x00\x88\x16",
			"xxxxxxxxxx????xx", 27);

		if ( ulMSRecvMethod == ((ULONG_PTR)(-1)) )
			return Z_HOOK_STATE_FAILURE;

		return Hook(ulMSRecvMethod, (ULONG_PTR)MSRecvHook, 0, TRUE);
	} __except(EXCEPTION_EXECUTE_HANDLER) {
	}

	return Z_HOOK_STATE_FAILURE;
}

/* Sent packet */
PZ_SEND_PACKET ppSendPacket;

/* Send event handler */
bool SendPacketEvent ( void )
{
	ZPacket* packet = new ZPacket(ppSendPacket, Z_PACKET_STREAM_SEND);	
	bool retval = packet->Dispatch();

	delete packet;	
	return retval;
}

/* MapleStory Send object address  */
DWORD dwMSSendObject;
/* MapleStory Send method address */
DWORD dwMSSendMethod;
/* MapleStory Send method return  */
DWORD dwMSSendReturn;

/* MapleStory Send hook */
void Z_ASM MSSendHook ( void )
{
	__asm
	{
		mov [ppSendPacket],esp
		pushad
		call SendPacketEvent
		popad
		jmp  dword ptr [dwMSSendReturn]
	}
}

/* MapleStory Send object address  */
ULONG_PTR ulMSSendObject;
/* MapleStory Send method address */
ULONG_PTR ulMSSendMethod;

/* Install the MapleStory Send hook */
DWORD Z_API InstallMapleStorySendHook ( void )
{
	/* MapleStory Send Class AoB  */
	static LPCSTR lpszSendObjectMask = "\x8B\x0D\x00\x00\x00\x00\x83\x65\x00\x00\x8D\x45\x00\x50\xE8\x00\x00\x00\x00\x83\x4D\x00\x00\x8D\x4D\x00\xC7\x46";
	/* MapleStory Send Method AoB */
	static LPCSTR lpszSendMethodMask = "\xB8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x51\x56\x57\x8B\xF9\x8D\x77\x00\x8B\xCE\x89\x00\x00\xE8\x00\x00\x00\x00\x8B\x47";
	
	__try {
		ulMSSendMethod = FindPattern((LPBYTE)lpszSendMethodMask, "x???xx???xxxxxxxx?xxx??x????xx", 0);

		if ( ulMSSendMethod == (ULONG_PTR)( -1 ) )
			return Z_HOOK_STATE_FAILURE;

		dwMSSendMethod = (DWORD)ulMSSendMethod;
		dwMSSendReturn = dwMSSendMethod + 5;
		ulMSSendObject = FindPattern((LPBYTE)lpszSendObjectMask, "xx????xx??xx?xx????xx??xx?xx", 2);

		if ( ulMSSendObject == (ULONG_PTR)( -1 ) )
			return Z_HOOK_STATE_FAILURE;

		dwMSSendObject = *(PDWORD)ulMSSendObject;
		return Hook(ulMSSendMethod, (ULONG_PTR)MSSendHook, 0, TRUE);
	} __except (EXCEPTION_EXECUTE_HANDLER) {
	}

	return Z_HOOK_STATE_FAILURE;
}

/* MapleStory Send method signature */
typedef BOOL ( Z_API *PFNSENDPACKET ) ( __in PZ_PACKET ppPacket );

/* Send a MapleStory packet using byte data */
DWORD Z_API SendPacket ( __in_bcount(nLength) LPBYTE lpBytes, __in DWORD dwLength )
{
	static PFNSENDPACKET pfnSendPacket = (PFNSENDPACKET)dwMSSendMethod;

	Z_PACKET pPacket;

	ZeroMemory(&pPacket, sizeof(Z_PACKET));

	pPacket.lpBytes  = lpBytes;
	pPacket.dwLength = dwLength;

	BOOL retval = FALSE;

	__try {
		__asm
		{
			mov ecx,dwMSSendObject
			mov ecx,[ecx]
		}
		retval = pfnSendPacket(&pPacket);
	} __except (EXCEPTION_EXECUTE_HANDLER) {
	}

	return retval;
}
