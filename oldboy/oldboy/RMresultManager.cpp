#include "stdafx.h"
#include "RMresultManager.h"
#include "RMlabel.h"
#include "RMdefine.h"
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

	std::string p1ResultText;
	std::string p2ResultText;
	
	if ( (player1->GetCount(COUNT_SCORE) == player2->GetCount(COUNT_SCORE) ) )
	{
		p1ResultText.append( "Draw" );
		p2ResultText.append( "Draw" );
	}
	else
	{
		p1ResultText.append( (player1->GetCount(COUNT_SCORE) > player2->GetCount(COUNT_SCORE)) ? "Win" : "Lose" );
		p2ResultText.append( (player1->GetCount(COUNT_SCORE) < player2->GetCount(COUNT_SCORE)) ? "Win" : "Lose" );
	}
	

	p1ResultText.append( (player1->IsDead()) ? " And Fail..." : " And Clear!!!" );
	p2ResultText.append( (player2->IsDead()) ? " And Fail..." : " And Clear!!!" );
	
	CRMlabel* p1Result = new CRMlabel();
	p1Result->CreateLabel( L"p1Result" , string2wstring( p1ResultText ), LABEL_FONT_NORMAL, 55.0f );
	p1Result->SetRGBA( 0.0f, 0.3f, 0.7f, 1.f );
	p1Result->SetSceneType( SCENE_RESULT );
	p1Result->SetPosition( ( SCREEN_SIZE_X / 2 ) - 450 , 200 );

	CRMlabel* p1Score = new CRMlabel();
	p1Score->CreateLabel( L"p1Score" , string2wstring( LABEL_RESULT_SCORE + std::to_string( player1->GetCount(COUNT_SCORE) ) ), LABEL_FONT_NORMAL, 35.0f );
	p1Score->SetRGBA( 0.0f, 0.3f, 0.7f, 1.f );
	p1Score->SetSceneType( SCENE_RESULT );
	p1Score->SetPosition( ( SCREEN_SIZE_X / 2 ) - 450 , 250 );

	CRMlabel* p1Perfect = new CRMlabel();
	p1Perfect->CreateLabel( L"p1Perfect" , string2wstring( LABEL_RESULT_PERFECT + std::to_string( player1->GetCount(COUNT_PERFECT) ) ), LABEL_FONT_NORMAL, 35.0f );
	p1Perfect->SetRGBA( 0.0f, 0.3f, 0.7f, 1.f );
	p1Perfect->SetSceneType( SCENE_RESULT );
	p1Perfect->SetPosition( ( SCREEN_SIZE_X / 2 ) - 450 , 300 );

	CRMlabel* p1Good = new CRMlabel();
	p1Good->CreateLabel( L"p1Good" , string2wstring( LABEL_RESULT_GOOD + std::to_string( player1->GetCount(COUNT_GOOD) ) ), LABEL_FONT_NORMAL, 35.0f );
	p1Good->SetRGBA( 0.0f, 0.3f, 0.7f, 1.f );
	p1Good->SetSceneType( SCENE_RESULT );
	p1Good->SetPosition( ( SCREEN_SIZE_X / 2 ) - 450 , 350 );

	CRMlabel* p1Miss = new CRMlabel();
	p1Miss->CreateLabel( L"p1Miss" , string2wstring( LABEL_RESULT_MISS + std::to_string( player1->GetCount(COUNT_MISS) ) ), LABEL_FONT_NORMAL, 35.0f );
	p1Miss->SetRGBA( 0.0f, 0.3f, 0.7f, 1.f );
	p1Miss->SetSceneType( SCENE_RESULT );
	p1Miss->SetPosition( ( SCREEN_SIZE_X / 2 ) - 450 , 400 );

	CRMlabel* p1Combo = new CRMlabel();
	p1Combo->CreateLabel( L"p1Combo" , string2wstring( LABEL_RESULT_COMBO + std::to_string( player1->GetCount(COUNT_MAX_COMBO) ) ), LABEL_FONT_NORMAL, 35.0f );
	p1Combo->SetRGBA( 0.0f, 0.3f, 0.7f, 1.f );
	p1Combo->SetSceneType( SCENE_RESULT );
	p1Combo->SetPosition( ( SCREEN_SIZE_X / 2 ) - 450 , 450 );

	//////////////////////////////////////////////////////////////////////////

	CRMlabel* p2Result = new CRMlabel();
	p2Result->CreateLabel( L"p2Result" , string2wstring( p2ResultText ), LABEL_FONT_NORMAL, 55.0f );
	p2Result->SetRGBA( 0.0f, 0.3f, 0.7f, 1.f );
	p2Result->SetSceneType( SCENE_RESULT );
	p2Result->SetPosition( ( SCREEN_SIZE_X / 2 ) + 50 , 200 );

	CRMlabel* p2Score = new CRMlabel();
	p2Score->CreateLabel( L"p2Score" , string2wstring( LABEL_RESULT_SCORE + std::to_string( player2->GetCount(COUNT_SCORE) ) ), LABEL_FONT_NORMAL, 35.0f );
	p2Score->SetRGBA( 0.0f, 0.3f, 0.7f, 1.f );
	p2Score->SetSceneType( SCENE_RESULT );
	p2Score->SetPosition( ( SCREEN_SIZE_X / 2 ) + 50 , 250 );

	CRMlabel* p2Perfect = new CRMlabel();
	p2Perfect->CreateLabel( L"p2Perfect" , string2wstring( LABEL_RESULT_PERFECT + std::to_string( player2->GetCount(COUNT_PERFECT) ) ), LABEL_FONT_NORMAL, 35.0f );
	p2Perfect->SetRGBA( 0.0f, 0.3f, 0.7f, 1.f );
	p2Perfect->SetSceneType( SCENE_RESULT );
	p2Perfect->SetPosition( ( SCREEN_SIZE_X / 2 ) + 50 , 300 );

	CRMlabel* p2Good = new CRMlabel();
	p2Good->CreateLabel( L"p2Good" , string2wstring( LABEL_RESULT_GOOD + std::to_string( player2->GetCount(COUNT_GOOD) ) ), LABEL_FONT_NORMAL, 35.0f );
	p2Good->SetRGBA( 0.0f, 0.3f, 0.7f, 1.f );
	p2Good->SetSceneType( SCENE_RESULT );
	p2Good->SetPosition( ( SCREEN_SIZE_X / 2 ) + 50 , 350 );

	CRMlabel* p2Miss = new CRMlabel();
	p2Miss->CreateLabel( L"p2Miss" , string2wstring( LABEL_RESULT_MISS + std::to_string( player2->GetCount(COUNT_MISS) ) ), LABEL_FONT_NORMAL, 35.0f );
	p2Miss->SetRGBA( 0.0f, 0.3f, 0.7f, 1.f );
	p2Miss->SetSceneType( SCENE_RESULT );
	p2Miss->SetPosition( ( SCREEN_SIZE_X / 2 ) + 50 , 400 );

	CRMlabel* p2Combo = new CRMlabel();
	p2Combo->CreateLabel( L"p2Combo" , string2wstring( LABEL_RESULT_COMBO + std::to_string( player2->GetCount(COUNT_MAX_COMBO) ) ), LABEL_FONT_NORMAL, 35.0f );
	p2Combo->SetRGBA( 0.0f, 0.3f, 0.7f, 1.f );
	p2Combo->SetSceneType( SCENE_RESULT );
	p2Combo->SetPosition( ( SCREEN_SIZE_X / 2 ) + 50 , 450 );

}

// Label이 wstring에서 string으로 바뀔때까지 임시로 가지는 함수
std::wstring CRMresultManager::string2wstring(const std::string& str) const {
	std::wstring wstr(str.length(),L' ');
	copy(str.begin(),str.end(),wstr.begin());
	return wstr;
}