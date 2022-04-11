//----------------------------------------
//　ディスクの処理
//　Author：橋野幹生
//----------------------------------------
#include "Disc.h"
#include "vec.h"
#include "goal.h"
#include "mob.h"
#include "player.h"

//グローバル変数宣言
LPD3DXMESH g_pMeshDisc = NULL;			//メッシュ情報へのポインタ
LPD3DXBUFFER g_pBuffMatDisc = NULL;		//マテリアル情報へのポインタ
DWORD g_nNumMatDisc = 0;				//マテリアル情報の数
D3DXMATERIAL * g_pMatDisc;				//マテリアルデータへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureDisc[10];	//テクスチャへのポインタ
Disc g_aDisc;				//ディスクの変数
DISC_SHOT g_DiscType;		//投げたディスクの種類を設定用
float g_fData;				//カーブ軌道時に使用。
bool g_bShotUp = false;		//一回だけ起動するよう

//---------------------------------------------------
//	ディスクの初期化
//---------------------------------------------------
void InitDisc(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//デバイス取得

	//ディスクの各値初期化
	{
		g_aDisc.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//現在の位置
		g_aDisc.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//前回の位置
		g_aDisc.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//角度
		g_aDisc.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
		g_aDisc.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//カラー
		g_aDisc.bUse = false;				//使っているかどうか
		g_aDisc.speed = 0.0f;				//移動スピード
		g_aDisc.status = STATUS_WAITING;	//現在の状態
		g_aDisc.vtxMin = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);			//頂点の最小値取得用
		g_aDisc.vtxMax = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);		//頂点の最大値取得用
		g_aDisc.vtxMax = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);		//頂点の最大値取得用
		g_aDisc.type = 0;
	}
	g_fData = 0.0f;		//軌道がカーブの時に使用
	g_bShotUp = false;	//重力をするかどうか

						//Ⅹファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\disc.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatDisc,
		NULL,
		&g_nNumMatDisc,
		&g_pMeshDisc);

	//マテリアルデータへのポインタを取得
	g_pMatDisc = (D3DXMATERIAL*)g_pBuffMatDisc->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatDisc; nCntMat++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(
			pDevice,
			g_pMatDisc[nCntMat].pTextureFilename,
			&g_pTextureDisc[nCntMat]);
	}

	int nNumVtx;		//頂点数
	DWORD sizeFVF;		//頂点フォーマットのサイズ
	BYTE * pVtxBuff;	//頂点バッファへのポインタ

						//頂点数の取得
	nNumVtx = g_pMeshDisc->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshDisc->GetFVF());

	//頂点バッファのロック
	g_pMeshDisc->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);


	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		// 最小値を求める
		if (vtx.x < g_aDisc.vtxMin.x)
		{// 比較した値が入ってる当たりよりも小さかったら、置き換え
			g_aDisc.vtxMin.x = vtx.x;
		}
		if (vtx.y < g_aDisc.vtxMin.y)
		{// 比較した値が入ってる当たりよりも小さかったら、置き換え
			g_aDisc.vtxMin.y = vtx.y;
		}
		if (vtx.z < g_aDisc.vtxMin.z)
		{// 比較した値が入ってる当たりよりも小さかったら、置き換え
			g_aDisc.vtxMin.z = vtx.z;
		}

		// 最大値を求める
		if (vtx.x > g_aDisc.vtxMax.x)
		{// 比較した値が入ってる当たりよりも大きかったら、置き換え
			g_aDisc.vtxMax.x = vtx.x;
		}
		if (vtx.y > g_aDisc.vtxMax.y)
		{// 比較した値が入ってる当たりよりも大きかったら、置き換え
			g_aDisc.vtxMax.y = vtx.y;
		}
		if (vtx.z > g_aDisc.vtxMax.z)
		{// 比較した値が入ってる当たりよりも大きかったら、置き換え
			g_aDisc.vtxMax.z = vtx.z;
		}

		//頂点フォーマットのポインタ分進める
		pVtxBuff += sizeFVF;
	}

	//頂点バッファをアンロック
	g_pMeshDisc->UnlockVertexBuffer();

	//ディスクのサイズ計算
	g_aDisc.size.x = g_aDisc.vtxMax.x - g_aDisc.vtxMin.x;
	g_aDisc.size.y = g_aDisc.vtxMax.y - g_aDisc.vtxMin.y;
	g_aDisc.size.z = g_aDisc.vtxMax.z - g_aDisc.vtxMin.z;
}

