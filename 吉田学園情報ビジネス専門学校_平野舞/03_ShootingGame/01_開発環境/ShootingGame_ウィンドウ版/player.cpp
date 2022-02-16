//-------------------------------------------
//
//プレイヤー情報[player.cpp]
//Author:平野舞
//
//-------------------------------------------
#include "main.h"
#include "player.h"
#include "input.h"
#include "Bullet.h"
#include "sound.h"
#include "explosion.h"
#include "enemy.h"
#include "fade.h"

//マクロ定義
#define PLAYER_WIDTH		(60.0f)		//プレイヤーの幅
#define PLAYER_HEIGHT		(75.0f)		//プレイヤーの高さ
#define PLAYER_DIS			(4.0f)		//移動距離
#define PLAYER_ENEMY		(80.0f)		//当たり判定

//グローバル宣言
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;			//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//頂点バッファへのポインタ
Player g_player;									//プレイヤーの情報
D3DXVECTOR3 g_moveBullet;							//弾の情報

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
		"data/TEXTURE/player001.png",
		&g_pTexturePlayer);

	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置の初期化
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量の初期化
	g_player.bDisp = true;
	g_player.nLife = 5;
	g_player.state = PLAYERSTATE_APPEAR;
	g_player.nCounterState = 60;
	g_moveBullet = D3DXVECTOR3(10.0f, 0.0f, 0.0f);

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
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH, g_player.pos.y - PLAYER_HEIGHT, g_player.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH, g_player.pos.y - PLAYER_HEIGHT, g_player.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH, g_player.pos.y + PLAYER_HEIGHT, g_player.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH, g_player.pos.y + PLAYER_HEIGHT, g_player.pos.z);

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

	switch (g_player.state)
	{
	case PLAYERSTATE_APPEAR:
		g_player.nCounterState--;
		if (0 == g_player.nCounterState % 10)
		{
			//頂点カラー
			pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		}
		if (1 == g_player.nCounterState % 10)
		{
			//頂点カラー
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
		}
		if (g_player.nCounterState <= 0)
		{
			g_player.state = PLAYERSTATE_NORMAL;
			//頂点カラー
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		break;
	case PLAYERSTATE_NORMAL:
		break;
	case PLAYERSTATE_DAMAGE:
		g_player.nCounterState--;
		if (0 == g_player.nCounterState % 10)
		{
			//頂点カラー
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		}
		if (1 == g_player.nCounterState % 10)
		{
			//頂点カラー
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
		}
		if (g_player.nCounterState <= 0)
		{
			g_player.state = PLAYERSTATE_NORMAL;
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		break;
	case PLAYERSTATE_DEATH:
		g_player.nCounterState--;
		if (g_player.nCounterState <= 0)
		{
			//モード設定(ゲーム画面に移行)
			SetFade(MODE_RESULT);
			return;
		}
		break;
	}

	Enemy *pEnemy = GetEnemy();
	int nCntEnemy;

	if (g_player.bDisp == true && g_player.state == PLAYERSTATE_NORMAL)
	{
		for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
		{
			if (pEnemy->bUse == true)
			{//敵が使用されている
				if (g_player.pos.x >= pEnemy->pos.x - PLAYER_ENEMY
					&& g_player.pos.x <= pEnemy->pos.x + PLAYER_ENEMY
					&& g_player.pos.y >= pEnemy->pos.y - PLAYER_ENEMY
					&& g_player.pos.y <= pEnemy->pos.y + PLAYER_ENEMY)
				{ //敵の当たり判定
					HitPlayer(1);
				}
			}
		}
	}
	
	if (GetKeyboardPress(DIK_A) == true)
	{//Aキーが押された
		if (GetKeyboardPress(DIK_W) == true)
		{//AWキー押した場合
			/*g_player.pos.x += sinf(-D3DX_PI / 0.75f) * PLAYER_DIS;
			g_player.pos.y += cosf(-D3DX_PI / 0.75f) * PLAYER_DIS;*/
			g_player.move.x += sinf(-D3DX_PI / 4.0f * 3.0f) * 0.8f;
			g_player.move.y += cosf(-D3DX_PI / 4.0f * 3.0f) * 0.8f;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//ASキー押した場合
			/*g_player.pos.x += sinf(-D3DX_PI / 4.0f * 3.0f) * PLAYER_DIS;
			g_player.pos.y += cosf(-D3DX_PI / 4.0f * 3.0f) * PLAYER_DIS;*/
			g_player.move.x += sinf(-D3DX_PI / 4.0f * 1.0f) * 0.8f;
			g_player.move.y += cosf(-D3DX_PI / 4.0f * 1.0f) * 0.8f;
		}
		else
		{//Aキーのみ
			g_player.pos.x -= PLAYER_DIS;
			g_player.move.x += sinf(-D3DX_PI / 2.0f) * 0.8f;
			g_player.move.y += cosf(-D3DX_PI / 2.0f) * 0.8f;
		}
	}

	else if (GetKeyboardPress(DIK_D) == true)
	{//Dキーが押された
		if (GetKeyboardPress(DIK_W) == true)
		{//DWキー押した場合
			/*g_player.pos.x += sinf(D3DX_PI * 0.75f) * PLAYER_DIS;
			g_player.pos.y += cosf(D3DX_PI * 0.75f) * PLAYER_DIS;*/
			g_player.move.x += sinf(D3DX_PI / 4.0f * 3.0f) * 0.8f;
			g_player.move.y += cosf(D3DX_PI / 4.0f * 3.0f) * 0.8f;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//DSキー押した場合
			/*g_player.pos.x += sinf(D3DX_PI * 0.25f) * PLAYER_DIS;
			g_player.pos.y += cosf(D3DX_PI * 0.25f) * PLAYER_DIS;*/
			g_player.move.x += sinf(D3DX_PI / 4.0f * 1.0f) * 0.8f;
			g_player.move.y += cosf(D3DX_PI / 4.0f * 1.0f) * 0.8f;
		}
		else
		{//Dキーのみ
			/*g_player.pos.x += PLAYER_DIS;*/
			g_player.move.x += sinf(D3DX_PI / 2.0f) * 0.8f;
			g_player.move.y += cosf(D3DX_PI / 2.0f) * 0.8f;
		}
	}

	else if (GetKeyboardPress(DIK_W) == true)
	{//Wキーが押された
		//if (GetKeyboardPress(DIK_D) == true)
		//{//WDキー押した場合
		//	/*g_player.pos.x += sinf(D3DX_PI) * PLAYER_DIS;
		//	g_player.pos.y += cosf(D3DX_PI) * PLAYER_DIS;*/
		//	g_player.move.x += sinf(D3DX_PI / 4.0f * 4.0f) * 0.8f;
		//	g_player.move.y += cosf(D3DX_PI / 4.0f * 4.0f) * 0.8f;
		//}
		//else if (GetKeyboardPress(DIK_A) == true)
		//{//WAキー押した場合
		//	/*g_player.pos.x += sinf(-D3DX_PI) * PLAYER_DIS;
		//	g_player.pos.y += cosf(-D3DX_PI) * PLAYER_DIS;*/
		//	g_player.move.x += sinf(D3DX_PI / 2.0f) * 0.8f;
		//	g_player.move.y += cosf(D3DX_PI / 2.0f) * 0.8f;
		//}
		if (GetKeyboardPress(DIK_W) == true)
		{//Wキーのみ
			/*g_player.pos.y -= PLAYER_DIS;*/
			g_player.move.x += sinf(D3DX_PI ) * 0.8f;
			g_player.move.y += cosf(D3DX_PI ) * 0.8f;
		}
	}

	else if (GetKeyboardPress(DIK_S) == true)
	{//Sキーが押された
		//if (GetKeyboardPress(DIK_D) == true)
		//{//SDキー押した場合
		//	g_player.pos.x += sinf(D3DX_PI * 0.5f) * PLAYER_DIS;
		//	g_player.pos.y += cosf(D3DX_PI * 0.5f) * PLAYER_DIS;
		//}
		//else if (GetKeyboardPress(DIK_A) == true)
		//{//SAキー押した場合
		//	g_player.pos.x += sinf(-D3DX_PI * 0.5f) * PLAYER_DIS;
		//	g_player.pos.y += cosf(-D3DX_PI * 0.5f) * PLAYER_DIS;
		//}
		if(GetKeyboardPress(DIK_S) == true)
		{//Sキーのみ
			g_player.move.x += sinf(0.0f) * 0.8f;
			g_player.move.y += cosf(0.0f) * 0.8f;
		}
	}

	//位置を更新
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;

	//移動量を更新(減衰させる)
	g_player.move.x += (0.0f - g_player.move.x) * 0.08f;
	g_player.move.y += (0.0f - g_player.move.y) * 0.08f;

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH, g_player.pos.y - PLAYER_HEIGHT,0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH, g_player.pos.y - PLAYER_HEIGHT,0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH, g_player.pos.y + PLAYER_HEIGHT,0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH, g_player.pos.y + PLAYER_HEIGHT,0.0f);

	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{//SPACEキーが押された   
		//弾の設定
		SetBullet(g_player.pos, g_moveBullet,BULLETTYPE_PLAYER);
		//サウンドの再生
		PlaySound(SOUND_LABEL_SE_SHOT);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();

	Gamengai();
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
//プレイヤーのヒット処理
//-------------------------------------------
void HitPlayer(int nDamage)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	g_player.nLife -= nDamage;
	if (g_player.nLife <= 0)
	{
		//爆発の処理
		SetExplosion(g_player.pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		g_player.bDisp = false;
		//モード設定(ゲーム画面に移行)
		SetFade(MODE_GAMEOVER);
	}
	else
	{
		g_player.state = PLAYERSTATE_DAMAGE;
		g_player.nCounterState = 60;
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
//プレイヤーの取得
//-------------------------------------------
void * GetPlayer(void)
{
	return &g_player;
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