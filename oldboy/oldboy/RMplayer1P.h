#pragma once
#include "rmplayer.h"
class CRMplayer1P :
	public CRMplayer
{
	SINGLETON(CRMplayer1P);

private:
	CRMplayer1P(void);
	~CRMplayer1P(void);
};

