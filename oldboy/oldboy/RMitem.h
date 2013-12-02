#pragma once
#include "rmobject.h"

class CRMitem :
	public CRMobject
{
public:
	CRMitem(void);
	~CRMitem(void);

	void	Update();
	// 추상클래스 상속 한 것 구현

	ObjectType		GetObjectTypeColor() { return GetObjectType(); }
	ObjectType		GetObjectTypeGray() { return m_ObjectTypeColor; }

private:
	UINT			m_StartTime;
	PlayerNumber	m_TargetPlayer;

	ObjectType		m_ObjectTypeColor;
};

// 부모 클래스
// 각 티어의 세부 아이템들은 이 클래스를 상속 받아서 구현 하면 됨