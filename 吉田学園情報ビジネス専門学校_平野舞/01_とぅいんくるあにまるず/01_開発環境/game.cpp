//---------------------------------------------------------------------------------
//
// ゲーム処理[game.cpp]
// Author : 平野舞
//
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// インクルードファイル
//---------------------------------------------------------------------------------
#include "game.h"				// ゲーム
#include "application.h"		// アプリケーション
#include "renderer.h"			// レンダリング
#include "object2D.h"			// 2Dオブジェクト
#include "player.h"				// プレイヤー
#include "bullet.h"				// 弾
#include "life.h"				// ライフ
#include "bg.h"					// 背景
#include "effect.h"				// エフェクト
#include "wall.h"				// 壁
#include "skill.h"				// スキル
#include "ResourceManager.h"	// リソースマネージャー
#include "VirtualController.h"	// 仮想コントローラー
#include "time.h"				// タイマー
#include "enemyManager.h"		// 敵マネージャー
#include "itemManager.h"		// アイテムマネージャー
#include "sound.h"				// 音
#include "enemy.h"				// 敵
#include "TextureFileName.h"	// 画像のファイル名
#include "fade.h"				// フェード
#include "pause.h"				// ポーズ
#include "countDown.h"			// カウントダウン

//---------------------------------------------------------------------------------
// テクスチャ名
//---------------------------------------------------------------------------------
char* CGame::m_cFileName[] =
{
	// 背景
	TEX_BG_GAME,
	// 壁
	TEX_WALL,

	// カウントダウン
	TEX_COUNTDOWN,

	// 1P
	TEX_PLAYER_ONE,
	// 2P
	TEX_PLAYER_SECOND,

	// 弾
	TEX_BULLET,
	// 寿命
	TEX_LIFE,
	// スキル
	TEX_SKILL,

	// アイテム( ボム )
	TEX_ITEM_BOM,
	// アイテム( お邪魔 )
	TEX_ITEM_OBSTACLE,

	// 敵( うさぎ )
	TEX_ENEMY_RABBIT,
	// 敵( ねこ )
	TEX_ENEMY_CAT,
	// 敵( いぬ )
	TEX_ENEMY_DOG,
	// 敵( まる )
	TEX_ENEMY_CIRCLE,
	// 敵( ほし )
	TEX_ENEMY_STAR,
	// 敵( 死神 )
	TEX_ENEMY_DEATH,
	// 敵( ボス )
	TEX_ENEMY_BOSS,

	// エフェクト
	TEX_EFFECT,
	nullptr
};

//---------------------------------------------------------------------------------
// 静的メンバ変数宣言
//---------------------------------------------------------------------------------
// ゲーム
CGame* CGame::m_Instance = nullptr;
// プレイヤー
CPlayer* CGame::m_pPlayer[MAX_PLAYER] = { nullptr };
// ライフ
CLife* CGame::m_pLife[MAX_PLAYER] = { nullptr };
// スキルのポインタ
CSkill* CGame::m_pSkill[MAX_PLAYER] = { nullptr };

//---------------------------------------------------------------------------------
//	コンストラクタ
//---------------------------------------------------------------------------------
CGame::CGame()
{

}

//---------------------------------------------------------------------------------
//	デストラクタ
//---------------------------------------------------------------------------------
CGame::~CGame()
{

}

//---------------------------------------------------------------------------------
// インスタンスの生成
//---------------------------------------------------------------------------------
void CGame::CreateInstance()
{
	if (m_Instance == nullptr)
	{// nullptrだったら
		// メモリの生成
		m_Instance = new CGame;
	}
}

