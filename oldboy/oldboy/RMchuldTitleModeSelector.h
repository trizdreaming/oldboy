#pragma once
#include "RMobject.h"
#include "RMmacro.h"
class CRMchuldTitleModeSelector :
	public CRMobject
{
	SINGLETON(CRMchuldTitleModeSelector);
public:
	CRMchuldTitleModeSelector(void);
	~CRMchuldTitleModeSelector(void);

	virtual void	Update();

	void			ModeUp();
	void			ModeDown();
	ModeType		GetModeType();

private:
	UINT			GetIndex();
	UINT			m_ModeIndex;
	UINT			m_MaxModes;
};

