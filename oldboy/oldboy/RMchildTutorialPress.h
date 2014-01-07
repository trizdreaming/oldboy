#pragma once
#include "rmobject.h"

class CRMchildTutorialPress :
	public CRMobject
{
public:
	CRMchildTutorialPress(void);
	virtual ~CRMchildTutorialPress(void);

	virtual void	Update();

	ScriptPosition position;
};

