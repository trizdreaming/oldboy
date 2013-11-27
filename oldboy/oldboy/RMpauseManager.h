#pragma once
#include "RMmacro.h"
class CRMpauseManager
{
	SINGLETON(CRMpauseManager);

public:
	CRMpauseManager(void);
	~CRMpauseManager(void);

	void			ShowPause();
	void			ClosePause();
	bool			IsPause() { return m_IsPause; }

	void			SetPuaseSelectedCancel( bool const isCancel ) { m_PauseSelectCancel = isCancel; }
	bool			IsPauseSelectedCancel() { return m_PauseSelectCancel; }
private:
	bool			m_IsPause;
	bool			m_PauseSelectCancel;
};

