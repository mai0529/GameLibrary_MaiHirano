//-------------------------------------------------
//
//キラキラ情報[twinkle.h]
//Author:平野舞
//
//-------------------------------------------------

#ifndef _TWINKLE_H_
#define _TWINKLE_H_

//インクルードファイル
#include "main.h"
#include "item.h"
#include "score.h"

//マクロ定義
#define MAX_TWINKLE		(128)			//アイテムの最大数
#define TWINKLE_HEIGHT	(70.0f)			//高さ
#define TWINKLE_WIDTH		(70.0f)			//幅

//キラキラの構造体
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	int nNumber;			//何番目か
	bool bUse;				//使用するかしないか
}Twinkle;

//プロトタイプ宣言
void InitTwinkle(void);
void UninitTwinkle(void);
void UpdateTwinkle(void);
void DrawTwinkle(void);
void SetTwinkle(D3DXVECTOR3 pos, D3DXVECTOR3 move,int nNumber);
void CollisionTwinkle(D3DXVECTOR3 * pPos, float fWidth, float fHeigtht);
Twinkle *GetTwinkle(void);

#endif

