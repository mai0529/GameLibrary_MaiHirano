//-------------------------------------------
//
//障害物処理[obstacle.cpp]
//Author:平野舞
//
//-------------------------------------------

//インクルードファイル
#include "obstacle.h"
#include "score.h"
#include "time.h"
#include "player.h"

//グローバル宣言
LPDIRECT3DTEXTURE9 g_pTextureObstacle = NULL;			//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffObstacle = NULL;		//頂点バッファへのポインタ
Obstacle g_Obstacle[MAX_OBSTACLE];						//障害物の情報
	
//-------------------------------------------
//初期化処理
//-------------------------------------------
void InitObstacle(void)
{
	//初期化処理
	for (int nCount = 0; nCount < MAX_OBSTACLE; nCount++)
	{
		g_Obstacle[nCount].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
		g_Obstacle[nCount].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量
		g_Obstacle[nCount].bUse = false;							//使用しない
	}

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/obstacle.png",
		&g_pTextureObstacle);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_OBSTACLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffObstacle,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffObstacle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntObs = 0; nCntObs < MAX_OBSTACLE; nCntObs++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_Obstacle[nCntObs].pos.x - (OBSTACLE_WIDTH / 2.0f), g_Obstacle[nCntObs].pos.y - (OBSTACLE_HEIGHT / 2.0f), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Obstacle[nCntObs].pos.x + (OBSTACLE_WIDTH / 2.0f), g_Obstacle[nCntObs].pos.y - (OBSTACLE_HEIGHT / 2.0f), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Obstacle[nCntObs].pos.x - (OBSTACLE_WIDTH / 2.0f), g_Obstacle[nCntObs].pos.y + (OBSTACLE_HEIGHT / 2.0f), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Obstacle[nCntObs].pos.x + (OBSTACLE_WIDTH / 2.0f), g_Obstacle[nCntObs].pos.y + (OBSTACLE_HEIGHT / 2.0f), 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffObstacle->Unlock();
}

//-------------------------------------------
//終了処理
//-------------------------------------------
void UninitObstacle(void)
{
	//テクスチャの破棄
	if (g_pTextureObstacle != NULL)
	{
		g_pTextureObstacle->Release();
		g_pTextureObstacle = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffObstacle != NULL)
	{
		g_pVtxBuffObstacle->Release();
		g_pVtxBuffObstacle = NULL;
	}
}

//-------------------------------------------
//更新処理
//-------------------------------------------
void UpdateObstacle(void)
{
	//タイムを獲得
	int nGetTime = GetTime();

	//障害物を設置
	if (nGetTime == 55 || nGetTime == 45)
	{
		//現在時刻をシード(種)にする
		srand((unsigned int)time(NULL));

		int nPosY = rand() % 500 + 50;		//乱数で50～650を指定
		SetObstacle(D3DXVECTOR3(1300.0f, nPosY, 0.0f));
	}

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffObstacle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntObs = 0; nCntObs < MAX_OBSTACLE; nCntObs++)
	{
		if (g_Obstacle[nCntObs].bUse)
		{
			//位置情報の更新
			g_Obstacle[nCntObs].move.x = 3.0f;
			g_Obstacle[nCntObs].pos.x -= g_Obstacle[nCntObs].move.x;

			//頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(g_Obstacle[nCntObs].pos.x - (OBSTACLE_WIDTH / 2.0f), g_Obstacle[nCntObs].pos.y - (OBSTACLE_HEIGHT / 2.0f), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Obstacle[nCntObs].pos.x + (OBSTACLE_WIDTH / 2.0f), g_Obstacle[nCntObs].pos.y - (OBSTACLE_HEIGHT / 2.0f), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Obstacle[nCntObs].pos.x - (OBSTACLE_WIDTH / 2.0f), g_Obstacle[nCntObs].pos.y + (OBSTACLE_HEIGHT / 2.0f), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Obstacle[nCntObs].pos.x + (OBSTACLE_WIDTH / 2.0f), g_Obstacle[nCntObs].pos.y + (OBSTACLE_HEIGHT / 2.0f), 0.0f);

			if (g_Obstacle[nCntObs].pos.x < 0)
			{//画面外に出たら
				g_Obstacle[nCntObs].bUse = false;
			}
		}
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffObstacle->Unlock();
}

//-------------------------------------------
//描画処理
//-------------------------------------------
void DrawObstacle(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffObstacle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntObs = 0; nCntObs < MAX_OBSTACLE; nCntObs++)
	{
		if (g_Obstacle[nCntObs].bUse)
		{//敵が使用されている場合
		 //テクスチャ設定
			pDevice->SetTexture(0, g_pTextureObstacle);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntObs * 4, 2);
		}
	}
}

//-------------------------------------------
//設定処理
//-------------------------------------------
void SetObstacle(D3DXVECTOR3 pos)
{
	for (int nCntObs = 0; nCntObs < MAX_OBSTACLE; nCntObs++)
	{
		if (!g_Obstacle[nCntObs].bUse)
		{//障害物が使用されていない場合
			g_Obstacle[nCntObs].pos = pos;		//位置
			g_Obstacle[nCntObs].bUse;			//使用する

			break;
		}
	}
}

//-------------------------------------------
//情報の取得処理
//-------------------------------------------
Obstacle * GetObstacle(void)
{
	return &g_Obstacle[0];
}

//-------------------------------------------
//当たり判定処理
//-------------------------------------------
void CollisionObstacle(D3DXVECTOR3 * pPos, float fWidth, float fHeigtht)
{
	for (int nCntObs = 0; nCntObs < MAX_OBSTACLE; nCntObs++)
	{
		if (g_Obstacle[nCntObs].bUse)
		{//障害物を使っているとき
			if (pPos->x - (fWidth / 2.0f) >= g_Obstacle[nCntObs].pos.x - (OBSTACLE_WIDTH / 2.0f)
				&& pPos->x + (fWidth / 2.0f) <= g_Obstacle[nCntObs].pos.x + (OBSTACLE_WIDTH / 2.0f)
				&& pPos->y + (fHeigtht / 2.0f) >= g_Obstacle[nCntObs].pos.y - (OBSTACLE_HEIGHT / 2.0f)
				&& pPos->y - (fHeigtht / 2.0f) <= g_Obstacle[nCntObs].pos.y + (OBSTACLE_HEIGHT / 2.0f))
			{
				HitPlayer(1);		//ヒット処理
			}
		}
	}
}