//---------------------------------------------------
//	ディスクの終了処理
//---------------------------------------------------
void UninitDisc(void)
{
	//メッシュ破棄
	if (g_pMeshDisc != NULL)
	{
		g_pMeshDisc->Release();
		g_pMeshDisc = NULL;
	}

	//マテリアル破棄
	if (g_pBuffMatDisc != NULL)
	{
		g_pBuffMatDisc->Release();
		g_pBuffMatDisc = NULL;
	}

	//テクスチャ破棄
	for (int nCntMat = 0; nCntMat < (int)g_nNumMatDisc; nCntMat++)
	{
		if (g_pTextureDisc[nCntMat] != NULL)
		{
			g_pTextureDisc[nCntMat]->Release();
			g_pTextureDisc[nCntMat] = NULL;
		}
	}
}

//---------------------------------------------------
//	ディスクの更新処理
//---------------------------------------------------
void UpdateDisc(void)
{
	if (g_aDisc.bUse == true)
	{
		//現在の位置を保存
		g_aDisc.posOld = g_aDisc.pos;

		if (g_aDisc.status == STATUS_WAITING)
		{
			//今のところ何もしない
		}

		float fSinData;

		if (g_aDisc.status == STATUS_MOVING)
		{
			switch (g_DiscType)
			{
			case SHOT_NOMAL:		//通常のディスク軌道（真っすぐ）
				fSinData = 0.0f;
				break;

			case SHOT_CURVE:		//カーブ
				g_fData += 0.03f;
				fSinData = sinf((D3DX_PI / 2.0f) + g_fData);
				break;

			case SHOT_UP:			//上方向に投げる
				fSinData = 0.0f;

				if (g_bShotUp == false)
				{//一回だけ使用
					g_aDisc.move.y = 1.5f;	//上方向へ
					g_bShotUp = true;
				}
				break;

			default:
				break;
			}

			if (g_DiscType == SHOT_UP)
			{//上方向へ投げた時
				//重力
				g_aDisc.move.y -= 0.05f;
			}

			//ディスクの移動量更新
			g_aDisc.move.x = sinf(g_aDisc.rot.y + fSinData) * g_aDisc.speed;
			g_aDisc.move.z = cosf(g_aDisc.rot.y + fSinData) * g_aDisc.speed;

			//ディスクの位置更新
			g_aDisc.pos.z -= g_aDisc.move.z;
			g_aDisc.pos.x -= g_aDisc.move.x;
			g_aDisc.pos.y += g_aDisc.move.y;

			//反射に関する当たり判定
			CollisionVec(g_aDisc.pos, g_aDisc.posOld, &g_aDisc.bUse, &g_aDisc.speed, &g_aDisc.rot);

			//ゴールとの当たり判定
			CollisionGoal(g_aDisc.pos, &g_aDisc.bUse, g_aDisc.type);

		}
	}
}

//---------------------------------------------------
//	ディスクの描画処理
//---------------------------------------------------
void DrawDisc(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL * pMat;			//マテリアルデータへのポインタ

	if (g_aDisc.bUse == true)
	{//ディスクが使用されている時
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aDisc.mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_aDisc.rot.y, g_aDisc.rot.x, g_aDisc.rot.z);
		D3DXMatrixMultiply(&g_aDisc.mtxWorld,
			&g_aDisc.mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aDisc.pos.x, g_aDisc.pos.y, g_aDisc.pos.z);
		D3DXMatrixMultiply(&g_aDisc.mtxWorld, &g_aDisc.mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aDisc.mtxWorld);

		//現在のマテリアル保持
		pDevice->GetMaterial(&matDef);

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_pBuffMatDisc->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_nNumMatDisc; nCntMat++)
		{
			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureDisc[nCntMat]);

			//モデルパーツの描画
			g_pMeshDisc->DrawSubset(nCntMat);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureDisc[nCntMat]);
		}

		//保持していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

//---------------------------------------------------
//	ディスクの位置設定（これはプレイヤーの初期設定で呼び出す）
//
//	type → プレイヤー1なら0、プレイヤー2なら1
//---------------------------------------------------
void SetPosDisc(D3DXVECTOR3 pos, int type)
{//ディスクの初期位置設定
	if (g_aDisc.bUse == false)
	{//ディスクが使用されていない時
		g_aDisc.pos = D3DXVECTOR3(pos.x, pos.y, pos.z);	//位置設定
		g_aDisc.bUse = true;				//使っている状態にする
		g_aDisc.status = STATUS_WAITING;	//状態を設定
		g_bShotUp = false;
		g_aDisc.type = type;
	}
}

