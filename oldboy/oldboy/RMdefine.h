#pragma once

//이미지 도큐먼트 헤더 형식 지정 관련 정의
#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

//define for memroy leak check
#ifdef _DEBUG
#define	new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif

#define GAME_NAME	L"Rhythm Match v0.125"
#define CLASS_NAME	L"RhythmMatch"

#define SCREEN_SIZE_X 1024 // 1024 + 16
#define SCREEN_SIZE_Y 662  // 668 + 32

#define NOTE_SIZE 100

#define MAX_NOTE_IN_POOL	200
#define MAX_EFFECT			20

#define DEFAULT_POSITION_X -5504
#define DEFAULT_POSITION_Y -5504

// judge Manager 에서 사용하는 값으로 노트의 시작 위치를 담당
#define NOTE_ONE_START_POSITION_X	395
#define NOTE_TWO_START_POSITION_X	910
#define NOTE_START_POSITION_Y		-100

// 아이템 시작 위치
#define ITEM_DISPLAY_POSITION_1P_X		295
#define ITEM_DISPLAY_POSITION_2P_X		810

// 포지션 에러 발생 시 리턴 할 값
#define ERROR_POSITION -9504

#define NOTE_JUDGE_PERFECT_START_LINE	534
#define NOTE_JUDGE_PERFECT_END_LINE		556
#define NOTE_JUDGE_GOOD_START_LINE		514
#define NOTE_JUDGE_GOOD_END_LINE		576
#define NOTE_JUDGE_FAST_MISS_LINE		504
#define NOTE_JUDGE_LATE_MISS_LINE		555

// shutter 에서 사용하는 값으로 노트의 시작 위치를 담당
#define SHUTTER_P1_START_POSITION_X 0
#define SHUTTER_P2_START_POSITION_X 515
#define SHUTTER_START_POSITION_Y -668

// shutter 관련 플레이어 HP 설정
#define PLAYER_HP_MAX		10

// Label 관련 define
#define LABEL_JUDGE_PERFECT	L"PERFECT!!"
#define LABEL_JUDGE_GOOD	L"  GOOD!  "
#define LABEL_JUDGE_MISS	L"  MISS..."

#define LABEL_PLAY_SCORE	L"SCORE"
#define LABEL_PLAY_COMBO	L"COMBO"

#define LABEL_RESULT_SCORE		"SCORE   : "
#define LABEL_RESULT_PERFECT	"PERFECT : "
#define LABEL_RESULT_GOOD		"GOOD    : "
#define LABEL_RESULT_MISS		"MISS    : "
#define LABEL_RESULT_COMBO		"COMBO   : "

#define LABEL_NAME_P1_SCORE	L"플레이어1점수"
#define LABEL_NAME_P1_COMBO	L"플레이어1콤보"
#define LABEL_NAME_P2_SCORE	L"플레이어2점수"
#define LABEL_NAME_P2_COMBO	L"플레이어2콤보"

#define LABEL_NAME_SELECT_LIST1	L"셀렉트리스트1"
#define LABEL_NAME_SELECT_LIST2	L"셀렉트리스트2"
#define LABEL_NAME_SELECT_LIST3	L"셀렉트리스트3"
#define LABEL_NAME_SELECT_LIST4	L"셀렉트리스트4"
#define LABEL_NAME_SELECT_LIST5	L"셀렉트리스트5"

#define LABEL_FONT_NORMAL	L"맑은 고딕"

#define LABEL_FPS			L"FPS"

#define MAX_INPUT_KEY		256

// Resource 관련

#define FOLDER_SLASH		"/"
#define MUSIC_FOLDER_SEARCH	"./Music/.\\*" // 뮤직 폴더 이하 모든 파일 의미
#define MUSIC_FOLDER		"./Music/"
#define BGM_TITLE			"./Resource/bgm_title_00_01.mp3"

#define OPENING_VIDEO_FILE	L"./Resource/sample.avi"

#define BG_IMAGE_TITLE	L"./Resource/image_bg_00_01.png"
#define BG_IMAGE_SELECT	L"./Resource/image_bg_select_01.png"
#define BG_IMAGE_RESULT	L"./Resource/image_bg_result_01.png"

#define PLAY_IMAGE_JUDGE_RING	L"./Resource/judgeRing.png"
#define PLAY_IMAGE_BLUE_GAUGE	L"./Resource/blueBar.png"
#define PLAY_IMAGE_RED_GAUGE	L"./Resource/redBar.png"

