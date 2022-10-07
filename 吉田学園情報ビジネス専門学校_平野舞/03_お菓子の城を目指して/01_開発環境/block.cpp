//-------------------------------------------
//
//ブロックの処理[block.cpp]
//Author:平野舞
//
//-------------------------------------------

//インクルードファイル
#include "block.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureBlock[BLOCK_NUM] = {};	//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;			//頂点バッファへのポインタ
BLOCK g_aBlock[MAX_BLOCK];								//ブロックの情報

//テキストファイル用のグローバル変数
BlockFile g_aBlockFile[MAX_BLOCK][256];					//テキストファイル読み込み用
char g_cBlockTexName[3][256];							//テクスチャ名
char g_cBlock[256];										//読み込み用
int g_nCntFile;											//カウンター

//-------------------------------------------
//ブロックの初期化処理
//-------------------------------------------
void InitBlock(void)
{
	g_nCntFile = 0;

	//外部ファイルの読み込み
	LoadBlock();

	//カウント用
	int nCntBlock;
	
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	for (int nCount = 0; nCount < 3; nCount++)
	{//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			&g_cBlockTexName[nCount][0],
			&g_apTextureBlock[nCount]);
	}

	//ブロックの情報の初期化
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置の初期化
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量の初期化
		g_aBlock[nCntBlock].nType = BLOCK_BRICK;						//種類の初期化
		g_aBlock[nCntBlock].nItem = 0;									//何のアイテムか
		g_aBlock[nCntBlock].nLife = 1;									//寿命の初期化
		g_aBlock[nCntBlock].fWidth = 0;									//幅の初期化
		g_aBlock[nCntBlock].fHeigth = 0;								//高さの初期化
		g_aBlock[nCntBlock].nCounterState = 60;							//状態管理の初期化
		g_aBlock[nCntBlock].bUse = false;								//使用の初期化
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + BLOCK_WIDTH, g_aBlock[nCntBlock].pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + BLOCK_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + BLOCK_WIDTH , g_aBlock[nCntBlock].pos.y + BLOCK_HEIGHT, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;		//頂点データを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();

	//ブロックの設置
	for (nCntBlock = 0; nCntBlock < g_nCntFile; nCntBlock++)
	{
		SetBlock(g_aBlockFile[nCntBlock][0].pos, g_aBlockFile[nCntBlock][0].fWidth, g_aBlockFile[nCntBlock][0].fHeigth, g_aBlockFile[nCntBlock][0].nType, g_aBlockFile[nCntBlock][0].nItem);
		g_aBlock[nCntBlock].nType = g_aBlockFile[nCntBlock][0].nType;
	}
																									
	//コンクリブロック
	for (int nCount = 0; nCount < 4; nCount++)
	{
		SetBlock(D3DXVECTOR3(5160.0f + (320 * nCount), 430.0f, 0.0f), BLOCK_WIDTH * 3, BLOCK_HEIGHT, BLOCK_CONCRETE,ITEM_CANDY);
		SetBlock(D3DXVECTOR3(5000.0f + (320 * nCount), 510.0f, 0.0f), BLOCK_WIDTH * 3, BLOCK_HEIGHT, BLOCK_CONCRETE,ITEM_CANDY);
	}
	for (int nCount = 0; nCount < 3; nCount++)
	{
		SetBlock(D3DXVECTOR3(6830.0f + (BLOCK_WIDTH * nCount), 100.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION,ITEM_CANDY);
	}

	//ゴール手前
	for (int nCount = 0; nCount < 7; nCount++)
	{//階段
		SetBlock(D3DXVECTOR3(8200.0f + (40 * nCount), 650.0f - (40 * nCount), 0.0f), BLOCK_WIDTH,BLOCK_HEIGHT * nCount, BLOCK_CONCRETE,ITEM_CANDY);
	}
	for (int nCount = 0; nCount < 7; nCount++)
	{//階段
		SetBlock(D3DXVECTOR3(8700.0f - (40 * nCount), 650.0f - (40 * nCount), 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT * nCount, BLOCK_CONCRETE,ITEM_CANDY);
	}
}

//-------------------------------------------
//ブロックの終了処理
//-------------------------------------------
void UninitBlock(void)
{
	int nCntBlock;

	for (nCntBlock = 0; nCntBlock < BLOCK_NUM; nCntBlock++)
	{
		//テクスチャの破棄
		if (g_apTextureBlock[nCntBlock] != NULL)
		{
			g_apTextureBlock[nCntBlock]->Release();
			g_apTextureBlock[nCntBlock] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}

//-------------------------------------------
//ブロックの更新処理
//-------------------------------------------
void UpdateBlock(void)
{
	int nCntBlock;
	float nWnumber;
	float nHnumber;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{//ブロックが使用されている場合
			//StateBlock(nCntBlock);

			//ブロックの位置情報の更新
			switch (g_aBlock[nCntBlock].state)
			{
			case BLOCKSTATE_NORMAL:
				break;
			case BLOCKSTATE_DAMAGE:
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);

				g_aBlock[nCntBlock].nCounterState--;
				if (g_aBlock[nCntBlock].nCounterState >= 0)
				{
					g_aBlock[nCntBlock].pos.y = g_aBlock[nCntBlock].pos.y - 1.0f;
				}
				else
				{//元の位置に戻す
					g_aBlock[nCntBlock].pos.y = g_aBlock[nCntBlock].pos.y + 10.0f;
					g_aBlock[nCntBlock].state = BLOCKSTATE_NORMAL;
				}
				break;
			}

			//位置を更新
			g_aBlock[nCntBlock].pos.x += g_aBlock[nCntBlock].move.x;
			g_aBlock[nCntBlock].pos.y += g_aBlock[nCntBlock].move.y;
			
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeigth, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeigth, 0.0f);
		
			//基準からの倍数
			nWnumber = g_aBlock[nCntBlock].fWidth / BLOCK_WIDTH;
			nHnumber = g_aBlock[nCntBlock].fHeigth / BLOCK_HEIGHT;

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f * nWnumber, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f * nHnumber);
			pVtx[3].tex = D3DXVECTOR2(1.0f * nWnumber, 1.0f * nHnumber);
		}
		pVtx += 4;		//頂点データを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();
}

