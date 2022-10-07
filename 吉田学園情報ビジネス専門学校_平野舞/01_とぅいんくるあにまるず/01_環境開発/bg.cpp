//-----------------------------------------------------------------------------------------------
//
// 背景の処理[bg.cpp]
// Author : 平野舞
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// インクルードファイル
//-----------------------------------------------------------------------------------------------
#include "bg.h"					// 背景
#include "object2D.h"			// 2Dオブジェクト
#include "application.h"		// アプリケーション
#include "renderer.h"			// レンダリング
#include "VirtualController.h"	// 仮想コントローラー
#include "TextureFileName.h"	// 画像のファイル名

//-----------------------------------------------------------------------------------------------
// 定数宣言
//-----------------------------------------------------------------------------------------------
// 背景の移動スピード
static const float BG_SPPED = -0.001f;

//-----------------------------------------------------------------------------------------------
//　コンストラクタ
//-----------------------------------------------------------------------------------------------
CBg::CBg()
	:m_fTexV(0), m_page(TUTORIAL_PAGE_NONE)
{
	for (int nCntBg = 0; nCntBg < MAX_TEXTURE; nCntBg++)
	{
		m_paObject2D[nCntBg] = nullptr;
	}
}

//-----------------------------------------------------------------------------------------------
//　デストラクタ
//-----------------------------------------------------------------------------------------------
CBg::~CBg()
{

}

//-----------------------------------------------------------------------------------------------
// 生成
//-----------------------------------------------------------------------------------------------
CBg* CBg::Create()
{
	// ポインタを宣言
	CBg* pBG = new CBg;

	if (pBG != nullptr)
	{// nullptrではなかったら
		// 初期化する
		pBG->Init(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2.0f, CRenderer::SCREEN_HEIGHT / 2.0f, 0.0f));
	}

	return pBG;
}

//-----------------------------------------------------------------------------------------------
//　初期化
//-----------------------------------------------------------------------------------------------
HRESULT CBg::Init(const D3DXVECTOR3& pos)
{
	// オブジェクト2Dを生成
	m_paObject2D[0] = CObject2D::Create(pos, D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT, 0.0f));

	// テクスチャ、親の設定
	switch (CApplication::GetMode())
	{
		// タイトル
	case CApplication::MODE_TITLE:
		m_paObject2D[0]->LoadTexture(TEX_BG_TITLE);
		SetObjectParent(CObject::OBJECT_PARENT_TITLE);
		break;
		// チュートリアル
	case CApplication::MODE_TUTORIAL:
		m_paObject2D[0]->LoadTexture(TEX_BG_TUTORIAL_ONE);
		// オブジェクト2Dを生成
		m_paObject2D[1] = CObject2D::Create(pos, D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT, 0.0f));
		m_paObject2D[1]->LoadTexture(TEX_BG_TOTORIAL_SECOND);
		SetObjectParent(CObject::OBJECT_PARENT_TUTORIAL);
		// 1ページ目を表示
		m_page = TUTORIAL_PAGE_ONE;
		break;
		// ゲーム
	case CApplication::MODE_GAME:
		m_paObject2D[0]->LoadTexture(TEX_BG_GAME);
		SetObjectParent(CObject::OBJECT_PARENT_GAME);
		break;
		// リザルト
	case CApplication::MODE_RESULT:
		m_paObject2D[0]->LoadTexture(TEX_BG_RESULT);
		SetObjectParent(CObject::OBJECT_PARENT_RESULT);
		break;
		// その他
	default:
		break;
	}

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
//　終了
//-----------------------------------------------------------------------------------------------
void CBg::Uninit()
{
	for (int nCntBg = 0; nCntBg < MAX_TEXTURE; nCntBg++)
	{
		if (m_paObject2D[nCntBg] != nullptr)
		{// nullptrではなかったら
			// 終了する
			m_paObject2D[nCntBg]->Uninit();
		}
	}
}

//-----------------------------------------------------------------------------------------------
//　更新
//-----------------------------------------------------------------------------------------------
void CBg::Update()
{
	if (GetObjectParent() == CObject::OBJECT_PARENT_TUTORIAL)
	{// チュートリアルモードだったら
		State();
	}

	if (GetObjectParent() == CObject::OBJECT_PARENT_GAME)
	{// ゲームモードだったら
		// U座標の位置を加算
		m_fTexV += BG_SPPED;

		// 座標の更新
		m_paObject2D[0]->SetTexPos(0.0f, m_fTexV);
	}
}

//-----------------------------------------------------------------------------------------------
//　描画
//-----------------------------------------------------------------------------------------------
void CBg::Draw()
{

}

//-----------------------------------------------------------------------------------------------
// ページの設定
//-----------------------------------------------------------------------------------------------
void CBg::SetPage(TUTORIAL_PAGE page)
{
	m_page = page;
}

//-----------------------------------------------------------------------------------------------
// 状態
//-----------------------------------------------------------------------------------------------
void CBg::State()
{
	switch (m_page)
	{
		// 1ページ目
	case TUTORIAL_PAGE_ONE:
		m_paObject2D[0]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_paObject2D[1]->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		break;
		// 2ページ目
	case TUTORIAL_PAGE_SECOND:
		m_paObject2D[0]->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		m_paObject2D[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;
		// その他
	default:
		break;
	}
}