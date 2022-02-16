//-------------------------------------------------
//
//敵情報[enemy.h]
//Author:平野舞
//
//-------------------------------------------------

#ifndef _ENEMY_H_
#define _ENEMY_H_

//インクルードファイル
#include "main.h"
#include "score.h"
#include "block.h"
#include "player.h"
#include "explosion.h"

//マクロ定義
#define MAX_ENEMY			(128)		//敵の最大数
#define NUM_ENEMY			(3)			//敵の種類の最大数
#define ENEMY_WIDTH			(60.0f)		//敵の幅
#define ENEMY_HEIGHT		(70.0f)		//敵の高さ
#define ENEMY_G				(0.7f)		//敵の重力

//敵の状態
typedef enum
{
	ENEMYSTATE_NORMAL = 0,		//通常状態
	ENEMYSTATE_DAMAGE,			//ダメージ状態
	ENEMYSTATE_MAX
}ENEMYSTATE; 

//敵の種類
typedef enum
{
	ENEMY_GHOST = 0,			//おばけ	
	ENEMY_BONE,					//骸骨
	ENEMY_WOLF,					//狼
	ENEMY_MAX
}ENEMY;

//敵構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 PosOld;		//位置
	D3DXVECTOR3 move;		//移動量
	int nNumber;			//何番目か
	ENEMY nType;			//種類
	ENEMYSTATE state;		//状態
	int nCounterState;		//状態管理カウンター
	int nCounterAnim;		//テクスチャカウンター
	int nPatternAnim;		//テクスチャパターンNo.
	int nLife;				//体力
	bool bUse;				//使用しているかどうか
}Enemy;

//プロトタイプ宣言
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
//void StateEnemy(int nCntEnemy);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, ENEMY nType,int nLife, int nNumber);
void HitEnemy(int nCntEnemy, int nDamage);
Enemy * GetEnemy(void);
void CollisionEnemy(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld , D3DXVECTOR3 * pMove,float fWidth, float fHeigtht);
void MoveEnemy(int nCntEnemy);

#endif