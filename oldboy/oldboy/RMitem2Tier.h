#pragma once
#include "rmitem.h"
class CRMitem2Tier :
	public CRMitem
{
public:
	CRMitem2Tier(void);
	~CRMitem2Tier(void);

private:
	ItemType	m_ThisType;
};

