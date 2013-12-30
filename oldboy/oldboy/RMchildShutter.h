#pragma once
#include "RMobject.h"

class CRMchildShutter :
	public CRMobject
{
public:
	CRMchildShutter(void);
	virtual ~CRMchildShutter(void);

	virtual void	Update();

private:
	bool			m_IsDead;
};

