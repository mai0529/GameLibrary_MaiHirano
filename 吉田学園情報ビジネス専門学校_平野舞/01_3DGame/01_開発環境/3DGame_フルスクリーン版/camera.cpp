//-------------------------------------------
//カメラ処理[camera.cpp]
//Author:平野舞
//
//-------------------------------------------

//インクルードファイル
#include "camera.h"
#include "fade.h"
#include "map.h"
#include "stage.h"

//グローバル変数宣言
Camera g_camera[2];			//カメラ情報

//-------------------------------------------
//初期化処理
//-------------------------------------------
void InitCamera(void)
{
		//--------------------------カメラ1--------------------------------------------------------
		//カメラ情報の初期化
		g_camera[0].posV = D3DXVECTOR3(0.0f, 400.0f, -300.0f);		//視点の初期化
		g_camera[0].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//注視点の初期化
		g_camera[0].posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//目的の視点の初期化
		g_camera[0].posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//目的の注視点の初期化
		g_camera[0].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			//上方向の初期化
		g_camera[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//向き(角度)の初期化
		g_camera[0].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//目的の向き(角度)の初期化
		g_camera[0].fDistance = sqrtf((g_camera[0].posV.x - g_camera[0].posR.x) * (g_camera[0].posV.x - g_camera[0].posR.x) +
			(g_camera[0].posV.z - g_camera[0].posR.z) * (g_camera[0].posV.z - g_camera[0].posR.z));			//距離の初期化

		//ビューポート構成の保存
		g_camera[0].viewport.X = 0.0f;					//ビューポートの開始位置(X)
		g_camera[0].viewport.Y = 0.0f;					//ビューポートの開始位置(Y)
		g_camera[0].viewport.Width = SCREEN_WIDTH;		//ビューポートの幅
		g_camera[0].viewport.Height = SCREEN_HEIGHT;	//ビューポートの高さ
		g_camera[0].viewport.MinZ = 0.0f;				//ビューポートの最小サイズ
		g_camera[0].viewport.MaxZ = 1.0f;				//ビューポートの最大サイズ

		//--------------------------カメラ2--------------------------------------------------------
			//カメラ情報の初期化
		g_camera[1].posV = D3DXVECTOR3(0.0f, 2800.0f, 0.0f);		//視点の初期化
		g_camera[1].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//注視点の初期化
		g_camera[1].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			//上方向の初期化
		g_camera[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//向き(角度)の初期化
		g_camera[1].fDistance = sqrtf((g_camera[1].posV.x - g_camera[1].posR.x) * (g_camera[1].posV.x - g_camera[1].posR.x) +
			(g_camera[1].posV.z - g_camera[1].posR.z) * (g_camera[1].posV.z - g_camera[1].posR.z));			//距離の初期化

	//ビューポート構成の保存
		g_camera[1].viewport.X = 0.0f;					//ビューポートの開始位置(X)
		g_camera[1].viewport.Y = 0.0f;					//ビューポートの開始位置(Y)
		g_camera[1].viewport.Width = 250.0f;			//ビューポートの幅
		g_camera[1].viewport.Height = 250.0f;			//ビューポートの高さ
		g_camera[1].viewport.MinZ = 0.0f;				//ビューポートの最小サイズ
		g_camera[1].viewport.MaxZ = 1.0f;				//ビューポートの最大サイズ
}

//-------------------------------------------
//終了処理
//-------------------------------------------
void UninitCamera(void)
{
	//特になし
}

//-------------------------------------------
//更新処理
//-------------------------------------------
void UpdateCamera(void)
{
	//カメラの旋回
	//TurningCamera();

	//カメラの移動
	//MoveCamera();

	//カメラの追従
	//プレイヤー情報の取得
	Player * pPlayer = GetPlayer();

	//注視点
	g_camera[0].posRDest.x = pPlayer->pos.x + sinf(pPlayer->rot.y + D3DX_PI) * 30.0f;
	g_camera[0].posRDest.z = pPlayer->pos.z + cosf(pPlayer->rot.y + D3DX_PI) * 30.0f;

	//視点
	g_camera[0].posVDest.x = pPlayer->pos.x - sinf(g_camera[0].rot.y) * 300.0f;
	g_camera[0].posVDest.z = pPlayer->pos.z - cosf(g_camera[0].rot.y) * 300.0f;

	//代入
	g_camera[0].posR.x += (g_camera[0].posRDest.x - g_camera[0].posR.x) * 0.07f;
	g_camera[0].posR.z += (g_camera[0].posRDest.z - g_camera[0].posR.z) * 0.07f;
	g_camera[0].posV.x += (g_camera[0].posVDest.x - g_camera[0].posV.x) * 0.07f;
	g_camera[0].posV.z += (g_camera[0].posVDest.z - g_camera[0].posV.z) * 0.07f;

	//移動更新
	g_camera[0].posR.x = g_camera[0].posV.x + sinf(g_camera[0].rot.y) * g_camera[0].fDistance;
	g_camera[0].posR.z = g_camera[0].posV.z + cosf(g_camera[0].rot.y) * g_camera[0].fDistance;

	//xの角度が範囲から超えた場合(角度の正規化)
	if (g_camera[0].rot.x < -D3DX_PI)
	{//角度が-3.14よりも小さくなった場合
		g_camera[0].rot.x += D3DX_PI * 2;
	}
	else if (g_camera[0].rot.x > D3DX_PI)
	{//角度が3.14よりも大きくなった場合
		g_camera[0].rot.x -= D3DX_PI * 2;
	}

	//yの角度が範囲から超えた場合(角度の正規化)
	if (g_camera[0].rot.y < -D3DX_PI)
	{//角度が-3.14よりも小さくなった場合
		g_camera[0].rot.y += D3DX_PI * 2;
	}
	else if (g_camera[0].rot.y > D3DX_PI)
	{//角度が3.14よりも大きくなった場合
		g_camera[0].rot.y -= D3DX_PI * 2;
	}

	//zの角度が範囲から超えた場合(角度の正規化)
	if (g_camera[0].rot.z < -D3DX_PI)
	{//角度が-3.14よりも小さくなった場合
		g_camera[0].rot.z += D3DX_PI * 2;
	}
	else if (g_camera[0].rot.z > D3DX_PI)
	{//角度が3.14よりも大きくなった場合
		g_camera[0].rot.z -= D3DX_PI * 2;
	}

	//-------------------2個目のカメラ---------------------------
	//注視点
	g_camera[1].posRDest.x = 750.5f + sinf(D3DX_PI) * -150.0f;
	g_camera[1].posRDest.z = 350.5f + cosf(D3DX_PI) * -150.0f;

	//視点
	g_camera[1].posVDest.x = 750.5f - sinf(g_camera[1].rot.y) * 250.0f;
	g_camera[1].posVDest.z = 350.5f - cosf(g_camera[1].rot.y) * 250.0f;

	//代入
	g_camera[1].posR.x += (g_camera[1].posRDest.x - g_camera[1].posR.x) * 0.1f;
	g_camera[1].posR.z += (g_camera[1].posRDest.z - g_camera[1].posR.z) * 0.1f;
	g_camera[1].posV.x += (g_camera[1].posVDest.x - g_camera[1].posV.x) * 0.1f;
	g_camera[1].posV.z += (g_camera[1].posVDest.z - g_camera[1].posV.z) * 0.1f;
}

//-------------------------------------------
//設定処理
//-------------------------------------------
void SetCamera(int nCntCamere)
{
	//デバイスの取得nm
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera[nCntCamere].mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_camera[nCntCamere].mtxView, &g_camera[nCntCamere].posV, &g_camera[nCntCamere].posR, &g_camera[nCntCamere].vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera[nCntCamere].mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera[nCntCamere].mtxProjection);

	switch (nCntCamere)
	{
	case 0:		//nCntCameraが0だったら
		//プロジェクションマトリックスの作成
		D3DXMatrixPerspectiveFovLH(&g_camera[0].mtxProjection,
			D3DXToRadian(45.0f),								//視野角
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,			//アスペクト比
			10.0f,												//ニア
			1000.0f);											//ファー
		break;
	case 1:		//nCntCameraが1だったら
		//プロジェクションマトリックスの作成
		D3DXMatrixPerspectiveFovLH(&g_camera[1].mtxProjection,
			D3DXToRadian(20.0f),								//視野角
			(float)250.0f / (float)250.0f,						//アスペクト比
			0.0f,												//ニア
			1280.0f);											//ファー
		break;
	default:
		break;
	}

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera[nCntCamere].mtxProjection);
}

