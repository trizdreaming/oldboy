#pragma once
#include "RMobject.h"

class CRMchildNote :
	public CRMobject
{
public:
	CRMchildNote(void);
	~CRMchildNote(void);

	virtual void	Update();
	virtual void	Render();
	virtual void	SetObjectType(ObjectType objectType);

private:
	ObjectType		m_Original_type;
};

