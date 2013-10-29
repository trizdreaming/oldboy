#pragma once
#include "rmobject.h"

class CRMchildShutter :
	public CRMobject
{
public:
	CRMchildShutter(void);
	~CRMchildShutter(void);

	virtual void	Update();

private:
	int				m_Tick;
};

