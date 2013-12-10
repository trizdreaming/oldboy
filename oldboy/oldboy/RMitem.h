#pragma once
#include "rmobject.h"

class CRMitem :
	public CRMobject
{
public:
	CRMitem(void);
	virtual ~CRMitem(void); //sm9: 중요하다. 가상 함수가 있는 자식들은 반드시 가상 소멸자를 습관하 할 것.. 이거 안하면 나중에 자원해제할 때, 자식만의 자원은 해제가 안된다.
	// 참고: http://pacs.tistory.com/31
	// 다른 곳에서도 잘 찾아서 소멸자에 virtual 해줘라.


	virtual WidgetType		GetWidgetTypeForColor() { return m_WidgetTypeForColor; }
	virtual WidgetType		GetWidgetTypeForGray() { return GetWidgetType(); }
	virtual	WidgetType		GetWidgetTypeOfCard() { return m_WidgetTypeOfCard; }
	
	virtual void	Active();
	void			SetTime( UINT holdingTime ) { m_StartTime = holdingTime; }
	virtual void	Update();
	
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