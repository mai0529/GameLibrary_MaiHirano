//===================================================================
//
//3Dアクション(mob.cpp)
//Author:大原隆俊
//
//===================================================================
//===================================================================
//インクルードファイル
//===================================================================
#include <stdio.h>
#include "main.h"
#include "player.h"
#include "input.h"
#include "camera.h"
#include "meshfield.h"
#include "shadow.h"
#include "wall.h"
#include "mob.h"
#include "controller.h"
#include"score.h"
#include"disc.h"
#include "Field.h"
#include "enemy.h"
#include"controller.h"

//===================================================================
//グローバル変数
//===================================================================
MOB g_Mob;								//プレイヤー構造体
MobKey g_aMobKey;						//キー構造体
MobKeySet g_aMobKeySet;					//キーセット構造体
MobMotionSet g_MobMotionSet;			//モーション構造体

//===================================================================
//プレイヤーの初期化設定
//===================================================================
void InitMob(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	ZeroMemory(&g_Mob, sizeof(g_Mob)); //構造体変数をクリアできる便利関数

	int nNumVtx;		//頂点数
	DWORD sizeFVF;		//頂点フォーマットのサイズ
	BYTE *pVtxBuff;		//頂点バッファへのポインタ

						//Xファイルの読み込み
	D3DXLoadMeshFromX("data//MODEL//player_body.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Mob.aModel[0].pBuffMat,
		NULL,
		&g_Mob.aModel[0].nNumMat,
		&g_Mob.aModel[0].pMesh);

	D3DXLoadMeshFromX("data//MODEL//mob_head.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Mob.aModel[1].pBuffMat,
		NULL,
		&g_Mob.aModel[1].nNumMat,
		&g_Mob.aModel[1].pMesh);

	D3DXLoadMeshFromX("data//MODEL//player_armR.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Mob.aModel[2].pBuffMat,
		NULL,
		&g_Mob.aModel[2].nNumMat,
		&g_Mob.aModel[2].pMesh);

	D3DXLoadMeshFromX("data//MODEL//player_handR.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Mob.aModel[3].pBuffMat,
		NULL,
		&g_Mob.aModel[3].nNumMat,
		&g_Mob.aModel[3].pMesh);

	D3DXLoadMeshFromX("data//MODEL//player_armL.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Mob.aModel[4].pBuffMat,
		NULL,
		&g_Mob.aModel[4].nNumMat,
		&g_Mob.aModel[4].pMesh);

	D3DXLoadMeshFromX("data//MODEL//player_handL.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Mob.aModel[5].pBuffMat,
		NULL,
		&g_Mob.aModel[5].nNumMat,
		&g_Mob.aModel[5].pMesh);

	D3DXLoadMeshFromX("data//MODEL//player_legR.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Mob.aModel[6].pBuffMat,
		NULL,
		&g_Mob.aModel[6].nNumMat,
		&g_Mob.aModel[6].pMesh);

	D3DXLoadMeshFromX("data//MODEL//player_footR.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Mob.aModel[7].pBuffMat,
		NULL,
		&g_Mob.aModel[7].nNumMat,
		&g_Mob.aModel[7].pMesh);

	D3DXLoadMeshFromX("data//MODEL//player_legL.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Mob.aModel[8].pBuffMat,
		NULL,
		&g_Mob.aModel[8].nNumMat,
		&g_Mob.aModel[8].pMesh);

	D3DXLoadMeshFromX("data//MODEL//player_footL.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Mob.aModel[9].pBuffMat,
		NULL,
		&g_Mob.aModel[9].nNumMat,
		&g_Mob.aModel[9].pMesh);

	//体
	g_Mob.aModel[0].pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);		//位置の初期設定
	g_Mob.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きの初期設定
	g_Mob.aModel[0].nIdx = 0;								//インデックス番号
	g_Mob.aModel[0].nIdxModelParent = -1;					//親のインデックス
															//頭
	g_Mob.aModel[1].pos = D3DXVECTOR3(0.0f, 30.0f, 0.0f);	//位置の初期設定
	g_Mob.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きの初期設定
	g_Mob.aModel[1].nIdx = 1;								//インデックス番号
	g_Mob.aModel[1].nIdxModelParent = 0;						//親のインデックス
																//右腕
	g_Mob.aModel[2].pos = D3DXVECTOR3(-15.0f, 30.0f, 0.0f);	//位置の初期設定
	g_Mob.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きの初期設定
	g_Mob.aModel[2].nIdx = 2;								//インデックス番号
	g_Mob.aModel[2].nIdxModelParent = 0;						//親のインデックス
																//右手
	g_Mob.aModel[3].pos = D3DXVECTOR3(-25.0f, 0.0f, 0.0f);		//位置の初期設定
	g_Mob.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きの初期設定
	g_Mob.aModel[3].nIdx = 3;								//インデックス番号
	g_Mob.aModel[3].nIdxModelParent = 2;						//親のインデックス
																//左腕
	g_Mob.aModel[4].pos = D3DXVECTOR3(15.0f, 30.0f, 0.0f);	//位置の初期設定
	g_Mob.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きの初期設定
	g_Mob.aModel[4].nIdx = 4;								//インデックス番号
	g_Mob.aModel[4].nIdxModelParent = 0;						//親のインデックス
																//左手
	g_Mob.aModel[5].pos = D3DXVECTOR3(25.0f, 0.0f, 0.0f);	//位置の初期設定
	g_Mob.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きの初期設定
	g_Mob.aModel[5].nIdx = 5;								//インデックス番号
	g_Mob.aModel[5].nIdxModelParent = 4;						//親のインデックス
																//右腿
	g_Mob.aModel[6].pos = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);	//位置の初期設定
	g_Mob.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きの初期設定
	g_Mob.aModel[6].nIdx = 6;								//インデックス番号
	g_Mob.aModel[6].nIdxModelParent = 0;						//親のインデックス
																//右足
	g_Mob.aModel[7].pos = D3DXVECTOR3(0.0f, -15.0f, 0.0f);	//位置の初期設定
	g_Mob.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きの初期設定
	g_Mob.aModel[7].nIdx = 7;								//インデックス番号
	g_Mob.aModel[7].nIdxModelParent = 6;						//親のインデックス
																//左腿
	g_Mob.aModel[8].pos = D3DXVECTOR3(10.0f, 0.0f, 0.0f);	//位置の初期設定
	g_Mob.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きの初期設定
	g_Mob.aModel[8].nIdx = 8;								//インデックス番号
	g_Mob.aModel[8].nIdxModelParent = 0;						//親のインデックス
																//左足
	g_Mob.aModel[9].pos = D3DXVECTOR3(0.0f, -15.0f, 0.0f);;	//位置の初期設定
	g_Mob.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きの初期設定
	g_Mob.aModel[9].nIdx = 9;								//インデックス番号
	g_Mob.aModel[9].nIdxModelParent = 8;						//親のインデックス

																//モーションセットの設定
																//待機モーション
	g_MobMotionSet.aMobKeySet[0].nNum_Key = 2;			//キーの数
	g_MobMotionSet.aMobKeySet[0].fFlame = 0.0f;			//最初のフレーム
	g_MobMotionSet.aMobKeySet[0].bLoop = true;			//ループする
														//キーフレーム一つ目
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].pos[0] = D3DXVECTOR3(0.0f, 20.5f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].rot[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].pos[1] = D3DXVECTOR3(0.0f, 30.5f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].rot[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].pos[2] = D3DXVECTOR3(-15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].rot[2] = D3DXVECTOR3(0.0f, 0.0f, 0.5f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].pos[3] = D3DXVECTOR3(-25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].rot[3] = D3DXVECTOR3(0.0f, -0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].pos[4] = D3DXVECTOR3(15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].rot[4] = D3DXVECTOR3(0.0f, 0.0f, -0.5f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].pos[5] = D3DXVECTOR3(25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].rot[5] = D3DXVECTOR3(0.0f, 0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].pos[6] = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].rot[6] = D3DXVECTOR3(0.0f, 0.0f, -0.09f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].pos[7] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].rot[7] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].pos[8] = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].rot[8] = D3DXVECTOR3(0.0f, 0.0f, 0.09f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].pos[9] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].rot[9] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[0].fMaxFlame = 140.0f;	//最大フレーム数
																//キーフレーム二つ目
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].pos[0] = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].rot[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].pos[1] = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].rot[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].pos[2] = D3DXVECTOR3(-15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].rot[2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].pos[3] = D3DXVECTOR3(-25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].rot[3] = D3DXVECTOR3(0.0f, -0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].pos[4] = D3DXVECTOR3(15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].rot[4] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].pos[5] = D3DXVECTOR3(25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].rot[5] = D3DXVECTOR3(0.0f, 0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].pos[6] = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].rot[6] = D3DXVECTOR3(0.0f, 0.0f, -0.09f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].pos[7] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].rot[7] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].pos[8] = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].rot[8] = D3DXVECTOR3(0.0f, 0.0f, 0.09f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].pos[9] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].rot[9] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[0].aMobKey[1].fMaxFlame = 140.0f;	//最大フレーム数

																//移動モーション
	g_MobMotionSet.aMobKeySet[1].nNum_Key = 4;			//キーの数
	g_MobMotionSet.aMobKeySet[1].fFlame = 0.0f;			//最初のフレーム
	g_MobMotionSet.aMobKeySet[1].bLoop = true;			//ループする
														//キーフレーム一つ目1
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].pos[0] = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].rot[0] = D3DXVECTOR3(-0.5f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].pos[1] = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].rot[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].pos[2] = D3DXVECTOR3(-15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].rot[2] = D3DXVECTOR3(0.0f, 1.0f, 1.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].pos[3] = D3DXVECTOR3(-25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].rot[3] = D3DXVECTOR3(0.0f, -0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].pos[4] = D3DXVECTOR3(15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].rot[4] = D3DXVECTOR3(0.0f, 1.0f, -1.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].pos[5] = D3DXVECTOR3(25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].rot[5] = D3DXVECTOR3(0.0f, 0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].pos[6] = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].rot[6] = D3DXVECTOR3(-0.5f, 0.0f, -0.09f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].pos[7] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].rot[7] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].pos[8] = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].rot[8] = D3DXVECTOR3(0.5f, 0.0f, 0.09f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].pos[9] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].rot[9] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[0].fMaxFlame = 150.0f;	//最大フレーム数
																//キーフレーム二つ目
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].pos[0] = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].rot[0] = D3DXVECTOR3(-0.5f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].pos[1] = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].rot[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].pos[2] = D3DXVECTOR3(-15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].rot[2] = D3DXVECTOR3(0.0f, -1.0f, 1.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].pos[3] = D3DXVECTOR3(-25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].rot[3] = D3DXVECTOR3(0.0f, -0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].pos[4] = D3DXVECTOR3(15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].rot[4] = D3DXVECTOR3(0.0f, -1.0f, -1.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].pos[5] = D3DXVECTOR3(25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].rot[5] = D3DXVECTOR3(0.0f, 0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].pos[6] = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].rot[6] = D3DXVECTOR3(0.5f, 0.0f, -0.09f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].pos[7] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].rot[7] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].pos[8] = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].rot[8] = D3DXVECTOR3(-0.5f, 0.0f, 0.09f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].pos[9] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].rot[9] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[1].fMaxFlame = 150.0f;	//最大フレーム数
																//キーフレーム3つ目
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].pos[0] = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].rot[0] = D3DXVECTOR3(-0.5f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].pos[1] = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].rot[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].pos[2] = D3DXVECTOR3(-15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].rot[2] = D3DXVECTOR3(0.0f, 1.0f, 1.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].pos[3] = D3DXVECTOR3(-25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].rot[3] = D3DXVECTOR3(0.0f, -0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].pos[4] = D3DXVECTOR3(15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].rot[4] = D3DXVECTOR3(0.0f, 1.0f, -1.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].pos[5] = D3DXVECTOR3(25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].rot[5] = D3DXVECTOR3(0.0f, 0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].pos[6] = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].rot[6] = D3DXVECTOR3(-0.5f, 0.0f, -0.09f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].pos[7] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].rot[7] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].pos[8] = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].rot[8] = D3DXVECTOR3(0.5f, 0.0f, 0.09f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].pos[9] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].rot[9] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[2].fMaxFlame = 150.0f;	//最大フレーム数
																//キーフレーム4つ目
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].pos[0] = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].rot[0] = D3DXVECTOR3(-0.5f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].pos[1] = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].rot[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].pos[2] = D3DXVECTOR3(-15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].rot[2] = D3DXVECTOR3(0.0f, -1.0f, 1.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].pos[3] = D3DXVECTOR3(-25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].rot[3] = D3DXVECTOR3(0.0f, -0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].pos[4] = D3DXVECTOR3(15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].rot[4] = D3DXVECTOR3(0.0f, -1.0f, -1.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].pos[5] = D3DXVECTOR3(25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].rot[5] = D3DXVECTOR3(0.0f, 0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].pos[6] = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].rot[6] = D3DXVECTOR3(0.5f, 0.0f, -0.09f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].pos[7] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].rot[7] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].pos[8] = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].rot[8] = D3DXVECTOR3(-0.5f, 0.0f, 0.09f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].pos[9] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].rot[9] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[1].aMobKey[3].fMaxFlame = 150.0f;	//最大フレーム数

																//投擲モーション
	g_MobMotionSet.aMobKeySet[2].nNum_Key = 3;			//キーの数
	g_MobMotionSet.aMobKeySet[2].fFlame = 0.0f;			//最初のフレーム
	g_MobMotionSet.aMobKeySet[2].bLoop = false;			//ループする
														//キーフレーム一つ目
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].pos[0] = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].rot[0] = D3DXVECTOR3(0.0f, -0.75f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].pos[1] = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].rot[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].pos[2] = D3DXVECTOR3(-15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].rot[2] = D3DXVECTOR3(1.0f, 0.0f, 1.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].pos[3] = D3DXVECTOR3(-25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].rot[3] = D3DXVECTOR3(1.0f, -0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].pos[4] = D3DXVECTOR3(15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].rot[4] = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].pos[5] = D3DXVECTOR3(25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].rot[5] = D3DXVECTOR3(0.0f, 0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].pos[6] = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].rot[6] = D3DXVECTOR3(0.8f, 0.0f, -0.09f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].pos[7] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].rot[7] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].pos[8] = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].rot[8] = D3DXVECTOR3(0.0f, 0.0f, 0.09f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].pos[9] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].rot[9] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[0].fMaxFlame = 150.0f;	//最大フレーム数
																//キーフレーム二つ目
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].pos[0] = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].rot[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].pos[1] = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].rot[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].pos[2] = D3DXVECTOR3(-15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].rot[2] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].pos[3] = D3DXVECTOR3(-25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].rot[3] = D3DXVECTOR3(0.0f, -0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].pos[4] = D3DXVECTOR3(15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].rot[4] = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].pos[5] = D3DXVECTOR3(25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].rot[5] = D3DXVECTOR3(0.0f, 0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].pos[6] = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].rot[6] = D3DXVECTOR3(0.0f, 0.0f, -0.09f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].pos[7] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].rot[7] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].pos[8] = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].rot[8] = D3DXVECTOR3(0.0f, 0.0f, 0.09f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].pos[9] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].rot[9] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[1].fMaxFlame = 150.0f;	//最大フレーム数
																//キーフレーム3つ目
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].pos[0] = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].rot[0] = D3DXVECTOR3(0.0f, 0.75f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].pos[1] = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].rot[1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].pos[2] = D3DXVECTOR3(-15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].rot[2] = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].pos[3] = D3DXVECTOR3(-25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].rot[3] = D3DXVECTOR3(0.0f, -0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].pos[4] = D3DXVECTOR3(15.0f, 30.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].rot[4] = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].pos[5] = D3DXVECTOR3(25.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].rot[5] = D3DXVECTOR3(0.0f, 0.25f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].pos[6] = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].rot[6] = D3DXVECTOR3(-0.8f, 0.0f, -0.09f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].pos[7] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].rot[7] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].pos[8] = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].rot[8] = D3DXVECTOR3(0.0f, 0.0f, 0.09f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].pos[9] = D3DXVECTOR3(0.0f, -15.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].rot[9] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MobMotionSet.aMobKeySet[2].aMobKey[2].fMaxFlame = 150.0f;	//最大フレーム数

	for (int nCntModel = 0; nCntModel < MAX_MOB_PARTS; nCntModel++)
	{
		//頂点数取得
		nNumVtx = g_Mob.aModel[nCntModel].pMesh->GetNumVertices();

		//頂点フォーマットのサイズ取得
		sizeFVF = D3DXGetFVFVertexSize(g_Mob.aModel[nCntModel].pMesh->GetFVF());

		//頂点バッファのロック
		g_Mob.aModel[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		//比較のための数値代入
		g_Mob.vtxMax.x = -1000.0f;
		g_Mob.vtxMin.x = 1000.0f;
		g_Mob.vtxMax.y = -1000.0f;
		g_Mob.vtxMin.y = 1000.0f;
		g_Mob.vtxMax.z = -1000.0f;
		g_Mob.vtxMin.z = 1000.0f;

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//頂点座標の代入
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//頂点座標を比較してプレイヤーのMin,Maxを取得
			if (vtx.x > g_Mob.vtxMax.x)
			{//X座標の最大値
				g_Mob.vtxMax.x = vtx.x;
			}

			if (vtx.x < g_Mob.vtxMin.x)
			{//X座標の最小値
				g_Mob.vtxMin.x = vtx.x;
			}

			if (vtx.y > g_Mob.vtxMax.y)
			{//Y座標の最大値
				g_Mob.vtxMax.y = vtx.y;
			}

			if (vtx.y < g_Mob.vtxMin.y)
			{//Y座標の最小値
				g_Mob.vtxMin.y = vtx.y;
			}

			if (vtx.z > g_Mob.vtxMax.z)
			{//Z座標の最大値
				g_Mob.vtxMax.z = vtx.z;
			}

			if (vtx.z < g_Mob.vtxMin.z)
			{//Z座標の最小値
				g_Mob.vtxMin.z = vtx.z;
			}
			//頂点フォーマットのサイズ分ポインタを進める
			pVtxBuff += sizeFVF;
		}

		//頂点バッファアンロック
		g_Mob.aModel[nCntModel].pMesh->UnlockVertexBuffer();
	}

	FILE *pFile = fopen("data//TEXTFILE//mob.txt", "r");
	D3DXVECTOR3 posplayer;
	D3DXVECTOR3 rotplayer;
	char aData[128];
	fscanf(pFile, "pos = %f %f %f", &posplayer.x, &posplayer.y, &posplayer.z);
	fscanf(pFile, "%s", &aData[0]);
	fscanf(pFile, "%s", &aData[0]);
	fscanf(pFile, "%f", &rotplayer.x);
	fscanf(pFile, "%f", &rotplayer.y);
	fscanf(pFile, "%f", &rotplayer.z);
	/*fscanf(pFile, "rot = %f %f %f", &rotplayer.x, &rotplayer.y, &rotplayer.z);*/
	fclose(pFile);
	/*posplayer = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	rotplayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);*/
	g_Mob.bUse = false;
	g_Mob.pos = posplayer;					//位置の初期設定
	g_Mob.rot = rotplayer;					//向きの初期設定
	g_Mob.size.x = g_Mob.vtxMax.x - g_Mob.vtxMin.x;		//X方向のサイズ
	g_Mob.size.z = g_Mob.vtxMax.z - g_Mob.vtxMin.z;		//Z方向のサイズ
	g_Mob.IdxShadow = SetShadow(D3DXVECTOR3(g_Mob.pos.x, 0.5f, g_Mob.pos.z), g_Mob.rot);
	SetMob(posplayer, rotplayer, PLAYER_P1);
}

