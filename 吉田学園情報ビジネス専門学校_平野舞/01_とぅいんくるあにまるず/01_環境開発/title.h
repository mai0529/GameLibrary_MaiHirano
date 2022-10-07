//-------------------------------------------
//
// タイトル情報[title.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _TITLE_H_		// 二重インクルード防止
#define _TITLE_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include <d3dx9.h>		// 描画処理に必要

//-------------------------------------------
// 前方宣言
//-------------------------------------------
// メニュー
class CMenu;

//-------------------------------------------
// クラス
//-------------------------------------------
class CTitle
{
public:
	// 選択肢
	enum TITLE_SELECT
	{
		// 何もなし
		TITLE_SELECT_NONE = 0,
		// ゲーム
		TITLE_SELECT_GAME,
		// チュートリアル
		TITLE_SELECT_TUTORIAL,
		// 最大数
		TITLE_SELECT_MAX
	};

private:
	// メニューセレクトの最大数
	static const int MAX_MENU_SELECT = 2;

private:
	// コンストラクタ
	CTitle();
public:
	// デストラクタ
	~CTitle();

	// インスタンスの生成
	static void CreateInstance();
	// インスタンスの取得
	static CTitle* GetInstance();

	// 初期化
	HRESULT Init();
	// 終了
	void Uninit();
	// 更新
	void Update();

private:
	// タイトルクラスのポインタ
	static CTitle* m_Instance;
	// テクスチャ名
	static char* m_cFileName[];
	// メニュー
	static CMenu* m_pMenu[MAX_MENU_SELECT];

	// 選択肢
	TITLE_SELECT m_select;
};

#endif		// _TITLE_H_
