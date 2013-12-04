#include "stdafx.h"
#include "RMmacro.h"
#include "RMnoteManager.h"
#include "RMJudgeManager.h"
#include "RMxmlLoader.h"
#include "RMnoteData.h"

CRMnoteManager::CRMnoteManager(void):
	m_GamePlaying(false),
	m_GameStartTime(0),
	m_ElapsedTime(0),
	m_PauseStartTime(0),
	m_PausedTime(0),
	m_P1NoteReadyTime(0),
	m_P1NoteReadyLevel(0),
	m_P1NoteReadyType(OBJECT_NONE),
	m_P2NoteReadyTime(0),
	m_P2NoteReadyLevel(0),
	m_P2NoteReadyType(OBJECT_NONE),
	m_P1NoteIndex(0),
	m_P2NoteIndex(0)
{
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
	m_P1NoteReadyLevel = 0;
	m_P1NoteReadyType = OBJECT_NONE;
	m_P2NoteReadyTime = UINT_MAX;
	m_P2NoteReadyLevel = 0;
	m_P2NoteReadyType = OBJECT_NONE;
	m_P1NoteIndex = 0;
	m_P2NoteIndex = 0;
}

void CRMnoteManager::StartNote()
{
	
	if ( m_P1NoteReadyTime == UINT_MAX )
	{
		CRMnoteData* p1Note = CRMxmlLoader::GetInstance()->GetNoteByIndex(m_P1NoteIndex);
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
		}
	}

	if (m_GamePlaying)
	{
		m_ElapsedTime = timeGetTime() - m_GameStartTime;

		if ( m_ElapsedTime > (m_P1NoteReadyTime + m_PausedTime) )
		{
			CRMjudgeManager::GetInstance()->StartNote( PLAYER_ONE , m_P1NoteReadyType );
			m_P1NoteReadyTime = UINT_MAX;
		}
		if ( m_ElapsedTime > (m_P2NoteReadyTime + m_PausedTime) )
		{
			CRMjudgeManager::GetInstance()->StartNote( PLAYER_TWO , m_P2NoteReadyType );
			m_P2NoteReadyTime = UINT_MAX;
		}
	}

}
