//-------------------------------------------
//
// �R���g���[���[���[Joypad.h]
// Author:���앑
//
//-------------------------------------------

#ifndef _JOYPAD_H_		// ��d�C���N���[�h�h�~
#define _JOYPAD_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include <d3dx9.h>			// �`�揈���ɕK�v
#include <xinput.h>			// �W���C�p�b�h�����ɕK�v

//-------------------------------------------
// �R���g���[���[�N���X
//-------------------------------------------
class CJoypad
{
private:
	static const int MAX_PLAYER = 2;
public:
	// �X�e�B�b�N�̏��
	enum STICK
	{
		// �X�e�B�b�N�����ɌX������
		STICK_LEFT = 0,
		// �X�e�B�b�N���E�ɌX������
		STICK_RIGHT,
		// �X�e�B�b�N����ɌX������
		STICK_UP,
		// �X�e�B�b�N�����ɌX������
		STICK_DOWN,
		// �ő吔
		STICK_MAX
	};

public:
	// �R���X�g���N�^
	CJoypad();
	// �f�X�g���N�^
	~CJoypad();
	// ������
	HRESULT Init();
	// �I��
	void Uninit();
	// �X�V
	void Update();
	// �v���X���̎擾
	bool GetPress(int nPlayer,int nKey);
	// �g���K�[���̎擾
	bool GetTrigger(int nPlayer, int nKey);
	// �����[�X���̎擾
	bool GetRelease(int nPlayer, int nKey);
	// ���s�[�g���̎擾
	bool GetRepeat(int nPlayer, int nKey);
	// �X�e�B�b�N�v���X���̎擾
	bool GetStickPress(int nPlayer, int nKey);
	// �X�e�B�b�N�΂ߓ��͂̏����擾
	D3DXVECTOR3 GetStickDir(int nPlayer);

private:
	// �v���X���
	XINPUT_STATE m_StatePress[MAX_PLAYER];
	// �g���K�[���
	XINPUT_STATE m_StateTrigger[MAX_PLAYER];
	// �����[�X���
	XINPUT_STATE m_StateRelease[MAX_PLAYER];
	// �R���g���[���[���q�����Ă��邩�ǂ���
	bool m_bConnect[MAX_PLAYER];
	// ���s�[�g�p�J�E���^�[
	int m_nCntRepeat[MAX_PLAYER];
};
#endif		// _JOYPAD_H_

//Key�{�^���̃}�N��----------------------------------------------------------
// XINPUT_GAMEPAD_DPAD_UP		�� �\���L�[�̏�{�^��
// XINPUT_GAMEPAD_DPAD_DOWN		�� �\���L�[�̉��{�^��
// XINPUT_GAMEPAD_DPAD_LEFT		�� �\���L�[�̍��{�^��
// XINPUT_GAMEPAD_DPAD_RIGHT	�� �\���L�[�̉E�{�^��
// XINPUT_GAMEPAD_A				�� A�{�^��
// XINPUT_GAMEPAD_B				�� B�{�^��
// XINPUT_GAMEPAD_X				�� X�{�^��
// XINPUT_GAMEPAD_Y				�� Y�{�^��
// XINPUT_GAMEPAD_START			�� START�{�^��
// XINPUT_GAMEPAD_BACK			�� BACK�{�^��