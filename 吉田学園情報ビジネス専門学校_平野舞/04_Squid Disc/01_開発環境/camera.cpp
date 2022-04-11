//===================================================================
//
//3Dアクション(camera.cpp)
//Author:テュアン
//
//===================================================================
//===================================================================
//インクルードファイル
//===================================================================
#include "main.h"
#include "camera.h"
#include "input.h"
#include "player.h"
#include "mob.h"
//===================================================================
//グローバル変数
//===================================================================
Camera g_camera[2];
Player *pPlayer = GetPlayer();
MOB*pMob = GetMob();
//===================================================================
//カメラの初期化処理
//===================================================================
void InitCamera(void)
{
	//カメラ①
	//視点・注視点・上方向を設定する
	g_camera[0].posV = D3DXVECTOR3(0.0f, 150.0f, 250.0f);	//注視点
	g_camera[0].posR = D3DXVECTOR3(0.0f, 100.0f, 0.0f);		//視点
	g_camera[0].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		//上方向
	g_camera[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//y軸で回転する
	g_camera[0].posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//posRDestの初期化
	g_camera[0].posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//posVDestの初期化

	//視点と注視点間の距離
	g_camera[0].fDistance = sqrtf((g_camera[0].posV.x - g_camera[0].posR.x)*(g_camera[0].posV.x - g_camera[0].posR.x)
		+ (g_camera[0].posV.z - g_camera[0].posR.z)*(g_camera[0].posV.z - g_camera[0].posR.z));

	//注視点と目的の注視点間の距離
	g_camera[0].fDistanceA = sqrtf((g_camera[0].posRDest.x - pPlayer->pos.x) * (g_camera[0].posRDest.x - pPlayer->pos.x)
		+ (g_camera[0].posRDest.z - pPlayer->pos.z)  * (g_camera[0].posRDest.z - pPlayer->pos.z));


	g_camera[0].viewport.MinZ = 0.0f;
	g_camera[0].viewport.MaxZ = 1.0f;
	g_camera[0].viewport.X = 0.0f;
	g_camera[0].viewport.Y = 0.0f;
	g_camera[0].viewport.Width = SCREEN_WIDTH / 2;
	g_camera[0].viewport.Height = 720.0f;

	//カメラ②
	//視点・注視点・上方向を設定する
	g_camera[1].posV = D3DXVECTOR3(0.0f, 150.0f, 250.0f);	//注視点
	g_camera[1].posR = D3DXVECTOR3(0.0f, 100.0f, 0.0f);		//視点
	g_camera[1].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		//上方向
	g_camera[1].rot = D3DXVECTOR3(0.0f, -D3DX_PI, 0.0f);	//y軸で回転する
	g_camera[1].posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//posRDestの初期化
	g_camera[1].posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//posVDestの初期化


	 //視点と注視点間の距離

	g_camera[1].fDistance = sqrtf((g_camera[1].posV.x - g_camera[1].posR.x)*(g_camera[1].posV.x - g_camera[1].posR.x)
		+ (g_camera[1].posV.z - g_camera[1].posR.z)*(g_camera[1].posV.z - g_camera[1].posR.z));

	//注視点と目的の注視点間の距離
	g_camera[1].fDistanceA = sqrtf((g_camera[1].posRDest.x - pMob->pos.x) * (g_camera[1].posRDest.x - pMob->pos.x)
		+ (g_camera[1].posRDest.z - pMob->pos.z)  * (g_camera[1].posRDest.z - pMob->pos.z));


	g_camera[1].viewport.MinZ = 0.0f;
	g_camera[1].viewport.MaxZ = 1.0f;
	g_camera[1].viewport.X = 640.0f;
	g_camera[1].viewport.Y = 0.0f;
	g_camera[1].viewport.Width = SCREEN_WIDTH / 2;
	g_camera[1].viewport.Height = 720.0f;
}
//===================================================================
//カメラ終了処理
//===================================================================
void UninitCamera(void)
{

}

//===================================================================
//カメラ更新処理
//===================================================================
void UpdateCamera(void)
{
	//カメラ移動処理
	MoveCamera();
}

//===================================================================
//カメラセット処理
//===================================================================
void SetCamera(int nCnt)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera[nCnt].mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_camera[nCnt].mtxView,
		&g_camera[nCnt].posV,
		&g_camera[nCnt].posR,
		&g_camera[nCnt].vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera[nCnt].mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera[nCnt].mtxProjection);

	//ポロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&g_camera[nCnt].mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		10000.0f);
	//
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera[nCnt].mtxProjection);

}
//===============================================
Camera *GetCamera(void)
{

	return &g_camera[0];

}


//===================================================================
//カメラ移動処理
//===================================================================
void MoveCamera(void)
{
	//カメラ①
	//カメラの追従処理
	g_camera[0].posRDest.x = pPlayer->pos.x - sinf(pPlayer->rot.y) * 10;
	g_camera[0].posRDest.y = pPlayer->pos.y;
	g_camera[0].posRDest.z = pPlayer->pos.z - cosf(pPlayer->rot.y) * 10;

	g_camera[0].posVDest.x = pPlayer->pos.x - sinf(g_camera[0].rot.y) * 250;
	g_camera[0].posVDest.y = pPlayer->pos.y;
	g_camera[0].posVDest.z = pPlayer->pos.z - cosf(g_camera[0].rot.y) * 250;

	g_camera[0].posR.x += (g_camera[0].posRDest.x - g_camera[0].posR.x)*0.1f;
	g_camera[0].posV.x += (g_camera[0].posVDest.x - g_camera[0].posV.x)*0.1f;
	g_camera[0].posR.z += (g_camera[0].posRDest.z - g_camera[0].posR.z)*0.1f;
	g_camera[0].posV.z += (g_camera[0].posVDest.z - g_camera[0].posV.z)*0.1f;

	//カメラ②
	//カメラの追従処理
	g_camera[1].posRDest.x = pMob->pos.x - sinf(pMob->rot.y) * 10;
	g_camera[1].posRDest.y = pMob->pos.y;
	g_camera[1].posRDest.z = pMob->pos.z - cosf(pMob->rot.y) *10;

	g_camera[1].posVDest.x = pMob->pos.x - sinf(g_camera[1].rot.y) *250;
	g_camera[1].posVDest.y = pMob->pos.y;
	g_camera[1].posVDest.z = pMob->pos.z - cosf(g_camera[1].rot.y) * 250;

	g_camera[1].posR.x += (g_camera[1].posRDest.x - g_camera[1].posR.x)*0.1f;
	g_camera[1].posV.x += (g_camera[1].posVDest.x - g_camera[1].posV.x)*0.1f;
	g_camera[1].posR.z += (g_camera[1].posRDest.z - g_camera[1].posR.z)*0.1f;
	g_camera[1].posV.z += (g_camera[1].posVDest.z - g_camera[1].posV.z)*0.1f;


	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (g_camera[nCnt].rot.y > D3DX_PI)
		{
			g_camera[nCnt].rot.y -= D3DX_PI * 2;
		}
		if (g_camera[nCnt].rot.y < -D3DX_PI)
		{
			g_camera[nCnt].rot.y += D3DX_PI * 2;
		}
	}

}