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

void CRMjudgeManager::StartNote( PLAYER_NUMBER player )
{
	

	switch ( player )
	{
	case PLAYER_ONE:
		auto& iter = CRMobjectManager::GetInstance()->GetObjectList( LAYER_MEMORY_PULL )->begin();
		(*iter)->SetObjectType(OBJECT_NOTE_NORMAL_1);
		(*iter)->SetPosition(395, -100);
		(*iter)->SetSceneType(SCENE_PLAY);
		CRMobjectManager::GetInstance()->AddObject( *iter , LAYER_NOTE1 );
		CRMobjectManager::GetInstance()->GetObjectList( LAYER_MEMORY_PULL )->remove(0);
		break;
	case PLAYER_TWO:
		auto& iter = CRMobjectManager::GetInstance()->GetObjectList( LAYER_MEMORY_PULL )->begin();
		(*iter)->SetObjectType(OBJECT_NOTE_NORMAL_1);
		(*iter)->SetPosition(910, -100);
		(*iter)->SetSceneType(SCENE_PLAY);
		CRMobjectManager::GetInstance()->AddObject( *iter , LAYER_NOTE2 );
		CRMobjectManager::GetInstance()->GetObjectList( LAYER_MEMORY_PULL )->remove(0);
		break;
	case PLAYER_NO:
	default:
		break;
	}
}

void CRMjudgeManager::JudgeNote()
{

}
