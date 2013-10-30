#include "stdafx.h"
#include "oldboy.h"
#include "RMjudgeManager.h"
#include "RMobjectManager.h"
#include "RMobject.h"

CRMjudgeManager* CRMjudgeManager::m_pInstance = nullptr;

CRMjudgeManager::CRMjudgeManager(void)
{
}


CRMjudgeManager::~CRMjudgeManager(void)
{
}


CRMjudgeManager* CRMjudgeManager::GetInstance()
{
	if ( m_pInstance == nullptr )
	{
		m_pInstance = new CRMjudgeManager();
	}

	return m_pInstance;
}

void CRMjudgeManager::ReleaseInstance()
{
	if ( m_pInstance != nullptr )
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void CRMjudgeManager::StartNote( PlayerNumber player )
{
	
	auto& iter = CRMobjectManager::GetInstance()->GetObjectList( LAYER_MEMORY_PULL )->begin();
	auto thisNote = iter;
	switch ( player )
	{
	case PLAYER_ONE:
		
		(*thisNote)->SetObjectType(OBJECT_NOTE_NORMAL_1);
		(*thisNote)->SetPosition(395, -100);
		(*thisNote)->SetSceneType(SCENE_PLAY);
		CRMobjectManager::GetInstance()->AddObject( *thisNote , LAYER_NOTE1 );
		CRMobjectManager::GetInstance()->GetObjectList( LAYER_MEMORY_PULL )->remove(0);
		break;
	case PLAYER_TWO:
		(*iter)->SetObjectType(OBJECT_NOTE_NORMAL_1);
		(*iter)->SetPosition(910, -100);
		(*iter)->SetSceneType(SCENE_PLAY);
		CRMobjectManager::GetInstance()->AddObject( *iter , LAYER_NOTE2 );
		CRMobjectManager::GetInstance()->GetObjectList( LAYER_MEMORY_PULL )->remove(0);
		break;
	case NO_PLAYER:
	default:
		break;
	}
}

void CRMjudgeManager::JudgeNote()
{
	auto& iter = CRMobjectManager::GetInstance()->GetObjectList( LAYER_MEMORY_PULL )->begin();
	auto thisNote = iter;
}
