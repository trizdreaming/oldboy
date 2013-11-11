#include "stdafx.h"
#include "oldboy.h"

#include "RMobject.h"
#include "RMlabel.h"
#include "RMobjectManager.h"
#include "RMlabelManager.h"


CRMobjectManager::CRMobjectManager(void)
{
	m_ObjectListLayerBackground.clear();
	m_ObjectListLayerNotePlayer1.clear();
	m_ObjectListLayerNotePlayer2.clear();
	m_ObjectListLayerNoteHit.clear();
	m_ObjectListLayerEffect.clear();
	m_ObjectListLayerShutter.clear();
	m_ObjectListLayerLabel.clear();
	m_ObjectListMemeoryPullOfNote.clear();
}


CRMobjectManager::~CRMobjectManager(void)
{
	for ( auto& iter : m_ObjectListLayerBackground )
	{
		auto toBeDelete = iter;
		SafeDelete( toBeDelete );
	}
	m_ObjectListLayerBackground.clear();

	for ( auto& iter : m_ObjectListLayerNotePlayer1 )
	{
		auto toBeDelete = iter;
		SafeDelete( toBeDelete );
	}
	m_ObjectListLayerNotePlayer1.clear();

	for ( auto& iter : m_ObjectListLayerNotePlayer2 )
	{
		auto toBeDelete = iter;
		SafeDelete( toBeDelete );
	}
	m_ObjectListLayerNotePlayer2.clear();

	for ( auto& iter : m_ObjectListLayerNoteHit )
	{
		auto toBeDelete = iter;
		SafeDelete( toBeDelete );
	}
	m_ObjectListLayerNoteHit.clear();

	for ( auto& iter : m_ObjectListLayerEffect )
	{
		auto toBeDelete = iter;
		SafeDelete( toBeDelete );
	}
	m_ObjectListLayerEffect.clear();

	for ( auto& iter : m_ObjectListLayerShutter )
	{
		auto toBeDelete = iter;
		SafeDelete( toBeDelete );
	}
	m_ObjectListLayerShutter.clear();

	/*
	for ( auto& iter : m_ObjectListLayerLabel )
	{
		auto toBeDelete = iter;
		SafeDelete( toBeDelete );
	}
	라벨 매니저에서 이미 해당 영역 메모리 해제하였음
	*/
	m_ObjectListLayerLabel.clear();

	for ( auto& iter : m_ObjectListMemeoryPullOfNote )
	{
		auto toBeDelete = iter;
		SafeDelete( toBeDelete );
	}
	m_ObjectListMemeoryPullOfNote.clear();
}

void CRMobjectManager::AddObject( CRMobject* object, LayerType layer )
{
	if ( object != nullptr )
	{
		switch ( layer )
		{
		case LAYER_BACKGROUND:
			m_ObjectListLayerBackground.push_back(object);
			break;
		case LAYER_NOTE1:
			m_ObjectListLayerNotePlayer1.push_front(object);
			break;
		case LAYER_NOTE2:
			m_ObjectListLayerNotePlayer2.push_front(object);
			break;
		case LAYER_NOTE_HIT:
			m_ObjectListLayerNoteHit.push_back(object);
			break;
		case LAYER_EFFECT:
			m_ObjectListLayerEffect.push_back(object);
			break;
		case LAYER_SHUTTER:
			m_ObjectListLayerShutter.push_back(object);
			break;
		case LAYER_LABEL:
			m_ObjectListLayerLabel.push_back(object);
			break;
		case LAYER_MEMORY_POOL:
			m_ObjectListMemeoryPullOfNote.push_front(object);
			break;
		case LAYER_NONE:
			break;
		default:
			break;
		}
	}

	return;
}

