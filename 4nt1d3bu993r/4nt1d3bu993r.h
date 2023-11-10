#pragma once
#include <Windows.h>
#include <string>

static HMODULE LoadLibraryFromCurrentDir(const char* dllName)
{
	char selfPath[MAX_PATH];
	MEMORY_BASIC_INFORMATION mbi;
	HMODULE hModule = ((::VirtualQuery(LoadLibraryFromCurrentDir, &mbi, 
		sizeof(mbi)) != 0) ? (HMODULE)mbi.AllocationBase : NULL);
	::GetModuleFileNameA(hModule, selfPath, MAX_PATH);
	std::string moduleDir(selfPath);
	size_t idx = moduleDir.find_last_of('\\');
	moduleDir = moduleDir.substr(0, idx);
	std::string modulePath = moduleDir + "\\" + dllName;
	::SetDllDirectoryA(moduleDir.c_str());
	HMODULE hDll = LoadLibraryA(modulePath.c_str());
	if (!hDll)
	{
		exit(0);
	}
	return hDll;
}

static class __ANTI_DEBUGGER
{ 
public:
	__ANTI_DEBUGGER()
	{
		LoadLibraryFromCurrentDir("4nt1d3bu993r.dll");
		//fuckyou(); 
	}
} a;