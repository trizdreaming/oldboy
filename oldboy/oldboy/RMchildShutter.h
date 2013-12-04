#pragma once
#include "RMobject.h"

class CRMchildShutter :
	public CRMobject
{
public:
	CRMchildShutter(void);
	~CRMchildShutter(void);

	virtual void	Update();
};

