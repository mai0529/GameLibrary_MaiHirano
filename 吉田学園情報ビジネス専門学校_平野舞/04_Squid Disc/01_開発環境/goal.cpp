//----------------------------------------
//　ゴール処理
//　Author：橋野幹生
//----------------------------------------
#include "goal.h"
#include "mob.h"
#include "player.h"
#include "score.h"
#include "disc.h"
#include"sound.h"
//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGoal = NULL;		//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureGoal = NULL;			//テクスチャへのポインタ
Goal g_aGoal;

//----------------------------------------
//	ゴールの初期化処理
//
//	X → 横幅の半径		Y → 縦幅の半径
//----------------------------------------
void InitGoal(float X, float Z)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイス取得

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\goal_000.png",	//テクスチャ入れる
		&g_pTextureGoal);

	//各値初期化
	g_aGoal.pos = D3DXVECTOR3(0.0f, 0.1f, 0.0f);	//位置
	g_aGoal.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//角度
	g_aGoal.fWidth = X;		//横幅
	g_aGoal.fHeight = Z;	//縦幅

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGoal,
		NULL);

	VERTEX_3D * pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_aGoal.pos.x - g_aGoal.fWidth, g_aGoal.pos.y, g_aGoal.pos.z + g_aGoal.fHeight);
	pVtx[1].pos = D3DXVECTOR3(g_aGoal.pos.x + g_aGoal.fWidth, g_aGoal.pos.y, g_aGoal.pos.z + g_aGoal.fHeight);
	pVtx[2].pos = D3DXVECTOR3(g_aGoal.pos.x - g_aGoal.fWidth, g_aGoal.pos.y, g_aGoal.pos.z - g_aGoal.fHeight);
	pVtx[3].pos = D3DXVECTOR3(g_aGoal.pos.x + g_aGoal.fWidth, g_aGoal.pos.y, g_aGoal.pos.z - g_aGoal.fHeight);

	//各頂点の法線の設定(ベクトルの大きさは１にする)
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定a
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	g_pVtxBuffGoal->Unlock();
}

//----------------------------------------
//	ゴールの終了処理
//----------------------------------------
void UninitGoal(void)
{
	//サウンドの停止
	StopSound();
	//頂点バッファ破棄
	if (g_pVtxBuffGoal != NULL)
	{
		g_pVtxBuffGoal->Release();
		g_pVtxBuffGoal = NULL;
	}

	//テクスチャ破棄
	if (g_pTextureGoal != NULL)
	{
		g_pTextureGoal->Release();
		g_pTextureGoal = NULL;
	}
}

//----------------------------------------
//	ゴールの更新処理
//----------------------------------------
void UpdateGoal(void)
{
	//処理なし
}

//----------------------------------------
//	ゴールの描画処理
//----------------------------------------
void DrawGoal(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureGoal);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_aGoal.mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aGoal.rot.y, g_aGoal.rot.x, g_aGoal.rot.z);
	D3DXMatrixMultiply(&g_aGoal.mtxWorld, &g_aGoal.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_aGoal.pos.x, g_aGoal.pos.y, g_aGoal.pos.z);
	D3DXMatrixMultiply(&g_aGoal.mtxWorld, &g_aGoal.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_aGoal.mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffGoal, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//影描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);	//プリミティブの種類

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureGoal);
}

