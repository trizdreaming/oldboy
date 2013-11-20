#pragma once
#include "RMobject.h"

class CRMchildGauge : 
	public CRMobject
{
public:
	CRMchildGauge(void);
	~CRMchildGauge(void);

public:
	virtual void	Update();
};

