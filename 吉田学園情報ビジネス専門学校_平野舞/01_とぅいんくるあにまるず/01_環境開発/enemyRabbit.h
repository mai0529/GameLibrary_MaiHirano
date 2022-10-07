//-------------------------------------------
//
// うさぎ型敵の情報[enemyRabbit.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _ENEMYRABBIT_H_		// 二重インクルード防止
#define _ENEMYRABBIT_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include "enemy.h"	// 2Dオブジェクト

//-------------------------------------------
// クラス
//-------------------------------------------
class CEnemyRabbit : public CEnemy
{
public:
	// コンストラクタ
	CEnemyRabbit();
	// デストラクタ
	~CEnemyRabbit() override;

	// 生成
	static CEnemyRabbit* Create(const D3DXVECTOR3& pos);
	
	// 初期化
	HRESULT Init(const D3DXVECTOR3& pos) override;
	// 終了
	void Uninit() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

private:
	// 1P側移動
	void OneMove();
	// 2P側移動
	void SecondMove();

private:
	// 速度
	float m_fSpeed;
	// カウント
	int m_nCntMove;
	// 出現カウント
	int m_nCntApeer;
	// 情報を取得したかどうか
	bool m_bGet;
};

#endif		// _ENEMYRABBIT_H_