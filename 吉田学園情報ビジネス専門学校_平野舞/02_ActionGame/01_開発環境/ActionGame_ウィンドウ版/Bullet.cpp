//-------------------------------------------
//
//弾の発射処理[Bullet.cpp]
//Author:平野舞
//
//-------------------------------------------

//インクルードファイル
#include "Bullet.h"
#include "enemy.h"
#include "input.h"
#include "sound.h"
#include "score.h"
#include "player.h"
#include "flame.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureBullet[NUM_BULLET] = {};		//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;			//頂点バッファへのポインタ
Bullet g_aBullet[MAX_BULLET];								//弾の情報

//-------------------------------------------
//弾の初期化処理
//-------------------------------------------
void InitBullet(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	int nCntBullet;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bullet001.png",
		&g_pTextureBullet[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bullet002.png",
		&g_pTextureBullet[1]);

	//弾の情報の初期化
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife =0;
		g_aBullet[nCntBullet].type = BULLETTYPE_PLAYER;
		g_aBullet[nCntBullet].bUse = false;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - (BULLET_WIDTH / 2), g_aBullet[nCntBullet].pos.y - (BULLET_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (BULLET_WIDTH / 2), g_aBullet[nCntBullet].pos.y - (BULLET_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - (BULLET_WIDTH / 2), g_aBullet[nCntBullet].pos.y + (BULLET_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (BULLET_WIDTH / 2), g_aBullet[nCntBullet].pos.y + (BULLET_HEIGHT / 2), 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;		//頂点データを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//-------------------------------------------
//弾の終了処理
//-------------------------------------------
void UninitBullet(void)
{
	int nCntBullet;

	for (nCntBullet = 0; nCntBullet < NUM_BULLET; nCntBullet++)
	{
		//テクスチャの破棄
		if (g_pTextureBullet[nCntBullet] != NULL)
		{
			g_pTextureBullet[nCntBullet]->Release();
			g_pTextureBullet[nCntBullet] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//-------------------------------------------
//弾の更新処理
//-------------------------------------------
void UpdateBullet(void)
{
	int nCntBullet;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//弾が使用されている
		 //弾の位置情報の更新
			g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;

			//頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - (BULLET_WIDTH / 2), g_aBullet[nCntBullet].pos.y - (BULLET_HEIGHT / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (BULLET_WIDTH / 2), g_aBullet[nCntBullet].pos.y - (BULLET_HEIGHT / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - (BULLET_WIDTH / 2), g_aBullet[nCntBullet].pos.y + (BULLET_HEIGHT / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (BULLET_WIDTH / 2), g_aBullet[nCntBullet].pos.y + (BULLET_HEIGHT / 2), 0.0f);

			Enemy *pEnemy = GetEnemy();
			int nCntEnemy;

			for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
			{
				if (pEnemy->bUse == true)
				{//敵が使用されている
					if (g_aBullet[nCntBullet].pos.x >= pEnemy->pos.x - (ENEMY_WIDTH / 2)
						&& g_aBullet[nCntBullet].pos.x <= pEnemy->pos.x + (ENEMY_WIDTH / 2)
						&& g_aBullet[nCntBullet].pos.y >= pEnemy->pos.y - ENEMY_HEIGHT
						&& g_aBullet[nCntBullet].pos.y <= pEnemy->pos.y)
					{ //敵の当たり判定
						if (pEnemy->nType == ENEMY_WOLF)
						{//狼
							HitEnemy(nCntEnemy, 1);
							AddScore(200);
						}
						else if (pEnemy->nType == ENEMY_BONE)
						{//骸骨
							if (pEnemy->nLife != 1)
							{//10回まではスコアもらえる
								HitEnemy(nCntEnemy, 1);
								AddScore(10);
							}
						}
						else if (pEnemy->nNumber == 1)
						{
							HitEnemy(nCntEnemy, 1);
							SetItem(pEnemy->pos, ITEM_CAKE);
						}
						g_aBullet[nCntBullet].bUse = false;		//使用していない状態にする
					}
				}
			}

			//炎の当たり判定
			CollisionFlame(&g_aBullet[nCntBullet].pos, BULLET_WIDTH, BULLET_HEIGHT);

			if (g_aBullet[nCntBullet].pos.x > SCREEN_WIDTH)
			{
				g_aBullet[nCntBullet].bUse = false;		//使用していない状態にする
			}

			//寿命のカウントダウン
			g_aBullet[nCntBullet].nLife -= 1;
			if (g_aBullet[nCntBullet].nLife == 0)
			{
				g_aBullet[nCntBullet].bUse = false;		//使用していない状態にする
			}
		}

		pVtx += 4;		//頂点データを４つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//-------------------------------------------
//弾の描画処理
//-------------------------------------------
void DrawBullet(void)
{
	int nCntBullet;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//弾が使用されている場合
				//テクスチャ設定
				pDevice->SetTexture(0, g_pTextureBullet[g_aBullet[nCntBullet].type]);
				//ポリゴンの描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}
}

//-------------------------------------------
//弾の設定処理
//-------------------------------------------
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTYPE type)
{	
	int nCntBullet;

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{//弾が使用されていない場合
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].nLife = 100;
			g_aBullet[nCntBullet].type = type;
			g_aBullet[nCntBullet].bUse = true;		//弾を使用している状態にする
			PlaySound(SOUND_LABEL_SE_SHOT);
			break;
		}
	}
}