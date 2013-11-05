#pragma once

#include "RMobject.h"

class CRMchildEffectImage:
	public CRMobject
{
public:
	CRMchildEffectImage(void);
	~CRMchildEffectImage(void);

	virtual void        Update();

private:
	int	m_EffectTime;
	int	m_EffectType;
};