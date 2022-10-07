//---------------------------------------------------------------------------------
//
// アプリケーションの処理[application.cpp]
// Author : 平野舞
//
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// インクルードファイル
//---------------------------------------------------------------------------------
#include <stdio.h>				// 外部ファイル読み込み用
#include "witchResults.h"		// 結果表示
#include "application.h"		// アプリケーション
#include "renderer.h"			// レンダリング
#include "sound.h"				// 音
#include "VirtualController.h"	// 仮想コントローラー
#include "title.h"				// タイトル
#include "game.h"				// ゲーム
#include "result.h"				// リザルト
#include "fade.h"				// フェード
#include "tutorial.h"			// チュートリアル

//---------------------------------------------------------------------------------
// 静的メンバ変数宣言
//---------------------------------------------------------------------------------
// レンダリングポインタ
CRenderer* CApplication::m_pRenderer = nullptr;
// モード
CApplication::MODE CApplication::m_mode = MODE_TITLE;

//---------------------------------------------------------------------------------
//	コンストラクタ
//---------------------------------------------------------------------------------
CApplication::CApplication()
{

}

//---------------------------------------------------------------------------------
//	デストラクタ
//---------------------------------------------------------------------------------
CApplication::~CApplication()
{

}

//---------------------------------------------------------------------------------
//	初期化
//---------------------------------------------------------------------------------
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// 仮想コントローラー
	CVController::CreateInstance();
	CVController::GetInstance()->Init(hInstance, hWnd);

	// 音
	CSound::Create();
	CSound::GetInstace()->Init(hWnd);

	// レンダリングのメモリを生成する
	m_pRenderer = new CRenderer;

	if (m_pRenderer == nullptr)
	{// nullptrだったら
		return -1;
	}

	// レンダリングの初期化
	m_pRenderer->Init(hWnd, bWindow);

	// モード設定
	SetMode(m_mode);

	return S_OK;
}

//---------------------------------------------------------------------------------
//	終了
//---------------------------------------------------------------------------------
void CApplication::Uninit()
{
	// タイトル
	CTitle::GetInstance()->Uninit();

	// ゲーム
	CGame::GetInstance()->Uninit();

	// リザルト
	CResult::GetInstance()->Uninit();

	// 音
	CSound::GetInstace()->Uninit();

	// 仮想コントローラー
	CVController::GetInstance()->Uninit();

	// レンダリング
	if (m_pRenderer != nullptr)
	{// nullptrではなかったら
		// 終了
		m_pRenderer->Uninit();

		// メモリを破棄
		delete m_pRenderer;

		// nullptrに戻す
		m_pRenderer = nullptr;
	}
}

//---------------------------------------------------------------------------------
//	更新
//---------------------------------------------------------------------------------
void CApplication::Update()
{
	// 仮想コントローラー
	CVController::GetInstance()->Update();

	// 各画面の更新
	switch (m_mode)
	{
		// タイトル
	case MODE_TITLE:
		CTitle::GetInstance()->Update();
		break;
		// チュートリアル
	case MODE_TUTORIAL:
		CTutorial::GetInstance()->Update();
		break;
		// ゲーム
	case MODE_GAME:
		CGame::GetInstance()->Update();
		break;
		// リザルト
	case MODE_RESULT:
		CResult::GetInstance()->Update();
		break;
		// その他
	default:
		break;
	}

	if (m_pRenderer != nullptr)
	{// レンダリング
		m_pRenderer->Update();
	}
}

//---------------------------------------------------------------------------------
//	描画
//---------------------------------------------------------------------------------
void CApplication::Draw()
{
	if (m_pRenderer != nullptr)
	{// レンダリング
		m_pRenderer->Draw();
	}
}

//---------------------------------------------------------------------------------
//	レンダリングポインタの取得
//---------------------------------------------------------------------------------
CRenderer* CApplication::GetRenderer()
{
	return m_pRenderer;
}

//---------------------------------------------------------------------------------
// モードの設定
//---------------------------------------------------------------------------------
void CApplication::SetMode(MODE mode)
{
	// 各画面の終了
	switch (m_mode)
	{
		// タイトル
	case MODE_TITLE:
		CTitle::GetInstance()->Uninit();
		break;
		// チュートリアル
	case MODE_TUTORIAL:
		CTutorial::GetInstance()->Uninit();
		break;
		// ゲーム
	case MODE_GAME:
		// 結果表示のインスタンスを生成
		CWitchResult::CreateInstance();
		CWitchResult::GetInstance()->SetWinner();

		CGame::GetInstance()->Uninit();
		break;
		// リザルト
	case MODE_RESULT:
		CResult::GetInstance()->Uninit();
		break;
		// その他
	default:
		break;
	}

	m_mode = mode;

	// 各画面の開始
	switch (mode)
	{
		// タイトル
	case MODE_TITLE:
		// インスタンスを生成する
		CTitle::CreateInstance();

		// 初期化
		CTitle::GetInstance()->Init();
		break;
		// チュートリアル
	case MODE_TUTORIAL:
		// インスタンスを生成
		CTitle::CreateInstance();

		// 初期化
		CTutorial::GetInstance()->Init();
		break;
		// ゲーム
	case MODE_GAME:
		//　インスタンスを生成する
		CGame::CreateInstance();

		// 初期化
		CGame::GetInstance()->Init();
		break;
		// リザルト
	case MODE_RESULT:
		// インスタンスを生成
		CResult::CreateInstance();
		// 初期化
		CResult::GetInstance()->Init();
		break;
		// その他
	default:
		break;
	}
}

//---------------------------------------------------------------------------------
// モードの取得
//---------------------------------------------------------------------------------
CApplication::MODE CApplication::GetMode()
{
	return m_mode;
}