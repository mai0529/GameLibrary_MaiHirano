//============================================================
//
// 3D制作　エネミー（イカ）処理[Enemy.cpp]
// AUTHOR:Sasaki Rikuto
//
//============================================================
#include "main.h"
#include "enemy.h"
#include"score.h"
//============================================================
//マクロ定義
//============================================================
#define ANGLE_DAMPING_COEFFICIENT  (0.05f);//減衰係数
#define MAX_Enemy	(1280)				//モデルの最大数
#define NUM_Enemy	(2)				//モデル数
#define ENEMY_G		(1.0f)
//============================================================
//グローバル変数
//============================================================
int g_nEnemyCounter;//敵のカウント

//↓Enemyinfo構造体にする
typedef struct
{
	//↓構造体にしたい,MAX_Enemy ⇒ MAX_Enemy_TYPE 2
	LPD3DXMESH			 MeshEnemy;
	LPD3DXBUFFER		 pBuffMatEnemy;
	DWORD				nNumMatEnemy;
	D3DXVECTOR3			VtxMinEnemy;		//最小値　min[MAX_Enemy_TYPE]
	D3DXVECTOR3			VtxMaxEnemy;		//最大値　max[MAX_Enemy_TYPE]

}EnemyLinfo;

D3DXMATRIX g_mtxWorldEnemy;
Enemy g_Enemy[MAX_Enemy];
EnemyLinfo g_EnemyInfo[NUM_Enemy];
int GetCount;
int DetCount;

//============================================================
//　エネミーの初期化処理
//============================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntEnemy;
	g_nEnemyCounter = 0;

	//ノーマルなイカ
	D3DXLoadMeshFromX("data//MODEL//ika.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_EnemyInfo[0].pBuffMatEnemy,
		NULL,
		&g_EnemyInfo[0].nNumMatEnemy,
		&g_EnemyInfo[0].MeshEnemy);

	//ゴールドのイカ
	D3DXLoadMeshFromX("data//MODEL//ika2.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_EnemyInfo[1].pBuffMatEnemy,
		NULL,
		&g_EnemyInfo[1].nNumMatEnemy,
		&g_EnemyInfo[1].MeshEnemy);

	int nNumVtx;									//頂点数
	DWORD sizeFVF;									//頂点フォーマットのサイズ
	BYTE*pVtxBuff;									//頂点バッファのポインタ

	for (nCntEnemy = 0; nCntEnemy < MAX_Enemy; nCntEnemy++)
	{
		g_Enemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置の初期化
		g_Enemy[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きの初期化
		g_Enemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCntEnemy].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//目的角度の初期化

		g_Enemy[nCntEnemy].bUse = false;
	}

	for (int CntEnemy = 0; CntEnemy < NUM_Enemy; CntEnemy++)
	{
		g_EnemyInfo[nCntEnemy].VtxMinEnemy = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);	//最小値
		g_EnemyInfo[nCntEnemy].VtxMaxEnemy = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);	//最大値
	}

	//↓タイプ数分繰り返す
	for (nCntEnemy = 0; nCntEnemy < NUM_Enemy; nCntEnemy++)
	{
		//頂点数の取得
		nNumVtx = g_EnemyInfo[nCntEnemy].MeshEnemy->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_EnemyInfo[nCntEnemy].MeshEnemy->GetFVF());

		//頂点バッファをロック
		g_EnemyInfo[nCntEnemy].MeshEnemy->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < (int)nNumVtx; nCntVtx++)
		{
			//頂点座標の代入
			D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;

			//頂点座標を比較してモデルの最大値を取得
			if (Vtx.x >g_EnemyInfo[nCntEnemy].VtxMaxEnemy.x)
			{
				//↓グローバル変数のmin,maxにかえる
				g_EnemyInfo[nCntEnemy].VtxMaxEnemy.x = Vtx.x;
			}

			if (Vtx.y > g_EnemyInfo[nCntEnemy].VtxMaxEnemy.y)
			{
				g_EnemyInfo[nCntEnemy].VtxMaxEnemy.y = Vtx.y;
			}

			if (Vtx.z > g_EnemyInfo[nCntEnemy].VtxMaxEnemy.z)
			{
				g_EnemyInfo[nCntEnemy].VtxMaxEnemy.z = Vtx.z;
			}

			//頂点座標を比較してモデルの最小値を取得

			if (Vtx.x <g_EnemyInfo[nCntEnemy].VtxMinEnemy.x)
			{
				g_EnemyInfo[nCntEnemy].VtxMinEnemy.x = Vtx.x;
			}

			if (Vtx.y < g_EnemyInfo[nCntEnemy].VtxMinEnemy.y)
			{
				g_EnemyInfo[nCntEnemy].VtxMinEnemy.y = Vtx.y;
			}

			if (Vtx.z <g_EnemyInfo[nCntEnemy].VtxMinEnemy.z)
			{
				g_EnemyInfo[nCntEnemy].VtxMinEnemy.z = Vtx.z;
			}

			//頂点フォーマットのサイズ分ポインタを進めるccc
			pVtxBuff += sizeFVF;
		}

		//頂点バッファのアンロック
		g_EnemyInfo[nCntEnemy].MeshEnemy->UnlockVertexBuffer();
	}
}

