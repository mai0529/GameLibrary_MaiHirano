//-------------------------------------------
//
// 仮想コントローラー情報[VirtualController.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _VIRTUALCONTROLLER_H_		// 二重インクルード防止
#define _VIRTUALCONTROLLER_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include <Windows.h>		// WindowsAPIに必要
#include <d3dx9.h>			// 描画処理に必要

//-------------------------------------------
// 前方宣言
//-------------------------------------------
// キーボード
class CInputKeyboard;
// ジョイパッド
class CJoypad;

//-------------------------------------------
// クラス
//-------------------------------------------
class CVController
{
public:
	// 仮想キー
	enum VIRTUAL_KEY
	{
		// 上
		VIRTUAL_KEY_UP = 0,
		// 下
		VIRTUAL_KEY_DOWN,
		// 左
		VIRTUAL_KEY_LEFT,
		// 右
		VIRTUAL_KEY_RIGHT,
		// F
		VIRTUAL_KEY_A,
		// SPACE
		VIRTUAL_KEY_B,
		// ENTER
		VIRTUAL_KEY_START,
		// 仮想キーの最大数
		VIRTUAL_KEY_MAX
	};

	// 仮想スティック
	enum VIRTUAL_STICK
	{
		// スティックを上に傾けた時
		VIRTUAL_STICK_UP = 0,
		// スティックを下に傾けた時
		VIRTUAL_STICK_DOWN,
		// スティックを左に傾けた時
		VIRTUAL_STICK_LEFT,
		// スティックを右に傾けた時
		VIRTUAL_STICK_RIGHT,
		// 最大数
		VIRTUAL_STICK_MAX
	};

private:
	// コンストラクタ
	CVController();

public:
	// デストラクタ
	~CVController();

	// インスタンスの生成
	static void CreateInstance();
	// インスタンスの取得
	static CVController* GetInstance();

	// 初期化
	void Init(HINSTANCE hInstance, HWND hWnd);
	// 終了
	void Uninit();
	// 更新
	void Update();

	// プレス情報の取得
	bool GetPress(int nPlayer,int nKey);
	// トリガー情報の取得
	bool GetTrigger(int nPlayer,int nKey);
	// リリース情報の取得
	bool GetRelease(int nPlayer,int nKey);
	// リピート情報の取得
	bool GetRepeat(int nPlayer,int nKey);
	// スティックプレス情報の取得
	bool GetStickPress(int nPlayer,int nKey);
	// スティックの斜め情報を取得
	D3DXVECTOR3 GetStickDir(int nPlayer);

private:
	// 仮想コントローラーのポインタ
	static CVController* m_pVController;
	// 1Pのキーボードーキー
	static int m_nKeyboardKey_1P[VIRTUAL_KEY_MAX];
	// 2Pのキーボードーキー
	static int m_nKeyboardKey_2P[VIRTUAL_KEY_MAX];
	// ジョイパッドキー
	static int m_JoypadKey[VIRTUAL_KEY_MAX];
	// ジョイパッドのスティック
	static int m_JoypadStick[VIRTUAL_STICK_MAX];

	// キーボードのポインタ
	CInputKeyboard* m_pKeyboard;
	// ジョイパッドのポインタ
	CJoypad* m_pJoypad;
};

#endif	// _VIRTUALCONTROLLER_H_