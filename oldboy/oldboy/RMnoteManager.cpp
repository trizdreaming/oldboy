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
	m_NoteReadyTime(0),
	m_NoteReadyLevel(0),
	m_NoteReadyType(OBJECT_NONE)
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
	m_NoteReadyTime = INT_MAX;
	m_NoteReadyLevel = 0;
	m_NoteReadyType = OBJECT_NONE;
}

void CRMnoteManager::StartNote()
{
	
	if ( m_NoteReadyTime == INT_MAX )
	{
		CRMnoteData* note = CRMxmlLoader::GetInstance()->GetNoteFirst();
		if ( note == nullptr )
		{
			m_GamePlaying = false;
		}
		else
		{
			m_NoteReadyTime = note->GetTime();
			m_NoteReadyLevel = note->GetLevel();
			m_NoteReadyType = note->GetType();
		}
	}

	if (m_GamePlaying)
	{
		m_ElapsedTime = timeGetTime() - m_GameStartTime;

		if ( m_ElapsedTime > m_NoteReadyTime )
		{
			CRMjudgeManager::GetInstance()->StartNote( PLAYER_ONE , m_NoteReadyType );
			CRMjudgeManager::GetInstance()->StartNote( PLAYER_TWO , m_NoteReadyType );
			HRESULT hr = CRMxmlLoader::GetInstance()->DeleteNoteFirst();
			if ( hr == S_FALSE )
			{
				m_GamePlaying = false;
			}
			m_NoteReadyTime = INT_MAX;
		}
	}

}
