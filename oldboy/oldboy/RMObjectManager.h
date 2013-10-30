#pragma once

#include "RMenumSet.h"

class CRMobject;

class CRMobjectManager
{
private:
	CRMobjectManager(void);
	~CRMobjectManager(void);

public:
	static CRMobjectManager*	GetInstance();
	static void					ReleaseInstance();
	
	std::list<CRMobject*>*		GetObjectList(LayerType layer);

	void	AddObject(CRMobject*	object, LayerType layer);

	void	Update();
	void	Render();


private:
	std::list<CRMobject*>		m_ObjectListLayerBackground;

	std::list<CRMobject*>		m_ObjectListLayerNotePlayer1;
	std::list<CRMobject*>		m_ObjectListLayerNotePlayer2;
	std::list<CRMobject*>		m_ObjectListLayerNoteHit;

	std::list<CRMobject*>		m_ObjectListLayerEffect;
	std::list<CRMobject*>		m_ObjectListLayerShutter;
	std::list<CRMobject*>		m_ObjectListLayerLabel;

	std::list<CRMobject*>		m_ObjectListMemeoryPullOfNote;

	static	CRMobjectManager*	m_pInstance;
};

