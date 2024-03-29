//-------------------------------------------
//
//リザルト処理[result.cpp]
//Author:平野舞
//
//-------------------------------------------

//インクルードファイル
#include "result.h"
#include "controller.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureResult[2] = {};			//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult[3] = {};		//頂点バッファへのポインタ
D3DXVECTOR3 g_posRank[8];								//スコアの位置
Result g_nResult;										//スコアの値

//-------------------------------------------
//初期化処理
//-------------------------------------------
void InitResult(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/result007.jpg",
		&g_pTextureResult[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number001.png",
		&g_pTextureResult[1]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult[0],
		NULL);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult[1],
		NULL);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult[2],
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//背景
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResult[0]->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffResult[0]->Unlock();

	//スコア
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResult[1]->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < 8; nCount++)
	{//スコアの設置
		g_posRank[nCount] = D3DXVECTOR3(450.0f + (70.0f * nCount), 260.0f, 0.0f);
	}

	for (int nCount = 0; nCount < 8; nCount++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_posRank[nCount].x - (RESULT_WIDTH / 2), g_posRank[nCount].y - (RESULT_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posRank[nCount].x + (RESULT_WIDTH / 2), g_posRank[nCount].y - (RESULT_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posRank[nCount].x - (RESULT_WIDTH / 2), g_posRank[nCount].y + (RESULT_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posRank[nCount].x + (RESULT_WIDTH / 2), g_posRank[nCount].y + (RESULT_HEIGHT / 2), 0.0f);

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
	g_pVtxBuffResult[1]->Unlock();

	//ケーキ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResult[2]->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(700.0f - (RESULT_WIDTH / 2.0f), 500.0f - (RESULT_HEIGHT / 2.0f), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(700.0f + (RESULT_WIDTH / 2.0f), 500.0f - (RESULT_HEIGHT / 2.0f), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(700.0f - (RESULT_WIDTH / 2.0f), 500.0f + (RESULT_HEIGHT / 2.0f), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(700.0f + (RESULT_WIDTH / 2.0f), 500.0f + (RESULT_HEIGHT / 2.0f), 0.0f);

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

	//頂点バッファをアンロックする
	g_pVtxBuffResult[2]->Unlock();

	SetResult();

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM002);
}

//-------------------------------------------
//終了処理
//-------------------------------------------
void UninitResult(void)
{
	//サウンドの停止
	StopSound();

	for (int nCount = 0; nCount < 2 ; nCount++)
	{
		//テクスチャの破棄
		if (g_pTextureResult[nCount] != NULL)
		{
			g_pTextureResult[nCount]->Release();
			g_pTextureResult[nCount] = NULL;
		}
	}

	for (int nCount = 0; nCount < 3; nCount++)
	{
		//頂点バッファの破棄
		if (g_pVtxBuffResult[nCount] != NULL)
		{
			g_pVtxBuffResult[nCount]->Release();
			g_pVtxBuffResult[nCount] = NULL;
		}
	}
}

//-------------------------------------------
//更新処理処理
//-------------------------------------------
void UpdateResult(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) == true || GetControllerPressTrigger(0, XINPUT_GAMEPAD_A))
	{
		PlaySound(SOUND_LABEL_SE000);
		//モード設定
		SetFade(MODE_RANKING);
	}
}

//-------------------------------------------
//描画処理
//-------------------------------------------
void DrawResult(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult[0], 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//背景
	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureResult[0]);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//スコア
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult[1], 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntX = 0; nCntX < 8; nCntX++)
	{
		//テクスチャ設定
		pDevice->SetTexture(0, g_pTextureResult[1]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntX * 4, 2);
	}

	//ケーキ数
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult[2], 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureResult[1]);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//-------------------------------------------
//リセット処理
//-------------------------------------------
void ResetResult(void)
{
	g_nResult.nScore = 0;		//スコアのリセット
	g_nResult.nData = 0;		//ケーキの数のリセット
}

//-------------------------------------------
//設定処理
//-------------------------------------------
void SetResult(void)
{
	//スコアの情報
	g_nResult.nScore = GetScore();
	int aPosTexU[8];

	aPosTexU[0] = g_nResult.nScore % 100000000 / 10000000;
	aPosTexU[1] = g_nResult.nScore % 10000000 / 1000000;
	aPosTexU[2] = g_nResult.nScore % 1000000 / 100000;
	aPosTexU[3] = g_nResult.nScore % 100000 / 10000;
	aPosTexU[4] = g_nResult.nScore % 10000 / 1000;
	aPosTexU[5] = g_nResult.nScore % 1000 / 100;
	aPosTexU[6] = g_nResult.nScore % 100 / 10;
	aPosTexU[7] = g_nResult.nScore % 10 / 1;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResult[1]->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	for (int nCount = 0; nCount < SCORE_MAX; nCount++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[nCount], 0.0f);
		pVtx[1].tex = D3DXVECTOR2((0.1f * aPosTexU[nCount]) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[nCount], 1.0f);
		pVtx[3].tex = D3DXVECTOR2((0.1f * aPosTexU[nCount]) + 0.1f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffResult[1]->Unlock();

	//ケーキの数の情報
	g_nResult.nData = GetnCount();
	int aPosTexU2;

	aPosTexU2 = g_nResult.nData % 10 / 1;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResult[2]->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU2, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((0.1f * aPosTexU2) + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU2, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((0.1f * aPosTexU2) + 0.1f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffResult[2]->Unlock();
}