//-------------------------------------------
//
//スコア処理[score.cpp]
//Author:平野舞
//
//-------------------------------------------
#include "score.h"

//マクロ定義
#define SCORE_WIDTH		(20.0f)		//スコアの幅
#define SCORE_HEIGHT	(45.0f)		//スコアの高さ

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;			//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		//頂点バッファへのポインタ
D3DXVECTOR3 g_posScore[8];							//スコアの位置
int g_nScore;										//スコアの値

//-------------------------------------------
//初期化処理
//-------------------------------------------
void InitScore(void)
{
	int nCount;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number000.png",
		&g_pTextureScore);

	for (nCount = 0; nCount < 8; nCount++)
	{
		g_posScore[nCount] = D3DXVECTOR3(1200.0f, 100.0f, 0.0f);		//位置を初期化する
	}
		g_nScore = 0;													//値を初期化する
		
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	g_posScore[0] = D3DXVECTOR3(920.0f, 100.0f, 0.0f);
	g_posScore[1] = D3DXVECTOR3(960.0f, 100.0f, 0.0f);
	g_posScore[2] = D3DXVECTOR3(1000.0f, 100.0f, 0.0f);
	g_posScore[3] = D3DXVECTOR3(1040.0f, 100.0f, 0.0f);
	g_posScore[4] = D3DXVECTOR3(1080.0f, 100.0f, 0.0f);
	g_posScore[5] = D3DXVECTOR3(1120.0f, 100.0f, 0.0f);
	g_posScore[6] = D3DXVECTOR3(1160.0f, 100.0f, 0.0f);
	g_posScore[7] = D3DXVECTOR3(1200.0f, 100.0f, 0.0f);

	for (nCount = 0; nCount < 8; nCount++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_posScore[nCount].x - SCORE_WIDTH, g_posScore[nCount].y - SCORE_HEIGHT, g_posScore[nCount].z);
		pVtx[1].pos = D3DXVECTOR3(g_posScore[nCount].x + SCORE_WIDTH, g_posScore[nCount].y - SCORE_HEIGHT, g_posScore[nCount].z);
		pVtx[2].pos = D3DXVECTOR3(g_posScore[nCount].x - SCORE_WIDTH, g_posScore[nCount].y + SCORE_HEIGHT, g_posScore[nCount].z);
		pVtx[3].pos = D3DXVECTOR3(g_posScore[nCount].x + SCORE_WIDTH, g_posScore[nCount].y + SCORE_HEIGHT, g_posScore[nCount].z);

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
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;		//頂点データを４つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();

	SetScore(0);
}

//-------------------------------------------
//終了処理
//-------------------------------------------
void UninitScore(void)
{
	//テクスチャの破棄
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffScore != NULL)
	{	
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//-------------------------------------------
//更新処理
//-------------------------------------------
void UpdateScore(void)
{
	//(今のところなし)
}

//-------------------------------------------
//描画処理
//-------------------------------------------
void DrawScore(void)
{
	int nCntScore;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntScore = 0; nCntScore < 8; nCntScore++)
	{
		//テクスチャ設定
		pDevice->SetTexture(0, g_pTextureScore);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
	}
}

//-------------------------------------------
//スコアの設定処理
//-------------------------------------------
void SetScore(int nScore)
{
	int aPosTexU[8];			//各桁の数字を格納
	int nCountScore;

	g_nScore = nScore;

	aPosTexU[0] = g_nScore % 100000000 / 10000000;
	aPosTexU[1] = g_nScore % 10000000 / 1000000;
	aPosTexU[2] = g_nScore % 1000000 / 100000;
	aPosTexU[3] = g_nScore % 100000 / 10000;
	aPosTexU[4] = g_nScore % 10000 / 1000;
	aPosTexU[5] = g_nScore % 1000 / 100;
	aPosTexU[6] = g_nScore % 100 / 10;
	aPosTexU[7] = g_nScore % 10 / 1;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	for (nCountScore = 0; nCountScore < 8; nCountScore++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[nCountScore], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f * aPosTexU[nCountScore] + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[nCountScore], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f * aPosTexU[nCountScore] + 0.1f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

//-------------------------------------------
//スコアの加算処理
//-------------------------------------------
void AddScore(int nValue)
{
	int aPosTexU[8];		//各桁の数字を格納
	int nCountScore;

	g_nScore += nValue;

	aPosTexU[0] = g_nScore % 100000000 / 10000000;
	aPosTexU[1] = g_nScore % 10000000 / 1000000;
	aPosTexU[2] = g_nScore % 1000000 / 100000;
	aPosTexU[3] = g_nScore % 100000 / 10000;
	aPosTexU[4] = g_nScore % 10000 / 1000;
	aPosTexU[5] = g_nScore % 1000 / 100;
	aPosTexU[6] = g_nScore % 100 / 10;
	aPosTexU[7] = g_nScore % 10 / 1;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	for (nCountScore = 0; nCountScore < 8; nCountScore++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[nCountScore], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f * aPosTexU[nCountScore] + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[nCountScore], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f * aPosTexU[nCountScore] + 0.1f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

//-------------------------------------------
//スコアの取得
//-------------------------------------------
int GetScore(void)
{
	return g_nScore;
}