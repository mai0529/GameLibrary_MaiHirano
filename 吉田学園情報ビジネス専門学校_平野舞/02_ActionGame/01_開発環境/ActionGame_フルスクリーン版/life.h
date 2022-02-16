//-------------------------------------------
//
//ライフ情報[life.h]
//Author:平野舞
//
//-------------------------------------------

#ifndef _LIFE_H_
#define _LIFE_H_

//インクルードファイル
#include "main.h"
#include "player.h"

//マクロ定義
#define MAX_LIFE			(6)			//ライフの最大数
#define LIFE_WIDTH			(50.0f)		//ライフの幅
#define LIFE_HEIGHT			(50.0f)		//ライフの高さ

//弾爆発の構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	bool bUse;				//使用しているかどうか
}Life;

//プロトタイプ宣言
void InitLife(void);
void UninitLife(void);
void UpdateLife(void);
void DrawLife(void);
void SetLife(D3DXVECTOR3 pos);
void AddLife(int nValue);
Life * GetMaxLife(void);
Life * GetLife(void);

#endif