//-----------------------------------------------------------------------------------------------
//
// 2Dポリゴン処理[object2D.cpp]
// Author : 平野舞
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// インクルードファイル
//-----------------------------------------------------------------------------------------------
#include "object2D.h"			// 2Dオブジェクト
#include "application.h"		// アプリケーション
#include "renderer.h"			// レンダリング
#include "main.h"				// メイン
#include "ResourceManager.h"	// リソースマネージャー

//-----------------------------------------------------------------------------------------------
// コンストラクタ
//
// int nPriority → 描画優先順位を指定
//-----------------------------------------------------------------------------------------------
CObject2D::CObject2D(int nPriority /* = 3 */)
	:CObject(nPriority),m_pVtxBuffer(nullptr), m_pos(0.0f, 0.0f, 0.0f), m_size(0.0f, 0.0f, 0.0f), m_col(0.0f, 0.0f, 0.0f, 0.0f)
{

}

//-----------------------------------------------------------------------------------------------
//　デストラクタ
//-----------------------------------------------------------------------------------------------
CObject2D::~CObject2D()
{

}

//-----------------------------------------------------------------------------------------------
//　生成
//
// char* cFileName		   → 画像の名前(パスも含め)
// const D3DXVECTOR3& pos  → 生成する座標の位置
// const D3DXVECTOR3& size → 生成するポリゴンの大きさ
//-----------------------------------------------------------------------------------------------
CObject2D* CObject2D::Create(char* cFileName,const D3DXVECTOR3& pos, const D3DXVECTOR3& size, int nPriority /*= 3*/)
{
	// ポインタクラスを宣言
	CObject2D* pObject2D = new CObject2D(nPriority);

	if (pObject2D != nullptr)
	{// もしnullptrではなかったら
		// 画像の設定
		pObject2D->LoadTexture(cFileName);
		// ポリゴンサイズを設定
		pObject2D->SetSize(size);

		// 初期化
		pObject2D->Init(pos);
	}

	return pObject2D;
}

//-----------------------------------------------------------------------------------------------
// 初期化
//
// const D3DXVECTOR3& pos → 最初に表示する座標位置
//-----------------------------------------------------------------------------------------------
HRESULT CObject2D::Init(const D3DXVECTOR3& pos)
{
	SetPosition(pos);

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffer,
		nullptr);

	// 頂点バッファのポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファをロックしポインタを取得
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - (m_size.x / 2.0f), pos.y - (m_size.y / 2.0f), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + (m_size.x / 2.0f), pos.y - (m_size.y / 2.0f), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - (m_size.x / 2.0f), pos.y + (m_size.y / 2.0f), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + (m_size.x / 2.0f), pos.y + (m_size.y / 2.0f), 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR( 1.0f,1.0f,1.0f,1.0f );
	pVtx[1].col = D3DXCOLOR( 1.0f,1.0f,1.0f,1.0f );
	pVtx[2].col = D3DXCOLOR( 1.0f,1.0f,1.0f,1.0f );
	pVtx[3].col = D3DXCOLOR( 1.0f,1.0f,1.0f,1.0f );

	// テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuffer->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
//　ポリゴン終了
//-----------------------------------------------------------------------------------------------
void CObject2D::Uninit()
{
	// 頂点バッファの破棄
	if (m_pVtxBuffer != nullptr)
	{
		m_pVtxBuffer->Release();
		m_pVtxBuffer = nullptr;
	}

	// オブジェクトの破棄
	Release();
}

//-----------------------------------------------------------------------------------------------
//　ポリゴン更新
//-----------------------------------------------------------------------------------------------
void CObject2D::Update()
{

}

