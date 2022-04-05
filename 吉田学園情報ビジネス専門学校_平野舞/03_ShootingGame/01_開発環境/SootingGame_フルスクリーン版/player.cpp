//-------------------------------------------
//
//プレイヤー処理[player.cpp]
//Author:平野舞
//
//-------------------------------------------

//インクルードファイル
#include "player.h"
#include "life.h"
#include "obstacle.h"
#include "input.h"
#include "Bullet.h"
#include "sound.h"
#include "explosion.h"
#include "enemy.h"
#include "fade.h"
#include "item.h"
#include "controller.h"

//グローバル宣言
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;			//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//頂点バッファへのポインタ
Player g_player;									//プレイヤーの情報
bool g_PlayerFade;									//フェードしているかどうか

//-------------------------------------------
//プレイヤーの初期化処理
//-------------------------------------------
void InitPlayer(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/player000.png",
		&g_pTexturePlayer);

	g_player.pos = D3DXVECTOR3(200.0f,200.0f, 0.0f);	//位置の初期化
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量の初期化
	g_player.bDisp = true;								//出現状態の初期化
	g_player.nLife = 5;									//プレイヤーライフの初期化
	g_player.state = PLAYERSTATE_APPEAR;				//プレイヤー状態の初期化
	g_player.nCounterState = 60;						//プレイヤー出現カウンターの初期化
	g_PlayerFade = false;								//フェードしていない

	//頂点バッファの生成
	pDevice -> CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer-> Lock(0, 0, (void**) &pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - (PLAYER_WIDTH / 2.0f), g_player.pos.y - (PLAYER_HEIGHT / 2.0f), g_player.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + (PLAYER_WIDTH / 2.0f), g_player.pos.y - (PLAYER_HEIGHT / 2.0f), g_player.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - (PLAYER_WIDTH / 2.0f), g_player.pos.y + (PLAYER_HEIGHT / 2.0f), g_player.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + (PLAYER_WIDTH / 2.0f), g_player.pos.y + (PLAYER_HEIGHT / 2.0f), g_player.pos.z);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();

	SetLife(D3DXVECTOR3(g_player.pos.x, g_player.pos.y - 85.0f, g_player.pos.z), 5, 5);
}

