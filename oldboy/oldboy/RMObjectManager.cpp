#include "stdafx.h"
#include "RMmacro.h"
#include "RMobject.h"
#include "RMlabel.h"
#include "RMobjectManager.h"
#include "RMlabelManager.h"
#include "RMpauseManager.h"
#include "RMitemManager.h"
#include "RMrandomGenerator.h"
#include "RMchildAlbumImage.h"
#include "RMmainLoop.h"

CRMobjectManager::CRMobjectManager(void) :
	m_TooltipIndex(0)
{
	ZeroMemory(&m_ObjectListAlbumImage, sizeof(m_ObjectListAlbumImage));
	ZeroMemory(&m_ObjectListTutorialPress, sizeof(m_ObjectListTutorialPress));
}


CRMobjectManager::~CRMobjectManager(void)
{
	for ( auto& iter : m_ObjectListLayerBackground )
	{
		auto toBeDelete = iter;
		SafeDelete( toBeDelete );
	}
	m_ObjectListLayerBackground.clear();

	for ( auto& iter : m_ObjectListLayerJudgeGauge )
	{
		auto toBeDelete = iter;
		SafeDelete( toBeDelete );
	}
	m_ObjectListLayerJudgeGauge.clear();

	for ( auto& iter : m_ObjectListLayerItem )
	{
		auto toBeDelete = iter;
		SafeDelete( toBeDelete );
	}
	m_ObjectListLayerItem.clear();

	for ( auto& iter : m_ObjectListLayerCard)
	{
		auto toBeDelete = iter;
		SafeDelete( toBeDelete );
	}
	m_ObjectListLayerCard.clear();

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

	for ( auto& iter : m_ObjectListMemoryPoolOfNote )
	{
		auto toBeDelete = iter;
		SafeDelete( toBeDelete );
	}
	m_ObjectListMemoryPoolOfNote.clear();

	for ( auto& iter : m_ObjectListTooltips )
	{
		auto toBeDelete = iter;
		SafeDelete( toBeDelete );
	}

	for ( auto& iter : m_ObjectListLayerUI )
	{
		auto toBeDelete = iter;
		SafeDelete( toBeDelete );
	}
	m_ObjectListLayerUI.clear();

	for ( auto& iter : m_ObjectListLayerPause )
	{
		auto toBeDelete = iter;
		SafeDelete( toBeDelete );
	}
	m_ObjectListLayerPause.clear();

	for ( auto& iter : m_ObjectListAlbumImage )
	{
		auto toBeDelete = iter;
		SafeDelete( toBeDelete );
	}

	for ( auto& iter : m_ObjectListTutorialPress )
	{
		auto toBeDelete = iter;
		SafeDelete( toBeDelete );
	}

	for ( auto& iter : m_ObjectListTutorialScripts )
	{
		auto toBeDelete = iter;
		SafeDelete( toBeDelete );
	}
	m_ObjectListTutorialScripts.clear();

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
		case LAYER_JUDGE_GAUGE:
			m_ObjectListLayerJudgeGauge.push_back(object);
			break;
		case LAYER_ITEM:
			m_ObjectListLayerItem.push_back(object);
			break;
		case LAYER_CARD:
			m_ObjectListLayerCard.push_back(object);
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
			m_ObjectListMemoryPoolOfNote.push_front(object);
			break;
		case LAYER_UI:
			m_ObjectListLayerUI.push_front(object);
			break;
		case LAYER_PAUSE:
			m_ObjectListLayerPause.push_front(object);
			break;
		case LAYER_TOOLTIP:
			m_ObjectListTooltips.push_back(object);
			break;
		case LAYER_SCRIPT:
			m_ObjectListTutorialScripts.push_back(object);
			break;
		default:
			break;
		}
	}
}

