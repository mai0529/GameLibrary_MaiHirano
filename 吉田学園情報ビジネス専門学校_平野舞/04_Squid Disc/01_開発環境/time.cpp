//-------------------------------------------
//
//タイマー処理[time.cpp]
//Author:平野舞
//
//-------------------------------------------

//インクルードファイル
#include "time.h"
#include "fade.h"
//マクロ定義
#define TIME_WIDTH		(20.0f)		//タイムの幅
#define TIME_HEIGHT		(45.0f)		//タイムの高さ
#define NUM_TIME		(3)			//タイムの最大桁数

//グローバル宣言
LPDIRECT3DTEXTURE9 g_pTextureTime[2] = {};			//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime[2] = {};		//頂点バッファへのポインタ
D3DXVECTOR3 g_posTime[NUM_TIME];					//タイムの位置
int g_nTime;										//タイムの値
int g_nCntTime;										//何フレームか

//-------------------------------------------
//タイマーの初期化処理
//-------------------------------------------
void InitTime(void)
{
	for (int nCount = 0; nCount < NUM_TIME; nCount++)
	{//位置の初期化
		g_posTime[nCount] = D3DXVECTOR3(615.0f + (25.0f * nCount), 30.0f, 0.0f);
	}
	g_nTime = 90;						//何秒間か
	g_nCntTime = 60;					//60フレーム

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//--------------------------------背景の処理----------------------------------------------------

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/background000.jpg",
		&g_pTextureTime[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime[0],
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTime[0]->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f) - (80.0f / 2.0f), 30.0f - (50.0f / 2.0f), 0);
	pVtx[1].pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f) + (80.0f / 2.0f), 30.0f - (50.0f / 2.0f), 0);
	pVtx[2].pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f) - (80.0f / 2.0f), 30.0f + (50.0f / 2.0f), 0);
	pVtx[3].pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f) + (80.0f / 2.0f), 30.0f + (50.0f / 2.0f), 0);

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
	g_pVtxBuffTime[0]->Unlock();

	//--------------------------------数字の処理----------------------------------------------------

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number000.png",
		&g_pTextureTime[1]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_TIME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime[1],
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTime[1]->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < NUM_TIME; nCount++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_posTime[nCount].x - (TIME_WIDTH / 2.0f), g_posTime[nCount].y - (TIME_HEIGHT / 2.0f), 0);
		pVtx[1].pos = D3DXVECTOR3(g_posTime[nCount].x + (TIME_WIDTH / 2.0f), g_posTime[nCount].y - (TIME_HEIGHT / 2.0f), 0);
		pVtx[2].pos = D3DXVECTOR3(g_posTime[nCount].x - (TIME_WIDTH / 2.0f), g_posTime[nCount].y + (TIME_HEIGHT / 2.0f), 0);
		pVtx[3].pos = D3DXVECTOR3(g_posTime[nCount].x + (TIME_WIDTH / 2.0f), g_posTime[nCount].y + (TIME_HEIGHT / 2.0f), 0);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;		//頂点情報を4つ分進める
	}
		//頂点バッファをアンロックする
		g_pVtxBuffTime[1]->Unlock();
}

//-------------------------------------------
//タイマーの終了処理
//-------------------------------------------
void UninitTime(void)
{
	//テクスチャの破棄
	for (int nCount = 0; nCount < 2; nCount++)
	{
		if (g_pTextureTime[nCount] != NULL)
		{
			g_pTextureTime[nCount]->Release();
			g_pTextureTime[nCount] = NULL;
		}
	}

	//頂点バッファの破棄
	for (int nCount = 0; nCount < 2; nCount++)
	{
		if (g_pVtxBuffTime[nCount] != NULL)
		{
			g_pVtxBuffTime[nCount]->Release();
			g_pVtxBuffTime[nCount] = NULL;
		}
	}
}

//-------------------------------------------
//タイマーの更新処理
//-------------------------------------------
void UpdateTime(void)
{
	// フェード情報の取得
	FADE fade = GetFade();

	int nTimePos[3];		//タイムのテクスチャ位置

	if (g_nTime != 0)
	{//タイマーが0ではなかったら
		g_nCntTime--;		//フレーム数を減らす
	}

	if (g_nCntTime <= 0)
	{//フレーム数が0より小さくなったら
		g_nTime--;					//タイマーを1減らす
									
		g_nCntTime = 90;			//フレーム数を90に戻す
	}

	if (g_nTime <= 0 && fade == FADE_NONE)
	{
		SetFade(MODE_END);
		return;
	}

	//数字のテクスチャを格納
	nTimePos[0] = g_nTime % 1000 / 100;
	nTimePos[1] = g_nTime % 100 / 10;
	nTimePos[2] = g_nTime % 10;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTime[1]->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTime = 0; nCntTime < NUM_TIME; nCntTime++)
	{//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.1f * nTimePos[nCntTime], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f * nTimePos[nCntTime] + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * nTimePos[nCntTime], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f * nTimePos[nCntTime] + 0.1f, 1.0f);

		pVtx += 4;		//データを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTime[1]->Unlock();
}

//-------------------------------------------
//タイマーの描画処理
//-------------------------------------------
void DrawTime(void)
{
	for (int nCntTime = 0; nCntTime < 2; nCntTime++)
	{
		//デバイスへのポインタ
		LPDIRECT3DDEVICE9 pDevice;

		//デバイスの取得
		pDevice = GetDevice();

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffTime[nCntTime], 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//アルファテストを有効
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		switch (nCntTime)
		{
		case 0:			//0だったら背景を描画
			//テクスチャ設定
			pDevice->SetTexture(0, g_pTextureTime[0]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
			break;
		case 1:			//1だったら数字を描画
		for (int nCntTime = 0; nCntTime < NUM_TIME; nCntTime++)
		{
			//テクスチャ設定
			pDevice->SetTexture(0, g_pTextureTime[1]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTime * 4, 2);
		}
		break;
		default:
			//assert(false);
			break;
		}

		//アルファテストを無効に戻す
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	}
}