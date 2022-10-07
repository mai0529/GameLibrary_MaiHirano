//-------------------------------------------
//
//キラキラ情報[twinkle.cpp]
//Author:平野舞
//
//-------------------------------------------

//インクルードファイル
#include "twinkle.h"

//グローバル宣言
LPDIRECT3DTEXTURE9 g_pTextureTwinkle = NULL;				//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTwinkle = NULL;			//頂点バッファへのポインタ
Twinkle g_aTwinkle[MAX_TWINKLE];							//アイテムの情報

//-------------------------------------------
//キラキラの初期化処理
//-------------------------------------------
void InitTwinkle(void)
{
	int nCntTwinkle;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/light000.png",
		&g_pTextureTwinkle);

	for (nCntTwinkle = 0; nCntTwinkle < MAX_TWINKLE; nCntTwinkle++)
	{
		g_aTwinkle[nCntTwinkle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
		g_aTwinkle[nCntTwinkle].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
		g_aTwinkle[nCntTwinkle].nNumber =0;									//何番目か
		g_aTwinkle[nCntTwinkle].bUse = false;								//使用するかしないか
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TWINKLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTwinkle,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTwinkle->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTwinkle = 0; nCntTwinkle < MAX_TWINKLE; nCntTwinkle++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aTwinkle[nCntTwinkle].pos.x - (TWINKLE_WIDTH / 2), g_aTwinkle[nCntTwinkle].pos.y - (TWINKLE_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aTwinkle[nCntTwinkle].pos.x + (TWINKLE_WIDTH / 2), g_aTwinkle[nCntTwinkle].pos.y - (TWINKLE_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aTwinkle[nCntTwinkle].pos.x - (TWINKLE_WIDTH / 2), g_aTwinkle[nCntTwinkle].pos.y + (TWINKLE_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aTwinkle[nCntTwinkle].pos.x + (TWINKLE_WIDTH / 2), g_aTwinkle[nCntTwinkle].pos.y + (TWINKLE_HEIGHT / 2), 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
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
	g_pVtxBuffTwinkle->Unlock();

	SetTwinkle(D3DXVECTOR3(50.0f,  0.0f, 0.0f),D3DXVECTOR3(1.2f,1.0f,0.0f),0);
	SetTwinkle(D3DXVECTOR3(200.0f, 0.0f, 0.0f),D3DXVECTOR3(0.5f,0.8f,0.0f),0);
	SetTwinkle(D3DXVECTOR3(400.0f, 0.0f, 0.0f),D3DXVECTOR3(1.5f,1.2f,0.0f), 0);
	SetTwinkle(D3DXVECTOR3(1530.0f,0.0f, 0.0f),D3DXVECTOR3(-0.4f,0.3f,0.0f),0);
	SetTwinkle(D3DXVECTOR3(1750.0f,0.0f, 0.0f),D3DXVECTOR3(-0.7f,0.5f,0.0f),0);
	SetTwinkle(D3DXVECTOR3(2030.0f,0.0f, 0.0f),D3DXVECTOR3(-0.3f,0.4f, 0.0f), 0);
	SetTwinkle(D3DXVECTOR3(3010.0f,0.0f, 0.0f),D3DXVECTOR3(-0.8f,0.8f, 0.0f), 0);
	SetTwinkle(D3DXVECTOR3(4570.0f,0.0f, 0.0f),D3DXVECTOR3(-0.4f,0.2f, 0.0f), 0);
	SetTwinkle(D3DXVECTOR3(5940.0f,0.0f, 0.0f),D3DXVECTOR3(-0.5f,0.3f, 0.0f), 0);
	SetTwinkle(D3DXVECTOR3(6340.0f,0.0f, 0.0f),D3DXVECTOR3(-0.4f,0.2f, 0.0f), 0);
	SetTwinkle(D3DXVECTOR3(7140.0f,0.0f, 0.0f),D3DXVECTOR3(-0.3f,0.2f,0.0f),0);
	SetTwinkle(D3DXVECTOR3(8480.0f,395.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),1);
}

//-------------------------------------------
//キラキラの終了処理
//-------------------------------------------
void UninitTwinkle(void)
{
	//テクスチャの破棄
	if (g_pTextureTwinkle != NULL)
	{
		g_pTextureTwinkle->Release();
		g_pTextureTwinkle = NULL;
	}


	//頂点バッファの破棄
	if (g_pVtxBuffTwinkle != NULL)
	{
		g_pVtxBuffTwinkle->Release();
		g_pVtxBuffTwinkle = NULL;
	}
}

//-------------------------------------------
//キラキラの更新処理
//-------------------------------------------
void UpdateTwinkle(void)
{
	int nCntTwinkle;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTwinkle->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTwinkle = 0; nCntTwinkle < MAX_TWINKLE; nCntTwinkle++)
	{
		if (g_aTwinkle[nCntTwinkle].bUse == true)
		{
			//位置を更新
			g_aTwinkle[nCntTwinkle].pos.x += g_aTwinkle[nCntTwinkle].move.x;
			g_aTwinkle[nCntTwinkle].pos.y += g_aTwinkle[nCntTwinkle].move.y;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aTwinkle[nCntTwinkle].pos.x - (TWINKLE_WIDTH / 2), g_aTwinkle[nCntTwinkle].pos.y - (TWINKLE_HEIGHT / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aTwinkle[nCntTwinkle].pos.x + (TWINKLE_WIDTH / 2), g_aTwinkle[nCntTwinkle].pos.y - (TWINKLE_HEIGHT / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aTwinkle[nCntTwinkle].pos.x - (TWINKLE_WIDTH / 2), g_aTwinkle[nCntTwinkle].pos.y + (TWINKLE_HEIGHT / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aTwinkle[nCntTwinkle].pos.x + (TWINKLE_WIDTH / 2), g_aTwinkle[nCntTwinkle].pos.y + (TWINKLE_HEIGHT / 2), 0.0f);

		}
		pVtx += 4;		//頂点データを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTwinkle->Unlock();
}

//-------------------------------------------
//アイテムの描画処理
//-------------------------------------------
void DrawTwinkle(void)
{
	int nCntTwinkle;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTwinkle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureTwinkle);

	for (nCntTwinkle = 0; nCntTwinkle < MAX_TWINKLE; nCntTwinkle++)
	{
		if (g_aTwinkle[nCntTwinkle].bUse == true)
		{
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTwinkle * 4, 2);
		}
	}
}

//-------------------------------------------
//キラキラの設定処理
//-------------------------------------------
void SetTwinkle(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nNumber)
{
	int nCntTwinkle;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTwinkle->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTwinkle = 0; nCntTwinkle < MAX_TWINKLE; nCntTwinkle++)
	{
		if (g_aTwinkle[nCntTwinkle].bUse == false)
		{//ブロックが使用されていない場合
			g_aTwinkle[nCntTwinkle].pos = pos;
			g_aTwinkle[nCntTwinkle].move = move;
			g_aTwinkle[nCntTwinkle].nNumber = nNumber;
			g_aTwinkle[nCntTwinkle].bUse = true;
			break;
		}
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTwinkle->Unlock();
}

//-------------------------------------------
//キラキラの当たり判定処理
//-------------------------------------------
void CollisionTwinkle(D3DXVECTOR3 * pPos, float fWidth, float fHeigtht)
{
	int nCntTwinkle;

	for (nCntTwinkle = 0; nCntTwinkle < MAX_TWINKLE; nCntTwinkle++)
	{
		if (g_aTwinkle[nCntTwinkle].bUse == true)
		{//キラキラを使っているとき
			if (pPos->x + (fWidth / 2) >= g_aTwinkle[nCntTwinkle].pos.x - (TWINKLE_WIDTH / 2)
				&& pPos->x - (fWidth / 2) <= g_aTwinkle[nCntTwinkle].pos.x + (TWINKLE_WIDTH / 2)
				&& pPos->y >= g_aTwinkle[nCntTwinkle].pos.y - (TWINKLE_HEIGHT / 2)
				&& pPos->y - fHeigtht <= g_aTwinkle[nCntTwinkle].pos.y + (TWINKLE_HEIGHT / 2))
			{
				if (g_aTwinkle[nCntTwinkle].nNumber == 1)
				{
					SetItem(D3DXVECTOR3(g_aTwinkle[nCntTwinkle].pos.x, g_aTwinkle[nCntTwinkle].pos.y, 0.0f), ITEM_CAKE);
				}
				else
				{
					SetItem(D3DXVECTOR3(g_aTwinkle[nCntTwinkle].pos.x, g_aTwinkle[nCntTwinkle].pos.y, 0.0f), ITEM_CANDY);
				}
				g_aTwinkle[nCntTwinkle].bUse = false;
			}
		}
	}
}

//-------------------------------------------
//キラキラの取得
//-------------------------------------------
Twinkle *GetTwinkle(void)
{
	return &g_aTwinkle[0];
}