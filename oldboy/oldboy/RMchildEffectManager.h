#pragma once
#include "oldboy.h" 
//왜 다른 매니저들은 cpp에 include해도 singletone이 되는가? 덕철이형 알려줘요.
#include "RMenumSet.h"
#include "RMobject.h"

class CRMchildEffectManager
{
	SINGLETON(CRMchildEffectManager);

private:
	CRMchildEffectManager(void);
	~CRMchildEffectManager(void);

public:
	void SetFlag(PlayerNumber targetPlayer , float m_PositionX, float m_PositionY);
	void ResetFlag();

	float GetStartPositionX() {return m_EffectStartPositionX; }
	float GetStartPositionY() {return m_EffectStartPositionY; }
	char GetFlag() {return m_BitFlag;}

private:
	int m_FlagSetter1P; //어떤 비트 포지션에 넣을지 모듈러 연산으로 확인
	int m_FlagSetter2P; //어떤 비트 포지션에 넣을지 모듈러 연산으로 확인
	char m_BitFlag;
	float m_EffectStartPositionX;
	float m_EffectStartPositionY;
};

