//-------------------------------------------
//
//弾の爆発情報[explosion.h]
//Author:平野舞
//
//-------------------------------------------

#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//インクルードファイル
#include "main.h"

//マクロ定義
#define MAX_EXPLOSION			(128)		//弾の最大数
#define EXPLOSION_WIDTH			(40.0f)		//弾の幅
#define EXPLOSION_HEIGHT		(40.0f)		//弾の高さ
#define EXPLOSION_CNTANIM		(3)			//アニメーション速度

//弾爆発の構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXCOLOR col;			//色
	int nCounterAnim;		//アニメーションカウンター
	int nPatternAnim;		//アニメーションパターンNo.
	bool bUse;				//使用しているかどうか
}Explosion;

//プロトタイプ宣言
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col);

#endif