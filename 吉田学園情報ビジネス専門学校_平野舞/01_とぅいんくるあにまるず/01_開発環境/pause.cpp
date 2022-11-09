//---------------------------------------------------------------------------------
//
// ポーズの処理[pause.cpp]
// Author : 平野舞
//
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// インクルードファイル
//---------------------------------------------------------------------------------
#include "pause.h"				// ポーズ
#include "application.h"		// アプリケーション
#include"renderer.h"			// レンダリング
#include "object2D.h"			// オブジェクト2D
#include "ResourceManager.h"	// リソースマネージャー
#include "TextureFileName.h"	// 画像のファイル名
#include "VirtualController.h"	// 仮想コントローラー
#include "fade.h"				// フェード
#include "sound.h"				// 音
#include "menu.h"				// メニュー
#include "game.h"				// ゲーム
#include "bg.h"					// 背景

//---------------------------------------------------------------------------------
// マクロ定義
//---------------------------------------------------------------------------------
// コントローラ
#define PLAYER_CONTROLLER		(0)

//---------------------------------------------------------------------------------
// 定数宣言
//---------------------------------------------------------------------------------
// メニューの幅
static const float WIDTH_MENU = 600.0f;
// メニューの高さ
static const float HEIGHT_MENU = 200.0f;
// x軸の位置
static const float POS_X_MENU_SELECT = (float)CRenderer::SCREEN_WIDTH / 2.0f;
// y軸の位置
static const float POS_Y_MENU_SELECT = (float)CRenderer::SCREEN_HEIGHT / 2.0f - 90.0f;
// 選択の間隔
static const float POS_DIS_MENU_SELECT = 180.0f;

//---------------------------------------------------------------------------------
// テクスチャ名
//---------------------------------------------------------------------------------
char* CPause::m_cFileName[] =
{
	// 背景
	TEX_BG_PAUSE,
	// ゲームを続ける
	TEX_MENU_GAME_PLAY,
	// ゲームをやり直す
	TEX_MENU_GAME_REPLAY,
	// メニューに戻る
	TEX_MENU_SELECT,
	nullptr
};

//---------------------------------------------------------------------------------
// 静的メンバ変数宣言
//---------------------------------------------------------------------------------
// タイトルクラスのポインタ
CPause* CPause::m_Instance = nullptr;
// メニューのポインタ
CMenu* CPause::m_pMenu[MAX_MENU_SELECT] = { nullptr };

//---------------------------------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------------------------------
CPause::CPause()
	:m_select(EPAUSE_SELECT_NONE)
{

}

//---------------------------------------------------------------------------------
// デストラクタ
//---------------------------------------------------------------------------------
CPause::~CPause()
{

}

//---------------------------------------------------------------------------------
// インスタンスの生成
//---------------------------------------------------------------------------------
void CPause::CreateInstance()
{
	if (m_Instance == nullptr)
	{// nullptrだったら
	 // メモリを生成
		m_Instance = new CPause;
	}
}

//---------------------------------------------------------------------------------
// インスタンスの取得
//---------------------------------------------------------------------------------
CPause* CPause::GetInstance()
{
	if (m_Instance != nullptr)
	{// nullptrではなかったら
		return m_Instance;
	}

	return nullptr;
}

//---------------------------------------------------------------------------------
// インスタンスの削除
//---------------------------------------------------------------------------------
void CPause::DeleteInstance()
{
	// メモリを破棄
	delete m_Instance;

	// nullptrにする
	m_Instance = nullptr;
}

//---------------------------------------------------------------------------------
// 初期化
//---------------------------------------------------------------------------------
HRESULT CPause::Init()
{
	// テクスチャの読み込み
	CResourceManager::GetInstance()->LoadTexture(m_cFileName);

	// 背景
	CBg::Create(CBg::ETYPE_BG_PAUSE);

	// セレクトの初期化
	m_select = EPAUSE_SELECT_GAME_PLAY;

	// メニュー
	MenuInit();

	return S_OK;
}

//---------------------------------------------------------------------------------
// 終了
//---------------------------------------------------------------------------------
void CPause::Uninit()
{
	// 親の削除
	CObject::ReleaseParent(CObject::EOBJECT_PARENT_PAUSE);
}

//---------------------------------------------------------------------------------
// 更新
//---------------------------------------------------------------------------------
void CPause::Update()
{
	// メニュー
	MenuUpdate();

	// メニューの決定
	MenuDecision();
}

