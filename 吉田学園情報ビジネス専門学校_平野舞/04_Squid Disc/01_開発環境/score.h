//-------------------------------------------
//
//スコア情報[score.h]
//Author:平野舞
//
//-------------------------------------------
#ifndef _SCORE_H_
#define _SCORE_H_

//インクルードファイル
#include "main.h"

//プロトタイプ宣言
void InitScore(void);						//初期化処理
void UninitScore(void);						//終了処理
void UpdateScore(void);						//更新処理
void DrawScore(void);						//描画処理
void SetScore(int nOrder,int nScore);		//設定処理
void AddScore(int order, int nValue);		//加算処理
int GetScore(int order);					//スコアの取得

#endif