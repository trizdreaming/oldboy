#include "stdafx.h"
#include "oldboy.h"
#include "RMchildEffectManager.h"

CRMchildEffectManager::CRMchildEffectManager(void):
	m_BitFlag(0x00),
	m_EffectStartPositionX(0.f),
	m_EffectStartPositionY(0.f),
	m_FlagSetter1P(0),
	m_FlagSetter2P(0)
{
}

CRMchildEffectManager::~CRMchildEffectManager(void)
{
}


//////////////////////////////////////////////////////////////////////////////
//BitFlag 사용법															//
//각 비트는 어떤 이펙트를 play 화면에 보여줘야할지 말아야 할지 스위칭		//
//한 화면에 최대 8개까지 판정 가능											//
//////////////////////////////////////////////////////////////////////////////

void CRMchildEffectManager::SetFlag( PlayerNumber targetPlayer , float positionX, float positionY )
{
	//노트를 뿌려줄 포지션 결정
	//judgeManager에서 위치값을 던져주면 저장 했다가
	//이펙트 업데이터가 포지션을 받아 쓸 수 있도록 함
	m_EffectStartPositionX = positionX;
	m_EffectStartPositionY = positionY;
	
#ifdef _DEBUG
	printf_s( "1P flag : %d , 2P flag: %d \n", m_FlagSetter1P, m_FlagSetter2P );
#endif // _DEBUG

	switch ( targetPlayer )
	{
	case PLAYER_ONE:
		m_FlagSetter1P = ++m_FlagSetter1P % 4;

		m_BitFlag |= ( 0x0010 << (3 - m_FlagSetter1P) );
#ifdef _DEBUG
		printf_s("1P BitFlag 발동! %x \n", m_BitFlag);
#endif
		break;		
	case PLAYER_TWO:
		m_FlagSetter2P = ++m_FlagSetter2P % 4;

		m_BitFlag |= ( 0x0001 << (3 - m_FlagSetter2P) );
#ifdef _DEBUG
		printf_s("2P BitFlag 발동! %x \n", m_BitFlag);
#endif
		break;

	case NO_PLAYER:
	default:
		break;
	}
}

void CRMchildEffectManager::ResetFlag()
{
	m_BitFlag = 0x00;
}


