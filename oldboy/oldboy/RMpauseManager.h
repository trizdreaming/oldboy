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

	void			SetPuaseSelectedCancel( bool const isCancel ) { m_PauseSelectCancel = isCancel; } //SM9: const??
	bool			IsPauseSelectedCancel() { return m_PauseSelectCancel; }
private:
	bool			m_IsPause;
	bool			m_PauseSelectCancel; //SM9: 이 멤버가 이 클래스 내부에서는 전혀 쓰이지 않고 있다. 이런 디자인은 커플링만 유발하는 좋지 않은 패턴이다.
	// 차라리 메인루프의 if ( CRMpauseManager::GetInstance()->IsPauseSelectedCancel() )부분을 이 클래스의 역할로 가져오는 것이 좋다.
};

