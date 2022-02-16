#ifndef _PLAYER_H_
#define _PLAYER_H_

//プレイヤーの状態
typedef enum
{
	PLAYERSTATE_APPEAR = 0,		//出現状態(点滅)
	PLAYERSTATE_NORMAL,			//通常状態
	PLAYERSTATE_DAMAGE,			//ダメージ状態
	PLAYERSTATE_DEATH,			//死亡状態
	PLAYERSTATE_MAX				
}PLAYERSTATE;

//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void HitPlayer(int nDamage);
void * GetPlayer(void);
void Gamengai(void);

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

#endif