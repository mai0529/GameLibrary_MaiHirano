//-------------------------------------------
//
// 爆弾型アイテムの情報[itemBom.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _ITEMBOM_H_		// 二重インクルード防止
#define _ITEMBOM_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include "item.h"	// アイテム

//-------------------------------------------
// クラス
//-------------------------------------------
class CItemBom : public CItem
{
public:
	// コンストラクタ
	CItemBom();
	// デストラクタ
	~CItemBom() override;

	// 生成
	static CItemBom* Create(const D3DXVECTOR3& pos);

	// 初期化
	HRESULT Init(const D3DXVECTOR3& pos) override;
	// 終了
	void Uninit() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

	// 敵を全部消す
	void DeleteEnemy(MULTI_TYPE player);

private:
	// 移動
	D3DXVECTOR3 Move();

private:
	// 移動カウント
	int m_nCntMove;
};

#endif		// _ITEMBOM_H_