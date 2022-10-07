//-------------------------------------------
//
// 共通列挙型[common_malti.h]
// Author : 平野舞
//
//-------------------------------------------
#ifndef _COMMON_H_		// 二重インクルード防止
#define _COMMON_H_

//-------------------------------------------
// 1Pか2Pか
//-------------------------------------------
enum MULTI_TYPE
{// 1Pか2Pか
	// 何もなし
	MULTI_TYPE_NONE = 0,
	// 1P
	MULTI_TYPE_ONE,
	// 2P
	MULTI_TYPE_SECOND,
	// 決まりごとの最大数
	COMMAND_TYPE_MAX
};

//-------------------------------------------
// オブジェクト種類
//-------------------------------------------
enum OBJECT_TYPE
{
	// 何もなし
	OBJECT_TYPE_NONE = 0,
	// プレイヤー
	OBJECT_TYPE_PLAYER,
	// ライフ
	OBJECT_TYPE_LIFE,
	// スキル
	OBJECT_TYPE_SKILL,
	// 敵
	OBJECT_TYPE_ENEMY,
	// 弾
	OBJECT_TYPE_BULLET,
	// アイテム
	OBJECT_TYPE_ITEM,
	// 壁
	OBJECT_TYPE_WALL,
	// エフェクト
	OBJECT_TYPE_EFFECT,
	// パーティクル
	OBJECT_TYPE_PARTICLE,
	// メニュー
	OBJECT_TYPE_MENU,
	//種類の最大数
	OBJECT_TYPE_MAX
};

#endif		// _COMMON_H_