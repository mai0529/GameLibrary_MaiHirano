//-------------------------------------------
//
// アプリケーション情報[application.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _APPLICATION_H_		// 二重インクルード防止
#define _APPLICATION_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include <d3dx9.h>		// 描画処理に必要

//-------------------------------------------
// 前方宣言
//-------------------------------------------
// レンダリング
class CRenderer;

//-------------------------------------------
// クラス
//-------------------------------------------
class CApplication
{
public:
	// 各画面
	enum MODE
	{

		// タイトル
		MODE_TITLE = 0,
		// チュートリアル
		MODE_TUTORIAL,
		// ゲーム
		MODE_GAME,
		// ポーズ
		MODE_PAUSE,
		// リザルト
		MODE_RESULT,
		// モードの最大数
		MODE_MAX
	};

public:
	// コンストラクタ
	CApplication();
	// デストラクタ
	~CApplication();

	// 初期化
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	// 終了
	void Uninit();
	// 更新
	void Update();
	// 描画
	void Draw();

	// レンダリングポインタの取得
	static CRenderer* GetRenderer();

	// モードの設定
	static void SetMode(MODE mode);
	// モードの取得
	static MODE GetMode();

private:
	// レンダリングのポインタ
	static CRenderer* m_pRenderer;
	// モード
	static MODE m_mode;
};

#endif		// _APPLICATION_H_