//----------------------------------------
//	ゴールの当たり判定処理
//----------------------------------------
void CollisionGoal(D3DXVECTOR3 pos, bool *bUse, int type)
{
	Player *pPlayer = GetPlayer();
	MOB *pMob = GetMob();

	float fPosZ = 0.0f;

	switch (type)
	{
	case 0:
		if (g_aGoal.pos.z + g_aGoal.fHeight >= pos.z &&
			g_aGoal.pos.z + g_aGoal.fHeight - (g_aGoal.fHeight / 4.0f) <= pos.z)
		{//2P側(奥側)
			if (g_aGoal.pos.x - g_aGoal.fWidth < pos.x &&
				g_aGoal.pos.x - g_aGoal.fWidth + (g_aGoal.fWidth / 1.5f) > pos.x)
			{//1Pに3点獲得
				*bUse = false;		//falseにする

				//サウンドの再生
				PlaySound(SOUND_LABEL_SE_Score);

				AddScore(0, 3);//1Pに3点追加

				if (pMob->pos.z > g_aGoal.pos.z + g_aGoal.fHeight - (g_aGoal.fHeight / 4.0f))
				{//もしプレイヤーがゴール内に居たら
					fPosZ = g_aGoal.pos.z + g_aGoal.fHeight - (g_aGoal.fHeight / 4.0f);	//ゴールの外側にｚを設定
				}
				else
				{
					fPosZ = pMob->pos.z - 30.0f;	//そのままの値
				}

				SetPosDisc(D3DXVECTOR3(pMob->pos.x, pMob->pos.y + 30.0f, fPosZ), 1);
			}
			if (g_aGoal.pos.x + g_aGoal.fWidth > pos.x &&
				g_aGoal.pos.x + g_aGoal.fWidth - (g_aGoal.fWidth / 1.5f) < pos.x)
			{//1Pに3点獲得
				*bUse = false;		//falseにする

				//サウンドの再生
				PlaySound(SOUND_LABEL_SE_Score);

				AddScore(0, 3);		//1Pに3点追加

				if (pMob->pos.z > g_aGoal.pos.z + g_aGoal.fHeight - (g_aGoal.fHeight / 4.0f))
				{//もしプレイヤーがゴール内に居たら
					fPosZ = g_aGoal.pos.z + g_aGoal.fHeight - (g_aGoal.fHeight / 4.0f);	//ゴールの外側にｚを設定
				}
				else
				{
					fPosZ = pMob->pos.z - 30.0f;	//そのままの値
				}

				SetPosDisc(D3DXVECTOR3(pMob->pos.x, pMob->pos.y + 30.0f, fPosZ), 1);
			}
			if (g_aGoal.pos.x - ((g_aGoal.fWidth / 1.5f) / 2.0f) < pos.x &&
				g_aGoal.pos.x + ((g_aGoal.fWidth / 1.5f) / 2.0f) > pos.x)
			{//1Pに5点獲得
				*bUse = false;		//falseにする

				//サウンドの再生
				PlaySound(SOUND_LABEL_SE_Score);

				AddScore(0, 5);		//1Pに5点追加

				if (pMob->pos.z > g_aGoal.pos.z + g_aGoal.fHeight - (g_aGoal.fHeight / 4.0f))
				{//もしプレイヤーがゴール内に居たら
					fPosZ = g_aGoal.pos.z + g_aGoal.fHeight - (g_aGoal.fHeight / 4.0f);	//ゴールの外側にｚを設定
				}
				else
				{
					fPosZ = pMob->pos.z - 30.0f;	//そのままの値
				}

				SetPosDisc(D3DXVECTOR3(pMob->pos.x, pMob->pos.y + 30.0f, fPosZ), 1);
			}
		}

		if (pos.y <= g_aGoal.pos.y)
		{//床に落ちたとき
			if (g_aGoal.pos.x - g_aGoal.fWidth < pos.x &&
				g_aGoal.pos.x + g_aGoal.fWidth > pos.x)
			{
				if (g_aGoal.pos.z >= pos.z &&
					g_aGoal.pos.z - g_aGoal.fHeight + (g_aGoal.fHeight / 4.0f) <= pos.z)
				{//1Pに点獲得
					*bUse = false;		//falseにする

					//サウンドの再生
					PlaySound(SOUND_LABEL_SE_Score);

					AddScore(0, 2);		//1Pに2点追加

					if (pMob->pos.z > g_aGoal.pos.z + g_aGoal.fHeight - (g_aGoal.fHeight / 4.0f))
					{//もしプレイヤーがゴール内に居たら
						fPosZ = g_aGoal.pos.z + g_aGoal.fHeight - (g_aGoal.fHeight / 4.0f);	//ゴールの外側にｚを設定
					}
					else
					{
						fPosZ = pMob->pos.z - 30.0f;	//そのままの値
					}

					SetPosDisc(D3DXVECTOR3(pMob->pos.x, pMob->pos.y + 30.0f, fPosZ), 1);
				}
			}
		}

		break;

	case 1:
		if (g_aGoal.pos.z - g_aGoal.fHeight < pos.z &&
			g_aGoal.pos.z - g_aGoal.fHeight + (g_aGoal.fHeight / 4.0f) > pos.z)
		{//1P側(手前側)
			if (g_aGoal.pos.x - g_aGoal.fWidth < pos.x &&
				g_aGoal.pos.x - g_aGoal.fWidth + (g_aGoal.fWidth / 1.5f) > pos.x)
			{//2Pに3点獲得
				*bUse = false;		//falseにする

				//サウンドの再生
				PlaySound(SOUND_LABEL_SE_Score);

				AddScore(1, 3);		//2Pに3点追加

				if (pPlayer->pos.z < g_aGoal.pos.z - g_aGoal.fHeight + (g_aGoal.fHeight / 4.0f))
				{//もしプレイヤーがゴール内に居たら
					fPosZ = g_aGoal.pos.z - g_aGoal.fHeight + (g_aGoal.fHeight / 4.0f);	//ゴールの外側にｚを設定
				}
				else
				{
					fPosZ = pPlayer->pos.z + 30.0f;	//そのままの値
				}

				SetPosDisc(D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 30.0f, fPosZ), 0);
			}
			if (g_aGoal.pos.x + g_aGoal.fWidth > pos.x &&
				g_aGoal.pos.x + g_aGoal.fWidth - (g_aGoal.fWidth / 1.5f) < pos.x)
			{//2Pに3点獲得
				*bUse = false;		//falseにする
				
				//サウンドの再生
				PlaySound(SOUND_LABEL_SE_Score);

				AddScore(1, 3);		//2Pに3点追加

				if (pPlayer->pos.z < g_aGoal.pos.z - g_aGoal.fHeight + (g_aGoal.fHeight / 4.0f))
				{//もしプレイヤーがゴール内に居たら
					fPosZ = g_aGoal.pos.z - g_aGoal.fHeight + (g_aGoal.fHeight / 4.0f);	//ゴールの外側にｚを設定
				}
				else
				{
					fPosZ = pPlayer->pos.z + 30.0f;	//そのままの値
				}

				SetPosDisc(D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 30.0f, fPosZ), 0);
			}
			if (g_aGoal.pos.x - ((g_aGoal.fWidth / 1.5f) / 2.0f) < pos.x &&
				g_aGoal.pos.x + ((g_aGoal.fWidth / 1.5f) / 2.0f) > pos.x)
			{//2Pに5点獲得
				*bUse = false;		//falseにする

				//サウンドの再生
				PlaySound(SOUND_LABEL_SE_Score);

				AddScore(1, 5);		//2Pに5点追加

				if (pPlayer->pos.z < g_aGoal.pos.z - g_aGoal.fHeight + (g_aGoal.fHeight / 4.0f))
				{//もしプレイヤーがゴール内に居たら
					fPosZ = g_aGoal.pos.z - g_aGoal.fHeight + (g_aGoal.fHeight / 4.0f);	//ゴールの外側にｚを設定
				}
				else
				{
					fPosZ = pPlayer->pos.z + 30.0f;	//そのままの値
				}

				SetPosDisc(D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 30.0f, fPosZ), 0);
			}
		}

		if (pos.y <= g_aGoal.pos.y)
		{//床に落ちたとき
			if (g_aGoal.pos.x - g_aGoal.fWidth < pos.x &&
				g_aGoal.pos.x + g_aGoal.fWidth > pos.x)
			{
				if (g_aGoal.pos.z <= pos.z &&
					g_aGoal.pos.z + g_aGoal.fHeight - (g_aGoal.fHeight / 4.0f) >= pos.z)
				{//2Pに点獲得
					*bUse = false;		//falseにする

					//サウンドの再生
					PlaySound(SOUND_LABEL_SE_Score);

					AddScore(1, 2);		//2Pに2点追加

					if (pPlayer->pos.z > g_aGoal.pos.z - g_aGoal.fHeight + (g_aGoal.fHeight / 4.0f))
					{//もしプレイヤーがゴール内に居たら
						fPosZ = g_aGoal.pos.z - g_aGoal.fHeight + (g_aGoal.fHeight / 4.0f);	//ゴールの外側にｚを設定
					}
					else
					{
						fPosZ = pPlayer->pos.z + 30.0f;	//そのままの値
					}

					SetPosDisc(D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + 30.0f, fPosZ), 0);
				}
			}
		}
		break;

	default:
		break;
	}
}