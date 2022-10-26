//-------------------------------------------
//
// パーティクルの情報[particle.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _PARTICLE_H_		// 二重インクルード防止
#define _PARTICLE_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include "object.h"		// オブジェクト
#include "common.h"		// 共通

//-------------------------------------------
// 前方宣言
//-------------------------------------------
// エフェクト
class CEffect;

//-------------------------------------------
// クラス
//-------------------------------------------
class CParticle : public CObject
{
public:
	// コンストラクタ
	CParticle();
	// デストラクタ
	virtual ~CParticle();

	// 生成
	static CParticle* Create(const D3DXVECTOR3& pos);

	// 初期化
	HRESULT Init(const D3DXVECTOR3& pos) override;
	// 終了
	void Uninit() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

private:
	// 連鎖
	void Chain(MULTI_TYPE type, const D3DXVECTOR3& pos);
	// 敵との当たり判定
	void CollisionEnemy(const D3DXVECTOR3& pos);

private:
	// テクスチャのポインタ
	static LPDIRECT3DTEXTURE9 m_pTexture;
	// 連鎖数
	static int m_nChain;
	// 生成時間
	static int m_nCreateTime;
	// 前回の生成時間
	static int m_nCreateTimeOld;

	// エフェクトのポインタ
	CEffect* m_paEffect;
	// 位置
	D3DXVECTOR3 m_pos;
	// 寿命
	int m_nLife;
	// サイズ
	float m_AddSize;
};

#endif		// _PARTICLE_H_