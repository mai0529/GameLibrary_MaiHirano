//---------------------------------------------------------------------------------
//
// 仮想コントローラー[VirtualController.cpp]
// Author : 平野舞
//
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// インクルードファイル
//---------------------------------------------------------------------------------
#include"VirtualController.h"	// 仮想コントローラー
#include "InputKeyboard.h"		// キーボード
#include "joypad.h"				// コントローラー
#include "common.h"				// 共通

//---------------------------------------------------------------------------------
// 静的メンバ変数宣言
//---------------------------------------------------------------------------------
// 仮想コントローラーのポインタ
CVController* CVController::m_pVController = nullptr;

// 1Pのキーボードーキー
int CVController::m_nKeyboardKey_1P[VIRTUAL_KEY_MAX] =
{
	DIK_W,
	DIK_S,
	DIK_A,
	DIK_D,
	DIK_F,
	DIK_SPACE,
	DIK_RETURN,
};

// 2Pのキーボードーキー
int CVController::m_nKeyboardKey_2P[VIRTUAL_KEY_MAX] =
{
	DIK_UP,
	DIK_DOWN,
	DIK_LEFT,
	DIK_RIGHT,
	DIK_L,
	DIK_M,
	DIK_RETURN,
};

// ジョイパッドキー
int CVController::m_JoypadKey[VIRTUAL_KEY_MAX] = 
{
	XINPUT_GAMEPAD_DPAD_UP,
	XINPUT_GAMEPAD_DPAD_DOWN,
	XINPUT_GAMEPAD_DPAD_LEFT,
	XINPUT_GAMEPAD_DPAD_RIGHT,
	XINPUT_GAMEPAD_A,
	XINPUT_GAMEPAD_B,
	XINPUT_GAMEPAD_START
};

// ジョイパッドのスティック
int CVController::m_JoypadStick[VIRTUAL_STICK_MAX] = 
{
	// スティックを上に傾けた時
	CJoypad::STICK_UP,
	// スティックを下に傾けた時
	CJoypad::STICK_DOWN,
	// スティックを左に傾けた時
	CJoypad::STICK_LEFT,
	// スティックを右に傾けた時
	CJoypad::STICK_RIGHT
};

//---------------------------------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------------------------------
CVController::CVController()
{

}

//---------------------------------------------------------------------------------
// デストラクタ
//---------------------------------------------------------------------------------
CVController::~CVController()
{

}

//---------------------------------------------------------------------------------
// インスタンスの生成
//---------------------------------------------------------------------------------
void CVController::CreateInstance()
{
	if (m_pVController == nullptr)
	{// nullptrだったら
		// メモリを生成する
		m_pVController = new CVController;
	}
}

//---------------------------------------------------------------------------------
// インスタンスの取得
//---------------------------------------------------------------------------------
CVController* CVController::GetInstance()
{
	return m_pVController;
}

//---------------------------------------------------------------------------------
// 初期化
//---------------------------------------------------------------------------------
void CVController::Init(HINSTANCE hInstance, HWND hWnd)
{
	// キーボードのメモリを生成する
	m_pKeyboard = new CInputKeyboard;

	if (m_pKeyboard == nullptr)
	{// nullptrだったら
		return;
	}

	// キーボードの初期化
	m_pKeyboard->Init(hInstance, hWnd);

	// コントローラーのメモリを生成する
	m_pJoypad = new CJoypad;

	if (m_pJoypad == nullptr)
	{// nullptrだったら
		return;
	}

	// コントローラーの初期化
	m_pJoypad->Init();
}

//---------------------------------------------------------------------------------
// 終了
//---------------------------------------------------------------------------------
void CVController::Uninit()
{
	// コントローラー
	if (m_pJoypad != nullptr)
	{// nullptrではなかったら
	 // 終了
		m_pJoypad->Uninit();

		// メモリを破棄
		delete m_pJoypad;

		// nullptrに戻す
		m_pJoypad = nullptr;
	}

	// キーボード
	if (m_pKeyboard != nullptr)
	{// nullptrではなかったら
	 // 終了
		m_pKeyboard->Uninit();

		// メモリを破棄
		delete m_pKeyboard;

		// nullptrに戻す
		m_pKeyboard = nullptr;
	}

	if (m_pVController != nullptr)
	{// nullptrではなかったら
		// メモリを破棄
		delete m_pVController;

		// nullptrに戻す
		m_pVController = nullptr;
	}
}

