//-----------------------------------------------------------------------------------------------
//
// 星のお邪魔敵の処理[enemyStar.cpp]
// Author : 平野舞
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// インクルードファイル
//-----------------------------------------------------------------------------------------------
#include "enemyStar.h"			// 星のお邪魔敵
#include "application.h"		// アプリケーション
#include "renderer.h"			// レンダリング
#include "game.h"				// ゲーム
#include "player.h"				// プレイヤー
#include "TextureFileName.h"	// 画像のファイル名

//-----------------------------------------------------------------------------------------------
// 定数宣言
//-----------------------------------------------------------------------------------------------
// 幅
static const float ENEMY_STAR_WIDTH = 50.0f;
// 高さ
static const float ENEMY_STAR_HEIGHT = 50.0f;
// 移動量
static const float ENEMY_STAR_MOVING = -4.0f;
// フレーム数
static const int ENEMY_STAR_FRAME = 120;
// 重力
static const float ENEMY_STAR_GRAVITY = 0.1f;

//-----------------------------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------------------------
CEnemyStar::CEnemyStar()
	:m_move(0.0f,0.0f,0.0f), m_bSetMove(false)
{

}

//-----------------------------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------------------------
CEnemyStar::~CEnemyStar()
{

}

//-----------------------------------------------------------------------------------------------
// 生成
//-----------------------------------------------------------------------------------------------
CEnemyStar* CEnemyStar::Create(const D3DXVECTOR3& pos)
{
	// ポインタクラスを宣言
	CEnemyStar* pEnemyStar = new CEnemyStar;

	if (pEnemyStar != nullptr)
	{// もしnullptrではなかったら
	 // 初期化
		pEnemyStar->Init(pos);
	}

	return pEnemyStar;
}

//-----------------------------------------------------------------------------------------------
// 初期化
//
// const D3DXVECTOR3& pos → 最初に表示する座標位置
//-----------------------------------------------------------------------------------------------
HRESULT CEnemyStar::Init(const D3DXVECTOR3& pos)
{
	// テクスチャの設定
	CObject2D::LoadTexture(TEX_ENEMY_STAR);
	//サイズ
	CEnemy::SetSize(D3DXVECTOR3(ENEMY_STAR_WIDTH, ENEMY_STAR_HEIGHT, 0.0f));
	// 種類
	CEnemy::SetEnemyType(ENEMY_TYPE_STAR);

	CEnemy::Init(pos);

	// 頂点カラー
	CObject2D::SetColor(D3DXCOLOR(3.0f, 1.0f, 0.0f, 1.0f));

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// 終了
//-----------------------------------------------------------------------------------------------
void CEnemyStar::Uninit()
{
	CEnemy::Uninit();
}

//-----------------------------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------------------------
void CEnemyStar::Update()
{
	if (!m_bSetMove)
	{// 移動量を設定していなかったら
		Move();
	}

	// 重力加算
	m_move.y += ENEMY_STAR_GRAVITY;

	// 移動量を設定
	CEnemy::SetMove(m_move);

	CEnemy::Update();
}

//-----------------------------------------------------------------------------------------------
// 描画
//-----------------------------------------------------------------------------------------------
void CEnemyStar::Draw()
{
	CEnemy::Draw();
}

//-----------------------------------------------------------------------------------------------
// 動き
//-----------------------------------------------------------------------------------------------
void CEnemyStar::Move()
{
	// 位置を取得
	D3DXVECTOR3 pos = CObject2D::GetPosition();

	//位置の差
	D3DXVECTOR3 posDis = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// プレイヤーのポインタ
	CPlayer* pPlayer = nullptr;

	// プレイヤーの位置
	D3DXVECTOR3 PlayerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	switch (CObject2D::GetPlayerType())
	{
		// 1P側
	case MULTI_TYPE_ONE:
		// プレイヤーの情報を取得
		pPlayer = CGame::GetPlayer(MULTI_TYPE_SECOND -1);
		break;
		// 2P側
	case MULTI_TYPE_SECOND:
		// プレイヤーの情報を取得
		pPlayer = CGame::GetPlayer(MULTI_TYPE_ONE - 1);
		break;
		// その他
	default:
		break;
	}

	// 位置の取得
	PlayerPos = pPlayer->GetPosition();

	// 距離の差
	posDis = PlayerPos - pos;

	// 移動量の加算
	m_move.x = posDis.x / ENEMY_STAR_FRAME;
	m_move.y = (posDis.y - (0.5f * ENEMY_STAR_FRAME * ENEMY_STAR_FRAME * ENEMY_STAR_GRAVITY)) / ENEMY_STAR_FRAME;

	// 移動量を設定した
	m_bSetMove = true;
}