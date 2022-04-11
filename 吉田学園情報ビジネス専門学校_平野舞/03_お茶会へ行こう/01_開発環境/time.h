#ifndef _TIME_H_
#define _TIME_H_

//インクルードファイル
#include "main.h"

//マクロ定義
#define TIME_WIDTH		(40.0f)		//スコアの幅
#define TIME_HEIGHT		(60.0f)		//スコアの高さ
#define TIME_MAX		(3)			//スコアの最大桁数

//プロトタイプ宣言
void InitTime(void);
void UninitTime(void);
void UpdateTime(void);
void DrawTime(void);
int GetTime(void);

#endif
