#pragma once
#include "rmplayer.h"
class CRMplayer2P :
	public CRMplayer
{
public:
	SINGLETON(CRMplayer2P);

	CRMplayer2P(void);
	~CRMplayer2P(void);
};

