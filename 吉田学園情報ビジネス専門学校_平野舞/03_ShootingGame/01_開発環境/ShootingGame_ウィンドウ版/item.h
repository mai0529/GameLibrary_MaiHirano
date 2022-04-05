//-------------------------------------------
//
//アイテム情報[item.h]
//Author:平野舞
//
//-------------------------------------------
#ifndef _ITEM_H_
#define _ITEM_H_

//インクルードファイル
#include "main.h"

//アイテムの構造体
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	bool bUse;				//使用するかしないか
}Item;

//プロトタイプ宣言
void InitItem(void);		//初期化処理
void UninitItem(void);		//終了処理
void UpdateItem(void);		//更新処理
void DrawItem(void);		//描画処理
void SetItem(D3DXVECTOR3 pos);			//設定処理
void CollisionItem(D3DXVECTOR3 * pPos, float fWidth, float fHeigtht);	//当たり判定
int GetScoreUpItem(void);				//スコアアップアイテムの取得

#endif