#pragma once
#include "rmobject.h"

class CRMitem :
	public CRMobject
{
public:
	CRMitem(void);
	~CRMitem(void);

	virtual WidgetType		GetWidgetTypeForColor() { return m_WidgetTypeForColor; }
	virtual WidgetType		GetWidgetTypeForGray() { return GetWidgetType(); }
	virtual	WidgetType		GetWidgetTypeOfCard() { return m_WidgetTypeOfCard; }
	
	virtual void	Active();
	virtual void	Update();
	void			SetTime( UINT holdingTime ) { m_StartTime = holdingTime; }
	PlayerNumber	GetTargerPlayer() { return m_TargetPlayer; }
	PlayerNumber	GetOwnPlayer() { return m_OwnPlayer; }
	
protected:
	virtual void	DeActive() { m_Active = false; }

	WidgetType		m_WidgetTypeForColor;
	WidgetType		m_WidgetTypeOfCard;

	UINT			m_TimeSlice;
	UINT			m_StartTime;

friend class CRMitemManager;
	PlayerNumber	m_TargetPlayer;
	PlayerNumber	m_OwnPlayer;

	bool			m_Active;
};

// 부모 클래스
// 각 티어의 세부 아이템들은 이 클래스를 상속 받아서 구현 하면 됨