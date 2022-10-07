//-----------------------------------------------------------------------------------------------
//
// エフェクトの処理[effect.cpp]
// Author : 平野舞
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// インクルードファイル
//-----------------------------------------------------------------------------------------------
#include "effect.h"				// エフェクト
#include "application.h"		// アプリケーション
#include "renderer.h"			// レンダリング
#include "TextureFileName.h"	// 画像のファイル名

//-----------------------------------------------------------------------------------------------
// 定数宣言
//-----------------------------------------------------------------------------------------------
// 幅
static const float EFFECT_WIDTH = 40.0f;
// 高さ
static const float EFFECT_HEIGHT = 40.0f;
// 速度
static const float EFFECT_SPEED = 1.5f;
// 寿命
static const int EFFECT_LIFE = 30;

//-----------------------------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------------------------
CEffect::CEffect()
	:m_size(0.0f,0.0f,0.0f), m_fAngle(0.0f),m_nLife(0)
{

}

//-----------------------------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------------------------
CEffect::~CEffect()
{

}

//-----------------------------------------------------------------------------------------------
// 生成
//
//const D3DXVECTOR3& pos → 生成する座標位置
//-----------------------------------------------------------------------------------------------
CEffect* CEffect::Create(const D3DXVECTOR3& pos)
{
	// ポインタクラスを宣言
	CEffect* pPlayer = new CEffect;

	if (pPlayer != nullptr)
	{// もしnullptrではなかったら
	 // 初期化
		pPlayer->Init(pos);
	}

	return pPlayer;
}

//-----------------------------------------------------------------------------------------------
// 初期化
//
// const D3DXVECTOR3& pos → 最初に表示する座標位置
//-----------------------------------------------------------------------------------------------
HRESULT CEffect::Init(const D3DXVECTOR3& pos)
{
	// オブジェクトの種類の設定
	SetObjectType(OBJECT_TYPE::OBJECT_TYPE_EFFECT);
	// オブジェクトの親を設定
	SetObjectParent(OBJECT_PARENT::OBJECT_PARENT_GAME);

	// テクスチャの設定
	CObject2D::LoadTexture(TEX_EFFECT);
	// サイズ
	CObject2D::SetSize(D3DXVECTOR3(EFFECT_WIDTH, EFFECT_HEIGHT, 0.0f));

	CObject2D::Init(pos);

	// 寿命設定
	m_nLife = EFFECT_LIFE;

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// 終了
//-----------------------------------------------------------------------------------------------s
void CEffect::Uninit()
{
	CObject2D::Uninit();
}

//-----------------------------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------------------------
void CEffect::Update()
{
	// 位置の取得
	D3DXVECTOR3 pos = CObject2D::GetPosition();

	// サイズを取得
	D3DXVECTOR3 size = CObject2D::GetSize();

	// 移動量の計算
	m_move.x = sinf(m_fAngle) * EFFECT_SPEED;
	m_move.y = cosf(m_fAngle) * EFFECT_SPEED;

	// 移動量の加算
	pos += m_move;

	// サイズを小さくする
	size -= m_size;

	// 寿命を減らす
	m_nLife--;

	if (m_nLife == 0)
	{// 寿命が0だったら
		// 終了する
		Uninit();
	}
	else
	{
		// 位置の更新
		CObject2D::SetPosition(pos);
		CObject2D::SetSize(size);
		CObject2D::UpdatePos();
	}
}

//-----------------------------------------------------------------------------------------------
// 描画
//-----------------------------------------------------------------------------------------------
void CEffect::Draw()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//加算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CObject2D::Draw();

	//設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//-----------------------------------------------------------------------------------------------
// サイズの設定
//-----------------------------------------------------------------------------------------------
void CEffect::SetSizeEf(D3DXVECTOR3 size)
{
	m_size = size;
}

//-----------------------------------------------------------------------------------------------
// 角度の設定
//-----------------------------------------------------------------------------------------------
void CEffect::SetAngle(float fAngle)
{
	m_fAngle = fAngle;
}

//-----------------------------------------------------------------------------------------------
// 寿命の設定
//-----------------------------------------------------------------------------------------------
void CEffect::SetLife(int nLife)
{
	m_nLife = nLife;
}