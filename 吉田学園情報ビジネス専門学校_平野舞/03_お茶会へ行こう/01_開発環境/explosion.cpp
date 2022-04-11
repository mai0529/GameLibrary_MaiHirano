//-------------------------------------------
//
//弾の爆発処理[explosion.cpp]
//Author:平野舞
//
//-------------------------------------------
#include "explosion.h"
#include "sound.h"

//マクロ定義
#define MAX_EXPLOSION			(128)		//弾の最大数
#define EXPLOSION_WIDTH			(40.0f)		//弾の幅
#define EXPLOSION_HEIGHT		(40.0f)		//弾の高さ
#define EXPLOSION_CNTANIM		(4)			//アニメーション速度

//弾爆発の構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXCOLOR col;			//色
	int nCounterAnim;		//アニメーションカウンター
	int nPatternAnim;		//アニメーションパターンNo.
	bool bUse;				//使用しているかどうか
}Explosion;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;			//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;		//頂点バッファへのポインタ
Explosion g_aExplosion[MAX_EXPLOSION];					//弾の情報

//-------------------------------------------
//弾爆発の初期化処理
//-------------------------------------------
void InitExplosion(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	int nCntExplosion;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/explosion000.png",
		&g_pTextureExplosion);

	//弾の情報の初期化
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_WIDTH, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_HEIGHT, g_aExplosion[nCntExplosion].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_WIDTH, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_HEIGHT, g_aExplosion[nCntExplosion].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_WIDTH, g_aExplosion[nCntExplosion].pos.y + EXPLOSION_HEIGHT, g_aExplosion[nCntExplosion].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_WIDTH, g_aExplosion[nCntExplosion].pos.y + EXPLOSION_HEIGHT, g_aExplosion[nCntExplosion].pos.z);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
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
	g_pVtxBuffExplosion->Unlock();
}

//-------------------------------------------
//弾爆発の終了処理
//-------------------------------------------
void UninitExplosion(void)
{
	//テクスチャの破棄
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//-------------------------------------------
//弾爆発の更新処理
//-------------------------------------------
void UpdateExplosion(void)
{
	int nCntExplosion;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{//爆発が使用されている
		 //サウンドの再生
			//PlaySound(SOUND_LABEL_SE_EXPLOSION);
			//弾の爆発の更新
			g_aExplosion[nCntExplosion].nCounterAnim++;

			//カウンターが4になったら
			if (g_aExplosion[nCntExplosion].nCounterAnim % EXPLOSION_CNTANIM == 0)
			{//パターンNo.を増やす
				g_aExplosion[nCntExplosion].nPatternAnim++;
			}

			if (g_aExplosion[nCntExplosion].nPatternAnim == 7)
			{
				g_aExplosion[nCntExplosion].bUse = false;		//使用していない状態にする
			}

			//頂点座標の更新
			pVtx[0].tex = D3DXVECTOR2(0.125f * g_aExplosion[nCntExplosion].nPatternAnim, 0.0f);
			pVtx[1].tex = D3DXVECTOR2((0.125f * g_aExplosion[nCntExplosion].nPatternAnim) + 0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.125f * g_aExplosion[nCntExplosion].nPatternAnim, 1.0f);
			pVtx[3].tex = D3DXVECTOR2((0.125f * g_aExplosion[nCntExplosion].nPatternAnim) + 0.125f , 1.0f);

			pVtx += 4;		//頂点データを４つ分進める
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}

//-------------------------------------------
//弾爆発の描画処理
//-------------------------------------------
void DrawExplosion(void)
{
	int nCntExplosion;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureExplosion);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{//弾が使用されている場合
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, 2);
		}
	}
}

//-------------------------------------------
//弾爆発の設定処理
//-------------------------------------------
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCntExplosion;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{//弾が使用されていない場合
			g_aExplosion[nCntExplosion].nCounterAnim = 0;
			g_aExplosion[nCntExplosion].nPatternAnim = 0;

			g_aExplosion[nCntExplosion].pos = pos;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_WIDTH, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_HEIGHT, g_aExplosion[nCntExplosion].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_WIDTH, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_HEIGHT, g_aExplosion[nCntExplosion].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_WIDTH, g_aExplosion[nCntExplosion].pos.y + EXPLOSION_HEIGHT, g_aExplosion[nCntExplosion].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_WIDTH, g_aExplosion[nCntExplosion].pos.y + EXPLOSION_HEIGHT, g_aExplosion[nCntExplosion].pos.z);

			g_aExplosion[nCntExplosion].col = col;
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			g_aExplosion[nCntExplosion].bUse = true;

			break;
		}
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}

