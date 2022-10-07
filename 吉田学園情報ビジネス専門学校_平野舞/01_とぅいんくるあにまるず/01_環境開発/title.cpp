//---------------------------------------------------------------------------------
//
// タイトル処理[title.cpp]
// Author : 平野舞
//
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// インクルードファイル
//---------------------------------------------------------------------------------
#include "title.h"				// タイトル
#include "application.h"		// アプリケーション
#include "VirtualController.h"	// 仮想コントローラー
#include "ResourceManager.h"	// リソースマネージャー
#include "bg.h"					// 背景
#include "fade.h"				// フェード
#include "sound.h"				// 音
#include "menu.h"				// メニュー
#include "TextureFileName.h"	// 画像のファイル名

//---------------------------------------------------------------------------------
// テクスチャ名
//---------------------------------------------------------------------------------
char* CTitle::m_cFileName[] =
{
	// 背景
	TEX_BG_TITLE,
	// スタートメニュー
	TEX_MENU_START,
	// チュートリアルメニュー
	TEX_MENU_TUTORIAL,
	nullptr
};

//---------------------------------------------------------------------------------
// 静的メンバ変数宣言
//---------------------------------------------------------------------------------
// タイトルのポインタ
CTitle* CTitle::m_Instance = nullptr;
// メニュー
CMenu* CTitle::m_pMenu[MAX_MENU_SELECT] = { nullptr };

//---------------------------------------------------------------------------------
//	コンストラクタ
//---------------------------------------------------------------------------------
CTitle::CTitle()
	:m_select(TITLE_SELECT_NONE)
{

}

//---------------------------------------------------------------------------------
//	デストラクタ
//---------------------------------------------------------------------------------
CTitle::~CTitle()
{

}

//---------------------------------------------------------------------------------
// インスタンスの生成
//---------------------------------------------------------------------------------
void CTitle::CreateInstance()
{
	if (m_Instance == nullptr)
	{// nullptrだったら
	 // メモリの生成
		m_Instance = new CTitle;
	}
}

//---------------------------------------------------------------------------------
// インスタンスの取得
//---------------------------------------------------------------------------------
CTitle* CTitle::GetInstance()
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
HRESULT CTitle::Init()
{
	// ゲーム選択
	m_select = TITLE_SELECT_GAME;

	// 生成
	// リソースマネージャーのインスタンスを生成
	CResourceManager::CreateInstance();
	// テクスチャの読み込み
	CResourceManager::GetInstance()->LoadTexture(m_cFileName);

	// 背景
	CBg::Create();

	// タイトルメニュー選択
	m_pMenu[0] = CMenu::Create(D3DXVECTOR3(650.0f,520.0f,0.0f));
	m_pMenu[0]->LoadTexture(TEX_MENU_START);

	// チュートリアルメニュー選択
	m_pMenu[1] = CMenu::Create(D3DXVECTOR3(650.0f, 640.0f, 0.0f));
	m_pMenu[1]->LoadTexture(TEX_MENU_TUTORIAL);

	switch (m_select)
	{
		// ゲーム
	case TITLE_SELECT_GAME:
		m_pMenu[0]->SetState(CMenu::MENU_STATE_DECISION);
		m_pMenu[1]->SetState(CMenu::MENU_STATE_NO_DECISION);
		break;
		// チュートリアル
	case TITLE_SELECT_TUTORIAL:
		m_pMenu[0]->SetState(CMenu::MENU_STATE_NO_DECISION);
		m_pMenu[1]->SetState(CMenu::MENU_STATE_DECISION);
		break;
		// その他
	default:
		break;
	}

	// 音の再生
	CSound::GetInstace()->Play(CSound::SOUND_LABEL_TITLE);

	return S_OK;
}

//---------------------------------------------------------------------------------
//	終了
//---------------------------------------------------------------------------------
void CTitle::Uninit()
{
	// 音の停止
	CSound::GetInstace()->Stop();

	if (m_Instance != nullptr)
	{// nullptrではなかったら
		// 親を削除
		CObject::ReleseParent(CObject::OBJECT_PARENT_TITLE);

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
void CTitle::Update()
{
	if (CVController::GetInstance()->GetTrigger(MULTI_TYPE_ONE - 1, CVController::VIRTUAL_KEY_DOWN)
		|| CVController::GetInstance()->GetTrigger(MULTI_TYPE_SECOND - 1, CVController::VIRTUAL_KEY_DOWN))
	{// 下
		if (m_select == TITLE_SELECT_GAME)
		{// ゲームが選択されていたら
			// チュートリアルにする
			m_select = TITLE_SELECT_TUTORIAL;
			// 状態を変更
			m_pMenu[0]->SetState(CMenu::MENU_STATE_NO_DECISION);
			m_pMenu[1]->SetState(CMenu::MENU_STATE_DECISION);
		}
	}
	else if (CVController::GetInstance()->GetTrigger(MULTI_TYPE_ONE - 1, CVController::VIRTUAL_KEY_UP)
		|| CVController::GetInstance()->GetTrigger(MULTI_TYPE_SECOND - 1, CVController::VIRTUAL_KEY_UP))
	{// 上
		if (m_select == TITLE_SELECT_TUTORIAL)
		{// ゲームが選択されていたら
			// ゲームにする
			m_select = TITLE_SELECT_GAME;
			// 状態を変更
			m_pMenu[0]->SetState(CMenu::MENU_STATE_DECISION);
			m_pMenu[1]->SetState(CMenu::MENU_STATE_NO_DECISION);
		}
	}

	if (m_select == TITLE_SELECT_GAME)
	{// ゲームが選択されていたら
		if (CVController::GetInstance()->GetTrigger(MULTI_TYPE_ONE - 1, CVController::VIRTUAL_KEY_START)
			|| CVController::GetInstance()->GetTrigger(MULTI_TYPE_ONE - 1, CVController::VIRTUAL_KEY_A))
		{// ENETERキー,STARTボタン 、Aボタンが押されたら
		 // ゲーム画面に移行
			CApplication::SetMode(CApplication::MODE_GAME);

			// 音の再生
			CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_DECISION_CAT);
			CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_DECISION_DOG);
		}
	}
	else if (m_select == TITLE_SELECT_TUTORIAL)
	{// チュートリアルが選択されていたら
		if (CVController::GetInstance()->GetTrigger(MULTI_TYPE_ONE - 1, CVController::VIRTUAL_KEY_START)
			|| CVController::GetInstance()->GetTrigger(MULTI_TYPE_ONE - 1, CVController::VIRTUAL_KEY_A))
		{// ENETERキー,STARTボタン、Aボタンが押されたら
		 // チュートリアル画面に移行
			CApplication::SetMode(CApplication::MODE_TUTORIAL);

			// 音の再生
			CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_DECISION_CAT);
			CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_DECISION_DOG);

		}
	}
}