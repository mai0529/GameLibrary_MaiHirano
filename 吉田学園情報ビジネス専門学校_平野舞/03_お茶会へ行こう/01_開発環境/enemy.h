//-------------------------------------------
//
//敵の情報[enemy.h]
//Author:平野舞
//
//-------------------------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_

//インクルードファイル
#include "main.h"

//マクロ定義
#define MAX_ENEMY		(128)		//敵の最大数
#define ENEMY_WIDTH		(60.0f)		//敵の幅
#define ENEMY_HEIGHT	(70.0f)		//敵の高さ

//敵の状態
typedef enum
{
	ENEMYSTATE_NORMAL = 0,		//通常状態
	ENEMYSTATE_DAMAGE,			//ダメージ状態
	ENEMYSTATE_MAX
}ENEMYSTATE;

//外部ファイル用敵構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	int nType;			//種類
}EnemyFile;

//敵構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	int nType;				//種類
	ENEMYSTATE state;		//状態
	int nCounterState;		//状態管理カウンター
	int nLife;				//体力
	bool bUse;				//使用しているかどうか
}Enemy;

//プロトタイプ宣言
void InitEnemy(void);							//初期化処理
void UninitEnemy(void);							//終了処理
void UpdateEnemy(void);							//更新処理
void DrawEnemy(void);							//描画処理
void SetEnemy(D3DXVECTOR3 pos, int nType);		//設定処理
void StateEnemy(int nCntEnemy);					//状態管理処理
void HitEnemy(int nCntEnemy, int nDamage);		//ヒット処理
void LoadEnemy(void);							//外部ファイルの読み込み処理
Enemy * GetEnemy(void);							//情報の取得

#endif