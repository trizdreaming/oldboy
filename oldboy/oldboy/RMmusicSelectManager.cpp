#include "stdafx.h"
#include "RMmacro.h"
#include "RMdefine.h"
#include "RMmusicSelectManager.h"
#include "RMlabel.h"

CRMmusicSelectManager::CRMmusicSelectManager(void)
{
}


CRMmusicSelectManager::~CRMmusicSelectManager(void)
{
}

HRESULT CRMmusicSelectManager::ShowMusicList( const std::vector<std::string>& musicVector, const int index ) const
{
	int totalMusicNum = musicVector.size();

	//printConsole("Total Music Count:%d \n", totalMusicNum);

	if ( totalMusicNum > 0 )	// 0
	{
		int indexFix = 0;
		indexFix = index % totalMusicNum;

		CRMlabel* musicList1 = new CRMlabel();
		musicList1->CreateLabel( L"LABELNAME1" , string2wstring(musicVector.at(indexFix)), LABEL_FONT_NORMAL, 55.0F );
		musicList1->SetRGBA( 0.0f, 0.3f, 0.7f, 1.f );
		musicList1->SetSceneType( SCENE_SELECT_MUSIC );
		musicList1->SetPosition( 100 , ( SCREEN_SIZE_Y / 2 ) - 50 );
	}
	if ( totalMusicNum > 1 )	// 1
	{
		int indexFix = 0;
		indexFix = (index + 1) % totalMusicNum;
		
		CRMlabel* musicList2 = new CRMlabel();
		musicList2->CreateLabel( L"LABELNAME2" , string2wstring(musicVector.at(indexFix)), LABEL_FONT_NORMAL, 35.0F );
		musicList2->SetRGBA( 0.0f, 0.3f, 0.7f, 1.f );
		musicList2->SetSceneType( SCENE_SELECT_MUSIC );
		musicList2->SetPosition( 100 , ( SCREEN_SIZE_Y / 2 ) + 100 );
	}
	if ( totalMusicNum > 2 )	// -1
	{
		int indexFix = 0;
		indexFix = (totalMusicNum + index - 1) % totalMusicNum;

		CRMlabel* musicList3 = new CRMlabel();
		musicList3->CreateLabel( L"LABELNAME3" , string2wstring(musicVector.at(indexFix)), LABEL_FONT_NORMAL, 35.0F );
		musicList3->SetRGBA( 0.0f, 0.3f, 0.7f, 1.f );
		musicList3->SetSceneType( SCENE_SELECT_MUSIC );
		musicList3->SetPosition( 100 , ( SCREEN_SIZE_Y / 2 ) - 150 );
	}
	if ( totalMusicNum > 3 )	// 2
	{
		int indexFix = 0;
		indexFix = (index + 2) % totalMusicNum;

		CRMlabel* musicList4 = new CRMlabel();
		musicList4->CreateLabel( L"LABELNAME4" , string2wstring(musicVector.at(indexFix)), LABEL_FONT_NORMAL, 35.0F );
		musicList4->SetRGBA( 0.0f, 0.3f, 0.7f, 1.f );
		musicList4->SetSceneType( SCENE_SELECT_MUSIC );
		musicList4->SetPosition( 100 , ( SCREEN_SIZE_Y / 2 ) + 200 );
	}
	if ( totalMusicNum > 4 )	// -2
	{
		int indexFix = 0;
		indexFix = (totalMusicNum + index - 2) % totalMusicNum;

		CRMlabel* musicList5 = new CRMlabel();
		musicList5->CreateLabel( L"LABELNAME5" , string2wstring(musicVector.at(indexFix)), LABEL_FONT_NORMAL, 35.0F );
		musicList5->SetRGBA( 0.0f, 0.3f, 0.7f, 1.f );
		musicList5->SetSceneType( SCENE_SELECT_MUSIC );
		musicList5->SetPosition( 100 , ( SCREEN_SIZE_Y / 2 ) - 250 );
	}
	return NULL;
}

// Label이 wstring에서 string으로 바뀔때까지 임시로 가지는 함수
std::wstring CRMmusicSelectManager::string2wstring(const std::string& str) const {
	std::wstring wstr(str.length(),L' ');
	copy(str.begin(),str.end(),wstr.begin());
	return wstr;
}