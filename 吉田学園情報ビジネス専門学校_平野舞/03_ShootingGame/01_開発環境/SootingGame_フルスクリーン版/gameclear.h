//-------------------------------------------------
//
//ゲームクリア情報[gameclear.h]
//Author:平野舞
//
//-------------------------------------------------
#ifndef _GAMECLEAR_H_
#define _GAMECLEAR_H_

//インクルードファイル
#include "main.h"

//マクロ定義
#define MAX_GAMECLEAR	(2)		//背景画像の最大数

//プロトタイプ宣言
void InitGameclear(void);
void UninitGameclear(void);
void UpdateGameclear(void);
void DrawGameclear(void);

#endif