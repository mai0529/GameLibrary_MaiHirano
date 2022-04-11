//=======================================================
//
//3Dアクションゲーム制作(input.h)
//Author:大原隆俊
//
//=======================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//===================================================================
//インクルードファイル
//===================================================================
#include "main.h"

//===================================================================
//キーの種類
//===================================================================
typedef enum
{
	JOYKEY_UP = 0,			//十字キー↑
	JOYKEY_DOWN,			//十字キー↓
	JOYKEY_LEFT,			//十字キー←
	JOYKEY_RIGHT,			//十字キー→
	JOYKEY_START,			//スタ-トボタン
	JOYKEY_BACK,			//BACKボタン
	JOYKEY_LPUSH,			//Lトリガー
	JOYKEY_RPUSH,			//Rトリガー
	JOYKEY_L1,				//L1
	JOYKEY_R1,				//R1
	JOYKEY_L2,				//L2
	JOYKEY_R2,				//R2
	JOYKEY_A,				//Aボタン
	JOYKEY_B,				//Bボタン
	JOYKEY_X,				//Xボタン
	JOYKEY_Y,				//Yボタン
	MAX_JOYKEY
}JOYkey;

//===================================================================
//プロトタイプ宣言
//===================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
HRESULT InitJoypad(void);
void UninitJoypad(void);
void UpdateJoypad(void);
bool GetJoypadPress(JOYkey key);
bool GetJoypadTrigger(JOYkey key);
#endif
