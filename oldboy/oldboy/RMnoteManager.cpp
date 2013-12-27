#include "stdafx.h"
#include "RMmacro.h"
#include "RMnoteManager.h"
#include "RMJudgeManager.h"
#include "RMxmlLoader.h"
#include "RMnoteData.h"
#include "RMitemManager.h"
#include "RMairTomo.h"

CRMnoteManager::CRMnoteManager(void):
	m_GamePlaying(false),
	m_GameStartTime(0),
	m_ElapsedTime(0),
	m_PauseStartTime(0),
	m_PausedTime(0),
	m_P1NoteReadyTime(0),
	m_P1NoteBeforeTime(0),
	m_P1NoteReadyLevel(0),
	m_P1NoteReadyType(WIDGET_NONE),
	m_P2NoteReadyTime(0),
	m_P2NoteBeforeTime(0),
	m_P2NoteReadyLevel(0),
	m_P2NoteReadyType(WIDGET_NONE),
	m_P1NoteIndex(0),
	m_P2NoteIndex(0)
{
	ZeroMemory(&m_IsItemDelayOn, sizeof(m_IsItemDelayOn));
	ZeroMemory(&m_IsItemDuplicateOn, sizeof(m_IsItemDuplicateOn));
	ZeroMemory(&m_IsItemDuplicateReady, sizeof(m_IsItemDuplicateReady));
}


CRMnoteManager::~CRMnoteManager(void)
{
}

void CRMnoteManager::Initialize()
{
	m_GamePlaying = true;
	m_GameStartTime = timeGetTime();
	m_ElapsedTime = 0;
	m_PauseStartTime = timeGetTime();
	m_PausedTime = 0;
	m_P1NoteReadyTime = UINT_MAX;
	m_P1NoteBeforeTime = 0;
	m_P1NoteReadyLevel = 0;
	m_P1NoteReadyType = WIDGET_NONE;
	m_P2NoteReadyTime = UINT_MAX;
	m_P2NoteBeforeTime = 0;
	m_P2NoteReadyLevel = 0;
	m_P2NoteReadyType = WIDGET_NONE;
	m_P1NoteIndex = 0;
	m_P2NoteIndex = 0;
	ZeroMemory(&m_IsItemDelayOn, sizeof(m_IsItemDelayOn));
	ZeroMemory(&m_IsItemDuplicateOn, sizeof(m_IsItemDuplicateOn));
	ZeroMemory(&m_IsItemDuplicateReady, sizeof(m_IsItemDuplicateReady));
}

