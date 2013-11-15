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

private:
	bool			m_GamePlaying;
	UINT			m_GameStartTime;
	UINT			m_ElapsedTime;

	UINT			m_NoteReadyTime;
	UINT			m_NoteReadyLevel;
	ObjectType		m_NoteReadyType;
};

