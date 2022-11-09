//-------------------------------------------
//
// お邪魔型アイテムの情報[itemObstacle.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _ITEMOBSTACLE_H_		// 二重インクルード防止
#define _ITEMOBSTACLE_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include "item.h"	// アイテム

//-------------------------------------------
// クラス
//-------------------------------------------
class CItemObstacle : public CItem
{
public:
	// コンストラクタ
	CItemObstacle();
	// デストラクタ
	~CItemObstacle() override;

	// 生成
	static CItemObstacle* Create(const D3DXVECTOR3& pos);

	// 初期化
	HRESULT Init() override;
	// 終了
	void Uninit() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

	// 敵の発生
	void GenerationEnemy(MULTI_TYPE player,const D3DXVECTOR3& pos);
};

#endif		// _ITEMOBSTACLE_H_