//-------------------------------------------
//ブロックの描画処理
//-------------------------------------------
void DrawBlock(void)
{
	int nCntBlock;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{//ブロックが使用されている場合
			//テクスチャ設定
			pDevice->SetTexture(0, g_apTextureBlock[g_aBlock[nCntBlock].nType]);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBlock * 4, 2);
		}
	}
}

//-------------------------------------------
//ブロックの設定処理
//-------------------------------------------
void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeigtht, int nType,int nItem)
{	
	int nCntBlock;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{//ブロックが使用されていない場合
			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].fWidth = fWidth;
			g_aBlock[nCntBlock].fHeigth = fHeigtht;
			g_aBlock[nCntBlock].nItem = nItem;
			g_aBlock[nCntBlock].bUse = true;	

			break;
		}
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();
}

//-------------------------------------------
//ブロックの当たり判定
//-------------------------------------------
bool CollisionBlock(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove, float fWidth, float fHeigtht)
{
	int nCntBlock;

	bool bIsLanding = false;		//着地しているかどうか

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{//ブロックを使っているとき
			if (pPos->x + (fWidth / 2) >= g_aBlock[nCntBlock].pos.x &&
				pPos->x - (fWidth / 2) <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth)
			{//横幅の当たり判定
				if (pPosOld->y <= g_aBlock[nCntBlock].pos.y&&
					pPos->y >= g_aBlock[nCntBlock].pos.y)
				{//上の当たり判定
					bIsLanding = true;
					pPos->y = g_aBlock[nCntBlock].pos.y;
					pMove->y = 0.0f;
					//移動量の更新
					pPos->x += g_aBlock[nCntBlock].move.x;
					//pPos->y += g_aBlock[nCntBlock].move.y;
				}
				else if (pPosOld->y - fHeigtht >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeigth &&
					pPos->y - fHeigtht <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeigth)
				{//下の当たり判定
					pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeigth + fHeigtht;
					pMove->y = 0.0f;
					QuestionBlock(nCntBlock);
				}
			}
			if (pPos->y - fHeigtht <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeigth &&
				pPos->y > g_aBlock[nCntBlock].pos.y )
			{//高さの当たり判定
				if (pPosOld->x - (fWidth / 2) >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth - g_aBlock[nCntBlock].move.x &&
					pPos->x - (fWidth / 2) <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth  - g_aBlock[nCntBlock].move.x)
				{//左の当たり判定
					pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + (fWidth / 2) - g_aBlock[nCntBlock].move.x;
					pMove->x = 0.0f;
				}
				else if (pPosOld->x + (fWidth / 2) <= g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].move.x &&
					pPos->x + (fWidth / 2) >= g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].move.x )
				{//右の当たり判定
					pPos->x = g_aBlock[nCntBlock].pos.x - (fWidth / 2) + g_aBlock[nCntBlock].move.x ;
					pMove->x = 0.0f;
				}
			}
		}
	}

	return bIsLanding;
}

