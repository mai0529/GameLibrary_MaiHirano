//-------------------------------------------
//
// フェード情報[fade.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _FADE_H_		// 二重インクルード防止
#define _FADE_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include <d3dx9.h>			// 描画処理に必要
#include "application.h"	// アプリケーション

//-------------------------------------------
// 前方宣言
//-------------------------------------------
class CObject2D;

//-------------------------------------------
// クラス
//-------------------------------------------
class CFade
{
public:
	enum FADE
	{
		// 何もしていない状態
		FADE_NONE = 0,
		// フェードイン状態
		FADE_IN,
		// フェードアウト状態
		FADE_OUT,
		// フェードの最大数
		FADE_MAX
	};

private:
	// コンストラクタ
	explicit CFade();
public:
	// デストラクタ
	~CFade();

	// インスタンスの生成
	static void CreateInstance();
	// インスタンスの取得
	static CFade* GetInstance();

	// 初期化
	void Init(CApplication::MODE modeNext);
	// 終了
	void Uninit();
	// 更新
	void Update();

	// 設定
	void SetFade(CApplication::MODE modeNext);
	// 情報の取得
	FADE GetFade();

private:
	// フェードクラスのポインタ
	static CFade* m_Instance;
	// 2Dオブジェクトのポインタ
	static CObject2D* m_pObject2D;
	// フェードの状態
	FADE m_fade;
	// 次のモード
	CApplication::MODE m_modeNext;
};

#endif		// _TITLE_H_