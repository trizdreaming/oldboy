#pragma once
#include "RMplayer.h"
#include "RMmacro.h"

class CRMvirtualPlayer:
	public CRMplayer
{
	SINGLETON(CRMvirtualPlayer);

public:
	void	Initialize();
	void	SetRandomJudge( UINT NextNoteTime, WidgetType NextNoteType , UINT BeforeNoteTime );
	void	PlayVirtualPlayer();
	void	ItemVirtualPlayer();

private:
	CRMvirtualPlayer(void);
	~CRMvirtualPlayer(void);

private:
	UINT					m_Mental;
	UINT					m_KeyInputReadyTime;
	WidgetType				m_KeyInputReadyType;
	std::list<UINT>			m_InputReadyList;
	std::list<WidgetType>	m_InputReadyType;

	UINT					m_ReadyItem;
};

