//===================================================================
//
//3Dアクション(shadow.cpp)
//Author:大原隆俊
//
//===================================================================
//===================================================================
//インクルードファイル
//===================================================================
#include "main.h"
#include "shadow.h"

//===================================================================
//グローバル変数
//===================================================================
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;	//頂点バッファへのポインタ
Shadow g_aShadow[MAX_SHADOW];						//影の最大数

//===================================================================
//影の初期化設定
//===================================================================
void InitShadow(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_3D*pVtx;	//頂点情報のポインタ

	//テクスチャ読み込み 
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//shadow000.jpg",
		&g_pTextureShadow);

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,	//確保するバッファのサイズ 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,	//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//頂点座標設定
		pVtx[0].pos = D3DXVECTOR3(-10.0f, 0.0f, 10.0f);
		pVtx[1].pos = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
		pVtx[2].pos = D3DXVECTOR3(-10.0f, 0.0f, -10.0f);
		pVtx[3].pos = D3DXVECTOR3(10.0f, 0.0f, -10.0f);

		//各頂点の法線設定（ベクトルの大きさは1にする）
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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

		g_aShadow[nCntShadow].bUse = false;

		pVtx += 4;	//頂点データのポインタを4つずつ進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffShadow->Unlock();
}

//===================================================================
//影の終了処理
//===================================================================
void UninitShadow(void)
{
	//バッファ破棄
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}

	//テクスチャ破棄
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
}

//===================================================================
//影の更新処理
//===================================================================
void UpdateShadow(void)
{

}

//===================================================================
//影の描画処理
//===================================================================
void DrawShadow(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//減算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureShadow);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aShadow[nCntShadow].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCntShadow].rot.y, g_aShadow[nCntShadow].rot.x, g_aShadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCntShadow].pos.x, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCntShadow].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//影描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntShadow * 4, 2);	//プリミティブの種類
		}
	}
	//テクスチャをもとに戻す
	pDevice->SetTexture(0, NULL);

	//設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//===================================================================
//影の設定
//===================================================================
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	VERTEX_3D*pVtx;	//頂点情報のポインタ
	int nCntShadow;
	
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == false)
		{
			g_aShadow[nCntShadow].pos = pos;
			g_aShadow[nCntShadow].rot = rot;
			g_aShadow[nCntShadow].bUse = true;
			break;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffShadow->Unlock();
	return nCntShadow;	//影の番号(Index)を返す
}

//===================================================================
//影の位置更新処理
//===================================================================
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos)
{
	g_aShadow[nIdxShadow].pos = pos;
}

//===================================================================
//影の消去処理
//===================================================================
void UnsetShadow(int nIdxShadow)
{
	g_aShadow[nIdxShadow].bUse = false;
}