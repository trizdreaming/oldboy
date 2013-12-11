#pragma once
#include "RMobject.h"

class CRMchildEffectImage:
	public CRMobject
{
public:
	CRMchildEffectImage(void);
	virtual ~CRMchildEffectImage(void);

	virtual void	Update();

private:
	UINT	m_EffectTime;
	UINT	m_EffectType;
};