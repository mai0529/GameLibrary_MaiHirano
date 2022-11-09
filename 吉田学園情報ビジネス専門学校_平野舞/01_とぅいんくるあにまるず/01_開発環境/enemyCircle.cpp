//-----------------------------------------------------------------------------------------------
//
// おじゃま型敵の処理[enemyCircle.cpp]
// Author : 平野舞
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// インクルードファイル
//-----------------------------------------------------------------------------------------------
#include "enemyCircle.h"	// 丸のお邪魔敵
#include "application.h"	// アプリケーション
#include "renderer.h"		// レンダリング
#include "game.h"			// ゲーム
#include "player.h"			// プレイヤー
#include "TextureFileName.h"	// 画像のファイル名

//-----------------------------------------------------------------------------------------------
// 定数宣言
//-----------------------------------------------------------------------------------------------
// 幅
static const float ENEMY_CIRCLE_WIDTH = 50.0f;
// 高さ
static const float ENEMY_CIRCLE_HEIGHT = 50.0f;
// 移動量
static const float ENEMY_CIRCLE_MOVING = 4.0f;


//-----------------------------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------------------------
CEnemyCircle::CEnemyCircle()
	:m_bSetMove(false),m_bAttack(false)
{

}

//-----------------------------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------------------------
CEnemyCircle::~CEnemyCircle()
{

}

//-----------------------------------------------------------------------------------------------
// 生成
//-----------------------------------------------------------------------------------------------
CEnemyCircle* CEnemyCircle::Create(const D3DXVECTOR3& pos)
{
	// ポインタクラスを宣言
	CEnemyCircle* pEnemyCircle = new CEnemyCircle;

	if (pEnemyCircle != nullptr)
	{// もしnullptrではなかったら
		// 位置
		pEnemyCircle->SetPosition(pos);
		// 初期化
		pEnemyCircle->Init();
	}

	return pEnemyCircle;
}

//-----------------------------------------------------------------------------------------------
// 初期化
//
// const D3DXVECTOR3& pos → 最初に表示する座標位置
//-----------------------------------------------------------------------------------------------
HRESULT CEnemyCircle::Init()
{
	// テクスチャの設定
	CObject2D::LoadTexture(TEX_ENEMY_CIRCLE);
	//サイズ
	CEnemy::SetSize(D3DXVECTOR3(ENEMY_CIRCLE_WIDTH, ENEMY_CIRCLE_HEIGHT, 0.0f));
	// 種類
	CEnemy::SetEnemyType(ENEMY_TYPE_CIRCLE);

	CEnemy::Init();

	// 頂点カラー
	CObject2D::SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// 終了
//-----------------------------------------------------------------------------------------------
void CEnemyCircle::Uninit()
{
	CEnemy::Uninit();
}

//-----------------------------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------------------------
void CEnemyCircle::Update()
{
	if (!m_bSetMove)
	{// 移動量を設定
		switch (CObject2D::GetPlayerType())
		{
			// 1P側
		case MULTI_TYPE_ONE:
			CEnemy::SetMove(D3DXVECTOR3(ENEMY_CIRCLE_MOVING, -ENEMY_CIRCLE_MOVING, 0.0f));
			break;
			//2P側
		case MULTI_TYPE_SECOND:
			CEnemy::SetMove(D3DXVECTOR3(-ENEMY_CIRCLE_MOVING, -ENEMY_CIRCLE_MOVING, 0.0f));
			break;
		default:
			break;
		}

		// 移動量を設定した
		m_bSetMove = true;
	}

	if (!m_bAttack)
	{// 画面上に当たっていなかったら
		// 移動
		Move();
	}

	CEnemy::Update();
}

//-----------------------------------------------------------------------------------------------
// 描画
//-----------------------------------------------------------------------------------------------
void CEnemyCircle::Draw()
{
	CEnemy::Draw();
}

//-----------------------------------------------------------------------------------------------
// 動き
//-----------------------------------------------------------------------------------------------
void CEnemyCircle::Move()
{
	// 位置を取得
	D3DXVECTOR3 pos = CObject2D::GetPosition();

	// 移動量の初期化
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 距離の差
	D3DXVECTOR3 posDis = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// プレイヤーのポインタ
	CPlayer* pPlayer = nullptr;

	switch (CObject2D::GetPlayerType())
	{
		// 1P側
	case MULTI_TYPE_ONE:
		// プレイヤー情報を取得
		pPlayer = CGame::GetPlayer(MULTI_TYPE_SECOND - 1);
		break;
		// 2P側
	case MULTI_TYPE_SECOND:
		// プレイヤー情報を取得
		pPlayer = CGame::GetPlayer(MULTI_TYPE_ONE - 1);
		break;
		// その他
	default:
		break;
	}

	if (pos.y - (ENEMY_CIRCLE_HEIGHT / 2.0f) < 0.0f)
	{// 画面上に当たったら
		// 距離の差を求める
		posDis = pPlayer->GetPosition() - CEnemy::GetPosition();

		// 正規化
		D3DXVec3Normalize(&posDis, &posDis);

		// 移動量
		move.x = posDis.x * ENEMY_CIRCLE_MOVING;
		move.y = posDis.y * ENEMY_CIRCLE_MOVING;

		// 画面の上に当たった
		m_bAttack = true;

		// 移動量を設定
		CEnemy::SetMove(move);
	}
}