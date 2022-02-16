//-------------------------------------------
//
//ランキング情報[ranking.h]
//Author:平野舞
//
//-------------------------------------------

#ifndef _RANKING_H_
#define _RANKING_H_

//インクルードファイル
#include "main.h"

//マクロ定義
#define MAX_RANKY				(5)			//Yの数
#define MAX_RANKX				(3)			//Xの数
#define RANKING_WIDTH			(50)		//順位の幅
#define RANKING_HEIGHT			(100)		//順位の高さ
#define MAX_TEX					(2)			//画像の枚数

//ランキング構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	int nTime;			//時間
}Rank;

//プロトタイプ宣言
void InitRanking(void);		//初期化処理
void UninitRanking(void);	//終了処理
void UpdateRanking(void);	//更新処理
void DrawRanking(void);		//描画処理
void ResetRanking(void);	//ランキングのリセット処理
void SetRanking(void);		//設定処理

#endif