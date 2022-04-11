//----------------------------------------
//　ディスク
//----------------------------------------
#ifndef _DISC_H_
#define _DISC_H_

#include "main.h"

//ディスクの状態
typedef enum
{
	STATUS_WAITING = 0,	//プレイヤーが持っている状態
	STATUS_MOVING		//投げられた状態
}DISC_STATUS;

//ディスクの投げ方の種類
typedef enum
{
	SHOT_NOMAL = 0,	//通常軌道(向いている方向に真っすぐ)
	SHOT_CURVE,		//カーブ軌道
	SHOT_UP			//上方向に落とします
}DISC_SHOT;

//ディスクの構造体
typedef struct
{
	D3DXVECTOR3 pos;		//現在の位置
	D3DXVECTOR3 posOld;		//前回の位置
	D3DXVECTOR3 rot;		//角度
	D3DXVECTOR3 move;		//移動量
	D3DXCOLOR col;			//カラー
	D3DXMATRIX mtxWorld;	//ワールドマトリクス
	bool bUse;				//使用しているかどうか
	float speed;			//移動スピード
	DISC_STATUS status;		//ディスクの状態
	float gravity;			//重力
	D3DXVECTOR3 vtxMin;		//モデルの最小値
	D3DXVECTOR3 vtxMax;		//モデルの最大値
	D3DXVECTOR3 size;		//サイズ
	int type;				//プレイヤーのどっちが持っているか
}Disc;

//プロトタイプ宣言
void InitDisc(void);		//ディスクの初期化処理
void UninitDisc(void);		//ディスクの終了処理
void UpdateDisc(void);		//ディスクの更新処理
void DrawDisc(void);		//ディスクの描画処理
void SetPosDisc(D3DXVECTOR3 pos, int type);		//ディスクの初期位置設定
void SetMoveDisc(D3DXVECTOR3 rot, float speed, DISC_SHOT shot, int type);	//ディスクの軌道設定
void CollisionDisc_Player(D3DXVECTOR3 *pos, D3DXVECTOR3 size, int type);	//ディスクとプレイヤーの当たり判定(キャッチの処理)
void SetPositionDisc(D3DXVECTOR3 pos, int type);	//プレイヤーがディスクを持てるようになる処理

#endif


