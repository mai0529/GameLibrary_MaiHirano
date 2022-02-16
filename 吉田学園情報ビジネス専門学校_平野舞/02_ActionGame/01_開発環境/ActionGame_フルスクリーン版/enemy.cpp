//-------------------------------------------
//
//敵の処理[enemy.cpp]
//Author:平野舞
//
//-------------------------------------------

//インクルードファイル
#include "enemy.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureEnemy[NUM_ENEMY] = {};	//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;			//頂点バッファへのポインタ
Enemy g_aEnemy[MAX_ENEMY];								//敵の情報
int g_nNumEnemy = 0;									//敵の総数

//-------------------------------------------
//敵の初期化処理
//-------------------------------------------
void InitEnemy(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	int nCntEnemy;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/enemy000.png",
		&g_apTextureEnemy[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/enemy001.png",
		&g_apTextureEnemy[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/enemy002.png",
		&g_apTextureEnemy[2]);

	//敵の情報の初期化
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置の初期化
		g_aEnemy[nCntEnemy].PosOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//前位置情報の初期化
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量の初期化
		g_aEnemy[nCntEnemy].nNumber = 0;								//何番目か
		g_aEnemy[nCntEnemy].nType = ENEMY_GHOST;						//種類の初期化
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
		g_aEnemy[nCntEnemy].nCounterState = 60;
		g_aEnemy[nCntEnemy].nCounterAnim = 0;
		g_aEnemy[nCntEnemy].nPatternAnim = 0;
		g_aEnemy[nCntEnemy].nLife = 0;									//寿命の初期化
		g_aEnemy[nCntEnemy].bUse = false;								//使用の初期化
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

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - (ENEMY_WIDTH / 2), g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (ENEMY_WIDTH / 2), g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - (ENEMY_WIDTH / 2), g_aEnemy[nCntEnemy].pos.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (ENEMY_WIDTH / 2), g_aEnemy[nCntEnemy].pos.y, 0.0f);

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

	//おばけ
	SetEnemy(D3DXVECTOR3(1280.0f, 420.0f, 0.0f), D3DXVECTOR3(-0.9f, 0.0f, 0.0f), ENEMY_GHOST, 1, 0);
	SetEnemy(D3DXVECTOR3(2670.0f, 400.0f, 0.0f), D3DXVECTOR3(-1.3f, 0.0f, 0.0f), ENEMY_GHOST, 1, 0);
	SetEnemy(D3DXVECTOR3(4090.0f, 620.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMY_GHOST, 1, 1);
	SetEnemy(D3DXVECTOR3(5690.0f, 300.0f, 0.0f), D3DXVECTOR3(-0.6f, 0.0f, 0.0f), ENEMY_GHOST, 1, 0);
	SetEnemy(D3DXVECTOR3(6990.0f, 300.0f, 0.0f), D3DXVECTOR3(-0.4f, 0.0f, 0.0f), ENEMY_GHOST, 1, 0);
	SetEnemy(D3DXVECTOR3(8300.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMY_GHOST, 1, 1);

	//骸骨
	SetEnemy(D3DXVECTOR3(700.0f, 650.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), ENEMY_BONE, 11, 0);
	SetEnemy(D3DXVECTOR3(1800.0f, 650.0f, 0.0f), D3DXVECTOR3(-1.2f, 0.0f, 0.0f), ENEMY_BONE, 11, 0);
	SetEnemy(D3DXVECTOR3(2200.0f, 650.0f, 0.0f), D3DXVECTOR3(-0.8f, 0.0f, 0.0f), ENEMY_BONE, 11, 0);
	SetEnemy(D3DXVECTOR3(3200.0f, 650.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f), ENEMY_BONE, 11, 0);
	SetEnemy(D3DXVECTOR3(8200.0f, 650.0f, 0.0f), D3DXVECTOR3(-0.3f, 0.0f, 0.0f), ENEMY_BONE, 11, 0);

	//狼
	SetEnemy(D3DXVECTOR3(1380.0f, 650.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), ENEMY_WOLF, 2, 0);
	SetEnemy(D3DXVECTOR3(2700.0f, 650.0f, 0.0f), D3DXVECTOR3(-1.7f, 0.0f, 0.0f), ENEMY_WOLF, 2, 0);
	SetEnemy(D3DXVECTOR3(3800.0f, 650.0f, 0.0f), D3DXVECTOR3(-1.3f, 0.0f, 0.0f), ENEMY_WOLF, 2, 0);
	SetEnemy(D3DXVECTOR3(4200.0f, 650.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f), ENEMY_WOLF, 2, 0);
	SetEnemy(D3DXVECTOR3(4200.0f, 650.0f, 0.0f), D3DXVECTOR3(-0.3f, 0.0f, 0.0f), ENEMY_WOLF, 2, 0);
	SetEnemy(D3DXVECTOR3(4500.0f, 650.0f, 0.0f), D3DXVECTOR3(-0.2f, 0.0f, 0.0f), ENEMY_WOLF, 2, 0);

	for (int nCount = 0; nCount < 10; nCount++)
	{
		SetEnemy(D3DXVECTOR3(6400.0f + (-100.0f * nCount), 650.0f, 0.0f), D3DXVECTOR3(-0.2f, 0.0f, 0.0f), ENEMY_WOLF, 2, 0);
	}

	for (int nCount = 0; nCount < 10; nCount++)
	{
		SetEnemy(D3DXVECTOR3(7200.0f + (-100.0f * nCount), 650.0f, 0.0f), D3DXVECTOR3(-0.2f, 0.0f, 0.0f), ENEMY_WOLF, 2, 0);
	}
}

//-------------------------------------------
//敵の終了処理
//-------------------------------------------
void UninitEnemy(void)
{
	int nCntEnemy;

	//テクスチャの破棄
	for (nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
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
	int nCntEnemy;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//敵が使用されている
			//前回の位置を更新
			g_aEnemy[nCntEnemy].PosOld = g_aEnemy[nCntEnemy].pos;

			//カウンターを増やす
			g_aEnemy[nCntEnemy].nCounterAnim++;

			if (g_aEnemy[nCntEnemy].nCounterAnim % 10 == 0)
			{
				g_aEnemy[nCntEnemy].nPatternAnim++;
			}
			if (g_aEnemy[nCntEnemy].nPatternAnim == 4)
			{
				g_aEnemy[nCntEnemy].nPatternAnim = 0;
			}

			if (g_aEnemy[nCntEnemy].nType == ENEMY_GHOST)
			{//おばけ
				//テクスチャの更新
				pVtx[0].tex = D3DXVECTOR2((1.0f / 4) * g_aEnemy[nCntEnemy].nPatternAnim, 0.0f);
				pVtx[1].tex = D3DXVECTOR2((1.0f / 4) * (g_aEnemy[nCntEnemy].nPatternAnim + 1), 0.0f);
				pVtx[2].tex = D3DXVECTOR2((1.0f / 4) * g_aEnemy[nCntEnemy].nPatternAnim, (1.0f / 2));
				pVtx[3].tex = D3DXVECTOR2((1.0f / 4) * (g_aEnemy[nCntEnemy].nPatternAnim + 1), (1.0f / 2));
			}
			else
			{//他のキャラ
				pVtx[0].tex = D3DXVECTOR2((1.0f / 3) * g_aEnemy[nCntEnemy].nPatternAnim, 0.0f);
				pVtx[1].tex = D3DXVECTOR2((1.0f / 3) * (g_aEnemy[nCntEnemy].nPatternAnim + 1), 0.0f);
				pVtx[2].tex = D3DXVECTOR2((1.0f / 3) * g_aEnemy[nCntEnemy].nPatternAnim, (1.0f / 2));
				pVtx[3].tex = D3DXVECTOR2((1.0f / 3) * (g_aEnemy[nCntEnemy].nPatternAnim + 1), (1.0f / 2));
			}

			//位置を更新
			g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].move.x;
			g_aEnemy[nCntEnemy].pos.y += g_aEnemy[nCntEnemy].move.y;

			if (g_aEnemy[nCntEnemy].nType == ENEMY_BONE || g_aEnemy[nCntEnemy].nType == ENEMY_WOLF)
			{//重力
				g_aEnemy[nCntEnemy].move.y += ENEMY_G;
				//ブロックとの当たり判定
				CollisionBlock(&g_aEnemy[nCntEnemy].pos, &g_aEnemy[nCntEnemy].PosOld, &g_aEnemy[nCntEnemy].move, (ENEMY_WIDTH / 2), ENEMY_HEIGHT);
			}

			if (g_aEnemy[nCntEnemy].nType == ENEMY_GHOST)
			{
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
			}
			if (g_aEnemy[nCntEnemy].nNumber == 1)
			{
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(0.8f, 0.6f, 0.6f, 0.7f);
				pVtx[1].col = D3DXCOLOR(0.8f, 0.6f, 0.6f, 0.7f);
				pVtx[2].col = D3DXCOLOR(0.8f, 0.6f, 0.6f, 0.7f);
				pVtx[3].col = D3DXCOLOR(0.8f, 0.6f, 0.6f, 0.7f);
			}

			//状態管理
			//StateEnemy(nCntEnemy);

			//敵の位置情報の更新
			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL:
				break;
			case ENEMYSTATE_DAMAGE:
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

				if (g_aEnemy[nCntEnemy].pos.x < 0 || g_aEnemy[nCntEnemy].pos.y < SCREEN_HEIGHT)
				{
					g_aEnemy[nCntEnemy].bUse = false;		//使用していない状態にする
				}

			}

			//頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - (ENEMY_WIDTH / 2), g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (ENEMY_WIDTH / 2), g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - (ENEMY_WIDTH / 2), g_aEnemy[nCntEnemy].pos.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (ENEMY_WIDTH / 2), g_aEnemy[nCntEnemy].pos.y, 0.0f);
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
	int nCntEnemy;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
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
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, ENEMY nType,int nLife,int nNumber)
{	
	int nCntEnemy;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{//敵が使用されていない場合
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].move = move;
			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].nLife = nLife;
			g_aEnemy[nCntEnemy].nNumber = nNumber;
			g_aEnemy[nCntEnemy].bUse = true;

			break;
		}
		pVtx += 4;		//頂点データを４つ分進める
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

	pVtx += 4 * nCntEnemy;

	if (g_aEnemy[nCntEnemy].bUse == true)
	{
		g_aEnemy[nCntEnemy].nLife -= nDamage;
		if (g_aEnemy[nCntEnemy].nLife == 0)
		{
			g_aEnemy[nCntEnemy].bUse = false;
			//演出
			PlaySound(SOUND_LABEL_SE_HIT);
			SetExplosion(D3DXVECTOR3 (g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y - (ENEMY_HEIGHT / 2),0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f));
			g_nNumEnemy--;
		}
		else
		{
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
			g_aEnemy[nCntEnemy].nCounterState = 10;
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
//敵の取得
//-------------------------------------------
Enemy * GetEnemy(void)
{
	return &g_aEnemy[0];
}

//-------------------------------------------
//敵の当たり判定
//-------------------------------------------
void CollisionEnemy(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove,float fWidth, float fHeigtht)
{
	Player *pPlayer = GetPlayer();

	int nCntEnemy;

	if (pPlayer->bDisp == true && pPlayer->state == PLAYERSTATE_NORMAL)
	{
		for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
		{
			if (g_aEnemy[nCntEnemy].bUse == true)
			{
				if (g_aEnemy[nCntEnemy].nType == ENEMY_BONE)
				{//骸骨
					if (pPos->x + (fWidth / 2) >= g_aEnemy[nCntEnemy].pos.x - (ENEMY_WIDTH / 2)
						&& pPos->x - (fWidth / 2) <= g_aEnemy[nCntEnemy].pos.x + (ENEMY_WIDTH / 2))
					{
						if (pPosOld->y <= g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT
							&& pPos->y >= g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT)
						{//敵の頭に当たったら
							pMove->y -= 20.0f;
							HitEnemy(nCntEnemy, g_aEnemy[nCntEnemy].nLife);
							AddScore(400);
						}
						else if (pPosOld->y - fHeigtht >= g_aEnemy[nCntEnemy].pos.y
							&& pPos->y - fHeigtht <= g_aEnemy[nCntEnemy].pos.y)
						{//下に当たったら
							HitPlayer(1);
						}
					}
					if (pPos->y - fHeigtht <= g_aEnemy[nCntEnemy].pos.y
						&&pPos->y > g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT)
					{
						if (pPosOld->x - (fWidth / 2) >= g_aEnemy[nCntEnemy].pos.x + (ENEMY_WIDTH / 2) - g_aEnemy[nCntEnemy].move.x
							&& pPos->x - (fWidth / 2) <= g_aEnemy[nCntEnemy].pos.x + (ENEMY_WIDTH / 2) - g_aEnemy[nCntEnemy].move.x)
						{//左に当たったら
							HitPlayer(1);
						}
						else if (pPosOld->x + (fWidth / 2) <= g_aEnemy[nCntEnemy].pos.x - (ENEMY_WIDTH / 2) - g_aEnemy[nCntEnemy].move.x
							&& pPos->x + (fWidth / 2) >= g_aEnemy[nCntEnemy].pos.x - (ENEMY_WIDTH / 2) - g_aEnemy[nCntEnemy].move.x)
						{//右に当たったら
							HitPlayer(1);
						}
					}
				}
				else if ((pPos->x + (fWidth / 2) >= g_aEnemy[nCntEnemy].pos.x - (ENEMY_WIDTH / 2)
					&& pPos->x - (fWidth / 2) <= g_aEnemy[nCntEnemy].pos.x + (ENEMY_WIDTH / 2)
					&& pPos->y >= g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT
					&& pPos->y - fHeigtht <= g_aEnemy[nCntEnemy].pos.y))
				{//その他
					if (g_aEnemy[nCntEnemy].nType == ENEMY_GHOST)
					{//おばけ
						HitPlayer(pPlayer->nLife);
					}
					else if (g_aEnemy[nCntEnemy].nType == ENEMY_WOLF)
					{//狼
						HitPlayer(1);
					}
				}
			}
		}
	}
}

//-------------------------------------------
//敵の移動処理
//-------------------------------------------
void MoveEnemy(int nCntEnemy)
{
	BLOCK *pBlock = GetBlock();
	if (g_aEnemy[nCntEnemy].pos.x < pBlock->pos.x)
	{

	}
}

//-------------------------------------------
//敵の状態管理処理
//-------------------------------------------
//void StateEnemy(int nCntEnemy)
//{
//	//頂点情報へのポインタ
//	VERTEX_2D *pVtx;
//
//	//頂点バッファをロックし、頂点情報へのポインタを取得
//	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
//
//	//敵の位置情報の更新
//	switch (g_aEnemy[nCntEnemy].state)
//	{
//	case ENEMYSTATE_NORMAL:
//		break;
//	case ENEMYSTATE_DAMAGE:
//		g_aEnemy[nCntEnemy].nCounterState--;
//		if (g_aEnemy[nCntEnemy].nCounterState <= 0)
//		{
//			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
//			//頂点カラーの設定
//			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		}
//		break;
//	}
//
//		//頂点バッファをアンロックする
//	g_pVtxBuffEnemy->Unlock();
//}