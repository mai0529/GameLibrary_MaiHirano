//-------------------------------------------
//
// 敵の情報[enemy.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _ENEMY_H_		// 二重インクルード防止
#define _ENEMY_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include "object2D.h"		// 2Dオブジェクト

//-------------------------------------------
// クラス
//-------------------------------------------
class CEnemy : public CObject2D
{
public:
	// 敵の種類
	enum ENEMY_TYPE
	{
		// うさぎ
		ENEMY_TYPE_RABBIT = 0,
		// ねこ
		ENEMY_TYPE_CAT,
		// いぬ
		ENEMY_TYPE_DOG,
		// 丸のお邪魔敵
		ENEMY_TYPE_CIRCLE,
		// 星のお邪魔敵
		ENEMY_TYPE_STAR,
		// 死神
		ENEMY_TYPE_DEATH,
		// ボス
		ENEMY_TYPE_BOSS,
		// 種類の最大数
		ENEMY_TYPE_MAX
	};

	enum ENEMY_STATE
	{
		// 通常状態
		ENEMY_STATE_NORMAL = 0,
		// ダメージ状態
		ENEMY_STATE_DAMAGE,
		// 死亡状態
		ENEMY_STATE_DEATH,
		// 状態の最大数
		ENEMY_STATE_MAX
	};

public:
	// コンストラクタ
	CEnemy();
	// デストラクタ
	~CEnemy() override;

	// 生成
	static CEnemy* Create(const D3DXVECTOR3& pos);

	// 初期化
	HRESULT Init() override;
	// 終了
	void Uninit() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

	// ヒット
	void Hit(int nDamage);

	// 格納先の番号を設定
	void SetID(int nID);
	// 格納先番号の取得
	int GetID();

	// サイズを設定
	void SetSize(const D3DXVECTOR3& size);
	// 移動量を設定
	void SetMove(const D3DXVECTOR3& move);

	// 速度を設定
	void SetSpeed(float fSpeed);
	// 速度を取得
	float GetSpeed();

	// 寿命の設定
	void SetLife(int nLife);
	// 寿命の取得
	int GetLife();

	// 種類の設定
	void SetEnemyType(ENEMY_TYPE type);
	// 種類の取得
	ENEMY_TYPE GetEnemyType();

	// 状態の取得
	ENEMY_STATE GetState();

	// 出現経過時間を取得
	int GetAppeaTime();

private:
	// 状態
	void State();
	// 点滅
	void Blink();
	// 壁の当たり判定
	bool CollisionWall(D3DXVECTOR3 pos);
	// 画面外判定
	bool OffScreen(D3DXVECTOR3 pos);

private:
	// 格納先の番号
	int m_nID;
	// 前の位置
	D3DXVECTOR3 m_posOld;
	// サイズ
	D3DXVECTOR3 m_size;
	// 移動量
	D3DXVECTOR3 m_move;
	// カラー
	D3DXCOLOR m_col;
	// 速度
	float m_fSpeed;
	// 寿命
	int m_nLife;
	// 敵の種類
	ENEMY_TYPE m_type;
	// 状態
	ENEMY_STATE m_state;
	// 出現経過カウント
	int m_nAppeaTime;
	// 点滅カウンター
	int m_nCntBlink;
};

#endif		// _ENEMY_H_