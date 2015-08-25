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
#ifndef __ZPEPacket_h__
#define __ZPEPacket_h__

/* Tell the compiler to reference this header file only once */
#pragma once

#include "Windows.h"

/* Internal packet structure */
typedef struct _PACKET_MESSAGE_STRUCT {
#ifdef _MAPLE_EUROPE
	/* EMS packey opcode; is always 1-byte in length */
	::BYTE Command;
#else
	/* GMS packey opcode; is always 2-byte in length */
	::WORD Opcode;
#endif
	/* Array of bytes that contain the packet data.
	 * We declare this as 1-byte array, but when we handle
	 * it it will be treated as having a length of: dwLength - 2
	 */
	::BYTE Data[1];
} PACKET_MESSAGE;

/* Packets tructure for MapleStory */
typedef struct _PACKET_STRUCT {
	/* Unknown 4-byte variable */
	::DWORD dwUnknown1;
	/*
	 * Declaring the pointer to the internal packet structure
	 * allows us to address it as several different data types
	 * without dereferencing it.
	 */
	union
	{
		/* Packet data as a void pointer */
		::LPVOID lpvData;
		/* Array of bytes */
		::LPBYTE lpBytes;
		/* Packet message */
		PACKET_MESSAGE* pMessage;
	};
	/* Length of the packet (in bytes) */
	::DWORD dwLength;
	/* Unknown 4-byte variable */
	::DWORD dwUnknown2;
} PACKET;

/* Structure for packet that has been sent */
typedef struct _SEND_PACKET_STRUCT {
	/* 4-byte return address of the packet */
	::DWORD dwReturn;
	/* Packet */
	PACKET* ppPacket;
} SEND_PACKET;

/* Flags that contain attributes about the packet data */
enum ZPE_PACKET_ATTRIBUTES
{
	/* Packet was received */
	ZPE_PACKET_ATTRIBUTE_RECV  = 0x01,
	/* Packet was sent */
	ZPE_PACKET_ATTRIBUTE_SEND  = 0x02,
	/* Packet contains only NULL data */
	ZPE_PACKET_ATTRIBUTE_NULL  = 0x04,
	/* Packet is empty (has only an opcode) */
	ZPE_PACKET_ATTRIBUTE_EMPTY = 0x08
};

/*
 * This class is only a container for our ZPE_PACKET
 * structure; Creating this class gives us a more
 * natural way to access the packet's data.
 */
class ZPEPacket
{
private:
	/* Pointer to the MapleStory data packet */
	PACKET* ppPacket;
	/* Return address */
	::DWORD dwReturn;
	/* Packet attributes */
	::DWORD dwAttributes;

public:
	/*
	 * Constructor
	 *
	 * Create a ZPE packet object for a packet structure, lpvPacket,
	 * with the initial attributes, dwInitialAttributes already set
	 */
	ZPEPacket ( __in ::LPVOID lpvPacket, __in ::DWORD dwInitialAttributes );

	/* Destructor
	 *
	 * This class is never extended, but we're declaring the destructor as
	 * virtual in case we chose to extended it in the future.
	 */
	virtual ~ZPEPacket ( void )
	{
		this->ppPacket = NULL;
	}

public:
	/* Is this a packet that was received */
	inline bool IsRecv ( void ) const
	{
		return ( dwAttributes & ZPE_PACKET_ATTRIBUTE_RECV ) != 0;
	}

	/* Is this a packet that was sent */
	inline bool IsSend ( void ) const
	{
		return ( dwAttributes & ZPE_PACKET_ATTRIBUTE_SEND ) != 0;
	}

	/* Does this packet contain only NULL data */
	inline bool IsNull ( void ) const
	{
		return ( dwAttributes & ZPE_PACKET_ATTRIBUTE_NULL ) != 0;
	}

	/* Is this packet empty */
	inline bool IsEmpty ( void ) const
	{
		return ( dwAttributes & ZPE_PACKET_ATTRIBUTE_EMPTY ) != 0;
	}

public:
	/* Locate string data inside the byte code of this packet
	 *
	 * FindString iterates over the byte of the packet and returns
	 * the index of the first character in the located string and
	 * stores the length of that string in lpwLength. If no string
	 * is found (-1) is returned.
	 */
	::DWORD FindString ( __inout ::LPDWORD lpdwOffset, __out ::LPWORD lpwLength );

	/* Block this packet (by setting it's opcode to (-1) and nullifying it's data) */
	bool Block ( void );

	/* Is this packet going to be dispatched to the UI */
	bool IsIgnored ( void );

	/*
	 * Dispatch this packet to the user interface
	 *
	 * Although this is a native C++ class, this method will bridge
	 * into the Managed C++/CLI code region
	 */
	bool Dispatch ( void );
};

#endif /* __ZPEPacket_h__ */
