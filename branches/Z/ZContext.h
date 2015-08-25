#ifndef __ZContext_h__
#define __ZContext_h__

#pragma once

#include "Windows.h"

#define Z_COLLECTION_COUNT 8

using namespace System;
using namespace System::ComponentModel;
using namespace System::Drawing;
using namespace System::Windows::Forms;

namespace Z
{
	/* Pattern-matching objects */
	ref class ZPatternCollection;

	/* Packet template objects */
	ref class ZTemplateCollection;

	/* Application */
	ref class ZApplication;
	/* MapleStory memory management */
	ref class ZMemoryManager;
	/* Template management */
	ref class ZTemplateManager;
	/* Packet Builder */
	ref class ZPacketBuilder;
	/* Pattern Management */
	ref class ZPatternManager;
	/* Packet Collections */
	ref class ZCollection;
	/* Packet Flooder */
	ref class ZFloodControl;
	/* About */
	ref class ZAbout;

	/* Z Application Context */
	ref class ZContext : public System::Windows::Forms::ApplicationContext
	{
	/* Singleton */
	public: static ZContext^ G;

#pragma region User Interface Elements

	public:
		/* Application Window */
		ZApplication^ Application;
	public:
		/* MapleStory memory management */
		ZMemoryManager^ Memory;
	public:
		/* Template management */
		ZTemplateManager^ Templates;
	public:
		/* Packet Builder */
		ZPacketBuilder^ PacketBuilder;
	public: /* Pattern Management */
		/* Blocked received packets */
		ZPatternManager^ BlockedRecvPatterns;
		/* Ignored received packets */
		ZPatternManager^ IgnoredRecvPatterns;
		/* Blocked sent packets */
		ZPatternManager^ BlockedSendPatterns;
		/* Ignored sent packets */
		ZPatternManager^ IgnoredSendPatterns;
		/* Custom packet patterns */
		ZPatternManager^ UserCreatedPatterns;
	public:
		array<ZCollection^>^ Collections;
	public:
		ZFloodControl^ FloodControl;
	public: /* Help */
		ZAbout^ About;

#pragma endregion

	public:
		/* Constructor */
		ZContext ( ZApplication^ window );
		/* Dispose */
		~ZContext ( void );

	private:
		/* Child form is first shown  */
		static void FormShownEvent ( Object^ sender, EventArgs^ e );
		
		/* Child form is being closed */
		static void FormCloseEvent ( Object^ sender, CancelEventArgs^ e );

	private:
		/* Attach a child form to the MainForm and attach the required event handlers */
		void AttachChild ( Form^ form );
	};
}

#endif /* __ZContext_h__ */
