//-------------------------------------------
//
//弾の情報[Bullet.h]
//Author:平野舞
//
//-------------------------------------------
#ifndef _BULLET_H_
#define _BULLET_H_

//インクルードファイル
#include "main.h"

//弾の種類
typedef enum
{
	BULLETTYPE_PLAYER = 0,		//プレイヤーの弾
	BULLETTYPE_ENEMY,			//敵の弾
	BULLETTYPE_MAX
}BULLETTYPE;

//弾の構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	int nLife;				//寿命
	BULLETTYPE type;		//弾の種類
	bool bUse;				//使用しているかどうか
}Bullet;

//プロトタイプ宣言
void InitBullet(void);		//初期化処理
void UninitBullet(void);	//終了処理
void UpdateBullet(void);	//更新処理
void DrawBullet(void);		//描画処理
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,int nLife,BULLETTYPE type);		//設定処理

#endif