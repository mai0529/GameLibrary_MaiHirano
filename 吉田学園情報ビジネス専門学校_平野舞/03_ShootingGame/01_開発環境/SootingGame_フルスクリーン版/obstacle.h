//-------------------------------------------
//
//障害物情報[obstacle.h]
//Author:平野舞
//
//-------------------------------------------
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

//インクルードファイル
#include "main.h"

//マクロ定義
#define MAX_OBSTACLE	(16)			//障害物の最大数
#define OBSTACLE_WIDTH	(100.0f)		//幅
#define OBSTACLE_HEIGHT	(150.0f)		//高さ

//障害物の構造体
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	bool bUse;				//使用するかどうか
}Obstacle;

//プロトタイプ宣言
void InitObstacle(void);			//初期化処理
void UninitObstacle(void);			//終了処理
void UpdateObstacle(void);			//更新処理
void DrawObstacle(void);			//描画処理
void SetObstacle(D3DXVECTOR3 pos);	//設定処理
Obstacle * GetObstacle(void);		//取得処理

void CollisionObstacle(D3DXVECTOR3 * pPos, float fWidth, float fHeigtht);		//当たり判定

#endif
