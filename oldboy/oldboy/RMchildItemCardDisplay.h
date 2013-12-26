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
	virtual void	SetPosition(float x, float y);

private:
	UINT			m_PrevTime;
	UINT			m_TimeSlice;
	bool			m_FlickFlag;

	float			m_WidthOriginal;
	float			m_PositionXOriginal;
	float			m_PositionYOriginal;
};

