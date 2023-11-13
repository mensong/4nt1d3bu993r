#pragma once
#include <Windows.h>
#include <string>

#ifdef _DEBUG
#pragma comment(lib, "4nt1d3bu993r_d.lib")
#else
#pragma comment(lib, "4nt1d3bu993r.lib")
#endif
extern "C" void _4nt1();

static class __ANTI_DEBUGGER
{ 
public:
	__ANTI_DEBUGGER()
	{
		_4nt1();
	}
} a;