//-------------------------------------------------
//
//ゴール処理[goal.h]
//Author:平野舞
//
//-------------------------------------------------

//インクルードファイル
#include "goal.h"
#include "fade.h"

//グローバル宣言
LPDIRECT3DTEXTURE9 g_pTextureGoal = {};					//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGoal = NULL;			//頂点バッファへのポインタ
Goal g_Goal;											//ゴールの情報
int g_nContGoal = 0;

//-------------------------------------------
//城の初期化処理
//-------------------------------------------
void InitGoal(void)
{
	g_nContGoal = 0;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Goal000.png",
		&g_pTextureGoal);
		
	g_Goal.pos = D3DXVECTOR3(9000.0f, 650.0f, 0.0f);	//位置の初期化
	g_Goal.move = D3DXVECTOR3(-0.0f, 0.0f, 0.0f);		//移動量の初期化
	g_Goal.bUse= true;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGoal,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_Goal.pos.x - (GOAL_WIDTH / 2), g_Goal.pos.y - GOAL_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Goal.pos.x + (GOAL_WIDTH / 2), g_Goal.pos.y - GOAL_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Goal.pos.x - (GOAL_WIDTH / 2), g_Goal.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Goal.pos.x + (GOAL_WIDTH / 2), g_Goal.pos.y, 0.0f);

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
	pVtx[0].tex = D3DXVECTOR2(0.0f ,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f ,0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f ,1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f ,1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffGoal->Unlock();
}

//-------------------------------------------
//城の終了処理
//-------------------------------------------
void UninitGoal(void)
{
	//テクスチャの破棄
	if (g_pTextureGoal != NULL)
	{
		g_pTextureGoal->Release();
		g_pTextureGoal = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffGoal != NULL)
	{
		g_pVtxBuffGoal->Release();
		g_pVtxBuffGoal = NULL;
	}
}

//-------------------------------------------
//城の更新処理
//-------------------------------------------
void UpdateGoal(void)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	//位置を更新
	g_Goal.pos.x += g_Goal.move.x;
	g_Goal.pos.y += g_Goal.move.y;

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_Goal.pos.x - (GOAL_WIDTH / 2), g_Goal.pos.y - GOAL_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Goal.pos.x + (GOAL_WIDTH / 2), g_Goal.pos.y - GOAL_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Goal.pos.x - (GOAL_WIDTH / 2), g_Goal.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Goal.pos.x + (GOAL_WIDTH / 2), g_Goal.pos.y, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffGoal->Unlock();
}

//-------------------------------------------
//城の描画処理
//-------------------------------------------
void DrawGoal(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffGoal, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureGoal);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//-------------------------------------------
//城の当たり判定処理
//-------------------------------------------
void CollisionGoal(D3DXVECTOR3 * pPos, float fWidth, float fHeigtht)
{
	int nData = GetTime();

	if (g_Goal.bUse == true)
	{//城を使っているとき
		if (pPos->x + (fWidth / 2) >= g_Goal.pos.x - (GOAL_WIDTH / 2)
			&& pPos->x - (fWidth / 2) <= g_Goal.pos.x + (GOAL_WIDTH / 2)
			&& pPos->y >= g_Goal.pos.y - GOAL_HEIGHT
			&& pPos->y - fHeigtht <= g_Goal.pos.y)
		{
			if (g_nContGoal == 0)
			{
				PlaySound(SOUND_LABEL_SE_GOAL);
				AddScore(1700);
				AddScore(nData * 65);
				SetFade(MODE_GAMECLEAR);
				g_nContGoal = 1;
			}
		}
	}
}

//-------------------------------------------
//城の取得
//-------------------------------------------
Goal * GetGoal(void)
{
	return &g_Goal;
}