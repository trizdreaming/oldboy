#include "stdafx.h"
#include "RMmacro.h"
#include "RMnoteManager.h"
#include "RMJudgeManager.h"
#include "RMxmlLoader.h"
#include "RMnoteData.h"
#include "RMitemManager.h"

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
		}
	}

	if (m_GamePlaying)
	{
		m_ElapsedTime = timeGetTime() - m_GameStartTime;

		if ( m_ElapsedTime > (m_P1NoteReadyTime + m_PausedTime) )
		{
			// 너무 붙어 있는 노트는 생략
			int noteTurm = (m_P1NoteReadyTime - m_P1NoteBeforeTime);
			if ( noteTurm > 100 )
			{
				CRMjudgeManager::GetInstance()->StartNote( PLAYER_ONE , m_P1NoteReadyType );
				m_P1NoteBeforeTime = m_P1NoteReadyTime;
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
