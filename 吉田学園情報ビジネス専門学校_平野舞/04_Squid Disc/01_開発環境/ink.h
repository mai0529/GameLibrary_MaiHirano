//============================================================
//
// 3D制作　インクの処理[Ink.h]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#ifndef _INK_H_
#define _INK_H_

#include "main.h"

//============================================================
// インクの構造体の定義
//============================================================
typedef struct
{
	D3DXVECTOR3 pos;				//視点					
	D3DXVECTOR3 rot;				//注視点
	D3DXVECTOR3 size;				//サイズ
	D3DXVECTOR3 move;				//サイズ
	D3DXMATRIX mtxWorld;			//
	bool bUse;						//
}Ink;

//============================================================
// プロトタイプ宣言
//============================================================
void lnitInk(void);
void UninitInk(void);
void UpdateInk(void);
void DrawInk(void);
int SetInk(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetPositionInk(int nIdxInk, D3DXVECTOR3 pos);
bool CollisionInk(
	D3DXVECTOR3* pPos,				//現在の位置
	D3DXVECTOR3* pPosOld,			//前回の高さ
	D3DXVECTOR3* pMove,				//移動量
	D3DXVECTOR3* pSize);			//サイズ

#endif

