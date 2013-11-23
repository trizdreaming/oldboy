#pragma once
#include "RMmacro.h"
class CRMpauseManager
{
	SINGLETON(CRMpauseManager);

public:
	CRMpauseManager(void);
	~CRMpauseManager(void);

	void			ShowPause();
	void			ClosePause();

};