//===================================================================
//プレイヤーの終了処理
//===================================================================
void UninitMob(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MOB_PARTS; nCntModel++)
	{
		//バッファ破棄
		if (g_Mob.aModel[nCntModel].pMesh != NULL)
		{
			g_Mob.aModel[nCntModel].pMesh->Release();
			g_Mob.aModel[nCntModel].pMesh = NULL;
		}

		//テクスチャ破棄
		if (g_Mob.aModel[nCntModel].pBuffMat != NULL)
		{
			g_Mob.aModel[nCntModel].pBuffMat->Release();
			g_Mob.aModel[nCntModel].pBuffMat = NULL;
		}
	}
}

//===================================================================
//プレイヤーの更新処理
//===================================================================
void UpdateMob(void)
{
	int nPlayKeySet = g_MobMotionSet.nUseKeySet;				//使用中のキーセットの番号の変数
	MobKeySet* keyset = &g_MobMotionSet.aMobKeySet[nPlayKeySet];		//使用中のキーセット
	int nPlaykey = keyset->nUseKey;							//使用中のキー番号
	MobKey* key = &keyset->aMobKey[nPlaykey];						//使用中のキー
	int nNextUsekey = (nPlaykey + 1) % keyset->nNum_Key;	//次のキー番号
	MobKey* nextkey = &keyset->aMobKey[nNextUsekey];				//次のキー

																	//移動処理
	SetMobMove();

	//モデルに対してキーセット回転、位置の加算処理
	for (int nCntModel = 0; nCntModel < MAX_MOB_PARTS; nCntModel++)
	{
		//目標までの差分
		D3DXVECTOR3 diffpos = nextkey->pos[nCntModel] - key->pos[nCntModel];
		//現在の場所
		g_Mob.aModel[nCntModel].pos = key->pos[nCntModel] + (diffpos / key->fMaxFlame) * keyset->fFlame;

		//目標までの傾き
		D3DXVECTOR3 diffrot = nextkey->rot[nCntModel] - key->rot[nCntModel];
		//現在の傾き
		g_Mob.aModel[nCntModel].rot = key->rot[nCntModel] + (diffrot / key->fMaxFlame) * keyset->fFlame;

		//現在のフレーム数加算、キーの終了判定
		keyset->fFlame += 1.0f;

		if (keyset->fFlame >= key->fMaxFlame)
		{//キーが最終フレームに到達
			if (nPlaykey + 1 == keyset->nNum_Key)
			{//最後のキーだった場合
				if (keyset->bLoop == true)
				{//ループモーションのとき最初のキーに移行
					keyset->fFlame = 0.0f;
					keyset->nUseKey = nNextUsekey;
				}
				else
				{//ループモーションじゃないとき、モーション終了
					keyset->bUse = false;
				}
			}
			else
			{//次のキーに移行（最後ではない）
				keyset->fFlame = 0.0f;
				keyset->nUseKey = nNextUsekey;
			}
		}
	}

	if (((g_MobMotionSet.nUseKeySet == 2) && (g_MobMotionSet.aMobKeySet[2].bUse == false)) ||
		(g_MobMotionSet.nUseKeySet != 2))
	{//投擲モーション終了orそもそも投擲じゃない
	 //キーセットを変更
		if (g_Mob.move.x != 0.0f || g_Mob.move.z != 0.0f)
		{//移動している
			if (g_MobMotionSet.nUseKeySet != 1)
			{//移動モーションにする
				g_MobMotionSet.nUseKeySet = 1;
				g_MobMotionSet.aMobKeySet[1].nUseKey = 0;
				g_MobMotionSet.aMobKeySet[1].fFlame = 0.0f;
				g_MobMotionSet.aMobKeySet[1].bUse = true;
			}
		}
		else
		{//止まっている
			if (g_MobMotionSet.nUseKeySet != 0)
			{//待機モーションにする
				g_MobMotionSet.nUseKeySet = 0;
				g_MobMotionSet.aMobKeySet[0].nUseKey = 0;
				g_MobMotionSet.aMobKeySet[0].fFlame = 0.0f;
				g_MobMotionSet.aMobKeySet[0].bUse = true;
			}
		}
	}

	if (GetKeyboardTrigger(DIK_O) == true || GetControllerPressTrigger(1, XINPUT_GAMEPAD_A) == true)
	{//SPACEキーを押すorジョイパッドAボタンを押

		if (g_MobMotionSet.nUseKeySet != 2)
		{//投擲モーションにする
			g_MobMotionSet.nUseKeySet = 2;
			g_MobMotionSet.aMobKeySet[2].nUseKey = 0;
			g_MobMotionSet.aMobKeySet[2].fFlame = 0.0f;
			g_MobMotionSet.aMobKeySet[2].bUse = true;
			
		}

		SetMoveDisc(D3DXVECTOR3(g_Mob.rot),	//角度
			7.5f, SHOT_NOMAL,1);		//ディスクのスピード

		D3DXVECTOR3 move = D3DXVECTOR3(sinf(g_Mob.rot.y + D3DX_PI) * 1.0f, 0, cosf(g_Mob.rot.y + D3DX_PI) * 1.0f);
	}

	bool iMasat = CollisionField
	(
		&g_Mob.pos,
		&g_Mob.posOld,
		g_Mob.size / 2
	);

	CollisionEnemy
	(
		&g_Mob.pos,
		&g_Mob.posOld,
		&g_Mob.move,
		&g_Mob.size
	);

	CollisionDisc_Player(&g_Mob.pos, D3DXVECTOR3(10.0f, 40.0f, 10.0f), 1);

	SetPositionDisc(D3DXVECTOR3(g_Mob.pos.x, g_Mob.pos.y + 30.0f, g_Mob.pos.z - 30.0f), 1);
}

