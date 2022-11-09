//-------------------------------------------
//
// 星のお邪魔敵の情報[enemyStar.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _ENEMYSTAR_H_		// 二重インクルード防止
#define _ENEMYSTAR_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include "enemy.h"	// 2Dオブジェクト

//-------------------------------------------
// クラス
//-------------------------------------------
class CEnemyStar : public CEnemy
{
public:	
	// コンストラクタ
	CEnemyStar();
	// デストラクタ
	~CEnemyStar() override;

	// 生成
	static CEnemyStar* Create(const D3DXVECTOR3& pos);

	// 初期化
	HRESULT Init() override;
	// 終了
	void Uninit() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

private:
	// 動き
	void Move();

private:
	// 移動量
	D3DXVECTOR3 m_move;
	// 移動量を設定したかどうか
	bool m_bSetMove;
};

#endif		// _ENEMYSTAR_H_