void CRMnoteManager::StartNote()
{
	// 리펙토링 하면 좋을듯 

	if ( m_P1NoteReadyTime == UINT_MAX )
	{
		CRMnoteData* p1Note = CRMxmlLoader::GetInstance()->GetNoteByIndex( m_P1NoteIndex );
		if ( p1Note == nullptr)
		{
			m_GamePlaying = false;
		}
		else
		{
			m_P1NoteReadyTime = p1Note->GetTime();
			m_P1NoteReadyLevel = p1Note->GetLevel();
			m_P1NoteReadyType = p1Note->GetType();
			++m_P1NoteIndex;
			if ( m_IsItemDelayOn[PLAYER_ONE] == true )
			{
				m_P1NoteReadyTime += 500;
			}
		}
	}

	if ( m_P2NoteReadyTime == UINT_MAX )
	{
		CRMnoteData* p2Note = CRMxmlLoader::GetInstance()->GetNoteByIndex(m_P2NoteIndex);
		if ( p2Note == nullptr )
		{
			m_GamePlaying = false;
		}
		else
		{
			m_P2NoteReadyTime = p2Note->GetTime();
			m_P2NoteReadyLevel = p2Note->GetLevel();
			m_P2NoteReadyType = p2Note->GetType();
			++m_P2NoteIndex;
			if ( m_IsItemDelayOn[PLAYER_TWO] == true )
			{
				m_P2NoteReadyTime += 500;
			}
			CRMairTomo::GetInstance()->SetRandomJudge( m_P2NoteReadyTime, m_P2NoteReadyType, m_P2NoteBeforeTime );
		}
	}

	if (m_GamePlaying)
	{
		m_ElapsedTime = timeGetTime() - m_GameStartTime;

		//////////////////////////////////////////////////////////////////////////
		// 아이템 구현중인 부분 (따다닥) 중복 리펙토링 후 통합 노트 간격 검사 부분 테스트 필요
		// 우와앙 디버깅 테스트 힘들어...
		if ( m_IsItemDuplicateOn[PLAYER_ONE] &&  m_IsItemDuplicateReady[PLAYER_ONE] )
		{
			int m_P1NoteMiddleTime = ( m_P1NoteReadyTime - m_P1NoteBeforeTime ) / 2;
			m_P1NoteMiddleTime += m_P1NoteBeforeTime;

			if ( m_ElapsedTime > (m_P1NoteMiddleTime + m_PausedTime) )
			{
				int noteTurm = (m_P1NoteMiddleTime - m_P1NoteBeforeTime);
				//printf_s("delay :%d \n",noteTurm);
				if ( noteTurm > 100 )
				{
					CRMjudgeManager::GetInstance()->StartNote( PLAYER_ONE , m_P1NoteReadyType );
					m_P1NoteBeforeTime = m_P1NoteMiddleTime;
					m_IsItemDuplicateReady[PLAYER_ONE] = false;
				}
			}
		}
		if ( m_IsItemDuplicateOn[PLAYER_TWO] &&  m_IsItemDuplicateReady[PLAYER_TWO] )
		{
			int m_P2NoteMiddleTime = ( m_P2NoteReadyTime - m_P2NoteBeforeTime ) / 2;
			m_P2NoteMiddleTime += m_P2NoteBeforeTime;

			if ( m_ElapsedTime > (m_P2NoteMiddleTime + m_PausedTime) )
			{
				int noteTurm = (m_P2NoteMiddleTime - m_P2NoteBeforeTime);
				if ( noteTurm > 100 )
				{
					CRMjudgeManager::GetInstance()->StartNote( PLAYER_TWO , m_P1NoteReadyType );
					m_P2NoteBeforeTime = m_P2NoteMiddleTime;
					m_IsItemDuplicateReady[PLAYER_TWO] = false;
				}
			}
		}

		//////////////////////////////////////////////////////////////////////////

		if ( m_ElapsedTime > (m_P1NoteReadyTime + m_PausedTime) )
		{
			// 너무 붙어 있는 노트는 생략
			int noteTurm = (m_P1NoteReadyTime - m_P1NoteBeforeTime);
			if ( noteTurm > 100 )
			{
				CRMjudgeManager::GetInstance()->StartNote( PLAYER_ONE , m_P1NoteReadyType );
				m_P1NoteBeforeTime = m_P1NoteReadyTime;
				m_IsItemDuplicateReady[PLAYER_ONE] = true;
			}
			m_P1NoteReadyTime = UINT_MAX;
		}
		if ( m_ElapsedTime > (m_P2NoteReadyTime + m_PausedTime) )
		{
			int noteTurm = (m_P2NoteReadyTime - m_P2NoteBeforeTime);
			if ( noteTurm > 100 )
			{
				CRMjudgeManager::GetInstance()->StartNote( PLAYER_TWO , m_P2NoteReadyType );
				m_P2NoteBeforeTime = m_P2NoteReadyTime;
				m_IsItemDuplicateReady[PLAYER_TWO] = true;
			}
			m_P2NoteReadyTime = UINT_MAX;
		}
	}

}

void CRMnoteManager::StartItemDelay( PlayerNumber player )
{
	m_IsItemDelayOn[player] = true;
}

void CRMnoteManager::StopItemDelay( PlayerNumber player )
{
	m_IsItemDelayOn[player] = false;
}

void CRMnoteManager::StartItemDuplicate( PlayerNumber player )
{
	m_IsItemDuplicateOn[player] = true;
	m_IsItemDuplicateReady[player] = true;
}

void CRMnoteManager::StopItemDuplicate( PlayerNumber player )
{
	m_IsItemDuplicateOn[player] = false;
	m_IsItemDuplicateReady[player] = false;
}
