#include "stdafx.h"
#include "oldboy.h"
#include "RMjudgeManager.h"
#include "RMobjectManager.h"
#include "RMobject.h"
#include "RMsound.h"
#include "RMplayer1P.h"
#include "RMplayer2P.h"

CRMjudgeManager::CRMjudgeManager(void)
{
}


CRMjudgeManager::~CRMjudgeManager(void)
{
}

void CRMjudgeManager::StartNote( PlayerNumber player , ObjectType objectType )
{
	std::list<CRMobject*>* notePoolList = CRMobjectManager::GetInstance()->GetObjectList( LAYER_MEMORY_POOL );

	if ( notePoolList->size() == 0 )
	{
		return; 
	}
		

	auto& iter = notePoolList->begin();
	auto thisNote = iter;
	switch ( player )
	{
	case PLAYER_ONE:
		(*thisNote)->SetObjectType( objectType );
		(*thisNote)->SetPosition( 395, -100 );
		(*thisNote)->SetSceneType( SCENE_PLAY );
		CRMobjectManager::GetInstance()->AddObject( *thisNote , LAYER_NOTE1 );
		notePoolList->erase(notePoolList->begin());
		break;
	case PLAYER_TWO:
		(*thisNote)->SetObjectType( objectType );
		(*thisNote)->SetPosition( 910, -100 );
		(*thisNote)->SetSceneType( SCENE_PLAY );
		CRMobjectManager::GetInstance()->AddObject( *thisNote , LAYER_NOTE2 );
		notePoolList->erase(notePoolList->begin());
		break;
	case NO_PLAYER:
	default:
		break;
	}
}

