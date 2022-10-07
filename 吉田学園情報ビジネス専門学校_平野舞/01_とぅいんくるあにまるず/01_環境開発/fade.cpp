//---------------------------------------------------------------------------------
//
// フェード処理[fade.cpp]
// Author : 平野舞
//
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// インクルードファイル
//---------------------------------------------------------------------------------
#include "fade.h"		// フェード
#include "object2D.h"	// オブジェクト2D
#include "renderer.h"	// レンダラー

//---------------------------------------------------------------------------------
// 定数宣言
//---------------------------------------------------------------------------------
// α値の変動
static const float FADE_COL_A = 0.05f;

//---------------------------------------------------------------------------------
// 静的メンバ変数宣言
//---------------------------------------------------------------------------------
// フェードのポインタ
CFade* CFade::m_Instance = nullptr;
// オブジェクトのポインタ
CObject2D* CFade::m_pObject2D = nullptr;

//---------------------------------------------------------------------------------
//	コンストラクタ
//---------------------------------------------------------------------------------
CFade::CFade()
	:m_fade(FADE_NONE), m_modeNext(CApplication::MODE_TITLE)
{

}

//---------------------------------------------------------------------------------
//	デストラクタ
//---------------------------------------------------------------------------------
CFade::~CFade()
{

}

//---------------------------------------------------------------------------------
// インスタンスの生成
//---------------------------------------------------------------------------------
void CFade::CreateInstance()
{
	if (m_Instance == nullptr)
	{// nullptrだったら
	 // メモリの生成
		m_Instance = new CFade;
	}
}

//---------------------------------------------------------------------------------
// インスタンスの取得
//---------------------------------------------------------------------------------
CFade* CFade::GetInstance()
{
	if (m_Instance != nullptr)
	{// nullptrではなかったら
		return m_Instance;
	}

	return nullptr;
}

//---------------------------------------------------------------------------------
//	初期化
//
// CApplication::MODE modeNext → 次に設定したい画面
//---------------------------------------------------------------------------------
void CFade::Init(CApplication::MODE modeNext)
{
	// フェードインしている状態にする
	m_fade = FADE_IN;
	// 次のモードを設定
	m_modeNext = modeNext;

	// ポリゴンの設定
	m_pObject2D = CObject2D::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2.0f, CRenderer::SCREEN_HEIGHT / 2.0f, 0.0f), 
		D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT, 0.0f));
	m_pObject2D->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	// モードの設定
	CApplication::SetMode(m_modeNext);
}

//---------------------------------------------------------------------------------
//	終了
//---------------------------------------------------------------------------------
void CFade::Uninit()
{
	if (m_pObject2D != nullptr)
	{
		// 終了
		m_pObject2D->Uninit();

		// nullptrにする
		m_pObject2D = nullptr;
	}
}

//---------------------------------------------------------------------------------
//	更新
//---------------------------------------------------------------------------------
void CFade::Update()
{
	if (m_fade != FADE_NONE)
	{// フェードしていたら
		// カラーの取得
		D3DXCOLOR col = m_pObject2D->GetColor();

		if (m_fade == FADE_IN)
		{// フェードインしていたら
			// ポリゴンを透明にしていく
			col.a -= FADE_COL_A;

			if (col.a <= 0.0f)
			{// a値が0以下になったら
				// a値を0にする
				col.a = 0.0f;

				// フェードしていない状態にする
				m_fade = FADE_NONE;
			}
		}
		else if (m_fade == FADE_OUT)
		{// フェードアウトしていたら
			// ポリゴンを不透明にしていく
			col.a += FADE_COL_A;

			if (col.a >= 1.0f)
			{// a値が1以上になったら
				// a値を1にする
				col.a = 1.0f;

				// フェードイン状態にする
				m_fade = FADE_IN;

				// モードの設定
				CApplication::SetMode(m_modeNext);
			}
		}

		// 色の設定
		m_pObject2D->SetColor(col);
	}
}

//---------------------------------------------------------------------------------
// 設定
//
// CApplication::MODE modeNext → 次に設定したい画面
//---------------------------------------------------------------------------------
void CFade::SetFade(CApplication::MODE modeNext)
{
	// フェードアウトする
	m_fade = FADE_OUT;

	// 次のモードを設定
	m_modeNext = modeNext;

	// 色の設定
	m_pObject2D->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
}

//---------------------------------------------------------------------------------
// 情報の取得
//---------------------------------------------------------------------------------
CFade::FADE CFade::GetFade()
{
	return m_fade;
}