//============================================================
//エネミーの終了処理
//============================================================
void UninitEnemy(void)
{
	for (int nCntEnemy = 0; nCntEnemy < NUM_Enemy; nCntEnemy++)
	{ //テクスチャの破棄
	  //メッシュの破棄
		if (g_EnemyInfo[nCntEnemy].pBuffMatEnemy != NULL)
		{
			g_EnemyInfo[nCntEnemy].pBuffMatEnemy->Release();
			g_EnemyInfo[nCntEnemy].pBuffMatEnemy = NULL;
		}
	}
}

//============================================================
// エネミーのアップデート処理
//============================================================
void UpdateEnemy(void)
{
	g_nEnemyCounter++; //敵の間隔

	if (g_nEnemyCounter % 600 == 0)
	{
		SetEnemy(D3DXVECTOR3(-300.0f, 0.0f, -150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 0.0f, 0.0f), 0); //ノーマルイカ
	}

	 if (g_nEnemyCounter % 600 == 0)
	{
		SetEnemy(D3DXVECTOR3(-300.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 0.0f, 0.0f), 0); //ノーマルイカ
	}

	 if (g_nEnemyCounter % 750 == 0)
	 {
		 SetEnemy(D3DXVECTOR3(300.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-3.0f, 0.0f, 0.0f), 1); //ノーマルイカ
	 }

	 if (g_nEnemyCounter % 750 == 0)
	 {
		 SetEnemy(D3DXVECTOR3(300.0f, 0.0f, 150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-3.0f, 0.0f, 0.0f), 1); //ノーマルイカ
	 }



	for (int nCntEnemy = 0; nCntEnemy < MAX_Enemy; nCntEnemy++)
	{
			//移動値
			g_Enemy[nCntEnemy].pos.x += g_Enemy[nCntEnemy].move.x / 2;
			g_Enemy[nCntEnemy].pos.y += g_Enemy[nCntEnemy].move.y / 2;
			g_Enemy[nCntEnemy].pos.z += g_Enemy[nCntEnemy].move.z / 2;

			if (g_Enemy[nCntEnemy].pos.x<= -700.0f)

			{//画面外に出た時
				g_Enemy[nCntEnemy].bUse = false;
			}
	}
}

