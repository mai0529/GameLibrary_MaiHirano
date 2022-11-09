//-----------------------------------------------------------------------------------------------
//
// お邪魔型アイテムの処理[enemyObstacle.cpp]
// Author : 平野舞
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// インクルードファイル
//-----------------------------------------------------------------------------------------------
#include "itemObstacle.h"		// お邪魔型アイテム
#include "application.h"		// アプリケーション
#include "renderer.h"			// レンダリング
#include "enemyManager.h"		// 敵マネージャー
#include "TextureFileName.h"	// 画像のファイル名

//-----------------------------------------------------------------------------------------------
// 定数宣言
//-----------------------------------------------------------------------------------------------
// 移動量
static const float ITEM_OBSTACLE_MOVING = 1.0f;

//-----------------------------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------------------------
CItemObstacle::CItemObstacle()
{

}

//-----------------------------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------------------------
CItemObstacle::~CItemObstacle()
{

}

//-----------------------------------------------------------------------------------------------
// 生成
//-----------------------------------------------------------------------------------------------
CItemObstacle* CItemObstacle::Create(const D3DXVECTOR3& pos)
{
	// ポインタクラスを宣言
	CItemObstacle* pItemObstacle = new CItemObstacle;

	if (pItemObstacle != nullptr)
	{// もしnullptrではなかったら
		// 位置
		pItemObstacle->SetPosition(pos);
		// 初期化
		pItemObstacle->Init();
	}

	return pItemObstacle;
}

//-----------------------------------------------------------------------------------------------
// 初期化
//
// const D3DXVECTOR3& pos → 最初に表示する座標位置
//-----------------------------------------------------------------------------------------------
HRESULT CItemObstacle::Init()
{
	// テクスチャの設定
	CObject2D::LoadTexture(TEX_ITEM_OBSTACLE);
	// 種類
	CItem::SetItemType(ITEM_TYPE_OBSTACLE);

	CItem::Init();

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// 終了
//-----------------------------------------------------------------------------------------------s
void CItemObstacle::Uninit()
{
	CItem::Uninit();
}

//-----------------------------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------------------------
void CItemObstacle::Update()
{
	// 移動量の初期化
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 移動量
	move.y = ITEM_OBSTACLE_MOVING;

	// 移動量を設定
	CItem::SetMove(move);

	CItem::Update();
}

//-----------------------------------------------------------------------------------------------
// 描画
//-----------------------------------------------------------------------------------------------
void CItemObstacle::Draw()
{
	CItem::Draw();
}

//-----------------------------------------------------------------------------------------------
// 敵の発生
//-----------------------------------------------------------------------------------------------
void CItemObstacle::GenerationEnemy(MULTI_TYPE player, const D3DXVECTOR3& pos)
{
	// 敵の種類をランダムで指定
	int nEnemyType = rand() % 2 + 3;

	// お邪魔敵の発生
	CEnemyManager::GetInstance()->Create(player, nEnemyType, pos,0,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),1);
}