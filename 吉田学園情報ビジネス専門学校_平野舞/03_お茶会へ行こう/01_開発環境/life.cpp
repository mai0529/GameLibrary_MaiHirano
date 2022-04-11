// ------------------------------------------
//
//ライフ表示処理[life.cpp]
//Author:平野舞
//
//-------------------------------------------

//インクルードファイル
#include "life.h"

//マクロ定義
#define MAX_WIDTH		(70.0f)		//幅
#define MAX_HEIGHT		(28.0f)		//高さ

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_apTextureLife[2] = {};			//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife[2] = {};		//頂点バッファへのポインタ
Life g_aLife;										//ライフ情報

//-------------------------------------------
//初期化処理
//-------------------------------------------
void InitLife(void)
{
	//初期化
		g_aLife.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
		g_aLife.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き
		g_aLife.nMaxLife = 0;								//最大ライフ数
		g_aLife.nNowLife = 0;								//今のライフ数
		g_aLife.bUse = false;								//使用しない

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み(ゲージ)
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/life001.png",
		&g_apTextureLife[0]);

	//テクスチャの読み込み(枠)
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/life000.png",
		&g_apTextureLife[1]);

	for (int nCount = 0; nCount < 2; nCount++)
	{
		//頂点バッファの生成
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffLife[nCount],
			NULL);
	}

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	for (int nCount = 0; nCount < 2; nCount++)
	{
		//頂点バッファをロック
		g_pVtxBuffLife[nCount]->Lock(0, 0, (void**)&pVtx, 0);

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aLife.pos.x - (MAX_WIDTH / 2), g_aLife.pos.y - (MAX_HEIGHT / 2.0f), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aLife.pos.x + (MAX_WIDTH / 2), g_aLife.pos.y - (MAX_HEIGHT / 2.0f), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aLife.pos.x - (MAX_WIDTH / 2), g_aLife.pos.y + (MAX_HEIGHT / 2.0f), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aLife.pos.x + (MAX_WIDTH / 2), g_aLife.pos.y + (MAX_HEIGHT / 2.0f), 0.0f);

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

		//頂点バッファをアンロックする
		g_pVtxBuffLife[nCount]->Unlock();
	}
}

//-------------------------------------------
//終了処理
//-------------------------------------------
void UninitLife(void)
{
	for (int nCntLife = 0; nCntLife < 2; nCntLife++)
	{//テクスチャの破棄
		if (g_apTextureLife[nCntLife] != NULL)
		{
			g_apTextureLife[nCntLife]->Release();
			g_apTextureLife[nCntLife] = NULL;
		}
	}

	for (int nCntLife = 0; nCntLife < 2; nCntLife++)
	{//頂点バッファの破棄
		if (g_pVtxBuffLife[nCntLife] != NULL)
		{
			g_pVtxBuffLife[nCntLife]->Release();
			g_pVtxBuffLife[nCntLife] = NULL;
		}
	}
}

//-------------------------------------------
//更新処理
//-------------------------------------------
void UpdateLife(void)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	for (int nCount = 0; nCount < 2; nCount++)
	{
		//頂点バッファをロック
		g_pVtxBuffLife[nCount]->Lock(0, 0, (void**)&pVtx, 0);

		if (g_aLife.bUse == true)
		{//使用していたら
			//テクスチャ座標の更新
			pVtx[0].tex = D3DXVECTOR2(0.0f + (0.5f / g_aLife.nMaxLife) * (g_aLife.nMaxLife - g_aLife.nNowLife), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.5f + (0.5f / g_aLife.nMaxLife) * (g_aLife.nMaxLife - g_aLife.nNowLife), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (0.5f / g_aLife.nMaxLife) * (g_aLife.nMaxLife - g_aLife.nNowLife), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f + (0.5f / g_aLife.nMaxLife) * (g_aLife.nMaxLife - g_aLife.nNowLife), 1.0f);

			if (g_aLife.nNowLife == 0)
			{//ライフが0になったら
				g_aLife.bUse = false;		//使用しない
			}

			//位置の更新
			pVtx[0].pos = D3DXVECTOR3(g_aLife.pos.x - (MAX_WIDTH / 2), g_aLife.pos.y - (MAX_HEIGHT / 2.0f), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aLife.pos.x + (MAX_WIDTH / 2), g_aLife.pos.y - (MAX_HEIGHT / 2.0f), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aLife.pos.x - (MAX_WIDTH / 2), g_aLife.pos.y + (MAX_HEIGHT / 2.0f), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aLife.pos.x + (MAX_WIDTH / 2), g_aLife.pos.y + (MAX_HEIGHT / 2.0f), 0.0f);

			pVtx += 4;		//頂点データを４つ分進める
		}

		//頂点バッファをアンロックする
		g_pVtxBuffLife[nCount]->Unlock();
	}
}

//-------------------------------------------
//描画処理
//-------------------------------------------
void DrawLife(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	for (int nCount = 0; nCount < 2; nCount++)
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffLife[nCount], 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		if (g_aLife.bUse == true)
		{//お菓子が使用されている場合
		 //テクスチャ設定
			pDevice->SetTexture(0, g_apTextureLife[nCount]);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}
}

//-------------------------------------------
//設定処理
//-------------------------------------------
void SetLife(D3DXVECTOR3 pos, int nMax, int nNow)
{
	for (int nCount = 0; nCount < 2; nCount++)
	{
		if (g_aLife.bUse == false)
		{//使用していなかったら
			g_aLife.pos = pos;			//位置
			g_aLife.nMaxLife = nMax;	//最大ライフ数
			g_aLife.nNowLife = nNow;	//今のライフ数
			g_aLife.bUse = true;		//使用する

			break;
		}
	}
}

//-------------------------------------------
//ライフの減算処理
//-------------------------------------------
void SubLife(int nCntLife,int nReduce)
{
		if (g_aLife.bUse == true)
		{//今の体力からダメージ分減らす
			g_aLife.nNowLife -= nReduce;
		}
}

//-------------------------------------------
//ライフゲージの位置の更新処理
//-------------------------------------------
void SetPositionLife(D3DXVECTOR3 pos)
{
	if (g_aLife.bUse == true)
	{//使用していたら
		g_aLife.pos = pos;
	}
}