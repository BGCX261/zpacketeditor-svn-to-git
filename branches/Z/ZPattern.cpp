#include "Z.h"
#include "Z_CLI.h"

using namespace Z;
using namespace System::Collections;
using namespace System::Globalization;
using namespace System::Text;

/* Constructor */
ZPattern::ZPattern ( String^ pattern )
{
	this->m_CreationRegex = pattern;

	String^ byteCode = ZParser::GetByteCodeForPattern(pattern);
	StringBuilder^ sb = gcnew StringBuilder(byteCode->Length);

	for ( int n = 0; n < byteCode->Length; n++ ) {
		if ( byteCode[n] == (::WCHAR)'*' ) {
			sb->Append(WildCard);
		} else if ( byteCode[n] == (::WCHAR)'?' ) {
			sb->Append(MarkCard);
		} else {
			sb->Append(byteCode[n]);
		}
	}

	this->m_CompiledRegex = String::Concat(L"^", sb->ToString(), "$");
	this->m_Regex = gcnew Regex(this->m_CompiledRegex,
		RegexOptions::Compiled | RegexOptions::CultureInvariant | RegexOptions::IgnorePatternWhitespace);
	this->Enabled = true;
}
/* Constructor */
ZPattern::ZPattern ( String^ pattern, bool enabled )
{
	this->m_CreationRegex = pattern;
	String^ byteCode = ZParser::GetByteCodeForPattern(pattern);
	StringBuilder^ sb = gcnew StringBuilder(byteCode->Length);

	for ( int n = 0; n < byteCode->Length; n++ ) {
		if ( byteCode[n] == (::WCHAR)'*' ) {
			sb->Append(WildCard);
		} else if ( byteCode[n] == (::WCHAR)'?' ) {
			sb->Append(MarkCard);
		} else {
			sb->Append(byteCode[n]);
		}
	}

	this->m_CompiledRegex = String::Concat(L"^", sb->ToString(), "$");
	this->m_Regex = gcnew Regex(this->m_CompiledRegex,
		RegexOptions::CultureInvariant | RegexOptions::IgnorePatternWhitespace);
	this->Enabled = enabled;
}

/* Test to see if a string is a valid pattern */
bool ZPattern::IsValidPattern ( String^ s )
{
	if ( String::IsNullOrEmpty(s->Trim()) )
		return false;

	return ( ZParser::GetByteCodeForPattern(s) != nullptr );
}

/* Is a pattern in this collection a match to the specified byte data */
bool ZPattern::IsMatch ( String^ bytes )
{
	return this->Enabled ? this->m_Regex->IsMatch(bytes) : false;
}

/* Is a pattern in this collection a match to the specified byte data */
int ZPatternCollection::IsMatch ( String^ rawBytes )
{
	using namespace System::Threading;

	Object^ obj = ((System::Collections::ICollection^)(this->m_Collection))->SyncRoot;
	
	Monitor::Enter(obj);

	try {
		if ( this->m_Collection->Count > 0 ) {
			for ( int p = 0; p < this->m_Collection->Count; p++ ){
				if ( this->m_Collection[p]->IsMatch(rawBytes) )
					return p;
			}
		}
	} finally {
		Monitor::Exit(obj);
	}

	return ( -1 );
}

/* Add a new pattern to the collection */
int ZPatternCollection::Add ( ZPattern^ newPattern )
{
	using namespace System::Threading;

	Object^ obj = ((System::Collections::ICollection^)(this->m_Collection))->SyncRoot;
	
	Monitor::Enter(obj);

	try {
		this->m_Collection->Add(newPattern);
		return this->m_Collection->Count - 1;
	} finally {
		Monitor::Exit(obj);
	}
}

/* Remove a pattern from the collection */
void ZPatternCollection::Remove ( int index )
{
	using namespace System::Threading;

	Object^ obj = ((System::Collections::ICollection^)(this->m_Collection))->SyncRoot;
	
	Monitor::Enter(obj);

	try {
		this->m_Collection->RemoveAt(index);
	} finally {
		Monitor::Exit(obj);
	}
}

/* Remove all items from the collection */
void ZPatternCollection::Clear ( void )
{
	using namespace System::Threading;

	Object^ obj = ((System::Collections::ICollection^)(this->m_Collection))->SyncRoot;
	
	Monitor::Enter(obj);

	try {
		this->m_Collection->Clear();
	} finally {
		Monitor::Exit(obj);
	}
}
