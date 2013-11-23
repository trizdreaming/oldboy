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

	void			SetPause( const bool isPause = true ) { m_IsPaused = isPause; };

private:
	bool			m_GamePlaying;
	bool			m_IsPaused;

	UINT			m_GameStartTime;
	UINT			m_ElapsedTime;
	UINT			m_PausedTime;

	UINT			m_NoteReadyTime;
	UINT			m_NoteReadyLevel;
	ObjectType		m_NoteReadyType;
};

