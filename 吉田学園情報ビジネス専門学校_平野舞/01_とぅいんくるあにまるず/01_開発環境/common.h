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
#endif		// _COMMON_H_