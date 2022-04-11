//===================================================================
//
//3Dアクション(wall.cpp)
//Author:大原隆俊
//
//===================================================================
//===================================================================
//インクルードファイル
//===================================================================
#include "main.h"
#include "wall.h"

//===================================================================
//グローバル変数
//===================================================================
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;	//頂点バッファへのポインタ
Wall g_aWall[MAX_WALL];							//壁の最大数

//===================================================================
//壁の初期化設定 
//===================================================================
void InitWall(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャ読み込み 
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//block000.jpg",
		&g_pTextureWall);

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,	//確保するバッファのサイズ 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,	//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	VERTEX_3D*pVtx;	//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//頂点座標設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//各頂点の法線設定（ベクトルの大きさは1にする）
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(100,50, 200, 255);
		pVtx[1].col = D3DCOLOR_RGBA(100,50,200, 255);
		pVtx[2].col = D3DCOLOR_RGBA(100,50, 200, 255);
		pVtx[3].col = D3DCOLOR_RGBA(100,50, 200, 255);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(4.0f, 1.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 2.0f);
		pVtx[3].tex = D3DXVECTOR2(4.0f, 2.0f);

		//bUseの初期化
		g_aWall[nCntWall].bUse = false;

		pVtx += 4;
	}
	
	//頂点バッファをアンロックする
	g_pVtxBuffWall->Unlock();

	SetWall(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));				//〇壁
	SetWall(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f));		//右壁
	SetWall(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI*1.0f, 0.0f));		//手前壁
	SetWall(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));	//左壁
}

//===================================================================
//壁の終了処理
//===================================================================
void UninitWall(void)
{
	//バッファ破棄
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}

	//テクスチャ破棄
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}
}

//===================================================================
//壁の更新処理
//===================================================================
void UpdateWall(void)
{

}

//===================================================================
//壁の描画処理
//===================================================================
void DrawWall(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureWall);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aWall[nCntWall].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCntWall].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//影描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntWall * 4, 2);	//プリミティブの種類
		}
	}

	//テクスチャ設定
	pDevice->SetTexture(0, NULL);
}

//===================================================================
//壁の設置処理
//===================================================================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	VERTEX_3D*pVtx;	//頂点情報のポインタ
	int nCntWall;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == false)
		{
			g_aWall[nCntWall].pos = pos;
			g_aWall[nCntWall].rot = rot;

			pVtx[0].pos = D3DXVECTOR3(-140.0f, 100.0f, 140.0f);
			pVtx[1].pos = D3DXVECTOR3(140.0f, 100.0f, 140.0f);
			pVtx[2].pos = D3DXVECTOR3(-140.0f, 0.0f, 140.0f);
			pVtx[3].pos = D3DXVECTOR3(140.0f, 0.0f, 140.0f);

			g_aWall[nCntWall].bUse = true;
			break;
		}
		pVtx += 4;	//ポインタを4つ進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffWall->Unlock();
}

//===================================================================
//取得処理
//===================================================================
Wall* GetWall(void)
{
	return &g_aWall[0];
}