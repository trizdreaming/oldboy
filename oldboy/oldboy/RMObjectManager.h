#pragma once

#include "RMenumSet.h"

class CRMobject;

class CRMobjectManager
{
	SINGLETON(CRMobjectManager);

private:
	CRMobjectManager(void);
	~CRMobjectManager(void);

public:

	std::list<CRMobject*>*		GetObjectList(LayerType layer);  //SM9: 사실 이렇게 내부 자료구조를 통째로 외부에서 iterate 도는 것도 좋은 구조는 아니다.
																	// 정 안되면, 오브젝트 하나씩 꺼내서 처리할 수 있도록 GetObjectFirst(), GetObjectNext()식으로 쓰는게 좋다

	void	AddObject(CRMobject* bject, LayerType layer);

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
};

