//============================================================
//
//選択肢処理(Frame.cpp)
//AUTHOR:佐々木陸斗
//
//=============================================================
#include "main.h"
#include"input.h"
#include"fade.h"
#include"sound.h"
#include"controller.h"
//==============================================================
//グローバル変数
//==============================================================
LPDIRECT3DTEXTURE9 g_pTextureFrame = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFrame = NULL;//頂点バッファへのぽいんた
D3DXVECTOR3 g_FramePos;
int Count = 0;
//==============================================================
//選択肢の初期化処理
//==============================================================
void lnitFrame(void)
{

	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Frame.png",
		&g_pTextureFrame);

	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFrame,
		NULL);

	VERTEX_2D*pVtx;		//頂点情報へポインタ

	g_FramePos = D3DXVECTOR3(800.0f, 550.0f, 0.0f);

	//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffFrame->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffFrame->Unlock();
}

//==============================================================
//操作説明の終了
//==============================================================
void UninitFrame(void)
{
	//サウンドの停止
	StopSound();
	//テクスチャの破棄
	if (g_pTextureFrame != NULL)
	{
		g_pTextureFrame->Release();
		g_pTextureFrame = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffFrame != NULL)
	{
		g_pVtxBuffFrame->Release();
		g_pVtxBuffFrame = NULL;
	}
}

//==============================================================
//操作説明の更新処理
//==============================================================
void UpdateFrame(void)
{
	// フェード情報の取得
	FADE fade = GetFade();
	//決定キー(Wキーが押されたかどうか)
	if (GetKeyboardTrigger(DIK_W) == true || GetControllerPressTrigger(0, XINPUT_GAMEPAD_DPAD_UP) == true)
	{
		//サウンドの再生
		PlaySound(SOUND_LABEL_SE_Frame);
		VERTEX_2D*pVtx;
		g_pVtxBuffFrame->Lock(0, 0, (void**)&pVtx, 0);
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(420.0f, 400.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(860.0f, 400.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(420.0f, 485.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(860.0f, 485.0f, 0.0f);
		pVtx += 4;//ポインタを４つ分進める
		Count = 0;
	}
	//決定キー(ENTERキーが押されたかどうか)
	else if (GetKeyboardTrigger(DIK_RETURN) == true && fade == FADE_NONE || GetControllerPressTrigger(0, XINPUT_GAMEPAD_A) == true && fade == FADE_NONE)
		{
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_Score);

			//モード設定
			SetFade(MODE_SOUSA);
		}




	//決定キー(Sキーが押されたかどうか)
	if (GetKeyboardTrigger(DIK_S) == true || GetControllerPressTrigger(0, XINPUT_GAMEPAD_DPAD_DOWN) == true)
	{
		//サウンドの再生
		PlaySound(SOUND_LABEL_SE_Frame);
		VERTEX_2D*pVtx;
		g_pVtxBuffFrame->Lock(0, 0, (void**)&pVtx, 0);
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(420.0f, 515.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(860.0f, 515.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(420.0f, 600.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(860.0f, 600.0f, 0.0f);
		pVtx += 4;//ポインタを４つ分進める
		Count++;
	}
	//決定キー(ENTERキーが押されたかどうか)
	if (Count > 0)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true && fade == FADE_NONE || GetControllerPressTrigger(0, XINPUT_GAMEPAD_A) == true && fade == FADE_NONE)
		{
			//サウンドの再生
			PlaySound(SOUND_LABEL_SE_Score);

			//モード設定
			SetFade(MODE_SETUMEI);
			Count = 0;
		}
	}
}

//==============================================================
//操作説明の描画処理
//==============================================================
void DrawFrame(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffFrame, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureFrame);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//選択肢の設定処理
void SetFrame(D3DXVECTOR3 pos)
{

	VERTEX_2D*pVtx;
	g_pVtxBuffFrame->Lock(0, 0, (void**)&pVtx, 0);


	g_FramePos = pos;

	pVtx[0].pos = D3DXVECTOR3(420.0f, 400.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(860.0f, 400.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(420.0f, 485.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(860.0f, 485.0f, 0.0f);

	pVtx += 4;//ポインタを４つ分進める

	g_pVtxBuffFrame->Unlock();
}