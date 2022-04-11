//-------------------------------------------------
//
//ゴール情報[goal.h]
//Author:平野舞
//
//-------------------------------------------------
#ifndef _GOAL_H_
#define _GOAL_H_

//インクルードファイル
#include "main.h"
#include "score.h"
#include "time.h"
#include "sound.h"

//マクロ定義
#define GOAL_HEIGHT		(300.0f)			//高さ
#define GOAL_WIDTH		(200.0f)			//幅

typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	float fWidth;			//幅
	float fHeigth;			//高さ
	bool bUse;				//使用するかしないか
}Goal;

//プロトタイプ宣言
void InitGoal(void);
void UninitGoal(void);
void UpdateGoal(void);
void DrawGoal(void);
void CollisionGoal(D3DXVECTOR3 * pPos, float fWidth, float fHeigtht);
Goal * GetGoal(void);

#endif
