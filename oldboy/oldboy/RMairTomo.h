#pragma once
#include "RMplayer.h"
#include "RMmacro.h"

class CRMairTomo:
	public CRMplayer
{
	SINGLETON(CRMairTomo);

public:
	void	Initialize();
	void	SetRandomJudge( UINT NextNoteTime, WidgetType NextNoteType , UINT BeforeNoteTime );
	void	PlayVirtualPlayer();
	void	ItemVirtualPlayer();

private:
	CRMairTomo(void);
	~CRMairTomo(void);

private:
	UINT					m_Mental;
	UINT					m_KeyInputReadyTime;
	WidgetType				m_KeyInputReadyType;
	std::list<UINT>			m_InputReadyList;
	std::list<WidgetType>	m_InputReadyType;

	UINT					m_ReadyItem;
};

