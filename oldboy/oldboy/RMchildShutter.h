#pragma once
#include "RMobject.h"

class CRMchildShutter :
	public CRMobject
{
public:
	CRMchildShutter(void);
	~CRMchildShutter(void);

	virtual void	Update();
	void			SetPlayer( PlayerNumber playerNumber ) { m_playerNumber = playerNumber; }

private:
	int				m_Tick;
	PlayerNumber	m_playerNumber;
};

