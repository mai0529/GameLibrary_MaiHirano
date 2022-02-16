//-------------------------------------------
//
//ゲームタイトル処理[title.cpp]
//Author:平野舞
//
//-------------------------------------------

//インクルードファイル
#include "title.h"
#include "fade.h"
#include "sound.h"
#include "input.h"

//グローバル宣言
LPDIRECT3DTEXTURE9 g_pTextureTitle[MAX_TITLE] = {};			//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle[MAX_TITLE] = {};	//頂点バッファへのポインタ								//タイトルの情報
int g_nCounter = 60;

//-------------------------------------------
//初期化処理
//-------------------------------------------
void InitTitle(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/title001.jpg",
		&g_pTextureTitle[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/press_enter.png",
		&g_pTextureTitle[1]);

	for (int nCount = 0; nCount < MAX_TITLE; nCount++)
	{
		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffTitle[nCount],
			NULL);
	}

	//初期化
	g_nCounter = 60;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle[0]->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffTitle[0]->Unlock();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle[1]->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - (ENTER_WIDTH / 2), 500.0f - (ENTER_HEIGHT / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + (ENTER_WIDTH / 2), 500.0f - (ENTER_HEIGHT / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - (ENTER_WIDTH / 2), 500.0f + (ENTER_HEIGHT / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + (ENTER_WIDTH / 2), 500.0f + (ENTER_HEIGHT / 2), 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffTitle[1]->Unlock();


	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM000);
}

//-------------------------------------------
//終了処理
//-------------------------------------------
void UninitTitle(void)
{
	//サウンドの停止
	StopSound();

	for (int nCount = 0; nCount < 2; nCount++)
	{
		//テクスチャの破棄
		if (g_pTextureTitle[nCount] != NULL)
		{				  
			g_pTextureTitle[nCount]->Release();
			g_pTextureTitle[nCount] = NULL;
		}
	}

	for (int nCount = 0; nCount < 2; nCount++)
	{
		//頂点バッファの破棄
		if (g_pVtxBuffTitle[nCount] != NULL)
		{
			g_pVtxBuffTitle[nCount]->Release();
			g_pVtxBuffTitle[nCount] = NULL;
		}
	}
}

//-------------------------------------------
//更新処理
//-------------------------------------------
void UpdateTitle(void)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle[1]->Lock(0, 0, (void**)&pVtx, 0);

	g_nCounter--;

	if (0 == g_nCounter % 30)
	{
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	}

	if (10 == g_nCounter % 30)
	{
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.0f);
		pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.0f);
		pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.0f);
		pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.0f);
	}

	if (g_nCounter == 0)
	{
		g_nCounter = 60;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	//g_pVtxBuffTitle[1]->Lock(0, 0, (void**)&pVtx, 0);

	//決定キー(ENTERキー)が押されたかどうか
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		PlaySound(SOUND_LABEL_SE000);
		//モード設定
		SetFade(MODE_TUTORIAL);
	}
}

//-------------------------------------------
//描画処理
//-------------------------------------------
void DrawTitle(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	for (int nCount = 0; nCount < MAX_TITLE; nCount++)
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffTitle[nCount], 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャ設定
		pDevice->SetTexture(0, g_pTextureTitle[nCount]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}