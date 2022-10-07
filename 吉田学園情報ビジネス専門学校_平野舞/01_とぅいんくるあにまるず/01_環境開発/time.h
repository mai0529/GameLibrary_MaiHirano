//-------------------------------------------
//
// タイマーの情報[time.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _TIME_H_		// 二重インクルード防止
#define _TIME_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include <d3dx9.h>		// 描画処理に必要

//-------------------------------------------
// クラス
//-------------------------------------------
class CTime
{
private:
	// コンストラクタ
	CTime();

public:
	// デストラクタ
	~CTime();

	// インスタンスの生成
	static void CreateInstance();
	// インスタンスの取得
	static CTime* GetInstance();

	// 初期化
	void Init();
	// 終了
	void Uninit();
	// 更新
	void Update();

	// タイマの秒数を取得
	int GetTime();
	// タイマのリセット
	void ResetTime();

private:
	// ポインタ
	static CTime* m_pTime;
	// フレーム数
	int m_nFrame;
	// 秒数
	int m_nTime;
};

#endif		// _TIME_H_