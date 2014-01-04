#pragma once
#include "RMmacro.h"
#include "RMenumSet.h"

/************************************************************************/
/* �̸����� ���� �������鼭 ������ �������� ���� �׳� ���⼭ �����͸� �������ô�.                                                                     */
/************************************************************************/
class CRMglobalParameterManager
{
	SINGLETON(CRMglobalParameterManager);

private:
	CRMglobalParameterManager(void);
	~CRMglobalParameterManager(void);

public:
	void				Initialize();
	void				SetShutterP1PositionY( float P1PositionY ) { m_ShutterP1PositionY = P1PositionY; }
	void				SetShutterP2PositionY( float P2PositionY ) { m_ShutterP2PositionY = P2PositionY; }
	float				GetShutterP1PositionY() { return m_ShutterP1PositionY; }
	float				GetShutterP2PositionY() { return m_ShutterP2PositionY; }

	void				SetPlayerJudgeType( PlayerNumber playerNumber, JudgeType judgeType );			
	JudgeType			GetP1JudgeType() { return m_JudgeTypeP1; }			
	JudgeType			GetP2JudgeType() { return m_JudgeTypeP2; }

	void				SetAirTomoMode( bool airTomoOn ) { m_AirTomoOn = airTomoOn; }
	bool				GetAirTomoMode() { return m_AirTomoOn; }

private:
	float				m_ShutterP1PositionY;
	float				m_ShutterP2PositionY;

	JudgeType			m_JudgeTypeP1;
	JudgeType			m_JudgeTypeP2;

	bool				m_AirTomoOn;
};

