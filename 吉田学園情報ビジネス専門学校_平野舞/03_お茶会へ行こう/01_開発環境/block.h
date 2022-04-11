//-------------------------------------------------
//
//ブロック情報[block.h]
//Author:平野舞
//
//-------------------------------------------------
#ifndef _BLOCK_H_
#define _BLOCK_H_

//インクルードファイル
#include "main.h"
#include "item.h"
#include "input.h"
#include "enemy.h"
#include "sound.h"

//マクロ定義
#define BLOCK_NUM			(3)			//ブロックの最大種類
#define MAX_BLOCK			(128)		//ブロックの最大数
#define BLOCK_WIDTH			(40.0f)		//ブロックの幅
#define BLOCK_HEIGHT		(40.0f)		//ブロックの高さ

typedef enum
{
	BLOCKSTATE_NORMAL = 0,		//通常状態
	BLOCKSTATE_DAMAGE,			//ダメージ状態
	BLOCKSTATE_MAX
}BLOCKSTATE;

//ブロックの種類
typedef enum
{
	BLOCK_BRICK = 0,
	BLOCK_CONCRETE,
	BLOCK_QUESTION,
	BLOCK_MAX
}Block;

//テキストファイル読み込み構造体
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	float fWidth;			//幅
	float fHeigth;			//高さ
	int nType;			//種類
	int nItem;				//アイテムの種類
}BlockFile;

//ブロック構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	int nType;			//種類
	int nItem;				//アイテムの種類
	int nLife;				//寿命
	float fWidth;			//幅
	float fHeigth;			//高さ
	BLOCKSTATE state;		//状態
	int nCounterState;		//状態管理
	bool bUse;				//使用しているかどうか
}BLOCK;

//プロトタイプ宣言
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeigtht, int nType,int nNumber);
bool CollisionBlock(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove, float fWidth, float fHeigtht);
void QuestionBlock(int nCntBlock);
void HitBlock(int nCntBlock);
void LoadBlock(void);
BLOCK * GetBlock(void);

#endif