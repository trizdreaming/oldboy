#include "stdafx.h"
#include "oldboy.h"
#include "RMxmlLoader.h"
#include "RMmusicData.h"
#include "RMnoteData.h"

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

	std::string filePath = "";
	filePath.append("./Music/");
	filePath.append( folderName );
	filePath.append("/index.xml");
	TiXmlDocument m_Document = TiXmlDocument( filePath.c_str() );

	//m_Document.LoadFile(TIXML_ENCODING_UTF8);
	bool m_LoadSuccess = m_Document.LoadFile();

	std::string title;
	std::string artist;
	std::string level;
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

		title = TinyXPath::S_xpath_string(m_Document.RootElement(), "/Music/Title/text()").c_str();
		artist = TinyXPath::S_xpath_string(m_Document.RootElement(), "/Music/Artist/text()").c_str();
		level = TinyXPath::S_xpath_string(m_Document.RootElement(), "/Music/Level/text()").c_str();

		imageBackground = TinyXPath::S_xpath_string(m_Document.RootElement(), "/Music/Image/imageBackground/text()").c_str();
		imageShutter = TinyXPath::S_xpath_string(m_Document.RootElement(), "/Music/Image/imageShutter/text()").c_str();
		imageNote1 = TinyXPath::S_xpath_string(m_Document.RootElement(), "/Music/Image/imageNote1/text()").c_str();
		imageNote2 = TinyXPath::S_xpath_string(m_Document.RootElement(), "/Music/Image/imageNote2/text()").c_str();
		imageNoteEffect = TinyXPath::S_xpath_string(m_Document.RootElement(), "/Music/Image/imageNoteEffect/text()").c_str();

		soundBackground = TinyXPath::S_xpath_string(m_Document.RootElement(), "/Music/Sound/soundBackground/text()").c_str();
		soundNoteEffect1 = TinyXPath::S_xpath_string(m_Document.RootElement(), "/Music/Sound/soundNoteEffect1/text()").c_str();
		soundNoteEffect2 = TinyXPath::S_xpath_string(m_Document.RootElement(), "/Music/Sound/soundNoteEffect2/text()").c_str();

		note = TinyXPath::S_xpath_string(m_Document.RootElement(), "/Music/Note/text()").c_str();

		printConsole("Loaded Music :%s \n", title.c_str());
		
	}

	if ( title == "" || artist == "" || level == "" || imageBackground == "" || imageShutter == "" || imageNote1 == "" || imageNote2 == "" || imageNoteEffect == "" || soundBackground == "" || soundNoteEffect1 == "" || soundNoteEffect2 == "" || note == "" )
	{
		return S_FALSE;
	}
	
	m_MusicDataMap[folderName] = new CRMmusicData( title, artist, level, imageBackground, imageShutter, imageNote1, imageNote2, imageNoteEffect, soundBackground, soundNoteEffect1, soundNoteEffect2, note );
	
	return S_OK;

}

HRESULT CRMxmlLoader::LoadNoteData( const std::string& folderName )
{
	std::string filePath = "";
	filePath.append("./Music/");
	filePath.append( folderName );
	filePath.append("/");
	filePath.append( m_MusicDataMap[folderName]->GetNote() );

	TiXmlDocument m_Document = TiXmlDocument( filePath.c_str() );

	bool m_LoadSuccess = m_Document.LoadFile();

	if ( m_LoadSuccess )
	{
		m_NoteList.clear();

		TiXmlNode* node = m_Document.FirstChild("Notes")->FirstChild("Note");
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

	m_NoteList.pop_front();
	return S_OK;
}
