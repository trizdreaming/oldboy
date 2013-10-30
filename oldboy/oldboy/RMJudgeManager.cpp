#include "stdafx.h"
#include "oldboy.h"
#include "RMjudgeManager.h"
#include "RMobjectManager.h"

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
		CRMobjectManager::GetInstance()->AddObject( *iter , LAYER_NOTE1 );
		CRMobjectManager::GetInstance()->GetObjectList( LAYER_MEMORY_PULL )->remove(0);
		break;
	case PLAYER_TWO:
		auto& iter = CRMobjectManager::GetInstance()->GetObjectList( LAYER_MEMORY_PULL )->begin();
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
