#pragma once
#include "RMenumSet.h"

class CRMmainLoop
{
	SINGLETON(CRMmainLoop);
private:
	CRMmainLoop(void);
	~CRMmainLoop(void);

public:
	// 초기화 및 무한루프
	HRESULT					CreateMainLoopWindow();
	void					RunMessageLoop();

	// 씬 관리
	SceneType				GetNowScene() { return m_SceneType; }
	HRESULT					GoNextScene();
	HRESULT					GoPrevScene();

	HWND					GetHwnd() { return m_Hwnd; }				// 윈도우 핸들 반환
	static LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);	// 객체 없이도 사용 가능하도록 static으로 함

private:

	void	FindMusicData();

	// 임시 테스트 함수
	void	TestSound();
	HRESULT	TestKeyboard();

	HRESULT	CreateObject();


private:

	HWND							m_Hwnd;
	
	UINT							m_NowTime;
	UINT							m_PrevTime;
	UINT							m_ElapsedTime;
	UINT							m_Fps;

	UINT							m_FpsCheckTime;

	SceneType						m_SceneType;

	std::vector<std::string>		m_MusicVector;

	std::string						m_PlayMusicName;
};

