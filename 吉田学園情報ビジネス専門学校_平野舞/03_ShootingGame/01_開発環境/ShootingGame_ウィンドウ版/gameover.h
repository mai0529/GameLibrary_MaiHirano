//-------------------------------------------------
//
//ゲームオーバー情報[gameover.h]
//Author:平野舞
//
//-------------------------------------------------
#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

//インクルードファイル
#include "main.h"

//マクロ定義
#define MAX_GAMEOVER	(2)		//背景画像の最大数

//プロトタイプ宣言
void InitGameover(void);
void UninitGameover(void);
void UpdateGameover(void);
void DrawGameover(void);

#endif