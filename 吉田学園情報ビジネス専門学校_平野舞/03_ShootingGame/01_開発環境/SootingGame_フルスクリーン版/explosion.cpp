//-------------------------------------------
//
//弾の爆発処理[explosion.cpp]
//Author:平野舞
//
//-------------------------------------------

//インクルードファイル
#include "explosion.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;			//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;		//頂点バッファへのポインタ
Explosion g_aExplosion[MAX_EXPLOSION];					//弾の情報

//-------------------------------------------
//弾爆発の初期化処理
//-------------------------------------------
void InitExplosion(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	int nCntExplosion;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/explosion001.png",
		&g_pTextureExplosion);

	//弾の情報の初期化
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - (EXPLOSION_WIDTH / 2), g_aExplosion[nCntExplosion].pos.y - (EXPLOSION_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + (EXPLOSION_WIDTH / 2), g_aExplosion[nCntExplosion].pos.y - (EXPLOSION_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - (EXPLOSION_WIDTH / 2), g_aExplosion[nCntExplosion].pos.y + (EXPLOSION_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + (EXPLOSION_WIDTH / 2), g_aExplosion[nCntExplosion].pos.y + (EXPLOSION_HEIGHT / 2), 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
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
	g_pVtxBuffExplosion->Unlock();
}

//-------------------------------------------
//弾爆発の終了処理
//-------------------------------------------
void UninitExplosion(void)
{
	//テクスチャの破棄
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//-------------------------------------------
//弾爆発の更新処理
//-------------------------------------------
void UpdateExplosion(void)
{
	int nCntExplosion;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{//爆発が使用されている
			//弾の爆発の更新
			g_aExplosion[nCntExplosion].nCounterAnim++;

			//カウンターが4になったら
			if (g_aExplosion[nCntExplosion].nCounterAnim % EXPLOSION_CNTANIM == 0)
			{//パターンNo.を増やす
				g_aExplosion[nCntExplosion].nPatternAnim++;
			}

			if (g_aExplosion[nCntExplosion].nPatternAnim == 7)
			{
				g_aExplosion[nCntExplosion].bUse = false;		//使用していない状態にする
			}

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - (EXPLOSION_WIDTH / 2), g_aExplosion[nCntExplosion].pos.y - (EXPLOSION_HEIGHT / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + (EXPLOSION_WIDTH / 2), g_aExplosion[nCntExplosion].pos.y - (EXPLOSION_HEIGHT / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - (EXPLOSION_WIDTH / 2), g_aExplosion[nCntExplosion].pos.y + (EXPLOSION_HEIGHT / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + (EXPLOSION_WIDTH / 2), g_aExplosion[nCntExplosion].pos.y + (EXPLOSION_HEIGHT / 2), 0.0f);

			//頂点座標の更新
			pVtx[0].tex = D3DXVECTOR2(0.125f * g_aExplosion[nCntExplosion].nPatternAnim, 0.0f);
			pVtx[1].tex = D3DXVECTOR2((0.125f * g_aExplosion[nCntExplosion].nPatternAnim) + 0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.125f * g_aExplosion[nCntExplosion].nPatternAnim, 1.0f);
			pVtx[3].tex = D3DXVECTOR2((0.125f * g_aExplosion[nCntExplosion].nPatternAnim) + 0.125f , 1.0f);

			//色の更新
			pVtx[0].col = g_aExplosion[nCntExplosion].col;
			pVtx[1].col =  g_aExplosion[nCntExplosion].col;
			pVtx[2].col =  g_aExplosion[nCntExplosion].col;
			pVtx[3].col =  g_aExplosion[nCntExplosion].col;

		}
		pVtx += 4;		//頂点データを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}

//-------------------------------------------
//弾爆発の描画処理
//-------------------------------------------
void DrawExplosion(void)
{
	int nCntExplosion;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureExplosion);

	//aブレインディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{//弾が使用されている場合
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, 2);
		}
	}

	//aブレインディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//-------------------------------------------
//弾爆発の設定処理
//-------------------------------------------
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCntExplosion;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{//弾が使用されていない場合
			g_aExplosion[nCntExplosion].nCounterAnim = 0;
			g_aExplosion[nCntExplosion].nPatternAnim = 0;

			g_aExplosion[nCntExplosion].pos = pos;
			g_aExplosion[nCntExplosion].col = col;
			g_aExplosion[nCntExplosion].bUse = true;

			break;
		}
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}

