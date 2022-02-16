//-------------------------------------------
//
//炎情報[flame.cpp]
//Author:平野舞
//
//-------------------------------------------

//インクルードファイル
#include "flame.h"

//グローバル宣言
LPDIRECT3DTEXTURE9 g_pTextureFlame = NULL;				//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFlame = NULL;			//頂点バッファへのポインタ
Flame g_aFlame[MAX_FLAME];								//アイテムの情報

//-------------------------------------------
//炎の初期化処理
//-------------------------------------------
void InitFlame(void)
{
	int nCntFlame;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/light000.png",
		&g_pTextureFlame);

	for (nCntFlame = 0; nCntFlame < MAX_FLAME; nCntFlame++)
	{
		g_aFlame[nCntFlame].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
		g_aFlame[nCntFlame].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
		g_aFlame[nCntFlame].nNumber =0;									//何番目か
		g_aFlame[nCntFlame].bUse = false;								//使用するかしないか
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_FLAME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFlame,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffFlame->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntFlame = 0; nCntFlame < MAX_FLAME; nCntFlame++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aFlame[nCntFlame].pos.x - (FLAME_WIDTH / 2), g_aFlame[nCntFlame].pos.y - (FLAME_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aFlame[nCntFlame].pos.x + (FLAME_WIDTH / 2), g_aFlame[nCntFlame].pos.y - (FLAME_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aFlame[nCntFlame].pos.x - (FLAME_WIDTH / 2), g_aFlame[nCntFlame].pos.y + (FLAME_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aFlame[nCntFlame].pos.x + (FLAME_WIDTH / 2), g_aFlame[nCntFlame].pos.y + (FLAME_HEIGHT / 2), 0.0f);

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
	g_pVtxBuffFlame->Unlock();

	SetFlame(D3DXVECTOR3(50.0f,  0.0f, 0.0f),D3DXVECTOR3(1.2f,1.0f,0.0f),0);
	SetFlame(D3DXVECTOR3(200.0f, 0.0f, 0.0f),D3DXVECTOR3(0.5f,0.8f,0.0f),0);
	SetFlame(D3DXVECTOR3(400.0f, 0.0f, 0.0f),D3DXVECTOR3(1.5f,1.2f,0.0f), 0);
	SetFlame(D3DXVECTOR3(1530.0f,0.0f, 0.0f),D3DXVECTOR3(-0.4f,0.3f,0.0f),0);
	SetFlame(D3DXVECTOR3(1750.0f,0.0f, 0.0f),D3DXVECTOR3(-0.7f,0.5f,0.0f),0);
	SetFlame(D3DXVECTOR3(2030.0f,0.0f, 0.0f),D3DXVECTOR3(-0.3f,0.4f, 0.0f), 0);
	SetFlame(D3DXVECTOR3(3010.0f,0.0f, 0.0f),D3DXVECTOR3(-0.8f,0.8f, 0.0f), 0);
	SetFlame(D3DXVECTOR3(4570.0f,0.0f, 0.0f),D3DXVECTOR3(-0.4f,0.2f, 0.0f), 0);
	SetFlame(D3DXVECTOR3(5940.0f,0.0f, 0.0f),D3DXVECTOR3(-0.5f,0.3f, 0.0f), 0);
	SetFlame(D3DXVECTOR3(6340.0f,0.0f, 0.0f),D3DXVECTOR3(-0.4f,0.2f, 0.0f), 0);
	SetFlame(D3DXVECTOR3(7140.0f,0.0f, 0.0f),D3DXVECTOR3(-0.3f,0.2f,0.0f),0);
	SetFlame(D3DXVECTOR3(8480.0f,395.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),1);
}

//-------------------------------------------
//炎の終了処理
//-------------------------------------------
void UninitFlame(void)
{
	//テクスチャの破棄
	if (g_pTextureFlame != NULL)
	{
		g_pTextureFlame->Release();
		g_pTextureFlame = NULL;
	}


	//頂点バッファの破棄
	if (g_pVtxBuffFlame != NULL)
	{
		g_pVtxBuffFlame->Release();
		g_pVtxBuffFlame = NULL;
	}
}

//-------------------------------------------
//炎の更新処理
//-------------------------------------------
void UpdateFlame(void)
{
	int nCntFlame;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffFlame->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntFlame = 0; nCntFlame < MAX_FLAME; nCntFlame++)
	{
		if (g_aFlame[nCntFlame].bUse == true)
		{
			//位置を更新
			g_aFlame[nCntFlame].pos.x += g_aFlame[nCntFlame].move.x;
			g_aFlame[nCntFlame].pos.y += g_aFlame[nCntFlame].move.y;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aFlame[nCntFlame].pos.x - (FLAME_WIDTH / 2), g_aFlame[nCntFlame].pos.y - (FLAME_HEIGHT / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aFlame[nCntFlame].pos.x + (FLAME_WIDTH / 2), g_aFlame[nCntFlame].pos.y - (FLAME_HEIGHT / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aFlame[nCntFlame].pos.x - (FLAME_WIDTH / 2), g_aFlame[nCntFlame].pos.y + (FLAME_HEIGHT / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aFlame[nCntFlame].pos.x + (FLAME_WIDTH / 2), g_aFlame[nCntFlame].pos.y + (FLAME_HEIGHT / 2), 0.0f);

		}
		pVtx += 4;		//頂点データを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffFlame->Unlock();
}

//-------------------------------------------
//アイテムの描画処理
//-------------------------------------------
void DrawFlame(void)
{
	int nCntFlame;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffFlame, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureFlame);

	for (nCntFlame = 0; nCntFlame < MAX_FLAME; nCntFlame++)
	{
		if (g_aFlame[nCntFlame].bUse == true)
		{
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntFlame * 4, 2);
		}
	}
}

//-------------------------------------------
//炎の設定処理
//-------------------------------------------
void SetFlame(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nNumber)
{
	int nCntFlame;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffFlame->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntFlame = 0; nCntFlame < MAX_FLAME; nCntFlame++)
	{
		if (g_aFlame[nCntFlame].bUse == false)
		{//ブロックが使用されていない場合
			g_aFlame[nCntFlame].pos = pos;
			g_aFlame[nCntFlame].move = move;
			g_aFlame[nCntFlame].nNumber = nNumber;
			g_aFlame[nCntFlame].bUse = true;
			break;
		}
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffFlame->Unlock();
}

//-------------------------------------------
//炎の当たり判定処理
//-------------------------------------------
void CollisionFlame(D3DXVECTOR3 * pPos, float fWidth, float fHeigtht)
{
	int nCntFlame;

	for (nCntFlame = 0; nCntFlame < MAX_FLAME; nCntFlame++)
	{
		if (g_aFlame[nCntFlame].bUse == true)
		{//炎を使っているとき
			if (pPos->x + (fWidth / 2) >= g_aFlame[nCntFlame].pos.x - (FLAME_WIDTH / 2)
				&& pPos->x - (fWidth / 2) <= g_aFlame[nCntFlame].pos.x + (FLAME_WIDTH / 2)
				&& pPos->y >= g_aFlame[nCntFlame].pos.y - (FLAME_HEIGHT / 2)
				&& pPos->y - fHeigtht <= g_aFlame[nCntFlame].pos.y + (FLAME_HEIGHT / 2))
			{
				if (g_aFlame[nCntFlame].nNumber == 1)
				{
					SetItem(D3DXVECTOR3(g_aFlame[nCntFlame].pos.x, g_aFlame[nCntFlame].pos.y, 0.0f), ITEM_CAKE);
				}
				else
				{
					SetItem(D3DXVECTOR3(g_aFlame[nCntFlame].pos.x, g_aFlame[nCntFlame].pos.y, 0.0f), ITEM_CANDY);
				}
				g_aFlame[nCntFlame].bUse = false;
			}
		}
	}
}

//-------------------------------------------
//炎の取得
//-------------------------------------------
Flame *GetFlame(void)
{
	return &g_aFlame[0];
}