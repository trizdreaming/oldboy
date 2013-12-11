#pragma once
#include "RMobject.h"

class CRMchildGauge : 
	public CRMobject
{
public:
	CRMchildGauge(void);
	virtual ~CRMchildGauge(void);

public:
	virtual void	Update();

private:
	int				m_Tick;
};

