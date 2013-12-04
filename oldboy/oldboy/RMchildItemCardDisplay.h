#pragma once
#include "rmobject.h"

class CRMchildItemCardDisplay:
	public CRMobject
{
public:
	CRMchildItemCardDisplay(void);
	~CRMchildItemCardDisplay(void);

public:
	void			Update();
	void			SetPlayer( PlayerNumber playerNumber ) { m_PlayerNumber = playerNumber; }
	void			Render();

private:
	PlayerNumber	m_PlayerNumber;
	UINT			m_PrevTime;
	UINT			m_TimeSlice;
	bool			m_FlickFlag;
};

