//---------------------------------------------------------------------------------
//
// ���z�R���g���[���[[VirtualController.cpp]
// Author : ���앑
//
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//---------------------------------------------------------------------------------
#include"VirtualController.h"	// ���z�R���g���[���[
#include "InputKeyboard.h"		// �L�[�{�[�h
#include "joypad.h"				// �R���g���[���[
#include "common.h"				// ����

//---------------------------------------------------------------------------------
// �ÓI�����o�ϐ��錾
//---------------------------------------------------------------------------------
// ���z�R���g���[���[�̃|�C���^
CVController* CVController::m_pVController = nullptr;

// 1P�̃L�[�{�[�h�[�L�[
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

// 2P�̃L�[�{�[�h�[�L�[
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

// �W���C�p�b�h�L�[
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

// �W���C�p�b�h�̃X�e�B�b�N
int CVController::m_JoypadStick[VIRTUAL_STICK_MAX] = 
{
	// �X�e�B�b�N����ɌX������
	CJoypad::STICK_UP,
	// �X�e�B�b�N�����ɌX������
	CJoypad::STICK_DOWN,
	// �X�e�B�b�N�����ɌX������
	CJoypad::STICK_LEFT,
	// �X�e�B�b�N���E�ɌX������
	CJoypad::STICK_RIGHT
};

//---------------------------------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------------------------------
CVController::CVController()
{

}

//---------------------------------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------------------------------
CVController::~CVController()
{

}

//---------------------------------------------------------------------------------
// �C���X�^���X�̐���
//---------------------------------------------------------------------------------
void CVController::CreateInstance()
{
	if (m_pVController == nullptr)
	{// nullptr��������
		// �������𐶐�����
		m_pVController = new CVController;
	}
}

//---------------------------------------------------------------------------------
// �C���X�^���X�̎擾
//---------------------------------------------------------------------------------
CVController* CVController::GetInstance()
{
	return m_pVController;
}

//---------------------------------------------------------------------------------
// ������
//---------------------------------------------------------------------------------
void CVController::Init(HINSTANCE hInstance, HWND hWnd)
{
	// �L�[�{�[�h�̃������𐶐�����
	m_pKeyboard = new CInputKeyboard;

	if (m_pKeyboard == nullptr)
	{// nullptr��������
		return;
	}

	// �L�[�{�[�h�̏�����
	m_pKeyboard->Init(hInstance, hWnd);

	// �R���g���[���[�̃������𐶐�����
	m_pJoypad = new CJoypad;

	if (m_pJoypad == nullptr)
	{// nullptr��������
		return;
	}

	// �R���g���[���[�̏�����
	m_pJoypad->Init();
}

//---------------------------------------------------------------------------------
// �I��
//---------------------------------------------------------------------------------
void CVController::Uninit()
{
	// �R���g���[���[
	if (m_pJoypad != nullptr)
	{// nullptr�ł͂Ȃ�������
	 // �I��
		m_pJoypad->Uninit();

		// ��������j��
		delete m_pJoypad;

		// nullptr�ɖ߂�
		m_pJoypad = nullptr;
	}

	// �L�[�{�[�h
	if (m_pKeyboard != nullptr)
	{// nullptr�ł͂Ȃ�������
	 // �I��
		m_pKeyboard->Uninit();

		// ��������j��
		delete m_pKeyboard;

		// nullptr�ɖ߂�
		m_pKeyboard = nullptr;
	}

	if (m_pVController != nullptr)
	{// nullptr�ł͂Ȃ�������
		// ��������j��
		delete m_pVController;

		// nullptr�ɖ߂�
		m_pVController = nullptr;
	}
}

//---------------------------------------------------------------------------------
// �X�V
//---------------------------------------------------------------------------------
void CVController::Update()
{
	if (m_pKeyboard != nullptr)
	{// �L�[�{�[�h
		m_pKeyboard->Update();
	}

	if (m_pJoypad != nullptr)
	{// �R���g���[���[
		m_pJoypad->Update();
	}
}

