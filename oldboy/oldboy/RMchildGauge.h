#pragma once
#include "RMobject.h"

class CRMchildGauge : 
	public CRMobject
{
public:
	CRMchildGauge(void);
	~CRMchildGauge(void);

public:
	virtual void	Update();
	void			SetPlayer( PlayerNumber playerNumber ) { m_playerNumber = playerNumber; }

private:
	int				m_Tick;
	PlayerNumber	m_playerNumber;
};

