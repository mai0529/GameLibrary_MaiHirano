//============================================================
//
//ゲームの処理(game.cpp)
//AUTHOR:佐々木陸斗
//
//=============================================================
#include "main.h"
#include "input.h"
#include"TITLE.h"
#include"game.h"
#include"sound.h"
#include"Time.h"
#include"meshfield.h"
#include"shadow.h"
#include"player.h"
#include"wall.h"
#include"camera.h"
#include"light.h"
#include"score.h"
#include"time.h"
#include"disc.h"
#include"vec.h"
#include"model.h"
#include"Field.h"
#include"ink.h"
#include "mob.h"
#include"enemy.h"
#include "goal.h"

//==============================================================
//ゲームの初期化処理
//==============================================================
void lnitGAME(void)
{
	
	//メッシュフィールドの初期化設定
	//InitMeshfield();

	//	ゴール初期化処理
	InitGoal(350.0f, 600.0f);

	//影の初期化設定
	InitShadow();
	
	//インクの初期化処理
	lnitInk();

	//ディスクの初期化
	InitDisc();

	//プレイヤーの初期化設定
	InitPlayer();

	//2人目のプレイヤーの初期化設定
	InitMob();

	//モデルの初期化設定
	//InitModel();

	//エネミーの初期化設定
	InitEnemy();

    //モデルの初期化処理
	InitField();

	//カメラの初期化設定
	InitCamera();

	//ライトの初期化設定
	InitLight();

	//タイマー初期化処理
	InitTime();

	//スコア初期化処理
	InitScore();

	//サウンドの再生
	PlaySound(SOUND_LABEL_GAME);
	
}
//==============================================================
//ゲームの終了処理
//==============================================================
void UninitGAME(void)
{
	//サウンドの停止
	StopSound();
	
	//カメラの終了設定
	UninitCamera();

	//メッシュフィールドの終了設定
	//UninitMeshfield();

	//ディスクの終了処理
	UninitDisc();

	//プレイヤーの終了処理
	UninitPlayer();

	//2人目のプレイヤーの終了設定
	UninitMob();

	//モデルの終了設定
	//UninitModel();

	//エネミーの終了処理
	UninitEnemy();

	//モデルの終了設定
	UninitField();

	//影の終了処理
	UninitShadow();

	//インクの終了処理
	UninitInk();

	//ゴールの終了処理
	UninitGoal();

	//ライトの終了設定
	UninitLight();

	//タイマー終了処理
	UninitTime();

	//スコア終了処理
	//UninitScore();
}

//==============================================================
//ゲームの描画処理
//==============================================================
void DrawGAME(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//ビューポート
	D3DVIEWPORT9 viewport;

	pDevice->GetViewport(&viewport);
	
	Camera * pCamera = GetCamera();

	for (int nCnt = 0; nCnt < 2; nCnt++,pCamera++)
	{
		pDevice->SetViewport(&pCamera->viewport);

		//画面のクリア
		pDevice->Clear(0,
			NULL,
			(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
			D3DCOLOR_RGBA(0, 0, 0, 0),
			1.0f,
			0);

		SetCamera(nCnt);
		

		//ディスクの描画処理
		DrawDisc();

		//モデルの描画処理
		//DrawModel();

		//エネミーの描画処理
		DrawEnemy();

		//モデルの描画処理
		DrawField();

		//ゴール描画処理
		DrawGoal();

		//影の描画処理
		DrawShadow();

		//インクの描画処理
		DrawInk();

		//プレイヤーの描画処理
		DrawPlayer();

		//2人目のプレイヤーの描画設定
		DrawMob();

		//タイマー描画処理
		DrawTime();

		//スコア描画処理
		DrawScore();
	}
		pDevice->SetViewport(&viewport);
}

//==============================================================
//ゲームの更新処理
//==============================================================
void UpdateGAME(void)
{
	
	//メッシュフィールドの更新設定
	//UpdateMeshfield();

	//ゴール更新処理
	UpdateGoal();

	//影の更新設定
	UpdateShadow();

	//インクの更新処理
	UpdateInk();

	//ディスクの更新処理
	UpdateDisc();

	//プレイヤー更新処理
	UpdatePlayer();

	//2人目のプレイヤーの更新設定
	UpdateMob();

	//モデルの更新設定
	//UpdateModel();

	//エネミーの更新処理
	UpdateEnemy();

	//モデルの更新設定
	UpdateField();

	//カメラの更新設定
	UpdateCamera();

	//壁の更新設定
	//UpdateWall();

	//ライトの更新設定
	UpdateLight();

	//タイマー更新処理
	UpdateTime();

	//スコア更新処理
	UpdateScore();

	

	//決定キー(ENTERキーが押されたかどうか)
	if (GetKeyboardTrigger(DIK_P) == true)
	{
		//モード設定
 		SetMode(MODE_END);

	}
}