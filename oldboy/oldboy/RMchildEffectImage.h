#pragma once
#include "rmobject.h"

class CRMchildEffectImage:
	public CRMobject
{
public:
	CRMchildEffectImage(void);
	~CRMchildEffectImage(void);

	virtual void        Update();

private:
	int m_EffectTime;
};