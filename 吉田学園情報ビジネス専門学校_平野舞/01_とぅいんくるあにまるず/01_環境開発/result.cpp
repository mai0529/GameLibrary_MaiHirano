//---------------------------------------------------------------------------------
//
// リザルト処理[result.cpp]
// Author : 平野舞
//
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// インクルードファイル
//---------------------------------------------------------------------------------
#include "result.h"				// リザルト
#include "application.h"		// アプリケーション
#include "VirtualController.h"	// 仮想コントローラー
#include "ResourceManager.h"	// リソースマネージャー
#include "bg.h"					// 背景
#include "witchResults.h"		// 結果表示
#include "fade.h"				// フェード
#include "sound.h"				// 音
#include "TextureFileName.h"	// 画像のファイル名

//---------------------------------------------------------------------------------
// テクスチャ名
//---------------------------------------------------------------------------------
char* CResult::m_cFileName[] =
{
	// 背景
	TEX_BG_RESULT,
	// WIN
	TEX_RESULT_WIN,
	// LOSE
	TEX_RESULT_LOST,
	// 1P勝ち
	TEX_RESULT_1P_WIN,
	// 1P負け
	TEX_RESULT_1P_LOSE,
	// 2P勝ち
	TEX_RESULT_2P_WIN,
	// 2P負け
	TEX_RESULT_2P_LOSE,
	nullptr
};

//-----------------------------------------------------------------------------------------------
// 定数宣言
//-----------------------------------------------------------------------------------------------
// 幅
static const float RESULT_WIDTH = 200.0f;
// 高さ
static const float RESULT_HEIGHT = 200.0f;

//---------------------------------------------------------------------------------
// 静的メンバ変数宣言
//---------------------------------------------------------------------------------
// タイトルのポインタ
CResult* CResult::m_Instance = nullptr;

//---------------------------------------------------------------------------------
//	コンストラクタ
//---------------------------------------------------------------------------------
CResult::CResult()
{
	
}

//---------------------------------------------------------------------------------
//	デストラクタ
//---------------------------------------------------------------------------------
CResult::~CResult()
{

}

//---------------------------------------------------------------------------------
// インスタンスの生成
//---------------------------------------------------------------------------------
void CResult::CreateInstance()
{
	if (m_Instance == nullptr)
	{// nullptrだったら
	 // メモリの生成
		m_Instance = new CResult;
	}
}

//---------------------------------------------------------------------------------
// インスタンスの取得
//---------------------------------------------------------------------------------
CResult* CResult::GetInstance()
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
HRESULT CResult::Init()
{
	// 生成
	// リソースマネージャーのインスタンスを生成
	CResourceManager::CreateInstance();
	// テクスチャの読み込み
	CResourceManager::GetInstance()->LoadTexture(m_cFileName);

	// 背景
	CBg::Create();

	// 結果表示
	CWitchResult::GetInstance()->Init(D3DXVECTOR3(400.0f,350.0f,0.0f));

	// 音の再生
	CSound::GetInstace()->Play(CSound::SOUND_LABEL_RESULT);

	return S_OK;
}

//---------------------------------------------------------------------------------
//	終了
//---------------------------------------------------------------------------------
void CResult::Uninit()
{
	// 音の停止
	CSound::GetInstace()->Stop();

	if (m_Instance != nullptr)
	{// nullptrではなかったら
		 // 親を削除
		CObject::ReleseParent(CObject::OBJECT_PARENT_RESULT);

		// 結果表示
		CWitchResult::GetInstance()->Uninit();

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
void CResult::Update()
{
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