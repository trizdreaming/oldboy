#pragma once
#include "RMobject.h"
class CRMchildAlertGrow :
	public CRMobject
{
public:
	CRMchildAlertGrow(void);
	virtual ~CRMchildAlertGrow(void);

	virtual void	Update();

private:
	UINT			m_AnimationFrame;
};

