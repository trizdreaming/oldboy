#include "stdafx.h"
#include "RMmacro.h"
#include "RMprintConsole.h"


CRMprintConsole::CRMprintConsole(void)
{
	AllocConsole();
	FILE* pFile; 
	freopen_s(&pFile, "CONOUT$", "wb", stdout);
}


CRMprintConsole::~CRMprintConsole(void)
{
	FreeConsole();
}
