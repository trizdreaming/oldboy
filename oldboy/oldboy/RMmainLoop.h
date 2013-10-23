#pragma once
#include "oldboy.h"

class CRMmainLoop
{
private:
	CRMmainLoop(void);
	~CRMmainLoop(void);

//싱글톤 관련 method
public:
	static CRMmainLoop*	GetInstance();
	static void			ReleaseInstance();


public:
	void					RunMessageLoop();
	HRESULT					Init();
	
	HWND					GetHwnd(){return m_Hwnd;}
	static LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM); //객체 없이도 사용 가능하도록 static으로 함


private:
	HWND m_Hwnd;
	
	UINT m_NowTime;
	UINT m_PrevTime;
	UINT m_ElapsedTime;
	UINT m_Fps;

//싱글톤 관련 member 변수
private:
	static CRMmainLoop* m_pInstance;
};