//============================================================
// エネミーの描画処理
//============================================================
void DrawEnemy(void)
{
	//デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//計算用
	D3DMATERIAL9 matDef;//マテリアルの保存
	D3DXMATERIAL *pMat;//マテリアルの保管

	//現在のマテリアル
	pDevice->GetMaterial(&matDef);

	for (int nCntEnemy = 0; nCntEnemy < MAX_Enemy; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldEnemy);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[nCntEnemy].rot.x, g_Enemy[nCntEnemy].rot.y, g_Enemy[nCntEnemy].rot.z);
			D3DXMatrixMultiply(&g_mtxWorldEnemy, &g_mtxWorldEnemy, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldEnemy, &g_mtxWorldEnemy, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldEnemy);

			EnemyLinfo* EnemyInfo = &g_EnemyInfo[g_Enemy[nCntEnemy].nType];

			//マテリアルデータへのポイント取得
			pMat = (D3DXMATERIAL*)EnemyInfo->pBuffMatEnemy->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)EnemyInfo->nNumMatEnemy; nCntMat++)
			{
				//マテリアル設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//モデルパーツの描画
				EnemyInfo->MeshEnemy->DrawSubset(nCntMat);
			}
		
		}
		else
		{
			pDevice->SetTexture(0, NULL);
		}
	}

	//保存したマテリアル
	pDevice->SetMaterial(&matDef);
}
//============================================================
// エネミーの当たり判定
//============================================================
bool CollisionEnemy(
	D3DXVECTOR3* pPos,				//現在の位置
	D3DXVECTOR3* pPosOld,			//前回の高さ
	D3DXVECTOR3* pMove,				//移動量
	D3DXVECTOR3* pSize)//サイズ
{
	bool bIsLanding = false;		//着地しているかどうか
	
	for (int nCntEnemy = 0; nCntEnemy<MAX_Enemy; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse == true)//使用している場合
		{
			/*Player*pPlayer;
			pPlayer = GetPlayer();
*/
			//右の当たり判定
			if (pPos->z - pSize->z <g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].size.z &&
				pPos->z + pSize->z >g_Enemy[nCntEnemy].pos.z - g_Enemy[nCntEnemy].size.z &&

				pPos->y - pSize->y <g_Enemy[nCntEnemy].pos.y + g_Enemy[nCntEnemy].size.y &&
				pPos->y + pSize->y >g_Enemy[nCntEnemy].pos.y - g_Enemy[nCntEnemy].size.y &&

				pPosOld->x >= g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].size.x + pSize->x &&
				pPos->x < g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].size.x + pSize->x)

				//ブロックにめり込んだ
			{
				pPos->x = g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].size.x + pSize->x;
				pMove->x = 0.0f;
				
			}

			//左の当たり判定
			if (pPos->z - pSize->z < g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].size.z &&
				pPos->z + pSize->z > g_Enemy[nCntEnemy].pos.z - g_Enemy[nCntEnemy].size.z &&

				pPos->y - pSize->y < g_Enemy[nCntEnemy].pos.y + g_Enemy[nCntEnemy].size.y &&
				pPos->y + pSize->y > g_Enemy[nCntEnemy].pos.y - g_Enemy[nCntEnemy].size.y &&

				pPosOld->x <= g_Enemy[nCntEnemy].pos.x - g_Enemy[nCntEnemy].size.x - pSize->x &&
				pPos->x > g_Enemy[nCntEnemy].pos.x - g_Enemy[nCntEnemy].size.x - pSize->x)

				//ブロックにめり込んだ
			{
				pPos->x = g_Enemy[nCntEnemy].pos.x - g_Enemy[nCntEnemy].size.x - pSize->x;
				pMove->x = 0.0f;
				
			}
			
			//下面の当たり判定
			if (pPos->x - pSize->x < g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].size.x &&
				pPos->x + pSize->x > g_Enemy[nCntEnemy].pos.x - g_Enemy[nCntEnemy].size.x &&

				pPos->z - pSize->z < g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].size.z &&
				pPos->z + pSize->z > g_Enemy[nCntEnemy].pos.z - g_Enemy[nCntEnemy].size.z &&

				pPosOld->y <= g_Enemy[nCntEnemy].pos.y - g_Enemy[nCntEnemy].size.y - pSize->y &&
				pPos->y > g_Enemy[nCntEnemy].pos.y - g_Enemy[nCntEnemy].size.y - pSize->y)
				//ブロックにめり込んだ
			{
				pPos->y = g_Enemy[nCntEnemy].pos.y - g_Enemy[nCntEnemy].size.y - pSize->y;
				pMove->y = 0.0f;
				
			}
			//正面当たり判定
			if (pPos->x - pSize->x < g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].size.x &&
				pPos->x + pSize->x > g_Enemy[nCntEnemy].pos.x - g_Enemy[nCntEnemy].size.x &&

				pPos->y - pSize->y < g_Enemy[nCntEnemy].pos.y + g_Enemy[nCntEnemy].size.y &&
				pPos->y + pSize->y > g_Enemy[nCntEnemy].pos.y - g_Enemy[nCntEnemy].size.y &&

				pPosOld->z <= g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].size.z - pSize->z &&
				pPos->z > g_Enemy[nCntEnemy].pos.z - g_Enemy[nCntEnemy].size.z - pSize->z)

				//ブロックにめり込んだ
			{
				pPos->z = g_Enemy[nCntEnemy].pos.z - g_Enemy[nCntEnemy].size.z - pSize->z;
				pMove->z = 0.0f;
				
			}

			//上面の当たり判定
			if (pPos->x - pSize->x < g_Enemy[nCntEnemy].pos.x + g_Enemy[nCntEnemy].size.x &&
				pPos->x + pSize->x > g_Enemy[nCntEnemy].pos.x - g_Enemy[nCntEnemy].size.x &&

				pPos->z - pSize->z < g_Enemy[nCntEnemy].pos.z + g_Enemy[nCntEnemy].size.z &&
				pPos->z + pSize->z > g_Enemy[nCntEnemy].pos.z - g_Enemy[nCntEnemy].size.z &&

				pPosOld->y >= g_Enemy[nCntEnemy].pos.y + g_Enemy[nCntEnemy].size.y + pSize->y &&
				pPos->y < g_Enemy[nCntEnemy].pos.y + g_Enemy[nCntEnemy].size.y + pSize->y)
				//ブロックにめり込んだ
			{
				bIsLanding = true;
				pPos->y = g_Enemy[nCntEnemy].pos.y + g_Enemy[nCntEnemy].size.y + pSize->y;
				pMove->y = 0.0f;
				
			}
			
		}
	}

	return bIsLanding;
}
//============================================================
// エネミーの設定処理
//============================================================
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, int nType)	//type追加
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_Enemy; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse == false)
		{//ブロックが使用されてない場合
			g_Enemy[nCntEnemy].pos = pos;
			g_Enemy[nCntEnemy].rot = rot;
			g_Enemy[nCntEnemy].move = move;
			g_Enemy[nCntEnemy].bUse = true;	//使用している状態にする
			g_Enemy[nCntEnemy].nType = nType;

			g_Enemy[nCntEnemy].size.x = (g_EnemyInfo[nType].VtxMaxEnemy.x - g_EnemyInfo[nType].VtxMinEnemy.x) / 2.0f;
			g_Enemy[nCntEnemy].size.y = (g_EnemyInfo[nType].VtxMaxEnemy.y - g_EnemyInfo[nType].VtxMinEnemy.y);
			g_Enemy[nCntEnemy].size.z = (g_EnemyInfo[nType].VtxMaxEnemy.z - g_EnemyInfo[nType].VtxMinEnemy.z) / 2.0f;

			break;		//(for文を抜ける)
		}
	}
}
