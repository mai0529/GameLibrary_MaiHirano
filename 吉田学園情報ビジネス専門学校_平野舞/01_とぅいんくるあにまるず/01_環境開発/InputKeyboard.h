//-------------------------------------------
//
// キーボード情報[InputKeyboard.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _INPUTKEYBOARD_H_		// 二重インクルード防止
#define _INPUTKEYBOARD_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#define DIRECTINPUT_VERSION	(0x800)		// ビルド時の警告対処用
#include <dinput.h>						// 入力処理に必要

//-------------------------------------------
// 入力クラス
//-------------------------------------------
class CInputKeyboard
{
private:		// 定数
	// キーの最大数
	static const int MAX_KEY = 256;

public:		// 関数
	// コンストラクタ
	CInputKeyboard();
	// デストラクタ
	~CInputKeyboard();

	// 初期化
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	// 終了
	void Uninit();
	// 更新
	void Update();
	// プレス情報の取得
	bool GetPress(int nKey);
	// トリガー情報の取得
	bool GetTrigger(int nKey);
	// リリース情報の取得
	bool GetRelease(int nKey);
	// リピート情報の取得
	bool GetRepeat(int nKey);

private:	// 変数
	// DirectInputオブジェクトへのポインタ
	LPDIRECTINPUT8 m_pInput;
	// 入力デバイス(キーボード)へのポインタ
	LPDIRECTINPUTDEVICE8 m_Device;
	// プレス情報
	BYTE m_aState[MAX_KEY];
	// トレス情報
	BYTE m_aStateTrigger[MAX_KEY];
	// リリース情報
	BYTE m_aStateRelease[MAX_KEY];
	// リピート用カウント
	int m_nCntRepeat;
};

#endif		// _INPUTKEYBOARD_H_
