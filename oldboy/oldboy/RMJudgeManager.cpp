﻿#include "stdafx.h"
#include "RMdefine.h"
#include "RMconst.h"
#include "RMkeyMapping.h"
#include "RMjudgeManager.h"
#include "RMobjectManager.h"
#include "RMobject.h"
#include "RMsound.h"
#include "RMplayer1P.h"
#include "RMplayer2P.h"
#include "RMchildEffectImage.h"
#include "RMlabel.h"
#include "RMeffectManager.h"
#include "RMinput.h"
#include "RMpauseManager.h"
#include "RMairTomo.h"

CRMjudgeManager::CRMjudgeManager(void)
{
	ZeroMemory(&m_IsItemRecoverOn, sizeof(m_IsItemRecoverOn));
	m_VirtualPlayerOn = false;

	m_P1JudgeTypeTemp = JUDGE_NONE;
	m_P2JudgeTypeTemp = JUDGE_NONE;
}


CRMjudgeManager::~CRMjudgeManager(void)
{
}

void CRMjudgeManager::StartNote( PlayerNumber player , WidgetType widgetType ) const
{
	CRMobject* thisNote = CRMobjectManager::GetInstance()->GetObjectFront( LAYER_MEMORY_POOL );
	if ( thisNote == nullptr )
	{
		return; 
	}

	if ( player == PLAYER_ONE && !CRMplayer1P::GetInstance()->IsDead())
	{
		// 만약 이곳에서 HP 체크를 하지 않으면?
		// Judge 메소드 주석 참조
		thisNote->SetWidgetType( widgetType );
		thisNote->SetPosition( NOTE_ONE_START_POSITION_X, NOTE_START_POSITION_Y );
		thisNote->SetVisible(true);
		thisNote->SetSceneType( SCENE_PLAY );
		thisNote->SetPlayer( PLAYER_ONE );
		CRMobjectManager::GetInstance()->AddObject( thisNote , LAYER_NOTE1 );
		CRMobjectManager::GetInstance()->DeleteNoteListFront( LAYER_MEMORY_POOL );
	}
	else if ( player == PLAYER_TWO && !CRMplayer2P::GetInstance()->IsDead() )
	{
		thisNote->SetWidgetType( widgetType );
		thisNote->SetPosition( NOTE_TWO_START_POSITION_X, NOTE_START_POSITION_Y );
		thisNote->SetVisible(true);
		thisNote->SetSceneType( SCENE_PLAY );
		thisNote->SetPlayer( PLAYER_TWO );
		CRMobjectManager::GetInstance()->AddObject( thisNote , LAYER_NOTE2 );
		CRMobjectManager::GetInstance()->DeleteNoteListFront( LAYER_MEMORY_POOL );
	}
}

void CRMjudgeManager::JudgeNote()
{
	if ( CRMpauseManager::GetInstance()->IsPause() )
	{
		return;
	}
	// 이곳에서 HP 체크하면 안 됨
	// 만약 Dead일 때 Judge 자체를 안 해버리면?
	//
	// DeleteNote를 호출하지 않으므로 메모리풀로 다시 돌아가지 않음
	if ( !CRMplayer1P::GetInstance()->IsDead() )
	{
		JudgeNoteByPlayer( PLAYER_ONE );
	}
	else
	{
		CRMobjectManager::GetInstance()->RemoveNoteFromPlayerLayer( PLAYER_ONE );
	}
	
	if ( !CRMplayer2P::GetInstance()->IsDead() )
	{
		JudgeNoteByPlayer( PLAYER_TWO );
	}
	else
	{
		CRMobjectManager::GetInstance()->RemoveNoteFromPlayerLayer( PLAYER_TWO );
	}
}


