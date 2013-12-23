#pragma once
#include "RMobject.h"
class CRMchildCpuMode :
	public CRMobject
{
public:
	CRMchildCpuMode(void);
	virtual ~CRMchildCpuMode(void);

	virtual void	Update();

private:
	UINT			m_AnimationFrame;
};

