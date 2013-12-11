#include "stdafx.h"
#include "RMconst.h"

const wchar_t* GAME_NAME	= L"Rhythm Match v0.125";
const wchar_t* CLASS_NAME	= L"RhythmMatch";

// Label 관련 define
const wchar_t* LABEL_JUDGE_PERFECT	= L"PERFECT!!";
const wchar_t* LABEL_JUDGE_GOOD		= L"  GOOD!  ";
const wchar_t* LABEL_JUDGE_MISS		= L"  MISS...";

const wchar_t* LABEL_PLAY_SCORE		= L"SCORE";
const wchar_t* LABEL_PLAY_COMBO		= L"COMBO";

const char* LABEL_RESULT_SCORE			= "SCORE   : ";
const char* LABEL_RESULT_PERFECT		= "PERFECT : ";
const char* LABEL_RESULT_GOOD			= "GOOD    : ";
const char* LABEL_RESULT_MISS			= "MISS    : ";
const char* LABEL_RESULT_COMBO_BONUS	= "COMBO BONUS   : ";
const char* LABEL_RESULT_MAX_COMBO		= "MAX COMBO   : ";

const wchar_t* LABEL_NAME_P1_SCORE	= L"플레이어1점수";
const wchar_t* LABEL_NAME_P1_COMBO	= L"플레이어1콤보";
const wchar_t* LABEL_NAME_P2_SCORE	= L"플레이어2점수";
const wchar_t* LABEL_NAME_P2_COMBO	= L"플레이어2콤보";

const wchar_t* LABEL_NAME_SELECT_LIST1	= L"셀렉트리스트1";
const wchar_t* LABEL_NAME_SELECT_LIST2	= L"셀렉트리스트2";
const wchar_t* LABEL_NAME_SELECT_LIST3	= L"셀렉트리스트3";
const wchar_t* LABEL_NAME_SELECT_LIST4	= L"셀렉트리스트4";
const wchar_t* LABEL_NAME_SELECT_LIST5	= L"셀렉트리스트5";

const wchar_t* LABEL_FONT_NORMAL	= L"맑은 고딕";

const wchar_t* LABEL_FPS			= L"FPS";

// Resource 관련

const char* FOLDER_SLASH			= "/";
const char* MUSIC_FOLDER_SEARCH		= "./Music/.\\*"; // 뮤직 폴더 이하 모든 파일 의미
const char* MUSIC_FOLDER			= "./Music/";
const char* BGM_TITLE				= "./Resource/bgm_title_00_01.mp3";
const char* BGM_RESULT				= "./Resource/bgm_result_00_01.mp3";

const wchar_t* OPENING_VIDEO_FILE	= L"./Resource/sample.avi";

const wchar_t* BG_IMAGE_TITLE	= L"./Resource/image_bg_00_01.png";
const wchar_t* BG_IMAGE_SELECT	= L"./Resource/image_bg_select_01.png";
const wchar_t* BG_IMAGE_RESULT	= L"./Resource/image_bg_result_01.png";

const wchar_t* PLAY_IMAGE_JUDGE_RING	= L"./Resource/judgeRing.png";
const wchar_t* PLAY_IMAGE_BLUE_GAUGE	= L"./Resource/blueBar.png";
const wchar_t* PLAY_IMAGE_RED_GAUGE		= L"./Resource/redBar.png";

const wchar_t* PAUSE_IMAGE_PLAY_CANCEL	= L"./Resource/image_pa_play_01.png";
const wchar_t* PAUSE_IMAGE_PLAY_OK		= L"./Resource/image_pa_play_02.png";
const wchar_t* PAUSE_IMAGE_TITLE_CANCEL	= L"./Resource/image_pa_title_01.png";
const wchar_t* PAUSE_IMAGE_TITLE_OK		= L"./Resource/image_pa_title_02.png";

// Error 관련 
// 현재 에러는 콘솔 창에서 표현되는 것

// 메시지 박스 타이틀 ERROR_TITLE_~~~
const wchar_t* ERROR_TITLE_NORMAL			= L"ERROR!";
const wchar_t* ERROR_TITLE_LOAD				= L"LOAD ERROR!";
const wchar_t* ERROR_TITLE_NULLPTR			= L"NULLPTR ERROR!";

