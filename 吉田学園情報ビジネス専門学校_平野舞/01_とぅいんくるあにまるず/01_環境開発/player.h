//-------------------------------------------
//
// プレイヤーの情報[player.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _PLAYER_H_		// 二重インクルード防止
#define _PLAYER_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include "object2D.h"		// 2Dオブジェクト

//-------------------------------------------
// 前方宣言
//-------------------------------------------
// スキル
class CSkill;

//-------------------------------------------
// クラス
//-------------------------------------------
class CPlayer : public CObject2D
{
private:
	// プレイヤーの状態
	enum PLAYER_STATE
	{
		// 通常状態
		PLAYER_STATE_NORMAL = 0,
		// 無敵状態
		PLAYER_STATE_INVINCIBLE,
		// ダメージ状態
		PLAYER_STATE_DAMAGE,
		// 死亡状態
		PLAYER_STATE_DEATH,
		// 状態の最大数
		PLAYER_STATE_MAX
	};

public:
	// コンストラクタ
	CPlayer();
	// デストラクタ
	~CPlayer() override;

	// 生成
	static CPlayer* Create(MULTI_TYPE player,const D3DXVECTOR3& pos);

	// 初期化
	HRESULT Init(const D3DXVECTOR3& pos) override;
	// 終了
	void Uninit() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

	//寿命の取得
	int GetLife();

private:
	// 状態
	void State();
	// ヒット
	void Hit(int nDamage);
	// 点滅
	void Blink();

	// 弾の発射
	void Shoot(int nPlayer,const D3DXVECTOR3& pos);
	// スキル発動
	void Skill(int nPlayer);
	// 移動
	void Move(int nPlayer);

	// 敵との当たり判定
	void CollisionEnemy(const D3DXVECTOR3& pos);
	// アイテムとの当たり判定
	void CollisionItem(const D3DXVECTOR3& pos);
	// 壁との当たり判定
	D3DXVECTOR3 CollisionWall(D3DXVECTOR3 pos);
	// 画面外当たり判定
	D3DXVECTOR3 OffScreen(D3DXVECTOR3 pos);

private:
	// スキル
	CSkill* m_pSkill;
	// 前フレームの位置
	D3DXVECTOR3 m_posOld;
	// 移動量
	D3DXVECTOR3 m_move;
	// 寿命
	int m_nLife;
	// プレイヤーの状態
	PLAYER_STATE m_state;
	// 点滅カウンター
	int m_nCntBlink;
};

#endif		// _PLAYER_H_