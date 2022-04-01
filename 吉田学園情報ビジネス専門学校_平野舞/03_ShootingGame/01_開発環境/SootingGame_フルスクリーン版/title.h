//-------------------------------------------------
//
//タイトル情報[title.h]
//Author:平野舞
//
//-------------------------------------------------
#ifndef _TITLE_H_
#define _TITLE_H_

//インクルードファイル
#include "main.h"

//マクロ定義
#define MAX_TITLE		(2)				//背景画像の最大数
#define ENTER_WIDTH		(500.0f)		//幅
#define ENTER_HEIGHT	(100.0f)		//高さ

//プロトタイプ宣言
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif