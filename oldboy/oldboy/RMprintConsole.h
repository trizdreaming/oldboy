#pragma once

#ifndef _PRINT_CONSOLE
#define _PRINT_CONSOLE
#endif

class CRMprintConsole
{
	SINGLETON(CRMprintConsole);
private:
	CRMprintConsole(void);
	~CRMprintConsole(void);
};