void CRMobjectManager::Update()
{
	if ( !CRMpauseManager::GetInstance()->IsPause() )
	{
		for ( auto& iter : m_ObjectListLayerBackground )
		{
			iter->Update();
		}
		for ( auto& iter : m_ObjectListLayerCard )
		{
			iter->Update();
		}
		for ( auto& iter : m_ObjectListLayerJudgeGauge )
		{
			iter->Update();
		}
		for ( auto& iter : m_ObjectListMemoryPoolOfNote )
		{
			iter->Update();
		}
		for ( auto& iter : m_ObjectListLayerItem )
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

	for ( auto& iter : m_ObjectListLayerUI )
	{
		iter->Update();
	}

	for ( auto& iter : m_ObjectListLayerPause )
	{
		iter->Update();
	}

	if ( m_ObjectListAlbumImage[ALBUM_IMAGE_STATIC] != nullptr )
	{
		m_ObjectListAlbumImage[ALBUM_IMAGE_STATIC]->Update();
	}

	if ( m_ObjectListTutorialPress[POSITION_UP] != nullptr )
	{
		m_ObjectListTutorialPress[POSITION_UP]->Update();
	}

	if ( m_ObjectListTutorialPress[POSITION_DOWN] != nullptr )
	{
		m_ObjectListTutorialPress[POSITION_DOWN]->Update();
	}

	for ( auto& iter : m_ObjectListTutorialScripts )
	{
		iter->Update();
	}
}

void CRMobjectManager::Render() const
{
	for ( auto& iter : m_ObjectListLayerBackground )
	{
		iter->Render();
	}
	for ( auto& iter : m_ObjectListLayerJudgeGauge )
	{
		iter->Render();
	}
	for ( auto& iter : m_ObjectListLayerItem )
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
	for ( auto& iter : m_ObjectListMemoryPoolOfNote )
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
	for ( auto& iter : m_ObjectListLayerCard )
	{
		iter->Render();
	}
	for ( auto& iter : m_ObjectListLayerLabel )
	{
		iter->Render();
	}

	if ( m_ObjectListAlbumImage[ALBUM_IMAGE_STATIC] != nullptr )
	{
		if ( m_ObjectListAlbumImage[ALBUM_IMAGE_STATIC]->GetVisible() == true )
		{
			m_ObjectListAlbumImage[ALBUM_IMAGE_STATIC]->Render();
		}
	}

	for ( auto& iter : m_ObjectListLayerUI )
	{
		iter->Render();
	}

	// 메뉴를 가리면 안 되므로 여기에 둠

	for ( auto& iter : m_ObjectListLayerPause )
	{
		iter->Render();
	}

	for ( auto& iter : m_ObjectListLayerPause )
	{
		iter->Render();
	}

	for ( auto& iter : m_ObjectListTutorialScripts )
	{
		iter->Render();
	}

	if ( m_ObjectListTutorialPress[POSITION_UP] != nullptr )
	{
		//if ( m_ObjectListTutorialPress[POSITION_UP]->GetVisible() == true )
		{
			m_ObjectListTutorialPress[POSITION_UP]->Render();
		}
	}

	if ( m_ObjectListTutorialPress[POSITION_DOWN] != nullptr )
	{
		//if ( m_ObjectListTutorialPress[POSITION_DOWN]->GetVisible() == true )
		{
			m_ObjectListTutorialPress[POSITION_DOWN]->Render();
		}
	}

}

CRMobject* CRMobjectManager::GetObjectFront( LayerType layer ) const
// 메소드 내부에서 nullptr을 리턴하므로 예외처리 확실히 할 것!
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
		if ( m_ObjectListMemoryPoolOfNote.size() == 0 )
		{
			return nullptr;
		}
		return *( m_ObjectListMemoryPoolOfNote.rbegin() );
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
		m_ObjectListMemoryPoolOfNote.push_back( GetObjectFront( layer ) );
		m_ObjectListLayerNotePlayer1.pop_back();
		break;
	case LAYER_NOTE2:
		m_ObjectListMemoryPoolOfNote.push_back( GetObjectFront( layer ) );
		m_ObjectListLayerNotePlayer2.pop_back();
		break;
	case LAYER_MEMORY_POOL:
		m_ObjectListMemoryPoolOfNote.pop_back();
		break;
	}
}



void CRMobjectManager::RemoveAllNote()
{
	CRMobject* thisNote = nullptr;

	while ( m_ObjectListLayerNotePlayer1.size() > 0 )
	{
		thisNote = GetObjectFront( LAYER_NOTE1 );
		thisNote->SetVisible(false);
		m_ObjectListMemoryPoolOfNote.push_back( thisNote );
		m_ObjectListLayerNotePlayer1.pop_back();
	}
	while ( m_ObjectListLayerNotePlayer2.size() > 0 )
	{
		thisNote = GetObjectFront( LAYER_NOTE2 );
		thisNote->SetVisible(false);
		m_ObjectListMemoryPoolOfNote.push_back( thisNote );
		m_ObjectListLayerNotePlayer2.pop_back();
	}
	for ( auto &iter : m_ObjectListMemoryPoolOfNote )
	{
		iter->SetVisible(false);
	}
}

