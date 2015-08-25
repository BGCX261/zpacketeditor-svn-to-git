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
#ifndef __ZPE_h__
#define __ZPE_h__

/* Tell the compiler to reference this header file only once */
#pragma once

#include "Windows.h"

/* Display a system-formatted error message */
void Error ( __in_z ::LPCTSTR lpszProc );

/* Length of the Opcode within each packet */
#ifdef _MAPLE_EUROPE
#	define MAPLE_OPCODE_LENGTH 1
#else
#	define MAPLE_OPCODE_LENGTH 2
#endif

/* Packet data class */
#include "ZPEPacket.h"

#endif /* __ZPE_h__ */
