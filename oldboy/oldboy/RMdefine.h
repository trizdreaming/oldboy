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

#define SCREEN_SIZE_X 1040 // 1024 + 16
#define SCREEN_SIZE_Y 700  // 668 + 32

#define NOTE_SIZE 100

#define DEFAULT_POSITION_X 5504
#define DEFAULT_POSITION_Y 5504

// judge Manager 에서 사용하는 값으로 노트의 시작 위치를 담당
#define NOTE_ONE_START_POSITION_X	395
#define NOTE_TWO_START_POSITION_X	910
#define NOTE_START_POSITION_Y		-100

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

// Label 관련 define
#define LABEL_JUDGE_PERFECT	L"PERFECT!!"
#define LABEL_JUDGE_GOOD	L"  GOOD!  "
#define LABEL_JUDGE_MISS	L"  MISS..."

#define LABEL_PLAY_SCORE	L"SCORE"
#define LABEL_PLAY_COMBO	L"COMBO"

#define LABEL_NAME_P1_SCORE	L"플레이어1점수"
#define LABEL_NAME_P1_COMBO	L"플레이어1콤보"
#define LABEL_NAME_P2_SCORE	L"플레이어2점수"
#define LABEL_NAME_P2_COMBO	L"플레이어2콤보"

#define LABEL_FONT_NORMAL	L"맑은 고딕"

#define LABEL_FPS			L"FPS"

#define MAX_INPUT_KEY		20

#define MAX_COUNT			6


// Resource 관련

#define FOLDER_SLASH		"/"
#define MUSIC_FOLDER_SEARCH	"./Music/.\\*"
#define MUSIC_FOLDER		"./Music/"
#define BGM_TITLE			"./Resource/bgm_title_00_01.mp3"

#define BG_IMAGE_DEFAULT	L"./Resource/image_bg_00_01.png"

// Error 관련 

#define ERROR_TITLE			L"ERROR!"
#define ERROR_CHANGE_SCENE	L"Error to Change Scene"

#define ERROR_SOUND_INIT	L"Error Sound Initialize...."
#define ERROR_SOUND_LOADING	L"Error Loading Sound Files...."

#define ERROR_CREATE_RESOURCE		L"Error to Create Object Resources"
#define ERROR_CREATE_RENDER			L"Error to Create Renderer"
#define ERROR_CREATE_RENDER_TARGET	L"Error to Create Render Target"
#define ERROR_CREATE_WIC_FACTORY	L"Error to Create WIC Factory"

#define ERROR_CREATE_BG_IMAGE		L"Error to Create BackGround Texture"
#define ERROR_LOAD_IMAGE	L"Error Loading Image Files...."
#define ERROR_LOAD_SOUND	L"Error Loading Sound Files...."

#define ERROR_LOAD_IMAGE_CONSOLE	"Image Loading Error! (%d) \n"
#define ERROR_FMOD_CONSOLE			"FMOD error! (%d) %s\n"