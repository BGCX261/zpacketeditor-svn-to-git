#ifndef __ZPattern_h__
#define __ZPattern_h__

#pragma once

#include "Windows.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Text::RegularExpressions;

namespace Z

{
	/* Z pattern-matching object */
	ref class ZPattern
	{
		/* Replaces * as a wildcard: (?:(?:[0-9a-fA-F]{2})*) */
		static String^ WildCard = L"(?:(?:[0-9a-fA-F]{2})*)";
		/* Replaces ? as a wildcard: (?:(?:[0-9a-fA-F]{2})*) */
		static String^ MarkCard = L"(?:[0-9a-fA-F]{2})";

	private:
		/* String used to create this pattern */
		String^ m_CreationRegex;
		/* String used to match against byte data */
		String^ m_CompiledRegex;
		/* Regular expression object */
		Regex^  m_Regex;

	public:
		/* Constructor */
		ZPattern ( String^ pattern );
		/* Constructor */
		ZPattern ( String^ pattern, bool enabled );

		/* Destructor */
		~ZPattern ( void )
		{
			/* Manually set all references to nullptr to speed up the GC */
			this->m_CreationRegex = nullptr;
			this->m_CompiledRegex = nullptr;
			this->m_Regex         = nullptr;
		}

	public:
		/* Is this pattern enabled */
		property bool Enabled;

		/* String used to create the compiled string */
		property String^ CreationString
		{
			String^ get ( ) {
				return this->m_CreationRegex;
			}
		}

		/* String used to create the regular expression object */
		property String^ CompiledString
		{
			String^ get ( ) {
				return this->m_CreationRegex;
			}
		}

	public:
		/* Test to see if a string is a valid pattern */
		static bool IsValidPattern ( String^ s );

	public:
		/* Is this pattern a match to the specified byte data */
		bool IsMatch ( String^ bytes );
	};

	/* Collection of Z pattern objects */
	ref class ZPatternCollection
	{
	private:
		/* Internal collection */
		List<ZPattern^>^ m_Collection;

	public:
		/* Constructor */
		ZPatternCollection ( void )
		{
			this->m_Collection = gcnew List<ZPattern^>;
		}

		/* Destructor */
		~ZPatternCollection ( void )
		{
			/* Manually set all references to nullptr to speed up the GC */
			this->Clear();

			this->m_Collection = nullptr;
		}

	public:
		/* Indexer */
		property ZPattern^ default[int] {
			ZPattern^ get ( int index ) {
				return this->m_Collection[index];
			}
		}


	public:
		/* Is a pattern in this collection a match to the specified byte data */
		int IsMatch ( String^ bytes );

		/* Add a new pattern to the collection */
		int Add ( ZPattern^ newPattern );

		/* Remove a pattern from the collection */
		void Remove ( int index );

		/* Remove all items from the collection */
		void Clear ( void );
	};
}

#endif /* __ZPattern_h__ */
