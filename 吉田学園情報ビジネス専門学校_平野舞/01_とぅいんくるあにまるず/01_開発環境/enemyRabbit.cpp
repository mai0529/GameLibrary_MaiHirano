//-----------------------------------------------------------------------------------------------
//
// うさぎ型敵の処理[enemyRabbit.cpp]
// Author : 平野舞
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// インクルードファイル
//-----------------------------------------------------------------------------------------------
#include "enemyRabbit.h"	// うさぎ型敵
#include "application.h"	// アプリケーション
#include "renderer.h"		// レンダリング
#include "time.h"			// タイマ
#include "wall.h"			// 壁
#include "TextureFileName.h"	// 画像のファイル名

//-----------------------------------------------------------------------------------------------
// 定数宣言
//-----------------------------------------------------------------------------------------------
// 幅
static const float ENEMY_RABBIT_WIDTH = 50.0f;
// 高さ
static const float ENEMY_RABBIT_HEIGHT = 50.0f;
// 横の移動距離
static const float ENEMY_RABBIT_WIDTH_MOVE = 2.0f;
// 縦の移動距離
static const float ENEMY_RABBIT_HEIGHT_MOVE = 60.0f;
// フレーム数
static const int ENEMY_RABBIT_FRAME = 60;
// 出現フレーム数
static const int ENEMY_RABBIT_APPEA_FREAM = 120;

//-----------------------------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------------------------
CEnemyRabbit::CEnemyRabbit()
	:m_fSpeed(0.0f), m_nCntMove(0),  m_nCntApeer(0),m_bGet(false)
{

}

//-----------------------------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------------------------
CEnemyRabbit::~CEnemyRabbit()
{

}

//-----------------------------------------------------------------------------------------------
// 生成
//-----------------------------------------------------------------------------------------------
CEnemyRabbit* CEnemyRabbit::Create(const D3DXVECTOR3& pos)
{
	// ポインタクラスを宣言
	CEnemyRabbit* pEnemyRabbit = new CEnemyRabbit;

	if (pEnemyRabbit != nullptr)
	{// もしnullptrではなかったら
		// 初期化
		pEnemyRabbit->Init(pos);
	}

	return pEnemyRabbit;
}

//-----------------------------------------------------------------------------------------------
// 初期化
//
// const D3DXVECTOR3& pos → 最初に表示する座標位置
//-----------------------------------------------------------------------------------------------
HRESULT CEnemyRabbit::Init(const D3DXVECTOR3& pos)
{
	// テクスチャの設定
	CObject2D::LoadTexture(TEX_ENEMY_RABBIT);
	// サイズ
	CEnemy::SetSize(D3DXVECTOR3(ENEMY_RABBIT_WIDTH, ENEMY_RABBIT_HEIGHT, 0.0f));
	// 種類
	CEnemy::SetEnemyType(ENEMY_TYPE_RABBIT);

	CEnemy::Init(pos);

	// 頂点カラー
	CObject2D::SetColor(D3DXCOLOR(1.0f,0.5f,0.5f,1.0f));

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// 終了
//-----------------------------------------------------------------------------------------------s
void CEnemyRabbit::Uninit()
{
	CEnemy::Uninit();
}

//-----------------------------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------------------------
void CEnemyRabbit::Update()
{
	if (CObject2D::GetPlayerType() == MULTI_TYPE_ONE)
	{// 1P側なら
		OneMove();
	}
	else if (CObject2D::GetPlayerType() == MULTI_TYPE_SECOND)
	{// 2P側なら
		SecondMove();
	}

	CEnemy::Update();
}

//-----------------------------------------------------------------------------------------------
// 描画
//-----------------------------------------------------------------------------------------------
void CEnemyRabbit::Draw()
{
	CEnemy::Draw();
}

//-----------------------------------------------------------------------------------------------
// 1P移動
//-----------------------------------------------------------------------------------------------
void CEnemyRabbit::OneMove()
{
	// 位置の取得
	D3DXVECTOR3 pos = CEnemy::GetPosition();

	// 移動量の初期化
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 壁の位置とサイズを取得
	D3DXVECTOR3 posWall = CWall::GetInstance()->GetPosition();
	D3DXVECTOR3 sizeWall = CWall::GetInstance()->GetSize();

	if (!m_bGet)
	{// 速度を取得していなかったら
		// 速度の取得
		m_fSpeed = CEnemy::GetSpeed();

		// 取得した
		m_bGet = true;
	}

	if (m_nCntApeer > ENEMY_RABBIT_APPEA_FREAM && pos.x + (ENEMY_RABBIT_WIDTH / 2.0f) > posWall.x - (sizeWall.x / 2.0f)
		|| m_nCntApeer > ENEMY_RABBIT_APPEA_FREAM && pos.x - (ENEMY_RABBIT_WIDTH / 2.0f) < 0.0f )
	{// x座標が壁に当たった時、0.0fになった時
		// 移動スピードを逆方向にする
		m_fSpeed *= -1.0f;

		// y座標を60下にする
		pos.y += ENEMY_RABBIT_HEIGHT_MOVE;

		// 位置設定
		CEnemy::SetPosition(pos);
	}

	// 移動量の加算
	move.x = m_fSpeed;
	move.y = sinf((D3DX_PI / 2.0f) / ENEMY_RABBIT_FRAME * m_nCntMove) * ENEMY_RABBIT_WIDTH_MOVE;

	// 移動量の設定
	CEnemy::SetMove(move);

	// カウントを加算
	m_nCntMove++;
	m_nCntApeer++;
}

//-----------------------------------------------------------------------------------------------
// 2P移動
//-----------------------------------------------------------------------------------------------
void CEnemyRabbit::SecondMove()
{
	// 位置の取得
	D3DXVECTOR3 pos = CEnemy::GetPosition();

	// 移動量の初期化
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 壁の位置とサイズを取得
	D3DXVECTOR3 posWall = CWall::GetInstance()->GetPosition();
	D3DXVECTOR3 sizeWall = CWall::GetInstance()->GetSize();

	if (!m_bGet)
	{// 出現時間とタイマが同じだったら
	 // 速度の取得
		m_fSpeed = CEnemy::GetSpeed();

		// 取得した
		m_bGet = true;
	}

	if (m_nCntApeer > ENEMY_RABBIT_APPEA_FREAM && pos.x - (ENEMY_RABBIT_WIDTH / 2.0f) < posWall.x + (sizeWall.x / 2.0f) + 5.0f
		|| m_nCntApeer > ENEMY_RABBIT_APPEA_FREAM && pos.x + (ENEMY_RABBIT_WIDTH / 2.0f) > CRenderer::SCREEN_WIDTH)
	{// x座標が壁に当たった時、1280.0fになった時
		// 移動スピードを逆方向にする
		m_fSpeed *= -1.0f;

		// y座標を60下にする
		pos.y += ENEMY_RABBIT_HEIGHT_MOVE;

		// 位置設定
		CEnemy::SetPosition(pos);
	}

	// 移動量の加算
	move.x = m_fSpeed;
	move.y = sinf((D3DX_PI / 2.0f) / ENEMY_RABBIT_FRAME * m_nCntMove) * ENEMY_RABBIT_WIDTH_MOVE;

	// 移動量の設定
	CEnemy::SetMove(move);

	// カウントを加算
	m_nCntMove++;
	m_nCntApeer++;
}