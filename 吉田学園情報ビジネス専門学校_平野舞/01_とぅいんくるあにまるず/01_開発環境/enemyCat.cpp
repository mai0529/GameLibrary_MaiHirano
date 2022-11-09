//-----------------------------------------------------------------------------------------------
//
// ねこ型敵の処理[enemyCat.cpp]
// Author : 平野舞
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// インクルードファイル
//-----------------------------------------------------------------------------------------------
#include "enemyCat.h"		// ねこ型敵
#include "application.h"	// アプリケーション
#include "renderer.h"		// レンダリング
#include "time.h"			// タイム
#include "TextureFileName.h"	// 画像のファイル名

//-----------------------------------------------------------------------------------------------
// 定数宣言
//-----------------------------------------------------------------------------------------------
// 幅
static const float ENEMY_CAT_WIDTH = 60.0f;
// 高さ
static const float ENEMY_CAT_HEIGHT = 50.0f;
// 半径
static const float ENEMY_CAT_RADIUS = 70.0f;
// 中心を決める時間
static const int ENEMY_CAT_GETPOS_TIME = 3;
// 回り始める時間
static const int ENEMY_CAT_START_TIME = 4;
// 回り終わる時間
static const int ENEMY_CAT_FINISH_TIME = 9;

//-----------------------------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------------------------
CEnemyCat::CEnemyCat()
	:m_posStart(0.0f,0.0f,0.0f),m_Center(0.0f,0.0f,0.0f),m_fAngle(0.0f),m_fRadius(0.0f), m_bGet(false)
{

}

//-----------------------------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------------------------
CEnemyCat::~CEnemyCat()
{

}

//-----------------------------------------------------------------------------------------------
// 生成
//-----------------------------------------------------------------------------------------------
CEnemyCat* CEnemyCat::Create(const D3DXVECTOR3& pos)
{
	// ポインタクラスを宣言
	CEnemyCat* pEnemyCat = new CEnemyCat;

	if (pEnemyCat != nullptr)
	{// もしnullptrではなかったら
		// 位置
		pEnemyCat->SetPosition(pos);
		// 初期化
		pEnemyCat->Init();
	}

	return pEnemyCat;
}

//-----------------------------------------------------------------------------------------------
// 初期化
//
// const D3DXVECTOR3& pos → 最初に表示する座標位置
//-----------------------------------------------------------------------------------------------
HRESULT CEnemyCat::Init()
{
	//角度
	m_fAngle = D3DX_PI;
	// 半径
	m_fRadius = ENEMY_CAT_RADIUS;

	// テクスチャの設定
	CObject2D::LoadTexture(TEX_ENEMY_CAT);
	// サイズ
	CEnemy::SetSize(D3DXVECTOR3(ENEMY_CAT_WIDTH, ENEMY_CAT_HEIGHT, 0.0f));
	// 種類
	CEnemy::SetEnemyType(ENEMY_TYPE_CAT);

	CEnemy::Init();

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// 終了
//-----------------------------------------------------------------------------------------------s
void CEnemyCat::Uninit()
{
	CEnemy::Uninit();
}

//-----------------------------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------------------------
void CEnemyCat::Update()
{
	// 移動
	Move();

	// 角度を更新
	m_fAngle += D3DX_PI / 180.0f;

	// 角度の正規化
	if (m_fAngle < -D3DX_PI)
	{
		m_fAngle += D3DX_PI * 2.0f;
	}
	else if (m_fAngle > D3DX_PI)
	{
		m_fAngle -= D3DX_PI * 2.0f;
	}

	CEnemy::Update();
}

//-----------------------------------------------------------------------------------------------
// 描画
//-----------------------------------------------------------------------------------------------
void CEnemyCat::Draw()
{
	CEnemy::Draw();
}

//-----------------------------------------------------------------------------------------------
// 移動
//-----------------------------------------------------------------------------------------------
void CEnemyCat::Move()
{
	// 速度の取得
	float fSpeed = CEnemy::GetSpeed();

	// 出現時間の取得
	int nAppea = CEnemy::GetAppeaTime();

	// 移動量の初期化
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 位置の初期化
	D3DXVECTOR3 pos = CObject2D::GetPosition();

	if (!m_bGet)
	{// 情報を取得していなかったら
		// 初期位置を取得
		m_posStart = CEnemy::GetPosition();
	}

	
	if (CObject2D::GetPlayerType() == MULTI_TYPE_ONE && CTime::GetInstance()->GetTime() == nAppea + ENEMY_CAT_GETPOS_TIME)
	{// 1P側なら
		if (m_posStart.x > 300)
		{// 中心
			m_Center = D3DXVECTOR3(pos.x - 100.0f, pos.y, 0.0f);
		}
		else if (m_posStart.x <= 300)
		{
			m_Center = D3DXVECTOR3(pos.x + 50.0f, pos.y, 0.0f);
		}
	}
	else if (CObject2D::GetPlayerType() == MULTI_TYPE_SECOND && CTime::GetInstance()->GetTime() == nAppea + ENEMY_CAT_GETPOS_TIME)
	{// 2P側なら
		m_Center = D3DXVECTOR3(pos.x - 50.0f, pos.y, 0.0f);
	}

	if (CTime::GetInstance()->GetTime() >= nAppea + ENEMY_CAT_START_TIME && CTime::GetInstance()->GetTime() <= nAppea + ENEMY_CAT_FINISH_TIME)
	{// 回る
		pos.x = (sinf(m_fAngle) * m_fRadius) + m_Center.x;
		pos.y = (cosf(m_fAngle) * m_fRadius) + m_Center.y;
	}
	else
	{
		move.y = fSpeed;
	}

	// 移動量の設定
	CEnemy::SetMove(move);

	// 位置の設定
	CObject2D::SetPosition(pos);
}