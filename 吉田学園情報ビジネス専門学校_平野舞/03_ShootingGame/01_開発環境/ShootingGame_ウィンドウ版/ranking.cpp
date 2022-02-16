//-------------------------------------------
//
//ランキング処理[ranking.cpp](未完成)
//Author:平野舞
//
//-------------------------------------------
#include "ranking.h"

//ランキング構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	int nScore;			//スコア
}RankScore;

//マクロ定義
#define RANKING_WIDTH			(50)		//順位の幅
#define RANKING_HEIGHT			(100)		//順位の高さ
#define RANKINGSCORE_WIDTH		(50)		//スコアの幅
#define RANKINGSCORE_HEIGHT		(100)		//スコアの高さ

//グローバル宣言
LPDIRECT3DTEXTURE9 g_pTextureRank = NULL;				//テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureRankScore = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;			//頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankScore = NULL;		//頂点バッファへのポインタ
RankScore g_aRankScore[MAX_RANK];						//ランキングスコア情報
int g_nRankUpdata = -1;									//更新ランクNo.
int g_nTimerRanking;									//ランキング画面表示タイマー

//-------------------------------------------
//初期化処理
//-------------------------------------------
void InitRanking(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ranking_rank.png",
		&g_pTextureRank);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRank,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(100 - RANKINGSCORE_WIDTH, 50 - RANKING_HEIGHT, 0);
	pVtx[1].pos = D3DXVECTOR3(100 + RANKINGSCORE_WIDTH, 50 - RANKING_HEIGHT, 0);
	pVtx[2].pos = D3DXVECTOR3(100 - RANKINGSCORE_WIDTH, 50 + RANKING_HEIGHT, 0);
	pVtx[3].pos = D3DXVECTOR3(100 + RANKINGSCORE_WIDTH, 50 + RANKING_HEIGHT, 0);

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
	g_pVtxBuffRank->Unlock();

	////テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice,
	//	"data/TEXTURE/number000.png",
	//	&g_pTextureRankScore);

	////頂点バッファの生成
	//pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
	//	D3DUSAGE_WRITEONLY,
	//	FVF_VERTEX_2D,
	//	D3DPOOL_MANAGED,
	//	&g_pVtxBuffRankScore,
	//	NULL);

	////頂点情報へのポインタ
	//VERTEX_2D *pVtx;

	////頂点バッファをロックし、頂点情報へのポインタを取得
	//g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

	////頂点座標の設定
	//pVtx[0].pos = D3DXVECTOR3(500 - RANKING_WIDTH, 50 - RANKINGSCORE_HEIGHT, 0);
	//pVtx[1].pos = D3DXVECTOR3(500 + RANKING_WIDTH, 50 - RANKINGSCORE_HEIGHT, 0);
	//pVtx[2].pos = D3DXVECTOR3(500 - RANKING_WIDTH, 50 + RANKINGSCORE_HEIGHT, 0);
	//pVtx[3].pos = D3DXVECTOR3(500 + RANKING_WIDTH, 50 + RANKINGSCORE_HEIGHT, 0);

	////rhwの設定
	//pVtx[0].rhw = 1.0f;
	//pVtx[1].rhw = 1.0f;
	//pVtx[2].rhw = 1.0f;
	//pVtx[3].rhw = 1.0f;

	////頂点カラーの設定
	//pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	////テクスチャ座標の設定
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	////頂点バッファをアンロックする
	//g_pVtxBuffRankScore ->Unlock();

}

//-------------------------------------------
//終了処理
//-------------------------------------------
void UninitRanking(void)
{
	//テクスチャの破棄
	if (g_pTextureRank != NULL)
	{
		g_pTextureRank->Release();
		g_pTextureRank = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffRank != NULL)
	{
		g_pVtxBuffRank->Release();
		g_pVtxBuffRank = NULL;
	}

	////テクスチャの破棄
	//if (g_pTextureRankScore != NULL)
	//{
	//	g_pTextureRankScore->Release();
	//	g_pTextureRankScore = NULL;
	//}

	////頂点バッファの破棄
	//if (g_pVtxBuffRankScore != NULL)
	//{
	//	g_pVtxBuffRankScore->Release();
	//	g_pVtxBuffRankScore = NULL;
	//}
}

//-------------------------------------------
//更新処理
//-------------------------------------------
void UpdateRanking(void)
{
	if (g_nRankUpdata != -1)
	{

	}
	//if ()
	{

	}
}

//-------------------------------------------
//描画処理
//-------------------------------------------
void DrawRanking(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureRank);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//-------------------------------------------
//ランキングのリセット
//-------------------------------------------
void ResetRanking(void)
{

}

//-------------------------------------------
//ランキングの設定
//-------------------------------------------
void SetRanking(int nScore)
{
	int nCntRank;

	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{

	}
}
