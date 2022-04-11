//----------------------------------------
//　ゴール
//----------------------------------------
#ifndef _GOAL_H_
#define _GOAL_H_

#include "main.h"

//ゴールの構造体
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//方向
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	float fWidth;			//幅
	float fHeight;			//高さ
}Goal;

void InitGoal(float X, float Z);	//ゴールの初期化処理	引数(横幅の半径, 縦幅の半径)
void UninitGoal(void);		//ゴールの終了処理
void UpdateGoal(void);		//ゴールの更新処理
void DrawGoal(void);		//ゴールの描画処理
void CollisionGoal(D3DXVECTOR3 pos, bool *bUse, int type);	//ゴールの当たり判定

#endif