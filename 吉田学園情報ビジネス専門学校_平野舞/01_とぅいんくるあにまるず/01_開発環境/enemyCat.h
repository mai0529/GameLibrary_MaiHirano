//-------------------------------------------
//
// ねこ型敵の情報[enemyCat.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _ENEMYCAT_H_		// 二重インクルード防止
#define _ENEMYCAT_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include "enemy.h"	// 2Dオブジェクト

//-------------------------------------------
// クラス
//-------------------------------------------
class CEnemyCat : public CEnemy
{
public:
	// コンストラクタ
	CEnemyCat();
	// デストラクタ
	~CEnemyCat() override;

	// 生成
	static CEnemyCat* Create(const D3DXVECTOR3& pos);
	
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

private:
	// 初期位置
	D3DXVECTOR3 m_posStart;
	// 中心
	D3DXVECTOR3 m_Center;
	// 角度
	float m_fAngle;
	// 半径
	float m_fRadius;
	// 情報を取得したかどうか
	bool m_bGet;
};

#endif		// _ENEMYCAT_H_