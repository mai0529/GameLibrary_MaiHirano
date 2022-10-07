//-----------------------------------------------------------------------------------------------
//
// �R���g���[���[�̏��[Joypad.cpp]
// Author:���앑
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------------------------
#include "joypad.h"		//�R���g���[���[

//-----------------------------------------------------------------------------------------------
// �萔�錾
//-----------------------------------------------------------------------------------------------
// ���s�[�g�Ԋu
static const int JOYPAD_REPEAT_INTERVAL = 20;

//-----------------------------------------------------------------------------------------------
// �R���X�g���N�^
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
// �f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CJoypad::~CJoypad()
{
}

//-----------------------------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------------------------
HRESULT CJoypad::Init()
{
	// �������̃N���A
	ZeroMemory(&m_StatePress, sizeof(XINPUT_STATE));

	// �������̃N���A
	ZeroMemory(&m_StateTrigger, sizeof(XINPUT_STATE));

	// XInput�̃X�e�[�g��ݒ�(�L���ɂ���)
	XInputEnable(true);

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �I��
//-----------------------------------------------------------------------------------------------
void CJoypad::Uninit()
{
	// XInput�̃X�e�[�g��ݒ�(�����ɂ���)
	XInputEnable(false);
}

//-----------------------------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------------------------
void CJoypad::Update()
{
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		// �W���C�p�b�h�̓��͏��
		XINPUT_STATE JoyKeyState[MAX_PLAYER];

		// �W���C�p�b�h�̏����擾
		if (XInputGetState(nCount, &JoyKeyState[nCount]) == ERROR_SUCCESS)
		{
			// �{�^���̃g���K�[����ۑ�
			m_StateTrigger[nCount].Gamepad.wButtons = (m_StatePress[nCount].Gamepad.wButtons ^ JoyKeyState[nCount].Gamepad.wButtons)
				& JoyKeyState[nCount].Gamepad.wButtons;
			// �{�^���̃����[�X����ۑ�
			m_StateRelease[nCount].Gamepad.wButtons = (m_StatePress[nCount].Gamepad.wButtons ^ JoyKeyState[nCount].Gamepad.wButtons)
				& ~JoyKeyState[nCount].Gamepad.wButtons;
			// �{�^���̃v���X����ۑ�
			m_StatePress[nCount] = JoyKeyState[nCount];

			// �q�����Ă���
			m_bConnect[nCount] = true;
		}
		else if (XInputGetState(nCount, &JoyKeyState[nCount]) != ERROR_SUCCESS)
		{// �q�����Ă��Ȃ�
			m_bConnect[nCount] = false;
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------------
// �{�^���v���X�����擾
//
// int nKey	   �� �{�^�����w��Acontroller.h�Ƀ}�N���̋L�ڂ���
//------------------------------------------------------------------------------------------------------------------------
bool CJoypad::GetPress(int nPlayer, int nKey)
{
	if (m_bConnect[nPlayer])
	{// �q�����Ă�����
		return (m_StatePress[nPlayer].Gamepad.wButtons & nKey) ? true : false;
	}

	return false;
}

//-------------------------------------------------------------------------------------------------------------------
// �{�^���g���K�[�����擾
//
// int nKey ���{�^�����w��Acontroller.h�Ƀ}�N���̋L�ڂ���
//------------------------------------------------------------------------------------------------------------------
bool CJoypad::GetTrigger(int nPlayer, int nKey)
{
	if (m_bConnect[nPlayer])
	{// �q�����Ă�����
		return (m_StateTrigger[nPlayer].Gamepad.wButtons & nKey) ? true : false;
	}
	
	return false;
}

//-------------------------------------------------------------------------------------------------------------------
// �{�^���g���K�[�����擾
//
// int nKey ���{�^�����w��Acontroller.h�Ƀ}�N���̋L�ڂ���
//------------------------------------------------------------------------------------------------------------------
bool CJoypad::GetRelease(int nPlayer, int nKey)
{
	if (m_bConnect[nPlayer])
	{// �q�����Ă�����
		return (m_StateRelease[nPlayer].Gamepad.wButtons & nKey) ? true : false;
	}
	
	return false;
}

//-------------------------------------------------------------------------------------------------------------------
//
// �{�^���g���K�[�����擾
//
// int nKey ���{�^�����w��Acontroller.h�Ƀ}�N���̋L�ڂ���
//------------------------------------------------------------------------------------------------------------------
bool CJoypad::GetRepeat(int nPlayer, int nKey)
{
	if (m_bConnect[nPlayer])
	{// �q�����Ă�����
		if (GetPress(nPlayer, nKey))
		{// �����ꂽ��
			//�J�E���g�𑝂₷
			m_nCntRepeat[nPlayer]++;

			if (GetPress(nPlayer, nKey) && m_nCntRepeat[nPlayer] == JOYPAD_REPEAT_INTERVAL)
			{
				// �J�E���g��0�ɖ߂�
				m_nCntRepeat[nPlayer] = 0;
				return true;
			}
			else if (GetRelease(nPlayer, nKey))
			{
				// �J�E���g��0�ɖ߂�
				m_nCntRepeat[nPlayer] = 0;
			}
		}
	}

	return false;
}

//---------------------------------------------------------------------------------------------------------------------
// �X�e�B�b�N�v���X�����擾
//
// int nKey    �� �X�e�B�b�N�̌X����������w��A
//					controller.h��enum�^�ŋL�ڂ���
//---------------------------------------------------------------------------------------------------------------------
bool CJoypad::GetStickPress(int nPlayer,int nKey)
{
	if (m_bConnect[nPlayer])
	{// �q�����Ă�����
		// �X�e�B�b�N�̃f�b�h�]�[���̏���
		if ((m_StatePress[nPlayer].Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
			&& m_StatePress[nPlayer].Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			&& (m_StatePress[nPlayer].Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
				&& m_StatePress[nPlayer].Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
		{// �l��0�ɂ���
			m_StatePress[nPlayer].Gamepad.sThumbLX = 0;
			m_StatePress[nPlayer].Gamepad.sThumbLY = 0;
		}

		if (nKey == STICK_LEFT && m_StatePress[nPlayer].Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{// �X�e�B�b�N�̍��������ꂽ
			return true;
		}

		if (nKey == STICK_RIGHT && m_StatePress[nPlayer].Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{// �X�e�B�b�N�̉E�������ꂽ
			return true;
		}

		if (nKey == STICK_DOWN && m_StatePress[nPlayer].Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{// �X�e�B�b�N�̉��������ꂽ
			return true;
		}

		if (nKey == STICK_UP && m_StatePress[nPlayer].Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{// �X�e�B�b�N�̏オ�����ꂽ
			return true;
		}
	}

	// ���ʂ�Ԃ�
	return false;
}

//---------------------------------------------------------------------------------------------------------------------
// �X�e�B�b�N�̎΂ߓ��͂��擾
//
// --�g����---
// D3DXVECTOR3 ���� = GetControllerStickDir(int nPlayer)�@�ŌĂяo��
// g_player.pos.x += ����.x * ���x  �Ŏ΂ߑΉ���
// g_player.pos.z += ����.y * ���x  �Ŏ΂ߑΉ���
//----------------------------------------------------------------------------------------------------------------------
D3DXVECTOR3 CJoypad::GetStickDir(int nPlayer)
{
	if (m_bConnect[nPlayer])
	{// �q�����Ă�����
		D3DXVECTOR3 StickAngle(m_StatePress[nPlayer].Gamepad.sThumbLX, m_StatePress[nPlayer].Gamepad.sThumbLY, 0.0f);

		// �p�x��1�ɂ���
		D3DXVec3Normalize(&StickAngle, &StickAngle);

		// �l��Ԃ�
		return StickAngle;
	}

	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}