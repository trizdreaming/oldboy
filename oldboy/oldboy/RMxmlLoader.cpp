#include "stdafx.h"
#include "LibraryTinyXML/tinyxml.h"
#include "LibraryTinyXML/xpath_static.h"
#include "RMmacro.h"
#include "RMxmlLoader.h"
#include "RMmusicData.h"
#include "RMnoteData.h"
#include "RMdefine.h"

CRMxmlLoader::CRMxmlLoader(void)
{
}


CRMxmlLoader::~CRMxmlLoader(void)
{
	for ( auto& iter : m_MusicDataMap )
	{
		auto toBeDelete = iter.second;
		SafeDelete( toBeDelete );
	}
	m_MusicDataMap.clear();
}


HRESULT CRMxmlLoader::LoadMusicData(const std::string& folderName )
{
	std::string filePath;
	filePath.append("./Music/");
	filePath.append( folderName );
	filePath.append("/index.xml");
	TiXmlDocument document = TiXmlDocument( filePath.c_str() );

	// document.LoadFile(TIXML_ENCODING_UTF8);
	bool m_LoadSuccess = document.LoadFile();

	std::string title;
	std::string artist;
	std::string level;
	std::string imageAlbum;
	std::string imageBackground;
	std::string imageShutter;
	std::string imageNote1;
	std::string imageNote2;
	std::string imageNoteEffect;
	std::string soundBackground;
	std::string soundNoteEffect1;
	std::string soundNoteEffect2;

	std::string note;


	if ( m_LoadSuccess )
	{

		title = TinyXPath::S_xpath_string(document.RootElement(), "/Music/Title/text()").c_str();
		artist = TinyXPath::S_xpath_string(document.RootElement(), "/Music/Artist/text()").c_str();
		level = TinyXPath::S_xpath_string(document.RootElement(), "/Music/Level/text()").c_str();

		imageAlbum = TinyXPath::S_xpath_string(document.RootElement(), "/Music/Image/imageAlbum/text()").c_str();
		imageBackground = TinyXPath::S_xpath_string(document.RootElement(), "/Music/Image/imageBackground/text()").c_str();
		imageShutter = TinyXPath::S_xpath_string(document.RootElement(), "/Music/Image/imageShutter/text()").c_str();
		imageNote1 = TinyXPath::S_xpath_string(document.RootElement(), "/Music/Image/imageNote1/text()").c_str();
		imageNote2 = TinyXPath::S_xpath_string(document.RootElement(), "/Music/Image/imageNote2/text()").c_str();
		imageNoteEffect = TinyXPath::S_xpath_string(document.RootElement(), "/Music/Image/imageNoteEffect/text()").c_str();

		soundBackground = TinyXPath::S_xpath_string(document.RootElement(), "/Music/Sound/soundBackground/text()").c_str();
		soundNoteEffect1 = TinyXPath::S_xpath_string(document.RootElement(), "/Music/Sound/soundNoteEffect1/text()").c_str();
		soundNoteEffect2 = TinyXPath::S_xpath_string(document.RootElement(), "/Music/Sound/soundNoteEffect2/text()").c_str();

		note = TinyXPath::S_xpath_string(document.RootElement(), "/Music/Note/text()").c_str();

		printConsole("Loaded Music :%s \n", title.c_str());
		
	}

	if ( title == "" )
	{
		MessageBox( NULL, ERROR_MESSAGE_LOAD_XML_TITLE, ERROR_TITLE_LOAD, MB_OK | MB_ICONSTOP );
		return S_FALSE;
	}
	else if ( artist == "" )
	{
		MessageBox( NULL, ERROR_MESSAGE_LOAD_XML_ARTIST, ERROR_TITLE_LOAD, MB_OK | MB_ICONSTOP );
		return S_FALSE;
	}
	else if ( level == "" )
	{
		MessageBox( NULL, ERROR_MESSAGE_LOAD_XML_LEVEL, ERROR_TITLE_LOAD, MB_OK | MB_ICONSTOP );
		return S_FALSE;
	}
	else if ( imageAlbum == "" )
	{
		MessageBox( NULL, ERROR_MESSAGE_LOAD_XML_IMAGE_ALBUM, ERROR_TITLE_LOAD, MB_OK | MB_ICONSTOP );
		return S_FALSE;
	}
	else if ( imageBackground == "" )
	{
		MessageBox( NULL, ERROR_MESSAGE_LOAD_XML_IMAGE_BACKGROUND, ERROR_TITLE_LOAD, MB_OK | MB_ICONSTOP );
		return S_FALSE;
	}
	else if ( imageShutter == "" )
	{
		MessageBox( NULL, ERROR_MESSAGE_LOAD_XML_IMAGE_SHUTTER, ERROR_TITLE_LOAD, MB_OK | MB_ICONSTOP );
		return S_FALSE;
	}
	else if ( imageNote1 == "" )
	{
		MessageBox( NULL, ERROR_MESSAGE_LOAD_XML_IMAGE_NOTE1, ERROR_TITLE_LOAD, MB_OK | MB_ICONSTOP );
		return S_FALSE;
	}
	else if ( imageNote2 == "" )
	{
		MessageBox( NULL, ERROR_MESSAGE_LOAD_XML_IMAGE_NOTE2, ERROR_TITLE_LOAD, MB_OK | MB_ICONSTOP );
		return S_FALSE;
	}
	else if ( imageNoteEffect == "" )
	{
		MessageBox( NULL, ERROR_MESSAGE_LOAD_XML_IMAGE_NOTE_EFFECT, ERROR_TITLE_LOAD, MB_OK | MB_ICONSTOP );
		return S_FALSE;
	}
	else if ( soundBackground == "" )
	{
		MessageBox( NULL, ERROR_MESSAGE_LOAD_XML_SOUND_BACKGROUND, ERROR_TITLE_LOAD, MB_OK | MB_ICONSTOP );
		return S_FALSE;
	}
	else if ( soundNoteEffect1 == "" )
	{
		MessageBox( NULL, ERROR_MESSAGE_LOAD_XML_SOUND_NOTE_EFFECT1, ERROR_TITLE_LOAD, MB_OK | MB_ICONSTOP );
		return S_FALSE;
	}
	else if ( soundNoteEffect2 == "" )
	{
		MessageBox( NULL, ERROR_MESSAGE_LOAD_XML_SOUND_NOTE_EFFECT2, ERROR_TITLE_LOAD, MB_OK | MB_ICONSTOP );
		return S_FALSE;
	}
	else if ( note == "" )
	{
		MessageBox( NULL, ERROR_MESSAGE_LOAD_XML_NOTE_DATA, ERROR_TITLE_LOAD, MB_OK | MB_ICONSTOP );
		return S_FALSE;
	}

	auto& toBeDelete = m_MusicDataMap[folderName];
	SafeDelete( toBeDelete );
	m_MusicDataMap[folderName] = new CRMmusicData();
	
	m_MusicDataMap[folderName]->SetTitle( title );
	m_MusicDataMap[folderName]->SetArtist( artist );
	m_MusicDataMap[folderName]->SetLevel( level );
	m_MusicDataMap[folderName]->SetImageAlbum( imageAlbum );
	m_MusicDataMap[folderName]->SetImageBackground( imageBackground );
	m_MusicDataMap[folderName]->SetImageShutter( imageShutter );
	m_MusicDataMap[folderName]->SetImageNote1( imageNote1 );
	m_MusicDataMap[folderName]->SetImageNote2( imageNote2 );
	m_MusicDataMap[folderName]->SetImageNoteEffect( imageNoteEffect );
	m_MusicDataMap[folderName]->SetSoundBackground( soundBackground );
	m_MusicDataMap[folderName]->SetSoundNoteEffect1( soundNoteEffect1 );
	m_MusicDataMap[folderName]->SetSoundNoteEffect2( soundNoteEffect2 );
	m_MusicDataMap[folderName]->SetNote( note );

	return S_OK;

}

