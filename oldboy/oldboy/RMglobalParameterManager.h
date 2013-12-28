#pragma once
#include "RMmacro.h"

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

private:
	float				m_ShutterP1PositionY;
	float				m_ShutterP2PositionY;
};

