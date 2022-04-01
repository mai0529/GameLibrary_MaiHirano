//-------------------------------------------------
//
//お菓子情報[Sweet.h]
//Author:平野舞
//
//-------------------------------------------------
#ifndef _SWEET_H_
#define _SWEET_H_

//インクルードファイル
#include "main.h"

//マクロ定義
#define MAX_SWEET		(5)				//アイテムの最大数
#define SWEET_HEIGHT	(120.0f)		//高さ
#define SWEET_WIDTH		(170.0f)		//幅

//アイテムの構造体
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	bool bUse;				//使用するかしないか
}Sweet;

//プロトタイプ宣言
void InitSweet(void);
void UninitSweet(void);
void UpdateSweet(void);
void DrawSweet(void);
void SetSweet(D3DXVECTOR3 pos);
Sweet * GetSweet(void);
void CollisionSweet(D3DXVECTOR3 * pPos, float fWidth, float fHeigtht);

#endif