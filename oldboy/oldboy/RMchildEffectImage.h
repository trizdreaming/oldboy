#pragma once

class CRMchildEffectImage:
	public CRMobject
{
public:
	CRMchildEffectImage(void);
	~CRMchildEffectImage(void);

	virtual void        Update();

private:
	UINT	m_EffectTime;
	UINT	m_EffectType;
};