void CRMobjectManager::RemoveNoteFromPlayerLayer( PlayerNumber playerNumber )
{
	CRMobject* thisNote = nullptr;

	if ( playerNumber == PLAYER_ONE )
	{
		while ( m_ObjectListLayerNotePlayer1.size() > 0 )
		{
			thisNote = GetObjectFront( LAYER_NOTE1 );
			thisNote->SetVisible(false);
			m_ObjectListMemoryPoolOfNote.push_back( thisNote );
			m_ObjectListLayerNotePlayer1.pop_back();
		}
	}
	else if ( playerNumber == PLAYER_TWO )
	{
		while ( m_ObjectListLayerNotePlayer2.size() > 0 )
		{
			thisNote = GetObjectFront( LAYER_NOTE2 );
			thisNote->SetVisible(false);
			m_ObjectListMemoryPoolOfNote.push_back( thisNote );
			m_ObjectListLayerNotePlayer2.pop_back();
		}
	}
	
	for ( auto &iter : m_ObjectListMemoryPoolOfNote )
	{
		iter->SetVisible(false);
	}
}

void CRMobjectManager::ShowTooltip()
{
	if ( m_TooltipIndex < 0 )
	{
		return;
	}

	auto &thisTooltip = m_ObjectListTooltips.at(m_TooltipIndex);

	if ( thisTooltip == nullptr )
	{
		return;
	}

	for ( auto& iter : m_ObjectListLayerShutter )
	{
		iter->Update();
	}

	thisTooltip->Render();
}

void CRMobjectManager::SetRandomTooltipIndex()
{
	int maxTooltip = m_ObjectListTooltips.size();

	if ( maxTooltip < 1 )
	{
		m_TooltipIndex = -1;
		return;
	}

	m_TooltipIndex = CRMrandomGenerator::GetInstance()->GetRandom(0, maxTooltip - 1);
}

bool CRMobjectManager::ShowMovingAlbumImage()
{
	if ( m_ObjectListAlbumImage[ALBUM_IMAGE_STATIC] != nullptr )
	{
		m_ObjectListAlbumImage[ALBUM_IMAGE_STATIC]->Update();
		m_ObjectListAlbumImage[ALBUM_IMAGE_STATIC]->Render();
	}
	if ( m_ObjectListAlbumImage[ALBUM_IMAGE_DYNAMIC] != nullptr )
	{
		auto thisObject = dynamic_cast<CRMchildAlbumImage*>(m_ObjectListAlbumImage[ALBUM_IMAGE_DYNAMIC]);
		if ( thisObject != nullptr)
		{
			thisObject->Update();
			thisObject->Render();
			for ( auto& iter : m_ObjectListLayerUI )
			{
				iter->Render();
			}
			return ( thisObject->IsFinish() );
		}
	}

	return false;
}

void CRMobjectManager::AddAlbumImage( CRMobject* object, AlbumImageType imageType )
{
	if ( object != nullptr )
	{
		m_ObjectListAlbumImage[imageType] = object;
	}
}

void CRMobjectManager::AddScriptPressImage( CRMobject* object, ScriptPosition scriptPositon )
{
	if ( object != nullptr && scriptPositon == POSITION_UP )
	{
		m_ObjectListTutorialPress[POSITION_UP] = object;
	}
	else if( object != nullptr && scriptPositon == POSITION_DOWN )
	{
		m_ObjectListTutorialPress[POSITION_DOWN] = object;
	}
}

void CRMobjectManager::UpAlbumImage()
{
	if ( m_ObjectListAlbumImage[ALBUM_IMAGE_DYNAMIC] != nullptr )
	{
		auto thisObject = dynamic_cast<CRMchildAlbumImage*>(m_ObjectListAlbumImage[ALBUM_IMAGE_DYNAMIC]);
		if ( thisObject != nullptr)
		{
			thisObject->Up();
		}
	}
}

void CRMobjectManager::DownAlbumImage()
{
	if ( m_ObjectListAlbumImage[ALBUM_IMAGE_DYNAMIC] != nullptr )
	{
		auto thisObject = dynamic_cast<CRMchildAlbumImage*>(m_ObjectListAlbumImage[ALBUM_IMAGE_DYNAMIC]);
		if ( thisObject != nullptr)
		{
			thisObject->Down();
		}
	}
}
