//-------------------------------------------------
//
//炎情報[flame.h]
//Author:平野舞
//
//-------------------------------------------------

#ifndef _FLAME_H_
#define _FLAME_H_

//インクルードファイル
#include "main.h"
#include "item.h"
#include "score.h"

//マクロ定義
#define MAX_FLAME		(128)			//アイテムの最大数
#define FLAME_HEIGHT	(70.0f)			//高さ
#define FLAME_WIDTH		(70.0f)			//幅

//炎の構造体
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	int nNumber;			//何番目か
	bool bUse;				//使用するかしないか
}Flame;

//プロトタイプ宣言
void InitFlame(void);
void UninitFlame(void);
void UpdateFlame(void);
void DrawFlame(void);
void SetFlame(D3DXVECTOR3 pos, D3DXVECTOR3 move,int nNumber);
void CollisionFlame(D3DXVECTOR3 * pPos, float fWidth, float fHeigtht);
Flame *GetFlame(void);

#endif

