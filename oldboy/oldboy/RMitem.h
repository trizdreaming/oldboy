#pragma once
#include "rmobject.h"

class CRMitem :
	public CRMobject
{
public:
	CRMitem(void);
	~CRMitem(void);

private:
	ItemType	m_ThisType;
};

// 부모 클래스
// 각 티어의 세부 아이템들은 이 클래스를 상속 받아서 구현 하면 됨