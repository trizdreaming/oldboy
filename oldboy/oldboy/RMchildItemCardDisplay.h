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

private:
	UINT			m_PrevTime;
	UINT			m_TimeSlice;
	bool			m_FlickFlag;

};