void CRMjudgeManager::JudgeNoteByPlayer( PlayerNumber playerNumber )
{

	LayerType playerLayer;
	CRMplayer* playerClass = nullptr;
	if ( playerNumber == PLAYER_ONE )
	{
		playerLayer = LAYER_NOTE1;
		playerClass = CRMplayer1P::GetInstance();
	}
	else
	{
		playerLayer = LAYER_NOTE2;
		playerClass = CRMplayer2P::GetInstance();
	}

	CRMobject* thisNote = CRMobjectManager::GetInstance()->GetObjectFront( playerLayer );
	if ( thisNote != nullptr )
	{
		/////////////////////////////////////////////////////////////////
		if ( IsKeyInputRight( thisNote , playerNumber ) )
		{
			if ( thisNote->GetPositionY() > NOTE_JUDGE_PERFECT_START_LINE && thisNote->GetPositionY() < NOTE_JUDGE_PERFECT_END_LINE )
			{
				thisNote->SetVisible(false);
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
				CRMeffectManager::GetInstance()->SetFlag( playerNumber , hitPositionX , hitPositionY );

				//score up
				playerClass->AddEvent( JUDGE_PERFECT );
				PrintScore( playerNumber, JUDGE_PERFECT );

				if ( m_IsItemRecoverOn[playerNumber] == true )
				{
					playerClass->AddHP(4);
				}

				//키 누르면서 바로 지우면 플래그 세팅이 안됨
				//키를 누르면 무조건 세팅이 되면 miss 처리 불가
				//deleteNote 이동
				CRMobjectManager::GetInstance()->DeleteNoteListFront( playerLayer );
			}
			// Good
			else if ( ( thisNote->GetPositionY() > NOTE_JUDGE_GOOD_START_LINE && thisNote->GetPositionY() < NOTE_JUDGE_GOOD_END_LINE ) )
			{
				thisNote->SetVisible(false);
				//effect 플래그 세팅
				float hitPositionX = thisNote->GetPositionX();
				float hitPositionY = thisNote->GetPositionY();
				CRMeffectManager::GetInstance()->SetFlag( playerNumber , hitPositionX , hitPositionY );

				//score up
				playerClass->AddEvent( JUDGE_GOOD );
				PrintScore( playerNumber, JUDGE_GOOD );

				if ( m_IsItemRecoverOn[playerNumber] == true )
				{
					playerClass->AddHP(2);
				}

				CRMobjectManager::GetInstance()->DeleteNoteListFront( playerLayer );
			}
			// 너무 빨리 눌러 MISS (a키를 누르고 있을때 good나오는 버그 회피)

			else if ( thisNote->GetPositionY() > NOTE_JUDGE_FAST_MISS_LINE )
			{
				thisNote->SetVisible(false);
				
				//score up;
				playerClass->AddEvent( JUDGE_MISS );
				playerClass->SubHP();
				PrintScore( playerNumber, JUDGE_MISS );

				CRMobjectManager::GetInstance()->DeleteNoteListFront( playerLayer );
			}
		}
		//note bottom miss
		else if ( thisNote->GetPositionY() > NOTE_JUDGE_LATE_MISS_LINE )
		{
			
			//score up
			playerClass->AddEvent( JUDGE_MISS );
			playerClass->SubHP();
			PrintScore( playerNumber, JUDGE_MISS );

			//thisNote->SetPosition( DEFAULT_POSITION_X, DEFAULT_POSITION_Y );
			CRMobjectManager::GetInstance()->DeleteNoteListFront( playerLayer );

		}
		// Perfect 
		

		/////////////////////////////////////////////////////////////////
	}
}


bool CRMjudgeManager::IsKeyInputRight( CRMobject* note , PlayerNumber player ) const
{
	KeyTable target1;
	KeyTable target2;

	if ( player == PLAYER_ONE )
	{
		target1 = KEY_TABLE_P1_TARGET1;
		target2 = KEY_TABLE_P1_TARGET2;
	}
	else
	{
		target1 = KEY_TABLE_P2_TARGET1;
		target2 = KEY_TABLE_P2_TARGET2;
	}

	if (player == PLAYER_TWO && m_VirtualPlayerOn)
	{
		CRMairTomo::GetInstance()->PlayVirtualPlayer();
	}
	if ( note->GetWidgetType() == WIDGET_NOTE_NORMAL_1 )
	{
		if ( ( CRMinput::GetInstance()->GetKeyStatusByKey( target2 ) == KEY_STATUS_PRESSED ) )
		{
			return false;
		}
		if ( ( CRMinput::GetInstance()->GetKeyStatusByKey( target1 ) == KEY_STATUS_DOWN ) )
		{
			return true;
		}
	}
	else if ( note->GetWidgetType() == WIDGET_NOTE_NORMAL_2 )
	{
		if ( ( CRMinput::GetInstance()->GetKeyStatusByKey( target1 ) == KEY_STATUS_PRESSED ) )
		{
			return false;
		}
		if ( CRMinput::GetInstance()->GetKeyStatusByKey( target2 ) == KEY_STATUS_DOWN )
		{
			return true;
		}
	}

	return false;
}