//---------------------------------------------------------------------------------
// 更新
//---------------------------------------------------------------------------------
void CVController::Update()
{
	if (m_pKeyboard != nullptr)
	{// キーボード
		m_pKeyboard->Update();
	}

	if (m_pJoypad != nullptr)
	{// コントローラー
		m_pJoypad->Update();
	}
}

//---------------------------------------------------------------------------------
// プレス情報の取得
//---------------------------------------------------------------------------------
bool CVController::GetPress(int nPlayer,int nKey)
{
	switch (nPlayer)
	{
	case MULTI_TYPE_ONE - 1:
		if (m_pKeyboard->GetPress(m_nKeyboardKey_1P[nKey]) || m_pJoypad->GetPress(nPlayer, m_JoypadKey[nKey]))
		{// trueだったら
			return true;
		}
			break;
	case MULTI_TYPE_SECOND - 1:
		if (m_pKeyboard->GetPress(m_nKeyboardKey_2P[nKey]) || m_pJoypad->GetPress(nPlayer, m_JoypadKey[nKey]))
		{// trueだったら
			return true;
		}
			break;
	}

	return false;
}

//---------------------------------------------------------------------------------
// トリガー情報の取得
//---------------------------------------------------------------------------------
bool CVController::GetTrigger(int nPlayer,int nKey)
{
	switch (nPlayer)
	{
	case MULTI_TYPE_ONE - 1:
		if (m_pKeyboard->GetTrigger(m_nKeyboardKey_1P[nKey]) || m_pJoypad->GetTrigger(nPlayer, m_JoypadKey[nKey]))
		{// trueだったら
			return true;
		}
		break;
	case MULTI_TYPE_SECOND - 1:
		if (m_pKeyboard->GetTrigger(m_nKeyboardKey_2P[nKey]) || m_pJoypad->GetTrigger(nPlayer, m_JoypadKey[nKey]))
		{// trueだったら
			return true;
		}
		break;
	}

	return false;
}

//---------------------------------------------------------------------------------
// リリース情報の取得
//---------------------------------------------------------------------------------
bool CVController::GetRelease(int nPlayer,int nKey)
{
	switch (nPlayer)
	{
	case MULTI_TYPE_ONE - 1:
		if (m_pKeyboard->GetRelease(m_nKeyboardKey_1P[nKey]) || m_pJoypad->GetRelease(nPlayer, m_JoypadKey[nKey]))
		{// trueだったら
			return true;
		}
		break;
	case MULTI_TYPE_SECOND - 1:
		if (m_pKeyboard->GetRelease(m_nKeyboardKey_2P[nKey]) || m_pJoypad->GetRelease(nPlayer, m_JoypadKey[nKey]))
		{// trueだったら
			return true;
		}
		break;
	}

	return false;
}

//---------------------------------------------------------------------------------
// リピート情報の取得
//---------------------------------------------------------------------------------
bool CVController::GetRepeat(int nPlayer,int nKey)
{
	switch (nPlayer)
	{
	case MULTI_TYPE_ONE - 1:
		if (m_pKeyboard->GetRepeat(m_nKeyboardKey_1P[nKey]) || m_pJoypad->GetRepeat(nPlayer, m_JoypadKey[nKey]))
		{// trueだったら
			return true;
		}
		break;
	case MULTI_TYPE_SECOND - 1:
		if (m_pKeyboard->GetRepeat(m_nKeyboardKey_2P[nKey]) || m_pJoypad->GetRepeat(nPlayer, m_JoypadKey[nKey]))
		{// trueだったら
			return true;
		}
		break;
	}

	return false;
}

//---------------------------------------------------------------------------------
// スティックプレス情報の取得
//---------------------------------------------------------------------------------
bool CVController::GetStickPress(int nPlayer,int nKey)
{
	if (m_pJoypad != nullptr)
	{// コントローラー
		return m_pJoypad->GetStickPress(nPlayer,m_JoypadStick[nKey]);
	}

	return false;
}

//---------------------------------------------------------------------------------
// スティック斜め入力の情報を取得
//---------------------------------------------------------------------------------
D3DXVECTOR3 CVController::GetStickDir(int nPlayer)
{
	if (m_pJoypad != nullptr)
	{// コントローラー
		return m_pJoypad->GetStickDir(nPlayer);
	}

	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}