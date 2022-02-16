//-------------------------------------------
//
//ゲーム処理[game.cpp](自動的にリザルトまだ)
//Author:平野舞
//
//-------------------------------------------
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

//-------------------------------------------
//初期化処理
//-------------------------------------------
void InitGame(void)
{
	//背景の初期化処理
	InitBG();

	//スコアの初期化処理
	InitScore();

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

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{//モード設定
		SetFade(MODE_RESULT);
	}
}

//-------------------------------------------
//描画処理
//-------------------------------------------
void DrawGame(void)
{
	//背景の描画処理
	DrawBG();

	//スコアの描画処理
	DrawScore();

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
}