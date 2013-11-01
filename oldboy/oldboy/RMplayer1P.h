#pragma once
#include "rmplayer.h"
class CRMplayer1P :
	public CRMplayer
{
public:
	SINGLETON(CRMplayer1P);

	CRMplayer1P(void);
	~CRMplayer1P(void);
};

