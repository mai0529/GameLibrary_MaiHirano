//-------------------------------------------
//
//ライフ表示処理[life.cpp](未完成)
//Author:平野舞
//
//-------------------------------------------

//インクルードファイル
#include "life.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureLife = NULL;			//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;		//頂点バッファへのポインタ
Life g_aLife[MAX_LIFE];								//弾の情報

//-------------------------------------------
//ライフの初期化処理
//-------------------------------------------
void InitLife(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	int nCntLife;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/heart.png",
		&g_pTextureLife);

	//弾の情報の初期化
	for (nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		g_aLife[nCntLife].pos = D3DXVECTOR3(35.0f + (30.0f *  nCntLife), 25.0f, 0.0f);
		g_aLife[nCntLife].bUse = false;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_LIFE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x - (LIFE_WIDTH / 2), g_aLife[nCntLife].pos.y - (LIFE_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x + (LIFE_WIDTH / 2), g_aLife[nCntLife].pos.y - (LIFE_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x - (LIFE_WIDTH / 2), g_aLife[nCntLife].pos.y + (LIFE_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x + (LIFE_WIDTH / 2), g_aLife[nCntLife].pos.y + (LIFE_HEIGHT / 2), 0.0f);

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
	g_pVtxBuffLife->Unlock();

	for (int nCount = 0; nCount < 3; nCount++)
	{
		SetLife(D3DXVECTOR3(35.0f + (30.0f * nCount), 25.0f, 0.0f));
	}
}

//-------------------------------------------
//ライフの終了処理
//-------------------------------------------
void UninitLife(void)
{
	//テクスチャの破棄
	if (g_pTextureLife != NULL)
	{
		g_pTextureLife->Release();
		g_pTextureLife = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}
}

//-------------------------------------------
//ライフの更新処理
//-------------------------------------------
void UpdateLife(void)
{
	int nCntLife;
	Player *pPlayer = GetPlayer();

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		if (g_aLife[nCntLife].bUse == true)
		{//ライフが使用されている
			//if (pPlayer->nLife += 1)
			//{//ライフが増えたら
			//	SetLife(D3DXVECTOR3(g_aLife[nCntLife].pos.x + 30.0f, 25.0f, 0.0f));

			//}
			//else if (pPlayer->nLife -= 1)
			//{//ライフが減ったら
			//	g_aLife[pPlayer->nLife + 1].bUse = false;
			//}

		 //頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x - (LIFE_WIDTH / 2), g_aLife[nCntLife].pos.y - (LIFE_HEIGHT / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x + (LIFE_WIDTH / 2), g_aLife[nCntLife].pos.y - (LIFE_HEIGHT / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x - (LIFE_WIDTH / 2), g_aLife[nCntLife].pos.y + (LIFE_HEIGHT / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x + (LIFE_WIDTH / 2), g_aLife[nCntLife].pos.y + (LIFE_HEIGHT / 2), 0.0f);
		}
		pVtx += 4;		//頂点データを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffLife->Unlock();
}

//-------------------------------------------
//ライフの描画処理
//-------------------------------------------
void DrawLife(void)
{
	int nCntLife;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureLife);

	for (nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		if (g_aLife[nCntLife].bUse == true)
		{//弾が使用されている場合
		 //ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLife * 4, 2);
		}
	}
}

//-------------------------------------------
//ライフの設定処理
//-------------------------------------------
void SetLife(D3DXVECTOR3 pos)
{
	int nCntLife;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		if (g_aLife[nCntLife].bUse == false)
		{//ライフが使用されていない場合
			g_aLife[nCntLife].pos = pos;
			g_aLife[nCntLife].bUse = true;

			break;
		}
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffLife->Unlock();
}

//-------------------------------------------
//ライフの設定処理
//-------------------------------------------
void AddLife(int nValue)
{

}

//-------------------------------------------
//ライフの取得
//-------------------------------------------
Life * GetMaxLife(void)
{
	return &g_aLife[MAX_LIFE - 1];
}

//-------------------------------------------
//ライフの取得
//-------------------------------------------
Life * GetLife(void)
{
	return &g_aLife[0];
}