//-------------------------------------------
//ハテナブロックの処理
//-------------------------------------------
void QuestionBlock(int nCntBlock)
{
	if (g_aBlock[nCntBlock].nType == BLOCK_QUESTION)
	{
		if (g_aBlock[nCntBlock].nLife != 0)
		{
			PlaySound(SOUND_LABEL_SE_BLOCK);

			//ブロックの上にアイテムを生成する
			g_aBlock[nCntBlock].nLife = 0;
			HitBlock(nCntBlock);
			if(g_aBlock[nCntBlock].nItem == ENEMY_WOLF)
			{//敵
			SetEnemy(D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y - BLOCK_HEIGHT, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), ENEMY_WOLF, 2,0);
			}
			else if (g_aBlock[nCntBlock].nItem == ITEM_POTION)
			{//回復薬
				SetItem(D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y - BLOCK_HEIGHT, 0.0f), ITEM_POTION);
			}
			else
			{//飴
				SetItem(D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y - BLOCK_HEIGHT, 0.0f), ITEM_CANDY);
			}
		}
	}
}

//-------------------------------------------
//ブロックのヒット処理
//-------------------------------------------
void HitBlock(int nCntBlock)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * nCntBlock;

	if (g_aBlock[nCntBlock].bUse == true)
	{
		if (g_aBlock[nCntBlock].nLife <= 0)
		{
			g_aBlock[nCntBlock].state = BLOCKSTATE_DAMAGE;
			g_aBlock[nCntBlock].nCounterState = 10;

			//頂点カラーの変更
			pVtx[0].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();
}

//-------------------------------------------
//ブロックの読み込み処理
//-------------------------------------------
void LoadBlock(void)
{
	int nCount = 0;

	FILE * pFile;		//ファイルポインタを宣言

	//ファイルを開く
	pFile = fopen("data/block.txt", "r");

	if (pFile != NULL)
	{//ファイルが開けた場合
		while (1)
		{
			fscanf(pFile, "%s", &g_cBlock[0]);		//文字列の読み込み

			if (strcmp(&g_cBlock[0], "BLOCK_TEXNAME") == 0)
			{//テクスチャ名の読み込み
				fscanf(pFile, "%s", &g_cBlock[0]);		//文字列の読み込み
				fscanf(pFile, "%s", &g_cBlockTexName[nCount][0]);
				nCount++;
			}

			if (strcmp(&g_cBlock[0], "PLACESET") == 0)
			{//モデルの数読み込み
				fscanf(pFile, "%s", &g_cBlock[0]);
				do
				{
					fscanf(pFile, "%s", &g_cBlock[0]);		//文字列の読み込み

					if (strcmp(&g_cBlock[0], "POS") == 0)
					{//位置の読み込み
						fscanf(pFile, "%s", &g_cBlock[0]);
						fscanf(pFile, "%f", &g_aBlockFile[g_nCntFile][0].pos.x);		//文字列の読み込み
						fscanf(pFile, "%f", &g_aBlockFile[g_nCntFile][0].pos.y);		//文字列の読み込み
						fscanf(pFile, "%f", &g_aBlockFile[g_nCntFile][0].pos.z);		//文字列の読み込み
					}
					else if (strcmp(&g_cBlock[0], "WIDTH") == 0)
					{//幅の読み込み
						fscanf(pFile, "%s", &g_cBlock[0]);
						fscanf(pFile, "%f", &g_aBlockFile[g_nCntFile][0].fWidth);		//文字列の読み込み
					}
					else if (strcmp(&g_cBlock[0], "HEIGTH") == 0)
					{//高さの読み込み
						fscanf(pFile, "%s", &g_cBlock[0]);
						fscanf(pFile, "%f", &g_aBlockFile[g_nCntFile][0].fHeigth);		//文字列の読み込み
					}
					else if (strcmp(&g_cBlock[0], "TYPE") == 0)
					{//種類の読み込み
						fscanf(pFile, "%s", &g_cBlock[0]);
						fscanf(pFile, "%d", &g_aBlockFile[g_nCntFile][0].nType);		//文字列の読み込み
					}
					else if (strcmp(&g_cBlock[0], "ITEM") == 0)
					{//アイテムの読み込み
						fscanf(pFile, "%s", &g_cBlock[0]);
						fscanf(pFile, "%d", &g_aBlockFile[g_nCntFile][0].nItem);		//文字列の読み込み
					}
				} while (strcmp(&g_cBlock[0], "END_PLACESSET") != 0);
				g_nCntFile++;
			}

			if (strcmp(&g_cBlock[0], "END_BLOCKSET") == 0)
			{//この文があったら抜ける
				break;
			}
		}
		fclose(pFile);									//ファイルを閉じる
	}
	else
	{//ファイルが開けなかった場合
		printf("ファイルが開けませんでした");
	}

}

//-------------------------------------------
//ブロックの取得
//-------------------------------------------
BLOCK * GetBlock(void)
{
	return &g_aBlock[0];
}