#pragma once
#include "rmobject.h"

class CRMitem :
	public CRMobject
{
public:
	CRMitem(void);
	~CRMitem(void);

	ObjectType		GetObjectTypeColor() { return m_ObjectTypeColor; }
	ObjectType		GetObjectTypeGray() { return GetObjectType(); }
	
	virtual void	Active();
	void			SetTime( UINT holdingTime ) { m_StartTime = holdingTime; }
	virtual void	Update();

protected:
	virtual void	DeActive() { m_Active = false; }

	ObjectType		m_ObjectTypeColor;
	UINT			m_TimeSlice;
	UINT			m_StartTime;

friend class CRMitemManager;
	PlayerNumber	m_TargetPlayer;
	PlayerNumber	m_OwnPlayer;

	bool			m_Active;
};

// 부모 클래스
// 각 티어의 세부 아이템들은 이 클래스를 상속 받아서 구현 하면 됨