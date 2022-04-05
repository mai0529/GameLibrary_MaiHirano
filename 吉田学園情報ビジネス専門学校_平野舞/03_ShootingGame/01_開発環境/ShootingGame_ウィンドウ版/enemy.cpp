//-------------------------------------------
//
//敵の処理[enemy.cpp]
//Author:平野舞
//
//-------------------------------------------

//インクルードファイル
#include "sound.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"
#include "fade.h"
#include "Sweet.h"
#include "player.h"
#include "Bullet.h"

//マクロ定義
#define NUM_ENEMY			(4)			//敵の種類の最大数

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureEnemy[NUM_ENEMY] = {};	//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;			//頂点バッファへのポインタ
Enemy g_aEnemy[MAX_ENEMY];								//敵の情報

//外部ファイル用のグローバル宣言
EnemyFile g_enemyFile[MAX_ENEMY][128];					//外部ファイル用の敵情報
char g_EnemyTex[4][128];								//テクスチャ読み込み用
int g_nCntEnemy;										//カウンタ

//-------------------------------------------
//敵の初期化処理
//-------------------------------------------
void InitEnemy(void)
{
	//外部ファイルの読み込み
	LoadEnemy();

	//敵の情報の初期化
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置の初期化
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量の初期化
		g_aEnemy[nCntEnemy].nType = 0;									//種類の初期化
		g_aEnemy[nCntEnemy].bUse = false;								//使用の初期化
		g_aEnemy[nCntEnemy].nLife = 2;									//寿命の初期化
	}

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	for (int nCntTex = 0; nCntTex < NUM_ENEMY; nCntTex++)
	{//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			&g_EnemyTex[nCntTex][0],
			&g_apTextureEnemy[nCntTex]);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT, g_aEnemy[nCntEnemy].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT, g_aEnemy[nCntEnemy].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y + ENEMY_HEIGHT, g_aEnemy[nCntEnemy].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y + ENEMY_HEIGHT, g_aEnemy[nCntEnemy].pos.z);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;		//頂点データを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();

	//現在時刻をシード(種)にする
	srand((unsigned int)time(NULL));

	//ランダム用の変数を宣言
	int nAddPosX;
	int nSubPosX;
	int nAddPosY;
	int nSubPosY;

	//ランダム配置用の変数を宣言
	int nPosX;
	int nPosY;

	for (int nCount = 0; nCount < g_nCntEnemy; nCount++)
	{
		nAddPosX = rand() % 150 + 150;		//150～300をランダムで指定
		nAddPosY = rand() % 80 + 20;		//20～100をランダムで指定

		nSubPosX = rand() % 150 - 200;		//-200～0をランダムで指定
		nSubPosY = rand() % 80 - 100;		//-100～0をランダムで指定

		nPosX = nAddPosX + nSubPosX;		//x座標のランダム
		nPosY = nAddPosY + nSubPosY;		//y座標のランダム

		//敵を設置
		SetEnemy(D3DXVECTOR3(g_enemyFile[nCount][0].pos.x + nPosX, g_enemyFile[nCount][0].pos.y + nPosY, g_enemyFile[nCount][0].pos.z),
			g_enemyFile[nCount][0].nType);
	}
}

