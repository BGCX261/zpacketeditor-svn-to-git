#include "Z.h"
#include "Z_CLI.h"

using namespace Z;
using namespace System::Threading;

/* Test to see if a string is a valid command */
bool ZTemplate::IsValidAlias ( String^ alias )
{
	if ( String::IsNullOrEmpty(alias) )
		return false;

	bool retval = true;

	for ( int i = 0; i < alias->Length; i++ ) {
		if ( ( retval = ( ( alias[i] == '_' ) || iswalnum(alias[i]) ) ) != true )
			break;
	}

	return retval;
}

/* Is a template in this collection a match to the specified byte data */
int ZTemplateCollection::IsMatch ( String^ rawBytes, ::DWORD dwStream )
{
	Object^ obj = ((System::Collections::ICollection^)(this->m_Collection))->SyncRoot;

	Monitor::Enter(obj);

	try {
		if ( this->m_Collection->Count > 0 ) {
			for ( int t = 0; t < this->m_Collection->Count; t++ ){
				if ( ( ( dwStream == Z_PACKET_STREAM_SEND ) && ( this->m_Collection[t]->IsMatch(rawBytes) && this->m_Collection[t]->SendPackets ) ) ||
					( ( dwStream == Z_PACKET_STREAM_RECEIVE ) && ( this->m_Collection[t]->IsMatch(rawBytes) && this->m_Collection[t]->RecvPackets ) ) ) {
						return t;
				}
			}
		}
	} finally {
		Monitor::Exit(obj);
	}

	return ( -1 );
}

/* Add a new template to the collection */
int ZTemplateCollection::Add ( ZTemplate^ newTemplate )
{
	Object^ obj = ((System::Collections::ICollection^)(this->m_Collection))->SyncRoot;
	
	Monitor::Enter(obj);

	try {
		this->m_Collection->Add(newTemplate);
		return this->m_Collection->Count - 1;
	} finally {
		Monitor::Exit(obj);
	}
}

/* Remove a template from the collection */
void ZTemplateCollection::Remove ( int index )
{
	Object^ obj = ((System::Collections::ICollection^)(this->m_Collection))->SyncRoot;
	
	Monitor::Enter(obj);

	try {
		this->m_Collection->RemoveAt(index);
	} finally {
		Monitor::Exit(obj);
	}
}

/* Remove all items from the collection */
void ZTemplateCollection::Clear ( void )
{
	Object^ obj = ((System::Collections::ICollection^)(this->m_Collection))->SyncRoot;
	
	Monitor::Enter(obj);

	try {
		this->m_Collection->Clear();
	} finally {
		Monitor::Exit(obj);
	}
}