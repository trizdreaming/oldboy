#pragma once
#include "rmplayer.h"
class CRMplayer2P :
	public CRMplayer
{
	SINGLETON(CRMplayer2P);

private:
	CRMplayer2P(void);
	~CRMplayer2P(void);
};
