//-------------------------------------------
//
//プレイヤー情報[player.h]
//Author:平野舞
//
//-------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

//インクルードファイル
#include "main.h"

//マクロ定義
#define PLAYER_WIDTH		(80.0f)		//プレイヤーの幅
#define PLAYER_HEIGHT		(80.0f)		//プレイヤーの高さ
#define PLAYER_DIS			(4.0f)		//移動距離
#define PLAYER_ENEMY		(80.0f)		//当たり判定

//プレイヤーの状態
typedef enum
{
	PLAYERSTATE_APPEAR = 0,		//出現状態(点滅)
	PLAYERSTATE_NORMAL,			//通常状態
	PLAYERSTATE_DAMAGE,			//ダメージ状態
	PLAYERSTATE_DEATH,			//死亡状態
	PLAYERSTATE_MAX				
}PLAYERSTATE;

//プレイヤー構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	PLAYERSTATE state;		//プレイヤーの状態
	int nCounterState;		//状態管理カウンター
	int nLife;				//体力
	bool bDisp;				//表示するかしないか
}Player;

//プロトタイプ宣言
void InitPlayer(void);				//初期化処理
void UninitPlayer(void);			//終了処理
void UpdatePlayer(void);			//更新処理
void DrawPlayer(void);				//描画処理
void StatePlayer(void);				//プレイヤーの状態管理
void FlashPlayer(void);				//プレイヤーの点滅処理
void HitPlayer(int nDamage);		//プレイヤーのヒット処理
void MovePlayer(void);				//プレイヤーの移動処理
void Gamengai(void);				//画面外処理
Player * GetPlayer(void);			//プレイヤー情報の取得処理

#endif