//---------------------------------------------------------------------------------
// インスタンスの取得
//---------------------------------------------------------------------------------
CGame* CGame::GetInstance()
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
HRESULT CGame::Init()
{
	// ポーズ中ではない
	CObject::SetPause(false);

	// ポーズのインスタンスを生成
	CPause::CreateInstance();

	// リソースマネージャーのインスタンスを生成
	CResourceManager::CreateInstance();
	// テクスチャの読み込み
	CResourceManager::GetInstance()->LoadTexture(m_cFileName);

	// タイマのインスタンスを生成
	CTime::CreateInstance();
	CTime::GetInstance()->Init();

	// 背景
	CBg::Create(CBg::ETYPE_BG_GAME);

	// 壁
	CWall::CreateInstance();
	CWall::GetInstance()->Init();

	// カウントダウン
	CCountDown::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2.0f,CRenderer::SCREEN_HEIGHT / 2.0f,0.0f));

	// プレイヤー
	m_pPlayer[0] = CPlayer::Create(CObject2D::MULTI_TYPE_ONE, D3DXVECTOR3(300.0f, 600.0f, 0.0f));
	m_pPlayer[1] = CPlayer::Create(CObject2D::MULTI_TYPE_SECOND, D3DXVECTOR3(1000.0f, 600.0f, 0.0f));

	// 敵マネージャーのインスタンスを生成
	CEnemyManager::CreateInstance();
	CEnemyManager::GetInstance()->Init();

	// アイテムマネージャーのインスタンスを生成
	CItemManager::CreateInstance();
	CItemManager::GetInstance()->Init();

	// ライフ
	m_pLife[0] = CLife::Create(D3DXVECTOR3(25.0f, 690.0f, 0.0f));
	m_pLife[1] = CLife::Create(D3DXVECTOR3(725.0f, 690.0f, 0.0f));

	// スキル
	m_pSkill[0] = CSkill::Create(D3DXVECTOR3(525.0f, 690.0f, 0.0f));
	m_pSkill[1] = CSkill::Create(D3DXVECTOR3(1225.0f, 690.0f, 0.0f));

	// 音の再生
	CSound::GetInstace()->Play(CSound::SOUND_LABEL_GAME);

	return S_OK;
}

//---------------------------------------------------------------------------------
//	終了
//---------------------------------------------------------------------------------
void CGame::Uninit()
{
	// 音の停止
	CSound::GetInstace()->Stop();

	if (m_Instance != nullptr)
	{// nullptrではなかったら
	 // オブジェクトの削除
		CObject::ReleaseAll();

		 // ポーズの破棄
		CPause::GetInstance()->DeleteInstance();

		// タイマを破棄する
		CTime::GetInstance()->Uninit();

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
void CGame::Update()
{
	if (!CObject::GetPause())
	{// ゲーム進行中
		// タイマーの更新
		CTime::GetInstance()->Update();

		// 敵マネージャーの更新
		CEnemyManager::GetInstance()->Update();

		// アイテムマネージャーの更新
		CItemManager::GetInstance()->Update();

		if (CVController::GetInstance()->GetTrigger(0, CVController::VIRTUAL_KEY_START) || CVController::GetInstance()->GetTrigger(1, CVController::VIRTUAL_KEY_START))
		{// SPACEキーを押したら
		 // ポーズ中にする
			CObject::SetPause(true);

			// ポーズを生成
			CPause::GetInstance()->Init();
		}
	}
	else if (CObject::GetPause())
	{// ポーズ中だったら
	 // 更新
		CPause::GetInstance()->Update();
	}

#ifdef _DEBUG
	if (CVController::GetInstance()->GetTrigger(0, CVController::VIRTUAL_KEY_A))
	{
		// リザルトに移行
		CFade::GetInstance()->SetFade(CApplication::MODE_RESULT);

		// 音の再生
		CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_DECISION_CAT);
		CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_DECISION_DOG);

		return;
	}
#endif	//_DEBUG
}

//---------------------------------------------------------------------------------
//	プレイヤーポインタの取得
//---------------------------------------------------------------------------------
CPlayer* CGame::GetPlayer(int nCntPlayer)
{
	return m_pPlayer[nCntPlayer];
}

//---------------------------------------------------------------------------------
// ライフのポインタを取得
//---------------------------------------------------------------------------------
CLife* CGame::GetLife(int nCntLife)
{
	return m_pLife[nCntLife];
}

//---------------------------------------------------------------------------------
// スキルのポインタを取得
//---------------------------------------------------------------------------------
CSkill* CGame::GetSkill(int nCntSkill)
{
	return m_pSkill[nCntSkill];
}