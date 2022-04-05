//-------------------------------------------
//
//ゲーム説明処理[setumei.cpp]
//Author:平野舞
//
//-------------------------------------------
#include "setumei.h"
#include "sound.h"
#include "input.h"
#include "fade.h"
#include "controller.h"

//マクロ定義
#define TITLE_WIDTH		(640.0f)	//幅
#define TITLE_HEIGHT	(360.0f)	//高さ

//グローバル宣言
LPDIRECT3DTEXTURE9 g_pTextureSetumei = NULL;			//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSetumei = NULL;		//頂点バッファへのポインタ
D3DXVECTOR3 g_posSetumei;								//タイトルの位置
bool g_SetumeiFade;										//フェードしているかどうか

//-------------------------------------------
//初期化処理
//-------------------------------------------
void InitSetumei(void)
{
	g_posSetumei = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//座標の初期化
	g_SetumeiFade = false;								//フェードしていない

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/setumei.png",
		&g_pTextureSetumei);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSetumei,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffSetumei->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(640.0f - TITLE_WIDTH, 360.0f - TITLE_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(640.0f + TITLE_WIDTH, 360.0f - TITLE_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(640.0f - TITLE_WIDTH, 360.0f + TITLE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(640.0f + TITLE_WIDTH, 360.0f + TITLE_HEIGHT, 0.0f);

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
	g_pVtxBuffSetumei->Unlock();

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM001);
}

//-------------------------------------------
//終了処理
//-------------------------------------------
void UninitSetumei(void)
{
	//サウンドの停止
	StopSound();

	//テクスチャの破棄
	if (g_pTextureSetumei != NULL)
	{
		g_pTextureSetumei->Release();
		g_pTextureSetumei = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffSetumei != NULL)
	{
		g_pVtxBuffSetumei->Release();
		g_pVtxBuffSetumei = NULL;
	}

}

//-------------------------------------------
//更新処理
//-------------------------------------------
void UpdateSetumei(void)
{
	//決定キー(ENTERキー)が押されたかどうか
	if (GetKeyboardTrigger(DIK_RETURN) == true && !g_SetumeiFade
		|| GetControllerPressTrigger(0, XINPUT_GAMEPAD_A) && !g_SetumeiFade)
	{
		SetFade(MODE_GAME);		//ゲーム画面に移行
		g_SetumeiFade = true;	//フェード中
	}
}

//-------------------------------------------
//描画処理
//-------------------------------------------
void DrawSetumei(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffSetumei, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureSetumei);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}