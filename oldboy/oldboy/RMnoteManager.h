#pragma once
#include "RMenumSet.h"
#include "RMmacro.h"

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
	int				m_GameStartTime;
	int				m_ElapsedTime;

	int				m_NoteReadyTime;
	int				m_NoteReadyLevel;
	ObjectType		m_NoteReadyType;
};

