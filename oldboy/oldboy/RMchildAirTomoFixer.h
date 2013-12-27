#pragma once
#include "RMobject.h"

class CRMchildAirTomoFixer :
	public CRMobject
{
public:
	CRMchildAirTomoFixer(void);
	virtual ~CRMchildAirTomoFixer(void);

	virtual void	Update();
	void			StartFixer();
private:
	UINT			m_StartTime;
};

