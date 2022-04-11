//============================================================
//
// 3Dインクの処理 [Ink.cpp]
// Aothur : Rikuto Sasaki
//
//============================================================
#include "ink.h"
#include "main.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//============================================================
//マクロ定義
//============================================================
#define MAX_Ink		(256)	//インクの最大数
#define Ink_SIZE	(60)	//インクのサイズ

//============================================================
//グローバル変数
//============================================================
LPDIRECT3DTEXTURE9 g_pTextureInk = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffInk = NULL;	// 頂点バッファへのポインタ
Ink g_aInk[MAX_Ink];						//インク

//============================================================
// インクの初期化
//============================================================
void lnitInk(void)
{
	int nCntInk;
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ink.png",					//shadow000.jpg"
		&g_pTextureInk);

	//インクの情報の初期化
	for (nCntInk = 0; nCntInk< MAX_Ink; nCntInk++)
	{
		g_aInk[nCntInk].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aInk[nCntInk].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aInk[nCntInk].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aInk[nCntInk].move= D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_aInk[nCntInk].bUse = false;
	}
	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_Ink,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffInk,
		NULL);

	//頂点情報へポインタ
	VERTEX_3D *pVtx = NULL;

	//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffInk->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntInk = 0; nCntInk < MAX_Ink; nCntInk++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(-55.0f, 0.0f, 55.0f);
		pVtx[1].pos = D3DXVECTOR3(55.0f, 0.0f, 55.0f);
		pVtx[2].pos = D3DXVECTOR3(-55.0f, 0.0f, -55.0f);
		pVtx[3].pos = D3DXVECTOR3(55.0f, 0.0f, -55.0f);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//各頂点の法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの描画
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx += 4;
	}
	//頂点バッファアンロック
	g_pVtxBuffInk->Unlock();

	srand((unsigned int)time(NULL));

	//プレイヤー1のエリア
	SetInk(D3DXVECTOR3(rand() % 200 + 50.0f, 0.3f, rand() % 10 + -400.0f), (D3DXVECTOR3(0.0f, 0.0f, 0.0f)));
	SetInk(D3DXVECTOR3(rand() % 200 + 50.0f, 0.3f, rand() % 10 + -400.0f), (D3DXVECTOR3(0.0f, 0.0f, 0.0f)));
	SetInk(D3DXVECTOR3(rand() % 200 + 50.0f, 0.3f, rand() % 10 + -400.0f), (D3DXVECTOR3(0.0f, 0.0f, 0.0f)));

	//プレイヤー2のエリア
	SetInk(D3DXVECTOR3(rand() % 200 + 50.0f, 0.3f, rand() % 400 + 100.0f), (D3DXVECTOR3(0.0f, 0.0f, 0.0f)));
	SetInk(D3DXVECTOR3(rand() % 200 + 50.0f, 0.3f, rand() % 400 + 100.0f), (D3DXVECTOR3(0.0f, 0.0f, 0.0f)));
	SetInk(D3DXVECTOR3(rand() % 200 + 50.0f, 0.3f, rand() % 400 + 100.0f), (D3DXVECTOR3(0.0f, 0.0f, 0.0f)));
}

//============================================================
// インクの終了処理
//============================================================
void UninitInk(void)
{
	//テクスチャの破棄
	if (g_pTextureInk != NULL)
	{
		g_pTextureInk->Release();
		g_pTextureInk = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffInk != NULL)
	{
		g_pVtxBuffInk->Release();
		g_pVtxBuffInk = NULL;
	}
}

//============================================================
// インクの更新処理
//============================================================
void UpdateInk(void)
{

}

