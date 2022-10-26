//---------------------------------------------------------------------------------
//
// 死神の処理[enemyDeath.cpp]
// Author : 平野舞
//
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// インクルードファイル
//---------------------------------------------------------------------------------
#include "enemyDeath.h"		// 死神
#include "game.h"			// ゲーム
#include "player.h"			// プレイヤー
#include "TextureFileName.h"	// 画像のファイル名

//---------------------------------------------------------------------------------
// 定数宣言
//---------------------------------------------------------------------------------
// 幅
static const float ENEMY_DEATH_WIDTH = 80.0f;
// 高さ
static const float ENEMY_DEATH_HEIGHT = 80.0f;
// 速度
static const float ENEMY_DEATH_SPEED = 1.7f;
// 加算速度
static const float ENEMY_DEATH_ADD_SPEED = 0.2f;

//---------------------------------------------------------------------------------
// 静的メンバ変数宣言
//---------------------------------------------------------------------------------
int CEnemyDeath::m_nCntAppea = 0;

//---------------------------------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------------------------------
CEnemyDeath::CEnemyDeath()
	:m_fSpeed(0.0f)
{
	// 出現回数を加算
	m_nCntAppea++;
}

//---------------------------------------------------------------------------------
// デストラクタ
//---------------------------------------------------------------------------------
CEnemyDeath::~CEnemyDeath()
{

}

//---------------------------------------------------------------------------------
// 生成
//
// const D3DXVECTOR3& pos → 最初に表示する座標位置
//---------------------------------------------------------------------------------
CEnemyDeath* CEnemyDeath::Create(const D3DXVECTOR3& pos)
{
	// メモリを生成
	CEnemyDeath* pEnemyDeath = new CEnemyDeath;

	if (pEnemyDeath != nullptr)
	{// nullptrではなかったら
		// 初期化
		pEnemyDeath->Init(pos);
	}

	return pEnemyDeath;
}

//---------------------------------------------------------------------------------
// 初期化
//
// const D3DXVECTOR3& pos → 最初に表示する座標位置
//---------------------------------------------------------------------------------
HRESULT CEnemyDeath::Init(const D3DXVECTOR3& pos)
{
	// 速度
	m_fSpeed = ENEMY_DEATH_SPEED;

	// テクスチャの設定
	CObject2D::LoadTexture(TEX_ENEMY_DEATH);
	//サイズ
	CEnemy::SetSize(D3DXVECTOR3(ENEMY_DEATH_WIDTH, ENEMY_DEATH_HEIGHT, 0.0f));
	// 種類
	CEnemy::SetEnemyType(ENEMY_TYPE_DEATH);

	CEnemy::Init(pos);

	return S_OK;
}

//---------------------------------------------------------------------------------
// 終了
//---------------------------------------------------------------------------------
void CEnemyDeath::Uninit()
{
	CEnemy::Uninit();

	m_nCntAppea = 0;
}

//---------------------------------------------------------------------------------
// 更新
//---------------------------------------------------------------------------------
void CEnemyDeath::Update()
{
	// 移動量の初期化
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ホーミング処理
	D3DXVECTOR3 PosDis = Homing();

	// 移動量を加算
	move = PosDis * (m_fSpeed + (((m_nCntAppea - 1) / 2) * ENEMY_DEATH_ADD_SPEED));

	// 移動量を設定
	CEnemy::SetMove(move);

	CEnemy::Update();
}

//---------------------------------------------------------------------------------
// 描画
//---------------------------------------------------------------------------------
void CEnemyDeath::Draw()
{
	CEnemy::Draw();
}

//---------------------------------------------------------------------------------
// ホーミング
//---------------------------------------------------------------------------------
D3DXVECTOR3 CEnemyDeath::Homing()
{
	// プレイヤーのポインタ
	CPlayer* pPlayer = nullptr;

	// 情報を取得
	switch (CObject2D::GetPlayerType())
	{
		// 1P側
	case MULTI_TYPE_ONE:
		pPlayer = CGame::GetPlayer(MULTI_TYPE_ONE - 1);
		break;
		// 2P側
	case MULTI_TYPE_SECOND:
		pPlayer = CGame::GetPlayer(MULTI_TYPE_SECOND - 1);
		break;
		// その他
	default:
		break;
	}

	// プレイヤーの位置を取得
	D3DXVECTOR3 PlayerPos = pPlayer->GetPosition();

	// 死神の場所を取得
	D3DXVECTOR3 EnemyPos = GetPosition();

	// 距離の差を求める
	D3DXVECTOR3 PosDis = PlayerPos - EnemyPos;

	// 正規化する
	D3DXVec3Normalize(&PosDis, &PosDis);

	return PosDis;
}