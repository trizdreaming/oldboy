#include "stdafx.h"
#include "RMresultManager.h"
#include "RMlabel.h"
#include "RMdefine.h"
#include "RMconst.h"
#include "RMplayer.h"
#include "RMplayer1P.h"
#include "RMplayer2P.h"


CRMresultManager::CRMresultManager(void)
{
}


CRMresultManager::~CRMresultManager(void)
{
}


void CRMresultManager::ShowResult()
{
	//std::to_string(  );
	CRMplayer*	player1 = CRMplayer1P::GetInstance();
	CRMplayer*	player2 = CRMplayer2P::GetInstance();

	
	UINT totalScoreP1 = player1->GetCount(COUNT_SCORE) + ( player1->GetCount(COUNT_MAX_COMBO) * SCORE_MAX_COMBO_RATE );
	UINT totalScoreP2 = player2->GetCount(COUNT_SCORE) + ( player2->GetCount(COUNT_MAX_COMBO) * SCORE_MAX_COMBO_RATE );


	CRMlabel* p1Perfect = new CRMlabel();
	p1Perfect->CreateLabel( L"p1Perfect" , string2wstring( std::to_string( player1->GetCount(COUNT_PERFECT) ) + " * " + std::to_string( SCORE_EACH_PERFECT ) ), LABEL_FONT_NORMAL, 35.0f );
	p1Perfect->SetRGBA( 0.0f, 0.3f, 0.7f, 1.f );
	p1Perfect->SetSceneType( SCENE_RESULT );
	p1Perfect->SetPosition( ( SCREEN_SIZE_X / 2 ) - 250 , 250 );

	CRMlabel* p1Good = new CRMlabel();
	p1Good->CreateLabel( L"p1Good" , string2wstring( std::to_string( player1->GetCount(COUNT_GOOD) ) + " * " + std::to_string( SCORE_EACH_GOOD ) ), LABEL_FONT_NORMAL, 35.0f );
	p1Good->SetRGBA( 0.0f, 114.0f/255, 54.0f/255, 1.f );
	p1Good->SetSceneType( SCENE_RESULT );
	p1Good->SetPosition( ( SCREEN_SIZE_X / 2 ) - 300 , 302 );

	CRMlabel* p1Miss = new CRMlabel();
	p1Miss->CreateLabel( L"p1Miss" , string2wstring( std::to_string( player1->GetCount(COUNT_MISS) ) + " * " + std::to_string( SCORE_EACH_MISS ) ), LABEL_FONT_NORMAL, 35.0f );
	p1Miss->SetRGBA( 158.0f/255, 11.0f/255, 15.0f/255, 1.f );
	p1Miss->SetSceneType( SCENE_RESULT );
	p1Miss->SetPosition( ( SCREEN_SIZE_X / 2 ) - 300 , 358 );

	CRMlabel* p1MaxCombo = new CRMlabel();
	p1MaxCombo->CreateLabel( L"p1MaxCombo" , string2wstring( std::to_string( player1->GetCount(COUNT_MAX_COMBO) ) + " * " + std::to_string( SCORE_MAX_COMBO_RATE ) ), LABEL_FONT_NORMAL, 35.0f );
	p1MaxCombo->SetRGBA( 0.0f, 0.0f, 0.0f, 1.f );
	p1MaxCombo->SetSceneType( SCENE_RESULT );
	p1MaxCombo->SetPosition( ( SCREEN_SIZE_X / 2 ) - 160 , 410 );

	CRMlabel* p1ComboBonus = new CRMlabel();
	p1ComboBonus->CreateLabel( L"p1Combo" , string2wstring( std::to_string( player1->GetCount(COUNT_COMBO_SCORE) ) ), LABEL_FONT_NORMAL, 35.0f );
	p1ComboBonus->SetRGBA( 0.0f, 0.0f, 0.0f, 1.f );
	p1ComboBonus->SetSceneType( SCENE_RESULT );
	p1ComboBonus->SetPosition( ( SCREEN_SIZE_X / 2 ) - 115 , 465 );

	CRMlabel* p1Score = new CRMlabel();
	p1Score->CreateLabel( L"p1Score" , string2wstring( std::to_string( totalScoreP1 ) ), LABEL_FONT_NORMAL, 35.0f );
	p1Score->SetRGBA( 0.0f, 0.0f, 0.0f, 1.f );
	p1Score->SetSceneType( SCENE_RESULT );
	p1Score->SetPosition( ( SCREEN_SIZE_X / 2 ) - 275 , 520 );
	//////////////////////////////////////////////////////////////////////////


	CRMlabel* p2Perfect = new CRMlabel();
	p2Perfect->CreateLabel( L"p2Perfect" , string2wstring(std::to_string( player2->GetCount(COUNT_PERFECT) ) + " * " + std::to_string( SCORE_EACH_PERFECT ) ), LABEL_FONT_NORMAL, 35.0f );
	p2Perfect->SetRGBA( 0.0f, 0.3f, 0.7f, 1.f );
	p2Perfect->SetSceneType( SCENE_RESULT );
	p2Perfect->SetPosition( ( SCREEN_SIZE_X / 2 ) + 250 , 250 );

	CRMlabel* p2Good = new CRMlabel();
	p2Good->CreateLabel( L"p2Good" , string2wstring( std::to_string( player2->GetCount(COUNT_GOOD) ) + " * " + std::to_string( SCORE_EACH_GOOD ) ), LABEL_FONT_NORMAL, 35.0f );
	p2Good->SetRGBA( 0.0f, 114.0f/255, 54.0f/255, 1.f );
	p2Good->SetSceneType( SCENE_RESULT );
	p2Good->SetPosition( ( SCREEN_SIZE_X / 2 ) + 200 , 302 );

	CRMlabel* p2Miss = new CRMlabel();
	p2Miss->CreateLabel( L"p2Miss" , string2wstring( std::to_string( player2->GetCount(COUNT_MISS) ) + " * " + std::to_string( SCORE_EACH_MISS ) ), LABEL_FONT_NORMAL, 35.0f );
	p2Miss->SetRGBA( 158.0f/255, 11.0f/255, 15.0f/255, 1.f );
	p2Miss->SetSceneType( SCENE_RESULT );
	p2Miss->SetPosition( ( SCREEN_SIZE_X / 2 ) + 200 , 358 );

	CRMlabel* p2MaxCombo = new CRMlabel();
	p2MaxCombo->CreateLabel( L"p2MaxCombo" , string2wstring( std::to_string( player2->GetCount(COUNT_MAX_COMBO) ) + " * " + std::to_string( SCORE_MAX_COMBO_RATE ) ), LABEL_FONT_NORMAL, 35.0f );
	p2MaxCombo->SetRGBA( 0.0f, 0.0f, 0.0f, 1.f );
	p2MaxCombo->SetSceneType( SCENE_RESULT );
	p2MaxCombo->SetPosition( ( SCREEN_SIZE_X / 2 ) + 335 , 410 );

	CRMlabel* p2ComboBonus = new CRMlabel();
	p2ComboBonus->CreateLabel( L"p2Combo" , string2wstring( std::to_string( player2->GetCount(COUNT_COMBO_SCORE) ) ), LABEL_FONT_NORMAL, 35.0f );
	p2ComboBonus->SetRGBA( 0.0f, 0.0f, 0.0f, 1.f );
	p2ComboBonus->SetSceneType( SCENE_RESULT );
	p2ComboBonus->SetPosition( ( SCREEN_SIZE_X / 2 ) + 380, 465 );

	CRMlabel* p2Score = new CRMlabel();
	p2Score->CreateLabel( L"p2Score" , string2wstring( std::to_string( totalScoreP2 ) ), LABEL_FONT_NORMAL, 35.0f );
	p2Score->SetRGBA( 0.0f, 0.0f, 0.0f, 1.f );
	p2Score->SetSceneType( SCENE_RESULT );
	p2Score->SetPosition( ( SCREEN_SIZE_X / 2 ) + 225 , 520 );
}

// Label이 wstring에서 string으로 바뀔때까지 임시로 가지는 함수
std::wstring CRMresultManager::string2wstring(const std::string& str) const {
	std::wstring wstr(str.length(),L' ');
	copy(str.begin(),str.end(),wstr.begin());
	return wstr;
}