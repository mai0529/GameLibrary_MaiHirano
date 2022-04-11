

//----------------------------------------
//　プレイヤーの処理
//　Author：橋野幹生
//----------------------------------------
#include <stdio.h>
#include <string.h>
#include "player.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "wall.h"
#include "bullet.h"
#include "effect.h"
#include "line.h"
#include "model.h"
#include "fade.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;	//テクスチャへのポインタ
LPD3DXMESH g_pMeshPlayer = NULL;			//メッシュ情報へのポインタ
LPD3DXBUFFER g_pBuffMatPlayer = NULL;		//マテリアル情報へのポインタ
DWORD g_nNumMatPlayer = 0;					//マテリアル情報の数
Player g_Player;							//プレイヤーの変数宣言

int nNowFrame = 0;		//現在のフレーム数
int nCntFrame = 0;		//総再生フレーム数
int nNowKeySet = 0;					//現在再生中のKeySet番号
int nNextKeySet = nNowKeySet + 1;	//次に再生するKeySet番号
int nPlayMotion = 0;	//現在再生中のモーション番号
int g_MaxSetMotion;

//パーツセットの構造体
typedef struct
{
	int nIndex;
	int nParent;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
}PartsSet;

//モーションセットの構造体
typedef struct
{
	int nLoop;				//ループするかどうか
	int nNumKey;			//最大キー数
	int nFrame;				//フレーム数
	D3DXVECTOR3 pos[20];
	D3DXVECTOR3 rot[20];
}MotionSet;

FILE * pFile;
int g_nNumModel = 0;
int g_nNumParts = 0;
char g_aModelPas[20][256];
PartsSet g_PartsSet[20];
MotionSet g_MotionSet[10][10];
D3DXVECTOR3 MotionDiff[20];
D3DXVECTOR3 PosDiff[20];
int nMaxFram[20];			//合計フレーム数

							//---------------------------------------------------
							//	プレイヤーのモーション読み込み
							//---------------------------------------------------
