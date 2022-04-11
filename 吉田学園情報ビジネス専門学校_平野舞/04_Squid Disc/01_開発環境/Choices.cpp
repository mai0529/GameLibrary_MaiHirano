//============================================================
//
//選択肢処理(Choices.cpp)
//AUTHOR:佐々木陸斗
//
//=============================================================
#include "main.h"

//==============================================================
//グローバル変数
//==============================================================
LPDIRECT3DTEXTURE9 g_pTextureChoices = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffChoices = NULL;//頂点バッファへのぽいんた
D3DXVECTOR3 g_ChoicesPos;

//==============================================================
//選択肢の初期化処理
//==============================================================
void lnitChoices(void)
{

	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Choices.png",
		&g_pTextureChoices);

	//頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffChoices,
		NULL);

	VERTEX_2D*pVtx;		//頂点情報へポインタ

	g_ChoicesPos = D3DXVECTOR3(800.0f, 550.0f, 0.0f);

	//頂点バッファをロックし、頂点情報へポインタ取得
	g_pVtxBuffChoices->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffChoices->Unlock();
}

//==============================================================
//操作説明の終了
//==============================================================
void UninitChoices(void)
{
	//テクスチャの破棄
	if (g_pTextureChoices != NULL)
	{
		g_pTextureChoices->Release();
		g_pTextureChoices = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffChoices != NULL)
	{
		g_pVtxBuffChoices->Release();
		g_pVtxBuffChoices = NULL;
	}
}

//==============================================================
//操作説明の更新処理
//==============================================================
void UpdateChoices(void)
{

}

//==============================================================
//操作説明の描画処理
//==============================================================
void DrawChoices(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffChoices, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureChoices);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//選択肢の設定処理
void SetChoices(D3DXVECTOR3 pos)
{

	VERTEX_2D*pVtx;
	g_pVtxBuffChoices->Lock(0, 0, (void**)&pVtx, 0);


	g_ChoicesPos = pos;

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(420.0f, 400.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(860.0f, 400.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(420.0f, 600.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(860.0f, 600.0f, 0.0f);

	pVtx += 4;//ポインタを４つ分進める

	g_pVtxBuffChoices->Unlock();
}