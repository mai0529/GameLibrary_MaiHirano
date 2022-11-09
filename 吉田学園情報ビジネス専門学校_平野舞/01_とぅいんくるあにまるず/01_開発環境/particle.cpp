//-----------------------------------------------------------------------------------------------
//
// パーティクルの処理[particle.cpp]
// Author : 平野舞
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// インクルードファイル
//-----------------------------------------------------------------------------------------------
#include "particle.h"		// パーティクル
#include "effect.h"			// エフェクト
#include "application.h"	// アプリケーション
#include "renderer.h"		// レンダリング
#include "object2D.h"		// 2Dオブジェクト
#include "enemyManager.h"	// 敵マネージャー
#include "enemy.h"			// 敵
#include "time.h"			// タイマ

//-----------------------------------------------------------------------------------------------
// 定数宣言
//-----------------------------------------------------------------------------------------------
// 幅
static const float PARTICLE_WIDTH = 13.0f;
// 高さ
static const float PARTICLE_HEIGHT = 13.0f;
// 角度
static const int PARTICLE_ANGLE = 628;
// 寿命
static const int PARTICLE_MAX_LIFE = 40;
//円の当たり判定の半径
static const float COLLISION_RADIUS = 60.0f;

//-----------------------------------------------------------------------------------------------
// 静的メンバ変数
//-----------------------------------------------------------------------------------------------
// テクスチャのポインタ
LPDIRECT3DTEXTURE9 CParticle::m_pTexture = nullptr;
// 連鎖数
int CParticle::m_nChain = 0;
// 生成時間
int CParticle::m_nCreateTime = 0;
// 前回の生成時間
int CParticle::m_nCreateTimeOld = 0;

//-----------------------------------------------------------------------------------------------
//　コンストラクタ
//-----------------------------------------------------------------------------------------------
CParticle::CParticle()
	:m_paEffect(nullptr), m_pos(0.0f,0.0f,0.0f),m_nLife(0), m_AddSize(0.0f)
{

}

//-----------------------------------------------------------------------------------------------
//　デストラクタ
//-----------------------------------------------------------------------------------------------
CParticle::~CParticle()
{

}

//-----------------------------------------------------------------------------------------------
// 生成
//-----------------------------------------------------------------------------------------------
CParticle* CParticle::Create(const D3DXVECTOR3& pos)
{
	// ポインタを宣言
	CParticle* pParticle = new CParticle;

	if (pParticle != nullptr)
	{// nullptrではなかったら
		// 位置
		pParticle->SetPosition(pos);
		 // 初期化する
		pParticle->Init();
	}

	return pParticle;
}

