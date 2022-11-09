//-------------------------------------------
//
// いぬ型敵の情報[enemyDog.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _ENEMYDOG_H_		// 二重インクルード防止
#define _ENEMYDOG_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include "enemy.h"	// 2Dオブジェクト

//-------------------------------------------
// クラス
//-------------------------------------------
class CEnemyDog : public CEnemy
{
public:
	// コンストラクタ
	CEnemyDog();
	// デストラクタ
	~CEnemyDog() override;

	// 生成
	static CEnemyDog* Create(const D3DXVECTOR3& pos);
	
	// 初期化
	HRESULT Init() override;
	// 終了
	void Uninit() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

private:
	// 移動
	void Move();
};

#endif		// _ENEMYDOG_H_