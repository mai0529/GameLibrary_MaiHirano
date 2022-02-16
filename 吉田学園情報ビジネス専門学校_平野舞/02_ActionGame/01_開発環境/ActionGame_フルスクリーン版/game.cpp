//-------------------------------------------
//
//ゲーム処理[game.cpp]
//Author:平野舞
//
//-------------------------------------------

//インクルードファイル
#include "game.h"

//-------------------------------------------
//初期化処理
//-------------------------------------------
void InitGame(void)
{
	//背景の初期化処理
	InitBG();

	//ゴールの初期化処理
	InitGoal();

	//ライフの初期化処理
	InitLife();

	//タイマーの初期化処理
	InitTime();

	//スコアの初期化処理
	InitScore();

	//ブロックの初期化処理
	InitBlock();

	//炎の初期化処理
	InitFlame();

	//プレイヤーの初期化処理
	InitPlayer();

	//弾の初期化処理
	InitBullet();

	//爆発処理の初期化処理
	InitExplosion();

	//アイテムの初期化処理
	InitItem();

	//敵の初期化処理
	InitEnemy();
	
	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM001);
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

	//ゴールの終了処理
	UninitGoal();

	//ライフの終了処理
	UninitLife();

	//タイマーの終了処理
	UninitTime();

	//スコアの終了処理
	UninitScore();

	//ブロックの終了処理
	UninitBlock();

	//炎の終了処理
	UninitFlame();

	//プレイヤーの終了処理
	UninitPlayer();

	//弾の終了処理
	UninitBullet();

	//爆発の終了処理
	UninitExplosion();

	//アイテムの終了処理
	UninitItem();

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

	//ゴールの更新処理
	UpdateGoal();

	//ライフの更新処理
	UpdateLife();

	//タイマーの更新処理
	UpdateTime();

	//スコアの更新処理
	UpdateScore();

	//ブロックの更新処理
	UpdateBlock();

	//炎の更新処理
	UpdateFlame();

	//プレイヤーの更新処理
	UpdatePlayer();

	//弾の更新処理
	UpdateBullet();

	//爆発の更新処理
	UpdateExplosion();

	//アイテムの更新処理
	UpdateItem();

	//敵の更新処理
	UpdateEnemy();

	//if (GetKeyboardTrigger(DIK_RETURN) == true)
	//{//モード設定
	//	SetFade(MODE_GAMECLEAR);
	//}
}

//-------------------------------------------
//描画処理
//-------------------------------------------
void DrawGame(void)
{
	//背景の描画処理
	DrawBG();

	//ゴールの描画処理
	DrawGoal();

	//ライフの描画処理
	DrawLife();

	//タイマーの描画処理
	DrawTime();

	//スコアの描画処理
	DrawScore();

	//ブロックの描画処理
	DrawBlock();

	//炎の描画処理
	DrawFlame();

	//プレイヤーの描画処理
	DrawPlayer();

	//弾の描画処理
	DrawBullet();

	//爆発の描画処理
	DrawExplosion();

	//アイテムの描画処理
	DrawItem();

	//敵の描画処理
	DrawEnemy();
}