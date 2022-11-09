//-------------------------------------------
//
// ポーズの情報[pause.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _PAUSE_H_		// 二重インクルード防止
#define _PAUSE_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include <d3dx9.h>		// 描画処理に必要

//-------------------------------------------
// 前方宣言
//-------------------------------------------
// オブジェクト2D
class CObject2D;
// メニュー
class CMenu;

//-------------------------------------------
// クラス
//-------------------------------------------
class CPause
{
private:
	// メニューセレクトの最大数
	static const int MAX_MENU_SELECT = 3;

public:
	// 選択肢
	enum EPAUSE_SELECT
	{
		// 何もなし
		EPAUSE_SELECT_NONE = 0,
		// ゲームに戻る
		EPAUSE_SELECT_GAME_PLAY,
		// ゲームをやり直す
		EPAUSE_SELECT_GAME_REPLAY,
		// 選択肢に戻る
		EPAUSE_SELECT_MENU_RETURN,
		// 最大数
		EPAUSE_SELECT_MAX
	};

private:
	// コンストラクタ
	CPause();
public:
	// デストラクタ
	~CPause();

	// インスタンスの生成
	static void CreateInstance();
	// インスタンスの取得
	static CPause* GetInstance();
	// インスタンスの削除
	void DeleteInstance();

	// 初期化
	HRESULT Init();
	// 終了
	void Uninit();
	// 更新
	void Update();

private:
	// メニューの初期化
	void MenuInit();
	// メニューの更新
	void MenuUpdate();
	// メニューの決定
	void MenuDecision();

private:
	// テクスチャ名
	static char* m_cFileName[];

	// オブジェクト2Dのポインタ
	CObject2D* m_pObject2D;
	// タイトルクラスのポインタ
	static CPause* m_Instance;
	// メニューのポインタ
	static CMenu* m_pMenu[MAX_MENU_SELECT];

	// 選択肢
	EPAUSE_SELECT m_select;
};

#endif		// _PAUSE_H_