#define PAUSE_IMAGE_PLAY_CANCEL	L"./Resource/image_pa_play_01.png"
#define PAUSE_IMAGE_PLAY_OK	L"./Resource/image_pa_play_02.png"
#define PAUSE_IMAGE_TITLE_CANCEL	L"./Resource/image_pa_title_01.png"
#define PAUSE_IMAGE_TITLE_OK	L"./Resource/image_pa_title_02.png"

// Error 관련 
// 현재 에러는 콘솔 창에서 표현되는 것

// 메시지 박스 타이틀 ERROR_TITLE_~~~
#define ERROR_TITLE_NORMAL			L"ERROR!"
#define ERROR_TITLE_LOAD			L"LOAD ERROR!"
#define ERROR_TITLE_NULLPTR			L"NULLPTR ERROR!"

// 메시지 박스 내용  ERROR_MESSAGE_~~~

// xmlLoader 관련 
#define ERROR_MESSAGE_LOAD_XML_TITLE				L"Missing title Data in index.xml"
#define ERROR_MESSAGE_LOAD_XML_ARTIST				L"Missing artist Data in index.xml"
#define ERROR_MESSAGE_LOAD_XML_LEVEL				L"Missing level Data in index.xml"
#define ERROR_MESSAGE_LOAD_XML_IMAGE_ALBUM			L"Missing imageAlbum Data in index.xml"
#define ERROR_MESSAGE_LOAD_XML_IMAGE_BACKGROUND		L"Missing imageBackground Data in index.xml"
#define ERROR_MESSAGE_LOAD_XML_IMAGE_SHUTTER		L"Missing imageShutter Data in index.xml"
#define ERROR_MESSAGE_LOAD_XML_IMAGE_NOTE1			L"Missing imageNote1 Data in index.xml"
#define ERROR_MESSAGE_LOAD_XML_IMAGE_NOTE2			L"Missing imageNote2 Data in index.xml"
#define ERROR_MESSAGE_LOAD_XML_IMAGE_NOTE_EFFECT	L"Missing imageNoteEffect Data in index.xml"
#define ERROR_MESSAGE_LOAD_XML_SOUND_BACKGROUND		L"Missing soundBackground Data in index.xml"
#define ERROR_MESSAGE_LOAD_XML_SOUND_NOTE_EFFECT1	L"Missing soundNoteEffect1 Data in index.xml"
#define ERROR_MESSAGE_LOAD_XML_SOUND_NOTE_EFFECT2	L"Missing soundNoteEffect2 Data in index.xml"
#define ERROR_MESSAGE_LOAD_XML_NOTE_DATA			L"Missing note Data in index.xml"

#define ERROR_CHANGE_SCENE	L"Error to Change Scene"

#define ERROR_SOUND_INIT	L"Error Sound Initialize...."
#define ERROR_SOUND_LOADING	L"Error Loading Sound Files...."

#define ERROR_TEXTURE_NULLPTR		L"Texture Pointer Null Error"

#define ERROR_CREATE_RESOURCE		L"Error to Create Object Resources"
#define ERROR_CREATE_RENDER			L"Error to Create Renderer"
#define ERROR_CREATE_RENDER_TARGET	L"Error to Create Render Target"
#define ERROR_CREATE_WIC_FACTORY	L"Error to Create WIC Factory"

#define ERROR_CREATE_BG_IMAGE		L"Error to Create BackGround Texture"
#define ERROR_LOAD_MUSIC_XML	L"Error Loading Music Index File...."
#define ERROR_LOAD_IMAGE	L"Error Loading Image Files...."
#define ERROR_LOAD_SOUND	L"Error Loading Sound Files...."

#define ERROR_CREATE_BANDIVID	L"Error creating BandiVideoLibrary."
#define ERROR_LOAD_VIDEO		L"Error Getting Video Info...."
#define ERROR_LOAD_VIDEO_DEVICE	L"Error Opening Video Device..."
#define ERROR_VIDEO_NULLPTR		L"Video Texture Pointer Null Error"

#define ERROR_LOAD_FILE			L"Error opening file..."	

#define ERROR_LOAD_IMAGE_CONSOLE	"Image Loading Error! (%d) \n"
#define ERROR_FMOD_CONSOLE			"FMOD Error! (%d) %s\n"