//-------------------------------------------
//プレイヤーの終了処理
//-------------------------------------------
void UninitPlayer(void)
{
	//テクスチャの破棄
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//-------------------------------------------
//プレイヤーの更新処理
//-------------------------------------------
void UpdatePlayer(void)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//プレイヤーの状態
	StatePlayer();

	//プレイヤーの移動処理
	MovePlayer();

	//弾の発射
	if (GetKeyboardTrigger(DIK_SPACE) == true || GetControllerPressTrigger(0, XINPUT_GAMEPAD_A))
	{//SPACEキーが押された   
	 //弾の設定
		SetBullet(g_player.pos, D3DXVECTOR3(10.0f, 0.0f, 0.0f), 100,BULLETTYPE_PLAYER);
		//サウンドの再生
		PlaySound(SOUND_LABEL_SE_SHOT);
	}

	//位置を更新
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;

	//移動量を更新(減衰させる)
	g_player.move.x += (0.0f - g_player.move.x) * 0.08f;
	g_player.move.y += (0.0f - g_player.move.y) * 0.08f;

	//敵情報の取得
	Enemy *pEnemy = GetEnemy();

	//敵とプレイヤーの当たり判定
	if (g_player.bDisp == true && g_player.state == PLAYERSTATE_NORMAL)
	{
		for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
		{
			if (pEnemy->bUse == true)
			{//敵が使用されている
				if (g_player.pos.x + (PLAYER_WIDTH / 2.0f) >= pEnemy->pos.x - ENEMY_WIDTH
					&& g_player.pos.x - (PLAYER_WIDTH / 2.0f) <= pEnemy->pos.x + ENEMY_WIDTH
					&& g_player.pos.y + (PLAYER_HEIGHT / 2.0f) >= pEnemy->pos.y - ENEMY_HEIGHT
					&& g_player.pos.y - (PLAYER_HEIGHT / 2.0f) <= pEnemy->pos.y + ENEMY_HEIGHT)
				{ //敵の当たり判定
					HitPlayer(1);
				}
			}
		}
	}

	//障害物情報の取得
	Obstacle *pObstacle = GetObstacle();

	//障害物とプレイヤーの当たり判定
	if (g_player.bDisp == true && g_player.state == PLAYERSTATE_NORMAL)
	{
		for (int nCntObs = 0; nCntObs < MAX_OBSTACLE; nCntObs++, pObstacle++)
		{
			if (pObstacle->bUse == true)
			{//敵が使用されている
				if (g_player.pos.x + (PLAYER_WIDTH / 2.0f) >= pObstacle->pos.x - (OBSTACLE_WIDTH / 2.0f)
					&& g_player.pos.x - (PLAYER_WIDTH / 2.0f) <= pObstacle->pos.x + (OBSTACLE_WIDTH / 2.0f)
					&& g_player.pos.y + (PLAYER_HEIGHT / 2.0f) >= pObstacle->pos.y - (OBSTACLE_HEIGHT / 2.0f)
					&& g_player.pos.y - (PLAYER_HEIGHT / 2.0f) <= pObstacle->pos.y + (OBSTACLE_HEIGHT / 2.0f))
				{ //敵の当たり判定
					HitPlayer(1);
				}
			}
		}
	}

	//アイテムの当たり判定
	CollisionItem(&g_player.pos, PLAYER_WIDTH, PLAYER_HEIGHT);

	//画面外処理
	Gamengai();

	//ライフゲージの位置更新
	SetPositionLife(D3DXVECTOR3(g_player.pos.x, g_player.pos.y - 85.0f, g_player.pos.z));

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH, g_player.pos.y - PLAYER_HEIGHT,0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH, g_player.pos.y - PLAYER_HEIGHT,0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH, g_player.pos.y + PLAYER_HEIGHT,0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH, g_player.pos.y + PLAYER_HEIGHT,0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}

