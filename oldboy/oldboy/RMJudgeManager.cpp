#include "stdafx.h"
#include "oldboy.h"
#include "RMjudgeManager.h"
#include "RMobjectManager.h"
#include "RMobject.h"

// CRMjudgeManager* CRMjudgeManager::m_pInstance = nullptr;

CRMjudgeManager::CRMjudgeManager(void)
{
}


CRMjudgeManager::~CRMjudgeManager(void)
{
}

// CRMjudgeManager* CRMjudgeManager::GetInstance()
// {
// 	if ( m_pInstance == nullptr )
// 	{
// 		m_pInstance = new CRMjudgeManager();
// 	}
// 
// 	return m_pInstance;
// }
// 
// void CRMjudgeManager::ReleaseInstance()
// {
// 	if ( m_pInstance != nullptr )
// 	{
// 		delete m_pInstance;
// 		m_pInstance = nullptr;
// 	}
// }

void CRMjudgeManager::StartNote( PlayerNumber player )
{
	if(CRMobjectManager::GetInstance()->GetObjectList( LAYER_MEMORY_POOL )->size() == 0)
		return; 

	auto& iter = CRMobjectManager::GetInstance()->GetObjectList( LAYER_MEMORY_POOL )->begin();
	auto thisNote = iter;
	switch ( player )
	{
	case PLAYER_ONE:
		
		(*thisNote)->SetObjectType(OBJECT_NOTE_NORMAL_1);
		(*thisNote)->SetPosition(395, -100);
		(*thisNote)->SetSceneType(SCENE_PLAY);
		CRMobjectManager::GetInstance()->AddObject( *thisNote , LAYER_NOTE1 );
		CRMobjectManager::GetInstance()->GetObjectList( LAYER_MEMORY_POOL )->remove(0);
		break;
	case PLAYER_TWO:
		(*thisNote)->SetObjectType(OBJECT_NOTE_NORMAL_1);
		(*thisNote)->SetPosition(910, -100);
		(*thisNote)->SetSceneType(SCENE_PLAY);
		CRMobjectManager::GetInstance()->AddObject( *thisNote , LAYER_NOTE2 );
		CRMobjectManager::GetInstance()->GetObjectList( LAYER_MEMORY_POOL )->remove(0);
		break;
	case NO_PLAYER:
	default:
		break;
	}
}

void CRMjudgeManager::JudgeNote()
{
	if(CRMobjectManager::GetInstance()->GetObjectList( LAYER_NOTE1 )->size() > 0)
	{
		auto& iterP1 = CRMobjectManager::GetInstance()->GetObjectList( LAYER_NOTE1 )->begin();
		auto thisNoteP1 = iterP1;
		/*printf("pi end\n");*/
		if ( (*thisNoteP1)->GetPositionY() > SCREEN_SIZE_Y )
		{
			CRMobjectManager::GetInstance()->AddObject( *thisNoteP1 , LAYER_MEMORY_POOL );
			CRMobjectManager::GetInstance()->GetObjectList( LAYER_NOTE1 )->remove(0);
			printf("pi end\n");
		}
	}
	
	if(CRMobjectManager::GetInstance()->GetObjectList( LAYER_NOTE2 )->size() > 0)
	{
		auto& iterP2 = CRMobjectManager::GetInstance()->GetObjectList( LAYER_NOTE2 )->begin();
		auto thisNoteP2 = iterP2;


		if ( (*thisNoteP2)->GetPositionY() > SCREEN_SIZE_Y )
		{
			CRMobjectManager::GetInstance()->AddObject( *thisNoteP2 , LAYER_MEMORY_POOL );
			CRMobjectManager::GetInstance()->GetObjectList( LAYER_NOTE2 )->remove(0);
		}
	}
}
