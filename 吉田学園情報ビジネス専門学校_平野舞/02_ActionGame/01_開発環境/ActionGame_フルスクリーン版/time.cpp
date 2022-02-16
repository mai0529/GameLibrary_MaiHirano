//-------------------------------------------
//
//タイマー処理[time.cpp]
//Author:平野舞
//
//-------------------------------------------

//インクルードファイル
#include "time.h"
#include "fade.h"

//グローバル宣言
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;			//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;		//頂点バッファへのポインタ
D3DXVECTOR3 g_posTime[3];							//スコアの位置
int g_nTime;										//スコアの値
int g_nCntTime;
int g_nCount;

//-------------------------------------------
//タイマーの初期化処理
//-------------------------------------------
void InitTime(void)
{
	int nCount;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number001.png",
		&g_pTextureTime);

	for (nCount = 0; nCount < TIME_MAX; nCount++)
	{
		g_posTime[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	g_nTime = 150;						//何秒間か
	int g_nCntTime = 60;				//60フレーム

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TIME_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCount = 0; nCount < 3; nCount++)
	{
		g_posTime[nCount] = D3DXVECTOR3(600.0f + (25.0f * nCount), 30.0f, 0.0f);
	}

	for (nCount = 0; nCount < TIME_MAX; nCount++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_posTime[nCount].x - (TIME_WIDTH / 2), g_posTime[nCount].y - (TIME_HEIGHT / 2), 0);
		pVtx[1].pos = D3DXVECTOR3(g_posTime[nCount].x + (TIME_WIDTH / 2), g_posTime[nCount].y - (TIME_HEIGHT / 2), 0);
		pVtx[2].pos = D3DXVECTOR3(g_posTime[nCount].x - (TIME_WIDTH / 2), g_posTime[nCount].y + (TIME_HEIGHT / 2), 0);
		pVtx[3].pos = D3DXVECTOR3(g_posTime[nCount].x + (TIME_WIDTH / 2), g_posTime[nCount].y + (TIME_HEIGHT / 2), 0);

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
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}
		//頂点バッファをアンロックする
		g_pVtxBuffTime->Unlock();
}

//-------------------------------------------
//タイマーの終了処理
//-------------------------------------------
void UninitTime(void)
{
	//テクスチャの破棄
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

//-------------------------------------------
//タイマーの更新処理
//-------------------------------------------
void UpdateTime(void)
{
	int nCntTime;

	int nTimePos[3];

	if (g_nTime != 0)
	{
		g_nCntTime--;
	}

	if (g_nCntTime <= 0)
	{
		g_nTime--;

		g_nCntTime = 60;
	}

	nTimePos[0] = g_nTime % 1000 / 100;
	nTimePos[1] = g_nTime % 100 / 10;
	nTimePos[2] = g_nTime % 10;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	for (nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.1f * nTimePos[nCntTime], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f * nTimePos[nCntTime] + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * nTimePos[nCntTime], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f * nTimePos[nCntTime] + 0.1f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTime->Unlock();

	if (g_nTime == 0)
	{
		if (g_nCount == 0)
		{
			SetFade(MODE_GAMEOVER);
		}
		g_nCount = 1;
	}
}

//-------------------------------------------
//タイマーの描画処理
//-------------------------------------------
void DrawTime(void)
{
	int nCntTime;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
	{
		//テクスチャ設定
		pDevice->SetTexture(0, g_pTextureTime);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTime * 4, 2);
	}
}

//-------------------------------------------
//タイマーの取得
//-------------------------------------------
int GetTime(void)
{
	return g_nTime;
}