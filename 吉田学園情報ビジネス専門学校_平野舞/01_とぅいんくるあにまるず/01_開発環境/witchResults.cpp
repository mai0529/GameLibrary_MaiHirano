//---------------------------------------------------------------------------------
//
// 結果表示処理[witchResults.cpp]
// Author : 平野舞
//
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// インクルードファイル
//---------------------------------------------------------------------------------
#include "witchResults.h"		// 結果表示
#include "application.h"		// アプリケーション
#include "VirtualController.h"	// 仮想コントローラー
#include "ResourceManager.h"	// リソースマネージャー
#include "bg.h"					// 背景
#include "game.h"				// ゲーム
#include "player.h"				// プレイヤー
#include "TextureFileName.h"	// 画像のファイル名

//-----------------------------------------------------------------------------------------------
// 定数宣言
//-----------------------------------------------------------------------------------------------
// 幅
static const float RESULT_WIDTH = 200.0f;
// 高さ
static const float RESULT_HEIGHT = 200.0f;
// プレイヤーリザルトの幅
static const float RESULT_PLAYER_WIDTH = 110.0f;
// プレイヤーリザルトの高さ
static const float RESULT_PLAYER_HEIGHT = 300.0f;

//---------------------------------------------------------------------------------
// 静的メンバ変数宣言
//---------------------------------------------------------------------------------
// タイトルのポインタ
CWitchResult* CWitchResult::m_Instance = nullptr;

//---------------------------------------------------------------------------------
//	コンストラクタ
//---------------------------------------------------------------------------------
CWitchResult::CWitchResult()
	:m_nWinner(0)
{
	for (int nCntResult = 0; nCntResult < MAX_TEX; nCntResult++)
	{
		m_paObject2D[nCntResult] = nullptr;
	}
}

//---------------------------------------------------------------------------------
//	デストラクタ
//---------------------------------------------------------------------------------
CWitchResult::~CWitchResult()
{

}

//---------------------------------------------------------------------------------
// インスタンスの生成
//---------------------------------------------------------------------------------
void CWitchResult::CreateInstance()
{
	if (m_Instance == nullptr)
	{// nullptrだったら
	 // メモリの生成
		m_Instance = new CWitchResult;
	}
}

//---------------------------------------------------------------------------------
// インスタンスの取得
//---------------------------------------------------------------------------------
CWitchResult* CWitchResult::GetInstance()
{
	if (m_Instance != nullptr)
	{// nullptrではなかったら
		return m_Instance;
	}

	return nullptr;
}

//-----------------------------------------------------------------------------------------------
// どっちが勝者か
//-----------------------------------------------------------------------------------------------
void CWitchResult::SetWinner()
{
	CPlayer* pPlayer_One = CGame::GetPlayer(0);
	CPlayer* pPlayer_Second = CGame::GetPlayer(1);

	if (pPlayer_One->GetLife() > pPlayer_Second->GetLife())
	{// 1Pの寿命が多かったら
		m_nWinner = MULTI_TYPE_ONE;
	}
	else if (pPlayer_One->GetLife() < pPlayer_Second->GetLife())
	{// 2Pの寿命が多かったら
		m_nWinner = MULTI_TYPE_SECOND;
	}
}

//---------------------------------------------------------------------------------
//	初期化
//---------------------------------------------------------------------------------
HRESULT CWitchResult::Init(const D3DXVECTOR3& pos)
{
	// オブジェクト2Dを生成
	m_paObject2D[0] = CObject2D::Create(nullptr,D3DXVECTOR3(pos.x, pos.y, 0.0f), D3DXVECTOR3(RESULT_WIDTH, RESULT_HEIGHT, 0.0f));
	m_paObject2D[1] = CObject2D::Create(nullptr,D3DXVECTOR3(pos.x + 700.0f, pos.y, 0.0f), D3DXVECTOR3(RESULT_WIDTH, RESULT_HEIGHT, 0.0f));
	m_paObject2D[2] = CObject2D::Create(nullptr,D3DXVECTOR3(pos.x - 300.0f, pos.y, 0.0f), D3DXVECTOR3(RESULT_PLAYER_WIDTH, RESULT_PLAYER_HEIGHT, 0.0f));
	m_paObject2D[3] = CObject2D::Create(nullptr,D3DXVECTOR3(pos.x + 400.0f, pos.y, 0.0f), D3DXVECTOR3(RESULT_PLAYER_WIDTH, RESULT_PLAYER_HEIGHT, 0.0f));

	for (int nCntResult = 0; nCntResult < MAX_TEX; nCntResult++)
	{
		// オブジェクトの親を設定
		m_paObject2D[nCntResult]->SetObjectParent(CObject::EOBJECT_PARENT_RESULT);
	}

	// テクスチャと色の設定
	switch (m_nWinner)
	{
		// 1Pの勝ち
	case MULTI_TYPE_ONE:
		m_paObject2D[0]->LoadTexture(TEX_RESULT_WIN);
		m_paObject2D[0]->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		m_paObject2D[1]->LoadTexture(TEX_RESULT_LOST);
		m_paObject2D[1]->SetColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));

		m_paObject2D[2]->LoadTexture(TEX_RESULT_1P_WIN);
		m_paObject2D[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_paObject2D[3]->LoadTexture(TEX_RESULT_2P_LOSE);
		m_paObject2D[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;
		// 2Pの勝ち
	case MULTI_TYPE_SECOND:
		m_paObject2D[0]->LoadTexture(TEX_RESULT_LOST);
		m_paObject2D[0]->SetColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
		m_paObject2D[1]->LoadTexture(TEX_RESULT_WIN); 
		m_paObject2D[1]->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

		m_paObject2D[2]->LoadTexture(TEX_RESULT_1P_LOSE);
		m_paObject2D[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_paObject2D[3]->LoadTexture(TEX_RESULT_2P_WIN);
		m_paObject2D[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;
		// その他
	default:
		break;
	}

	return S_OK;
}

//---------------------------------------------------------------------------------
//	終了
//---------------------------------------------------------------------------------
void CWitchResult::Uninit()
{
	if (m_Instance != nullptr)
	{// nullptrではなかったら
		// メモリを破棄する
		delete m_Instance;

		// nullptrにする
		m_Instance = nullptr;
	}
}

//---------------------------------------------------------------------------------
//	更新
//---------------------------------------------------------------------------------
void CWitchResult::Update()
{
	
}

//---------------------------------------------------------------------------------
// 描画
//---------------------------------------------------------------------------------
void CWitchResult::Draw()
{

}