void CRMjudgeManager::JudgeNote()
{
		/*
			1. 노트한테 너 위치 어디야?

			2. 위치가 판별 범위 안이면 
			키보드 매니저한테 묻기 => 눌렸냐?  -> 구현해야 할 것 - 인풋매니저의 키 버튼 푸시

			3. 눌렸으면?
			
			3-1 하단의 사라짐 코드처럼 마찬가지로 메모리풀로 넣어줌

			3-2 판별 => 노트의 종류를 겟 

			3-3 이펙트 발동! (by 신동찬 - "char형 비트연산으로 하겠습니다.")

			//545 퍼펙
			//+- 10   535 퍼팩시작, 555퍼펙끝
			//+- 30   515 굳 시작, 575굳 끝 
		*/

	std::list<CRMobject*>* note1List = CRMobjectManager::GetInstance()->GetObjectList( LAYER_NOTE1 );
	std::list<CRMobject*>* note2List = CRMobjectManager::GetInstance()->GetObjectList( LAYER_NOTE2 );
	
	////////////////////////
	//버그 해결 필요 : 겹치는 노트의 간격이 좁은 경우 첫 번째 노트 때문에 두번째 노트가 판정되지 않음
	////////////////////////

	if( note1List->size() > 0 )
	{
		auto& iterP1 = note1List->begin();
		auto thisNoteP1 = iterP1;

		// Player1 Miss 575
		if ( (*thisNoteP1)->GetPositionY() > SCREEN_SIZE_Y - 125 + NOTE_SIZE )
		{
			printf_s( "1P NoteOut Miss \n" );
			
			//score up
			CRMplayer1P::GetInstance()->AddEvent( JUDGE_MISS );

			DeleteNote( note1List );
		}
		// Player1 Perfect 
		else if ( (*thisNoteP1)->GetPositionY() > 534 && (*thisNoteP1)->GetPositionY() < 556 )
		{
			if ( IsKeyInputRight( *thisNoteP1 , note1List , PLAYER_ONE ) )
			{
				printf_s( "1P Perfect \n" );

				//score up
				CRMplayer1P::GetInstance()->AddEvent( JUDGE_PERFECT );
			}
		}
		// Player1 Good
		else if ( ( (*thisNoteP1)->GetPositionY() > 514 && (*thisNoteP1)->GetPositionY() < 576 ) )
		{
			if ( IsKeyInputRight( *thisNoteP1 , note1List , PLAYER_ONE ) )
			{
				printf_s( "1P Good \n" );

				//score up
				CRMplayer1P::GetInstance()->AddEvent( JUDGE_GOOD );
			}
		}
		// Player1 너무 빨리 눌러 MISS (a키를 누르고 있을때 good나오는 버그 회피)
		else if ( (*thisNoteP1)->GetPositionY() > 504 )
		{
			if ( IsKeyInputRight( *thisNoteP1 , note1List , PLAYER_ONE ) )
			{
				printf_s( "1P Time Miss \n" );

				//score up;
				CRMplayer1P::GetInstance()->AddEvent( JUDGE_MISS );
			}
		}

	}
	
	// Player2============================================================

	if( note2List->size() > 0 )
	{
		auto& iterP2 = note2List->begin();
		auto thisNoteP2 = iterP2;

		// Player2 Miss 575
		if ( (*thisNoteP2)->GetPositionY() > SCREEN_SIZE_Y - 125 + NOTE_SIZE )
		{
			printf_s( "2P NoteOut miss \n" );

			//score up
			CRMplayer2P::GetInstance()->AddEvent( JUDGE_MISS );

			DeleteNote( note2List );
		}
		// Player2 Perfect 
		else if ( (*thisNoteP2)->GetPositionY() > 534 && (*thisNoteP2)->GetPositionY() < 556 )
		{
			if ( IsKeyInputRight( *thisNoteP2 , note2List , PLAYER_TWO ) )
			{
				printf_s( "2P Perfect \n" );

				//score up
				CRMplayer2P::GetInstance()->AddEvent( JUDGE_PERFECT );
			}
		}
		// Player2 Good
		else if ( ( (*thisNoteP2)->GetPositionY() > 514 && (*thisNoteP2)->GetPositionY() < 576 ) )
		{
			if ( IsKeyInputRight( *thisNoteP2 , note2List , PLAYER_TWO ) )
			{
				printf_s( "2P Good \n" );

				//score up
				CRMplayer2P::GetInstance()->AddEvent( JUDGE_GOOD );
			}
		}
		// Player2 너무 빨리 눌러 MISS (a키를 누르고 있을때 good나오는 버그 회피)
		else if ( (*thisNoteP2)->GetPositionY() > 504 )
		{
			if ( IsKeyInputRight( *thisNoteP2 , note2List , PLAYER_TWO ) )
			{
				printf_s( "2P Time Miss \n" );

				//score up
				CRMplayer2P::GetInstance()->AddEvent( JUDGE_MISS );
			}
		}
	}

	printf_s("점수표 - 1P [P:%d] [G:%d] [M:%d] [C:%d] [S:%d]  2P [P:%d] [G:%d] [M:%d] [C:%d] [S:%d] \n", 
				CRMplayer1P::GetInstance()->GetCount( PERFECT_COUNT ), CRMplayer1P::GetInstance()->GetCount( GOOD_COUNT ), 
				CRMplayer1P::GetInstance()->GetCount( MISS_COUNT ), CRMplayer1P::GetInstance()->GetCount( COMBO_COUNT ), CRMplayer1P::GetInstance()->GetCount( SCORE_COUNT ),
				CRMplayer2P::GetInstance()->GetCount( PERFECT_COUNT ), CRMplayer2P::GetInstance()->GetCount( GOOD_COUNT ), 
				CRMplayer2P::GetInstance()->GetCount( MISS_COUNT ), CRMplayer2P::GetInstance()->GetCount( COMBO_COUNT ), CRMplayer2P::GetInstance()->GetCount( SCORE_COUNT )
				);
}


bool CRMjudgeManager::IsKeyInputRight( CRMobject* note , std::list<CRMobject*>* objectList , PlayerNumber player )
{
	KeyTable target1;
	KeyTable target2;
	switch ( player )
	{
	case PLAYER_ONE:
		target1 = P1_TARGET1;
		target2 = P1_TARGET2;
		break;
	case PLAYER_TWO:
		target1 = P2_TARGET1;
		target2 = P2_TARGET2;
		break;
	case NO_PLAYER:
	default:
		break;
	}

	if ( note->GetObjectType() == OBJECT_NOTE_NORMAL_1 )
	{
		if ( CRMinput::GetInstance()->GetKeyStatusByKey( target1 ) == KEY_DOWN )
		{
			DeleteNote( objectList );
			return true;
		}
	}
	else if ( note->GetObjectType() == OBJECT_NOTE_NORMAL_2 )
	{
		if ( CRMinput::GetInstance()->GetKeyStatusByKey( target2 ) == KEY_DOWN )
		{
			DeleteNote( objectList );
			return true;
		}
	}

	return false;
}


void CRMjudgeManager::DeleteNote( std::list<CRMobject*>* objectList )
{
	CRMobjectManager::GetInstance()->AddObject( *objectList->begin() , LAYER_MEMORY_POOL );
	objectList->erase(objectList->begin());
}

