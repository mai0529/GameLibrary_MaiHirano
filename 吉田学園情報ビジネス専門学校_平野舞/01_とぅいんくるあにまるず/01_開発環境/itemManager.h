//-------------------------------------------
//
// アイテムマネージャーの情報[itemManager.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _ITEMMANAGER_H_		// 二重インクルード防止
#define _ITEMMANAGER_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include <d3dx9.h>		// 描画処理に必要

//-------------------------------------------
// インクルード
//-------------------------------------------
#include "object.h"		// オブジェクト
#include "object2D.h"	// オブジェクト2D
#include "item.h"		// 敵

//-------------------------------------------
// 前方宣言
//-------------------------------------------
// 爆弾アイテム
class CItemBom;
// お邪魔アイテム
class CItemObstacle;

//-------------------------------------------
// クラス
//-------------------------------------------
class CItemManager : public CObject
{
private:
	// 敵の最大数
	static const int MAX_ITEM = 20;

private:
	// 外部ファイル読み込みの構造体
	struct File
	{
		// 出現カウンター
		int nCntApper;
		// 位置
		D3DXVECTOR3 pos;
		// 種類
		int nType;
	};

private:
	// コンストラクタ
	CItemManager();

public:
	// デストラクタ
	~CItemManager();

	// インスタンスの生成
	static void CreateInstance();
	// インスタンスの取得
	static CItemManager* GetInstance();

	// 敵の生成
	void Create(CObject2D::MULTI_TYPE player, int yType, D3DXVECTOR3 pos);

	// 初期化
	HRESULT Init() override;
	// 終了
	void Uninit() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

	// アイテムの処理
	void Item(int nCntItem, CObject2D::MULTI_TYPE player, CItem::ITEM_TYPE type);

	// アイテムの削除
	void ItemDelete(int nCntItem);

	// 爆弾アイテムのポインタ情報を取得
	CItemBom* GetItemBom(int nCntItem);
	// お邪魔アイテムのポインタ情報を取得
	CItemObstacle* GetItemObstacle(int nCntItem);

private:
	// 外部ファイル読み込み用
	void Load();

private:
	// 外部ファイル読み込み用
	File m_aFile[MAX_ITEM];
	// 外部ファイル用アイテムカウント
	int m_nCntFileItem;
	// 今のアイテムのカウント
	int m_nNowCntItem;

	// 敵マネージャーのポインタ
	static CItemManager* m_Instance;
	// アイテムクラスのポインタ
	CItem* m_pItem[MAX_ITEM];
};

#endif // _ITEMMANAGER_H_