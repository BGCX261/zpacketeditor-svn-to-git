#ifndef __ZTemplate_h__
#define __ZTemplate_h__

#pragma once

#include "Windows.h"

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Drawing;

namespace Z
{
	/* Pattern-matching objects */
	ref class ZPattern;

	/* Packet template objects */
	ref class ZTemplate : public Z::ZPattern
	{
	public:
		/* Constructor */
		ZTemplate ( String^ alias, String^ pattern ) : ZPattern(pattern)
		{
			this->Alias = alias;
			this->NoFormat = false;
			this->Colorize = false;
		}
		/* Constructor */
		ZTemplate ( String^ alias, Color backColor, Color foreColor, String^ pattern ) : ZPattern(pattern)
		{
			this->Alias   = alias;
			this->NoFormat  = false;
			this->Colorize  = false;
			this->BackColor = backColor;
			this->ForeColor = foreColor;
		}

		/* Destructor */
		~ZTemplate ( void )
		{
		}

	public:
		/* Apply to received packets */
		property bool RecvPackets;
		/* Apply to sent packets */
		property bool SendPackets;
		/* Do not format */
		property bool NoFormat;
		/* Color all fields */
		property bool Colorize;
		/* Foreground color */
		property Color ForeColor;
		/* Background color */
		property Color BackColor;
		/* Command */
		property String^ Alias;
		/* Is Command a valid string */
		property bool HasAlias {
			bool get ( ) {
				return ( String::IsNullOrEmpty(this->Alias) != true );
			}
		}

	public:
		/* Test to see if a string is a valid alias */
		static bool IsValidAlias ( String^ alias );
	};

	/* Collection of Z template objects */
	ref class ZTemplateCollection
	{
	private:
		/* Internal collection */
		List<ZTemplate^>^ m_Collection;

	public:
		/* Constructor */
		ZTemplateCollection ( void )
		{
			this->m_Collection = gcnew List<ZTemplate^>;
		}

		/* Destructor */
		~ZTemplateCollection ( void )
		{
			/* Manually set all references to nullptr to speed up the GC */
			this->Clear();

			this->m_Collection = nullptr;
		}

	public:
		/* Indexer */
		property ZTemplate^ default[int] {
			ZTemplate^ get ( int index ) {
				return this->m_Collection[index];
			}
		}

	public:
		/* Is a pattern in this collection a match to the specified byte data */
		int IsMatch ( String^ bytes, ::DWORD dwStream );

		/* Add a new pattern to the collection */
		int Add ( ZTemplate^ newTemplate );

		/* Remove a pattern from the collection */
		void Remove ( int index );

		/* Remove all items from the collection */
		void Clear ( void );
	};
}

#endif /* __ZTemplate_h__ */
