#pragma once

//Display - Direct 2D관련 include file
#include <d2d1.h>
#include <d2d1helper.h>

//Sound - fmod관련 include file
#include "Library//fmod.h"
#include "Library/fmod.hpp"
#include "Library/fmod_errors.h"

//
#include <stdio.h>
#include <timeapi.h>
#include <wincodec.h>
#include <map>

//Microsoft Visual C++ generated include file.
#include "resource.h"

// class include
// #include "RMmainLoop.h"
// 헤더 파일이 순환 구조로 부르는 형태로 되어 있음
// RMmainLoop.h -> RMinclude -> oldboy.h -> RMmainLoop.h 이런 형태로 되어 있는 구조
// 
// 확인 후 이 주석은 삭제 할 것