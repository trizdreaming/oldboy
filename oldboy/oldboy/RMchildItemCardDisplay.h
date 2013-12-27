#pragma once
#include "rmobject.h"

class CRMchildItemCardDisplay:
	public CRMobject
{
public:
	CRMchildItemCardDisplay(void);
	virtual ~CRMchildItemCardDisplay(void);

public:
	virtual void	Update();
	virtual void	Render();
	virtual void	SetPosition(float x, float y);

private:
	UINT			m_PrevTime;
	UINT			m_TimeSlice;
	
	bool			m_OneTimeFinishFlag;
	// 한 번만 보여주기 위한 플래그

	bool			m_Phase1Flag;
	bool			m_Phase2Flag;
	bool			m_Phase3Flag;
	bool			m_FlickFlag;

	UINT			m_FlickCount;

	float			m_WidthOriginal;
	float			m_HeightOriginal;
	float			m_PositionXOriginal;
	float			m_PositionYOriginal;
};

