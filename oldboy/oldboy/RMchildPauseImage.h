#pragma once
#include "RMobject.h"
#include "RMmacro.h"

class CRMchildPauseImage :
	public CRMobject
{
	SINGLETON(CRMchildPauseImage);

public:
	CRMchildPauseImage(void);
	~CRMchildPauseImage(void);

	virtual void	Update();
private:
	ObjectType m_ObjectType1;
};