void Load(void)
{
	char nData111[256];
	int nData;
	float fData;
	int nCntModel = 0;
	int nCntParts = 0;
	int nCntMotion = 0;
	int nCntKeyParts = 0;
	int nCntKey = 0;

	pFile = fopen("data\\motion.txt", "r");

	// strncmp : 指定した文字数比較する
	// sscanf : 指定した所を変数に入れる
	// fgetc : 一行を読み込み

	if (pFile != NULL)
	{//ファイルを開けたら
		do
		{//"SCRIPT"と一致するまで回す
			fscanf(pFile, "%s", &nData111[0]);
		} while (strcmp(&nData111[0], "SCRIPT") != 0);

		do
		{//"END_SCRIPT"と一致するまで回す
			fscanf(pFile, "%s", &nData111[0]);

			if (strcmp(&nData111[0], "NUM_MODEL") == 0)
			{
				fscanf(pFile, "%s", &nData111[0]);
				fscanf(pFile, "%d", &g_nNumModel);

				for (int i = 0; i < g_nNumModel; i++, nCntModel++)
				{
					do
					{//"MODEL_FILENAME"と一致するまで回す
						fscanf(pFile, "%s", &nData111[0]);
					} while (strcmp(&nData111[0], "MODEL_FILENAME") != 0);

					if (strcmp(&nData111[0], "MODEL_FILENAME") == 0)
					{
						fscanf(pFile, "%s", &nData111[0]);
						fscanf(pFile, "%s", &g_aModelPas[nCntModel][0]);
					}
				}
			}
			if (strcmp(&nData111[0], "CHARACTERSET") == 0)
			{
				do
				{//"END_CHARACTERSET"と一致するまで回す
					fscanf(pFile, "%s", &nData111[0]);

					if (strcmp(&nData111[0], "NUM_PARTS") == 0)
					{
						fscanf(pFile, "%s", &nData111[0]);
						fscanf(pFile, "%d", &g_nNumParts);

						for (int i = 0; i < g_nNumParts; i++, nCntParts++)
						{
							do
							{//"PARTSSET"と一致するまで回す
								fscanf(pFile, "%s", &nData111[0]);
							} while (strcmp(&nData111[0], "PARTSSET") != 0);

							if (strcmp(&nData111[0], "PARTSSET") == 0)
							{
								do
								{//"END_PARTSSET"と一致するまで回す
									fscanf(pFile, "%s", &nData111[0]);

									if (strcmp(&nData111[0], "INDEX") == 0)
									{
										fscanf(pFile, "%s", &nData111[0]);
										fscanf(pFile, "%d", &nData);
										g_PartsSet[nCntParts].nIndex = nData;
									}
									if (strcmp(&nData111[0], "PARENT") == 0)
									{
										fscanf(pFile, "%s", &nData111[0]);
										fscanf(pFile, "%d", &nData);
										g_PartsSet[nCntParts].nParent = nData;
									}
									if (strcmp(&nData111[0], "POS") == 0)
									{
										fscanf(pFile, "%s", &nData111[0]);
										fscanf(pFile, "%f", &fData);
										g_PartsSet[nCntParts].pos.x = fData;
										fscanf(pFile, "%f", &fData);
										g_PartsSet[nCntParts].pos.y = fData;
										fscanf(pFile, "%f", &fData);
										g_PartsSet[nCntParts].pos.z = fData;
									}
									if (strcmp(&nData111[0], "ROT") == 0)
									{
										fscanf(pFile, "%s", &nData111[0]);
										fscanf(pFile, "%f", &fData);
										g_PartsSet[nCntParts].rot.x = fData;
										fscanf(pFile, "%f", &fData);
										g_PartsSet[nCntParts].rot.y = fData;
										fscanf(pFile, "%f", &fData);
										g_PartsSet[nCntParts].rot.z = fData;
									}
								} while (strcmp(&nData111[0], "END_PARTSSET") != 0);
							}
						}
					}
				} while (strcmp(&nData111[0], "END_CHARACTERSET") != 0);
			}
			if (strcmp(&nData111[0], "MOTIONSET") == 0)
			{
				do
				{//"END_MOTIONSET"と一致するまで回す
					fscanf(pFile, "%s", &nData111[0]);

					if (strcmp(&nData111[0], "LOOP") == 0)
					{// "LOOP"と一致したとき
						fscanf(pFile, "%s", &nData111[0]);		// "="
						fscanf(pFile, "%d", &g_MotionSet[g_MaxSetMotion][nCntKey].nLoop);	//ループ
					}
					if (strcmp(&nData111[0], "NUM_KEY") == 0)
					{// "NUM_KEY"と一致したとき
						fscanf(pFile, "%s", &nData111[0]);		// "="
						fscanf(pFile, "%d", &g_MotionSet[g_MaxSetMotion][nCntKey].nNumKey);		//キー数
					}
					if (strcmp(&nData111[0], "KEYSET") == 0)
					{// "KEYSET"と一致したとき
						do
						{//"END_KEYSET"と一致するまで回す
							fscanf(pFile, "%s", &nData111[0]);

							if (strcmp(&nData111[0], "FRAME") == 0)
							{// "FRAME"と一致したとき
								fscanf(pFile, "%s", &nData111[0]);		// "="
								fscanf(pFile, "%d", &g_MotionSet[g_MaxSetMotion][nCntKey].nFrame);		//フレーム数

																										//フレーム数を合計する
								nMaxFram[nCntKey] += g_MotionSet[g_MaxSetMotion][nCntKey].nFrame;
							}
							if (strcmp(&nData111[0], "KEY") == 0)
							{// "KEY"と一致したとき
								do
								{//"END_KEY"と一致するまで回す
									fscanf(pFile, "%s", &nData111[0]);

									if (strcmp(&nData111[0], "POS") == 0)
									{// "POS"と一致したとき
										fscanf(pFile, "%s", &nData111[0]);		// "="
										fscanf(pFile, "%f", &fData);			// x座標
										g_MotionSet[g_MaxSetMotion][nCntKey].pos[nCntKeyParts].x = fData;
										fscanf(pFile, "%f", &fData);			// x座標
										g_MotionSet[g_MaxSetMotion][nCntKey].pos[nCntKeyParts].y = fData;
										fscanf(pFile, "%f", &fData);			// x座標
										g_MotionSet[g_MaxSetMotion][nCntKey].pos[nCntKeyParts].z = fData;
									}
									if (strcmp(&nData111[0], "ROT") == 0)
									{// "ROT"と一致したとき
										fscanf(pFile, "%s", &nData111[0]);		// "="
										fscanf(pFile, "%f", &fData);			// x座標
										g_MotionSet[g_MaxSetMotion][nCntKey].rot[nCntKeyParts].x = fData;
										fscanf(pFile, "%f", &fData);			// x座標
										g_MotionSet[g_MaxSetMotion][nCntKey].rot[nCntKeyParts].y = fData;
										fscanf(pFile, "%f", &fData);			// x座標
										g_MotionSet[g_MaxSetMotion][nCntKey].rot[nCntKeyParts].z = fData;
									}
								} while (strcmp(&nData111[0], "END_KEY") != 0);

								//パーツ数+1
								nCntKeyParts++;
							}
						} while (strcmp(&nData111[0], "END_KEYSET") != 0);
						//キー数を +1 する
						nCntKey++;
						nCntKeyParts = 0;
					}
				} while (strcmp(&nData111[0], "END_MOTIONSET") != 0);
				g_MaxSetMotion++;
				nCntKey = 0;
			}
		} while (strcmp(&nData111[0], "END_SCRIPT") != 0);
	}
	else
	{//ファイルが開けなかった場合

	}

	//確認用
	//ファイルを開く
	pFile = fopen("data\\teswt.txt", "w");		//(テキスト名を指定, モードを指定)

	if (pFile != NULL)
	{//ファイルが開けた場合
	 //for (int i = 0; i < g_nNumParts; i++)
	 //{
	 //	fprintf(pFile, "%s\n", &g_aModelPas[i][0]);
	 //}

		for (int i = 0; i < nCntKey; i++)
		{
			for (int i2 = 0; i2 < g_nNumParts; i2++)
			{
				fprintf(pFile, "%f\n", g_MotionSet[g_MaxSetMotion][i].pos[i2].x, g_MotionSet[g_MaxSetMotion][i].pos[i2].y, g_MotionSet[g_MaxSetMotion][i].pos[i2].z);
				fprintf(pFile, "\n");	//改行
				fprintf(pFile, "%f　%f　%f", g_MotionSet[g_MaxSetMotion][i].rot[i2].x, g_MotionSet[g_MaxSetMotion][i].rot[i2].y, g_MotionSet[g_MaxSetMotion][i].rot[i2].z);
				fprintf(pFile, "\n\n");	//改行
			}
			fprintf(pFile, "\n\n");	//改行
		}
		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		printf("\n***　ファイルが開けませんでした　***\n");
	}
}

