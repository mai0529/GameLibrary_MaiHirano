//-------------------------------------------
//
// ボス敵の情報[enemyBoss.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _ENEMYBOSS_H_		// 二重インクルード防止
#define _ENEMYBOSS_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include "enemy.h"	// 2Dオブジェクト

//-------------------------------------------
// クラス
//-------------------------------------------
class CEnemyBoss : public CEnemy
{
public:
	// コンストラクタ
	CEnemyBoss();
	// デストラクタ
	~CEnemyBoss() override;

	// 生成
	static CEnemyBoss* Create(const D3DXVECTOR3& pos);
	
	// 初期化
	HRESULT Init(const D3DXVECTOR3& pos) override;
	// 終了
	void Uninit() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

private:
	// 移動
	void Move();

private:
	// アニメーション用カウント
	int m_nCntAnim;
	// 現在のアニメーション
	int m_nNowPatternAnim;
};

#endif		// _ENEMYBOSS_H_