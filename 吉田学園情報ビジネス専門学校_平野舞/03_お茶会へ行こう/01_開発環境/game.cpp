//-------------------------------------------
//
//ゲーム処理[game.cpp]
//Author:平野舞
//
//-------------------------------------------

//インクルードファイル
#include "game.h"
#include "player.h"
#include "Bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "bg.h"
#include "input.h"
#include "score.h"
#include "sound.h"
#include "effect.h"
#include "fade.h"
#include "time.h"
#include "Sweet.h"
#include "life.h"
#include "obstacle.h"
#include "item.h"

//-------------------------------------------
//初期化処理
//-------------------------------------------
void InitGame(void)
{
	//背景の初期化処理
	InitBG();

	//スコアの初期化処理
	InitScore();

	//タイムの初期化処理
	InitTime();

	//ライフの初期化処理
	InitLife();

	//弾の初期化処理
	InitBullet();

	//エフェクトの初期化処理
	InitEffect();

	//プレイヤーの初期化処理
	InitPlayer();

	//爆発の初期化処理
	InitExplosion();

	//敵の初期化処理
	InitEnemy();

	//障害物の初期化処理
	InitObstacle();

	//お菓子の初期化処理
	InitSweet();

	//アイテムの初期化処理
	InitItem();
	
	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM000);
}

//-------------------------------------------
//終了処理
//-------------------------------------------
void UninitGame(void)
{
	//サウンドの停止
	StopSound();

	//背景の終了処理
	UninitBG();

	//スコアの終了処理
	UninitScore();

	//タイムの終了処理
	UninitTime();

	//弾の終了処理
	UninitBullet();

	//エフェクトの終了処理
	UninitEffect();

	//プレイヤーの終了処理
	UninitPlayer();

	//爆発の終了処理
	UninitExplosion();

	//敵の終了処理
	UninitEnemy();

	//障害物の終了処理
	UninitObstacle();

	//ライフの終了処理
	UninitLife();

	//お菓子の終了処理
	UninitSweet();

	//アイテムの終了処理
	UninitItem();
}

//-------------------------------------------
//更新処理
//-------------------------------------------
void UpdateGame(void)
{
	//背景の更新処理
	UpdateBG();

	//スコアの更新処理
	UpdateScore();

	//タイムの更新処理
	UpdateTime();

	//プレイヤーの更新処理
	UpdatePlayer();

	//弾の描画処理
	UpdateBullet();

	//エフェクトの更新処理
	UpdateEffect();

	//爆発の更新処理
	UpdateExplosion();

	//敵の更新処理
	UpdateEnemy();

	//障害物の更新処理
	UpdateObstacle();

	//アイテムの更新処理
	UpdateItem();

	//お菓子の更新処理
	UpdateSweet();

	//ライフの更新処理
	UpdateLife();
}

//-------------------------------------------
//描画処理
//-------------------------------------------
void DrawGame(void)
{
	//背景の描画処理
	DrawBG();

	//お菓子の描画処理
	DrawSweet();

	//ライフの描画処理
	DrawLife();

	//プレイヤーの描画処理
	DrawPlayer();

	//弾の描画処理
	DrawBullet();

	//エフェクトの描画処理
	DrawEffect();

	//爆発の描画処理
	DrawExplosion();

	//敵の描画処理
	DrawEnemy();

	//障害物の描画処理
	DrawObstacle();

	//アイテムの描画処理
	DrawItem();

	//スコアの描画処理
	DrawScore();

	//タイムの描画処理
	DrawTime();
}