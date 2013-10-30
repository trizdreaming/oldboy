#include "stdafx.h"
#include "oldboy.h"
#include "RMJudgeManager.h"

CRMJudgeManager* CRMJudgeManager::m_pInstance = nullptr;

CRMJudgeManager::CRMJudgeManager(void)
{
}


CRMJudgeManager::~CRMJudgeManager(void)
{
}


CRMJudgeManager* CRMJudgeManager::GetInstance()
{
	if ( m_pInstance == nullptr )
	{
		m_pInstance = new CRMJudgeManager();
	}

	return m_pInstance;
}

void CRMJudgeManager::ReleaseInstance()
{
	if ( m_pInstance != nullptr )
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void CRMJudgeManager::StartNote(PLAYER_NUMBER player)
{
	switch (player)
	{
	case PLAYER_ONE:
		break;
	case PLAYER_TWO:
		break;
	case PLAYER_NO:
	default:
		break;
	}
}

void CRMJudgeManager::JudgeNote()
{

}
