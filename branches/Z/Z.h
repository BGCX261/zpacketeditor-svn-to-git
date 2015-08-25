#ifndef __Z_h__
#define __Z_h__

#pragma once

#include "Windows.h"
#include "Strings.h"

void Main ( void );

/* Calling convention */
#define Z_API  WINAPI
/* Inline ASM */
#define Z_ASM  __declspec(naked)    Z_API
/* noreturn */
#define Z_EXIT __declspec(noreturn) Z_API

/* MapleStory regions */
enum MAPLESTORY_REGION
{
	MAPLESTORY_REGION_UNKNOWN, /* Unknown                */
	MAPLESTORY_REGION_EUROPE,  /* Europe                 */
	MAPLESTORY_REGION_GLOBAL   /* Global (North America) */
};

/* Return MapleStory region ID */
__inline DWORD Z_API GetMapleStoryRegion ( void )
{
	return MAPLESTORY_REGION_GLOBAL;
}

/* Show a message box with a system defined message string */
void Z_API Error ( __in_z ::LPCTSTR lpszProc );

/* Hook states */
enum Z_HOOK_STATE
{
	Z_HOOK_STATE_IGNORED = (::DWORD)( -1 ), /* Function is already hooked    */
	Z_HOOK_STATE_FAILURE = 0,               /* Failed to hook function       */
	Z_HOOK_STATE_SUCCESS = 1                /* Succeeded in hooking function */
};

/* Locate MSCRC bypass */
::BOOL Z_API LocateMapleStoryCRCRetn ( void );
/* Install MSCRC bypass */
::DWORD Z_API InstallMapleStoryCRCHook ( void );
/* Install HSCRC bypass */
::DWORD Z_API InstallHackShieldCRCHook ( void );

/* Get indirect pointer value */
__inline ::ULONG_PTR GetPtrValue ( __in ::PULONG_PTR pulBase, __in ::LONG_PTR nOffset )
{
	if ( !::IsBadReadPtr((::LPVOID)pulBase, sizeof(::ULONG_PTR)) && !::IsBadReadPtr((::LPVOID)( (*pulBase) + nOffset ), sizeof(::ULONG_PTR)) )
		return *(::PULONG_PTR)( (*pulBase) + nOffset );

	return (::ULONG_PTR)( -1 );
}

/* Set indirect pointer value */
__inline void SetPtrValue ( __in ::PULONG_PTR pulBase, __in ::LONG_PTR nOffset, __in ::ULONG_PTR ulValue )
{
	if ( !::IsBadWritePtr((::LPVOID)pulBase, sizeof(::ULONG_PTR)) && !::IsBadWritePtr((::LPVOID)( (*pulBase) + nOffset ), sizeof(::ULONG_PTR)) )
		*(::PULONG_PTR)( (*pulBase) + nOffset ) = ulValue;
}
/* Set indirect pointer value */
__inline void SetPtrValue ( __in ::PULONG_PTR pulBase, __in ::LONG_PTR nOffset, __in ::UINT32 uValue )
{
	if ( !::IsBadWritePtr((::LPVOID)pulBase, sizeof(::ULONG_PTR)) && !::IsBadWritePtr((::LPVOID)( (*pulBase) + nOffset ), sizeof(::ULONG_PTR)) )
		*(::PUINT32)( (*pulBase) + nOffset ) = uValue;
}
/* Set indirect pointer value */
__inline void SetPtrValue ( __in ::PULONG_PTR pulBase, __in ::LONG_PTR nOffset, __in ::UINT64 uValue )
{
	if ( !::IsBadWritePtr((::LPVOID)pulBase, sizeof(::ULONG_PTR)) && !::IsBadWritePtr((::LPVOID)( (*pulBase) + nOffset ), sizeof(::ULONG_PTR)) )
		*(::PUINT64)( (*pulBase) + nOffset ) = uValue;
}

/* Get the relative address offset from x to y */
#define JMP(x,y) ( ( (::INT)y - (::INT)x ) - 5 )

