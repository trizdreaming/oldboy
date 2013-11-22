#pragma once
#include "rmitem.h"
class CRMitem3Tier :
	public CRMitem
{
public:
	CRMitem3Tier(void);
	~CRMitem3Tier(void);

private:
	ItemType	m_ThisType;
};