void CRMjudgeManager::PrintScore( PlayerNumber player, JudgeType judgeType )
{
// 	printConsole("점수표 - 1P [P:%d] [G:%d] [M:%d] [C:%d] [S:%d]  2P [P:%d] [G:%d] [M:%d] [C:%d] [S:%d] \n", 
// 			CRMplayer1P::GetInstance()->GetCount( COUNT_PERFECT ), CRMplayer1P::GetInstance()->GetCount( COUNT_GOOD ), 
// 			CRMplayer1P::GetInstance()->GetCount( COUNT_MISS ), CRMplayer1P::GetInstance()->GetCount( COUNT_COMBO ), CRMplayer1P::GetInstance()->GetCount( COUNT_SCORE ),
// 			CRMplayer2P::GetInstance()->GetCount( COUNT_PERFECT ), CRMplayer2P::GetInstance()->GetCount( COUNT_GOOD ), 
// 			CRMplayer2P::GetInstance()->GetCount( COUNT_MISS ), CRMplayer2P::GetInstance()->GetCount( COUNT_COMBO ), CRMplayer2P::GetInstance()->GetCount( COUNT_SCORE )
// 			);
	
	CRMplayer*	thisPlayer = CRMplayer1P::GetInstance();
	CRMplayer*	otherPlayer = CRMplayer2P::GetInstance();

	float		positionX = 93;
	float		positionY = 100;

	
	
	if ( player == PLAYER_TWO )
	{
		thisPlayer = CRMplayer2P::GetInstance();
		otherPlayer = CRMplayer1P::GetInstance();
		
		positionX = 604;
		m_P2JudgeTypeTemp = judgeType;
	}
	else
	{
		m_P1JudgeTypeTemp = judgeType;
	}

	std::wstring score;

	score.clear();
	// 아 이거 계산하기 귀찮... ㅇㅅㅇ!!!!!!
	score.append( L"\n " );
	score.append( L"\n " );

	std::wstring tempString = std::to_wstring( thisPlayer->GetCount( COUNT_SCORE ) + 1000000 );
	tempString = tempString.substr(1, tempString.length());

	score.append( tempString );

	CRMlabel* playerScoreLabelShadow = new CRMlabel();
	playerScoreLabelShadow->CreateLabel( player == PLAYER_ONE ? LABEL_NAME_P1_SCORE_SHADOW : LABEL_NAME_P2_SCORE_SHADOW, score, LABEL_FONT_NORMAL, 55.0f );
	playerScoreLabelShadow->SetRGBA( 0.0f, 0.0f, 0.0f, 1.f );
	playerScoreLabelShadow->SetSceneType( SCENE_PLAY );
	playerScoreLabelShadow->SetPosition( positionX + 2 , positionY + 2 );

	CRMlabel* playerScoreLabel = new CRMlabel();
	playerScoreLabel->CreateLabel( player == PLAYER_ONE ? LABEL_NAME_P1_SCORE : LABEL_NAME_P2_SCORE, score, LABEL_FONT_NORMAL, 55.0f );
	playerScoreLabel->SetRGBA( 183.0f/255, 183.0f/255, 183.0f/254, 1.f );
	playerScoreLabel->SetSceneType( SCENE_PLAY );
	playerScoreLabel->SetPosition( positionX , positionY );




	score.clear();
	score.append( L"\n " );
	score.append( L"\n " );

	tempString.clear();
	tempString = std::to_wstring( thisPlayer->GetCount( COUNT_COMBO ) + 10000 );
	tempString = tempString.substr(1, tempString.length());

	score.append( tempString );

	if ( thisPlayer->GetCount( COUNT_COMBO ) < 2 )
	{
		score.clear();
	}


	CRMlabel* playerComboLabelShadow = new CRMlabel();
	playerComboLabelShadow->CreateLabel( player == PLAYER_ONE ? LABEL_NAME_P1_COMBO_SHADOW : LABEL_NAME_P2_COMBO_SHADOW, score, LABEL_FONT_NORMAL, 45.0F );
	playerComboLabelShadow->SetRGBA( 0.0f, 0.0f, 0.0f, 1.f );
	playerComboLabelShadow->SetSceneType( SCENE_PLAY );
	playerComboLabelShadow->SetPosition( positionX + 2 + 40, positionY + 250 + 2 );

	CRMlabel* playerComboLabel = new CRMlabel();
	playerComboLabel->CreateLabel( player == PLAYER_ONE ? LABEL_NAME_P1_COMBO : LABEL_NAME_P2_COMBO, score, LABEL_FONT_NORMAL, 45.0F );
	playerComboLabel->SetRGBA( 0.8f, 0.5f, 0.2f, 1.f );
	playerComboLabel->SetSceneType( SCENE_PLAY );
	playerComboLabel->SetPosition( positionX + 40, positionY + 250 );

}

void CRMjudgeManager::StartItemRecovery( PlayerNumber player )
{
	m_IsItemRecoverOn[player] = true;
}

void CRMjudgeManager::StopItemRecovery( PlayerNumber player )
{
	m_IsItemRecoverOn[player] = false;
}

void CRMjudgeManager::SetVirtualPlayerMode( bool VirPlayerOn )
{
	m_VirtualPlayerOn = VirPlayerOn;
}

void CRMjudgeManager::InitializeJudgeType()
{
	m_P1JudgeTypeTemp = JUDGE_NONE;
	m_P2JudgeTypeTemp = JUDGE_NONE;
}

JudgeType CRMjudgeManager::GetJudgeType( PlayerNumber player )
{
	if ( player == PLAYER_ONE )
	{
		return m_P1JudgeTypeTemp;
	}

	return m_P2JudgeTypeTemp;
}


