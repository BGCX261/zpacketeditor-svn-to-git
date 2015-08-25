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
#ifndef __ZPEContext_h__
#define __ZPEContext_h__

/* Tell the compiler to reference this header file only once */
#pragma once

/*
 * You can include native C++ header files in Managed C++/CLI
 * header files as long as they appear before the first line
 * of managed code
 */
#include "ZPE.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Drawing;
using namespace System::Windows::Forms;

namespace ZPE
{
	/*
	 * We forward-delcare the ZPEWindow class since it is not
	 * #include'd in this header file.
	 */
	ref class ZPEWindow;

	/*
	 * An application context class to manage the windows for
	 * received and sent packets
	 */
	ref class ZPEContext : System::Windows::Forms::ApplicationContext
	{
	public:
		/*
		 * Singleton access to the instance of the context.
		 *
		 * This must be done in this way because the rules
		 * of Managed C++ forbid the declaration of managed
		 * objects outside of a function body or an struct
		 * or class body.
		 */
		static ZPEContext^ G;

	private:
		/* Number of open windows */
		int Count;

	public:
		/* Received packet windows */
		ZPEWindow^ RecvPackets;
		/* Sent packet windows */
		ZPEWindow^ SendPackets;

	public:
		/*
		 * Constructor
		 *
		 * Creates and displays the received packets and sent packets windows.
		 */
		ZPEContext ( void );

	private:
		/* Occurs when one of the windows is closed. */
		void OnFormClosed ( Object^ sender, EventArgs^ e );
	};
}

#endif /* __ZPEContext_h__ */