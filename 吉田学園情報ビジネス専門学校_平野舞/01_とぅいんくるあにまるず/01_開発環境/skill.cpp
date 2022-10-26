//-----------------------------------------------------------------------------------------------
//
// スキル処理[skill.cpp]
// Author : 平野舞
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// インクルードファイル
//-----------------------------------------------------------------------------------------------
#include "skill.h"			// スキル
#include "enemy.h"			// 敵
#include "enemyManager.h"	// 敵マネージャー
#include "particle.h"		// パーティクル
#include "TextureFileName.h"	// 画像のファイル名

//-----------------------------------------------------------------------------------------------
// 定数宣言
//-----------------------------------------------------------------------------------------------
// 幅
static const float SKILL_WIDTH = 50.0f;
// 高さ
static const float SKILL_HEIGHT = 50.0f;
// 無敵時間
static const int SKILL_TIME = 300;

//-----------------------------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------------------------
CSkill::CSkill()
	:m_bDis(false), m_bUse(false), m_nCntEnemy(0), m_bInvincible(false), m_nInvincible(0)
{

}

//-----------------------------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------------------------
CSkill::~CSkill()
{

}

//-----------------------------------------------------------------------------------------------
// 生成
//-----------------------------------------------------------------------------------------------
CSkill* CSkill::Create(const D3DXVECTOR3& pos)
{
	// ポインタクラス宣言
	CSkill* pSkill = new CSkill;

	if (pSkill != nullptr)
	{// nullptrではなかったら
		// 初期化する
		pSkill->Init(pos);
	}

	return pSkill;
}

//-----------------------------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------------------------
HRESULT CSkill::Init(const D3DXVECTOR3& pos)
{
	// 表示する
	m_bDis = true;
	// 無敵時間
	m_nInvincible = SKILL_TIME;
	//オブジェクトタイプを設定
	SetObjectType(EOBJECT_TYPE::EOBJECT_TYPE_SKILL);
	// 親の設定
	SetObjectParent(EOBJECT_PARENT::EOBJECT_PARENT_GAME);
	// テクスチャの設定
	CObject2D::LoadTexture(TEX_SKILL);
	// サイズ
	CObject2D::SetSize(D3DXVECTOR3(SKILL_WIDTH, SKILL_HEIGHT, 0.0f));

	CObject2D::Init(pos);

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// 終了
//-----------------------------------------------------------------------------------------------
void CSkill::Uninit()
{
	CObject2D::Uninit();
}

//-----------------------------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------------------------
void CSkill::Update()
{
	if (m_bInvincible)
	{// 無敵状態だったら
		// カウントを減らす
		m_nInvincible--;
	}

	if (m_nInvincible <= 0)
	{// カウントが0以下になったら
		// 無敵状態ではない
		m_bInvincible = false;
	}
}

//-----------------------------------------------------------------------------------------------
// 描画
//-----------------------------------------------------------------------------------------------
void CSkill::Draw()
{
	if (m_bDis)
	{
		CObject2D::Draw();
	}
}

//-----------------------------------------------------------------------------------------------
// 防御スキル
//-----------------------------------------------------------------------------------------------
void CSkill::Defense()
{
	if (!m_bUse)
	{
		// 無敵状態
		m_bInvincible = true;
		// 表示しない
		m_bDis = false;
		// スキルを使用した
		m_bUse = true;
	}
}

//-----------------------------------------------------------------------------------------------
// スキル
//-----------------------------------------------------------------------------------------------
void CSkill::Skill(MULTI_TYPE player)
{
	if (m_bUse)
	{// スキルを使用していたら
		return;
	}

	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		// オブジェクトのポインタ
		CObject* pObject = nullptr;

		// オブジェクトを取得
		pObject = CObject::GetObject(nCntObject);

		if (pObject != nullptr)
		{// nulltprではなかったら
			if (pObject->GetObjectType() == EOBJECT_TYPE_ENEMY)
			{// 種類が敵だったら
			 // ダウンキャスト
				CEnemy* pEnemy = (CEnemy*)pObject;
				D3DXVECTOR3 EnemyPos = pEnemy->GetPosition();

				switch (pEnemy->GetEnemyType())
				{
					// お邪魔敵
				case CEnemy::ENEMY_TYPE_CIRCLE:
				case CEnemy::ENEMY_TYPE_STAR:
					if (player != pEnemy->GetPlayerType())
					{
						// 敵の終了
						CEnemyManager::GetInstance()->DeleteEnemy(pEnemy->GetID());

						// 爆発( パーティクル )の生成
						CParticle::Create(EnemyPos);
					}

					// 敵の数を加算する
					m_nCntEnemy++;
					break;
					// 死神
				case CEnemy::ENEMY_TYPE_DEATH:
					break;
					// その他の敵
				default:
					if (player == pEnemy->GetPlayerType())
					{
						// 敵の終了
						CEnemyManager::GetInstance()->DeleteEnemy(pEnemy->GetID());

						// 爆発( パーティクル )の生成
						CParticle::Create(EnemyPos);
					}
					// 敵の数を加算する
					m_nCntEnemy++;
					break;
				}
			}
		}
	}

	for (int nCntEnemy = 0; nCntEnemy < (m_nCntEnemy / 4); nCntEnemy++)
	{
		// 位置をランダムで指定
		float fPosX = 0.0f;
		float fPosY = rand() % 400 + 200.0f;

		// 敵の種類をランダムで指定
		int nEnemyType = rand() % 2 + 3;

		switch (player)
		{
			// 1P
		case MULTI_TYPE_ONE:
			fPosX = rand() % 400 + 100.0f;
			break;
			// 2P
		case MULTI_TYPE_SECOND:
			fPosX = rand() % 400 + 700.0f;
			break;
			// その他
		default:
			break;
		}

		// 敵の発生
		CEnemyManager::GetInstance()->Create(player,nEnemyType, D3DXVECTOR3(fPosX, fPosY,0.0f), 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),1);
	}

	// 表示しない
	m_bDis = false;
	// スキルを使用した
	m_bUse = true;
}

//-----------------------------------------------------------------------------------------------
// 無敵状態かどうかを取得
//-----------------------------------------------------------------------------------------------
bool CSkill:: GetInvincible()
{
	return m_bInvincible;
}