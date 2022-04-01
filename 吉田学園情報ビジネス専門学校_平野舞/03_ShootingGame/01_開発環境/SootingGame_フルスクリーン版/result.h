//-------------------------------------------
//
//リザルト情報[result.h]
//Author:平野舞
//
//-------------------------------------------

#ifndef _RESULT_H_
#define _RESULT_H_

//インクルードファイル
#include "main.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "score.h"
#include "item.h"

//マクロ定義
#define RESULT_WIDTH	(40.0f)		//リザルトの幅
#define RESULT_HEIGHT	(85.0f)		//リザルトの高さ
#define RESULT_MAX		(2)			//リザルトの最大画像
#define MAX_RESULTX		(8)			//Xの最大数

//リザルト構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	int nScore;			//スコア
	int nData;			//数
}Result;

//プロトタイプ宣言
void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);
void ResetResult(void);
void SetResult(void);

#endif