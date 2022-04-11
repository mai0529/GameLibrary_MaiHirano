////----------------------------------------
////　モデルの処理
////　Author：橋野幹生
////----------------------------------------
//#include "model.h"
//#include "camera.h"
//#include "input.h"
//#include "shadow.h"
//#include "disc.h"
//
//
////グローバル変数宣言
//LPDIRECT3DTEXTURE9 g_pTextureModel = NULL;	//テクスチャへのポインタ
//LPD3DXMESH g_pMeshModel = NULL;				//メッシュ情報へのポインタ
//LPD3DXBUFFER g_pBuffMatModel = NULL;		//マテリアル情報へのポインタ
//DWORD g_nNumMatModel = 0;					//マテリアル情報の数
//Model g_aModel[MAX_MODEL];
////int g_SelectModel;							//モデル選択用
//
////プロトタイプ宣言
//void MovePlayer1(void);
//
////---------------------------------------------------
////	モデルの初期化処理
////---------------------------------------------------
//void InitModel(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//	//テクスチャの読み込み
//	D3DXCreateTextureFromFile(
//		pDevice,
//		"data\\TEXTURE\\uroko_red.jpg",
//		&g_pTextureModel);
//
//	//Ⅹファイルの読み込み
//	D3DXLoadMeshFromX("data\\MODEL\\tank100.x",
//		D3DXMESH_SYSTEMMEM,
//		pDevice,
//		NULL,
//		&g_pBuffMatModel,
//		NULL,
//		&g_nNumMatModel,
//		&g_pMeshModel);
//
//	//各値の初期化
//	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
//	{
//		g_aModel[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
//		g_aModel[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向き
//		g_aModel[nCntModel].diff = 0.0f;							//差分計算用
//		g_aModel[nCntModel].rotDestModel = 0.0f;					//目的の角度
//		g_aModel[nCntModel].IdxShadow = SetShadow(D3DXVECTOR3(g_aModel[nCntModel].pos.x, 0.1f, g_aModel[nCntModel].pos.z), g_aModel[nCntModel].rot);
//		g_aModel[nCntModel].bUse = false;							//使ってるかどうか
//	}
//	//g_SelectModel = 0;
//
//	//モデルセット
//	SetModel(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
//
//
//	//ディスクの位置
//	SetPosDisc(D3DXVECTOR3(g_aModel[0].pos.x, g_aModel[0].pos.y + 20.0f, g_aModel[0].pos.z)/*, PLAYER_P1*/);
//}//うわぁ
//
////---------------------------------------------------
////	モデルの終了処理
////---------------------------------------------------
//void UninitModel(void)
//{
//	//メッシュ破棄
//	if (g_pMeshModel != NULL)
//	{
//		g_pMeshModel->Release();
//		g_pMeshModel = NULL;
//	}
//
//	//マテリアル破棄
//	if (g_pBuffMatModel != NULL)
//	{
//		g_pBuffMatModel->Release();
//		g_pBuffMatModel = NULL;
//	}
//
//	//テクスチャ破棄
//	if (g_pTextureModel != NULL)
//	{
//		g_pTextureModel->Release();
//		g_pTextureModel = NULL;
//	}
//}
//
////---------------------------------------------------
////	モデルの更新処理
////---------------------------------------------------
//void UpdateModel(void)
//{
//
//	//モデルの移動処理
//	MoveModel();
//
//	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
//	{
//		CollisionDisc_Player(&g_aModel[nCnt].pos, D3DXVECTOR3(5.0f, 5.0f, 5.0f), g_aModel[nCnt].type);
//	}
//
//	//影の位置を更新
//	SetPositionShadow(0, D3DXVECTOR3(g_aModel[0].pos.x, 0.1f, g_aModel[0].pos.z));
//
//	//SetPositionDisc(D3DXVECTOR3(g_aModel[0].pos.x, g_aModel[0].pos.y + 20.0f, g_aModel[0].pos.z));
//}
//
////---------------------------------------------------
////	モデルの移動処理
////---------------------------------------------------
//void MoveModel(void)
//{
//	MovePlayer1();
//}
//
////---------------------------------------------------
////	プレイヤー1の移動処理
////---------------------------------------------------
//void MovePlayer1(void)
//{
//	Camera * pCamera = GetCamera();
//
//	if (GetKeyboardPress(DIK_UPARROW) == true)
//	{//↑キーが押されたとき
//		if (GetKeyboardPress(DIK_RIGHTARROW) == true)
//		{//←キーと押されたとき(左斜め上方向)
//			g_aModel[0].pos.x += sinf(pCamera->rot.y + (D3DX_PI / 4)) * MODEL_SPEED;	//モデルの位置移動
//			g_aModel[0].pos.z += cosf(pCamera->rot.y + (D3DX_PI / 4)) * MODEL_SPEED;
//
//			g_aModel[0].rotDestModel = pCamera->rot.y - (D3DX_PI / 4 * 3.0f);			//モデルの向き変更
//		}
//		else if (GetKeyboardPress(DIK_LEFTARROW) == true)
//		{//→キーと押されたとき(右斜め上方向)
//			g_aModel[0].pos.x += sinf(pCamera->rot.y - (D3DX_PI / 4)) * MODEL_SPEED;	//モデルの位置移動
//			g_aModel[0].pos.z += cosf(pCamera->rot.y - (D3DX_PI / 4)) * MODEL_SPEED;
//
//			g_aModel[0].rotDestModel = pCamera->rot.y + (D3DX_PI / 4 * 3.0f);			//モデルの向き変更
//		}
//		else
//		{//↑キーのみ(上方向へ移動)
//			g_aModel[0].pos.x += sinf(pCamera->rot.y) * MODEL_SPEED;	//モデルの位置移動
//			g_aModel[0].pos.z += cosf(pCamera->rot.y) * MODEL_SPEED;
//
//			g_aModel[0].rotDestModel = pCamera->rot.y + D3DX_PI;		//モデルの向き変更
//		}
//	}
//	else if (GetKeyboardPress(DIK_DOWNARROW) == true)
//	{//↓キーが押されたとき
//		if (GetKeyboardPress(DIK_RIGHTARROW) == true)
//		{//←キーと押されたとき(左斜め下方向)
//			g_aModel[0].pos.x += sinf(pCamera->rot.y + (D3DX_PI / 4 * 3.0f)) * MODEL_SPEED;		//モデルの位置移動
//			g_aModel[0].pos.z += cosf(pCamera->rot.y + (D3DX_PI / 4 * 3.0f)) * MODEL_SPEED;
//
//			g_aModel[0].rotDestModel = pCamera->rot.y - (D3DX_PI / 4);							//モデルの向き変更
//		}
//		else if (GetKeyboardPress(DIK_LEFTARROW) == true)
//		{//→キーと押されたとき(右斜め下方向)
//			g_aModel[0].pos.x += sinf(pCamera->rot.y - (D3DX_PI / 4 * 3.0f)) * MODEL_SPEED;		//モデルの位置移動
//			g_aModel[0].pos.z += cosf(pCamera->rot.y - (D3DX_PI / 4 * 3.0f)) * MODEL_SPEED;
//
//			g_aModel[0].rotDestModel = pCamera->rot.y + (D3DX_PI / 4);							//モデルの向き変更
//		}
//		else
//		{//↓キーのみ(下方向へ移動)
//			g_aModel[0].pos.x += sinf(pCamera->rot.y + D3DX_PI) * MODEL_SPEED;		//モデルの位置移動
//			g_aModel[0].pos.z += cosf(pCamera->rot.y + D3DX_PI) * MODEL_SPEED;
//
//			g_aModel[0].rotDestModel = pCamera->rot.y;								//モデルの向き変更
//		}
//	}
//	else if (GetKeyboardPress(DIK_RIGHTARROW) == true)
//	{//→キーが押されたとき(右方向へ移動)
//		g_aModel[0].pos.x += sinf(pCamera->rot.y + (D3DX_PI / 2)) * MODEL_SPEED;	//モデルの位置移動
//		g_aModel[0].pos.z += cosf(pCamera->rot.y + (D3DX_PI / 2)) * MODEL_SPEED;
//
//		g_aModel[0].rotDestModel = pCamera->rot.y - (D3DX_PI / 2);					//モデルの向き変更
//	}
//	else if (GetKeyboardPress(DIK_LEFTARROW) == true)
//	{//←キーが押されたとき(左方向へ移動)
//		g_aModel[0].pos.x += sinf(pCamera->rot.y - (D3DX_PI / 2)) * MODEL_SPEED;	//モデルの位置移動
//		g_aModel[0].pos.z += cosf(pCamera->rot.y - (D3DX_PI / 2)) * MODEL_SPEED;
//
//		g_aModel[0].rotDestModel = pCamera->rot.y + (D3DX_PI / 2);					//モデルの向き変更
//	}
//
//	if (GetKeyboardTrigger(DIK_SPACE) == true)
//	{//スペースキーが押されたら
//
//		SetMoveDisc(D3DXVECTOR3(g_aModel[0].rot),	//角度
//			//g_aModel[0].type,		//P1という情報
//			7.5f, SHOT_NOMAL);		//ディスクのスピード
//
//		
//		
//		//D3DXVECTOR3(g_aModel[0].rot));	//角度
//		
//	}
//
//	if (GetKeyboardTrigger(DIK_N) == true)
//	{
//		SetMoveDisc(D3DXVECTOR3(g_aModel[0].rot),	//角度
//			//g_aModel[0].type,	//P1という情報
//			1.0f, SHOT_CURVE);		//ディスクのスピード
//	}
//
//	//if (GetKeyboardTrigger(DIK_M) == true)
//	//{
//	//	SetMoveDisc(D3DXVECTOR3(g_aModel[0].rot),	//角度
//	//		//g_aModel[0].type,	//P1という情報
//	//		1.0f, SHOT_CIRCLE);		//ディスクのスピード
//	//}
//
//	//角度の正規化
//	if (g_aModel[0].rot.y > D3DX_PI)
//	{
//		g_aModel[0].rot.y -= D3DX_PI * 2;
//	}
//	else if (g_aModel[0].rot.y < -D3DX_PI)
//	{
//		g_aModel[0].rot.y += D3DX_PI * 2;
//	}
//
//	//差分の計算
//	g_aModel[0].diff = (g_aModel[0].rotDestModel - g_aModel[0].rot.y);
//
//	//差分の正規化
//	if (g_aModel[0].diff > D3DX_PI)
//	{
//		g_aModel[0].diff -= D3DX_PI * 2;
//	}
//	else if (g_aModel[0].diff < -D3DX_PI)
//	{
//		g_aModel[0].diff += D3DX_PI * 2;
//	}
//
//	//モデルの移動を滑らかにするやつ
//	g_aModel[0].rot.y += g_aModel[0].diff * 0.1f;
//}
//
////---------------------------------------------------
////	モデルの描画処理
////---------------------------------------------------
//void DrawModel(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
//	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
//	D3DXMATERIAL * pMat;			//マテリアルデータへのポインタ
//
//	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
//	{
//		if (g_aModel[nCntModel].bUse == true)
//		{
//			//ワールドマトリックスの初期化
//			D3DXMatrixIdentity(&g_aModel[nCntModel].mtxWorld);
//
//			//向きを反映
//			D3DXMatrixRotationYawPitchRoll(&mtxRot,
//				g_aModel[nCntModel].rot.y, g_aModel[nCntModel].rot.x, g_aModel[nCntModel].rot.z);
//			D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorld,
//				&g_aModel[nCntModel].mtxWorld, &mtxRot);
//
//			//位置を反映
//			D3DXMatrixTranslation(&mtxTrans, g_aModel[nCntModel].pos.x, g_aModel[nCntModel].pos.y, g_aModel[nCntModel].pos.z);
//			D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorld, &g_aModel[nCntModel].mtxWorld, &mtxTrans);
//
//			//ワールドマトリックスの設定
//			pDevice->SetTransform(D3DTS_WORLD, &g_aModel[nCntModel].mtxWorld);
//
//			//現在のマテリアル保持
//			pDevice->GetMaterial(&matDef);
//
//			//マテリアルデータへのポインタを取得
//			pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();
//
//			for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
//			{
//				//マテリアルの設定
//				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
//
//				//モデルパーツの描画
//				g_pMeshModel->DrawSubset(nCntMat);
//
//				//テクスチャの設定
//				pDevice->SetTexture(0, NULL);
//			}
//
//			//保持していたマテリアルを戻す
//			pDevice->SetMaterial(&matDef);
//		}
//	}
//}
//
////---------------------------------------------------
////	モデルの情報
////---------------------------------------------------
//Model * GetModel(void)
//{
//	return g_aModel;
//}
//
////---------------------------------------------------
////	モデルの設定
////---------------------------------------------------
//void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
//{
//	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
//	{
//		if (g_aModel[nCntModel].bUse == false)
//		{// bUseがfalseだったら、
//			g_aModel[nCntModel].pos = pos;
//			g_aModel[nCntModel].rot = rot;
//			g_aModel[nCntModel].bUse = true;
//			//g_aModel[nCntModel].type ;
//
//			break;
//		}
//	}
//}
