//============================================================
//
//画面遷移の処理(fade.cpp)
//AUTHOR:佐々木陸斗
//
//=============================================================
#include "main.h"
#include "input.h"
#include"Fade.h"
#include"game.h"
#include"sound.h"
#include"Time.h"
#include"fade.h"
//==============================================================
//グローバル変数
//==============================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;		//頂点バッファへのポインタ
FADE g_fade;										//フェード状態
MODE g_modeNext;									//次の画面モード
D3DXCOLOR g_colorFade;								//ポリゴン（フェード）の色

//==============================================================
//フェード初期化処理
//==============================================================
void lnitFade(MODE modeNext)
{
	LPDIRECT3DDEVICE9 pDevice;

	g_fade = FADE_IN;							//フェードイン状態
	g_modeNext = modeNext;						//次の画面（モード）を設定
	g_colorFade = D3DXCOLOR(0.0f,0.0f,0.0f,1.0f);//黒いポリゴンにしておく

	 //デバイスの取得
	pDevice = GetDevice();


	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);


	VERTEX_2D*pVtx;		//頂点情報へポインタ

	//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DXCOLOR(g_colorFade);
	pVtx[1].col = D3DXCOLOR(g_colorFade);
	pVtx[2].col = D3DXCOLOR(g_colorFade);
	pVtx[3].col = D3DXCOLOR(g_colorFade);


	//頂点バッファアンロック
	g_pVtxBuffFade->Unlock();

	//モードの設定
	SetMode(g_modeNext);

}

//==============================================================
//フェードの終了処理
//==============================================================
void UninitFade(void)
{
	//頂点バッファの破棄
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}

//==============================================================
//フェードの更新処理
//==============================================================
void UpdateFade(void)
{
	if (g_fade == FADE_IN)

	{//フェードイン状態
		g_colorFade.a -= 0.01f;//ポリゴンを透明にしていく

		if (g_colorFade.a <= 0.0f)
		{
			g_colorFade.a = 0.0f;
			g_fade = FADE_NONE;		//何もしていない状態に
		}

	}
	else if (g_fade == FADE_OUT)
	{//フェードアウト状態
		g_colorFade.a += 0.07f;//ポリゴンを不透明にしていく

		if (g_colorFade.a >= 1.0f)
		{
			g_colorFade.a = 1.0f;
			g_fade = FADE_IN;		//フェードイン状態に

			//モードの設定（次の画面に移行）
			SetMode(g_modeNext);
		}

	}

	//頂点カラーの設定

	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの描画
	pVtx[0].col = D3DXCOLOR(g_colorFade);
	pVtx[1].col = D3DXCOLOR(g_colorFade);
	pVtx[2].col = D3DXCOLOR(g_colorFade);
	pVtx[3].col = D3DXCOLOR(g_colorFade);

	//頂点バッファアンロック
	g_pVtxBuffFade->Unlock();
}

//==============================================================
//フェードの描画処理
//==============================================================
void DrawFade(void)
{

	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0,NULL);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
	
//==============================================================
//フェードの設定処理
//==============================================================
void SetFade(MODE modeNext)
{
	g_fade = FADE_OUT;								//フェードアウト状態に
	g_modeNext = modeNext;							//次の画面（モード）を設定
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);//黒いポリゴンを透明に
}

//==============================================================
//フェードの状態を取得
//==============================================================
FADE GetFade(void)
{
	return g_fade;
}

