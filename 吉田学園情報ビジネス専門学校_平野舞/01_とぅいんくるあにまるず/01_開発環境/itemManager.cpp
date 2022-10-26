//---------------------------------------------------------------------------------
//
// アイテムマネージャーの処理[itemManager.cpp]
// Author : 平野舞
//
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// 定数宣言
//---------------------------------------------------------------------------------
// テキストファイル
#define TEXT_ITEM		("data/TEXT/item.txt")

//---------------------------------------------------------------------------------
// インクルードファイル
//---------------------------------------------------------------------------------
#include <stdio.h>				// 外部ファイル読み込み用
#include "itemManager.h"		// アイテムマネージャー
#include "itemBom.h"			// 爆弾型アイテム
#include "itemObstacle.h"		// お邪魔型アイテム
#include "time.h"				// タイマー

//---------------------------------------------------------------------------------
// 定数宣言
//---------------------------------------------------------------------------------
// 1P側と2P側の距離
static const float ITEM_DIS = 700.0f;

//---------------------------------------------------------------------------------
// 静的メンバ変数宣言
//---------------------------------------------------------------------------------
// 敵マネージャーのポインタ
CItemManager* CItemManager::m_Instance = nullptr;

//---------------------------------------------------------------------------------
//	コンストラクタ
//---------------------------------------------------------------------------------
CItemManager::CItemManager()
	:m_nCntFileItem(0), m_nNowCntItem(0)
{
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		// 出現カウント
		m_aFile[nCntItem].nCntApper = 0;
		// 位置
		m_aFile[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// 種類
		m_aFile[nCntItem].nType = CItem::ITEM_TYPE_BOM;
	}

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		m_pItem[nCntItem] = nullptr;
	}
}

//---------------------------------------------------------------------------------
// デストラクタ
//---------------------------------------------------------------------------------
CItemManager::~CItemManager()
{

}

//---------------------------------------------------------------------------------
// インスタンスの生成
//---------------------------------------------------------------------------------
void CItemManager::CreateInstance()
{
	if (m_Instance == nullptr)
	{// nullptrだったら
	 // メモリを生成
		m_Instance = new CItemManager;
	}
}

//---------------------------------------------------------------------------------
// インスタンスの取得
//---------------------------------------------------------------------------------
CItemManager* CItemManager::GetInstance()
{
	if (m_Instance != nullptr)
	{// nullptrではなかったら
		return m_Instance;
	}

	return nullptr;
}

//---------------------------------------------------------------------------------
// アイテムの生成
//---------------------------------------------------------------------------------
void CItemManager::Create(MULTI_TYPE player, int nType, D3DXVECTOR3 pos)
{
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (m_pItem[nCntItem] == nullptr)
		{// nullptrだったら
			switch (nType)
			{
				// 爆弾
			case CItem::ITEM_TYPE_BOM:
				m_pItem[nCntItem] = CItemBom::Create(pos);
				break;
				// お邪魔
			case CItem::ITEM_TYPE_OBSTACLE:
				m_pItem[nCntItem] = CItemObstacle::Create(pos);
				break;
				// その他
			default:
				break;
			}

			// 格納先の番号
			m_pItem[nCntItem]->SetID(nCntItem);

			// 1P側か2P側か
			m_pItem[nCntItem]->SetPlayerType(player);

			break;
		}
	}
}

//---------------------------------------------------------------------------------
// 初期化
//---------------------------------------------------------------------------------
void CItemManager::Init()
{
	// 外部ファイルの読み込み
	Load();
}

//---------------------------------------------------------------------------------
// 終了
//---------------------------------------------------------------------------------
void CItemManager::Uninit()
{
	if (m_Instance != nullptr)
	{// nullptrではなかったら
	 // メモリを削除する
		delete m_Instance;

		// nullptrにする
		m_Instance = nullptr;
	}
}

//---------------------------------------------------------------------------------
// 更新
//---------------------------------------------------------------------------------
void CItemManager::Update()
{
	if (m_nNowCntItem <= m_nCntFileItem && CTime::GetInstance()->GetTime() == m_aFile[m_nNowCntItem].nCntApper)
	{
		// 1P側
		CItemManager::Create(MULTI_TYPE_ONE, m_aFile[m_nNowCntItem].nType, m_aFile[m_nNowCntItem].pos);
		// 2P側
		CItemManager::Create(MULTI_TYPE_SECOND, m_aFile[m_nNowCntItem].nType, D3DXVECTOR3(m_aFile[m_nNowCntItem].pos.x + ITEM_DIS, m_aFile[m_nNowCntItem].pos.y, 0.0f));

		// カウントを増やす
		m_nNowCntItem++;
	}
}

