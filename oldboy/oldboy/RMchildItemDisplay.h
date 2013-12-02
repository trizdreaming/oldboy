#pragma once
#include "rmobject.h"
class CRMchildItemDisplay :
	public CRMobject
{
public:
	CRMchildItemDisplay(void);
	~CRMchildItemDisplay(void);

	void			SetTier( ItemTierType tier ) { m_ThisTier = tier; }
	ItemTierType	GetTier() { return m_ThisTier; }
	
	virtual void	Update();

private:
	ItemTierType	m_ThisTier;
};

