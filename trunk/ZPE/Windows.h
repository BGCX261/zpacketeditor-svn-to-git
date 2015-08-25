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
#ifndef __Windows_h__
#define __Windows_h__

/* Tell the compiler to reference this header file only once */
#pragma once

/* Detect if the Microsoft Visual C++ compiler is being used. */
#ifdef _MSC_VER
#	ifndef VC_EXTRALEAN
#	define VC_EXTRALEAN 1
#	endif
#else
#	ifndef WIN32_LEAN_AND_MEAN
#	define WIN32_LEAN_AND_MEAN 1
#	endif
#endif /* _MSC_VER */

#include <windows.h>

#endif /* __Windows_h__ */
