//-------------------------------------------
//
// リザルト情報[result.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _RESULT_H_		// 二重インクルード防止
#define _RESULT_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include <d3dx9.h>		// 描画処理に必要

//-------------------------------------------
// 前方宣言
//-------------------------------------------
// オブジェクト2D
class CObject2D;

//-------------------------------------------
// クラス
//-------------------------------------------
class CResult
{
private:
	// コンストラクタ
	CResult();
public:
	// デストラクタ
	~CResult();

	// インスタンスの生成
	static void CreateInstance();
	// インスタンスの取得
	static CResult* GetInstance();

	// 初期化
	HRESULT Init();
	// 終了
	void Uninit();
	// 更新
	void Update();

private:
	// タイトルクラスのポインタ
	static CResult* m_Instance;
	// テクスチャ名
	static char* m_cFileName[];
};

#endif		// _RESULT_H_