/* Hook subject to target */
__inline ::DWORD Hook ( ::ULONG_PTR subject, ::ULONG_PTR replace, ::ULONG_PTR NOPs, ::BOOL jump )
{
	__try {
		if ( jump && ( *(::LPBYTE)subject == 0xE9 ) )
			return Z_HOOK_STATE_IGNORED;

		::DWORD flOldProtect;

		if ( ::VirtualProtect((::LPVOID)subject, ( 5 + NOPs ), PAGE_EXECUTE_READWRITE, &flOldProtect) == FALSE ) {
			Error(TEXT("VirtualProtect"));
			return Z_HOOK_STATE_FAILURE;
		}

		*(::LPBYTE)subject = jump ? 0xE9 : 0xE8;
		*(::PDWORD)( subject + 1 ) = JMP(subject, replace);

		for ( ::SIZE_T n = 0; n < NOPs; n++ )
			*(::LPBYTE)( subject + n + 5 ) = 0x90;

		return Z_HOOK_STATE_SUCCESS;
	} __except (EXCEPTION_EXECUTE_HANDLER) {
	}

	return Z_HOOK_STATE_FAILURE;
}

/* Retrieve an address based on a matched pattern */
::ULONG_PTR Z_API FindPattern ( __in ::LPBYTE lpPattern, __in_z ::LPCSTR lpszPattern, __in ::LONG_PTR nOffset );

/* Kilobyte */
#define KIBIBYTE_UNIT 1024UL
/* Megabyte */
#define MEBIBYTE_UNIT 1048576UL
/* Gigabyte */
#define GIBIBYTE_UNIT 1073741824UL
/* Terabyte */
#define TEBIBYTE_UNIT 1099511627776UL

#define Z_RECV_BUFFER_LENGTH    0x0400
#define Z_SEND_BUFFER_LENGTH    0x0400
#define Z_HISTORY_BUFFER_LENGTH 0x1000


/* Is the MapleStory Recv hook installed */
::BOOL Z_API IsMSRecvHooked ( void );

/* Is the MapleStory Send hook installed */
::BOOL Z_API IsMSSendHooked ( void );

/* GMS data packet */
typedef struct _Z_GMS_PACKET_STRUCT {
	::WORD Command; /* Command ID */
	::BYTE Data[1]; /* Byte data  */
} Z_GMS_PACKET, *PZ_GMS_PACKET, *LPZ_GMS_PACKET;

/* EMS data packet */
typedef struct _Z_EMS_PACKET_STRUCT {
	::BYTE Command; /* Command ID */
	::BYTE Data[1]; /* Byte data  */
} Z_EMS_PACKET, *PZ_EMS_PACKET, *LPZ_EMS_PACKET;

/* MapleStory data packet */
typedef struct _Z_PACKET_STRUCT {
	::DWORD dwUnknown1;
	union {
		::LPVOID lpvData;
		::LPBYTE lpBytes;
		PZ_GMS_PACKET ppGMSPacket;
		PZ_EMS_PACKET ppEMSPacket;
	};
	::DWORD dwLength;
	::DWORD dwUnknown2;
} Z_PACKET, *PZ_PACKET, *LPZ_PACKET;

/* Sent data packet */
typedef struct _Z_SEND_PACKET_STRUCT {
	::DWORD      dwReturn;
	PZ_PACKET ppPacket;
} Z_SEND_PACKET, *PZ_SEND_PACKET, *LPZ_SEND_PACKET;

/* Install the MapleStory Recv hook */
::DWORD Z_API InstallMapleStoryRecvHook ( void );
/* Install the MapleStory Send hook */
::DWORD Z_API InstallMapleStorySendHook ( void );

/* Send a MapleStory packet using byte data */
::DWORD Z_API SendPacket ( __in_bcount(nLength) ::LPBYTE lpBytes, __in ::DWORD dwLength );

/* MapleStory packet */
#include "ZPacket.h"

#endif /* __Z_h__ */