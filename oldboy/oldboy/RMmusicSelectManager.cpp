#include "stdafx.h"
#include "RMdefine.h"
#include "RMconst.h"
#include "RMmacro.h"
#include "RMmusicSelectManager.h"
#include "RMlabel.h"
#include "RMxmlLoader.h"
#include "RMmusicData.h"

CRMmusicSelectManager::CRMmusicSelectManager(void):
	m_MusicSelectIndex(0)
{
}


CRMmusicSelectManager::~CRMmusicSelectManager(void)
{
}

HRESULT CRMmusicSelectManager::ShowMusicList( const std::vector<std::string>& musicVector ) const
{
	/*
	int totalMusicNum = musicVector.size();
	int indexFix = 0;
	//printConsole("Total Music Count:%d \n", totalMusicNum);

	if ( totalMusicNum > 0 )	// 0
	{
		indexFix = m_MusicSelectIndex % totalMusicNum;

		CRMlabel* musicList1 = new CRMlabel();
		musicList1->CreateLabel( LABEL_NAME_SELECT_LIST1 , string2wstring( CRMxmlLoader::GetInstance()->GetMusicData(musicVector.at(indexFix))->GetTitle() ), LABEL_FONT_NORMAL, 55.0F );
		musicList1->SetRGBA( 78.0f/255, 78.0f/255, 78.0f/255, 1.f );
		musicList1->SetSceneType( SCENE_SELECT_MUSIC );
		musicList1->SetPosition( 100 , ( SCREEN_SIZE_Y / 2 ) - 50 );
	}
	if ( totalMusicNum > 1 )	// 1
	{
		indexFix = (m_MusicSelectIndex + 1) % totalMusicNum;
		
		CRMlabel* musicList2 = new CRMlabel();
		musicList2->CreateLabel( LABEL_NAME_SELECT_LIST2 , string2wstring( CRMxmlLoader::GetInstance()->GetMusicData(musicVector.at(indexFix))->GetTitle() ), LABEL_FONT_NORMAL, 35.0F );
		musicList2->SetRGBA( 100.0f/255, 100.0f/255, 100.0f/255, 1.f );
		musicList2->SetSceneType( SCENE_SELECT_MUSIC );
		musicList2->SetPosition( 100 , ( SCREEN_SIZE_Y / 2 ) + 70 );
	}
	if ( totalMusicNum > 2 )	// -1
	{
		indexFix = (totalMusicNum + m_MusicSelectIndex - 1) % totalMusicNum;

		CRMlabel* musicList3 = new CRMlabel();
		musicList3->CreateLabel( LABEL_NAME_SELECT_LIST3 , string2wstring( CRMxmlLoader::GetInstance()->GetMusicData(musicVector.at(indexFix))->GetTitle() ), LABEL_FONT_NORMAL, 35.0F );
		musicList3->SetRGBA( 100.0f/255, 100.0f/255, 100.0f/255, 1.f );
		musicList3->SetSceneType( SCENE_SELECT_MUSIC );
		musicList3->SetPosition( 100 , ( SCREEN_SIZE_Y / 2 ) - 130 );
	}
	if ( totalMusicNum > 3 )	// 2
	{
		indexFix = (m_MusicSelectIndex + 2) % totalMusicNum;

		CRMlabel* musicList4 = new CRMlabel();
		musicList4->CreateLabel( LABEL_NAME_SELECT_LIST4 , string2wstring( CRMxmlLoader::GetInstance()->GetMusicData(musicVector.at(indexFix))->GetTitle() ), LABEL_FONT_NORMAL, 35.0F );
		musicList4->SetRGBA( 100.0f/255, 100.0f/255, 100.0f/255, 1.f );
		musicList4->SetSceneType( SCENE_SELECT_MUSIC );
		musicList4->SetPosition( 100 , ( SCREEN_SIZE_Y / 2 ) + 180 );
	}
	if ( totalMusicNum > 4 )	// -2
	{
		indexFix = (totalMusicNum + m_MusicSelectIndex - 2) % totalMusicNum;

		CRMlabel* musicList5 = new CRMlabel();
		musicList5->CreateLabel( LABEL_NAME_SELECT_LIST5 , string2wstring( CRMxmlLoader::GetInstance()->GetMusicData(musicVector.at(indexFix))->GetTitle() ), LABEL_FONT_NORMAL, 35.0F );
		musicList5->SetRGBA( 100.0f/255, 100.0f/255, 100.0f/255, 1.f );
		musicList5->SetSceneType( SCENE_SELECT_MUSIC );
		musicList5->SetPosition( 100 , ( SCREEN_SIZE_Y / 2 ) - 210 );
	}
	*/
	return NULL;
}

// Label이 wstring에서 string으로 바뀔때까지 임시로 가지는 함수
std::wstring CRMmusicSelectManager::string2wstring(const std::string& str) const {
	std::wstring wstr(str.length(),L' ');
	copy(str.begin(),str.end(),wstr.begin());
	return wstr;
}