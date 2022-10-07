//-----------------------------------------------------------------------------------------------
//
// キーボード処理[InputKeyboard.cpp]
// Author : 平野舞
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// インクルード
//-----------------------------------------------------------------------------------------------
#include "InputKeyboard.h"		// 入力

//-----------------------------------------------------------------------------------------------
// 定数宣言
//-----------------------------------------------------------------------------------------------
// リピート間隔
static const int KEY_REPEAT_INTERVAL = 20;

//-----------------------------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------------------------
CInputKeyboard::CInputKeyboard()
	:m_pInput(nullptr), m_Device(nullptr),m_nCntRepeat(0)
{

}

//-----------------------------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------------------------
CInputKeyboard::~CInputKeyboard()
{

}

//-------------------------------------------------------------------------------------------------------------
// 初期化
//
// HINSTANCE hInstance → インスタンスハンドルを指定
// HWND hWnd		   → ウインドウハンドルを指定
//-------------------------------------------------------------------------------------------------------------
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, nullptr)))
	{
		return E_FAIL;
	}

	// 入力デバイスの生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_Device, nullptr)))
	{
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(m_Device->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_Device->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// へのアクセス権を獲得
	m_Device->Acquire();

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// 終了
//-----------------------------------------------------------------------------------------------
void CInputKeyboard::Uninit()
{
	// 入力デバイスの破棄
	if (m_Device != nullptr)
	{// アクセス権を破棄
		m_Device->Unacquire();
		m_Device->Release();
		m_Device = nullptr;
	}

	// DirectInputオブジェクトの破棄
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}
}

//-----------------------------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------------------------
void CInputKeyboard::Update()
{
	// 入力情報
	BYTE aKeyState[MAX_KEY];

	// 入力デバイスからデータを取得
	if (SUCCEEDED(m_Device->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
		{
			// トリガー情報を保存
			m_aStateTrigger[nCntKey] = (m_aState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			// リリース情報を保存
			m_aStateRelease[nCntKey] = (m_aState[nCntKey] ^ aKeyState[nCntKey]) & ~aKeyState[nCntKey];
			// プレス情報を保存
			m_aState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		// キーボードへのアクセス権を獲得
		m_Device->Acquire();
	}
}

//-----------------------------------------------------------------------------------------------
// プレス情報を取得
//
// int nKey → キーボードのkeyを指定
//-----------------------------------------------------------------------------------------------
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aState[nKey] & 0x80) ? true : false;
}

//-----------------------------------------------------------------------------------------------
// トリガー情報を取得
//
// int nKey → キーボードのkeyを指定
//-----------------------------------------------------------------------------------------------
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aStateTrigger[nKey] & 0x80) ? true : false;
}

//-----------------------------------------------------------------------------------------------
// リリース情報を取得
//
// int nKey → キーボードのkeyを指定
//-----------------------------------------------------------------------------------------------
bool CInputKeyboard::GetRelease(int nKey)
{
	return (m_aStateRelease[nKey] & 0x80) ? true : false;
}

//-----------------------------------------------------------------------------------------------
// リピート情報を取得
//
// int nKey → キーボードのkeyを指定
//-----------------------------------------------------------------------------------------------
bool CInputKeyboard::GetRepeat(int nKey)
{
	if (GetPress(nKey))
	{// 押されたら
		// カウントを増やす
		m_nCntRepeat++;

		if (GetPress(nKey) && m_nCntRepeat == KEY_REPEAT_INTERVAL)
		{
			// カウントを0に戻す
			m_nCntRepeat = 0;
			return true;
		}
		else if (GetRelease(nKey))
		{// キーを離したら
			// カウントを0に戻す
			m_nCntRepeat = 0;
		}
	}
	return false;
}