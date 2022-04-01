//-------------------------------------------
//
//お菓子情報[sweet.cpp]
//Author:平野舞
//
//-------------------------------------------

//インクルードファイル
#include "sweet.h"
#include "fade.h"

//グローバル宣言
LPDIRECT3DTEXTURE9 g_pTextureSweet = NULL;			//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSweet = NULL;		//頂点バッファへのポインタ
Sweet g_Sweet[MAX_SWEET];							//アイテムの情報
int g_nSweetNumber;									//カウンター
int g_nSweetFade;									//画面遷移用カウンター

//-------------------------------------------
//お菓子の初期化処理
//-------------------------------------------
void InitSweet(void)
{
	int nCntSweet;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Sweet000.png",
		&g_pTextureSweet);

	for (nCntSweet = 0; nCntSweet < MAX_SWEET; nCntSweet++)
	{
		g_Sweet[nCntSweet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//位置
		g_Sweet[nCntSweet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
		g_Sweet[nCntSweet].bUse = false;								//使用するかしないか
	}
	g_nSweetNumber = 0;
	g_nSweetFade = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SWEET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSweet,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffSweet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntSweet = 0; nCntSweet < MAX_SWEET; nCntSweet++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_Sweet[nCntSweet].pos.x - (SWEET_WIDTH / 2), g_Sweet[nCntSweet].pos.y - SWEET_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Sweet[nCntSweet].pos.x + (SWEET_WIDTH / 2), g_Sweet[nCntSweet].pos.y - SWEET_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Sweet[nCntSweet].pos.x - (SWEET_WIDTH / 2), g_Sweet[nCntSweet].pos.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Sweet[nCntSweet].pos.x + (SWEET_WIDTH / 2), g_Sweet[nCntSweet].pos.y, 0.0f);

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
	g_pVtxBuffSweet->Unlock();

	//お菓子を配置
	for (int nCount = 0; nCount < MAX_SWEET; nCount++)
	{
		SetSweet(D3DXVECTOR3(70.0f, 120.0f + (150.0f * nCount), 0.0f));
	}
}

//-------------------------------------------
//お菓子の終了処理
//-------------------------------------------
void UninitSweet(void)
{
	//テクスチャの破棄
	if (g_pTextureSweet != NULL)
	{
		g_pTextureSweet->Release();
		g_pTextureSweet = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffSweet != NULL)
	{
		g_pVtxBuffSweet->Release();
		g_pVtxBuffSweet = NULL;
	}
}

//-------------------------------------------
//お菓子の更新処理
//-------------------------------------------
void UpdateSweet(void)
{
	if (g_nSweetNumber == MAX_SWEET)
	{
		if (g_nSweetFade == 0)
		{
			g_nSweetFade = 1;
			SetFade(MODE_GAMEOVER);
		}
	}
}

//-------------------------------------------
//お菓子の描画処理
//-------------------------------------------
void DrawSweet(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffSweet, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntSweet = 0; nCntSweet < MAX_SWEET; nCntSweet++)
	{
		if (g_Sweet[nCntSweet].bUse == true)
		{//お菓子が使用されている場合
		 //テクスチャ設定
			pDevice->SetTexture(0, g_pTextureSweet);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntSweet * 4, 2);
		}
	}
}

//-------------------------------------------
//お菓子の設定処理
//-------------------------------------------
void SetSweet(D3DXVECTOR3 pos)
{
	int nCntSweet;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffSweet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntSweet = 0; nCntSweet < MAX_SWEET; nCntSweet++)
	{
		if (g_Sweet[nCntSweet].bUse == false)
		{//お菓子が使用されていない場合
			g_Sweet[nCntSweet].pos = pos;		//位置

												//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_Sweet[nCntSweet].pos.x - (SWEET_WIDTH / 2), g_Sweet[nCntSweet].pos.y - SWEET_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Sweet[nCntSweet].pos.x + (SWEET_WIDTH / 2), g_Sweet[nCntSweet].pos.y - SWEET_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Sweet[nCntSweet].pos.x - (SWEET_WIDTH / 2), g_Sweet[nCntSweet].pos.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Sweet[nCntSweet].pos.x + (SWEET_WIDTH / 2), g_Sweet[nCntSweet].pos.y, 0.0f);

			g_Sweet[nCntSweet].bUse = true;		//使用する
			break;
		}
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffSweet->Unlock();
}

//-------------------------------------------
//お菓子の情報の取得
//-------------------------------------------
Sweet * GetSweet(void)
{
	return &g_Sweet[0];
}

//-------------------------------------------
//お菓子の当たり判定処理
//-------------------------------------------
void CollisionSweet(D3DXVECTOR3 * pPos, float fWidth, float fHeigtht)
{
	int nCntSweet;

	for (nCntSweet = 0; nCntSweet < MAX_SWEET; nCntSweet++)
	{
		if (g_Sweet[nCntSweet].bUse == true)
		{//アイテムを使っているとき
			if (pPos->x + (fWidth / 2.0f) >= g_Sweet[nCntSweet].pos.x - (SWEET_WIDTH / 2)
				&& pPos->x - (fWidth / 2.0f) <= g_Sweet[nCntSweet].pos.x + (SWEET_WIDTH / 2)
				&& pPos->y + (fHeigtht / 2.0f) >= g_Sweet[nCntSweet].pos.y - SWEET_HEIGHT
				&& pPos->y - (fHeigtht / 2.0f) <= g_Sweet[nCntSweet].pos.y)
			{
				g_Sweet[nCntSweet].bUse = false;		//使用しない
				g_nSweetNumber++;						//カウンターを増やす
			}
		}
	}
}