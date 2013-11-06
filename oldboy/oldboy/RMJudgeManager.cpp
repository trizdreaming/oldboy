#include "stdafx.h"
#include "oldboy.h"
#include "RMjudgeManager.h"
#include "RMobjectManager.h"
#include "RMobject.h"
#include "RMsound.h"
#include "RMplayer1P.h"
#include "RMplayer2P.h"
#include "RMchildEffectImage.h"
#include "RMlabel.h"
#include "RMchildEffectManager.h"

CRMjudgeManager::CRMjudgeManager(void) :
	m_Player1Judge(NO_JUDGE), m_Player2Judge(NO_JUDGE)
{
}


CRMjudgeManager::~CRMjudgeManager(void)
{
}

void CRMjudgeManager::StartNote( PlayerNumber player , ObjectType objectType )
{
		
	CRMobject* thisNote = CRMobjectManager::GetInstance()->GetObjectFront( LAYER_MEMORY_POOL );
	if ( thisNote == nullptr )
	{
		return; 
	}

	switch ( player )
	{
	case PLAYER_ONE:
		thisNote->SetObjectType( objectType );
		thisNote->SetPosition( 395, -100 );
		thisNote->SetVisible(true);
		thisNote->SetSceneType( SCENE_PLAY );
		CRMobjectManager::GetInstance()->AddObject( thisNote , LAYER_NOTE1 );
		CRMobjectManager::GetInstance()->DeleteNoteListFront( LAYER_MEMORY_POOL );
		break;
	case PLAYER_TWO:
		thisNote->SetObjectType( objectType );
		thisNote->SetPosition( 910, -100 );
		thisNote->SetVisible(true);
		thisNote->SetSceneType( SCENE_PLAY );
		CRMobjectManager::GetInstance()->AddObject( thisNote , LAYER_NOTE2 );
		CRMobjectManager::GetInstance()->DeleteNoteListFront( LAYER_MEMORY_POOL );
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



	//2p는 키 이펙트 추가 안 함
	
	// Player2============================================================

	JudgeNoteByPlayer( PLAYER_ONE );
	JudgeNoteByPlayer( PLAYER_TWO );
}


void CRMjudgeManager::JudgeNoteByPlayer( PlayerNumber playerNumber )
{

	LayerType playerLayer;
	CRMplayer* playerClass = nullptr;
	switch ( playerNumber )
	{
	case PLAYER_ONE:
		playerLayer = LAYER_NOTE1;
		playerClass = CRMplayer1P::GetInstance();
		break;
	case PLAYER_TWO:
		playerLayer = LAYER_NOTE2;
		playerClass = CRMplayer2P::GetInstance();
		break;
	case NO_PLAYER:
	default:
		break;
	}

	CRMobject* thisNote = CRMobjectManager::GetInstance()->GetObjectFront( playerLayer );
	if ( thisNote != nullptr )
	{
		if ( thisNote->GetPositionY() > 555 )
		{
#ifdef _DEBUG
			printf_s( "%dP NoteOut Miss \n",playerLayer );
#endif // _DEBUG

			//score up
			playerClass->AddEvent( JUDGE_MISS );
			PrintScore( playerNumber, JUDGE_MISS );

			CRMobjectManager::GetInstance()->DeleteNoteListFront( playerLayer );
		}
		// Player1 Perfect 
		else if ( thisNote->GetPositionY() > 534 && thisNote->GetPositionY() < 556 )
		{
			if ( IsKeyInputRight( thisNote , playerNumber ) )
			{

				//effect 플래그 세팅
				//플래그만 세팅하면 이펙트 노출은 알아서 되게끔 하자
				//플래그 세팅하는 곳은 effect manager(싱글톤)를 따로 두고 진행합시다
				/*
						1. judge에서 effect Manager flag세팅
						2. childeffectimage에서 flag 확인
						3. childeffectimage에서 flag 확인 후 다시 flag 초기화
				*/
				float hitPositionX = thisNote->GetPositionX();
				float hitPositionY = thisNote->GetPositionY();
				CRMchildEffectManager::GetInstance()->SetFlag( playerNumber , hitPositionX , hitPositionY );

#ifdef _DEBUG
				printf_s( "%dP Perfect \n", playerLayer );
#endif // _DEBUG

				//score up
				playerClass->AddEvent( JUDGE_PERFECT );
				PrintScore( playerNumber, JUDGE_PERFECT );

				//키 누르면서 바로 지우면 플래그 세팅이 안됨
				//키를 누르면 무조건 세팅이 되면 miss 처리 불가
				//deleteNote 이동
				CRMobjectManager::GetInstance()->DeleteNoteListFront( playerLayer );
			}
		}
		// Player1 Good
		else if ( ( thisNote->GetPositionY() > 514 && thisNote->GetPositionY() < 576 ) )
		{
			if ( IsKeyInputRight( thisNote , playerNumber ) )
			{
				float hitPositionX = thisNote->GetPositionX();
				float hitPositionY = thisNote->GetPositionY();
				CRMchildEffectManager::GetInstance()->SetFlag( playerNumber , hitPositionX , hitPositionY );
#ifdef _DEBUG
				printf_s( "%dP Good \n", playerLayer );
#endif // _DEBUG

				
				//score up
				playerClass->AddEvent( JUDGE_GOOD );
				PrintScore( playerNumber, JUDGE_GOOD );

				CRMobjectManager::GetInstance()->DeleteNoteListFront( playerLayer );
			}
		}
		// Player1 너무 빨리 눌러 MISS (a키를 누르고 있을때 good나오는 버그 회피)
		else if ( thisNote->GetPositionY() > 504 )
		{
			if ( IsKeyInputRight( thisNote , playerNumber ) )
			{

#ifdef _DEBUG
				printf_s( "%dP Time Miss \n", playerLayer );
#endif // _DEBUG

				//score up;
				playerClass->AddEvent( JUDGE_MISS );
				PrintScore( playerNumber, JUDGE_MISS );

				CRMobjectManager::GetInstance()->DeleteNoteListFront( playerLayer );
			}
		}
	}



	


}


bool CRMjudgeManager::IsKeyInputRight( CRMobject* note , PlayerNumber player )
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
			note->SetVisible( false );
			//DeleteNote( objectList );
			return true;
		}
	}
	else if ( note->GetObjectType() == OBJECT_NOTE_NORMAL_2 )
	{
		if ( CRMinput::GetInstance()->GetKeyStatusByKey( target2 ) == KEY_DOWN )
		{
			note->SetVisible( false );
			//DeleteNote( objectList );
			return true;
		}
	}

	return false;
}


