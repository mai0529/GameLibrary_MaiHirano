//-----------------------------------------------------------------------------------------------
//
// ボス敵の処理[enemyBoss.cpp]
// Author : 平野舞
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// インクルードファイル
//-----------------------------------------------------------------------------------------------
#include "enemyBoss.h"			// ボス敵
#include "application.h"		// アプリケーション
#include "renderer.h"			// レンダリング
#include "time.h"				// タイム
#include "TextureFileName.h"	// 画像のファイル名

//-----------------------------------------------------------------------------------------------
// 定数宣言
//-----------------------------------------------------------------------------------------------
// 幅
static const float ENEMY_BOSS_WIDTH = 350.0f;
// 高さ
static const float ENEMY_BOSS_HEIGHT = 290.0f;
// アニメーション間隔
static const int ENEMY_BOSS_INTERVAL = 15;
// アニメーションの最大数
static const int ENEMY_BOSS_MAXANIM = 2;
// U座標の最大分割数
static const int ENEMY_BOSS_DIVISION_U = 2;
// V座標の最大分割数
static const int ENEMY_BOSS_DIVISION_V = 1;
// 移動量
static const float ENEMY_BOSS_MOVING = -0.9f;
// 戻り始める時間
static const int ENEMY_RETURN_TIME = 5;

//-----------------------------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------------------------
CEnemyBoss::CEnemyBoss()
	:m_nCntAnim(0),m_nNowPatternAnim(0)
{

}

//-----------------------------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------------------------
CEnemyBoss::~CEnemyBoss()
{

}

//-----------------------------------------------------------------------------------------------
// 生成
//-----------------------------------------------------------------------------------------------
CEnemyBoss* CEnemyBoss::Create(const D3DXVECTOR3& pos)
{
	// ポインタクラスを宣言
	CEnemyBoss* pEnemyDog = new CEnemyBoss;

	if (pEnemyDog != nullptr)
	{// もしnullptrではなかったら
		// 初期化
		pEnemyDog->Init(pos);
	}

	return pEnemyDog;
}

//-----------------------------------------------------------------------------------------------
// 初期化
//
// const D3DXVECTOR3& pos → 最初に表示する座標位置
//-----------------------------------------------------------------------------------------------
HRESULT CEnemyBoss::Init(const D3DXVECTOR3& pos)
{
	// テクスチャの設定
	CObject2D::LoadTexture(TEX_ENEMY_BOSS);
	// サイズ
	CEnemy::SetSize(D3DXVECTOR3(ENEMY_BOSS_WIDTH, ENEMY_BOSS_HEIGHT, 0.0f));
	// 種類
	CEnemy::SetEnemyType(ENEMY_TYPE_BOSS);

	CEnemy::Init(pos);

	// 頂点カラー
	CObject2D::SetColor(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// 終了
//-----------------------------------------------------------------------------------------------s
void CEnemyBoss::Uninit()
{
	CEnemy::Uninit();
}

//-----------------------------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------------------------
void CEnemyBoss::Update()
{
	// カウントを増やす
	m_nCntAnim++;

	// 移動
	//Move();

	if (m_nCntAnim % ENEMY_BOSS_INTERVAL == 0)
	{
		// アニメーションを1つ進める
		m_nNowPatternAnim++;
	}

	if (m_nNowPatternAnim == ENEMY_BOSS_MAXANIM)
	{
		// アニメーションを元に戻す
		m_nNowPatternAnim = 0;
	}

	// テクスチャ座標の更新
	CObject2D::SetTexAnim(ENEMY_BOSS_DIVISION_U, ENEMY_BOSS_DIVISION_V ,m_nNowPatternAnim,0);

	CEnemy::Update();
}

//-----------------------------------------------------------------------------------------------
// 描画
//-----------------------------------------------------------------------------------------------
void CEnemyBoss::Draw()
{
	CEnemy::Draw();
}

//-----------------------------------------------------------------------------------------------
// 移動
//-----------------------------------------------------------------------------------------------
void CEnemyBoss::Move()
{
	
}