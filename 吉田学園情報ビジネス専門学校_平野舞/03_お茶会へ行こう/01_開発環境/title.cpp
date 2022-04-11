//-------------------------------------------
//
//ゲームタイトル処理[title.cpp]
//Author:平野舞
//
//-------------------------------------------
#include "title.h"
#include "sound.h"
#include "input.h"
#include "fade.h"
#include "controller.h"

//マクロ定義
#define TITLE_WIDTH		(340.0f)	//幅
#define TITLE_HEIGHT	(170.0f)	//高さ

//グローバル宣言
LPDIRECT3DTEXTURE9 g_pTextureTitle = NULL;			//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;		//頂点バッファへのポインタ
D3DXVECTOR3 g_posTitle;								//タイトルの位置
bool g_TitleFade;									//フェードしているかどうか

//-------------------------------------------
//初期化処理
//-------------------------------------------
void InitTitle(void)
{
	g_posTitle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//座標の初期化
	g_TitleFade = false;			//フェードしていない

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/title001.png",
		&g_pTextureTitle);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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

	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM001);
}

//-------------------------------------------
//終了処理
//-------------------------------------------
void UninitTitle(void)
{
	//サウンドの停止
	StopSound();

	//テクスチャの破棄
	if (g_pTextureTitle != NULL)
	{
		g_pTextureTitle->Release();
		g_pTextureTitle = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

}

//-------------------------------------------
//更新処理
//-------------------------------------------
void UpdateTitle(void)
{
	//決定キー(ENTERキー)が押されたかどうか
	if (GetKeyboardTrigger(DIK_RETURN) == true && !g_TitleFade
		|| GetControllerPressTrigger(0, XINPUT_GAMEPAD_START) && !g_TitleFade)
	{
		SetFade(MODE_SETUMEI);	//説明画面に移行
		g_TitleFade = true;		//フェード中
	}
}

//-------------------------------------------
//描画処理
//-------------------------------------------
void DrawTitle(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureTitle);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}