//-------------------------------------------
//
// 弾の情報[bullet.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _BULLET_H_		// 二重インクルード防止
#define _BULLET_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include "object2D.h"		// 2Dオブジェクト

//-------------------------------------------
// 前方宣言
//-------------------------------------------
class CEffect;		// エフェクト

//-------------------------------------------
// クラス
//-------------------------------------------
class CBullet : public CObject2D
{
public:
	// コンストラクタ
	CBullet();
	// デストラクタ
	~CBullet() override;

	// 生成
	static CBullet* Create(MULTI_TYPE playerType,const D3DXVECTOR3& pos);

	// 初期化
	HRESULT Init(const D3DXVECTOR3& pos) override;
	// 終了
	void Uninit() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

private:
	// 当たり判定
	void Collision(const D3DXVECTOR3& pos);

private:
	// エフェクトのポインタ
	static CEffect* m_pEffect;

	// 移動量
	D3DXVECTOR3 m_move;
	// 寿命
	int m_nLife;
};

#endif		// _BULLET_H_
