//============================================================
//
//タイトルの処理(TITLE.cpp)
//AUTHOR:佐々木陸斗
//
//=============================================================
#include "main.h"
#include "input.h"
#include "TITLE.h"
#include "game.h"
#include "fade.h"
#include "sound.h"
#include "Choices.h"
#include"Frame.h"

//==============================================================
//グローバル変数
//==============================================================

LPDIRECT3DTEXTURE9 g_pTextureTITLE = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTITLE = NULL;//頂点バッファへのぽいんた

//==============================================================
//タイトルの初期化処理
//==============================================================
void lnitTITLE(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	
	//サウンドの再生
	PlaySound(SOUND_LABEL_TITLE);

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/TITLE5.jpg",
		&g_pTextureTITLE);

	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 ,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTITLE,
		NULL);

	VERTEX_2D*pVtx;		//頂点情報へポインタ

	//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffTITLE->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffTITLE->Unlock();

	lnitFrame();
	lnitChoices();

	SetFrame(D3DXVECTOR3(800.0f, 550.0f, 0.0f));
	SetChoices(D3DXVECTOR3(800.0f, 550.0f, 0.0f));

}

//==============================================================
//タイトルの終了
//==============================================================
void UninitTITLE(void)
{
	//サウンドの停止
	StopSound();

	UninitFrame();
	UninitChoices();

	//テクスチャの破棄
	if (g_pTextureTITLE != NULL)
	{
		g_pTextureTITLE->Release();
		g_pTextureTITLE = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffTITLE != NULL)
	{
		g_pVtxBuffTITLE->Release();
		g_pVtxBuffTITLE = NULL;
	}
}

//==============================================================
//タイトルの更新処理
//==============================================================
void UpdateTITLE(void)
{
	UpdateFrame();
	UpdateChoices();
}

//==============================================================
//タイトルの描画処理
//==============================================================
void DrawTITLE(void)
{
	
	LPDIRECT3DDEVICE9 pDevice;
	
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTITLE, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTITLE);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0 , 2);

	
	DrawChoices();
	DrawFrame();
}