//---------------------------------------------------
//	プレイヤーの初期化処理
//---------------------------------------------------
void InitPlayer(void)
{
	Load();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//デバイス情報を取得

														//パーツの各値の初期化
	for (int nCntParts = 0; nCntParts < g_nNumParts; nCntParts++)
	{
		g_Player.aModel[nCntParts].pos = g_PartsSet[nCntParts].pos;
		g_Player.aModel[nCntParts].rot = g_PartsSet[nCntParts].rot;
		g_Player.aModel[nCntParts].nIdxModelParent = g_PartsSet[nCntParts].nParent;
	}

	//プレイヤーの各値の初期化
	{
		g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//現在の位置
		g_Player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//前回の位置
		g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き
		g_Player.diff = 0.0f;								//差分計算用
		g_Player.rotDest = 0.0f;							//目的の角度
		g_Player.vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//頂点の最小値を取得用
		g_Player.vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//頂点の最大値を取得用
		g_Player.size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//サイズ保存用
	}

	//影を設定
	g_Player.IdxShadow = SetShadow(D3DXVECTOR3(g_Player.pos.x, 0.1f, g_Player.pos.z), g_Player.rot);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\uroko_red.jpg",
		&g_pTexturePlayer);

	int nNumVtx;		//頂点数
	DWORD sizeFVF;		//頂点フォーマットのサイズ
	BYTE * pVtxBuff;	//頂点バッファへのポインタ

						//Ⅹファイルの読み込み
	for (int nCntParts = 0; nCntParts < g_nNumParts; nCntParts++)
	{
		D3DXLoadMeshFromX(&g_aModelPas[nCntParts][0],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Player.aModel[nCntParts].pBuffMat,
			NULL,
			&g_Player.aModel[nCntParts].nNumMat,
			&g_Player.aModel[nCntParts].pMesh);
	}

	g_Player.vtxMin = D3DXVECTOR3(-30.0f, 0.0f, -30.0f);
	g_Player.vtxMax = D3DXVECTOR3(30.0f, 110.0f, 30.0f);

	g_Player.size.x = g_Player.vtxMax.x - g_Player.vtxMin.x;
	g_Player.size.y = g_Player.vtxMax.y - g_Player.vtxMin.y;
	g_Player.size.z = g_Player.vtxMax.z - g_Player.vtxMin.z;

	//周りにラインを引く
	/**/
	SetLine(g_Player.pos,
		g_Player.rot,
		D3DXVECTOR3(g_Player.vtxMin.x, g_Player.vtxMin.y, g_Player.vtxMax.z),
		D3DXVECTOR3(g_Player.vtxMax.x, g_Player.vtxMin.y, g_Player.vtxMax.z),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	SetLine(g_Player.pos,
		g_Player.rot,
		D3DXVECTOR3(g_Player.vtxMin.x, g_Player.vtxMax.y, g_Player.vtxMax.z),
		D3DXVECTOR3(g_Player.vtxMax.x, g_Player.vtxMax.y, g_Player.vtxMax.z),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	SetLine(g_Player.pos,
		g_Player.rot,
		D3DXVECTOR3(g_Player.vtxMin.x, g_Player.vtxMin.y, g_Player.vtxMin.z),
		D3DXVECTOR3(g_Player.vtxMax.x, g_Player.vtxMin.y, g_Player.vtxMin.z),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	SetLine(g_Player.pos,
		g_Player.rot,
		D3DXVECTOR3(g_Player.vtxMin.x, g_Player.vtxMax.y, g_Player.vtxMin.z),
		D3DXVECTOR3(g_Player.vtxMax.x, g_Player.vtxMax.y, g_Player.vtxMin.z),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


	SetLine(g_Player.pos,
		g_Player.rot,
		D3DXVECTOR3(g_Player.vtxMax.x, g_Player.vtxMin.y, g_Player.vtxMin.z),
		D3DXVECTOR3(g_Player.vtxMax.x, g_Player.vtxMin.y, g_Player.vtxMax.z),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	SetLine(g_Player.pos,
		g_Player.rot,
		D3DXVECTOR3(g_Player.vtxMax.x, g_Player.vtxMax.y, g_Player.vtxMin.z),
		D3DXVECTOR3(g_Player.vtxMax.x, g_Player.vtxMax.y, g_Player.vtxMax.z),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	SetLine(g_Player.pos,
		g_Player.rot,
		D3DXVECTOR3(g_Player.vtxMin.x, g_Player.vtxMin.y, g_Player.vtxMin.z),
		D3DXVECTOR3(g_Player.vtxMin.x, g_Player.vtxMin.y, g_Player.vtxMax.z),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	SetLine(g_Player.pos,
		g_Player.rot,
		D3DXVECTOR3(g_Player.vtxMin.x, g_Player.vtxMax.y, g_Player.vtxMin.z),
		D3DXVECTOR3(g_Player.vtxMin.x, g_Player.vtxMax.y, g_Player.vtxMax.z),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


	SetLine(g_Player.pos,
		g_Player.rot,
		D3DXVECTOR3(g_Player.vtxMin.x, g_Player.vtxMin.y, g_Player.vtxMax.z),
		D3DXVECTOR3(g_Player.vtxMin.x, g_Player.vtxMax.y, g_Player.vtxMax.z),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	SetLine(g_Player.pos,
		g_Player.rot,
		D3DXVECTOR3(g_Player.vtxMax.x, g_Player.vtxMin.y, g_Player.vtxMin.z),
		D3DXVECTOR3(g_Player.vtxMax.x, g_Player.vtxMax.y, g_Player.vtxMin.z),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	SetLine(g_Player.pos,
		g_Player.rot,
		D3DXVECTOR3(g_Player.vtxMin.x, g_Player.vtxMin.y, g_Player.vtxMin.z),
		D3DXVECTOR3(g_Player.vtxMin.x, g_Player.vtxMax.y, g_Player.vtxMin.z),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	SetLine(g_Player.pos,
		g_Player.rot,
		D3DXVECTOR3(g_Player.vtxMax.x, g_Player.vtxMin.y, g_Player.vtxMax.z),
		D3DXVECTOR3(g_Player.vtxMax.x, g_Player.vtxMax.y, g_Player.vtxMax.z),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//---------------------------------------------------
//	プレイヤーの終了処理
//---------------------------------------------------
void UninitPlayer(void)
{
	//プレイヤーのメッシュ破棄
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	//モデルのメッシュ破棄
	for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
	{
		if (g_Player.aModel[nCntParts].pMesh != NULL)
		{
			g_Player.aModel[nCntParts].pMesh->Release();
			g_Player.aModel[nCntParts].pMesh = NULL;
		}
	}

	//プレイヤーのマテリアル破棄
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}

	//モデルのマテリアル破棄
	for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
	{
		if (g_Player.aModel[nCntParts].pBuffMat != NULL)
		{
			g_Player.aModel[nCntParts].pBuffMat->Release();
			g_Player.aModel[nCntParts].pBuffMat = NULL;
		}
	}

	//テクスチャ破棄
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
}

//---------------------------------------------------
//	プレイヤーの更新処理
//---------------------------------------------------
void UpdatePlayer(void)
{
	//重力
	g_Player.move.y -= 0.3f;

	//現在の座標を保存
	g_Player.posOld = g_Player.pos;

	//プレイヤーの移動処理
	MovePlayer();

	//重力を加算
	g_Player.pos.y += g_Player.move.y;

	//モデルの当たり判定
	CollisionModel(&g_Player.pos, &g_Player.posOld, g_Player.size, &g_Player.move);

	if (g_Player.pos.y <= 0.0f)
	{//床にいるとき
		g_Player.pos.y = 0.0f;
		g_Player.move.y = 0.0f;
	}

	//プレイヤーが移動している場合、エフェクトを付与
	if (g_Player.pos != g_Player.posOld)
	{
		SetEffect(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y, g_Player.pos.z), g_Player.rot, D3DXCOLOR(0.0f, 0.5f, 0.5f, 1.0f), 40, D3DXVECTOR3(3.0f, 3.0f, 0.0f));
		SetEffect(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y, g_Player.pos.z), g_Player.rot, D3DXCOLOR(0.5f, 0.5f, 0.0f, 1.0f), 40, D3DXVECTOR3(2.0f, 2.0f, 0.0f));
	}

	//影の位置を更新
	SetPositionShadow(0, D3DXVECTOR3(g_Player.pos.x, 0.1f, g_Player.pos.z));

	//MotionPlayer();		//モーション設定

	if (GetKeyboardTrigger(DIK_M) == true)
	{
		SetPlayer();		//モーション切り替え
	}
}

//---------------------------------------------------
//	プレイヤーのモーション処理
//---------------------------------------------------
void MotionPlayer(void)
{
	if (GetKeyboardTrigger(DIK_9) == true)
	{
		if (nCntFrame < nMaxFram[nPlayMotion])
		{
			//rot(角度)
			for (int i = 0; i < g_nNumParts; i++)
			{// パーツ数分回す
				MotionDiff[i].x = (g_MotionSet[nPlayMotion][nNextKeySet].rot[i].x - g_MotionSet[nPlayMotion][nNowKeySet].rot[i].x) / g_MotionSet[nPlayMotion][nNowKeySet].nFrame;
				MotionDiff[i].y = (g_MotionSet[nPlayMotion][nNextKeySet].rot[i].y - g_MotionSet[nPlayMotion][nNowKeySet].rot[i].y) / g_MotionSet[nPlayMotion][nNowKeySet].nFrame;
				MotionDiff[i].z = (g_MotionSet[nPlayMotion][nNextKeySet].rot[i].z - g_MotionSet[nPlayMotion][nNowKeySet].rot[i].z) / g_MotionSet[nPlayMotion][nNowKeySet].nFrame;

				g_Player.aModel[i].rot.x += (MotionDiff[i].x);
				g_Player.aModel[i].rot.y += (MotionDiff[i].y);
				g_Player.aModel[i].rot.z += (MotionDiff[i].z);
			}

			//pos(位置)
			for (int i = 0; i < g_nNumParts; i++)
			{// パーツ数分回す
				PosDiff[i].x = (g_MotionSet[nPlayMotion][nNextKeySet].pos[i].x - g_MotionSet[nPlayMotion][nNowKeySet].pos[i].x) / g_MotionSet[nPlayMotion][nNowKeySet].nFrame;
				PosDiff[i].y = (g_MotionSet[nPlayMotion][nNextKeySet].pos[i].y - g_MotionSet[nPlayMotion][nNowKeySet].pos[i].y) / g_MotionSet[nPlayMotion][nNowKeySet].nFrame;
				PosDiff[i].z = (g_MotionSet[nPlayMotion][nNextKeySet].pos[i].z - g_MotionSet[nPlayMotion][nNowKeySet].pos[i].z) / g_MotionSet[nPlayMotion][nNowKeySet].nFrame;

				g_Player.aModel[i].pos.x += (PosDiff[i].x);
				g_Player.aModel[i].pos.y += (PosDiff[i].y);
				g_Player.aModel[i].pos.z += (PosDiff[i].z);
			}

			if (nNowFrame >= g_MotionSet[nPlayMotion][nNowKeySet].nFrame)
			{// Frame分回ったら
				nNowFrame = 0;		//フレーム数を0(初期値)に戻す
				nNowKeySet++;		//次のキーに進む
				nNextKeySet++;		//再生中のキーの次のキーに進む

				if (nNextKeySet >= g_MotionSet[nPlayMotion][nPlayMotion].nNumKey)
				{
					nNextKeySet = 0;
				}
			}

			if (nNowKeySet >= g_MotionSet[nPlayMotion][0].nNumKey)
			{//キーが全部回ったら

				nNowKeySet = 0;	//最初のキーにする
				nNextKeySet = nNowKeySet + 1;	//最初のキーにする
												//break;
			}

			//フレーム数を1進める
			nNowFrame++;
			nCntFrame++;
		}
		else if (g_MotionSet[nPlayMotion][0].nLoop == 1)
		{
			nCntFrame = 0;
		}
	}
}

//---------------------------------------------------
//	モーション切り替え
//---------------------------------------------------
void SetPlayer()
{
	for (int i = 0; i < g_nNumParts; i++)
	{// パーツ数分回す
	 //rot(角度)
		g_Player.aModel[i].rot.x = 0.0f;
		g_Player.aModel[i].rot.y = 0.0f;
		g_Player.aModel[i].rot.z = 0.0f;
		//pos(位置)
		g_Player.aModel[i].pos.x = 0.0f;
		g_Player.aModel[i].pos.y = 0.0f;
		g_Player.aModel[i].pos.z = 0.0f;
	}
	nNowFrame = 0;
	nNowKeySet = 0;
	nNextKeySet = nNowKeySet + 1;
	nCntFrame = 0;

	nPlayMotion++;

	if (nPlayMotion >= g_MaxSetMotion)
	{
		nPlayMotion = 0;
	}
}

//---------------------------------------------------
//	プレイヤーの移動処理
//---------------------------------------------------
void MovePlayer(void)
{
	Camera * pCamera = GetCamera();		//カメラの情報取得

	if (GetKeyboardPress(DIK_UPARROW) == true)
	{//↑キーが押されたとき
		if (GetKeyboardPress(DIK_RIGHTARROW) == true)
		{//←キーと押されたとき(左斜め上方向)
			g_Player.pos.x += sinf(pCamera->rot.y + (D3DX_PI / 4)) * PLAYER_SPEED;	//プレイヤーの位置移動
			g_Player.pos.z += cosf(pCamera->rot.y + (D3DX_PI / 4)) * PLAYER_SPEED;
			//プレイヤーの目的の向きを設定
			g_Player.rotDest = pCamera->rot.y - (D3DX_PI / 4 * 3.0f);
		}
		else if (GetKeyboardPress(DIK_LEFTARROW) == true)
		{//→キーと押されたとき(右斜め上方向)
			g_Player.pos.x += sinf(pCamera->rot.y - (D3DX_PI / 4)) * PLAYER_SPEED;	//プレイヤーの位置移動
			g_Player.pos.z += cosf(pCamera->rot.y - (D3DX_PI / 4)) * PLAYER_SPEED;
			//プレイヤーの目的の向きを設定
			g_Player.rotDest = pCamera->rot.y + (D3DX_PI / 4 * 3.0f);
		}
		else
		{//↑キーのみ(上方向へ移動)
			g_Player.pos.x += sinf(pCamera->rot.y) * PLAYER_SPEED;	//プレイヤーの位置移動
			g_Player.pos.z += cosf(pCamera->rot.y) * PLAYER_SPEED;
			//プレイヤーの目的の向きを設定
			g_Player.rotDest = pCamera->rot.y + D3DX_PI;
		}
	}
	else if (GetKeyboardPress(DIK_DOWNARROW) == true)
	{//↓キーが押されたとき
		if (GetKeyboardPress(DIK_RIGHTARROW) == true)
		{//←キーと押されたとき(左斜め下方向)
			g_Player.pos.x += sinf(pCamera->rot.y + (D3DX_PI / 4 * 3.0f)) * PLAYER_SPEED;		//プレイヤーの位置移動
			g_Player.pos.z += cosf(pCamera->rot.y + (D3DX_PI / 4 * 3.0f)) * PLAYER_SPEED;
			//プレイヤーの目的の向きを設定
			g_Player.rotDest = pCamera->rot.y - (D3DX_PI / 4);
		}
		else if (GetKeyboardPress(DIK_LEFTARROW) == true)
		{//→キーと押されたとき(右斜め下方向)
			g_Player.pos.x += sinf(pCamera->rot.y - (D3DX_PI / 4 * 3.0f)) * PLAYER_SPEED;		//プレイヤーの位置移動
			g_Player.pos.z += cosf(pCamera->rot.y - (D3DX_PI / 4 * 3.0f)) * PLAYER_SPEED;
			//プレイヤーの目的の向きを設定
			g_Player.rotDest = pCamera->rot.y + (D3DX_PI / 4);
		}
		else
		{//↓キーのみ(下方向へ移動)
			g_Player.pos.x += sinf(pCamera->rot.y + D3DX_PI) * PLAYER_SPEED;		//プレイヤーの位置移動
			g_Player.pos.z += cosf(pCamera->rot.y + D3DX_PI) * PLAYER_SPEED;
			//プレイヤーの目的の向きを設定
			g_Player.rotDest = pCamera->rot.y;
		}
	}
	else if (GetKeyboardPress(DIK_RIGHTARROW) == true)
	{//→キーが押されたとき(右方向へ移動)
		g_Player.pos.x += sinf(pCamera->rot.y + (D3DX_PI / 2)) * PLAYER_SPEED;	//プレイヤーの位置移動
		g_Player.pos.z += cosf(pCamera->rot.y + (D3DX_PI / 2)) * PLAYER_SPEED;
		//プレイヤーの目的の向きを設定
		g_Player.rotDest = pCamera->rot.y - (D3DX_PI / 2);
	}
	else if (GetKeyboardPress(DIK_LEFTARROW) == true)
	{//←キーが押されたとき(左方向へ移動)
		g_Player.pos.x += sinf(pCamera->rot.y - (D3DX_PI / 2)) * PLAYER_SPEED;	//プレイヤーの位置移動
		g_Player.pos.z += cosf(pCamera->rot.y - (D3DX_PI / 2)) * PLAYER_SPEED;
		//プレイヤーの目的の向きを設定
		g_Player.rotDest = pCamera->rot.y + (D3DX_PI / 2);
	}

	//ジャンプ
	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{//エンターキーが押された
		g_Player.move.y += 5.0f;
	}

	//角度の正規化
	if (g_Player.rot.y > D3DX_PI)
	{
		g_Player.rot.y -= D3DX_PI * 2;
	}
	else if (g_Player.rot.y < -D3DX_PI)
	{
		g_Player.rot.y += D3DX_PI * 2;
	}

	//差分の計算
	g_Player.diff = (g_Player.rotDest - g_Player.rot.y);

	//差分の正規化
	if (g_Player.diff > D3DX_PI)
	{
		g_Player.diff -= D3DX_PI * 2;
	}
	else if (g_Player.diff < -D3DX_PI)
	{
		g_Player.diff += D3DX_PI * 2;
	}

	//プレイヤーの移動慣性
	g_Player.rot.y += g_Player.diff * 0.1f;
}

//---------------------------------------------------
//	プレイヤーの描画処理
//---------------------------------------------------
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL * pMat;			//マテリアルデータへのポインタ

									//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld,
		&g_Player.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
	{
		D3DXMATRIX mtxRotChild, mtxTransChild;	//計算用マトリックス

		D3DXMatrixIdentity(&g_Player.aModel[nCntParts].mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRotChild,
			g_Player.aModel[nCntParts].rot.y, g_Player.aModel[nCntParts].rot.x, g_Player.aModel[nCntParts].rot.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntParts].mtxWorld,
			&g_Player.aModel[nCntParts].mtxWorld, &mtxRotChild);

		//位置を反映
		D3DXMatrixTranslation(&mtxTransChild, g_Player.aModel[nCntParts].pos.x, g_Player.aModel[nCntParts].pos.y, g_Player.aModel[nCntParts].pos.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntParts].mtxWorld, &g_Player.aModel[nCntParts].mtxWorld, &mtxTransChild);

		D3DXMATRIX mtxParent;	//親のマトリクス代入用

		if (g_Player.aModel[nCntParts].nIdxModelParent == -1)
		{
			//プレイヤーのマトリクス代入
			mtxParent = g_Player.mtxWorld;
		}
		else
		{
			//自分の親モデルのマトリクス代入
			mtxParent = g_Player.aModel[g_Player.aModel[nCntParts].nIdxModelParent].mtxWorld;
		}

		//自分の親モデルマトリクスとの掛算（自分のマトリクス * 親のマトリクス = 自分のワールドマトリクス）
		D3DXMatrixMultiply(&g_Player.aModel[nCntParts].mtxWorld,
			&g_Player.aModel[nCntParts].mtxWorld,		//自分のマトリクス
			&mtxParent);								//親のマトリクス

														//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCntParts].mtxWorld);

		//現在のマテリアル保持
		pDevice->GetMaterial(&matDef);

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_Player.aModel[nCntParts].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntParts].nNumMat; nCntMat++)
		{
			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//Xファイルの描画
			g_Player.aModel[nCntParts].pMesh->DrawSubset(nCntMat);

			//テクスチャの設定
			pDevice->SetTexture(0, NULL);
		}

		//保持していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

//---------------------------------------------------
//	プレイヤーの情報
//---------------------------------------------------
Player * GetPlayer(void)
{//プレイヤーの情報を送る
	return &g_Player;
}


////=======================================
////初期化処理
////=======================================
//
//void InitModel2(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//	g_aModel2[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	g_aModel2[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	g_aModel2[0].rotDestModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	g_aModel2[0].vtxMaxModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//頂点の最大値取得
//	g_aModel2[0].vtxMinModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//頂点の最小値取得
//	g_aModel2[0].bUse = false;
//	g_aModel2[0].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//	//Xfile 読み込み
//	D3DXLoadMeshFromX("data//MODEL//3DGame_bus.x",
//		D3DXMESH_SYSTEMMEM,
//		pDevice,
//		NULL,
//		&g_pBuffMatModel2,
//		NULL,
//		&g_nNumMatModel2,
//		&g_pMeshModel2);
//
//	int nNumVtx;     //頂点数
//	DWORD sizeFVF;   //頂点フォーマットのサイズ
//	BYTE*pVtxBuff;   //頂点バッファへのポインタ
//					 //頂点数の取得
//	nNumVtx = g_pMeshModel2->GetNumVertices();
//
//	//頂点フォーマットのサイズを取得
//	sizeFVF = D3DXGetFVFVertexSize(g_pMeshModel2->GetFVF());
//
//	//頂点バッファのロック
//	g_pMeshModel2->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
//
//	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
//	{
//		for (int nCntModel = 0; nCntModel < MODEL_MAX; nCntModel++)
//		{
//			//頂点座標の代入
//			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
//
//			// 最小値計算
//			if (vtx.x < g_aModel2[nCntModel].vtxMinModel.x)
//			{// 比較した値が入ってる当たりよりも小さかったら置き換える
//				g_aModel2[nCntModel].vtxMinModel.x = (int)vtx.x;
//			}
//
//			if (vtx.z < g_aModel2[nCntModel].vtxMinModel.z)
//			{// 比較した値が入ってる当たりよりも小さかったら置き換える
//				g_aModel2[nCntModel].vtxMinModel.z = (int)vtx.z;
//			}
//
//			// 最大値を計算
//			if (vtx.x > g_aModel2[nCntModel].vtxMaxModel.x)
//			{// 比較した値が入ってる当たりよりも大きかったら置き換える
//				g_aModel2[nCntModel].vtxMaxModel.x = (int)vtx.x;
//			}
//
//			if (vtx.z > g_aModel2[nCntModel].vtxMaxModel.z)
//			{// 比較した値が入ってる当たりよりも大きかったら置き換える
//				g_aModel2[nCntModel].vtxMaxModel.z = (int)vtx.z;
//			}
//		}
//
//		//頂点フォーマットのポインタ分進める
//		pVtxBuff += sizeFVF;
//	}
//
//	//頂点バッファをアンロック
//	g_pMeshModel2->UnlockVertexBuffer();
//	SetModel2(D3DXVECTOR3(0.0f, 0.0f,250.0f), D3DXVECTOR3(0.0f, -D3DX_PI/2, 0.0f), MODEL_TYPE_BUS);
//	/*SetModel2(D3DXVECTOR3(0.0f, 0.0f, 230.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), MODEL_TYPE_BUS);*/
//}
////=======================================
////終了処理
////======================================= 
//void UninitModel2(void)
//{
//	//メッシュ破棄
//	if (g_pMeshModel2 != NULL)
//	{
//		g_pMeshModel2->Release();
//		g_pMeshModel2 = NULL;
//	}
//	//マテリアルの破棄
//	if (g_pBuffMatModel2 != NULL)
//	{
//		g_pBuffMatModel2->Release();
//		g_pBuffMatModel2 = NULL;
//	}
//}
////=======================================
////更新処理
////=======================================    
//void UpdateModel2(void)
//{	//位置を更新
//	g_aModel2[0].pos.x += g_aModel2[0].move.x;
//
//	g_aModel2[0].move.x = +2;
//	if (g_aModel2[0].pos.x == 700)
//	{
//		g_aModel2[0].pos.x = -470;
//	}
//
//}
////=======================================
////描画の処理
////=======================================       
//void DrawModel2(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスの取得
//	D3DXMATRIX mtxRot, mtxTrans, scale;     //計算用マトリックス
//
//	D3DMATERIAL9 matDef;                  //現在のマテリアル保存用
//	D3DXMATERIAL *pMat;                  //マテリアルデータへのポインタ
//	for (int nCnt = 0; nCnt < MODEL_MAX; nCnt++)
//	{
//		if (g_aModel2[nCnt].bUse == true)
//		{
//			//ワールドマトリックスの初期化
//			D3DXMatrixIdentity(&g_aModel2[nCnt].mtxWorld);
//
//			//モデルのサイズ
//			D3DXMatrixScaling(&scale,
//				scaleVector2.x,
//				scaleVector2.y,
//				scaleVector2.z);
//			D3DXMatrixMultiply(&g_aModel2[nCnt].mtxWorld, &g_aModel2[nCnt].mtxWorld, &scale);
//
//			//向きを反映
//			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aModel2[nCnt].rot.y, g_aModel2[nCnt].rot.x, g_aModel2[nCnt].rot.z);
//			D3DXMatrixMultiply(&g_aModel2[nCnt].mtxWorld, &g_aModel2[nCnt].mtxWorld, &mtxRot);
//
//			////位置を反映
//			D3DXMatrixTranslation(&mtxTrans, g_aModel2[nCnt].pos.x, g_aModel2[nCnt].pos.y, g_aModel2[nCnt].pos.z);
//			D3DXMatrixMultiply(&g_aModel2[nCnt].mtxWorld, &g_aModel2[nCnt].mtxWorld, &mtxTrans);
//
//			//ワールドマトリックスの設定
//			pDevice->SetTransform(D3DTS_WORLD, &g_aModel2[nCnt].mtxWorld);
//
//			//現在のマテリアルを保特
//			pDevice->GetMaterial(&matDef);
//
//			//マテリアルデータへのポインタを取得
//			pMat = (D3DXMATERIAL*)g_pBuffMatModel2->GetBufferPointer();
//
//			for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel2; nCntMat++)
//			{
//				//マテリアルの設定
//				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
//
//				//モデルパーツの描画
//				g_pMeshModel2->DrawSubset(nCntMat);
//			}
//			// 保特していたマテリアルを戻す
//			pDevice->SetMaterial(&matDef);
//		}
//	}
//
//}
//void SetModel2(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL_TYPE2 type)
//{
//
//	for (int nCntModel = 0; nCntModel < MODEL_MAX; nCntModel++)
//	{
//		//bUse がfalseの場合, pos,rotを代入しbUseをtrueにする
//		if (g_aModel2[nCntModel].bUse == false)
//		{
//			g_aModel2[nCntModel].pos = pos;
//			g_aModel2[nCntModel].rot = rot;
//			g_aModel2[nCntModel].bUse = true;
//
//			break;
//		}
//	}
//}
//
////-------------------------------------------
////モデルの当たり判定
////-------------------------------------------
//void CollisionModel2(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 size)
//{
//	for (int nCntModel = 0; nCntModel < MODEL_MAX; nCntModel++)
//	{
//		if (g_aModel2[nCntModel].bUse == true)
//		{
//			if (pos->z - (size.z / 2) < g_aModel2[nCntModel].pos.z + g_aModel2[nCntModel].vtxMaxModel.z*SIZE_Z &&
//				pos->z + (size.z / 2) > g_aModel2[nCntModel].pos.z + g_aModel2[nCntModel].vtxMinModel.z*SIZE_Z)
//			{ //左から(x)
//				if (posOld->x + (size.x / 2.f) <= g_aModel2[nCntModel].pos.x + g_aModel2[nCntModel].vtxMinModel.x*SIZE_X &&
//					pos->x + (size.x / 2.f) > g_aModel2[nCntModel].pos.x + g_aModel2[nCntModel].vtxMinModel.x*SIZE_X)
//				{
//
//					pos->x = g_aModel2[nCntModel].pos.x + g_aModel2[nCntModel].vtxMinModel.x*SIZE_X - (size.x / 2.f);
//				}
//				//右から(x)
//				else if (posOld->x - (size.x / 2) >= g_aModel2[nCntModel].pos.x + g_aModel2[nCntModel].vtxMaxModel.x*SIZE_X &&
//					pos->x - (size.x / 2) < g_aModel2[nCntModel].pos.x + g_aModel2[nCntModel].vtxMaxModel.x*SIZE_X)
//				{
//					pos->x = g_aModel2[nCntModel].pos.x + g_aModel2[nCntModel].vtxMaxModel.x*SIZE_X + (size.x / 2.f);
//				}
//			}
//			if (pos->x - (size.x / 2) < g_aModel2[nCntModel].pos.x + g_aModel2[nCntModel].vtxMaxModel.x*SIZE_X &&
//				pos->x + (size.x / 2) > g_aModel2[nCntModel].pos.x + g_aModel2[nCntModel].vtxMinModel.x*SIZE_X)
//			{ // ↑(z)
//
//				if (posOld->z + (size.z / 2) <= g_aModel2[nCntModel].pos.z + g_aModel2[nCntModel].vtxMinModel.z*SIZE_Z &&
//					pos->z + (size.z / 2) >  g_aModel2[nCntModel].pos.z + g_aModel2[nCntModel].vtxMinModel.z*SIZE_Z)
//				{
//					pos->z = g_aModel2[nCntModel].pos.z + g_aModel2[nCntModel].vtxMinModel.z*SIZE_Z - (size.z / 2);
//				}
//
//				// ↓(z)
//				else if (posOld->z - (size.z / 2) >= g_aModel2[nCntModel].pos.z + g_aModel2[nCntModel].vtxMaxModel.z*SIZE_Z &&
//					pos->z - (size.z / 2) <  g_aModel2[nCntModel].pos.z + g_aModel2[nCntModel].vtxMaxModel.z*SIZE_Z)
//				{
//					pos->z = g_aModel2[nCntModel].pos.z + g_aModel2[nCntModel].vtxMaxModel.z*SIZE_Z + (size.z / 2);
//				}
//			}
//		}
//	}
//}
//
//MODEL2*GetModel2(void)
//{
//	return g_aModel2;
//}