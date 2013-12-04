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
	D2D1::Matrix3x2F m_PrevMatrix;
	D2D1::Matrix3x2F m_Matrix;
	
	float			m_ScaleX;
	float			m_ScaleY;
	float			m_Rotation;

	PlayerNumber	m_PlayerNumber;
	UINT			m_PrevTime;
	UINT			m_TimeSlice;
	bool			m_FlickFlag;
};

