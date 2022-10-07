//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_BGM002,			// BGM2
	SOUND_LABEL_BGM003,			// BGM3
	SOUND_LABEL_SE000,			// 決定音
	SOUND_LABEL_SE_SHOT,		// 弾発射音
	SOUND_LABEL_SE_ITEM,		// ヒット音
	SOUND_LABEL_SE_HIT,			// 爆発音
	SOUND_LABEL_SE_DAMAGE,		// 敵と当たった音
	SOUND_LABEL_SE_BLOCK,		// ブロックと当たった音
	SOUND_LABEL_SE_GOAL,		// ゴールした音
	SOUND_LABEL_SE_WALK,		// 歩く音
	SOUND_LABEL_SE_FALL,		// 落ちた音
	SOUND_LABEL_SE_JUMP,		// ジャンプ音
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
