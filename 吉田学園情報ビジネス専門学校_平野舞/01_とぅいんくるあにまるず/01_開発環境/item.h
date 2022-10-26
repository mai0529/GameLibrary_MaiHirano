//-------------------------------------------
//
// アイテムの情報[item.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _ITEM_H_		// 二重インクルード防止
#define _ITEM_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include "object2D.h"	// 2Dオブジェクト

//-------------------------------------------
// クラス
//-------------------------------------------
class CItem : public CObject2D
{
public:
	enum ITEM_TYPE
	{
		// 爆弾
		ITEM_TYPE_BOM = 0,
		// お邪魔発生
		ITEM_TYPE_OBSTACLE,
		// 種類の最大数
		ITEM_TYPE_MAX
	};

public:
	// コンストラクタ
	CItem();
	// デストラクタ
	~CItem() override;

	// 生成
	static CItem* Create(const D3DXVECTOR3& pos);

	// 初期化
	HRESULT Init(const D3DXVECTOR3& pos) override;
	// 終了
	void Uninit() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

	// 格納先の番号の設定
	void SetID(int nID);
	// 格納先の番号取得
	int GetID();

	// 移動量を設定
	void SetMove(const D3DXVECTOR3& move);

	// 種類の設定
	void SetItemType(ITEM_TYPE type);
	// 種類の取得
	ITEM_TYPE GetItemType();

private:
	// 格納先の番号
	int m_nID;
	// 移動量
	D3DXVECTOR3 m_move;
	// アイテムの種類
	ITEM_TYPE m_type;
};

#endif		// _ITEM_H_