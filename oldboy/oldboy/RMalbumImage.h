#pragma once
#include "rmobject.h"

class CRMalbumImage :
	public CRMobject
{
public:
	CRMalbumImage(void);
	~CRMalbumImage(void);

	void	Update();
	bool	IsFinish() { return m_IsFinish; }
	
	void	Up();
	void	Down();

private:
	bool	m_IsUp;
	bool	m_IsDown;
	bool	m_IsFinish;
};