//-------------------------------------------
//敵の終了処理
//-------------------------------------------
void UninitEnemy(void)
{
	//テクスチャの破棄
	for (int nCntEnemy = 0; nCntEnemy < 4; nCntEnemy++)
	{
		if (g_apTextureEnemy[nCntEnemy] != NULL)
		{
			g_apTextureEnemy[nCntEnemy]->Release();
			g_apTextureEnemy[nCntEnemy] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//-------------------------------------------
//敵の更新処理
//-------------------------------------------
void UpdateEnemy(void)
{
	//プレイヤー情報の取得
	Player *pPlayer = GetPlayer();

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//敵が使用されている
			//敵の状態管理
			StateEnemy(nCntEnemy);

			//敵の位置情報の更新
			g_aEnemy[nCntEnemy].move.x = 3.0f;

			//移動量を位置に減算
			g_aEnemy[nCntEnemy].pos.x -= g_aEnemy[nCntEnemy].move.x;

			//弾の処理
			//float fDistance =g_aEnemy[nCntEnemy].pos.x - pPlayer->pos.x ;
			//
			//if (fDistance >= 100.0f)
			//{
			//	SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(-10.0f, 0.0f, 0.0f), 50.0f, BULLETTYPE_ENEMY);
			//}

			//お菓子の当たり判定
			CollisionSweet(&g_aEnemy[nCntEnemy].pos, ENEMY_WIDTH, ENEMY_HEIGHT);

			//頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT, g_aEnemy[nCntEnemy].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT, g_aEnemy[nCntEnemy].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y + ENEMY_HEIGHT, g_aEnemy[nCntEnemy].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y + ENEMY_HEIGHT, g_aEnemy[nCntEnemy].pos.z);

			if (g_aEnemy[nCntEnemy].pos.y < 0)
			{//画面外に出たら
				g_aEnemy[nCntEnemy].bUse = false;		//使用していない状態にする
			}

		}
		pVtx += 4;		//頂点データを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//-------------------------------------------
//敵の描画処理
//-------------------------------------------
void DrawEnemy(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//敵が使用されている場合
		 //テクスチャ設定
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}
}

//-------------------------------------------
//敵の設定処理
//-------------------------------------------
void SetEnemy(D3DXVECTOR3 pos, int nType)
{	
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{//敵が使用されていない場合
			g_aEnemy[nCntEnemy].pos = pos;		//位置
			g_aEnemy[nCntEnemy].nType = nType;	//種類
			g_aEnemy[nCntEnemy].bUse = true;	//使用する
		
			break;
		}
	}
}

//-------------------------------------------
//敵の状態管理処理
//-------------------------------------------
void StateEnemy(int nCntEnemy)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//pVtxのデータ情報
	pVtx += 4 * nCntEnemy;

	switch (g_aEnemy[nCntEnemy].state)
	{
	case ENEMYSTATE_NORMAL:		//通常状態
		break;
	case ENEMYSTATE_DAMAGE:		//ダメージ状態
		g_aEnemy[nCntEnemy].nCounterState--;
		if (g_aEnemy[nCntEnemy].nCounterState <= 0)
		{
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		break;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//-------------------------------------------
//敵のヒット処理
//-------------------------------------------
void HitEnemy(int nCntEnemy, int nDamage)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//pVtxのデータ情報
	pVtx += 4 * nCntEnemy;

	if (g_aEnemy[nCntEnemy].bUse == true)
	{
		g_aEnemy[nCntEnemy].nLife -= nDamage;		//ライフを1つ減らす

		if (g_aEnemy[nCntEnemy].nLife == 0)
		{//ライフが0になったら
			SetExplosion(g_aEnemy[nCntEnemy].pos, 255);		//爆発の処理	
			g_aEnemy[nCntEnemy].bUse = false;				//使用しない
		}
		else
		{
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;		//ダメージ状態にする
			g_aEnemy[nCntEnemy].nCounterState = 5;
			//頂点カラーの変更
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//-------------------------------------------
//外部ファイルの読み込み処理
//-------------------------------------------
void LoadEnemy(void)
{
	char cData[128];
	int nCntTex = 0;		//テクスチャのカウンタ
	g_nCntEnemy = 0;		//敵のカウンタ

	FILE * pFile;

	pFile = fopen("data/enemy.txt", "r");		//ファイルを開く

	if (pFile != NULL)
	{//ファイルが開けた場合
		while (1)
		{
			fscanf(pFile, "%s", &cData[0]);

			if (strcmp(&cData[0], "ENEMY_TEXNAME") == 0)
			{//テクスチャ名を読み込む
				fscanf(pFile, "%s", &cData[0]);
				fscanf(pFile, "%s", &g_EnemyTex[nCntTex][0]);
				nCntTex++;		//カウンタを増やす
			}
			else if (strcmp(&cData[0], "PLACESET") == 0)
			{//出現場所の読み込み
				do
				{
					fscanf(pFile, "%s", &cData[0]);

					if (strcmp(&cData[0], "POS") == 0)
					{//場所を読み込む
						fscanf(pFile, "%s", &cData[0]);
						fscanf(pFile, "%f", &g_enemyFile[g_nCntEnemy][0].pos.x);
						fscanf(pFile, "%f", &g_enemyFile[g_nCntEnemy][0].pos.y);
						fscanf(pFile, "%f", &g_enemyFile[g_nCntEnemy][0].pos.z);
					}
					else if (strcmp(&cData[0], "TYPE") == 0)
					{//種類を読み込む
						fscanf(pFile, "%s", &cData[0]);
						fscanf(pFile, "%d", &g_enemyFile[g_nCntEnemy][0].nType);
					}
				} while (strcmp(&cData[0], "END_PLACESSET") != 0);
				g_nCntEnemy++;
			}

			if (strcmp(&cData[0], "END_ENEMYSET") == 0)
			{
				break;
			}
		}
		fclose(pFile);			//ファイルを閉じる
	}
	else
	{//ファイルが開けなかった場合
		printf("ファイルが開けませんでした");
	}
}

//-------------------------------------------
//敵の取得
//-------------------------------------------
Enemy * GetEnemy(void)
{
	return &g_aEnemy[0];
}

