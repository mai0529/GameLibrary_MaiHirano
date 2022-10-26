//-------------------------------------------
//
// �L�[�{�[�h���[InputKeyboard.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _INPUTKEYBOARD_H_		// ��d�C���N���[�h�h�~
#define _INPUTKEYBOARD_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#define DIRECTINPUT_VERSION	(0x800)		// �r���h���̌x���Ώ��p
#include <dinput.h>						// ���͏����ɕK�v

//-------------------------------------------
// ���̓N���X
//-------------------------------------------
class CInputKeyboard
{
private:		// �萔
	// �L�[�̍ő吔
	static const int MAX_KEY = 256;

public:		// �֐�
	// �R���X�g���N�^
	CInputKeyboard();
	// �f�X�g���N�^
	~CInputKeyboard();

	// ������
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	// �I��
	void Uninit();
	// �X�V
	void Update();
	// �v���X���̎擾
	bool GetPress(int nKey);
	// �g���K�[���̎擾
	bool GetTrigger(int nKey);
	// �����[�X���̎擾
	bool GetRelease(int nKey);
	// ���s�[�g���̎擾
	bool GetRepeat(int nKey);

private:	// �ϐ�
	// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECTINPUT8 m_pInput;
	// ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
	LPDIRECTINPUTDEVICE8 m_Device;
	// �v���X���
	BYTE m_aState[MAX_KEY];
	// �g���X���
	BYTE m_aStateTrigger[MAX_KEY];
	// �����[�X���
	BYTE m_aStateRelease[MAX_KEY];
	// ���s�[�g�p�J�E���g
	int m_nCntRepeat;
};

#endif		// _INPUTKEYBOARD_H_