HRESULT CRMxmlLoader::LoadNoteData( const std::string& folderName )
{
	std::string filePath;
	filePath.append("./Music/");
	filePath.append( folderName );
	filePath.append("/");
	filePath.append( m_MusicDataMap[folderName]->GetNote() );

	TiXmlDocument document = TiXmlDocument( filePath.c_str() );

	bool m_LoadSuccess = document.LoadFile();

	if ( m_LoadSuccess )
	{
		if ( m_NoteList.size() > 0 )
		{
			for ( auto& toBeDelete : m_NoteList )
			{
				SafeDelete( toBeDelete );
			}
		}

		m_NoteList.clear();

		TiXmlNode* node = document.FirstChild("Notes")->FirstChild("Note");
		while ( node != NULL )
		{
			int time = 0;
			int level = 0;
			node->ToElement()->Attribute("time", &time);
			node->ToElement()->Attribute("level", &level);
			std::string type = node->ToElement()->GetText();


			CRMnoteData* noteData = new CRMnoteData (time, level, (type == "left") ? OBJECT_NOTE_NORMAL_1 : OBJECT_NOTE_NORMAL_2 );
			m_NoteList.push_back( noteData );
			node = node->NextSibling();
		}

		/*

		TiXmlNode* node = document.FirstChild("Notes");

		int	bpm = 0;
		if ( node != NULL )
		{
			node->ToElement()->Attribute("bpm", &bpm);
		}

		node = document.FirstChild("End");

		int endTime = 0;
		if ( node != NULL )
		{
			node->ToElement()->Attribute("time", &endTime);
		}

		node = document.FirstChild("Notes")->FirstChild("Note");

		int level = 0;

		int beat1Time = 0;
		int nextTime = 0;

		int endJoint = 0;
		int jointCount = 0;

		std::string type;
		CRMnoteData* noteData = nullptr;

		while ( node != NULL && nextTime < endTime)
		{
			node->ToElement()->Attribute("start", &beat1Time);
			node->ToElement()->Attribute("end", &endJoint);
			type = node->ToElement()->GetText();

			nextTime = beat1Time + ( 1000 * 60 / bpm );

			jointCount = 0;

			if ( type == "on" )
			{
				while ( beat1Time < endJoint )
				{
					printConsole ( "%d밀리초에 노트 하나 추가요~! \n", (beat1Time + (jointCount * 60 / bpm) - 2152) );

					noteData = new CRMnoteData( (beat1Time + (jointCount * 60 / bpm) - 2152) , (jointCount % 2) + 1 , (jointCount++ % 2 == 0) ? OBJECT_NOTE_NORMAL_1 : OBJECT_NOTE_NORMAL_2 );
					// 2152 = 화면 최상단에서 판정판까지 내려오기까지 걸리는 시간 ms
					m_NoteList.push_back( noteData );

					beat1Time += 1000 * 60 / bpm;
				}
			}

			node = node->NextSibling();
		}
		*/
	}
	
	if ( m_NoteList.size() == 0 )
	{
		return S_FALSE;
	}

	return S_OK;
}

CRMnoteData* CRMxmlLoader::GetNoteFirst()
{
	if ( m_NoteList.size() == 0 )
	{
		return nullptr;
	}
	return *(m_NoteList.begin());
}

HRESULT CRMxmlLoader::DeleteNoteFirst()
{
	if ( m_NoteList.size() == 0 )
	{
		return S_FALSE;
	}

	auto& toBeDelete = m_NoteList.begin();
	SafeDelete( *toBeDelete );

	m_NoteList.pop_front();

	return S_OK;
}
