#ifndef __ZPacket_h__
#define __ZPacket_h__

#pragma once

#include "Windows.h"

/* GMS data packet */
typedef struct _Z_GMS_PACKET_STRUCT
	Z_GMS_PACKET, *PZ_GMS_PACKET, *LPZ_GMS_PACKET;

/* EMS data packet */
typedef struct _Z_EMS_PACKET_STRUCT
	Z_EMS_PACKET, *PZ_EMS_PACKET, *LPZ_EMS_PACKET;

/* MapleStory data packet */
typedef struct _Z_PACKET_STRUCT
	Z_PACKET, *PZ_PACKET, *LPZ_PACKET;

/* MapleStory data packet (send) */
typedef struct _Z_SEND_PACKET_STRUCT
	Z_SEND_PACKET, *PZ_SEND_PACKET, *LPZ_SEND_PACKET;

/* Packet streams */
enum Z_PACKET_STREAM
{
	/* Received packet */
	Z_PACKET_STREAM_RECEIVE = 0x00,
	/* Sent packet */
	Z_PACKET_STREAM_SEND    = 0x01
};

/* MapleStory data packet types */
enum Z_PACKET_TYPE
{	
	/* Packet with NULL data */
	Z_PACKET_TYPE_NULL    = 0x02,
	/* Packet with empty data */
	Z_PACKET_TYPE_EMPTY   = 0x04
};

/* MapleStory packet */
class ZPacket
{
private:
	/* MapleStory data packet */
	PZ_PACKET ppPacket;
	/* MapleStory packet type */
	::DWORD dwPacketType;
	/* Return address */
	::DWORD dwReturn;

public:
	/* Constructor */
	ZPacket ( __in ::LPVOID lpvPacket, __in ::DWORD dwPacketType );

	/* Dispose */
	virtual ~ZPacket ( void );

public:
	/* Get the MapleStory data packet      */
	inline PZ_PACKET GetPacket ( void ) const
	{
		return this->ppPacket;
	}

	/* Get the total packet size */
	inline ::DWORD GetLength ( void ) const
	{
		return this->ppPacket->dwLength;
	}

	/* Get the command code */
	inline ::WORD GetCommand ( void ) const
	{
		switch ( GetMapleStoryRegion() ) {
			case MAPLESTORY_REGION_GLOBAL:
				return this->ppPacket->ppGMSPacket->Command;
			case MAPLESTORY_REGION_EUROPE:
				return this->ppPacket->ppEMSPacket->Command;
		}

		return 0;
	}

	/* Get the MapleStory data packet type */
	inline ::DWORD GetStream ( void ) const
	{
		return ( this->dwPacketType & Z_PACKET_STREAM_SEND );
	}

	/* Get the return address for the data */
	inline ::DWORD GetReturn ( void ) const
	{
		return this->dwReturn;
	}

	/* Is this packet NULL */
	inline bool IsNull ( void ) const
	{
		return ( ( this->dwPacketType & Z_PACKET_TYPE_NULL ) != 0 );
	}

	/* Is this packet empty */
	inline bool IsEmpty ( void ) const
	{
		return ( ( this->dwPacketType & Z_PACKET_TYPE_EMPTY ) != 0 );
	}

public:
	/* Nullify packet data */
	bool Block ( void );
	/* Dispatch this packet */
	bool Dispatch ( void );
};

/* Detect BSTR values inside of byte data  */
bool IsString ( __in_bcount(dwLength) ::LPBYTE lpBytes, __in ::DWORD dwOffset, __in ::DWORD dwLength, __out ::PDWORD pdwIndex, __out ::LPWORD pwCount );

#endif /* __ZPacket_h__ */
