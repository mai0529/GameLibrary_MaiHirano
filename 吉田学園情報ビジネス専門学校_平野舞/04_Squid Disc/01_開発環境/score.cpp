//-------------------------------------------
//
//スコア処理[score.cpp]
//Author:平野舞
//
//-------------------------------------------

//インクルードファイル
#include "score.h"


//マクロ定義
#define SCORE_WIDTH		(20.0f)		//スコアの幅
#define SCORE_HEIGHT	(45.0f)		//スコアの高さ
#define NUM_SCORE		(2)			//スコアの最大桁数
#define MAX_SCORE		(2)			//スコアの最大数

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureScore[3] = {};			//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore[3] = {};	//頂点バッファへのポインタ
D3DXVECTOR3 g_PosScore[MAX_SCORE][NUM_SCORE];		//スコアの位置
int g_nScore[MAX_SCORE];							//スコアの値
int g_aPosTexU[MAX_SCORE][NUM_SCORE];				//各桁の数字を格納

//-------------------------------------------
//初期化処理
//-------------------------------------------
void InitScore(void)
{
	//初期化
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		for (int nCntX = 0; nCntX < NUM_SCORE; nCntX++)
		{//位置
			g_PosScore[nCntScore][nCntX] = D3DXVECTOR3((570.0f + (25.0f * nCntX)) + (110.0f * nCntScore), SCREEN_HEIGHT / 2.0f, 0.0f);
		}
		g_nScore[nCntScore] = 0;		//得点
	}

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
		&g_pTextureScore[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore[0],
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore[0]->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f) - (160.0f / 2.0f), (SCREEN_HEIGHT / 2.0f) - (50.0f / 2.0f), 0);
	pVtx[1].pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f) + (160.0f / 2.0f), (SCREEN_HEIGHT / 2.0f) - (50.0f / 2.0f), 0);
	pVtx[2].pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f) - (160.0f / 2.0f), (SCREEN_HEIGHT / 2.0f) + (50.0f / 2.0f), 0);
	pVtx[3].pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f) + (160.0f / 2.0f), (SCREEN_HEIGHT / 2.0f) + (50.0f / 2.0f), 0);

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
	g_pVtxBuffScore[0]->Unlock();

	//--------------------------------「ー」(得点と得点の間にあるやつ)の処理---------------------------------------------------

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/score000.png",
		&g_pTextureScore[1]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore[1],
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore[1]->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f) - (50.0f / 2.0f), (SCREEN_HEIGHT / 2.0f) - (10.0f / 2.0f), 0);
	pVtx[1].pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f) + (50.0f / 2.0f), (SCREEN_HEIGHT / 2.0f) - (10.0f / 2.0f), 0);
	pVtx[2].pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f) - (50.0f / 2.0f), (SCREEN_HEIGHT / 2.0f) + (10.0f / 2.0f), 0);
	pVtx[3].pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f) + (50.0f / 2.0f), (SCREEN_HEIGHT / 2.0f) + (10.0f / 2.0f), 0);

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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffScore[1]->Unlock();

	//--------------------------------得点(数字)の処理---------------------------------------------------

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number000.png",
		&g_pTextureScore[2]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE * NUM_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore[2],
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore[2]->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		for (int nCntX = 0; nCntX < NUM_SCORE; nCntX++)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_PosScore[nCntScore][nCntX].x - (SCORE_WIDTH / 2.0f), g_PosScore[nCntScore][nCntX].y - (SCORE_HEIGHT / 2.0f), 0);
			pVtx[1].pos = D3DXVECTOR3(g_PosScore[nCntScore][nCntX].x + (SCORE_WIDTH / 2.0f), g_PosScore[nCntScore][nCntX].y - (SCORE_HEIGHT / 2.0f), 0);
			pVtx[2].pos = D3DXVECTOR3(g_PosScore[nCntScore][nCntX].x - (SCORE_WIDTH / 2.0f), g_PosScore[nCntScore][nCntX].y + (SCORE_HEIGHT / 2.0f), 0);
			pVtx[3].pos = D3DXVECTOR3(g_PosScore[nCntScore][nCntX].x + (SCORE_WIDTH / 2.0f), g_PosScore[nCntScore][nCntX].y + (SCORE_HEIGHT / 2.0f), 0);

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

			pVtx += 4;		//頂点データを４つ分進める
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore[2]->Unlock();

	SetScore(0, 0);
	SetScore(1, 0);
}

