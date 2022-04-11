//-------------------------------------------------
//
//背景情報[bg.h]
//Author:平野舞
//
//-------------------------------------------------
#ifndef _BG_H_
#define _BG_H_

//インクルードファイル
#include "main.h"

//マクロ定義
#define BG_SPEED	(0.001f)		//背景の速度

//プロトタイプ宣言
void InitBG(void);
void UninitBG(void);
void UpdateBG(void);
void DrawBG(void);

#endif