//============================================================
// インクの設定
//============================================================
int SetInk(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntInk;

	for (nCntInk = 0; nCntInk<MAX_Ink; nCntInk++)
	{
		//bUseがfalseの場合、pos,rotを代入しbUseをtrueにする
		if (g_aInk[nCntInk].bUse == false)
		{
			g_aInk[nCntInk].pos = pos;
			g_aInk[nCntInk].rot = rot;
			g_aInk[nCntInk].bUse = true;

			g_aInk[nCntInk].size.x = (g_aInk[nCntInk].pos.x) / 2.0f;
			g_aInk[nCntInk].size.y = (g_aInk[nCntInk].pos.y);
			g_aInk[nCntInk].size.z = (g_aInk[nCntInk].pos.z) / 2.0f;
			break;
		}
	}
	return nCntInk;//インクの番号(indexを返す）
}
//============================================================
// インクの位置の更新処理
//============================================================
void SetPositionInk(int nldxInk, D3DXVECTOR3 pos)
{
	//引数で指定された番号のインクのposを設定
	g_aInk[nldxInk].pos = pos;
}
//============================================================
// インクの描画処理
//============================================================
void DrawInk(void)
{
	//デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

	for (int nCntInk = 0; nCntInk < MAX_Ink; nCntInk++)
	{
		if (g_aInk[nCntInk].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aInk[nCntInk].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aInk[nCntInk].rot.y, g_aInk[nCntInk].rot.x, g_aInk[nCntInk].rot.z);
			D3DXMatrixMultiply(&g_aInk[nCntInk].mtxWorld, &g_aInk[nCntInk].mtxWorld, &mtxRot);

			//位置を反映.
			D3DXMatrixTranslation(&mtxTrans, g_aInk[nCntInk].pos.x, g_aInk[nCntInk].pos.y, g_aInk[nCntInk].pos.z);
			D3DXMatrixMultiply(&g_aInk[nCntInk].mtxWorld, &g_aInk[nCntInk].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aInk[nCntInk].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffInk, 0, sizeof(VERTEX_3D));

			//頂点フォーマット設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureInk);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntInk * 4, 2);
		}
	}
	
	//テクスチャの設定
	pDevice->SetTexture(0, NULL);
}
//============================================================
// エネミーの当たり判定
//============================================================
bool CollisionInk(
	D3DXVECTOR3* pPos,				//現在の位置
	D3DXVECTOR3* pPosOld,			//前回の高さ
	D3DXVECTOR3* pMove,				//移動量
	D3DXVECTOR3* pSize)//サイズ
{
	bool bIsLanding = false;		//着地しているかどうか

	for (int nCntInk = 0; nCntInk<MAX_Ink; nCntInk++)
	{
		if (g_aInk[nCntInk].bUse == true)//使用している場合
		{
			/*Player*pPlayer;
			pPlayer = GetPlayer();
			*/
			//右の当たり判定
			if (pPos->z - pSize->z <g_aInk[nCntInk].pos.z + g_aInk[nCntInk].size.z &&
				pPos->z + pSize->z >g_aInk[nCntInk].pos.z - g_aInk[nCntInk].size.z &&

				pPos->y - pSize->y <g_aInk[nCntInk].pos.y + g_aInk[nCntInk].size.y &&
				pPos->y + pSize->y >g_aInk[nCntInk].pos.y - g_aInk[nCntInk].size.y &&

				pPosOld->x >= g_aInk[nCntInk].pos.x + g_aInk[nCntInk].size.x + pSize->x &&
				pPos->x < g_aInk[nCntInk].pos.x + g_aInk[nCntInk].size.x + pSize->x)

				//インクにめり込んだ
			{
				pPos->x = g_aInk[nCntInk].pos.x + g_aInk[nCntInk].size.x + pSize->x;
				pMove->x = 0.0f;
			}

			//左の当たり判定
			if (pPos->z - pSize->z < g_aInk[nCntInk].pos.z + g_aInk[nCntInk].size.z &&
				pPos->z + pSize->z > g_aInk[nCntInk].pos.z - g_aInk[nCntInk].size.z &&

				pPos->y - pSize->y < g_aInk[nCntInk].pos.y + g_aInk[nCntInk].size.y &&
				pPos->y + pSize->y > g_aInk[nCntInk].pos.y - g_aInk[nCntInk].size.y &&

				pPosOld->x <= g_aInk[nCntInk].pos.x - g_aInk[nCntInk].size.x - pSize->x &&
				pPos->x > g_aInk[nCntInk].pos.x - g_aInk[nCntInk].size.x - pSize->x)

				//インクにめり込んだ
			{
				pPos->x = g_aInk[nCntInk].pos.x - g_aInk[nCntInk].size.x - pSize->x;
				pMove->x = 0.0f;
			}

			//下面の当たり判定
			if (pPos->x - pSize->x < g_aInk[nCntInk].pos.x + g_aInk[nCntInk].size.x &&
				pPos->x + pSize->x > g_aInk[nCntInk].pos.x - g_aInk[nCntInk].size.x &&

				pPos->z - pSize->z < g_aInk[nCntInk].pos.z + g_aInk[nCntInk].size.z &&
				pPos->z + pSize->z > g_aInk[nCntInk].pos.z - g_aInk[nCntInk].size.z &&

				pPosOld->y <= g_aInk[nCntInk].pos.y - g_aInk[nCntInk].size.y - pSize->y &&
				pPos->y > g_aInk[nCntInk].pos.y - g_aInk[nCntInk].size.y - pSize->y)
				//インクにめり込んだ
			{
				pPos->y = g_aInk[nCntInk].pos.y - g_aInk[nCntInk].size.y - pSize->y;
				pMove->y = 0.0f;
			}
			//正面当たり判定
			if (pPos->x - pSize->x < g_aInk[nCntInk].pos.x + g_aInk[nCntInk].size.x &&
				pPos->x + pSize->x > g_aInk[nCntInk].pos.x - g_aInk[nCntInk].size.x &&

				pPos->y - pSize->y < g_aInk[nCntInk].pos.y + g_aInk[nCntInk].size.y &&
				pPos->y + pSize->y > g_aInk[nCntInk].pos.y - g_aInk[nCntInk].size.y &&

				pPosOld->z <= g_aInk[nCntInk].pos.z + g_aInk[nCntInk].size.z - pSize->z &&
				pPos->z > g_aInk[nCntInk].pos.z - g_aInk[nCntInk].size.z - pSize->z)

				//インクにめり込んだ
			{
				pPos->z = g_aInk[nCntInk].pos.z - g_aInk[nCntInk].size.z - pSize->z;
				pMove->z = 0.0f;
			}

			//上面の当たり判定
			if (pPos->x - pSize->x < g_aInk[nCntInk].pos.x + g_aInk[nCntInk].size.x &&
				pPos->x + pSize->x > g_aInk[nCntInk].pos.x - g_aInk[nCntInk].size.x &&

				pPos->z - pSize->z < g_aInk[nCntInk].pos.z + g_aInk[nCntInk].size.z &&
				pPos->z + pSize->z > g_aInk[nCntInk].pos.z - g_aInk[nCntInk].size.z &&

				pPosOld->y >= g_aInk[nCntInk].pos.y + g_aInk[nCntInk].size.y + pSize->y &&
				pPos->y < g_aInk[nCntInk].pos.y + g_aInk[nCntInk].size.y + pSize->y)
				//インクにめり込んだ
			{
				bIsLanding = true;
				pPos->y = g_aInk[nCntInk].pos.y + g_aInk[nCntInk].size.y + pSize->y;
				pMove->y = 0.0f;
			}

		}
	}

	return bIsLanding;
}
