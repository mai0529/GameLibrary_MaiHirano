//-------------------------------------------
//
// 死神の情報[enemyDeath.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _ENEMYDEATH_H_		// 二重インクルード防止
#define _ENEMYDEATH_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include "enemy.h"	// 2Dオブジェクト

//-------------------------------------------
// クラス
//-------------------------------------------
class CEnemyDeath : public CEnemy
{
public:
	// コンストラクタ
	CEnemyDeath();
	// デストラクタ
	~CEnemyDeath() override;

	// 生成
	static CEnemyDeath* Create(const D3DXVECTOR3& pos);

	// 初期化
	HRESULT Init() override;
	// 終了
	void Uninit() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

private:
	// ホーミング
	D3DXVECTOR3 Homing();

private:
	// 出現回数
	static int m_nCntAppea;

	// 速度
	float m_fSpeed;
};

#endif		// _ENEMYDEATH_H_