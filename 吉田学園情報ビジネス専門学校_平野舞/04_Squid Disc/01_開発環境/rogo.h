//============================================================
//
// 3D制作　勝敗ロゴの処理[rogo.h]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#ifndef _ROGO_H_
#define _ROGO_H_

#include "main.h"

//マクロ定義
#define MAX_Rogo			(128)		//敵の最大数
#define NUM_Rogo			(10)		//敵の種類
#define Rogo_SIZE			(300.0f)	//敵のサイズ

//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;								//位置
	int nType;										//種類
	bool bUse;										//使用しているかどうか
}Rogo;


//プロトタイプ宣言
void lnitRogo(void);
void UninitRogo(void);
void UpdateRogo(void);
void DrawRogo(void);
void SetRogo(D3DXVECTOR3 pos, int nType);

Rogo*GetRogo(void);

#endif 


