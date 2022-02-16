//-------------------------------------------
//
//背景スクロール処理[bg.cpp](未完成)
//Author:平野舞
//
//-------------------------------------------
#include "bg.h"

//マクロ定義
#define NUM_BG		(3)				//背景の数
#define BG_WIDTH	(640.0f)		//幅
#define BG_HEIGHT	(360.0f)		//高さ

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureBG[NUM_BG] = {};		//テクスチャ(三枚分)へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;		//頂点バッファへのポインタ
float g_aPosTexV[NUM_BG];							//テクスチャ座標の開始位置(V値)


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
		"data/TEXTURE/bg100.png",
		&g_apTextureBG[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bg101.png",
		&g_apTextureBG[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bg102.png",
		&g_apTextureBG[2]);

	g_aPosTexV[NUM_BG] = 0.0f;		//座標の初期化
	
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
	pVtx[0].pos = D3DXVECTOR3(640.0f - BG_WIDTH ,360.0f - BG_HEIGHT,0.0f);
	pVtx[1].pos = D3DXVECTOR3(640.0f + BG_WIDTH ,360.0f - BG_HEIGHT,0.0f);
	pVtx[2].pos = D3DXVECTOR3(640.0f - BG_WIDTH ,360.0f + BG_HEIGHT,0.0f);
	pVtx[3].pos = D3DXVECTOR3(640.0f + BG_WIDTH ,360.0f + BG_HEIGHT,0.0f);

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
	g_pVtxBuffBG->Unlock();
}

//-------------------------------------------
//終了処理
//-------------------------------------------
void UninitBG(void)
{
	//テクスチャの破棄
	if (g_apTextureBG[NUM_BG] != NULL)
	{
		g_apTextureBG[NUM_BG]->Release();
		g_apTextureBG[NUM_BG] = NULL;
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
	pDevice->SetTexture(0, g_apTextureBG[0]);
	pDevice->SetTexture(0, g_apTextureBG[1]);
	pDevice->SetTexture(0, g_apTextureBG[2]);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}