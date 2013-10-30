#include "stdafx.h"
#include "oldboy.h"
#include "RMjudgeManager.h"
#include "RMobjectManager.h"
#include "RMobject.h"

// CRMjudgeManager* CRMjudgeManager::m_pInstance = nullptr;

CRMjudgeManager::CRMjudgeManager(void)
{
}


CRMjudgeManager::~CRMjudgeManager(void)
{
}

// CRMjudgeManager* CRMjudgeManager::GetInstance()
// {
// 	if ( m_pInstance == nullptr )
// 	{
// 		m_pInstance = new CRMjudgeManager();
// 	}
// 
// 	return m_pInstance;
// }
// 
// void CRMjudgeManager::ReleaseInstance()
// {
// 	if ( m_pInstance != nullptr )
// 	{
// 		delete m_pInstance;
// 		m_pInstance = nullptr;
// 	}
// }

void CRMjudgeManager::StartNote( PlayerNumber player )
{
	if ( CRMobjectManager::GetInstance()->GetObjectList( LAYER_MEMORY_POOL )->size() == 0 )
	{
		return; 
	}
		

	auto& iter = CRMobjectManager::GetInstance()->GetObjectList( LAYER_MEMORY_POOL )->begin();
	auto thisNote = iter;
	switch ( player )
	{
	case PLAYER_ONE:
		
		(*thisNote)->SetObjectType(OBJECT_NOTE_NORMAL_1);
		(*thisNote)->SetPosition(395, -100);
		(*thisNote)->SetSceneType(SCENE_PLAY);
		CRMobjectManager::GetInstance()->AddObject( *thisNote , LAYER_NOTE1 );
		CRMobjectManager::GetInstance()->GetObjectList( LAYER_MEMORY_POOL )->
			erase(CRMobjectManager::GetInstance()->GetObjectList( LAYER_MEMORY_POOL )->begin());
		break;
	case PLAYER_TWO:
		(*thisNote)->SetObjectType(OBJECT_NOTE_NORMAL_1);
		(*thisNote)->SetPosition(910, -100);
		(*thisNote)->SetSceneType(SCENE_PLAY);
		CRMobjectManager::GetInstance()->AddObject( *thisNote , LAYER_NOTE2 );
		CRMobjectManager::GetInstance()->GetObjectList( LAYER_MEMORY_POOL )->
			erase(CRMobjectManager::GetInstance()->GetObjectList( LAYER_MEMORY_POOL )->begin());
		break;
	case NO_PLAYER:
	default:
		break;
	}
}

void CRMjudgeManager::JudgeNote()
{
	if(CRMobjectManager::GetInstance()->GetObjectList( LAYER_NOTE1 )->size() > 0)
	{
		auto& iterP1 = CRMobjectManager::GetInstance()->GetObjectList( LAYER_NOTE1 )->begin();
		auto thisNoteP1 = iterP1;

		/*
			1. 노트한테 너 위치 어디야?

			2. 위치가 판별 범위 안이면 
			키보드 매니저한테 묻기 => 눌렸냐?  -> 구현해야 할 것 - 인풋매니저의 키 버튼 푸시

			3. 눌렸으면?
			
			3-1 하단의 사라짐 코드처럼 마찬가지로 메모리풀로 넣어줌

			3-2 판별 => 노트의 종류를 겟 

			3-3 이펙트 발동! (by 신동찬 - "char형 비트연산으로 하겠습니다.")
		*/

		// 메모리 풀로 넣어주는 코드
		if ( (*thisNoteP1)->GetPositionY() > SCREEN_SIZE_Y-1 )
		{
			CRMobjectManager::GetInstance()->AddObject( *thisNoteP1 , LAYER_MEMORY_POOL );
			CRMobjectManager::GetInstance()->GetObjectList( LAYER_NOTE1 )->
				erase(CRMobjectManager::GetInstance()->GetObjectList( LAYER_NOTE1 )->begin());
			printf("pi end\n");
		}
	}
	
	if(CRMobjectManager::GetInstance()->GetObjectList( LAYER_NOTE2 )->size() > 0)
	{
		auto& iterP2 = CRMobjectManager::GetInstance()->GetObjectList( LAYER_NOTE2 )->begin();
		auto thisNoteP2 = iterP2;


		if ( (*thisNoteP2)->GetPositionY() > SCREEN_SIZE_Y-1 )
		{
			CRMobjectManager::GetInstance()->AddObject( *thisNoteP2 , LAYER_MEMORY_POOL );
			CRMobjectManager::GetInstance()->GetObjectList( LAYER_NOTE2 )->
				erase(CRMobjectManager::GetInstance()->GetObjectList( LAYER_NOTE2 )->begin());
		}
	}
}