//---------------------------------------------------------------------------------
// �v���X���̎擾
//---------------------------------------------------------------------------------
bool CVController::GetPress(int nPlayer,int nKey)
{
	switch (nPlayer)
	{
	case MULTI_TYPE_ONE - 1:
		if (m_pKeyboard->GetPress(m_nKeyboardKey_1P[nKey]) || m_pJoypad->GetPress(nPlayer, m_JoypadKey[nKey]))
		{// true��������
			return true;
		}
			break;
	case MULTI_TYPE_SECOND - 1:
		if (m_pKeyboard->GetPress(m_nKeyboardKey_2P[nKey]) || m_pJoypad->GetPress(nPlayer, m_JoypadKey[nKey]))
		{// true��������
			return true;
		}
			break;
	}

	return false;
}

//---------------------------------------------------------------------------------
// �g���K�[���̎擾
//---------------------------------------------------------------------------------
bool CVController::GetTrigger(int nPlayer,int nKey)
{
	switch (nPlayer)
	{
	case MULTI_TYPE_ONE - 1:
		if (m_pKeyboard->GetTrigger(m_nKeyboardKey_1P[nKey]) || m_pJoypad->GetTrigger(nPlayer, m_JoypadKey[nKey]))
		{// true��������
			return true;
		}
		break;
	case MULTI_TYPE_SECOND - 1:
		if (m_pKeyboard->GetTrigger(m_nKeyboardKey_2P[nKey]) || m_pJoypad->GetTrigger(nPlayer, m_JoypadKey[nKey]))
		{// true��������
			return true;
		}
		break;
	}

	return false;
}

//---------------------------------------------------------------------------------
// �����[�X���̎擾
//---------------------------------------------------------------------------------
bool CVController::GetRelease(int nPlayer,int nKey)
{
	switch (nPlayer)
	{
	case MULTI_TYPE_ONE - 1:
		if (m_pKeyboard->GetRelease(m_nKeyboardKey_1P[nKey]) || m_pJoypad->GetRelease(nPlayer, m_JoypadKey[nKey]))
		{// true��������
			return true;
		}
		break;
	case MULTI_TYPE_SECOND - 1:
		if (m_pKeyboard->GetRelease(m_nKeyboardKey_2P[nKey]) || m_pJoypad->GetRelease(nPlayer, m_JoypadKey[nKey]))
		{// true��������
			return true;
		}
		break;
	}

	return false;
}

//---------------------------------------------------------------------------------
// ���s�[�g���̎擾
//---------------------------------------------------------------------------------
bool CVController::GetRepeat(int nPlayer,int nKey)
{
	switch (nPlayer)
	{
	case MULTI_TYPE_ONE - 1:
		if (m_pKeyboard->GetRepeat(m_nKeyboardKey_1P[nKey]) || m_pJoypad->GetRepeat(nPlayer, m_JoypadKey[nKey]))
		{// true��������
			return true;
		}
		break;
	case MULTI_TYPE_SECOND - 1:
		if (m_pKeyboard->GetRepeat(m_nKeyboardKey_2P[nKey]) || m_pJoypad->GetRepeat(nPlayer, m_JoypadKey[nKey]))
		{// true��������
			return true;
		}
		break;
	}

	return false;
}

//---------------------------------------------------------------------------------
// �X�e�B�b�N�v���X���̎擾
//---------------------------------------------------------------------------------
bool CVController::GetStickPress(int nPlayer,int nKey)
{
	if (m_pJoypad != nullptr)
	{// �R���g���[���[
		return m_pJoypad->GetStickPress(nPlayer,m_JoypadStick[nKey]);
	}

	return false;
}

//---------------------------------------------------------------------------------
// �X�e�B�b�N�΂ߓ��͂̏����擾
//---------------------------------------------------------------------------------
D3DXVECTOR3 CVController::GetStickDir(int nPlayer)
{
	if (m_pJoypad != nullptr)
	{// �R���g���[���[
		return m_pJoypad->GetStickDir(nPlayer);
	}

	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}