//===================================================================
//プレイヤーの描画処理
//===================================================================
void DrawMob(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//現在のマテリアル保存用
	D3DMATERIAL9 matDef;

	//マテリアルデータへのポインタ
	D3DXMATERIAL *pMat;

	if (g_Mob.bUse == false)
	{//falseのときに描画しない
		return;
	}

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Mob.mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Mob.rot.y, g_Mob.rot.x, g_Mob.rot.z);
	D3DXMatrixMultiply(&g_Mob.mtxWorld, &g_Mob.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Mob.pos.x, g_Mob.pos.y, g_Mob.pos.z);
	D3DXMatrixMultiply(&g_Mob.mtxWorld, &g_Mob.mtxWorld, &mtxTrans);

	for (int nCntModel = 0; nCntModel < MAX_MOB_PARTS; nCntModel++)
	{
		//プレイヤーパーツの構造体のワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Mob.aModel[nCntModel].mtxWorld);

		//プレイヤーパーツの構造体の向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Mob.aModel[nCntModel].rot.y, g_Mob.aModel[nCntModel].rot.x, g_Mob.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_Mob.aModel[nCntModel].mtxWorld, &g_Mob.aModel[nCntModel].mtxWorld, &mtxRot);

		//プレイヤーパーツの構造体の位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Mob.aModel[nCntModel].pos.x, g_Mob.aModel[nCntModel].pos.y, g_Mob.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_Mob.aModel[nCntModel].mtxWorld, &g_Mob.aModel[nCntModel].mtxWorld, &mtxTrans);

		//自分の親プレイヤーのマトリックスとの掛け算
		D3DXMATRIX mtxParent;
		if (g_Mob.aModel[nCntModel].nIdxModelParent == -1)
		{
			mtxParent = g_Mob.mtxWorld;
		}

		else
		{
			mtxParent = g_Mob.aModel[g_Mob.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}

		D3DXMatrixMultiply(&g_Mob.aModel[nCntModel].mtxWorld, &g_Mob.aModel[nCntModel].mtxWorld, &mtxParent);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Mob.aModel[nCntModel].mtxWorld);

		//現在のマテリアル保持
		pDevice->GetMaterial(&matDef);

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_Mob.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Mob.aModel[nCntModel].nNumMat; nCntMat++)
		{
			//マテリアル設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//プレイヤーパーツの描画
			g_Mob.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}
	}
	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//===================================================================