//-------------------------------------------
//プレイヤーの描画処理
//-------------------------------------------
void DrawPlayer(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	if (g_player.bDisp == true)
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャ設定
		pDevice->SetTexture(0, g_pTexturePlayer);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//-------------------------------------------
//プレイヤーの状態管理処理
//-------------------------------------------
void StatePlayer(void)
{
	switch (g_player.state)
	{
	case PLAYERSTATE_APPEAR:		//プレイヤーの出現状態
		g_player.nCounterState--;		//カウンターを減らす
		FlashPlayer();					//プレイヤーの点滅
		break;

	case PLAYERSTATE_NORMAL:		//プレイヤーの通常状態
		break;

	case PLAYERSTATE_DAMAGE:		//プレイヤーのダメージ状態
		g_player.nCounterState--;		//カウンターを減らす
		FlashPlayer();					//プレイヤーの点滅
		break;

	case PLAYERSTATE_DEATH:			//プレイヤーの死亡状態
		g_player.nCounterState--;		//カウンターを減らす

		if (g_player.nCounterState <= 0 && !g_PlayerFade)
		{//カウンターが0になったら
			SetFade(MODE_RESULT);		//モード設定(ゲーム画面に移行)
			g_PlayerFade;				//フェードしている
		}
		break;
	}
}

void FlashPlayer(void)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	if (0 == g_player.nCounterState % 10)
	{
		//頂点カラーの変更
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	}
	if (1 == g_player.nCounterState % 10)
	{
		//頂点カラーの変更
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
	}
	if (g_player.nCounterState <= 0)
	{
		g_player.state = PLAYERSTATE_NORMAL;
		//頂点カラーの変更
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}

//-------------------------------------------
//プレイヤーのヒット処理
//-------------------------------------------
void HitPlayer(int nDamage)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	g_player.nLife -= nDamage;
	SubLife(0, nDamage);

	if (g_player.nLife <= 0 && !g_PlayerFade)
	{
		//爆発の処理
		SetExplosion(g_player.pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		g_player.bDisp = false;
		//モード設定(ゲーム画面に移行)
		SetFade(MODE_GAMEOVER);
		g_PlayerFade;
	}
	else
	{
		g_player.state = PLAYERSTATE_DAMAGE;
		g_player.nCounterState = 120;
		//頂点カラーの変更
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	}
	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}

//-------------------------------------------
//プレイヤーの移動処理
//-------------------------------------------
void MovePlayer(void)
{
	//スティックの情報を取得
	D3DXVECTOR3 Stick = GetControllerStickDir(0);

	if (GetKeyboardPress(DIK_A) == true || GetControllerPress(0, XINPUT_GAMEPAD_DPAD_LEFT)
		|| GetControllerStickPress(0, STICK_LEFT))
	{//Aキーが押された
		if (GetKeyboardPress(DIK_W) == true)
		{//AWキー押した場合
			g_player.move.x += sinf(-D3DX_PI / 4.0f * 3.0f) * 0.8f;
			g_player.move.y += cosf(-D3DX_PI / 4.0f * 3.0f) * 0.8f;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//ASキー押した場合
			g_player.move.x += sinf(-D3DX_PI / 4.0f) * 0.8f;
			g_player.move.y += cosf(-D3DX_PI / 4.0f) * 0.8f;
		}
		else
		{//Aキーのみ
			g_player.pos.x -= PLAYER_DIS;
			g_player.move.x += sinf(-D3DX_PI / 2.0f) * 0.8f;
			g_player.move.y += cosf(-D3DX_PI / 2.0f) * 0.8f;
		}
	}
	else if (GetKeyboardPress(DIK_D) == true || GetControllerPress(0, XINPUT_GAMEPAD_DPAD_RIGHT)
		|| GetControllerStickPress(0, STICK_RIGHT))
	{//Dキーが押された
		if (GetKeyboardPress(DIK_W) == true)
		{//DWキー押した場合
			g_player.move.x += sinf(D3DX_PI / 4.0f * 3.0f) * 0.8f;
			g_player.move.y += cosf(D3DX_PI / 4.0f * 3.0f) * 0.8f;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//DSキー押した場合
			g_player.move.x += sinf(D3DX_PI / 4.0f) * 0.8f;
			g_player.move.y += cosf(D3DX_PI / 4.0f) * 0.8f;
		}
		else
		{//Dキーのみ
			g_player.move.x += sinf(D3DX_PI / 2.0f) * 0.8f;
			g_player.move.y += cosf(D3DX_PI / 2.0f) * 0.8f;
		}
	}
	else if (GetKeyboardPress(DIK_W) == true || GetControllerPress(0, XINPUT_GAMEPAD_DPAD_UP)
		|| GetControllerStickPress(0, STICK_UP))
	{//Wキーが押された
			g_player.move.x += sinf(D3DX_PI) * 0.8f;
			g_player.move.y += cosf(D3DX_PI) * 0.8f;
	}
	else if (GetKeyboardPress(DIK_S) == true || GetControllerPress(0, XINPUT_GAMEPAD_DPAD_DOWN)
		|| GetControllerStickPress(0, STICK_DOWN))
	{//Sキーが押された
			g_player.move.x += sinf(0.0f) * 0.8f;
			g_player.move.y += cosf(0.0f) * 0.8f;
	}
}

//-------------------------------------------
//プレイヤーの画面外処理
//-------------------------------------------
void Gamengai(void)
{
	if (g_player.pos.x + PLAYER_WIDTH > SCREEN_WIDTH)
	{//右端
		g_player.pos.x = SCREEN_WIDTH - PLAYER_WIDTH;

	}
	if (g_player.pos.x - PLAYER_WIDTH < 0)
	{//左端
		g_player.pos.x = 0 + PLAYER_WIDTH;

	}
	if (g_player.pos.y - PLAYER_HEIGHT < 0)
	{//上
		g_player.pos.y = 0 + PLAYER_HEIGHT;

	}
	if (g_player.pos.y + PLAYER_HEIGHT >  SCREEN_HEIGHT)
	{//下
		g_player.pos.y = SCREEN_HEIGHT - PLAYER_HEIGHT;

	}
}

//-------------------------------------------
//プレイヤーの取得
//-------------------------------------------
Player * GetPlayer(void)
{
	return &g_player;
}