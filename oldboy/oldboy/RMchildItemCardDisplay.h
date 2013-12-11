#pragma once
#include "rmobject.h"

class CRMchildItemCardDisplay:
	public CRMobject
{
public:
	CRMchildItemCardDisplay(void);
	virtual ~CRMchildItemCardDisplay(void);

public:
	void			Update();
	//void			SetOrder(UINT orderNumber) { m_OrderNumber = orderNumber; }
	//void			Render();

private:
	UINT			m_PrevTime;
	UINT			m_TimeSlice;
	//UINT			m_OrderNumber;
	bool			m_FlickFlag;
	//bool			m_OrderFlag;
	//float			m_MoveOffset;
};

