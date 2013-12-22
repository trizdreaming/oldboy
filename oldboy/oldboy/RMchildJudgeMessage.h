#pragma once
#include "RMobject.h"

class CRMchildJudgeMessage :
	public CRMobject
{
public:
	CRMchildJudgeMessage(void);
	virtual ~CRMchildJudgeMessage(void);

	virtual void	Update();
};

