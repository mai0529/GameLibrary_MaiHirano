//-----------------------------------------------------------------------------------------------
//
// 爆弾型アイテムの処理[enemyBom.cpp]
// Author : 平野舞
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// インクルードファイル
//-----------------------------------------------------------------------------------------------
#include "itemBom.h"			// 爆弾型アイテム
#include "application.h"		// アプリケーション
#include "renderer.h"			// レンダリング
#include "enemyManager.h"		// 敵マネージャー
#include "enemy.h"				// 敵
#include "particle.h"			// パーティクル
#include "TextureFileName.h"	// 画像のファイル名

//-----------------------------------------------------------------------------------------------
// 定数宣言
//-----------------------------------------------------------------------------------------------
// 移動量
static const float ITEM_BOM_MOVING = 1.0f;
// 速度
static const float ITEM_BOM_SPEED = 2.0f;
// 移動距離
static const float ITEM_BOM_MOVE = 2.0f;
// フレーム数
static const int ITEM_BOM_FRAME = 90;

//-----------------------------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------------------------
CItemBom::CItemBom()
	:m_nCntMove(0)
{

}

//-----------------------------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------------------------
CItemBom::~CItemBom()
{

}

//-----------------------------------------------------------------------------------------------
// 生成
//-----------------------------------------------------------------------------------------------
CItemBom* CItemBom::Create(const D3DXVECTOR3& pos)
{
	// ポインタクラスを宣言
	CItemBom* pItemBom = new CItemBom;

	if (pItemBom != nullptr)
	{// もしnullptrではなかったら
	 // 初期化
		pItemBom->Init(pos);
	}

	return pItemBom;
}

//-----------------------------------------------------------------------------------------------
// 初期化
//
// const D3DXVECTOR3& pos → 最初に表示する座標位置
//-----------------------------------------------------------------------------------------------
HRESULT CItemBom::Init(const D3DXVECTOR3& pos)
{
	// テクスチャの設定
	CObject2D::LoadTexture(TEX_ITEM_BOM);

	CItem::Init(pos);

	// 種類を設定
	CItem::SetItemType(ITEM_TYPE_BOM);

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// 終了
//-----------------------------------------------------------------------------------------------
void CItemBom::Uninit()
{
	CItem::Uninit();
}

//-----------------------------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------------------------
void CItemBom::Update()
{
	D3DXVECTOR3 move = Move();

	// 移動量を設定
	CItem::SetMove(move);

	CItem::Update();
}

//-----------------------------------------------------------------------------------------------
// 描画
//-----------------------------------------------------------------------------------------------
void CItemBom::Draw()
{
	CItem::Draw();
}

//-----------------------------------------------------------------------------------------------
// 敵を全部消す
//-----------------------------------------------------------------------------------------------
void CItemBom::DeleteEnemy(MULTI_TYPE player)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		// オブジェクトのポインタ
		CObject* pObject = nullptr;

		// オブジェクトを取得
		pObject = CObject::GetObject(nCntObject);

		if (pObject != nullptr)
		{// nulltprではなかったら
			if (pObject->GetObjectType() == OBJECT_TYPE_ENEMY)
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
					break;
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------------------------
// 移動
//-----------------------------------------------------------------------------------------------
D3DXVECTOR3 CItemBom::Move()
{
	// 移動量の初期化
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 移動量
	move.x = cosf((D3DX_PI / 2.0f) / ITEM_BOM_FRAME * m_nCntMove) * ITEM_BOM_MOVE;
	move.y = ITEM_BOM_MOVING;

	// カウントの加算
	m_nCntMove++;

	return move;
}