void CRMjudgeManager::PrintScore( PlayerNumber player, JudgeType judgeType )
{
#ifdef _DEBUG
	printf_s("점수표 - 1P [P:%d] [G:%d] [M:%d] [C:%d] [S:%d]  2P [P:%d] [G:%d] [M:%d] [C:%d] [S:%d] \n", 
			CRMplayer1P::GetInstance()->GetCount( PERFECT_COUNT ), CRMplayer1P::GetInstance()->GetCount( GOOD_COUNT ), 
			CRMplayer1P::GetInstance()->GetCount( MISS_COUNT ), CRMplayer1P::GetInstance()->GetCount( COMBO_COUNT ), CRMplayer1P::GetInstance()->GetCount( SCORE_COUNT ),
			CRMplayer2P::GetInstance()->GetCount( PERFECT_COUNT ), CRMplayer2P::GetInstance()->GetCount( GOOD_COUNT ), 
			CRMplayer2P::GetInstance()->GetCount( MISS_COUNT ), CRMplayer2P::GetInstance()->GetCount( COMBO_COUNT ), CRMplayer2P::GetInstance()->GetCount( SCORE_COUNT )
			);
#endif // _DEBUG

	CRMplayer*	thisPlayer = nullptr;
	wchar_t		*playerScoreLabelName;
	wchar_t		*playerComboLabelName;
	float		positionX = 0;
	float		positionY = 100;

	switch ( player )
	{
	case PLAYER_ONE:
		thisPlayer = CRMplayer1P::GetInstance();
		playerScoreLabelName = L"플레이어1점수";
		playerComboLabelName = L"플레이어1콤보";
		positionX = 100;

		break;
	case PLAYER_TWO:
		thisPlayer = CRMplayer2P::GetInstance();
		playerScoreLabelName = L"플레이어2점수";
		playerComboLabelName = L"플레이어2콤보";
		positionX = 600;

		break;
	default:
		return;
	}

	wchar_t		score[255] = { 0, };
	wchar_t		judge[255] = { 0, };
	
	switch ( judgeType )
	{
	case JUDGE_PERFECT:
		swprintf_s( judge, L"PERFECT!!" );
		break;
	case JUDGE_GOOD:
		swprintf_s( judge, L"  GOOD!  " );
		break;
	case JUDGE_MISS:
		swprintf_s( judge, L"  MISS..." );
		break;
	default:
		break;
	}

	swprintf_s( score, L"%10s \n %10d \n  %8s", L"SCORE", thisPlayer->GetCount( SCORE_COUNT ), judge );

	CRMlabel* playerScoreLabel = new CRMlabel();
	playerScoreLabel->CreateLabel( playerScoreLabelName , score, L"맑은 고딕", 35.0F );
	playerScoreLabel->SetRGBA( 0.0f, 0.3f, 0.7f, 1.f );
	playerScoreLabel->SetSceneType( SCENE_PLAY );
	playerScoreLabel->SetPosition( positionX , positionY );

	if ( thisPlayer->GetCount( COMBO_COUNT ) > 0 )
	{
		swprintf_s( score, L"%8s \n  %10d", L"COMBO", thisPlayer->GetCount( COMBO_COUNT ) );

		CRMlabel* playerComboLabel = new CRMlabel();
		playerComboLabel->CreateLabel( playerComboLabelName , score, L"맑은 고딕", 35.0F );
		playerComboLabel->SetRGBA( 0.8f, 0.5f, 0.2f, 1.f );
		playerComboLabel->SetSceneType( SCENE_PLAY );
		playerComboLabel->SetPosition( positionX, positionY + 250 );
	}
	else
	{
		CRMlabel* playerComboLabel = new CRMlabel();
		playerComboLabel->CreateLabel( playerComboLabelName , L"", L"맑은 고딕", 35.0F );
		playerComboLabel->SetRGBA( 0.f, 0.f, 0.f, 1.f );
		playerComboLabel->SetSceneType( SCENE_PLAY );
		playerComboLabel->SetPosition( positionX, positionY + 250 );
	}

}


