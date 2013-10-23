#pragma once
#include "oldboy.h"

class CRMmainLoop
{
private:
	CRMmainLoop(void);
	~CRMmainLoop(void);


public:
	// 싱글톤 관련 method
	static CRMmainLoop*	GetInstance();
	static void			ReleaseInstance();

	// 초기화 및 무한루프
	HRESULT					Init();
	void					RunMessageLoop();
	
	HWND					GetHwnd(){ return m_Hwnd; }				// 윈도우 핸들 반환
	static LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);	// 객체 없이도 사용 가능하도록 static으로 함


private:
	HWND	m_Hwnd;
	
	UINT	m_NowTime;
	UINT	m_PrevTime;
	UINT	m_ElapsedTime;
	UINT	m_Fps;

	//싱글톤 관련 member 변수
	static CRMmainLoop* m_pInstance;
};