//-----------------------------------------------------------------------------------------------
// アイテムの処理
//
// ITEM_TYPE type → アイテムの種類
//-----------------------------------------------------------------------------------------------
void CItemManager::Item(int nCntItem,MULTI_TYPE player, CItem::ITEM_TYPE type)
{
	switch (type)
	{
	case CItem::ITEM_TYPE_BOM:		// 爆弾
	{
		// 情報を取得
		CItemBom* pBom = CItemManager::GetInstance()->GetItemBom(nCntItem);

		if (pBom != nullptr)
		{// nullptrではなかったら
			// 削除
			pBom->DeleteEnemy(player);
		}
	}
		break;
	case CItem::ITEM_TYPE_OBSTACLE:	// お邪魔
	{
		// 情報を取得
		CItemObstacle* pObstacle = CItemManager::GetInstance()->GetItemObstacle(nCntItem);

		if (pObstacle != nullptr)
		{// nullptrではなかったら
			// お邪魔敵を生成
			pObstacle->GenerationEnemy(player, pObstacle->GetPosition());
		}
	}
		break;
	default:
		break;
	}
}

//---------------------------------------------------------------------------------
// アイテムの削除
//---------------------------------------------------------------------------------
void CItemManager::ItemDelete(int nCntItem)
{
	if (m_pItem[nCntItem] != nullptr)
	{// nullptrではなかったら
		// 終了
		m_pItem[nCntItem]->Uninit();

		// nullptrにする
		m_pItem[nCntItem] = nullptr;
	}

}

//---------------------------------------------------------------------------------
// アイテムのポインタ情報を取得
//---------------------------------------------------------------------------------
CItemBom* CItemManager::GetItemBom(int nCntItem)
{
	if (m_pItem[nCntItem] != nullptr && m_pItem[nCntItem]->GetItemType() == CItem::ITEM_TYPE_BOM)
	{// nullptrではない、種類が爆弾だったら
		CItemBom* pBom = (CItemBom*)m_pItem[nCntItem];

		return pBom;
	}

	return nullptr;
}

//---------------------------------------------------------------------------------
// お邪魔アイテムのポインタ情報を取得
//---------------------------------------------------------------------------------
CItemObstacle* CItemManager::GetItemObstacle(int nCntItem)
{
	if (m_pItem[nCntItem] != nullptr && m_pItem[nCntItem]->GetItemType() == CItem::ITEM_TYPE_OBSTACLE)
	{// nullptrではない、種類が爆弾だったら
		CItemObstacle* pObstacle = (CItemObstacle*)m_pItem[nCntItem];

		return pObstacle;
	}

	return nullptr;
}

//---------------------------------------------------------------------------------
// 外部ファイル読み込み用
//---------------------------------------------------------------------------------
void CItemManager::Load()
{
	char cData[125];

	// ファイルを開く
	FILE* pFile = fopen(TEXT_ITEM, "r");

	if (pFile == nullptr)
	{// ファイルが開けなかったら
		printf("ファイルが開けませんでした。");
		return;
	}

	while (1)
	{
		// 文字を読み込む
		fscanf(pFile, "%s", &cData[0]);

		if (strcmp(&cData[0], "ITEMSET") == 0)
		{// ENEMYSETの文字があったら
			do
			{
				// 文字を読み込む
				fscanf(pFile, "%s", &cData[0]);

				if (strcmp(&cData[0], "COUNTER") == 0)
				{// 出現カウンター
					fscanf(pFile, "%s", &cData[0]);
					fscanf(pFile, "%d", &m_aFile[m_nCntFileItem].nCntApper);
				}
				else if (strcmp(&cData[0], "POS") == 0)
				{// 位置
					fscanf(pFile, "%s", &cData[0]);
					fscanf(pFile, "%f", &m_aFile[m_nCntFileItem].pos.x);
					fscanf(pFile, "%f", &m_aFile[m_nCntFileItem].pos.y);
					fscanf(pFile, "%f", &m_aFile[m_nCntFileItem].pos.z);
				}
				else if (strcmp(&cData[0], "TYPE") == 0)
				{// 種類
					fscanf(pFile, "%s", &cData[0]);
					fscanf(pFile, "%d", &m_aFile[m_nCntFileItem].nType);
				}
			} while (strcmp(&cData[0], "END_ITEMSET") != 0);
			// カウントする
			m_nCntFileItem++;
		}
		if (strcmp(&cData[0], "END_SCRIPT") == 0)
		{// END_ENEMYSETの文字があったら
			break;
		}
	}
}