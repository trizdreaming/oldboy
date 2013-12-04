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
	
	CRMobject*					GetObjectFront( LayerType layer ) const;
	// 메소드 내부에서 nullptr을 리턴하므로 예외처리 확실히 할 것!

	void						ChargeNoteList( LayerType layer );
	void						DeleteNoteListFront( LayerType layer );
	
	void						RemoveAllNote();

	void						AddObject( CRMobject* bject, LayerType layer );

	void						Update(); // const
	void						Render() const;

private:
	std::list<CRMobject*>		m_ObjectListLayerBackground;

	std::list<CRMobject*>		m_ObjectListLayerJudgeGauge;
	std::list<CRMobject*>		m_ObjectListLayerItem;
	std::list<CRMobject*>		m_ObjectListLayerCard;
	
	std::list<CRMobject*>		m_ObjectListLayerNotePlayer1;
	std::list<CRMobject*>		m_ObjectListLayerNotePlayer2;
	std::list<CRMobject*>		m_ObjectListLayerNoteHit;

	std::list<CRMobject*>		m_ObjectListLayerEffect;
	std::list<CRMobject*>		m_ObjectListLayerShutter;
	std::list<CRMobject*>		m_ObjectListLayerLabel;
	std::list<CRMobject*>		m_ObjectListLayerPause;

	std::list<CRMobject*>		m_ObjectListMemoryPoolOfNote;
};

