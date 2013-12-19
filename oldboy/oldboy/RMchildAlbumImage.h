#pragma once
#include "rmobject.h"

class CRMchildAlbumImage :
	public CRMobject
{
public:
	CRMchildAlbumImage(void);
	~CRMchildAlbumImage(void);

	void	Update();
	bool	IsFinish() { return m_IsFinish; }
	
	void	Up();
	void	Down();

private:
	bool	m_IsUp;
	bool	m_IsDown;
	bool	m_IsFinish;
};