//---------------------------------------------------------------------------------
// メニューの初期化
//---------------------------------------------------------------------------------
void CPause::MenuInit()
{
	// ゲームを続ける
	m_pMenu[0] = CMenu::Create(TEX_MENU_GAME_PLAY, D3DXVECTOR3(POS_X_MENU_SELECT, POS_Y_MENU_SELECT, 0.0f), D3DXVECTOR3(WIDTH_MENU, HEIGHT_MENU, 0.0f));
	// ゲームをやり直す
	m_pMenu[1] = CMenu::Create(TEX_MENU_GAME_REPLAY, D3DXVECTOR3(POS_X_MENU_SELECT, POS_Y_MENU_SELECT + POS_DIS_MENU_SELECT, 0.0f), D3DXVECTOR3(WIDTH_MENU, HEIGHT_MENU, 0.0f));
	// モード選択に戻る
	m_pMenu[2] = CMenu::Create(TEX_MENU_SELECT, D3DXVECTOR3(POS_X_MENU_SELECT, POS_Y_MENU_SELECT + (POS_DIS_MENU_SELECT * 2), 0.0f), D3DXVECTOR3(WIDTH_MENU, HEIGHT_MENU, 0.0f));

	for (int nCntMenu = 0; nCntMenu < MAX_MENU_SELECT; nCntMenu++)
	{// 親をポーズにする
		m_pMenu[nCntMenu]->SetObjectParent(CObject::EOBJECT_PARENT_PAUSE);
	}

	switch (m_select)
	{
		// ゲームに戻る
	case EPAUSE_SELECT_GAME_PLAY:
		m_pMenu[0]->SetState(CMenu::MENU_STATE_DECISION);
		m_pMenu[1]->SetState(CMenu::MENU_STATE_NO_DECISION);
		m_pMenu[2]->SetState(CMenu::MENU_STATE_NO_DECISION);
		break;
		// ゲームをやり直す
	case EPAUSE_SELECT_GAME_REPLAY:
		m_pMenu[0]->SetState(CMenu::MENU_STATE_NO_DECISION);
		m_pMenu[1]->SetState(CMenu::MENU_STATE_DECISION);
		m_pMenu[2]->SetState(CMenu::MENU_STATE_NO_DECISION);
		break;
		// 選択モードに戻る
	case EPAUSE_SELECT_MENU_RETURN:
		m_pMenu[0]->SetState(CMenu::MENU_STATE_NO_DECISION);
		m_pMenu[1]->SetState(CMenu::MENU_STATE_NO_DECISION);
		m_pMenu[2]->SetState(CMenu::MENU_STATE_DECISION);
		break;
		// その他
	default:
		break;
	}
}

//---------------------------------------------------------------------------------
// メニューの更新
//---------------------------------------------------------------------------------
void CPause::MenuUpdate()
{
	if (CVController::GetInstance()->GetTrigger(PLAYER_CONTROLLER, CVController::VIRTUAL_KEY_DOWN))
	{// ↓を押されたら
		if (m_select == EPAUSE_SELECT_GAME_PLAY)
		{// ゲームに戻るが選択されてたら
		 // ゲームをやり直すにする
			m_select = EPAUSE_SELECT_GAME_REPLAY;

			m_pMenu[0]->SetState(CMenu::MENU_STATE_NO_DECISION);
			m_pMenu[1]->SetState(CMenu::MENU_STATE_DECISION);
			m_pMenu[2]->SetState(CMenu::MENU_STATE_NO_DECISION);
		}
		else if (m_select == EPAUSE_SELECT_GAME_REPLAY)
		{// ゲームをやり直すを選択していたら
		 // 選択モードに戻るにする
			m_select = EPAUSE_SELECT_MENU_RETURN;

			m_pMenu[0]->SetState(CMenu::MENU_STATE_NO_DECISION);
			m_pMenu[1]->SetState(CMenu::MENU_STATE_NO_DECISION);
			m_pMenu[2]->SetState(CMenu::MENU_STATE_DECISION);
		}
	}
	else if (CVController::GetInstance()->GetTrigger(PLAYER_CONTROLLER, CVController::VIRTUAL_KEY_UP))
	{
		if (m_select == EPAUSE_SELECT_GAME_REPLAY)
		{// ゲームをやり直すを選択していたら
		 // ゲームを戻るにする
			m_select = EPAUSE_SELECT_GAME_PLAY;

			m_pMenu[0]->SetState(CMenu::MENU_STATE_DECISION);
			m_pMenu[1]->SetState(CMenu::MENU_STATE_NO_DECISION);
			m_pMenu[2]->SetState(CMenu::MENU_STATE_NO_DECISION);
		}
		else if (m_select == EPAUSE_SELECT_MENU_RETURN)
		{// 選択モードに戻るを選択していたら
		 // ゲームをやり直すにする
			m_select = EPAUSE_SELECT_GAME_REPLAY;

			m_pMenu[0]->SetState(CMenu::MENU_STATE_NO_DECISION);
			m_pMenu[1]->SetState(CMenu::MENU_STATE_DECISION);
			m_pMenu[2]->SetState(CMenu::MENU_STATE_NO_DECISION);
		}
	}
}

//---------------------------------------------------------------------------------
// メニューの決定
//---------------------------------------------------------------------------------
void CPause::MenuDecision()
{
	if (CFade::GetInstance()->GetFade() == CFade::FADE_NONE &&
		CVController::GetInstance()->GetTrigger(PLAYER_CONTROLLER, CVController::VIRTUAL_KEY_START))
	{
		if (m_select == EPAUSE_SELECT_GAME_PLAY)
		{//ポーズ中ではない
			CObject::SetPause(false);
			// 終了する
			Uninit();
		}
		else if (m_select == EPAUSE_SELECT_GAME_REPLAY)
		{// ゲームをやり直すが選択されてたら
		 // 終了する
			Uninit();
			// ゲームをやり直す
			CFade::GetInstance()->SetFade(CApplication::MODE_GAME);
		}
		else if (m_select == EPAUSE_SELECT_MENU_RETURN)
		{// 選択モードに戻るが選択されてたら
		 // 終了する
			Uninit();
			// セレクトモードに戻る
			CFade::GetInstance()->SetFade(CApplication::MODE_TITLE);
		}
	}
}