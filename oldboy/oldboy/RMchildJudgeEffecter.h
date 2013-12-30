#pragma once
#include "RMobject.h"

class CRMchildJudgeEffecter :
	public CRMobject
{
public:
	CRMchildJudgeEffecter(void);
	virtual ~CRMchildJudgeEffecter(void);

	virtual void	Update();
	virtual void	Render();

private:
	UINT			m_AnimationFrame;
};

