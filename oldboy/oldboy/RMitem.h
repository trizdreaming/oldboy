#pragma once
#include "rmobject.h"

class CRMitem :
	public CRMobject
{
public:
	CRMitem(void);
	~CRMitem(void);

	ObjectType		GetObjectTypeColor() { return GetObjectType(); }
	ObjectType		GetObjectTypeGray() { return m_ObjectTypeColor; }

	void			Update() {};
	// 추상 함수이므로 임시로 추가

protected:
	ObjectType		m_ObjectTypeColor;

private:
	UINT			m_StartTime;
	PlayerNumber	m_TargetPlayer;
};

// 부모 클래스
// 각 티어의 세부 아이템들은 이 클래스를 상속 받아서 구현 하면 됨