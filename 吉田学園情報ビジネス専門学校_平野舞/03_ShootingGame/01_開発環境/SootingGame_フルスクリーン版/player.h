//-------------------------------------------------
//
//プレイヤー情報[player.h]
//Author:平野舞
//
//-------------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

//インクルードファイル
#include "main.h"
#include "fade.h"
#include "input.h"
#include "block.h"
#include "enemy.h"
#include "Bullet.h"
#include "score.h"
#include "item.h"
#include "goal.h"
#include "life.h"
#include "bg.h"
#include "twinkle.h"
#include "sound.h"

//マクロ定義
#define PLAYER_WIDTH			(60.0f)			//プレイヤーの幅
#define PLAYER_HEIGHT			(80.0f)			//プレイヤーの高さ
#define PLAYER_DIS				(2.5f)			//移動距離
#define PLAYER_JUMP				(15.0f)			//ジャンプの高さ
#define PLAYER_G				(0.65f)			//重力
#define PLAYER_GROUND			(660)			//地面の高さ
#define PLAYERTEX_U				(4)				//U方向のパターン数
#define PLAYERTEX_V				(2)				//V方向のパターン数
#define PLAYER_MOVE				(1.0f)			//移動しているかどうかの判定数

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
	D3DXVECTOR3 posOld;		//前回の位置
	D3DXVECTOR3 move;		//移動量
	int nCounterAnim;		//カウンター
	int nPatternAnim;		//パターン番号
	int nDirectionMove;		//向き
	bool bIsJumping;		//ジャンプ中かどうか
	PLAYERSTATE state;		//プレイヤーの状態
	int nCounterState;		//状態管理カウンター
	int nLife;				//体力
	bool bDisp;				//表示するかしないか
}Player;

//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void StatePlayer(void);
void HitPlayer(int nDamage);
Player * GetPlayer(void);
void OffScreen(void);
void MovePlayer(void);
void Scroll(void);
void Jumping(void);

#endif