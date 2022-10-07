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
#include "VirtualController.h"	// 仮想コントローラー
#include "ResourceManager.h"	// リソースマネージャー
#include "bg.h"					// 背景
#include "fade.h"				// フェード
#include "sound.h"				// 音
#include "TextureFileName.h"	// 画像のファイル名

//---------------------------------------------------------------------------------
// テクスチャ名
//---------------------------------------------------------------------------------
char* CTutorial::m_cFileName[] =
{
	// 1枚目の背景
	TEX_BG_TUTORIAL_ONE,
	// 2枚目の背景
	TEX_BG_TOTORIAL_SECOND,
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
	// 生成
	// リソースマネージャーのインスタンスを生成
	CResourceManager::CreateInstance();
	// テクスチャの読み込み
	CResourceManager::GetInstance()->LoadTexture(m_cFileName);

	// 背景
	m_pBg = CBg::Create();

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
		// 親の削除
		CObject::ReleseParent(CObject::OBJECT_PARENT_TUTORIAL);

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
	if ((CVController::GetInstance()->GetTrigger(MULTI_TYPE_ONE - 1, CVController::VIRTUAL_KEY_LEFT)
		|| CVController::GetInstance()->GetTrigger(MULTI_TYPE_SECOND - 1, CVController::VIRTUAL_KEY_LEFT)))
	{// 左
		m_pBg->SetPage(CBg::TUTORIAL_PAGE_ONE);
	}
	else if (CVController::GetInstance()->GetTrigger(MULTI_TYPE_ONE - 1, CVController::VIRTUAL_KEY_RIGHT)
		|| CVController::GetInstance()->GetTrigger(MULTI_TYPE_SECOND - 1, CVController::VIRTUAL_KEY_RIGHT))
	{// 右
		m_pBg->SetPage(CBg::TUTORIAL_PAGE_SECOND);
	}

	if (CVController::GetInstance()->GetTrigger(MULTI_TYPE_ONE - 1, CVController::VIRTUAL_KEY_START)
		|| CVController::GetInstance()->GetTrigger(MULTI_TYPE_ONE - 1, CVController::VIRTUAL_KEY_A))
	{// ENETERキー、STARTボタンが押されたら
	 // ゲーム画面に移行
		CApplication::SetMode(CApplication::MODE_TITLE);

		// 音の再生
			CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_DECISION_CAT);
			CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_DECISION_DOG);
	}
}