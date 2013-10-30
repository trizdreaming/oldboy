#pragma once
#include "oldboy.h"
#include <list>
#include "RMenumSet.h"
#include "RMobject.h"

class CRMobjectManager
{
private:
	CRMobjectManager(void);
	~CRMobjectManager(void);

public:
	static CRMobjectManager*	GetInstance();
	static void					ReleaseInstance();
	
	std::list<CRMobject*>*		GetObjectListLayer(LayerType layer);

	void	AddObject(CRMobject*	object, LayerType layer);

	void	Update();
	void	Render();


private:
	std::list<CRMobject*>		m_ObjectListLayerBackground;
	std::list<CRMobject*>		m_ObjectListLayerNote;
	std::list<CRMobject*>		m_ObjectListLayerShutter;
	std::list<CRMobject*>		m_ObjectListLayerLabel;

	static	CRMobjectManager*	m_pInstance;
};