//プレイヤーの移動処理
//===================================================================
void SetMobMove(void)
{
	Camera *pCamera = GetCamera();
	Wall *Wall = GetWall();

	//スティックの情報を取得
	D3DXVECTOR3 Stick = GetControllerStickDir(1);

	if (GetKeyboardPress(DIK_LEFT) == true || GetControllerPress(1, XINPUT_GAMEPAD_DPAD_LEFT) == true
		|| GetControllerStickPress(1, STICK_LEFT) == true)
	{//Aキーが押された
		if (GetKeyboardPress(DIK_UP) == true || GetControllerPress(1, XINPUT_GAMEPAD_DPAD_UP) == true)
		{//左前移動
			g_Mob.move.x += sinf((pCamera + 1)->rot.y + (-D3DX_PI * 0.25f)) * PLAYER_SPEED;
			g_Mob.move.z += cosf((pCamera + 1)->rot.y + (-D3DX_PI * 0.25f))* PLAYER_SPEED;
			g_Mob.rot.y = ((pCamera + 1)->rot.y + (D3DX_PI * 0.75f));
		}

		else if (GetKeyboardPress(DIK_DOWN) == true || GetControllerPress(1, XINPUT_GAMEPAD_DPAD_DOWN) == true)
		{//左後ろ移動
			g_Mob.move.x += sinf((pCamera + 1)->rot.y + (-D3DX_PI * 0.75f)) * PLAYER_SPEED;
			g_Mob.move.z += cosf((pCamera + 1)->rot.y + (-D3DX_PI * 0.75f)) * PLAYER_SPEED;
			g_Mob.rot.y = ((pCamera + 1)->rot.y + (D3DX_PI * 0.25f));
		}

		else if (GetControllerStickPress(1, STICK_UP) == true || GetControllerStickPress(1, STICK_DOWN) == true)
		{//スティックの斜め
			g_Mob.move.x -= Stick.x * PLAYER_SPEED;
			g_Mob.move.z -= Stick.y * PLAYER_SPEED;
		}

		else
		{//左移動
			g_Mob.move.x += sinf((pCamera + 1)->rot.y + (-D3DX_PI * 0.5f)) * PLAYER_SPEED;
			g_Mob.move.z += cosf((pCamera + 1)->rot.y + (-D3DX_PI * 0.5f)) * PLAYER_SPEED;
			g_Mob.rot.y = ((pCamera + 1)->rot.y + (D3DX_PI * 0.5f));
		}
	}

	else if (GetKeyboardPress(DIK_RIGHT) == true || GetControllerPress(1, XINPUT_GAMEPAD_DPAD_RIGHT) == true
		|| GetControllerStickPress(1, STICK_RIGHT) == true)
	{//Dキーが押された
		if (GetKeyboardPress(DIK_DOWN) == true || GetControllerPress(1, XINPUT_GAMEPAD_DPAD_DOWN) == true)
		{//右後ろ移動
			g_Mob.move.x += sinf((pCamera + 1)->rot.y + (D3DX_PI * 0.75f)) * PLAYER_SPEED;
			g_Mob.move.z += cosf((pCamera + 1)->rot.y + (D3DX_PI * 0.75f)) * PLAYER_SPEED;
			g_Mob.rot.y = ((pCamera + 1)->rot.y + (D3DX_PI * -0.25f));
		}

		else if (GetKeyboardPress(DIK_UP) == true || GetControllerPress(1, XINPUT_GAMEPAD_DPAD_UP) == true)
		{//右前移動
			g_Mob.move.x += sinf((pCamera + 1)->rot.y + (D3DX_PI * 0.25f)) * PLAYER_SPEED;
			g_Mob.move.z += cosf((pCamera + 1)->rot.y + (D3DX_PI * 0.25f))* PLAYER_SPEED;
			g_Mob.rot.y = ((pCamera + 1)->rot.y + (D3DX_PI * -0.75f));
		}

		else if (GetControllerStickPress(1, STICK_UP) == true || GetControllerStickPress(1, STICK_DOWN) == true)
		{//スティックの斜め
			g_Mob.move.x -= Stick.x * PLAYER_SPEED;
			g_Mob.move.z -= Stick.y * PLAYER_SPEED;
		}

		else
		{//右移動
			g_Mob.move.x += sinf((pCamera + 1)->rot.y + (D3DX_PI * 0.5f)) * PLAYER_SPEED;
			g_Mob.move.z += cosf((pCamera + 1)->rot.y + (D3DX_PI * 0.5f)) * PLAYER_SPEED;
			g_Mob.rot.y = ((pCamera + 1)->rot.y + (D3DX_PI * -0.5f));
		}

	}

	else if (GetKeyboardPress(DIK_UP) == true || GetControllerPress(1, XINPUT_GAMEPAD_DPAD_UP) == true
		|| GetControllerStickPress(1, STICK_UP) == true)
	{//Wキーが押された
	 //前移動
		g_Mob.move.x += sinf((pCamera + 1)->rot.y + (D3DX_PI * 0.0f)) * PLAYER_SPEED;
		g_Mob.move.z += cosf((pCamera + 1)->rot.y + (D3DX_PI * 0.0f)) * PLAYER_SPEED;
		g_Mob.rot.y = ((pCamera + 1)->rot.y + (D3DX_PI * 1.0f));
	}

	else if (GetKeyboardPress(DIK_DOWN) == true || GetControllerPress(1, XINPUT_GAMEPAD_DPAD_DOWN) == true
		|| GetControllerStickPress(1, STICK_DOWN) == true)
	{//Sキーが押された
	 //後ろ移動
		g_Mob.move.x += sinf((pCamera + 1)->rot.y + (D3DX_PI * 1.0f)) * PLAYER_SPEED;
		g_Mob.move.z += cosf((pCamera + 1)->rot.y + (D3DX_PI * 1.0f)) * PLAYER_SPEED;
		g_Mob.rot.y = ((pCamera + 1)->rot.y + (D3DX_PI * 0.0f));
	}


	//前回の位置を保存
	g_Mob.posOld = g_Mob.pos;

	//位置更新
	g_Mob.pos.x += g_Mob.move.x;
	g_Mob.pos.z += g_Mob.move.z;

	////ぶつかったときの当たり判定
	/*CollisionEnemy(&g_Mob.pos,
	&g_Mob.posOld,
	&g_Mob.size,
	&g_Mob.move);*/

	//移動量更新（減衰）
	g_Mob.move.x += (0.0f - g_Mob.move.x) * 0.1f;	//目的の値-現在の値 * 減衰係数
	g_Mob.move.z += (0.0f - g_Mob.move.z) * 0.1f;

	//一定の数値未満になったら0にする
	if (g_Mob.move.x <= 0.1f && g_Mob.move.x >= -0.1f)
	{
		g_Mob.move.x = 0.0f;

	}

	if (g_Mob.move.z <= 0.1f && g_Mob.move.z >= -0.1f)
	{
		g_Mob.move.z = 0.0f;
	}
	SetPositionShadow(g_Mob.IdxShadow, D3DXVECTOR3(g_Mob.pos.x, 0.3f, g_Mob.pos.z));
}

//===================================================================
//プレイヤーの設置処理
//===================================================================
void SetMob(D3DXVECTOR3 pos, D3DXVECTOR3 rot, PLAYER_TYPE type)
{
	BYTE *pVtxBuff;		//頂点バッファへのポインタ

	for (int nCntPlayer = 0; nCntPlayer < MAX_MOB_PARTS; nCntPlayer++)
	{
		//頂点バッファのロック
		g_Mob.aModel[nCntPlayer].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		g_Mob.bUse = true;	//使用している
		g_Mob.pos = pos;		//位置の初期設定
		g_Mob.rot = rot;		//向きの初期設定

								//頂点バッファアンロック
		g_Mob.aModel[nCntPlayer].pMesh->UnlockVertexBuffer();
	}
}

//===================================================================
//取得処理
//===================================================================
MOB* GetMob(void)
{
	return &g_Mob;
}