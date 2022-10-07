//-------------------------------------------
//
// エフェクトの情報[effect.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _EFFECT_H_		// 二重インクルード防止
#define _EFFECT_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include "object2D.h"	// 2Dオブジェクト

//-------------------------------------------
// クラス
//-------------------------------------------
class CEffect : public CObject2D
{
public:
	// コンストラクタ
	CEffect();
	// デストラクタ
	~CEffect() override;

	// 生成
	static CEffect* Create(const D3DXVECTOR3& pos);

	// 初期化
	HRESULT Init(const D3DXVECTOR3& pos) override;
	// 終了
	void Uninit() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

	// サイズの設定
	void SetSizeEf(D3DXVECTOR3 size);
	// 角度の設定
	void SetAngle(float fAngle);
	// 寿命の設定
	void SetLife(int nLife);

private:
	// 移動量
	D3DXVECTOR3 m_move;
	// サイズ
	D3DXVECTOR3 m_size;
	// 角度
	float m_fAngle;
	// 寿命
	int m_nLife;
};

#endif		// _PLAYER_H_