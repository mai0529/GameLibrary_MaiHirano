#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"

//マクロ定義
#define MAX_RANK	(5)		//ランク数

//プロトタイプ宣言
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
void ResetRanking(void);
void SetRanking(int nScore);

#endif