//-------------------------------------------
//
//アイテム処理[item.cpp]
//Author:平野舞
//
//-------------------------------------------

//インクルードファイル
#include "item.h"
#include "score.h"
#include "time.h"

//マクロ定義
#define MAX_ITEM		(8)			//アイテムの最大数
#define ITEM_WIDTH		(80.0f)		//アイテムの幅
#define ITEM_HEIGHT		(60.0f)		//アイテムの高さ

//グローバル宣言
LPDIRECT3DTEXTURE9 g_pTextureItem = NULL;			//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;		//頂点バッファへのポインタ
Item g_item[MAX_ITEM];								//アイテムの情報
int g_nItemScore;									//スコアUP
bool g_bCollisionItem;								//当たったかどうか
int g_nTimeItem;

//-------------------------------------------
//初期化処理
//-------------------------------------------
void InitItem(void)
{
	//現在時刻をシード(種)にする
	srand((unsigned int)time(NULL));

	//初期化処理
		for (int nCount = 0; nCount < MAX_ITEM; nCount++)
		{
			g_item[nCount].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
			g_item[nCount].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量
			g_item[nCount].bUse = false;							//使用しない
		}
		g_nItemScore = 0;											//スコアUP
		g_bCollisionItem = false;									//当たっていない
		g_nTimeItem = rand() % 30 + 30;

		//デバイスへのポインタ
		LPDIRECT3DDEVICE9 pDevice;

		//デバイスの取得
		pDevice = GetDevice();

		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data/TEXTURE/item000.png",
			&g_pTextureItem);

		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffItem,
			NULL);

		//頂点情報へのポインタ
		VERTEX_2D *pVtx;

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
		{
			//頂点座標の設定
			pVtx[2].pos = D3DXVECTOR3(g_item[nCntItem].pos.x - (ITEM_WIDTH / 2.0f), g_item[nCntItem].pos.y + (ITEM_HEIGHT / 2.0f), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_item[nCntItem].pos.x + (ITEM_WIDTH / 2.0f), g_item[nCntItem].pos.y + (ITEM_HEIGHT / 2.0f), 0.0f);
			pVtx[0].pos = D3DXVECTOR3(g_item[nCntItem].pos.x - (ITEM_WIDTH / 2.0f), g_item[nCntItem].pos.y - (ITEM_HEIGHT / 2.0f), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_item[nCntItem].pos.x + (ITEM_WIDTH / 2.0f), g_item[nCntItem].pos.y - (ITEM_HEIGHT / 2.0f), 0.0f);

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
		}

		//頂点バッファをアンロックする
		g_pVtxBuffItem->Unlock();		
}

//-------------------------------------------
//終了処理
//-------------------------------------------
void UninitItem(void)
{
	//テクスチャの破棄
	if (g_pTextureItem != NULL)
	{
		g_pTextureItem->Release();
		g_pTextureItem = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//-------------------------------------------
//更新処理
//-------------------------------------------
void UpdateItem(void)
{
	//タイムを獲得
	int nGetTime = GetTime();

	//現在時刻をシード(種)にする
	srand((unsigned int)time(NULL));

	int nPosY = rand() % 600 + 50;

	if (nGetTime == g_nTimeItem)
	{
		//アイテムの設定
		SetItem(D3DXVECTOR3(1300.0f, nPosY, 0.0f));
	}

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntObs = 0; nCntObs < MAX_ITEM; nCntObs++)
	{
		if (g_item[nCntObs].bUse == true)
		{
			//位置情報の更新
			g_item[nCntObs].move.x = 3.0f;
			g_item[nCntObs].pos.x -= g_item[nCntObs].move.x;

			//頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(g_item[nCntObs].pos.x - (ITEM_WIDTH / 2.0f), g_item[nCntObs].pos.y - (ITEM_HEIGHT / 2.0f), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_item[nCntObs].pos.x + (ITEM_WIDTH / 2.0f), g_item[nCntObs].pos.y - (ITEM_HEIGHT / 2.0f), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_item[nCntObs].pos.x - (ITEM_WIDTH / 2.0f), g_item[nCntObs].pos.y + (ITEM_HEIGHT / 2.0f), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_item[nCntObs].pos.x + (ITEM_WIDTH / 2.0f), g_item[nCntObs].pos.y + (ITEM_HEIGHT / 2.0f), 0.0f);

			if (g_item[nCntObs].pos.x < 0)
			{//画面外に出たら
				g_item[nCntObs].bUse = false;
			}
		}
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}

//-------------------------------------------
//描画処理
//-------------------------------------------
void DrawItem(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_item[nCntItem].bUse == true)
		{//敵が使用されている場合
		 //テクスチャ設定
			pDevice->SetTexture(0, g_pTextureItem);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, 2);
		}
	}
}

//-------------------------------------------
//設定処理
//-------------------------------------------
void SetItem(D3DXVECTOR3 pos)
{
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_item[nCntItem].bUse == false)
		{//障害物が使用されていない場合
			g_item[nCntItem].pos = pos;		//位置
			g_item[nCntItem].bUse = true;	//使用する

			break;
		}
	}
}

//-------------------------------------------
//当たり判定処理
//-------------------------------------------
void CollisionItem(D3DXVECTOR3 * pPos, float fWidth, float fHeigtht)
{
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_item[nCntItem].bUse == true)
		{//障害物を使っているとき
			if (pPos->x + (fWidth / 2.0f) >= g_item[nCntItem].pos.x - (ITEM_WIDTH / 2.0f)
				&& pPos->x - (fWidth / 2.0f) <= g_item[nCntItem].pos.x + (ITEM_WIDTH / 2.0f)
				&& pPos->y + (fHeigtht / 2.0f) >= g_item[nCntItem].pos.y - (ITEM_HEIGHT / 2.0f)
				&& pPos->y - (fHeigtht / 2.0f) <= g_item[nCntItem].pos.y + (ITEM_HEIGHT / 2.0f))
			{
				if (g_bCollisionItem == false)
				{
					g_item[nCntItem].bUse = false;		//使用しない
					g_nItemScore += 100;				//スコア100UP
					g_bCollisionItem = true;			//当たった
				}
			}
		}
	}

	//g_bCollisionItem = false;		//保留
}

//-------------------------------------------
//スコアアップアイテムの取得処理
//-------------------------------------------
int GetScoreUpItem(void)
{
	return g_nItemScore;
}