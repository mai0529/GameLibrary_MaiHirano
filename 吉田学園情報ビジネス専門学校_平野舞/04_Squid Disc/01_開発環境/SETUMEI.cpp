//============================================================
//
//ゲーム説明の処理(Setumei.cpp)
//AUTHOR:佐々木陸斗
//
//=============================================================
#include "main.h"
#include "input.h"
#include "SETUMEI.h"
#include "game.h"
#include "fade.h"
#include "sound.h"
#include "Choices.h"
#include"Frame.h"
#include"controller.h"

//==============================================================
//グローバル変数
//==============================================================

LPDIRECT3DTEXTURE9 g_pTextureSetumei = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSetumei = NULL;//頂点バッファへのぽいんた

//==============================================================
//ゲーム説明の初期化処理
//==============================================================
void lnitSetumei(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//サウンドの再生
	PlaySound(SOUND_LABEL_TITLE);

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/SETUMEI.jpg",
		&g_pTextureSetumei);

	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSetumei,
		NULL);

	VERTEX_2D*pVtx;		//頂点情報へポインタ

	//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffSetumei->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの描画
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファアンロック
	g_pVtxBuffSetumei->Unlock();
}

//==============================================================
//ゲーム説明の終了
//==============================================================
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

//==============================================================
//ゲーム説明の更新処理
//==============================================================
void UpdateSetumei(void)
{
	// フェード情報の取得
	FADE fade = GetFade();
	if (GetKeyboardTrigger(DIK_RETURN) == true && fade == FADE_NONE || GetControllerPressTrigger(0, XINPUT_GAMEPAD_A) == true && fade == FADE_NONE)
	{
		//サウンドの再生
		PlaySound(SOUND_LABEL_SE_Score);
		//モード設定
		SetFade(MODE_TITLE);
	}
}

//==============================================================
//ゲーム説明の描画処理
//==============================================================
void DrawSetumei(void)
{

	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffSetumei, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureSetumei);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

