#pragma once

enum SceneType
{
	SCENE_NONE,

	SCENE_OPENING,
	SCENE_TITLE,
	SCENE_SELECT_MUSIC,
	SCENE_PLAY,
	SCENE_RESULT,

	SCENE_MAX
};

enum LayerType
{
	LAYER_NONE,

	LAYER_BACKGROUND,
	LAYER_JUDGE_RING,		//item 구현용
	LAYER_GAUGE_PLAYER1,	//item 구현용
	LAYER_GAUGE_PLAYER2,	//item 구현용
	LAYER_ITEMCARD_PLAYER1,	//item 구현용
	LAYER_ITEMCARD_PLAYER2,	//item 구현용
	LAYER_TIERFLAG_PLAYER1,	//item 구현용
	LAYER_TIERFLAG_PLAYER2,	//item 구현용
	LAYER_NOTE1,
	LAYER_NOTE2,
	LAYER_NOTE_HIT,
	LAYER_EFFECT,
	LAYER_SHUTTER,
	LAYER_LABEL,
	LAYER_MEMORY_POOL,
	LAYER_PAUSE,

	LAYER_MAX
};

enum ObjectType
{
	OBJECT_NONE,

	OBJECT_BG_IMAGE_TITLE,
	OBJECT_BG_IMAGE_SELECT,
	OBJECT_BG_IMAGE_PLAY,
	OBJECT_BG_IMAGE_RESULT,

	OBJECT_PAUSE_IMAGE_PLAY_CANCEL,
	OBJECT_PAUSE_IMAGE_PLAY_OK,
	OBJECT_PAUSE_IMAGE_TITLE_CANCEL,
	OBJECT_PAUSE_IMAGE_TITLE_OK,

	OBJECT_JUDGE_RING, //item 구현용
	OBJECT_GAUGE_1P,  //item 구현용
	OBJECT_GAUGE_2P,  //item 구현용

	OBJECT_NOTE_NORMAL_1,
	OBJECT_NOTE_NORMAL_2,
	OBJECT_EFFECT,
	OBJECT_NOTE_HIT,
	OBJECT_SHUTTER,
	OBJECT_ALBUM_IMAGE,

	OBJECT_MAX
};

enum SoundType
{
	SOUND_NONE,

	SOUND_BG_TITLE,
	SOUND_BG_PLAY,
	SOUND_BG_RESULT,
	SOUND_NOTE_1,
	SOUND_NOTE_2,
	SOUND_NOTE_EFFECT,
	SOUND_SHUTTER,

	SOUND_MAX
};

enum PlayerNumber
{
	PLAYER_NONE,

	PLAYER_ONE,
	PLAYER_TWO,

	PLAYER_MAX
};

enum CountType
{
	COUNT_NONE,

	COUNT_PERFECT,
	COUNT_GOOD,
	COUNT_MISS,
	COUNT_COMBO,
	COUNT_MAX_COMBO,
	COUNT_COMBO_SCORE,
	COUNT_SCORE,

	COUNT_MAX
};

enum JudgeType
{
	JUDGE_NONE,

	JUDGE_PERFECT,
	JUDGE_GOOD,
	JUDGE_MISS,

	JUDGE_MAX
};

enum KeyStatus
{
	KEY_STATUS_NONE,

	KEY_STATUS_DOWN,
	KEY_STATUS_PRESSED,
	KEY_STATUS_UP,
	KEY_STATUS_NOT_PRESSED,

	KEY_MAX
};

enum ItemType
{
	ITEM_TYPE_NONE,
	//////////////////////////////////////////////////////////////////////////
	// 1 Tier
	ITEM_T1_NONE,

	ITEM_T1_REST,		// 잠시 쉬기
	ITEM_T1_MIST,		// 안개
	ITEM_T1_DUPLICATE,	// 따다닥
	
	ITEM_T1_MAX,
	//////////////////////////////////////////////////////////////////////////
	// 2 Tier
	ITEM_T2_NONE,

	ITEM_T2_DELAY,		// 노트 밀림
	ITEM_T2_ROTATE,		// 노트 빙글 회전
	ITEM_T2_GAUGE_CLEAR,// 상대방 공격 게이지 클리어
	ITEM_T2_BARRIER,	// 보호막

	ITEM_T2_MAX,
	//////////////////////////////////////////////////////////////////////////
	// 3 Tier
	ITEM_T3_NONE,

	ITEM_T3_REVERSE,	// 노트가 계속 반전
	ITEM_T3_RECOVERY,	// 셔터 회복

	ITEM_T3_MAX,
	//////////////////////////////////////////////////////////////////////////
	// END
	ITEM_TYPE_MAX
}; // 추후 아이템 구현에 맞게 수정합시다.

enum ItemTierType
{
	TIER_NONE,

	TIER_1P_ONE,
	TIER_1P_TWO,
	TIER_1P_THREE,

	TIER_2P_ONE,
	TIER_2P_TWO,
	TIER_2P_THREE,

	TIER_MAX
};