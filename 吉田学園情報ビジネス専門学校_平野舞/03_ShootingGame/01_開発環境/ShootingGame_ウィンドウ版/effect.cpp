//-------------------------------------------
//
//エフェクト処理[effect.cpp]
//Author:平野舞
//
//-------------------------------------------
#include "effect.h"

//エフェクトの構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXCOLOR col;			//色
	float fRadius;			//半径(大きさ)
	int nLife;				//寿命(表示時間)
	bool bUse;				//使用しているかどうか
}Effect;

//マクロ定義
#define MAX_EFFECT			(4096)		//エフェクトの最大数
#define EFFECT_WIDTH		(20.0f)		//弾の幅
#define EFFECT_HEIGHT		(20.0f)		//弾の高さ

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;			//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	//頂点バッファへのポインタ
Effect g_aEffect[MAX_EFFECT];						//エフェクトの情報

//-------------------------------------------
//エフェクトの初期化処理
//-------------------------------------------
void InitEffect(void)
{
	int nCntEffect;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/effect000.jpg",
		&g_pTextureEffect);

	//弾の情報の初期化
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(0.02f, 0.02f, 0.02f, 0.02f);
		g_aEffect[nCntEffect].fRadius = 5.0f;
		g_aEffect[nCntEffect].nLife = 15;
		g_aEffect[nCntEffect].bUse = false;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - EFFECT_WIDTH, g_aEffect[nCntEffect].pos.y - EFFECT_HEIGHT, g_aEffect[nCntEffect].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + EFFECT_WIDTH, g_aEffect[nCntEffect].pos.y - EFFECT_HEIGHT, g_aEffect[nCntEffect].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - EFFECT_WIDTH, g_aEffect[nCntEffect].pos.y + EFFECT_HEIGHT, g_aEffect[nCntEffect].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + EFFECT_WIDTH, g_aEffect[nCntEffect].pos.y + EFFECT_HEIGHT, g_aEffect[nCntEffect].pos.z);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(0.2f, 0.5f, 0.6f, 0.5f);
		pVtx[1].col = D3DXCOLOR(0.2f, 0.5f, 0.6f, 0.5f);
		pVtx[2].col = D3DXCOLOR(0.2f, 0.5f, 0.6f, 0.5f);
		pVtx[3].col = D3DXCOLOR(0.2f, 0.5f, 0.6f, 0.5f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;		//頂点データを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}

//-------------------------------------------
//エフェクトの終了処理
//-------------------------------------------
void UninitEffect(void)
{
	//テクスチャの破棄
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//-------------------------------------------
//エフェクトの更新処理
//-------------------------------------------
void UpdateEffect(void)
{
	int nCntEffect;
	//int nSiz = 5;
	float nData = 0.0;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//nSiz--;
		if (g_aEffect[nCntEffect].bUse == true)
		{//エフェクトが使用されている
			//頂点カラーの設定
			//g_aEffect[nCntEffect].col = 0.2 * 0.2 + nData * 1.0;
			//nData = g_aEffect[nCntEffect].col;
			/*nData = 0.02 * 0.02 + nData * 1.0;
			g_aEffect[nCntEffect].col = nData;*/

			//頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - EFFECT_WIDTH , g_aEffect[nCntEffect].pos.y - EFFECT_HEIGHT, g_aEffect[nCntEffect].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + EFFECT_WIDTH , g_aEffect[nCntEffect].pos.y - EFFECT_HEIGHT, g_aEffect[nCntEffect].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - EFFECT_WIDTH , g_aEffect[nCntEffect].pos.y + EFFECT_HEIGHT, g_aEffect[nCntEffect].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + EFFECT_WIDTH , g_aEffect[nCntEffect].pos.y + EFFECT_HEIGHT, g_aEffect[nCntEffect].pos.z);

			//寿命(表示時間)
			g_aEffect[nCntEffect].nLife -= 1;
			if (g_aEffect[nCntEffect].nLife == 0)
			{
				g_aEffect[nCntEffect].bUse = false;		//使用していない状態にする
			}
		}
		pVtx += 4;		//頂点データを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}

//-------------------------------------------
//エフェクトの描画処理
//-------------------------------------------
void DrawEffect(void)
{
	int nCntEffect;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureEffect);

	//aブレインディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{//弾が使用されている場合
		 //ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);
		}
	}

	//aブレインディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//-------------------------------------------
//エフェクトの設定処理
//-------------------------------------------
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife)
{
	int nCntEffect;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{//弾が使用されていない場合
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].nLife = nLife;
			g_aEffect[nCntEffect].bUse = true;
			break;
		}
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}