//-----------------------------------------------------------------------------------------------
//
// コントローラーの情報[Joypad.cpp]
// Author:平野舞
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
//インクルードファイル
//-----------------------------------------------------------------------------------------------
#include "joypad.h"		//コントローラー

//-----------------------------------------------------------------------------------------------
// 定数宣言
//-----------------------------------------------------------------------------------------------
// リピート間隔
static const int JOYPAD_REPEAT_INTERVAL = 20;

//-----------------------------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------------------------
CJoypad::CJoypad()
{
	for (int nCntJoypad = 0; nCntJoypad < MAX_PLAYER; nCntJoypad++)
	{
		m_bConnect[nCntJoypad] = false;
		m_nCntRepeat[nCntJoypad] = 0;
	}
}

//-----------------------------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------------------------
CJoypad::~CJoypad()
{
}

//-----------------------------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------------------------
HRESULT CJoypad::Init()
{
	// メモリのクリア
	ZeroMemory(&m_StatePress, sizeof(XINPUT_STATE));

	// メモリのクリア
	ZeroMemory(&m_StateTrigger, sizeof(XINPUT_STATE));

	// XInputのステートを設定(有効にする)
	XInputEnable(true);

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// 終了
//-----------------------------------------------------------------------------------------------
void CJoypad::Uninit()
{
	// XInputのステートを設定(無効にする)
	XInputEnable(false);
}

//-----------------------------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------------------------
void CJoypad::Update()
{
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		// ジョイパッドの入力情報
		XINPUT_STATE JoyKeyState[MAX_PLAYER];

		// ジョイパッドの情報を取得
		if (XInputGetState(nCount, &JoyKeyState[nCount]) == ERROR_SUCCESS)
		{
			// ボタンのトリガー情報を保存
			m_StateTrigger[nCount].Gamepad.wButtons = (m_StatePress[nCount].Gamepad.wButtons ^ JoyKeyState[nCount].Gamepad.wButtons)
				& JoyKeyState[nCount].Gamepad.wButtons;
			// ボタンのリリース情報を保存
			m_StateRelease[nCount].Gamepad.wButtons = (m_StatePress[nCount].Gamepad.wButtons ^ JoyKeyState[nCount].Gamepad.wButtons)
				& ~JoyKeyState[nCount].Gamepad.wButtons;
			// ボタンのプレス情報を保存
			m_StatePress[nCount] = JoyKeyState[nCount];

			// 繋がっている
			m_bConnect[nCount] = true;
		}
		else if (XInputGetState(nCount, &JoyKeyState[nCount]) != ERROR_SUCCESS)
		{// 繋がっていない
			m_bConnect[nCount] = false;
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------------
// ボタンプレス情報を取得
//
// int nKey	   → ボタンを指定、controller.hにマクロの記載あり
//------------------------------------------------------------------------------------------------------------------------
bool CJoypad::GetPress(int nPlayer, int nKey)
{
	if (m_bConnect[nPlayer])
	{// 繋がっていたら
		return (m_StatePress[nPlayer].Gamepad.wButtons & nKey) ? true : false;
	}

	return false;
}

//-------------------------------------------------------------------------------------------------------------------
// ボタントリガー情報を取得
//
// int nKey →ボタンを指定、controller.hにマクロの記載あり
//------------------------------------------------------------------------------------------------------------------
bool CJoypad::GetTrigger(int nPlayer, int nKey)
{
	if (m_bConnect[nPlayer])
	{// 繋がっていたら
		return (m_StateTrigger[nPlayer].Gamepad.wButtons & nKey) ? true : false;
	}
	
	return false;
}

//-------------------------------------------------------------------------------------------------------------------
// ボタントリガー情報を取得
//
// int nKey →ボタンを指定、controller.hにマクロの記載あり
//------------------------------------------------------------------------------------------------------------------
bool CJoypad::GetRelease(int nPlayer, int nKey)
{
	if (m_bConnect[nPlayer])
	{// 繋がっていたら
		return (m_StateRelease[nPlayer].Gamepad.wButtons & nKey) ? true : false;
	}
	
	return false;
}

//-------------------------------------------------------------------------------------------------------------------
//
// ボタントリガー情報を取得
//
// int nKey →ボタンを指定、controller.hにマクロの記載あり
//------------------------------------------------------------------------------------------------------------------
bool CJoypad::GetRepeat(int nPlayer, int nKey)
{
	if (m_bConnect[nPlayer])
	{// 繋がっていたら
		if (GetPress(nPlayer, nKey))
		{// 押されたら
			//カウントを増やす
			m_nCntRepeat[nPlayer]++;

			if (GetPress(nPlayer, nKey) && m_nCntRepeat[nPlayer] == JOYPAD_REPEAT_INTERVAL)
			{
				// カウントを0に戻す
				m_nCntRepeat[nPlayer] = 0;
				return true;
			}
			else if (GetRelease(nPlayer, nKey))
			{
				// カウントを0に戻す
				m_nCntRepeat[nPlayer] = 0;
			}
		}
	}

	return false;
}

//---------------------------------------------------------------------------------------------------------------------
// スティックプレス情報を取得
//
// int nKey    → スティックの傾ける向きを指定、
//					controller.hにenum型で記載あり
//---------------------------------------------------------------------------------------------------------------------
bool CJoypad::GetStickPress(int nPlayer,int nKey)
{
	if (m_bConnect[nPlayer])
	{// 繋がっていたら
		// スティックのデッドゾーンの処理
		if ((m_StatePress[nPlayer].Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
			&& m_StatePress[nPlayer].Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			&& (m_StatePress[nPlayer].Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
				&& m_StatePress[nPlayer].Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
		{// 値を0にする
			m_StatePress[nPlayer].Gamepad.sThumbLX = 0;
			m_StatePress[nPlayer].Gamepad.sThumbLY = 0;
		}

		if (nKey == STICK_LEFT && m_StatePress[nPlayer].Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{// スティックの左が押された
			return true;
		}

		if (nKey == STICK_RIGHT && m_StatePress[nPlayer].Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{// スティックの右が押された
			return true;
		}

		if (nKey == STICK_DOWN && m_StatePress[nPlayer].Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{// スティックの下が押された
			return true;
		}

		if (nKey == STICK_UP && m_StatePress[nPlayer].Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{// スティックの上が押された
			return true;
		}
	}

	// 結果を返す
	return false;
}

//---------------------------------------------------------------------------------------------------------------------
// スティックの斜め入力を取得
//
// --使い方---
// D3DXVECTOR3 □□ = GetControllerStickDir(int nPlayer)　で呼び出し
// g_player.pos.x += □□.x * 速度  で斜め対応化
// g_player.pos.z += □□.y * 速度  で斜め対応化
//----------------------------------------------------------------------------------------------------------------------
D3DXVECTOR3 CJoypad::GetStickDir(int nPlayer)
{
	if (m_bConnect[nPlayer])
	{// 繋がっていたら
		D3DXVECTOR3 StickAngle(m_StatePress[nPlayer].Gamepad.sThumbLX, m_StatePress[nPlayer].Gamepad.sThumbLY, 0.0f);

		// 角度を1にする
		D3DXVec3Normalize(&StickAngle, &StickAngle);

		// 値を返す
		return StickAngle;
	}

	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}