//-----------------------------------------------------------------------------------------------
//　ポリゴン描画
//-----------------------------------------------------------------------------------------------
void CObject2D::Draw()
{
	LPDIRECT3DTEXTURE9 pTexture = CResourceManager::GetInstance()->GetTexture(m_cFileName);

	// レンダリングの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャ設定
	pDevice->SetTexture(0, pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//-----------------------------------------------------------------------------------------------
//　位置の設定
//
// const D3DXVECTOR3& pos → 表示したい座標位置
//-----------------------------------------------------------------------------------------------
void CObject2D::SetPosition(const D3DXVECTOR3& pos)
{
	// 位置
	m_pos = pos;
}

//-----------------------------------------------------------------------------------------------
//　位置の取得
//-----------------------------------------------------------------------------------------------
const D3DXVECTOR3& CObject2D::GetPosition() const
{
	return m_pos;
}

//-----------------------------------------------------------------------------------------------
//　サイズの設定
//
// D3DXVECTOR3 size → ポリゴンの大きさ
//-----------------------------------------------------------------------------------------------
void CObject2D::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//-----------------------------------------------------------------------------------------------
// サイズの取得
//-----------------------------------------------------------------------------------------------
const D3DXVECTOR3& CObject2D::GetSize() const
{
	return m_size;
}

//-----------------------------------------------------------------------------------------------
// 1Pか2Pかを設定
//-----------------------------------------------------------------------------------------------
void CObject2D::SetPlayerType(MULTI_TYPE playerType)
{
	m_PlayerType = playerType;
}

//-----------------------------------------------------------------------------------------------
// 1Pか2Pかを取得
//-----------------------------------------------------------------------------------------------
MULTI_TYPE CObject2D::GetPlayerType()
{
	return m_PlayerType;
}

//-----------------------------------------------------------------------------------------------
//　色の設定
//
// D3DXCOLOR col → 色
//-----------------------------------------------------------------------------------------------
void CObject2D::SetColor(D3DXCOLOR col)
{
	m_col = col;

	// 頂点バッファのポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファをロックしポインタを取得
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].col = D3DXCOLOR(col.r , col.g , col.b , col.a );
	pVtx[1].col = D3DXCOLOR(col.r , col.g , col.b , col.a );
	pVtx[2].col = D3DXCOLOR(col.r , col.g , col.b , col.a );
	pVtx[3].col = D3DXCOLOR(col.r , col.g , col.b , col.a );

	// 頂点バッファをアンロックする
	m_pVtxBuffer->Unlock();
}

//-----------------------------------------------------------------------------------------------
// 頂点カラーの取得
//-----------------------------------------------------------------------------------------------
D3DXCOLOR CObject2D::GetColor()
{
	return m_col;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//　テクスチャアニメーション座標の設定
//
// int nDivisionX	→ U座標の分割数
// int nDivisionV	→ V座標の分割数
// int nNowPatternX → U座標の現在のアニメーション番号
// int nNowPatternV → V座標の現在のアニメーション番号
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CObject2D::SetTexAnim(int nDivisionU, int nDivisionV, int nNowPatternU, int nNowPatternV)
{
	// 頂点バッファのポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファをロックしポインタを取得
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].tex = D3DXVECTOR2(((1.0f / nDivisionU) * nNowPatternU), ((1.0f / nDivisionV) * nNowPatternV));
	pVtx[1].tex = D3DXVECTOR2(((1.0f / nDivisionU) * nNowPatternU) + (1.0f / nDivisionU), ((1.0f / nDivisionV) * nNowPatternV));
	pVtx[2].tex = D3DXVECTOR2(((1.0f / nDivisionU) * nNowPatternU), ((1.0f / nDivisionV) * nNowPatternV) + (1.0f / nDivisionV));
	pVtx[3].tex = D3DXVECTOR2(((1.0f / nDivisionU) * nNowPatternU) + (1.0f / nDivisionU), ((1.0f / nDivisionV) * nNowPatternV) + (1.0f / nDivisionV));

	// 頂点バッファをアンロックする
	m_pVtxBuffer->Unlock();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// アニメーション座標の設定
//
// float fTexU → U座標
// float fTexV → V座標
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CObject2D::SetTexPos(float fTexU, float fTexV)
{
	// 頂点バッファのポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファをロックしポインタを取得
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].tex = D3DXVECTOR2(fTexU, fTexV);
	pVtx[1].tex = D3DXVECTOR2(fTexU + 1.0f, fTexV);
	pVtx[2].tex = D3DXVECTOR2(fTexU, fTexV + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fTexU + 1.0f, fTexV + 1.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuffer->Unlock();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 位置の更新
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CObject2D::UpdatePos()
{
	// 頂点バッファのポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファをロックしポインタを取得
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2.0f), m_pos.y - (m_size.y / 2.0f), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2.0f), m_pos.y - (m_size.y / 2.0f), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2.0f), m_pos.y + (m_size.y / 2.0f), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2.0f), m_pos.y + (m_size.y / 2.0f), 0.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuffer->Unlock();
}

//-----------------------------------------------------------------------------------------------
// テクスチャの設定
//
// char* cFileName → ファイル名
//-----------------------------------------------------------------------------------------------
void CObject2D::LoadTexture(char* cFileName)
{
	m_cFileName = cFileName;
}