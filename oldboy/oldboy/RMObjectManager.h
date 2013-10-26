#pragma once
#include "oldboy.h"
#include "RMobject.h"
#include <list>

class CRMobjectManager
{
private:
	CRMobjectManager(void);
	~CRMobjectManager(void);

public:
	static CRMobjectManager*	GetInstance();
	static void					ReleaseInstance();

	void	Update();
	void	Render();

	void	AddObject(CRMobject* object);

private:
	std::list<CRMobject*>		m_ObjectList;
	static	CRMobjectManager*	m_pInstance;
};