//-------------------------------------------
//終了処理
//-------------------------------------------
void UninitScore(void)
{
	//テクスチャの破棄
	for (int nCount = 0; nCount < 3; nCount++)
	{
		if (g_pTextureScore[nCount] != NULL)
		{
			g_pTextureScore[nCount]->Release();
			g_pTextureScore[nCount] = NULL;
		}
	}

	//頂点バッファの破棄
	for (int nCount = 0; nCount < 3; nCount++)
	{
		if (g_pVtxBuffScore[nCount] != NULL)
		{
			g_pVtxBuffScore[nCount]->Release();
			g_pVtxBuffScore[nCount] = NULL;
		}
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
	for (int nCount = 0; nCount < 3; nCount++)
	{
		//デバイスへのポインタ
		LPDIRECT3DDEVICE9 pDevice;

		//デバイスの取得
		pDevice = GetDevice();

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffScore[nCount], 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//アルファテストを有効
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		//ポリゴン描画のカウンタ
		int nCntDraw = 0;

		switch (nCount)
		{
		case 0:			//0だったら背景の描画
			//テクスチャ設定
			pDevice->SetTexture(0, g_pTextureScore[0]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
			break;
		case 1:			//1だったら「ー」の描画
			//テクスチャ設定
			pDevice->SetTexture(0, g_pTextureScore[1]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
			break;
		case 2:			//1だったらスコアの描画
			for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
			{
				for (int nCntX = 0; nCntX < NUM_SCORE; nCntX++, nCntDraw++)
				{
					//テクスチャ設定
					pDevice->SetTexture(0, g_pTextureScore[2]);

					//ポリゴンの描画
					pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntDraw * 4, 2);
				}
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

//-------------------------------------------
//スコアの設定処理
//-------------------------------------------
void SetScore(int nOrder,int nScore)
{
	//得点を追加
	g_nScore[nOrder] = nScore;

	//テクスチャ分割
	g_aPosTexU[nOrder][0] = g_nScore[nOrder] % 100 / 10;
	g_aPosTexU[nOrder][1] = g_nScore[nOrder] % 10 / 1;
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore[2]->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		for (int nCntX = 0; nCntX < NUM_SCORE; nCntX++)
		{
			pVtx[0].tex = D3DXVECTOR2(0.1f * g_aPosTexU[nCntScore][nCntX], 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f * g_aPosTexU[nCntScore][nCntX] + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.1f * g_aPosTexU[nCntScore][nCntX], 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f * g_aPosTexU[nCntScore][nCntX] + 0.1f, 1.0f);

			pVtx += 4;		//データを4つ分進める
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore[2]->Unlock();
}

//-----------------------------------------------------------------
//
//スコアの加算処理
//int order→ポイント はいるのが1Pの場合0を指定、2Pの場合1を指定
//int nValue→加算される点数を指定
//
//----------------------------------------------------------------
void AddScore(int order, int nValue)
{
	//得点を追加
	g_nScore[order] += nValue;

	//テクスチャ分割
	g_aPosTexU[order][0] = g_nScore[order] % 100 / 10;
	g_aPosTexU[order][1] = g_nScore[order] % 10 / 1;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore[2]->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		for (int nCntX = 0; nCntX < NUM_SCORE; nCntX++)
		{
			pVtx[0].tex = D3DXVECTOR2(0.1f * g_aPosTexU[nCntScore][nCntX], 0.0f);
			pVtx[1].tex = D3DXVECTOR2((0.1f * g_aPosTexU[nCntScore][nCntX]) + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.1f * g_aPosTexU[nCntScore][nCntX], 1.0f);
			pVtx[3].tex = D3DXVECTOR2((0.1f * g_aPosTexU[nCntScore][nCntX]) + 0.1f, 1.0f);

			pVtx += 4;		//データ4つ分進める
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore[2]->Unlock();
}

//-----------------------------------------------------------------
//
//スコアの取得処理
//int △△ = GetScore();で呼び出し、
//△△++;で2Pのスコアも取得できる
//
//----------------------------------------------------------------
int GetScore(int order)
{
	return g_nScore[order];
}