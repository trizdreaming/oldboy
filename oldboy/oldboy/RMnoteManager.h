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

	void			StartPause() { m_GamePlaying = false; m_PauseStartTime = timeGetTime(); };
	void			EndPause() { m_GamePlaying = true; m_PausedTime = m_PausedTime + ( timeGetTime() - m_PauseStartTime ); };

private:
	bool			m_GamePlaying;

	UINT			m_GameStartTime;
	UINT			m_ElapsedTime;

	UINT			m_PauseStartTime;
	UINT			m_PausedTime;

	UINT			m_NoteReadyTime;
	UINT			m_NoteReadyLevel;
	ObjectType		m_NoteReadyType;
};

