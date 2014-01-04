#include "stdafx.h"
#include "RMresultManager.h"
#include "RMlabel.h"
#include "RMdefine.h"
#include "RMconst.h"
#include "RMplayer.h"
#include "RMplayer1P.h"
#include "RMplayer2P.h"
#include "RMsound.h"
#include "RMglobalParameterManager.h"


CRMresultManager::CRMresultManager(void)
{
}


CRMresultManager::~CRMresultManager(void)
{
}


void CRMresultManager::ShowResult()
{
	DrawLabel( 2, 2, 0.0f, 0.0f, 0.0f, 0);
	DrawLabel( 0, 0, 65.0f/255, 65.0f/255, 65.0f/254, 1 );
}


void CRMresultManager::DrawLabel( int offsetX, int offsetY, float R, float G, float B, int drawNum ) const
{
	std::wstring labelName;
	if ( drawNum==0 )
	{
		labelName = L"-1";
	} 
	else
	{
		labelName = L"-2";
	}

	CRMplayer*	player1 = CRMplayer1P::GetInstance();
	CRMplayer*	player2 = CRMplayer2P::GetInstance();

	UINT totalScoreP1 = player1->GetCount(COUNT_SCORE) + ( player1->GetCount(COUNT_MAX_COMBO) * SCORE_MAX_COMBO_RATE );
	UINT totalScoreP2 = player2->GetCount(COUNT_SCORE) + ( player2->GetCount(COUNT_MAX_COMBO) * SCORE_MAX_COMBO_RATE );

	if ( !player1->IsDead() )
	{
		totalScoreP1 += SCORE_CLEAR_BONUS;
	}
	if ( !player2->IsDead() )
	{
		totalScoreP2 += SCORE_CLEAR_BONUS;
	}

	CRMlabel* p1Perfect = new CRMlabel();
	p1Perfect->CreateLabel( L"p1Perfect" + labelName , string2wstring( std::to_string( player1->GetCount(COUNT_PERFECT) ) ), LABEL_FONT_NORMAL, 35.0f );
	p1Perfect->SetRGBA( R, G, B, 1.f );
	p1Perfect->SetSceneType( SCENE_RESULT );
	p1Perfect->SetPosition( ( SCREEN_SIZE_X / 2 ) - 177 + offsetX , 295 + offsetY );

	CRMlabel* p1Good = new CRMlabel();
	p1Good->CreateLabel( L"p1Good" + labelName , string2wstring( std::to_string( player1->GetCount(COUNT_GOOD) ) ), LABEL_FONT_NORMAL, 35.0f );
	p1Good->SetRGBA( R, G, B, 1.f );
	p1Good->SetSceneType( SCENE_RESULT );
	p1Good->SetPosition( ( SCREEN_SIZE_X / 2 ) - 177 + offsetX , 367 + offsetY );

	CRMlabel* p1Miss = new CRMlabel();
	p1Miss->CreateLabel( L"p1Miss" + labelName , string2wstring( std::to_string( player1->GetCount(COUNT_MISS) ) ), LABEL_FONT_NORMAL, 35.0f );
	p1Miss->SetRGBA( R, G, B, 1.f );
	p1Miss->SetSceneType( SCENE_RESULT );
	p1Miss->SetPosition( ( SCREEN_SIZE_X / 2 ) - 177 + offsetX , 437 + offsetY );

	CRMlabel* p1MaxCombo = new CRMlabel();
	p1MaxCombo->CreateLabel( L"p1MaxCombo" + labelName , string2wstring( std::to_string( player1->GetCount(COUNT_MAX_COMBO) ) ), LABEL_FONT_NORMAL, 35.0f );
	p1MaxCombo->SetRGBA( R, G, B, 1.f );
	p1MaxCombo->SetSceneType( SCENE_RESULT );
	p1MaxCombo->SetPosition( ( SCREEN_SIZE_X / 2 ) - 177 + offsetX , 508 + offsetY );

	CRMlabel* p1Score = new CRMlabel();
	p1Score->CreateLabel( L"p1Score" + labelName , string2wstring( std::to_string( totalScoreP1 ) ), LABEL_FONT_NORMAL, 35.0f );
	p1Score->SetRGBA( R, G, B, 1.f );
	p1Score->SetSceneType( SCENE_RESULT );
	p1Score->SetPosition( ( SCREEN_SIZE_X / 2 ) - 177 + offsetX , 578 + offsetY );
	//////////////////////////////////////////////////////////////////////////


	CRMlabel* p2Perfect = new CRMlabel();
	p2Perfect->CreateLabel( L"p2Perfect" + labelName , string2wstring(std::to_string( player2->GetCount(COUNT_PERFECT) ) ), LABEL_FONT_NORMAL, 35.0f );
	p2Perfect->SetRGBA( R, G, B, 1.f );
	p2Perfect->SetSceneType( SCENE_RESULT );
	p2Perfect->SetPosition( ( SCREEN_SIZE_X / 2 ) + 335 + offsetX , 295 + offsetY );

	CRMlabel* p2Good = new CRMlabel();
	p2Good->CreateLabel( L"p2Good" + labelName , string2wstring( std::to_string( player2->GetCount(COUNT_GOOD) ) ), LABEL_FONT_NORMAL, 35.0f );
	p2Good->SetRGBA( R, G, B, 1.f );
	p2Good->SetSceneType( SCENE_RESULT );
	p2Good->SetPosition( ( SCREEN_SIZE_X / 2 ) + 335 + offsetX , 367 + offsetY );

	CRMlabel* p2Miss = new CRMlabel();
	p2Miss->CreateLabel( L"p2Miss" + labelName , string2wstring( std::to_string( player2->GetCount(COUNT_MISS) ) ), LABEL_FONT_NORMAL, 35.0f );
	p2Miss->SetRGBA( R, G, B, 1.f );
	p2Miss->SetSceneType( SCENE_RESULT );
	p2Miss->SetPosition( ( SCREEN_SIZE_X / 2 ) + 335 + offsetX , 437 + offsetY );

	CRMlabel* p2MaxCombo = new CRMlabel();
	p2MaxCombo->CreateLabel( L"p2MaxCombo" + labelName , string2wstring( std::to_string( player2->GetCount(COUNT_MAX_COMBO) ) ), LABEL_FONT_NORMAL, 35.0f );
	p2MaxCombo->SetRGBA( R, G, B, 1.f );
	p2MaxCombo->SetSceneType( SCENE_RESULT );
	p2MaxCombo->SetPosition( ( SCREEN_SIZE_X / 2 ) + 335 + offsetX , 508 + offsetY );

	CRMlabel* p2Score = new CRMlabel();
	p2Score->CreateLabel( L"p2Score" + labelName , string2wstring( std::to_string( totalScoreP2 ) ), LABEL_FONT_NORMAL, 35.0f );
	p2Score->SetRGBA( R, G, B, 1.f );
	p2Score->SetSceneType( SCENE_RESULT );
	p2Score->SetPosition( ( SCREEN_SIZE_X / 2 ) + 335 + offsetX , 578 + offsetY );
}


// Label이 wstring에서 string으로 바뀔때까지 임시로 가지는 함수
std::wstring CRMresultManager::string2wstring(const std::string& str) const {
	std::wstring wstr(str.length(),L' ');
	copy(str.begin(),str.end(),wstr.begin());
	return wstr;
}