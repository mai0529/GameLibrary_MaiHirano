//-------------------------------------------
//
//背景処理[bg.cpp]
//Author:平野舞
//
//-------------------------------------------

//インクルードファイル
#include "bg.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureBG[NUM_BG] = {};			//テクスチャ(三枚分)へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;			//頂点バッファへのポインタ
BG g_aBG[NUM_BG];

//-------------------------------------------
//初期化処理
//-------------------------------------------
void InitBG(void)
{
	for (int nCount = 0; nCount < NUM_BG; nCount++)
	{
		g_aBG[nCount].fTexU = 0.0f;		//texUの初期化
		g_aBG[nCount].fTexV = 0.0f;		//texVの初期化	
	}
	//posの初期化
	g_aBG[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	g_aBG[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, 550.0f, 0.0f);
	g_aBG[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, 400.0f, 0.0f);


	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/sky002.jpg",
		&g_apTextureBG[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/city000.png",
		&g_apTextureBG[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/cloud000.png",
		&g_apTextureBG[2]);
	
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	float fWidth = 0.0f;
	float fHeight = 0.0f;

	for (int nCount = 0; nCount < NUM_BG; nCount++)
	{
		switch (nCount)
		{
		case 0:
			fWidth = SCREEN_WIDTH;
			fHeight = SCREEN_HEIGHT;
			break;
		case 1:
			fWidth = SCREEN_WIDTH;
			fHeight = 200;
			break;
		case 2:
			fWidth = SCREEN_WIDTH;
			fHeight = 100;
			break;
		default:
			break;
		}

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aBG[nCount].pos.x - fWidth / 2, g_aBG[nCount].pos.y - fHeight / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBG[nCount].pos.x + fWidth / 2, g_aBG[nCount].pos.y - fHeight / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBG[nCount].pos.x - fWidth / 2, g_aBG[nCount].pos.y + fHeight / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBG[nCount].pos.x + fWidth / 2, g_aBG[nCount].pos.y + fHeight / 2, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(g_aBG[nCount].fTexU, 0.1f);
		pVtx[1].tex = D3DXVECTOR2(g_aBG[nCount].fTexU + 1.0f, 0.1f);
		pVtx[2].tex = D3DXVECTOR2(g_aBG[nCount].fTexU, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aBG[nCount].fTexU + 1.0f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBG->Unlock();
}

//-------------------------------------------
//終了処理
//-------------------------------------------
void UninitBG(void)
{
	int nCountBG;

	for (nCountBG = 0; nCountBG < NUM_BG; nCountBG++)
	{
		//テクスチャの破棄
		if (g_apTextureBG[nCountBG] != NULL)
		{
			g_apTextureBG[nCountBG]->Release();
			g_apTextureBG[nCountBG] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}
}

//-------------------------------------------
//更新処理
//-------------------------------------------
void UpdateBG(void)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < NUM_BG; nCount++)
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(g_aBG[nCount].fTexU, 0.1f);
		pVtx[1].tex = D3DXVECTOR2(g_aBG[nCount].fTexU + 1.0f, 0.1f);
		pVtx[2].tex = D3DXVECTOR2(g_aBG[nCount].fTexU, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aBG[nCount].fTexU + 1.0f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBG->Unlock();
}

//-------------------------------------------
//描画処理
//-------------------------------------------
void DrawBG(void)
{
	int nCntBG;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		//テクスチャ設定
		pDevice->SetTexture(0, g_apTextureBG[nCntBG]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBG * 4, 2);
	}
}

//-------------------------------------------
//背景の取得
//-------------------------------------------
BG *GetBG(void)
{
	return &g_aBG[0];
}