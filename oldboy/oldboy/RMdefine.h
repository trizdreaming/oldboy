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

#define SCREEN_SIZE_X 1024 // 1024 + 16
#define SCREEN_SIZE_Y 662  // 668 + 32

#define NOTE_SIZE 100

#define MAX_NOTE_IN_POOL	200
#define MAX_EFFECT			20

#define DEFAULT_POSITION_X -5504
#define DEFAULT_POSITION_Y -5504

// judge Manager 에서 사용하는 값으로 노트의 시작 위치를 담당
#define NOTE_ONE_START_POSITION_X	405
#define NOTE_TWO_START_POSITION_X	920
#define NOTE_START_POSITION_Y		-100

// 아이템 시작 위치
#define ITEM_DISPLAY_POSITION_1P_X		270
#define ITEM_DISPLAY_POSITION_2P_X		785

// 데드라인 관련 위치
#define ITEM_DEAD_LINE				490
#define SHUTTER_DEAD_LINE			534

// 포지션 에러 발생 시 리턴 할 값
#define ERROR_POSITION -9504

#define NOTE_JUDGE_PERFECT_START_LINE	534
#define NOTE_JUDGE_PERFECT_END_LINE		556
#define NOTE_JUDGE_GOOD_START_LINE		514
#define NOTE_JUDGE_GOOD_END_LINE		576
#define NOTE_JUDGE_FAST_MISS_LINE		504
#define NOTE_JUDGE_LATE_MISS_LINE		565

// shutter 에서 사용하는 값으로 노트의 시작 위치를 담당
#define SHUTTER_P1_START_POSITION_X 0
#define SHUTTER_P2_START_POSITION_X 512
#define SHUTTER_START_POSITION_Y -668

// alert grow에서 사용하는 깜박임 속도
#define PLAY_ALERT_GROW_ANIMATION_SPEED 50

// shutter 관련 플레이어 HP 설정
#define PLAYER_HP_MAX		100
#define PLAYER_HP_MP_RATE	6.5f

// 점수 계산값 설정
#define SCORE_EACH_PERFECT 5
#define SCORE_EACH_GOOD 3
#define SCORE_EACH_MISS 0
#define SCORE_MAX_COMBO_RATE 2

#define MAX_INPUT_KEY		256