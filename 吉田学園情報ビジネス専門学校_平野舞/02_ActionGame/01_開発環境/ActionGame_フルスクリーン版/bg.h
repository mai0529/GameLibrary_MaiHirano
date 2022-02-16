//-------------------------------------------------
//
//背景情報[bg.h]
//Author:平野舞
//
//-------------------------------------------------
#ifndef _BG_H_
#define _BG_H_

#include "main.h"

//マクロ定義
#define NUM_BG		(3)				//背景の数
#define BG_HEIGHT	(100.0f)		//高さ

typedef struct
{
	D3DXVECTOR3 pos;		//位置
	float fTexU;
	float fTexV;
}BG;

//プロトタイプ宣言
void InitBG(void);
void UninitBG(void);
void UpdateBG(void);
void DrawBG(void);
BG *GetBG(void);

#endif