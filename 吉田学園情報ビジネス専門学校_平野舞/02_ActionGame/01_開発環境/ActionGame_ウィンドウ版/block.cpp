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

//-------------------------------------------
//ブロックの初期化処理
//-------------------------------------------
void InitBlock(void)
{
	int nCntBlock;
	
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/block001.jpg",
		&g_apTextureBlock[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/block002.jpg",
		&g_apTextureBlock[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/block004.png",
		&g_apTextureBlock[2]);

	//ブロックの情報の初期化
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置の初期化
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量の初期化
		g_aBlock[nCntBlock].nType = BLOCK_BRICK;						//種類の初期化
		g_aBlock[nCntBlock].nNumber = 0;								//何番目か
		g_aBlock[nCntBlock].nLife = 0;									//寿命の初期化
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
	//X軸移動
	//SetBlock(D3DXVECTOR3(1080.0f, 500.0f, 0.0f), D3DXVECTOR3(-0.7f, 0.0f, 0.0f), BLOCK_WIDTH * 2, BLOCK_HEIGHT / 2, BLOCK_CONCRETE,1,0);
	//Y軸移動									
	//SetBlock(D3DXVECTOR3(700.0f, 720.0f, 0.0f), D3DXVECTOR3(-0.6f, -0.7f, 0.0f), BLOCK_WIDTH * 2, BLOCK_HEIGHT, BLOCK_CONCRETE,1);
	//中間										  
	SetBlock(D3DXVECTOR3(260.0f, 500.0f, 0.0f),  D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_CONCRETE,1,0);
	SetBlock(D3DXVECTOR3(300.0f, 500.0f, 0.0f),  D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION,1,0);
	SetBlock(D3DXVECTOR3(340.0f, 500.0f, 0.0f),  D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_CONCRETE,1,0);
															
	//2個目のハテナブロック									 
	SetBlock(D3DXVECTOR3(1550.0f, 520.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_CONCRETE, 1,0);
	SetBlock(D3DXVECTOR3(1590.0f, 520.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_CONCRETE, 1,0);
	SetBlock(D3DXVECTOR3(1630.0f, 520.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1,0);
															
	//ケーキを取りに行くためのブロック						
	SetBlock(D3DXVECTOR3(1320.0f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 3, BLOCK_HEIGHT, BLOCK_CONCRETE, 1,0);
	SetBlock(D3DXVECTOR3(1500.0f, 350.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 3, BLOCK_HEIGHT, BLOCK_CONCRETE, 1,0);
	SetBlock(D3DXVECTOR3(1680.0f, 200.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 3, BLOCK_HEIGHT, BLOCK_CONCRETE, 1,0);
															
	//3個目のハテナブロック									 
	SetBlock(D3DXVECTOR3(1800.0f, 450.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_CONCRETE, 1,0);
	SetBlock(D3DXVECTOR3(1840.0f, 450.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1,1);
	SetBlock(D3DXVECTOR3(1880.0f, 450.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_CONCRETE, 1,0);
															
	//4個目のハテナブロック									 
	SetBlock(D3DXVECTOR3(2500.0f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_CONCRETE, 1, 0);
	SetBlock(D3DXVECTOR3(2540.0f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 2);
	SetBlock(D3DXVECTOR3(2580.0f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_CONCRETE, 1, 0);

	//5～7個目のハテナブロック
	SetBlock(D3DXVECTOR3(3040.0f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);
	SetBlock(D3DXVECTOR3(3080.0f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 1);
	SetBlock(D3DXVECTOR3(3120.0f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);
																
	//下のコンクリブロック							
	SetBlock(D3DXVECTOR3(3700.0f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 20, BLOCK_HEIGHT, BLOCK_CONCRETE, 1, 0);

	//5～7個目のハテナブロック
	SetBlock(D3DXVECTOR3(3900.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_CONCRETE, 1, 0);
	SetBlock(D3DXVECTOR3(3940.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);
	SetBlock(D3DXVECTOR3(3980.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 1);
	SetBlock(D3DXVECTOR3(4020.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);
	SetBlock(D3DXVECTOR3(4060.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);
	SetBlock(D3DXVECTOR3(4100.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 2);
	SetBlock(D3DXVECTOR3(4140.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);
	SetBlock(D3DXVECTOR3(4180.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 2, BLOCK_HEIGHT, BLOCK_CONCRETE, 1, 0);
	SetBlock(D3DXVECTOR3(4260.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);
	SetBlock(D3DXVECTOR3(4300.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 1);
	SetBlock(D3DXVECTOR3(4340.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_CONCRETE, 1, 0);

	//?ブロックの間にあるコンクリ
	SetBlock(D3DXVECTOR3(2655.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH , BLOCK_HEIGHT, BLOCK_CONCRETE, 1, 0);
	SetBlock(D3DXVECTOR3(2735.0f, 300.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 2, BLOCK_HEIGHT, BLOCK_CONCRETE, 1, 0);
	SetBlock(D3DXVECTOR3(2850.0f, 450.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 3, BLOCK_HEIGHT, BLOCK_CONCRETE, 1, 0);

	//コンクリブロック
	for (int nCount = 0; nCount < 4; nCount++)
	{
		SetBlock(D3DXVECTOR3(5000.0f + (320 * nCount), 510.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 3, BLOCK_HEIGHT, BLOCK_CONCRETE, 1, 0);
		SetBlock(D3DXVECTOR3(5160.0f + (320 * nCount), 430.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 3, BLOCK_HEIGHT, BLOCK_CONCRETE, 1, 0);
	}

	SetBlock(D3DXVECTOR3(5650.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);
	SetBlock(D3DXVECTOR3(5250.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 2);
	SetBlock(D3DXVECTOR3(6030.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);
	SetBlock(D3DXVECTOR3(6200.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);


	SetBlock(D3DXVECTOR3(6400.0f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 15, BLOCK_HEIGHT, BLOCK_CONCRETE, 1, 0);

	//8～14個目のハテナブロック
	SetBlock(D3DXVECTOR3(6550.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);
	SetBlock(D3DXVECTOR3(6590.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);
	SetBlock(D3DXVECTOR3(6630.0f, 320.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);
	SetBlock(D3DXVECTOR3(6670.0f, 320.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);
	SetBlock(D3DXVECTOR3(6710.0f, 280.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);
	SetBlock(D3DXVECTOR3(6750.0f, 280.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);

	SetBlock(D3DXVECTOR3(6790.0f, 240.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 5, BLOCK_HEIGHT, BLOCK_CONCRETE, 1, 0);
	for (int nCount = 0; nCount < 3; nCount++)
	{
		SetBlock(D3DXVECTOR3(6830.0f + (BLOCK_WIDTH * nCount), 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);
	}

	//ゴール手前
	for (int nCount = 0; nCount < 7; nCount++)
	{//階段
		SetBlock(D3DXVECTOR3(8200.0f + (40 * nCount), 650.0f - (40 * nCount), 0.0f), D3DXVECTOR3(-0.0f, 0.0f, 0.0f), BLOCK_WIDTH,BLOCK_HEIGHT * nCount, BLOCK_CONCRETE, 1,0);
	}
	for (int nCount = 0; nCount < 7; nCount++)
	{//階段
		SetBlock(D3DXVECTOR3(8700.0f - (40 * nCount), 650.0f - (40 * nCount), 0.0f), D3DXVECTOR3(-0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT * nCount, BLOCK_CONCRETE, 1, 0);
	}
																
	//床														
	SetBlock(D3DXVECTOR3(0.0f, 650.0f, 0.0f),    D3DXVECTOR3(-0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 20, BLOCK_HEIGHT * 2, BLOCK_BRICK, 1,0);
	SetBlock(D3DXVECTOR3(950.0f, 650.0f, 0.0f),  D3DXVECTOR3(-0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 32, BLOCK_HEIGHT * 2, BLOCK_BRICK,  1,0);
	SetBlock(D3DXVECTOR3(2400.0f, 650.0f, 0.0f), D3DXVECTOR3(-0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 21, BLOCK_HEIGHT * 2, BLOCK_BRICK, 1, 0);
	SetBlock(D3DXVECTOR3(3400.0f, 650.0f, 0.0f), D3DXVECTOR3(-0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 32, BLOCK_HEIGHT * 2, BLOCK_BRICK, 1, 0);
	SetBlock(D3DXVECTOR3(4860.0f, 650.0f, 0.0f), D3DXVECTOR3(-0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 60, BLOCK_HEIGHT * 2, BLOCK_BRICK, 1, 0);
	SetBlock(D3DXVECTOR3(7460.0f, 650.0f, 0.0f), D3DXVECTOR3(-0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 48, BLOCK_HEIGHT * 2, BLOCK_BRICK, 1, 0);

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
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeigtht, Block nType,int nLife ,int nNumber)
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
			g_aBlock[nCntBlock].move = move;
			g_aBlock[nCntBlock].fWidth = fWidth;
			g_aBlock[nCntBlock].fHeigth = fHeigtht;
			g_aBlock[nCntBlock].nType = nType;
			g_aBlock[nCntBlock].nLife = nLife;
			g_aBlock[nCntBlock].nNumber = nNumber;
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
			if(g_aBlock[nCntBlock].nNumber == 1)
			{//敵
			SetEnemy(D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y - BLOCK_HEIGHT, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), ENEMY_WOLF, 2,0);
			}
			else if (g_aBlock[nCntBlock].nNumber == 2)
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
//ブロックの取得
//-------------------------------------------
BLOCK * GetBlock(void)
{
	return &g_aBlock[0];
}
//-------------------------------------------
//ブロックの状態管理処理
//-------------------------------------------
//void StateBlock(int nCntBlock)
//{
//	//頂点情報へのポインタ
//	VERTEX_2D *pVtx;
//
//	//頂点バッファをロックし、頂点情報へのポインタを取得
//	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);
//
//	//ブロックの位置情報の更新
//	switch (g_aBlock[nCntBlock].state)
//	{
//	case BLOCKSTATE_NORMAL:
//		break;
//	case BLOCKSTATE_DAMAGE:
//		//頂点カラーの設定
//		pVtx[0].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
//		pVtx[1].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
//		pVtx[2].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
//		pVtx[3].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
//
//			g_aBlock[nCntBlock].nCounterState--;
//			if(g_aBlock[nCntBlock].nCounterState >= 0)
//			{
//				g_aBlock[nCntBlock].pos.y = g_aBlock[nCntBlock].pos.y - 1.0f;
//			}
//			else
//			{//元の位置に戻す
//				g_aBlock[nCntBlock].pos.y = g_aBlock[nCntBlock].pos.y + 10.0f;
//				g_aBlock[nCntBlock].state = BLOCKSTATE_NORMAL;
//			}
//		break;
//	}
//	//頂点バッファをアンロックする
//	g_pVtxBuffBlock->Unlock();
//}