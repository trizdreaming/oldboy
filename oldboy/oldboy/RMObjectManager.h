#pragma once
#include "oldboy.h"
#include "RMobject.h"
#include <list>
#include "RMEnumLayerType.h"

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

	void	AddObject(CRMobject* object, LayerType layer);

private:
	std::list<CRMobject*>		m_ObjectListLayer1;
	std::list<CRMobject*>		m_ObjectListLayer2;
	std::list<CRMobject*>		m_ObjectListLayer3;
	std::list<CRMobject*>		m_ObjectListLayer4;

	static	CRMobjectManager*	m_pInstance;
};