//-------------------------------------------
//カメラの旋回処理
//-------------------------------------------
void TurningCamera(void)
{
		//視点の旋回
		if (GetKeyboardPress(DIK_Z) == true)
		{//Zキーを押した場合、時計回り
			g_camera[0].rot.y += CAMERA_ANGLE;
			g_camera[0].posV.x = g_camera[0].posR.x - sinf(g_camera[0].rot.y) * g_camera[0].fDistance;
			g_camera[0].posV.z = g_camera[0].posR.z - cosf(g_camera[0].rot.y) * g_camera[0].fDistance;
		}
		else if (GetKeyboardPress(DIK_C) == true)
		{//Cキーを押した場合、反時計回り
			g_camera[0].rot.y -= CAMERA_ANGLE;
			g_camera[0].posV.x = g_camera[0].posR.x - sinf(g_camera[0].rot.y) * g_camera[0].fDistance;
			g_camera[0].posV.z = g_camera[0].posR.z - cosf(g_camera[0].rot.y) * g_camera[0].fDistance;
		}
}

//-------------------------------------------
//カメラの移動処理
//-------------------------------------------
void MoveCamera(void)
{
	if (GetKeyboardPress(DIK_A) == true)
	{//Aキーを押したら左に進む
		g_camera[1].posV.x -= sinf(g_camera[1].rot.y + (D3DX_PI / 2.0f)) * CAMERA_DIS;
		g_camera[1].posV.z -= cosf(g_camera[1].rot.y + (D3DX_PI / 2.0f)) * CAMERA_DIS;

		if (GetKeyboardPress(DIK_W) == true)
		{//Wキーを押したら左前に進む
			g_camera[1].posV.x -= sinf(g_camera[1].rot.y + D3DX_PI) * CAMERA_DIS;
			g_camera[1].posV.z -= cosf(g_camera[1].rot.y + D3DX_PI) * CAMERA_DIS;
		}

		else if (GetKeyboardPress(DIK_S) == true)
		{//Sキーを押したら左後ろに進む
			g_camera[1].posV.x += sinf(g_camera[1].rot.y + D3DX_PI) * CAMERA_DIS;
			g_camera[1].posV.z += cosf(g_camera[1].rot.y + D3DX_PI) * CAMERA_DIS;
		}
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{//Dキーを押したら右に進む
		g_camera[1].posV.x += sinf(g_camera[1].rot.y + (D3DX_PI / 2.0f)) * CAMERA_DIS;
		g_camera[1].posV.z += cosf(g_camera[1].rot.y + (D3DX_PI / 2.0f)) * CAMERA_DIS;

		if (GetKeyboardPress(DIK_W) == true)
		{//Wキーを押したら右前に進む
			g_camera[1].posV.x -= sinf(g_camera[1].rot.y + D3DX_PI) * CAMERA_DIS;
			g_camera[1].posV.z -= cosf(g_camera[1].rot.y + D3DX_PI) * CAMERA_DIS;
		}

		else if (GetKeyboardPress(DIK_S) == true)
		{//Sキーを押したら右後ろに進む
			g_camera[1].posV.x += sinf(g_camera[1].rot.y + D3DX_PI) * CAMERA_DIS;
			g_camera[1].posV.z += cosf(g_camera[1].rot.y + D3DX_PI) * CAMERA_DIS;
		}
	}
	else if (GetKeyboardPress(DIK_W) == true)
	{//Wキーを押したら前に進む
		g_camera[1].posV.x -= sinf(g_camera[1].rot.y + D3DX_PI) * CAMERA_DIS;
		g_camera[1].posV.z -= cosf(g_camera[1].rot.y + D3DX_PI) * CAMERA_DIS;

		if (GetKeyboardPress(DIK_A) == true)
		{//Aキーを押したら左前に進む
			g_camera[1].posV.x -= sinf(g_camera[1].rot.y + (D3DX_PI / 2.0f)) * CAMERA_DIS;
			g_camera[1].posV.z -= cosf(g_camera[1].rot.y + (D3DX_PI / 2.0f)) * CAMERA_DIS;
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//Dキーを押したら右前に進む
			g_camera[1].posV.x += sinf(g_camera[1].rot.y + (D3DX_PI / 2.0f)) * CAMERA_DIS;
			g_camera[1].posV.z += cosf(g_camera[1].rot.y + (D3DX_PI / 2.0f)) * CAMERA_DIS;
		}
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{//Sキーを押したら後ろに進む
		g_camera[1].posV.x += sinf(g_camera[1].rot.y + D3DX_PI) * CAMERA_DIS;
		g_camera[1].posV.z += cosf(g_camera[1].rot.y + D3DX_PI) * CAMERA_DIS;

		if (GetKeyboardPress(DIK_A) == true)
		{//Aキーを押したら左後ろに進む
			g_camera[1].posV.x -= sinf(g_camera[1].rot.y + (D3DX_PI / 2.0f)) * CAMERA_DIS;
			g_camera[1].posV.z -= cosf(g_camera[1].rot.y + (D3DX_PI / 2.0f)) * CAMERA_DIS;
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//Dキーを押したら右後ろに進む
			g_camera[1].posV.x += sinf(g_camera[1].rot.y + (D3DX_PI / 2.0f)) * CAMERA_DIS;
			g_camera[1].posV.z += cosf(g_camera[1].rot.y + (D3DX_PI / 2.0f)) * CAMERA_DIS;
		}
	}
	//移動更新
	//g_camera[1].posR.x = g_camera[1].posV.x + sinf(g_camera[1].rot.y) * g_camera[1].fDistance;
	//g_camera[1].posR.z = g_camera[1].posV.z + cosf(g_camera[1].rot.y) * g_camera[1].fDistance;
}

//-------------------------------------------
//カメラの取得処理
//-------------------------------------------
Camera * GetCamera(void)
{
	return &g_camera[0];
}