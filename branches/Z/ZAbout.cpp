#include "Z.h"
#include "Z_GUI.h"

using namespace Z;
using namespace System::Reflection;

/* Get assembly title string */
String^ ZAbout::GetAssemblyTitle ( void )
{
	try {
		array<Object^>^ attributes = Assembly::GetCallingAssembly()
			->GetCustomAttributes(AssemblyTitleAttribute::typeid, false);

		if ( attributes->Length > 0 ) {
			AssemblyTitleAttribute^ attribute = dynamic_cast<AssemblyTitleAttribute^>(attributes[0]);

			if ( attribute != nullptr )
				return attribute->Title;
		}
	} catch ( Exception^ ) {
	}

	return L"Z: The Packet Inspector";
}

/* Get version string */
String^ ZAbout::GetAssemblyVersion ( void )
{
	try {
		return Assembly::GetCallingAssembly()->GetName(false)->Version->ToString();
	} catch ( Exception^ ) {
	}

	return L"1.0.0.0";
}

/* Get copyright string */
String^ ZAbout::GetAssemblyCopyright ( void )
{
	try {
		array<Object^>^ attributes = Assembly::GetCallingAssembly()
			->GetCustomAttributes(AssemblyCopyrightAttribute::typeid, false);

		if ( attributes->Length > 0 ) {
			AssemblyCopyrightAttribute^ attribute = (AssemblyCopyrightAttribute^)attributes[0];
			return attribute->Copyright;
		}
	} catch ( Exception^ ) {
	}

	return L"Copyright (c) 2010 The Nu||z";
}



void ZAbout::OnLoad ( EventArgs^ e )
{
	this->m_lblVersion->Text   = String::Format(L"{0} {1}", this->GetAssemblyTitle(), this->GetAssemblyVersion());
	this->m_lblCopyright->Text = this->GetAssemblyCopyright();

	if ( this->ParentForm != nullptr )
		this->Opacity = this->ParentForm->Opacity;
}