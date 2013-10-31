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


#define SCREEN_SIZE_X 1040 // 1024 + 16
#define SCREEN_SIZE_Y 700  // 668 + 32

#define NOTE_SIZE 100

#define DEFAULT_POSITION_X 5504
#define DEFAULT_POSITION_Y 5504

#define MAX_INPUT_KEY	20

