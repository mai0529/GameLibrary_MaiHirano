//===================================
//
// 3D制作　エネミーモデル[enemy.h]
// AUTHOR:Sasaki Rikuto
//
//===================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
//===================================
//モデルの構造体の定義
//===================================
typedef struct
{
	D3DXVECTOR3 pos;					//位置					
	D3DXVECTOR3 move;				//移動量
	D3DXVECTOR3 scale;				//
	D3DXVECTOR3 rot;					//
	D3DXVECTOR3 rotDest;
	D3DXVECTOR3 posOld;				//前回の位置
									//D3DXVECTOR3 VtxMinenemy;				//最小値
									//D3DXVECTOR3 VtxMaxenemy;				//最大値
	D3DXVECTOR3 size;
	int nNumVtx;							//頂点数
	DWORD sizeFVF;							//頂点フォーマットのサイズ
	BYTE*pVtxBuff;							//頂点バッファのポインタ
	int nCounterState;						//状態管理カウンター
	int nLife;								//体力
	int nCounterAnim;						//カウンター
	int nPatternAnim;						//パターン番号
	int nDirectionMove;						//向き
	float fWidth;							//幅
	float fHeight;							//高さ
	bool bDisp;								//表示するかしないか
	bool bIsJumping;						//ジャンプ中
	bool bUse;
	int nType;								//タイプ
}Enemy;
//===================================
// プロトタイプ宣言
//===================================
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
bool CollisionEnemy(D3DXVECTOR3*pPos,//現在の位置
	D3DXVECTOR3*pPosOld,			//前回の高さ
	D3DXVECTOR3*pMove,				//移動量
	D3DXVECTOR3*pSize);				//サイズ
									//ブロックの設定処理
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXVECTOR3 move, int nType);
#endif

