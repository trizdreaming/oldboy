#pragma once
#include "RMobject.h"
#include "RMmacro.h"
class CRMchildTitleModeSelector :
	public CRMobject
{
public:
	CRMchildTitleModeSelector(void);
	virtual ~CRMchildTitleModeSelector(void);

	virtual void	Update();

	void			ModeUp();
	void			ModeDown();
	void			ModeExit();
	ModeType		GetModeType();

private:
	UINT			m_ModeIndex;
	UINT			m_MaxModes;
};

