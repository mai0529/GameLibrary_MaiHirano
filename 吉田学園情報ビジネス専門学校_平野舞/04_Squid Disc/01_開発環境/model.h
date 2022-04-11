//----------------------------------------
//　モデル
//----------------------------------------
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

//マクロ定義
#define MAX_MODEL			(1)		//モデルの最大数
#define MODEL_SPEED			(1.0f)	//モデルの移動速度

//typedef enum
//{
//	PLAYER_P1 = 0,
//	PLAYER_P2
//}PLAYER_TYPE;

//モデルの構造体
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//向き
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	float diff;				//差分用
	float rotDestModel;		//目的の角度
	int IdxShadow;			//影用
	bool bUse;				//使っているかどうか
	PLAYER_TYPE type;
}Model;

//プロトタイプ宣言
void InitModel(void);		//モデルの初期化
void UninitModel(void);		//モデルの終了
void UpdateModel(void);		//モデルの更新
void DrawModel(void);		//モデルの描画
void MoveModel(void);		//モデルの移動
Model * GetModel(void);		//モデルの情報
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//モデルの設定

#endif
