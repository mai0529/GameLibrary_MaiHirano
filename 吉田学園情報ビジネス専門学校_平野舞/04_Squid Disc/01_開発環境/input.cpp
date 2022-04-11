//=======================================================
//
//2Dアクションゲーム制作(input.cpp)
//Author:大原隆俊
//
//=======================================================
//===================================================================
//インクルードファイル
//===================================================================
#include "input.h"
#include "main.h"

//マクロ定義
#define NUM_KEY_MAX (256)							//キーの最大数

//グローバル変数
LPDIRECTINPUT8	g_pInput = NULL;					//DirectInputオブジェクトへのポインタ
LPDIRECTINPUTDEVICE8	g_pDevKeyboard = NULL;		//入力デバイス（キーボード）へのポインタ
BYTE	g_aKeyState[NUM_KEY_MAX];					//キーボードのプレス情報
BYTE	g_aKeyStateTrigger[NUM_KEY_MAX];			//キーボードのトリガー情報
XINPUT_STATE g_JoykeyState;							//ゲームパッドのプレス情報
XINPUT_STATE g_JoykeyStateTrigger;					//ゲームパッドのトリガー情報

//===================================================================
//キーボードの初期化処理
//===================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//Directオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//入力デバイス
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットの作成
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードを設定
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//===================================================================
//ジョイパッドの初期化
//===================================================================
HRESULT InitJoypad(void)
{
	//メモリのクリア
	memset(&g_JoykeyState, 0, sizeof(XINPUT_STATE));

	//Xinputのステートの設定（有効活用）
	XInputEnable(true);

	return S_OK;
}

//===================================================================
//キーボード終了処理
//===================================================================
void UninitKeyboard(void)
{
	//入力デバイス破棄
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//===================================================================
//ジョイパッド終了処理
//===================================================================
void UninitJoypad(void)
{
	//Xinputのステートの設定
	XInputEnable(false);
}

//===================================================================
//キーボード更新処理
//===================================================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];	//キーボードの入力情報
	int nCntKey;

	//入力デバイスからデータ取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey])&aKeyState[nCntKey];//キーボードのトリガー情報を保存
			g_aKeyState[nCntKey] = aKeyState[nCntKey];//キーボードのプレス情報を保存
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();		//キーボードのアクセス権を獲得
	}
}

//===================================================================
//ジョイパッド更新
//===================================================================
void UpdateJoypad(void)
{
	XINPUT_STATE joykeystate;

	//ショイパットの状態を取得
	if (XInputGetState(0, &joykeystate) == ERROR_SUCCESS)
	{
		g_JoykeyStateTrigger.Gamepad.wButtons = (g_JoykeyState.Gamepad.wButtons & joykeystate.Gamepad.wButtons) ^ joykeystate.Gamepad.wButtons;			//トリガー処理	
		g_JoykeyState = joykeystate;
	}
}

//===================================================================
//キーボードのプレス情報取得
//===================================================================
bool GetKeyboardPress(int nKey)
{
	return(g_aKeyState[nKey] & 0x80) ? true : false;	//3項演算子(?A:B;)
}

//===================================================================
//キーボードのトリガー情報を取得
//===================================================================
bool GetKeyboardTrigger(int nKey)
{
	return(g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//===================================================================
//ジョイパッドのプレス情報取得
//===================================================================
bool GetJoypadPress(JOYkey key)
{
	return (g_JoykeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//===================================================================
//ジョイパッドトリガー情報を取得
//===================================================================
bool GetJoypadTrigger(JOYkey key)
{
	return (g_JoykeyStateTrigger.Gamepad.wButtons & (0x01 << key)) ? true : false;
}