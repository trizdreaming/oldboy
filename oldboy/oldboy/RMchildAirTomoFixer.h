#pragma once
#include "RMobject.h"

class CRMchildAirTomoFixer :
	public CRMobject
{
public:
	CRMchildAirTomoFixer(void);
	virtual ~CRMchildAirTomoFixer(void);

	virtual void	Update();
private:
	UINT			m_StartTime;
};

