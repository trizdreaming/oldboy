#pragma once
#include "rmobject.h"
class CRMitemDisplay :
	public CRMobject
{
public:
	CRMitemDisplay(void);
	~CRMitemDisplay(void);

	void			SetTier( ItemTierType tier ) { m_ThisTier = tier; }
	ItemTierType	GetTier() { return m_ThisTier; }
	
	void			Update();

private:
	ItemTierType	m_ThisTier;
};

