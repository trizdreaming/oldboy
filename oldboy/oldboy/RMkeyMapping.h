#pragma once

#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A


///////////////////////////////////////////////////////////////////////
//_getch 사용은 어떤지? 대소문자 구분도 없음
/*
sample code
#include <iostream>
#include <conio.h>  // getch()함수 사용하기 위해서 포함.

#define LEFT   75
#define RIGHT  77
#define UP       72
#define DOWN  80
#define ESC     27
#define SPACE 32
#define FUN1    59
#define FUN2    60
#define ENTER 13

using namespace std;

int main()
{
cout << "Left, Right, Up, Down, ESC, Space, Fun1, Fun2" << endl;
cout << "키보드의 코드를 입력하세요" << endl;

int keys = 0;
do
{
keys = _getch();
switch(keys)
{
case LEFT :
	cout << keys << " 왼쪽" << endl;
	break;
case RIGHT : 
	cout << keys <<" 오른쪽" << endl;
	break;
case UP : 
	cout << keys <<" 위" << endl;
	break;
case DOWN :
	cout << keys <<" 아래" << endl;
	break;
case ESC :
	cout << keys <<" ESC Key" << endl;
	break;
case SPACE :
	cout << keys <<" Space" << endl;
	break;
case FUN1 :
	cout << keys <<" F1키" << endl;
	break;
case FUN2 :
	cout << keys <<" F2키" << endl;
	break;
default :
	cout << keys << ' ';
	break;
}
}while(keys != ENTER);

return EXIT_SUCCESS;
}
*/