#pragma once

#include "oldboy.h"
#include "RMEnumObjectType.h"

class CRMobject
{
public:
	CRMobject(void);
	~CRMobject(void);

public:
	virtual void	Update() = 0;
	// void			Update();
	void			Render();
	void			SetKey(EnumObjectType key) { m_key = key; }

	void			SetPosition(float x, float y) { m_xPosition = x; m_yPosition = y; }

protected:
	EnumObjectType	m_key;

	float			m_xPosition;
	float			m_yPosition;
	float			m_width;
	float			m_height;
	float			m_alpha;
};

