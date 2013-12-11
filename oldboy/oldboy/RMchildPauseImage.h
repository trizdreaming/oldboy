#pragma once
#include "RMobject.h"
#include "RMmacro.h"

class CRMchildPauseImage :
	public CRMobject
{
	SINGLETON(CRMchildPauseImage);

public:
	CRMchildPauseImage(void);
	virtual ~CRMchildPauseImage(void);

	virtual void	Update();
};

