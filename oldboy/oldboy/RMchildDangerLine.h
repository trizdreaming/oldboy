#pragma once
#include "RMobject.h"
class CRMchildDangerLine :
	public CRMobject
{
public:
	CRMchildDangerLine(void);
	virtual ~CRMchildDangerLine(void);

	virtual void	Update();

private:
	UINT			m_AnimationFrame;
};

