#ifndef _BULLET_H_
#define _BULLET_H_

//インクルードファイル
#include "main.h"

//マクロ定義
#define MAX_BULLET			(128)		//弾の最大数
#define BULLET_WIDTH		(20.0f)		//弾の幅
#define BULLET_HEIGHT		(20.0f)		//弾の高さ
#define BULLET_ENEMY		(45.0f)		//敵の当たり判定
#define NUM_BULLET			(2)			//弾の種類

//弾の種類
typedef enum
{
	BULLETTYPE_PLAYER = 0,
	BULLETTYPE_ENEMY,
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
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,BULLETTYPE type);

#endif