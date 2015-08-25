using namespace System;
using namespace System::Reflection;
using namespace System::Resources;
using namespace System::Runtime::InteropServices;
using namespace System::Security;
using namespace System::Security::Permissions;

[assembly: NeutralResourcesLanguage(L"")];

[assembly: RegistryPermission(SecurityAction::RequestMinimum,
	ViewAndModify = L"HKEY_CURRENT_USER\\SOFTWARE\\Nullz\\Z")];
[assembly: RegistryPermission(SecurityAction::RequestMinimum,
	ViewAndModify = L"HKEY_CURRENT_USER\\SOFTWARE\\Nullz\\Z\\Install")];

[assembly: ComVisible(false)];

[assembly: AssemblyTitle(L"Z: The Packet Inspector")];
[assembly: AssemblyDescription(L"Packet Editor for MapleStory")];
[assembly: AssemblyVersion(L"0.8.*")];
#ifndef _DESIGN_MODE
#	ifdef _GK_PUBLIC
[assembly: AssemblyConfiguration(L"GK_pub")];
[assembly: AssemblyProduct(L"Z")];
#	else
[assembly: AssemblyConfiguration(L"GK")];
[assembly: AssemblyProduct(L"Z")];
#	endif
#endif
[assembly: AssemblyCulture(L"")];
[assembly: AssemblyCompany(L"")];
[assembly: AssemblyCopyright(L"Copyright (c) 2010 The Nu||z")];
[assembly: AssemblyTrademark(L"ItsTheNullz@gmail.com")];
