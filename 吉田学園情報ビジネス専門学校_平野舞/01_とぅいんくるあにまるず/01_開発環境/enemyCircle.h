//-------------------------------------------
//
// おじゃま型敵の情報[enemyCircle.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _ENEMYCIRCLE_H_		// 二重インクルード防止
#define _ENEMYCIRCLE_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include "enemy.h"	// 2Dオブジェクト

//-------------------------------------------
// クラス
//-------------------------------------------
class CEnemyCircle : public CEnemy
{
public:	
	// コンストラクタ
	CEnemyCircle();
	// デストラクタ
	~CEnemyCircle() override;

	// 生成
	static CEnemyCircle* Create(const D3DXVECTOR3& pos);

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
	// 移動量を設定したかどうか
	bool m_bSetMove;
	// 画面上に当たったかどうか
	bool m_bAttack;
};

#endif		// _ENEMYCIRCLE_H_