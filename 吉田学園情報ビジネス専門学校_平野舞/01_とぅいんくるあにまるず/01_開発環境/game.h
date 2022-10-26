//-------------------------------------------
//
// ゲーム情報[game.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _GAME_H_		// 二重インクルード防止
#define _GAME_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include <d3dx9.h>		// 描画処理に必要

//-------------------------------------------
// 前方宣言
//-------------------------------------------
// プレイヤー
class CPlayer;
// ライフ
class CLife;
// スキル
class CSkill;

//-------------------------------------------
// クラス
//-------------------------------------------
class CGame
{
private:
	// プレイヤーの最大数
	static const int MAX_PLAYER = 2;

private:
	// コンストラクタ
	CGame();
public:
	// デストラクタ
	~CGame();

	// インスタンスの生成
	static void CreateInstance();
	// インスタンスの取得
	static CGame* GetInstance();

	// 初期化
	HRESULT Init();
	// 終了
	void Uninit();
	// 更新
	void Update();

	// プレイヤーポインタの取得
	static CPlayer* GetPlayer(int nCntPlayer);
	// ライフのポインタを取得
	static CLife* GetLife(int nCntLife);
	// スキルのポインタを取得
	static CSkill* GetSkill(int nCntSkill);

private:
	// ゲームクラスのポインタ
	static CGame* m_Instance;
	// テクスチャ名
	static char* m_cFileName[];

	// プレイヤーのポインタ
	static CPlayer* m_pPlayer[MAX_PLAYER];
	// ライフのポインタ
	static CLife* m_pLife[MAX_PLAYER];
	// スキルのポインタ
	static CSkill* m_pSkill[MAX_PLAYER];
};

#endif		// _GAME_H_