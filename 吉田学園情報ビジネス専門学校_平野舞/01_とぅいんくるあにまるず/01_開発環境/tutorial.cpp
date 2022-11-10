//---------------------------------------------------------------------------------
//
// チュートリアル処理[tutorial.cpp]
// Author : 平野舞
//
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// インクルードファイル
//---------------------------------------------------------------------------------
#include "tutorial.h"			// チュートリアル
#include "application.h"		// アプリケーション
#include "renderer.h"			// レンダリング
#include "VirtualController.h"	// 仮想コントローラー
#include "ResourceManager.h"	// リソースマネージャー
#include "bg.h"					// 背景
#include "fade.h"				// フェード
#include "sound.h"				// 音
#include "TextureFileName.h"	// 画像のファイル名
#include "object2D.h"			// オブジェクト

//---------------------------------------------------------------------------------
// 定数宣言
//---------------------------------------------------------------------------------
// 矢印の画像幅
static const float ARROW_WIDTH = 90.0f;
// 矢印の画像高さ
static const float ARROW_HEIGHT = 300.0f;
// 左矢印の位置(x軸)
static const float ARROW_LEFT_POS_X = 40.0f;
// 右矢印の位置(x軸)
static const float ARROW_RIGHT_POS_X = 1240.0f;
// 矢印の位置(y軸)
static const float ARROW_POS_Y = CRenderer::SCREEN_HEIGHT / 2.0f;

//---------------------------------------------------------------------------------
// テクスチャ名
//---------------------------------------------------------------------------------
char* CTutorial::m_cFileName[] =
{
	// 1枚目の背景
	TEX_BG_TUTORIAL_ONE,
	// 2枚目の背景
	TEX_BG_TOTORIAL_SECOND,
	// 矢印-右-
	TEX_TUTORIAL_ARROW_RIGHT,
	// 矢印-左-
	TEX_TUTORIAL_ARROW_LEFT,
	nullptr
};

//---------------------------------------------------------------------------------
// 静的メンバ変数宣言
//---------------------------------------------------------------------------------
// タイトルのポインタ
CTutorial* CTutorial::m_Instance = nullptr;
// 背景のポインタ
CBg* CTutorial::m_pBg = nullptr;

//---------------------------------------------------------------------------------
//	コンストラクタ
//---------------------------------------------------------------------------------
CTutorial::CTutorial()
{

}

//---------------------------------------------------------------------------------
//	デストラクタ
//---------------------------------------------------------------------------------
CTutorial::~CTutorial()
{

}

//---------------------------------------------------------------------------------
// インスタンスの生成
//---------------------------------------------------------------------------------
void CTutorial::CreateInstance()
{
	if (m_Instance == nullptr)
	{// nullptrだったら
	 // メモリの生成
		m_Instance = new CTutorial;
	}
}

//---------------------------------------------------------------------------------
// インスタンスの取得
//---------------------------------------------------------------------------------
CTutorial* CTutorial::GetInstance()
{
	if (m_Instance != nullptr)
	{// nullptrではなかったら
		return m_Instance;
	}

	return nullptr;
}

//---------------------------------------------------------------------------------
//	初期化
//---------------------------------------------------------------------------------
HRESULT CTutorial::Init()
{
	// ポーズ中ではない
	CObject::SetPause(false);

	// 生成
	// リソースマネージャーのインスタンスを生成
	CResourceManager::CreateInstance();
	// テクスチャの読み込み
	CResourceManager::GetInstance()->LoadTexture(m_cFileName);

	// 背景
	m_pBg = CBg::Create(CBg::ETYPE_BG_TUTORIAL);

	// 矢印の表示
	CObject2D::Create(TEX_TUTORIAL_ARROW_RIGHT, D3DXVECTOR3(ARROW_RIGHT_POS_X, ARROW_POS_Y, 0.0f), D3DXVECTOR3(ARROW_WIDTH, ARROW_HEIGHT, 0.0f));
	CObject2D::Create(TEX_TUTORIAL_ARROW_LEFT,D3DXVECTOR3(ARROW_LEFT_POS_X, ARROW_POS_Y,0.0f), D3DXVECTOR3(ARROW_WIDTH, ARROW_HEIGHT, 0.0f));

	// 音の再生
	CSound::GetInstace()->Play(CSound::SOUND_LABEL_TUTORIAL);

	return S_OK;
}

//---------------------------------------------------------------------------------
//	終了
//---------------------------------------------------------------------------------
void CTutorial::Uninit()
{
	// 音の停止
	CSound::GetInstace()->Stop();

	if (m_Instance != nullptr)
	{// nullptrではなかったら
	 // オブジェクトの破棄
		CObject::ReleaseAll();

		// テクスチャの破棄
		CResourceManager::GetInstance()->AllUnloadTexture();

		// メモリを破棄する
		delete m_Instance;

		// nullptrにする
		m_Instance = nullptr;
	}
}

//---------------------------------------------------------------------------------
//	更新
//---------------------------------------------------------------------------------
void CTutorial::Update()
{
	if ((CVController::GetInstance()->GetTrigger(0, CVController::VIRTUAL_KEY_LEFT)
		|| CVController::GetInstance()->GetTrigger(0, CVController::VIRTUAL_KEY_LEFT)))
	{// 左
		m_pBg->SetPage(CBg::TUTORIAL_PAGE_ONE);
	}
	else if (CVController::GetInstance()->GetTrigger(0, CVController::VIRTUAL_KEY_RIGHT)
		|| CVController::GetInstance()->GetTrigger(0, CVController::VIRTUAL_KEY_RIGHT))
	{// 右
		m_pBg->SetPage(CBg::TUTORIAL_PAGE_SECOND);
	}

	if (CFade::GetInstance()->GetFade() == CFade::FADE_NONE
		&& (CVController::GetInstance()->GetTrigger(0, CVController::VIRTUAL_KEY_START)
			|| CVController::GetInstance()->GetTrigger(0, CVController::VIRTUAL_KEY_A)))
	{// ENETERキー、STARTボタンが押されたら
		 // ゲーム画面に移行
		CFade::GetInstance()->SetFade(CApplication::MODE_TITLE);

		// 音の再生
		CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_DECISION_CAT);
		CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_DECISION_DOG);
		return;
	}
}