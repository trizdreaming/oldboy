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
	void			SetPlayer( PlayerNumber playerNumber ) { m_playerNumber = playerNumber; }

private:
	PlayerNumber	m_playerNumber;
	UINT m_prevTime;
	UINT m_timeSlice;
	bool m_flickFlag;
};

