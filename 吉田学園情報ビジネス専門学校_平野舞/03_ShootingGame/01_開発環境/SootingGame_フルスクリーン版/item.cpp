//-------------------------------------------
//
//アイテム情報[item.cpp]
//Author:平野舞
//
//-------------------------------------------

//インクルードファイル
#include "item.h"

//グローバル宣言
LPDIRECT3DTEXTURE9 g_pTextureItem[NUM_ITEM] = {};			//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;				//頂点バッファへのポインタ
Item g_Item[MAX_ITEM];										//アイテムの情報
int g_nItemNumber;

//-------------------------------------------
//アイテムの初期化処理
//-------------------------------------------
void InitItem(void) 
{
	int nCntItem;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/item003.png",
		&g_pTextureItem[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/item001.png",
		&g_pTextureItem[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/item002.png",
		&g_pTextureItem[2]);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_Item[nCntItem].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);			//位置
		g_Item[nCntItem].PosOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//前回の位置
		g_Item[nCntItem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
		g_Item[nCntItem].fWidth = 0.0f;								//幅
		g_Item[nCntItem].fHeigth = 0.0f;							//高さ
		g_Item[nCntItem].nType = ITEM_CANDY;						//種類
		g_Item[nCntItem].bUse = false;								//使用するかしないか
	}
	g_nItemNumber = 0;

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

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x - (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y - ITEM_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x + (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y - ITEM_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x - (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x + (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y, 0.0f);

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

		pVtx += 4;		//頂点データを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();

	SetItem(D3DXVECTOR3(1740.0f, 200.0f, 0.0f), ITEM_CAKE);
	SetItem(D3DXVECTOR3(2665.0f, 150.0f, 0.0f), ITEM_CAKE);
}

//-------------------------------------------
//アイテムの終了処理
//-------------------------------------------
void UninitItem(void)
{
	int nCntItem;

	for (nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
	{
		//テクスチャの破棄
		if (g_pTextureItem[nCntItem] != NULL)
		{
			g_pTextureItem[nCntItem]->Release();
			g_pTextureItem[nCntItem] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//-------------------------------------------
//アイテムの更新処理
//-------------------------------------------
void UpdateItem(void)
{
	int nCntItem;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_Item[nCntItem].bUse == true)
		{
			//前回の位置を更新
			g_Item[nCntItem].PosOld = g_Item[nCntItem].pos;

			//重力
			g_Item[nCntItem].move.y += ITEM_G;

			//位置を更新
			g_Item[nCntItem].pos.x += g_Item[nCntItem].move.x;
			g_Item[nCntItem].pos.y += g_Item[nCntItem].move.y;

			//ブロックとの当たり判定
			CollisionBlock(&g_Item[nCntItem].pos, &g_Item[nCntItem].PosOld, &g_Item[nCntItem].move, (ITEM_WIDTH / 2),ITEM_HEIGHT);

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x - (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y - ITEM_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x + (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y - ITEM_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x - (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x + (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y, 0.0f);
		}
		pVtx += 4;		//頂点データを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}

//-------------------------------------------
//アイテムの描画処理
//-------------------------------------------
void DrawItem(void)
{
	int nCntItem;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_Item[nCntItem].bUse == true)
		{//ブロックが使用されている場合
		 //テクスチャ設定
			pDevice->SetTexture(0, g_pTextureItem[g_Item[nCntItem].nType]);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, 2);
		}
	}
}

//-------------------------------------------
//アイテムの設定処理
//-------------------------------------------
void SetItem(D3DXVECTOR3 pos, ITEM nType)
{
	int nCntItem;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_Item[nCntItem].bUse == false)
		{//ブロックが使用されていない場合
			g_Item[nCntItem].pos = pos;
			g_Item[nCntItem].nType = nType;
			g_Item[nCntItem].bUse = true;
			break;
		}
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}

//-------------------------------------------
//アイテムの取得
//-------------------------------------------
Item * GetItem(void)
{
	return g_Item;
}

//-------------------------------------------
//アイテムの当たり判定処理
//-------------------------------------------
void CollisionItem(D3DXVECTOR3 * pPos, float fWidth, float fHeigtht)
{
	int nCntItem;

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_Item[nCntItem].bUse == true)
		{//アイテムを使っているとき
			if (pPos->x + (fWidth / 2) >= g_Item[nCntItem].pos.x - (ITEM_WIDTH / 2)
				&& pPos->x - (fWidth / 2) <= g_Item[nCntItem].pos.x + (ITEM_WIDTH / 2)
				&& pPos->y >= g_Item[nCntItem].pos.y - ITEM_HEIGHT
				&& pPos->y - fHeigtht <= g_Item[nCntItem].pos.y)
			{
				//サウンドの再生
				PlaySound(SOUND_LABEL_SE_ITEM);
				DeleteItem(nCntItem);
			}
		}
	}
}

//-------------------------------------------
//アイテム種類別処理
//-------------------------------------------
void DeleteItem(int nCntItem)
{
	Player *pPlayer = GetPlayer();
	Life *pLife = GetLife();

	if (g_Item[nCntItem].nType == ITEM_CANDY)
	{//飴
		AddScore(350);
	}
	else if (g_Item[nCntItem].nType == ITEM_POTION )
	{//回復薬
		pPlayer->nLife += 1;
		for (int nCount = 0; nCount < MAX_LIFE; nCount++, pLife++)
		{
			if (pLife->bUse == false)
			{
				pLife->bUse = true;
				break;
			}
		}
	}
	else if (g_Item[nCntItem].nType == ITEM_CAKE)
	{//ケーキ
		AddScore(777);
		g_nItemNumber++;
	}

	if (g_nItemNumber == 5)
	{//ケーキを全部取ったら
		AddScore(2000);
	}

	//演出
	SetExplosion(D3DXVECTOR3(g_Item[nCntItem].pos.x, g_Item[nCntItem].pos.y - (ITEM_HEIGHT / 2), 0.0f), D3DXCOLOR(0.7f, 0.4f, 0.4f, 0.7f));

	//アイテムを非表示にする
	g_Item[nCntItem].bUse = false;
}

//-------------------------------------------
//ケーキの数を取得
//-------------------------------------------
int GetnCount(void)
{
	return g_nItemNumber;
}