// 메시지 박스 내용  ERROR_MESSAGE_~~~

// xmlLoader 관련 
const wchar_t* ERROR_MESSAGE_LOAD_XML_TITLE					= L"Missing title Data in index.xml";
const wchar_t* ERROR_MESSAGE_LOAD_XML_ARTIST				= L"Missing artist Data in index.xml";
const wchar_t* ERROR_MESSAGE_LOAD_XML_LEVEL					= L"Missing level Data in index.xml";
const wchar_t* ERROR_MESSAGE_LOAD_XML_IMAGE_ALBUM			= L"Missing imageAlbum Data in index.xml";
const wchar_t* ERROR_MESSAGE_LOAD_XML_IMAGE_BACKGROUND		= L"Missing imageBackground Data in index.xml";
const wchar_t* ERROR_MESSAGE_LOAD_XML_IMAGE_SHUTTER			= L"Missing imageShutter Data in index.xml";
const wchar_t* ERROR_MESSAGE_LOAD_XML_IMAGE_NOTE1			= L"Missing imageNote1 Data in index.xml";
const wchar_t* ERROR_MESSAGE_LOAD_XML_IMAGE_NOTE2			= L"Missing imageNote2 Data in index.xml";
const wchar_t* ERROR_MESSAGE_LOAD_XML_IMAGE_NOTE_EFFECT		= L"Missing imageNoteEffect Data in index.xml";
const wchar_t* ERROR_MESSAGE_LOAD_XML_SOUND_BACKGROUND		= L"Missing soundBackground Data in index.xml";
const wchar_t* ERROR_MESSAGE_LOAD_XML_SOUND_NOTE_EFFECT1	= L"Missing soundNoteEffect1 Data in index.xml";
const wchar_t* ERROR_MESSAGE_LOAD_XML_SOUND_NOTE_EFFECT2	= L"Missing soundNoteEffect2 Data in index.xml";
const wchar_t* ERROR_MESSAGE_LOAD_XML_NOTE_DATA				= L"Missing note Data in index.xml";

const wchar_t* ERROR_CHANGE_SCENE	= L"Error to Change Scene";

const wchar_t* ERROR_SOUND_INIT		= L"Error Sound Initialize....";
const wchar_t* ERROR_SOUND_LOADING	= L"Error Loading Sound Files....";

const wchar_t* ERROR_TEXTURE_NULLPTR		= L"Texture Pointer Null Error";

const wchar_t* ERROR_CREATE_RESOURCE		= L"Error to Create Object Resources";
const wchar_t* ERROR_CREATE_RENDER			= L"Error to Create Renderer";
const wchar_t* ERROR_CREATE_RENDER_TARGET	= L"Error to Create Render Target";
const wchar_t* ERROR_CREATE_WIC_FACTORY		= L"Error to Create WIC Factory";

const wchar_t* ERROR_CREATE_BG_IMAGE		= L"Error to Create BackGround Texture";
const wchar_t* ERROR_LOAD_MUSIC_XML			= L"Error Loading Music Index File....";
const wchar_t* ERROR_LOAD_IMAGE				= L"Error Loading Image Files....";
const wchar_t* ERROR_LOAD_SOUND				= L"Error Loading Sound Files....";

const wchar_t* ERROR_CREATE_BANDIVID	= L"Error creating BandiVideoLibrary.";
const wchar_t* ERROR_LOAD_VIDEO			= L"Error Getting Video Info....";
const wchar_t* ERROR_LOAD_VIDEO_DEVICE	= L"Error Opening Video Device...";
const wchar_t* ERROR_VIDEO_NULLPTR		= L"Video Texture Pointer Null Error";

const wchar_t* ERROR_LOAD_FILE			= L"Error opening file...";

const char* ERROR_LOAD_IMAGE_CONSOLE	= "Image Loading Error! (%d) \n";
const char* ERROR_FMOD_CONSOLE			= "FMOD Error! (%d) %s\n";