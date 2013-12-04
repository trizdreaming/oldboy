#pragma once
#include "RMenumSet.h"

class CRMnoteData;

class CRMnoteManager
{
	SINGLETON(CRMnoteManager);

public:
	CRMnoteManager(void);
	~CRMnoteManager(void);

	void			Initialize();
	void			StartNote();

	void			StartPause() { if ( m_GamePlaying ) { m_GamePlaying = false; m_PauseStartTime = timeGetTime(); } };
	void			EndPause() { m_GamePlaying = true; m_PausedTime = m_PausedTime + ( timeGetTime() - m_PauseStartTime ); };

private:
	bool			m_GamePlaying;

	UINT			m_GameStartTime;
	UINT			m_ElapsedTime;

	UINT			m_PauseStartTime;
	UINT			m_PausedTime;

	UINT			m_P1NoteReadyTime;
	UINT			m_P1NoteReadyLevel;
	ObjectType		m_P1NoteReadyType;

	UINT			m_P2NoteReadyTime;
	UINT			m_P2NoteReadyLevel;
	ObjectType		m_P2NoteReadyType;

	UINT			m_P1NoteIndex;
	UINT			m_P2NoteIndex;
};