//---------------------------------------------------
//	投げたディスクの設定(これはディスクを投げるときに呼ぶ関数)SetBulletと同じ要領。model.cppを参考に。
//
//	type → プレイヤー1なら0、プレイヤー2なら1
//---------------------------------------------------
void SetMoveDisc(D3DXVECTOR3 rot, float speed, DISC_SHOT shot, int type)
{
	if (g_aDisc.bUse == true)
	{
		if (g_aDisc.status == STATUS_WAITING)
		{
			if (g_aDisc.type == type)
			{
				g_aDisc.rot = rot;		//角度設定
				g_aDisc.speed = speed;	//スピード設定
				g_aDisc.status = STATUS_MOVING;	//状態を設定
				g_DiscType = shot;		//種類を設定
			}
		}
	}
}

//---------------------------------------------------
//	ディスクとプレイヤーの当たり判定（これはキャッチの判定）
//
//	type → プレイヤー1なら0、プレイヤー2なら1
//---------------------------------------------------
void CollisionDisc_Player(D3DXVECTOR3 *pos, D3DXVECTOR3 size, int type)
{//ディスクがプレイヤーに当たったら
	Player *pPlayer = GetPlayer();
	MOB *pMob = GetMob();

	if (g_aDisc.bUse == true)
	{// bUseがtrueだったら（ディスクが使用されている状態の時
		if (g_aDisc.status == STATUS_MOVING)
		{
			if (pos->y < g_aDisc.pos.y + (g_aDisc.size.y / 2.0f) &&
				pos->y + (size.y) > g_aDisc.pos.y - (g_aDisc.size.y / 2.0f))
			{
				if (pos->z - (size.z / 2) < g_aDisc.pos.z + (g_aDisc.size.z / 2.0f) &&
					pos->z + (size.z / 2) > g_aDisc.pos.z - (g_aDisc.size.z / 2.0f))
				{// *posのz座標がモデルに重なっている時
					if (pos->x - (size.x / 2) <= g_aDisc.pos.x + (g_aDisc.size.x / 2.0f) &&
						pos->x + (size.x / 2) >= g_aDisc.pos.x - (g_aDisc.size.x / 2.0f))
					{//左側からモデルにめり込んだ時
						g_aDisc.bUse = false;

						switch(type)
						{
						case 0:
							//プレイヤー1にディスクセット
							SetPosDisc(D3DXVECTOR3(pPlayer->pos.x + 10.0f, pPlayer->pos.y + 20.0f, pPlayer->pos.z), 0);
							break;

						case 1:
							//プレイヤー2にディスクセット
							SetPosDisc(D3DXVECTOR3(pMob->pos.x + 10.0f, pMob->pos.y + 20.0f, pMob->pos.z), 1);
							break;

						default:
							break;
						}
					}
				}
				else if (pos->x - (size.x / 2) < g_aDisc.pos.x - (g_aDisc.size.x / 2.0f) &&
					pos->x + (size.x / 2) > g_aDisc.pos.x + (g_aDisc.size.x / 2.0f))
				{// *posのx座標がモデルに重なっている時
					if (pos->z - (size.z / 2) < g_aDisc.pos.z + (g_aDisc.size.z / 2.0f) &&
						pos->z + (size.z / 2) > g_aDisc.pos.z - (g_aDisc.size.z / 2.0f))
					{//モデルの手前側からめり込んだ時
						//falseにする
						g_aDisc.bUse = false;

						switch (type)
						{
						case 0:
							//プレイヤー1にディスクセット
							SetPosDisc(D3DXVECTOR3(pPlayer->pos.x + 10.0f, pPlayer->pos.y + 20.0f, pPlayer->pos.z), 0);
							break;

						case 1:
							//プレイヤー2にディスクセット
							SetPosDisc(D3DXVECTOR3(pMob->pos.x + 10.0f, pMob->pos.y + 20.0f, pMob->pos.z), 1);
							break;

						default:
							break;
						}
					}
				}
			}
		}
	}
}

//---------------------------------------------------
//	ディスクの位置の更新処理（プレイヤーがディスクをもてるようになる）プレイヤーの更新処理に入れる。影と同じ
//---------------------------------------------------
void SetPositionDisc(D3DXVECTOR3 pos, int type)
{
	if (g_aDisc.status != STATUS_MOVING)
	{
		if (g_aDisc.type == type)
		{
			g_aDisc.pos = pos;	//位置更新
		}
	}
}