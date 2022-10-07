//-------------------------------------------
//
// コントローラー情報[Joypad.h]
// Author:平野舞
//
//-------------------------------------------

#ifndef _JOYPAD_H_		// 二重インクルード防止
#define _JOYPAD_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include <d3dx9.h>			// 描画処理に必要
#include <xinput.h>			// ジョイパッド処理に必要

//-------------------------------------------
// コントローラークラス
//-------------------------------------------
class CJoypad
{
private:
	static const int MAX_PLAYER = 2;
public:
	// スティックの状態
	enum STICK
	{
		// スティックを左に傾けた時
		STICK_LEFT = 0,
		// スティックを右に傾けた時
		STICK_RIGHT,
		// スティックを上に傾けた時
		STICK_UP,
		// スティックを下に傾けた時
		STICK_DOWN,
		// 最大数
		STICK_MAX
	};

public:
	// コンストラクタ
	CJoypad();
	// デストラクタ
	~CJoypad();
	// 初期化
	HRESULT Init();
	// 終了
	void Uninit();
	// 更新
	void Update();
	// プレス情報の取得
	bool GetPress(int nPlayer,int nKey);
	// トリガー情報の取得
	bool GetTrigger(int nPlayer, int nKey);
	// リリース情報の取得
	bool GetRelease(int nPlayer, int nKey);
	// リピート情報の取得
	bool GetRepeat(int nPlayer, int nKey);
	// スティックプレス情報の取得
	bool GetStickPress(int nPlayer, int nKey);
	// スティック斜め入力の情報を取得
	D3DXVECTOR3 GetStickDir(int nPlayer);

private:
	// プレス情報
	XINPUT_STATE m_StatePress[MAX_PLAYER];
	// トリガー情報
	XINPUT_STATE m_StateTrigger[MAX_PLAYER];
	// リリース情報
	XINPUT_STATE m_StateRelease[MAX_PLAYER];
	// コントローラーが繋がっているかどうか
	bool m_bConnect[MAX_PLAYER];
	// リピート用カウンター
	int m_nCntRepeat[MAX_PLAYER];
};
#endif		// _JOYPAD_H_

//Keyボタンのマクロ----------------------------------------------------------
// XINPUT_GAMEPAD_DPAD_UP		→ 十字キーの上ボタン
// XINPUT_GAMEPAD_DPAD_DOWN		→ 十字キーの下ボタン
// XINPUT_GAMEPAD_DPAD_LEFT		→ 十字キーの左ボタン
// XINPUT_GAMEPAD_DPAD_RIGHT	→ 十字キーの右ボタン
// XINPUT_GAMEPAD_A				→ Aボタン
// XINPUT_GAMEPAD_B				→ Bボタン
// XINPUT_GAMEPAD_X				→ Xボタン
// XINPUT_GAMEPAD_Y				→ Yボタン
// XINPUT_GAMEPAD_START			→ STARTボタン
// XINPUT_GAMEPAD_BACK			→ BACKボタン