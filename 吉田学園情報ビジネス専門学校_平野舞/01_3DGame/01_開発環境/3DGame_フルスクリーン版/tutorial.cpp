//-------------------------------------------
//
//ゲーム説明処理[setumei.cpp]
//Author:平野舞
//
//-------------------------------------------
#include "tutorial.h"
#include "sound.h"
#include "input.h"
#include "fade.h"

//マクロ定義
#define TITLE_WIDTH		(600.0f)	//幅
#define TITLE_HEIGHT	(320.0f)	//高さ

//グローバル宣言
LPDIRECT3DTEXTURE9 g_pTextureTutorial = NULL;			//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;		//頂点バッファへのポインタ
D3DXVECTOR3 g_posTutorial;								//タイトルの位置
int g_nCntTutorial;										//フェード用のカウント

//-------------------------------------------
//初期化処理
//-------------------------------------------
void InitTutorial(void)
{
	g_posTutorial = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//座標の初期化
	g_nCntTutorial = 0;									//カウントの初期化

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/tutorial001.jpg",
		&g_pTextureTutorial);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f, 0.0f);
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
	g_pVtxBuffTutorial->Unlock();

	//サウンドの再生
	PlaySound(SOUND_LABEL_BGM000);
}

//-------------------------------------------
//終了処理
//-------------------------------------------
void UninitTutorial(void)
{
	//サウンドの停止
	StopSound();

	//テクスチャの破棄
	if (g_pTextureTutorial != NULL)
	{
		g_pTextureTutorial->Release();
		g_pTextureTutorial = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}

}

//-------------------------------------------
//更新処理
//-------------------------------------------
void UpdateTutorial(void)
{
	//決定キー(ENTERキー)が押されたかどうか
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{//モード設定
		if (g_nCntTutorial == 0)
		{//0の時
			PlaySound(SOUND_LABEL_SE000);
			SetFade(MODE_GAME);		//ゲームモードに移行
			g_nCntTutorial = 1;
		}
	}
}

//-------------------------------------------
//描画処理
//-------------------------------------------
void DrawTutorial(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureTutorial);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}