//-----------------------------------------------------------------------------------------------
//　初期化
//-----------------------------------------------------------------------------------------------
HRESULT CParticle::Init()
{
	// 寿命
	m_nLife = PARTICLE_MAX_LIFE;
	// オブジェクトの種類を設定
	SetObjectType(EOBJECT_TYPE::EOBJECT_TYPE_PARTICLE);

	// 前回の生成時間を設定
	m_nCreateTimeOld = m_nCreateTime;

	// 生成時間を取得
	m_nCreateTime = CTime::GetInstance()->GetTime();

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
//　終了
//-----------------------------------------------------------------------------------------------
void CParticle::Uninit()
{
	// オブジェクトの破棄
	Release();
}

//-----------------------------------------------------------------------------------------------
//　更新
//-----------------------------------------------------------------------------------------------
void CParticle::Update()
{
	// 乱数で角度を設定
	int fAngle = rand() % PARTICLE_ANGLE;

	// 乱数で色を設定
	float fColR = (rand() % 100) / 100.0f;
	float fColG = (rand() % 100) / 100.0f;
	float fColB = (rand() % 100) / 100.0f;

	// エフェクト
	m_paEffect = CEffect::Create(m_pos);
	// オブジェクトの種類を設定
	m_paEffect->SetObjectType(EOBJECT_TYPE::EOBJECT_TYPE_PARTICLE);
	// 親の設定
	m_paEffect->SetObjectParent(EOBJECT_PARENT::EOBJECT_PARENT_GAME);
	// サイズを設定
	m_paEffect->SetSize(D3DXVECTOR3(PARTICLE_WIDTH + m_AddSize, PARTICLE_HEIGHT + m_AddSize, 0.0f));
	// 角度を設定
	m_paEffect->SetAngle(fAngle / 100.0f);
	// 色の設定
	m_paEffect->SetColor(D3DXCOLOR(fColR, fColG, fColB, 1.0f));

	if (m_nCreateTime - m_nCreateTimeOld > 2)
	{// 一定時間が経ったら
		// 連鎖を初期化
		m_nChain = 0;
	}

	// 当たり判定
	CollisionEnemy(m_pos);

	// サイズを大きくする
	m_AddSize += 0.2f;

	// 寿命を減らす
	m_nLife--;

	if (m_nLife == 0)
	{// 寿命が0になったら
		// 終了する
		Uninit();
	}
}

//-----------------------------------------------------------------------------------------------
//　描画
//-----------------------------------------------------------------------------------------------
void CParticle::Draw()
{

}

//-----------------------------------------------------------------------------------------------
// 位置の設定
//
// const D3DXVECTOR3& pos → 設定したい位置
//-----------------------------------------------------------------------------------------------
void CParticle::SetPosition(const D3DXVECTOR3& pos)
{
	m_pos = pos;
}

//-----------------------------------------------------------------------------------------------
// 位置の取得
//-----------------------------------------------------------------------------------------------
const D3DXVECTOR3& CParticle::GetPosition() const
{
	return m_pos;
}

//-----------------------------------------------------------------------------------------------
// 連鎖
//
// CObject2D::MULTI_TYPE type → 1Pか2Pか
// const D3DXVECTOR3& pos	  → お邪魔敵が発生する位置
//-----------------------------------------------------------------------------------------------
void CParticle::Chain(CObject2D::MULTI_TYPE type, const D3DXVECTOR3& pos)
{
	if (m_nCreateTime - m_nCreateTimeOld <= 2)
	{// 加算する
		m_nChain++;
	}

	if (m_nChain > 1 && m_nChain % 4 == 0)
	{// 4の倍数になったら
	 // 敵の種類をランダムで指定
		int nEnemyType = rand() % 2 + 3;

		// お邪魔敵の発生
		CEnemyManager::GetInstance()->Create(type, nEnemyType,pos,0,D3DXCOLOR(1.0f,1.0f,0.0f,1.0f),1);
	}
}

//-----------------------------------------------------------------------------------------------
// 敵との当たり判定
//
// const D3DXVECTOR3& pos → 位置
//-----------------------------------------------------------------------------------------------
void CParticle::CollisionEnemy(const D3DXVECTOR3& pos)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		// オブジェクトのポインタ
		CObject* pObject = nullptr;

		// オブジェクトを取得
		pObject = CObject::GetObject(nCntObject);

		if (pObject == nullptr)
		{// nulltprだったら
			continue;
		}
		else if (pObject->GetObjectType() != EOBJECT_TYPE_ENEMY)
		{// 種類が敵以外だったら
			continue;
		}
		// ダウンキャスト
		CEnemy* pEnemy = (CEnemy*)pObject;

		if (pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE_CIRCLE || pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE_STAR)
		{ // 敵がお邪魔だったら
			continue;
		}
		// 位置を取得する
		D3DXVECTOR3 pEnemyPos = pEnemy->GetPosition();

		// 1P側か2P側かを取得する
		CObject2D::MULTI_TYPE Type = pEnemy->GetPlayerType();

		// 距離の差を求める
		D3DXVECTOR3 PosDis = pEnemyPos - pos;

		// 長さを求める
		float fLength = D3DXVec3Length(&PosDis);

		if (COLLISION_RADIUS >= fLength)
		{// 長さが距離の差よりも短かったら
			//敵の終了
			CEnemyManager::GetInstance()->DeleteEnemy(pEnemy->GetID());
			// 爆発( パーティクル )する
			CParticle::Create(pEnemyPos);
			// 連鎖
			Chain(Type, pEnemyPos);
			break;
		}
	}
}