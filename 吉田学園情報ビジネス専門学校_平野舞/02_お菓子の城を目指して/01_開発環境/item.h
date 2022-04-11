//-------------------------------------------------
//
//アイテム情報[item.h]
//Author:平野舞
//
//-------------------------------------------------
#ifndef _ITEM_H_
#define _ITEM_H_

//インクルードファイル
#include "main.h"
#include "block.h"
#include "score.h"
#include "player.h"
#include "explosion.h"
#include "life.h"
#include "sound.h"

//マクロ定義
#define NUM_ITEM		(3)				//アイテムの数
#define MAX_ITEM		(128)			//アイテムの最大数
#define ITEM_HEIGHT		(30.0f)			//高さ
#define ITEM_WIDTH		(50.0f)			//幅
#define ITEM_G			(0.7f)			//アイテムの重力

//アイテムの種類
typedef enum
{
	ITEM_CANDY = 0,			//飴
	ITEM_POTION,			//回復薬
	ITEM_CAKE,				//ケーキ
	ITEM_MAX
}ITEM;

//アイテムの構造体
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 PosOld;		//位置
	D3DXVECTOR3 move;		//移動量
	float fWidth;			//幅
	float fHeigth;			//高さ
	ITEM nType;				//種類
	bool bUse;				//使用するかしないか
}Item;

//プロトタイプ宣言
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos, ITEM nType);
Item * GetItem(void);
void CollisionItem(D3DXVECTOR3 * pPos, float fWidth, float fHeigtht);
void DeleteItem(int nCntItem);
int GetnCount(void);

#endif