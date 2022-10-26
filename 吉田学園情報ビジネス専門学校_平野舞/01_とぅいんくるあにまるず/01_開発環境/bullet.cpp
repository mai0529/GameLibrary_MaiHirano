//-----------------------------------------------------------------------------------------------
//
// 弾の処理[bullet.cpp]
// Author : 平野舞
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// インクルードファイル
//-----------------------------------------------------------------------------------------------
#include "bullet.h"			// プレイヤー
#include "application.h"	// アプリケーション
#include "renderer.h"		// レンダリング
#include "enemy.h"			// 敵
#include "sound.h"			// 音
#include "TextureFileName.h"	// 画像のファイル名

//-----------------------------------------------------------------------------------------------
// 変数変数
//-----------------------------------------------------------------------------------------------
// 幅
static const float BULLET_WIDTH = 40.0f;
// 高さ
static const float BULLET_HEIGHT = 40.0f;
// 移動量
static const float BULLET_MOVING = -4.0f;
// 寿命
static const int BULLET_LIFE = 100;

//-----------------------------------------------------------------------------------------------
// 静的メンバ変数
//-----------------------------------------------------------------------------------------------
// エフェクトのポインタ
CEffect* CBullet::m_pEffect = nullptr;

//-----------------------------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------------------------
CBullet::CBullet()
	:m_move(0.0f, 0.0f, 0.0f), m_nLife(0)
{

}

//-----------------------------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------------------------
CBullet::~CBullet()
{

}

//-----------------------------------------------------------------------------------------------
// 生成
//
// const D3DXVECTOR3& pos → 生成する座標位置
//-----------------------------------------------------------------------------------------------
CBullet* CBullet::Create(MULTI_TYPE playerType, const D3DXVECTOR3& pos)
{
	// ポインタクラスを宣言
	CBullet* pBullet = new CBullet;

	if (pBullet != nullptr)
	{// もしnullptrではなかったら
		// 1Pか2Pか
		pBullet->SetPlayerType(playerType);
	 // 初期化
		pBullet->Init(pos);
	}

	return pBullet;
}

//-----------------------------------------------------------------------------------------------
// 初期化
//
// const D3DXVECTOR3& pos → 最初に表示する座標位置
//-----------------------------------------------------------------------------------------------
HRESULT CBullet::Init(const D3DXVECTOR3& pos)
{
	// 移動量
	m_move.y = BULLET_MOVING;
	// 寿命
	m_nLife = BULLET_LIFE;

	// オブジェクトの種類
	CObject::SetObjectType(EOBJECT_TYPE_BULLET);
	// オブジェクトの親
	CObject::SetObjectParent(EOBJECT_PARENT_GAME);

	// テクスチャの設定
	CObject2D::LoadTexture(TEX_BULLET);

	// サイズ
	CObject2D::SetSize(D3DXVECTOR3(BULLET_WIDTH, BULLET_HEIGHT, 0.0f));

	CObject2D::Init(pos);

	// 色の設定
	switch (CObject2D::GetPlayerType())
	{
		// 1P
	case MULTI_TYPE_ONE:
		CObject2D::SetColor(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
		break;
		// 2P
	case MULTI_TYPE_SECOND:
		CObject2D::SetColor(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
		break;
	}

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// 終了
//-----------------------------------------------------------------------------------------------
void CBullet::Uninit()
{
	CObject2D::Uninit();
}

//-----------------------------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------------------------
void CBullet::Update()
{
	// 位置の取得
	D3DXVECTOR3 pos = CObject2D::GetPosition();

	// 移動量の更新
	pos += m_move;

	// 当たり判定
	Collision(pos);

	//ライフを減らしていく
	m_nLife--;

	if (m_nLife <= 0)
	{// ライフが0になったら
		// 終了する
		Uninit();
	}
	else
	{
		// 位置の更新
		CObject2D::SetPosition(pos);
		CObject2D::UpdatePos();
	}
}

//-----------------------------------------------------------------------------------------------
// 描画
//-----------------------------------------------------------------------------------------------
void CBullet::Draw()
{
	CObject2D::Draw();
}

//-----------------------------------------------------------------------------------------------
// 当たり判定
//-----------------------------------------------------------------------------------------------
void CBullet::Collision(const D3DXVECTOR3& pos)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		// オブジェクトのポインタ
		CObject* pObject = nullptr;

		// オブジェクトを取得
		pObject = CObject::GetObject(nCntObject);

		if (pObject == nullptr)
		{// nulltprだったら
			break;
		}

		if (pObject->GetObjectType() == EOBJECT_TYPE_ENEMY)
		{// 種類が敵ではなかったら
			// ダウンキャスト
			CEnemy* pEnemy = (CEnemy*)pObject;

			// 位置の取得
			D3DXVECTOR3 EnemyPos = pEnemy->GetPosition();
			D3DXVECTOR3 EnemySize = pEnemy->GetSize();

			if ((EnemyPos.x + EnemySize.x >= pos.x - (BULLET_WIDTH / 2.0f)
				&& EnemyPos.x - EnemySize.x <= pos.x + (BULLET_WIDTH / 2.0f)
				&& EnemyPos.y + EnemySize.y >= pos.y - (BULLET_HEIGHT / 2.0f)
				&& EnemyPos.y - EnemySize.y <= pos.y + (BULLET_HEIGHT / 2.0f)))
			{// 当たり判定
				if ((pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE_CIRCLE || pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE_STAR)
					&& pEnemy->GetPlayerType() != GetPlayerType())
				{// お邪魔敵だったら
				 // ライフを0にする
					m_nLife = 0;

					// 敵にヒット
					pEnemy->Hit(1);

					// 音の再生
					CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_ENEMYDAMAGE);
					break;
				}
				else if (pEnemy->GetEnemyType() != CEnemy::ENEMY_TYPE_CIRCLE && pEnemy->GetEnemyType() != CEnemy::ENEMY_TYPE_STAR
					&& CObject2D::GetPlayerType() == pEnemy->GetPlayerType())
				{ // 敵がお邪魔以外だったら
					// ライフを0にする
					m_nLife = 0;

					// 敵にヒット
					pEnemy->Hit(1);

					// 音の再生
					CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_ENEMYDAMAGE);
					break;
				}
			}
		}
	}
}