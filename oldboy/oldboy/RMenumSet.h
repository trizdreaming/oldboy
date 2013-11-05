#pragma once

enum SceneType
{
	SCENE_TITLE,
	SCENE_PLAY,
	SCENE_RESULT,
	NO_SCENE //SM9: 보통 ENUM 정의할 때, 의미 없는 원소는 ST_NONE 이런식으로 하고 가장 첫번째에 넣는다. (0부터 시작하니까)
};

enum LayerType
{
	LT_NONE, //SM9:  그러니까 아래 NO_LAYER는 이런식으로 네이밍을 하고 맨 앞에. 
	LAYER_BACKGROUND,
	LAYER_NOTE1,
	LAYER_NOTE2,
	LAYER_NOTE_HIT,
	LAYER_EFFECT,
	LAYER_SHUTTER,
	LAYER_LABEL,
	LAYER_MEMORY_POOL,
	NO_LAYER  
};

enum ObjectType
{
	OBJECT_BG_IMAGE_TITLE,
	OBJECT_BG_IMAGE_PLAY,
	OBJECT_NOTE_NORMAL_1,
	OBJECT_NOTE_NORMAL_2,
	OBJECT_EFFECT,
	OBJECT_NOTE_HIT,
	OBJECT_SHUTTER,
	NO_OBJECT //SM9: OT_NONE
};

enum KeyTable
{
	KEY_ESCAPE,
	KEY_RETURN,

	P1_TARGET1, //SM9: KT_P1_TARGET1 이렇게 enum의 약어를 따와서 prefix로 붙이는 네이밍..
	P1_TARGET2,
	P1_ATTACK,

	P2_TARGET1,
	P2_TARGET2,
	P2_ATTACK,

	NO_INPUT
};

enum PlayerNumber
{
	PLAYER_ONE,
	PLAYER_TWO,

	NO_PLAYER
};

enum CountType
{
	PERFECT_COUNT,
	GOOD_COUNT,
	MISS_COUNT,
	COMBO_COUNT,
	SCORE_COUNT,

	NO_COUNT
};

enum JudgeType
{
	JUDGE_PERFECT,
	JUDGE_GOOD,
	JUDGE_MISS,

	NO_JUDGE
};

enum KeyStatus
{
	KEY_DOWN,
	KEY_PRESSED,
	KEY_UP,
	KEY_NOTPRESSED,

	NO_KEYSTATUS
};