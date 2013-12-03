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
	
	void			Active() { m_Active = true; m_Tick = 0; }
	void			SetTime( UINT holdingTime ) { m_HoldingTick = holdingTime; }
	virtual void	Update();

protected:
	void			DeActive() { m_Active = false; }

	ObjectType		m_ObjectTypeColor; //sm9: 역시 타입과 멤버변수명이 애매모호함... 
	UINT			m_Tick;
	UINT			m_HoldingTick;

friend class CRMitemManager;
	PlayerNumber	m_TargetPlayer;
	PlayerNumber	m_OwnPlayer;

	bool			m_Active;
};

// 부모 클래스
// 각 티어의 세부 아이템들은 이 클래스를 상속 받아서 구현 하면 됨