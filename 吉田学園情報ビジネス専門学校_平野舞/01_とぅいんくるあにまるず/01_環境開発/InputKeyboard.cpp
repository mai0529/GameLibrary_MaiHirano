//-----------------------------------------------------------------------------------------------
//
// �L�[�{�[�h����[InputKeyboard.cpp]
// Author : ���앑
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �C���N���[�h
//-----------------------------------------------------------------------------------------------
#include "InputKeyboard.h"		// ����

//-----------------------------------------------------------------------------------------------
// �萔�錾
//-----------------------------------------------------------------------------------------------
// ���s�[�g�Ԋu
static const int KEY_REPEAT_INTERVAL = 20;

//-----------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------------------------
CInputKeyboard::CInputKeyboard()
	:m_pInput(nullptr), m_Device(nullptr),m_nCntRepeat(0)
{

}

//-----------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CInputKeyboard::~CInputKeyboard()
{

}

//-------------------------------------------------------------------------------------------------------------
// ������
//
// HINSTANCE hInstance �� �C���X�^���X�n���h�����w��
// HWND hWnd		   �� �E�C���h�E�n���h�����w��
//-------------------------------------------------------------------------------------------------------------
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, nullptr)))
	{
		return E_FAIL;
	}

	// ���̓f�o�C�X�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_Device, nullptr)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_Device->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_Device->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �ւ̃A�N�Z�X�����l��
	m_Device->Acquire();

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �I��
//-----------------------------------------------------------------------------------------------
void CInputKeyboard::Uninit()
{
	// ���̓f�o�C�X�̔j��
	if (m_Device != nullptr)
	{// �A�N�Z�X����j��
		m_Device->Unacquire();
		m_Device->Release();
		m_Device = nullptr;
	}

	// DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}
}

//-----------------------------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------------------------
void CInputKeyboard::Update()
{
	// ���͏��
	BYTE aKeyState[MAX_KEY];

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_Device->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
		{
			// �g���K�[����ۑ�
			m_aStateTrigger[nCntKey] = (m_aState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			// �����[�X����ۑ�
			m_aStateRelease[nCntKey] = (m_aState[nCntKey] ^ aKeyState[nCntKey]) & ~aKeyState[nCntKey];
			// �v���X����ۑ�
			m_aState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
		m_Device->Acquire();
	}
}

//-----------------------------------------------------------------------------------------------
// �v���X�����擾
//
// int nKey �� �L�[�{�[�h��key���w��
//-----------------------------------------------------------------------------------------------
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aState[nKey] & 0x80) ? true : false;
}

//-----------------------------------------------------------------------------------------------
// �g���K�[�����擾
//
// int nKey �� �L�[�{�[�h��key���w��
//-----------------------------------------------------------------------------------------------
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aStateTrigger[nKey] & 0x80) ? true : false;
}

//-----------------------------------------------------------------------------------------------
// �����[�X�����擾
//
// int nKey �� �L�[�{�[�h��key���w��
//-----------------------------------------------------------------------------------------------
bool CInputKeyboard::GetRelease(int nKey)
{
	return (m_aStateRelease[nKey] & 0x80) ? true : false;
}

//-----------------------------------------------------------------------------------------------
// ���s�[�g�����擾
//
// int nKey �� �L�[�{�[�h��key���w��
//-----------------------------------------------------------------------------------------------
bool CInputKeyboard::GetRepeat(int nKey)
{
	if (GetPress(nKey))
	{// �����ꂽ��
		// �J�E���g�𑝂₷
		m_nCntRepeat++;

		if (GetPress(nKey) && m_nCntRepeat == KEY_REPEAT_INTERVAL)
		{
			// �J�E���g��0�ɖ߂�
			m_nCntRepeat = 0;
			return true;
		}
		else if (GetRelease(nKey))
		{// �L�[�𗣂�����
			// �J�E���g��0�ɖ߂�
			m_nCntRepeat = 0;
		}
	}
	return false;
}