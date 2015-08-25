#ifndef __Windows_h__
#define __Windows_h__

#pragma once

#ifdef _MSC_VER
#	ifndef VC_EXTRALEAN
#	define VC_EXTRALEAN 1
#	endif
#else
#	ifndef WIN32_LEAN_AND_MEAN
#	define WIN32_LEAN_AND_MEAN 1
#	endif
#endif

#include <windows.h>

#include <ctype.h>
#include <tchar.h>

#endif /* __Windows_h__ */
