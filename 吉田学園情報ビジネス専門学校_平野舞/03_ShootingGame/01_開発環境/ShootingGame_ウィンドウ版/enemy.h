#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//マクロ定義
#define MAX_ENEMY		(128)		//敵の最大数

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
	ENEMY_HEART = 0,		
	ENEMY_CLOVER,	
	ENEMY_SPADE,
	ENEMY_DIA,
	ENEMY_BLACKDIA,
	ENEMY_BLACKSPADE,
	ENEMY_MAX
}ENEMY;

//敵構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	ENEMY nType;			//種類
	ENEMYSTATE state;		//状態
	int nCounterState;		//状態管理カウンター
	int nLife;				//体力
	bool bUse;				//使用しているかどうか
}Enemy;

//プロトタイプ宣言
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, ENEMY nType,int nLife);
void HitEnemy(int nCntEnemy, int nDamage);
Enemy * GetEnemy(void);

#endif