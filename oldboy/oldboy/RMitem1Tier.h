#pragma once
#include "rmitem.h"
class CRMitem1Tier :
	public CRMitem
{
public:
	CRMitem1Tier(void);
	~CRMitem1Tier(void);

private:
	ItemType	m_ThisType;
};

