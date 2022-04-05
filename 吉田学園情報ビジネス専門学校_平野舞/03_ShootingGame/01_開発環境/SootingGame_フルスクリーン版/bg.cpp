//-------------------------------------------
//
//背景スクロール処理[bg.cpp](未完成)
//Author:平野舞
//
//-------------------------------------------
#include "bg.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureBG = NULL;			//テクスチャ(三枚分)へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;		//頂点バッファへのポインタ
float g_aPosTexV;									//テクスチャ座標の開始位置(V値)


//-------------------------------------------
//初期化処理
//-------------------------------------------
void InitBG(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bg000.png",
		&g_apTextureBG);

	g_aPosTexV = 0.0f;		//座標の初期化
	
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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
	pVtx[0].tex = D3DXVECTOR2(g_aPosTexV, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(g_aPosTexV + 1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_aPosTexV, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(g_aPosTexV + 1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffBG->Unlock();
}

//-------------------------------------------
//終了処理
//-------------------------------------------
void UninitBG(void)
{
	//テクスチャの破棄
	if (g_apTextureBG != NULL)
	{
		g_apTextureBG->Release();
		g_apTextureBG = NULL;
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
	g_aPosTexV += BG_SPEED;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(g_aPosTexV, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(g_aPosTexV + 1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_aPosTexV, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(g_aPosTexV + 1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffBG->Unlock();
}

//-------------------------------------------
//描画処理
//-------------------------------------------
void DrawBG(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_apTextureBG);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}