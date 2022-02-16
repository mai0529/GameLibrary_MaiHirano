//------------------------------------------ -
//
//ゲームリザルト処理[result.cpp]
//Author:平野舞
//
//-------------------------------------------
#include "result.h"
#include "input.h"
#include "sound.h"
#include "fade.h"

//マクロ定義
#define RESULT_WIDTH	(320.0f)	//幅
#define RESULT_HEIGHT	(170.0f)	//高さ

//グローバル宣言
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;				//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;		//頂点バッファへのポインタ
D3DXVECTOR3 g_posResult;								//タイトルの位置

//-------------------------------------------
//初期化処理
//-------------------------------------------
void InitResult(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/gameclear_logo001.png",
		&g_pTextureResult);

	g_posResult = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//座標の初期化

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(640.0f - RESULT_WIDTH, 360.0f - RESULT_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(640.0f + RESULT_WIDTH, 360.0f - RESULT_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(640.0f - RESULT_WIDTH, 360.0f + RESULT_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(640.0f + RESULT_WIDTH, 360.0f + RESULT_HEIGHT, 0.0f);

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

	//頂点バッファをアンロックする
	g_pVtxBuffResult->Unlock();

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM002);
}

//-------------------------------------------
//終了処理
//-------------------------------------------
void UninitResult(void)
{
	//サウンドの停止
	StopSound();

	//テクスチャの破棄
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}

//-------------------------------------------
//更新処理
//-------------------------------------------
void UpdateResult(void)
{
	//決定キー(ENTERキー)が押されたかどうか
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{//モード設定
		SetFade(MODE_TITLE);
	}
}

//-------------------------------------------
//描画処理
//-------------------------------------------
void DrawResult(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureResult);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}