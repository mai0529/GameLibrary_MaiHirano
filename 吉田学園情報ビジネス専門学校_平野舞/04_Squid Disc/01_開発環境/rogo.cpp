//============================================================
//
// 3D制作　勝敗ロゴ[Rogo.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include"score.h"
#include"result.h"
#include"rogo.h"
//============================================================
//グローバル変数
//============================================================
LPDIRECT3DTEXTURE9 g_apTextureRogo[NUM_Rogo] = { NULL };	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRogo = NULL;			//頂点バッファポインタ
Rogo g_aRogo[MAX_Rogo];								//敵の情報
int WinScore[2];
//ロゴの取得
Rogo*GetRogo(void)
{
	return &g_aRogo[0];
}

//============================================================
//勝敗ロゴの初期化処理
//============================================================
void lnitRogo(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntRogo;


	//カウンターの初期化
	nCntRogo = 0;

	//デバイスの取得
	pDevice = GetDevice();


	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/WIN.png",
		&g_apTextureRogo[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/LOSE.png",
		&g_apTextureRogo[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Drow.png",
		&g_apTextureRogo[2]);

	//鳥の初期化
	for (nCntRogo = 0; nCntRogo < MAX_Rogo; nCntRogo++)
	{
		g_aRogo[nCntRogo].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRogo[nCntRogo].nType = 0;
		g_aRogo[nCntRogo].bUse = false;
	}

	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_Rogo * NUM_Rogo,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRogo,
		NULL);


	VERTEX_2D*pVtx;		//頂点情報へポインタ

						//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffRogo->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntRogo = 0; nCntRogo < MAX_Rogo; nCntRogo++)
	{

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの描画
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


		pVtx += 4;
	}
	//頂点バッファアンロック
	g_pVtxBuffRogo->Unlock();

	WinScore[0] = GetScore(0);
	WinScore[1] = GetScore(1);
	InitScore();

}

//============================================================
//勝敗ロゴの処理処理
//============================================================
void UninitRogo(void)
{
	UninitScore();

	int nCntRogo;

	for (nCntRogo = 0; nCntRogo < NUM_Rogo; nCntRogo++)
	{ //テクスチャの破棄
		if (g_apTextureRogo[nCntRogo] != NULL)
		{
			g_apTextureRogo[nCntRogo]->Release();
			g_apTextureRogo[nCntRogo] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffRogo != NULL)
	{
		g_pVtxBuffRogo->Release();
		g_pVtxBuffRogo = NULL;
	}

}
//============================================================
//勝敗ロゴの更新処理
//============================================================
void UpdateRogo(void)
{
	UpdateScore();

	int nCntRogo;
	VERTEX_2D*pVtx;
	//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffRogo->Lock(0, 0, (void**)&pVtx, 0);



	//勝敗を確認し表示する
	if (WinScore[0] > WinScore[1])
	{//1Pが勝利
		SetRogo(D3DXVECTOR3(100, 70.0f, 0.0f), 0);
		SetRogo(D3DXVECTOR3(800, 70.0f, 0.0f), 1);
	}

	 if (WinScore[0]<WinScore[1])
	{//2Pが勝利
		SetRogo(D3DXVECTOR3(100, 70.0f, 0.0f), 1);
		SetRogo(D3DXVECTOR3(800, 70.0f, 0.0f), 0);
	}

	if (WinScore[0] == WinScore[1])
	{//引き分け
		SetRogo(D3DXVECTOR3(640, 440.0f, 0.0f), 2);
	}

	for (nCntRogo = 0; nCntRogo < MAX_Rogo; nCntRogo++)
	{
		if (g_aRogo[nCntRogo].bUse == true)
		{

			//頂点座標の更新(ロゴの大きさ)
			pVtx[0].pos = D3DXVECTOR3(g_aRogo[nCntRogo].pos.x - Rogo_SIZE / 2, g_aRogo[nCntRogo].pos.y - Rogo_SIZE / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aRogo[nCntRogo].pos.x + Rogo_SIZE / 2, g_aRogo[nCntRogo].pos.y - Rogo_SIZE / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aRogo[nCntRogo].pos.x - Rogo_SIZE / 2, g_aRogo[nCntRogo].pos.y + Rogo_SIZE / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aRogo[nCntRogo].pos.x + Rogo_SIZE / 2, g_aRogo[nCntRogo].pos.y + Rogo_SIZE / 2, 0.0f);

		}
		pVtx += 4;//ポインタを４つ分進める
	}
	//頂点バッファアンロック
	g_pVtxBuffRogo->Unlock();
}

//============================================================
//勝敗ロゴ描画処理
//============================================================
void DrawRogo(void)
{
	DrawScore();

	LPDIRECT3DDEVICE9 pDevice;
	int nCntRogo;
	
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRogo, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (nCntRogo = 0; nCntRogo < MAX_Rogo; nCntRogo++)
	{
		if (g_aRogo[nCntRogo].bUse == true)
		{//敵が使用されている

		 //テクスチャの設定
			pDevice->SetTexture(0, g_apTextureRogo[g_aRogo[nCntRogo].nType]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntRogo * 4, 2);
		}
	}
}

//============================================================
//勝敗ロゴの設定処理
//============================================================
void SetRogo(D3DXVECTOR3 pos, int nType)
{
	int nCntRogo;

	VERTEX_2D*pVtx;

	//頂点バッファロックし、頂点情報へポインタ取得
	g_pVtxBuffRogo->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntRogo = 0; nCntRogo < MAX_Rogo; nCntRogo++)
	{
		if (g_aRogo[nCntRogo].bUse == false)
		{//敵が使用されてない場合

		 //敵の情報の設定
			g_aRogo[nCntRogo].pos = pos;

			//頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(g_aRogo[nCntRogo].pos.x - 6.0f, g_aRogo[nCntRogo].pos.y - 6.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aRogo[nCntRogo].pos.x + 6.0f, g_aRogo[nCntRogo].pos.y - 6.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aRogo[nCntRogo].pos.x - 6.0f, g_aRogo[nCntRogo].pos.y + 6.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aRogo[nCntRogo].pos.x + 6.0f, g_aRogo[nCntRogo].pos.y + 6.0f, 0.0f);


			//頂点カラーの描画
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_aRogo[nCntRogo].bUse = true;	//使用している状態にする
			g_aRogo[nCntRogo].nType = nType;

			break;
		}
		pVtx += 4;//ポインタを４つ分進める
	}
	g_pVtxBuffRogo->Unlock();
}
