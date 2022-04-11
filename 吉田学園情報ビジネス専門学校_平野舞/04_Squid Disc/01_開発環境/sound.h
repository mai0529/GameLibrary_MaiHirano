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
	//BGM
	SOUND_LABEL_A = 0,			// BGM0
	SOUND_LABEL_GAME,			// BGM:ゲーム用サウンド
	SOUND_LABEL_TITLE,			// BGM:操作説明用サウンド
	//SE
	SOUND_LABEL_SE_Catch,		//キャッチ
	SOUND_LABEL_SE_Count,		//カウントダウン
	SOUND_LABEL_SE_END,			//ゲーム終了
	SOUND_LABEL_SE_Score,		//点数
	SOUND_LABEL_SE_Throw,		//投げる
	SOUND_LABEL_SE_VS,			//
	SOUND_LABEL_SE_Frame,		//フレームの選択音
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