void CRMobjectManager::Update()
{
	for ( auto& iter : m_ObjectListLayerBackground )
	{
		iter->Update();
	}
	for ( auto& iter : m_ObjectListMemeoryPullOfNote )
	{
		iter->Update();
	}
	for ( auto& iter : m_ObjectListLayerNotePlayer1 )
	{
		iter->Update();
	}
	for ( auto& iter : m_ObjectListLayerNotePlayer2 )
	{
		iter->Update();
	}
	for ( auto& iter : m_ObjectListLayerEffect )
	{
		iter->Update();
	}
	for ( auto& iter : m_ObjectListLayerNoteHit )
	{
		iter->Update();
	}
	for ( auto& iter : m_ObjectListLayerShutter )
	{
		iter->Update();
	}
	
	m_ObjectListLayerLabel.clear();
	CRMobject* thisLabel = nullptr;

	// friend class로 라벨 매니저에 접근해서 라벨 맵의 원소를 직접 읽어옴
	for ( auto& iter : CRMlabelManager::GetInstance()->m_LabelMap )
	{
		thisLabel = iter.second;

		if ( thisLabel->GetVisible() == false )
		{
			continue;
		}

		thisLabel->Update();
		m_ObjectListLayerLabel.push_back( thisLabel );
		// 렌더링을 하기 위해 렌더링 레이어에 집어 넣음
	}
}

void CRMobjectManager::Render()
{
	for ( auto& iter : m_ObjectListLayerBackground )
	{
		iter->Render();
	}
	for ( auto& iter : m_ObjectListLayerNotePlayer1 )
	{
		iter->Render();
	}
	for ( auto& iter : m_ObjectListLayerNotePlayer2 )
	{
		iter->Render();
	}
	for ( auto& iter : m_ObjectListMemeoryPullOfNote )
	{
		iter->Render();
	}
	for ( auto& iter : m_ObjectListLayerEffect )
	{
		iter->Render();
	}
	for ( auto& iter : m_ObjectListLayerNoteHit )
	{
		iter->Render();
	}
	for ( auto& iter : m_ObjectListLayerShutter )
	{
		iter->Render();
	}
	for ( auto& iter : m_ObjectListLayerLabel )
	{
		iter->Render();
	}
}
/*
std::list<CRMobject*>* CRMobjectManager::GetObjectList( LayerType layer )
{
	switch ( layer )
	{
	case LAYER_BACKGROUND:
		return &m_ObjectListLayerBackground;
	case LAYER_NOTE1:
		return &m_ObjectListLayerNotePlayer1;
	case LAYER_NOTE2:
		return &m_ObjectListLayerNotePlayer2;
	case LAYER_EFFECT:
		return &m_ObjectListLayerEffect;
	case LAYER_NOTE_HIT:
		return &m_ObjectListLayerNoteHit;
	case LAYER_SHUTTER:
		return &m_ObjectListLayerShutter;
	case LAYER_LABEL:
		return &m_ObjectListLayerLabel;
	case LAYER_MEMORY_POOL:
		return &m_ObjectListMemeoryPullOfNote;
	case NO_LAYER:
	default:
		return &m_ObjectListLayerBackground;
	}
	return &m_ObjectListLayerBackground;
}
*/

CRMobject* CRMobjectManager::GetObjectFront( LayerType layer )
{
	switch ( layer )
	{
	case LAYER_NOTE1:
		if ( m_ObjectListLayerNotePlayer1.size() == 0 )
		{
			return nullptr;
		}
		return *( m_ObjectListLayerNotePlayer1.rbegin() );
	case LAYER_NOTE2:
		if ( m_ObjectListLayerNotePlayer2.size() == 0 )
		{
			return nullptr;
		}
		return *( m_ObjectListLayerNotePlayer2.rbegin() );
	case LAYER_MEMORY_POOL:
		if ( m_ObjectListMemeoryPullOfNote.size() == 0 )
		{
			return nullptr;
		}
		return *( m_ObjectListMemeoryPullOfNote.rbegin() );
	case LAYER_NONE:
	default:
		return nullptr;
	}
}


void CRMobjectManager::DeleteNoteListFront( LayerType layer )
{
	switch ( layer )
	{
	case LAYER_NOTE1:
		m_ObjectListMemeoryPullOfNote.push_back( GetObjectFront( layer ) );
		m_ObjectListLayerNotePlayer1.pop_back();
		break;
	case LAYER_NOTE2:
		m_ObjectListMemeoryPullOfNote.push_back( GetObjectFront( layer ) );
		m_ObjectListLayerNotePlayer2.pop_back();
		break;
	case LAYER_MEMORY_POOL:
		m_ObjectListMemeoryPullOfNote.pop_back();
		break;
	}
}
