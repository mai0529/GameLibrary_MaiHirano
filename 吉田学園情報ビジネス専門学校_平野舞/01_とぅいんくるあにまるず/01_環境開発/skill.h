//-------------------------------------------
//
// スキル情報[skill.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _SKILL_H_		// 二重インクルード防止
#define _SKILL_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include "object2D.h"	// 2Dオブジェクト

//-------------------------------------------
// クラス
//-------------------------------------------
class CSkill : public CObject2D
{
public:
	// コンストラクタ
	CSkill();
	// デストラクタ
	~CSkill() override;

	// 生成
	static CSkill* Create(const D3DXVECTOR3& pos);

	// 初期化
	HRESULT Init(const D3DXVECTOR3& pos) override;
	// 終了
	void Uninit() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

	// 防御スキル
	void Defense();
	// スキル
	void Skill(MULTI_TYPE player);

	// 無敵状態かどうかを取得
	bool GetInvincible();

private:
	// 表示するかどうか
	bool m_bDis;
	// スキルを使用したかどうか
	bool m_bUse;
	// 敵カウント
	int m_nCntEnemy;
	// 無敵状態かどうか
	bool m_bInvincible;
	// 無敵時間
	int m_nInvincible;
};

#endif		// _SKILL_H_