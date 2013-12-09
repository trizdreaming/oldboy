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

	void			StartPause() { if ( m_GamePlaying ) { m_GamePlaying = false; m_PauseStartTime = timeGetTime(); } };
	void			EndPause() { m_GamePlaying = true; m_PausedTime = m_PausedTime + ( timeGetTime() - m_PauseStartTime ); };

	// 딜레이 아이템 설정
	void			StartItemDelay( PlayerNumber player );
	void			StopItemDelay( PlayerNumber player );

	void			StartItemDuplicate( PlayerNumber player );
	void			StopItemDuplicate( PlayerNumber player );

private:
	bool			m_GamePlaying;

	UINT			m_GameStartTime;
	UINT			m_ElapsedTime;

	UINT			m_PauseStartTime;
	UINT			m_PausedTime;

	UINT			m_P1NoteReadyTime;
	UINT			m_P1NoteBeforeTime;
	UINT			m_P1NoteReadyLevel;
	WidgetType		m_P1NoteReadyType;

	UINT			m_P2NoteReadyTime;
	UINT			m_P2NoteBeforeTime;
	UINT			m_P2NoteReadyLevel;
	WidgetType		m_P2NoteReadyType;

	UINT			m_P1NoteIndex;
	UINT			m_P2NoteIndex;

	// 아이템 발동 상황을 표시
	std::array<bool, PLAYER_MAX>	m_IsItemDelayOn;
	std::array<bool, PLAYER_MAX>	m_IsItemDuplicateOn;
	std::array<bool, PLAYER_MAX>	m_IsItemDuplicateReady;
};

