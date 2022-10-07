//-------------------------------------------
//
// ���z�R���g���[���[���[VirtualController.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _VIRTUALCONTROLLER_H_		// ��d�C���N���[�h�h�~
#define _VIRTUALCONTROLLER_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include <Windows.h>		// WindowsAPI�ɕK�v
#include <d3dx9.h>			// �`�揈���ɕK�v

//-------------------------------------------
// �O���錾
//-------------------------------------------
// �L�[�{�[�h
class CInputKeyboard;
// �W���C�p�b�h
class CJoypad;

//-------------------------------------------
// �N���X
//-------------------------------------------
class CVController
{
public:
	// ���z�L�[
	enum VIRTUAL_KEY
	{
		// ��
		VIRTUAL_KEY_UP = 0,
		// ��
		VIRTUAL_KEY_DOWN,
		// ��
		VIRTUAL_KEY_LEFT,
		// �E
		VIRTUAL_KEY_RIGHT,
		// F
		VIRTUAL_KEY_A,
		// SPACE
		VIRTUAL_KEY_B,
		// ENTER
		VIRTUAL_KEY_START,
		// ���z�L�[�̍ő吔
		VIRTUAL_KEY_MAX
	};

	// ���z�X�e�B�b�N
	enum VIRTUAL_STICK
	{
		// �X�e�B�b�N����ɌX������
		VIRTUAL_STICK_UP = 0,
		// �X�e�B�b�N�����ɌX������
		VIRTUAL_STICK_DOWN,
		// �X�e�B�b�N�����ɌX������
		VIRTUAL_STICK_LEFT,
		// �X�e�B�b�N���E�ɌX������
		VIRTUAL_STICK_RIGHT,
		// �ő吔
		VIRTUAL_STICK_MAX
	};

private:
	// �R���X�g���N�^
	CVController();

public:
	// �f�X�g���N�^
	~CVController();

	// �C���X�^���X�̐���
	static void CreateInstance();
	// �C���X�^���X�̎擾
	static CVController* GetInstance();

	// ������
	void Init(HINSTANCE hInstance, HWND hWnd);
	// �I��
	void Uninit();
	// �X�V
	void Update();

	// �v���X���̎擾
	bool GetPress(int nPlayer,int nKey);
	// �g���K�[���̎擾
	bool GetTrigger(int nPlayer,int nKey);
	// �����[�X���̎擾
	bool GetRelease(int nPlayer,int nKey);
	// ���s�[�g���̎擾
	bool GetRepeat(int nPlayer,int nKey);
	// �X�e�B�b�N�v���X���̎擾
	bool GetStickPress(int nPlayer,int nKey);
	// �X�e�B�b�N�̎΂ߏ����擾
	D3DXVECTOR3 GetStickDir(int nPlayer);

private:
	// ���z�R���g���[���[�̃|�C���^
	static CVController* m_pVController;
	// 1P�̃L�[�{�[�h�[�L�[
	static int m_nKeyboardKey_1P[VIRTUAL_KEY_MAX];
	// 2P�̃L�[�{�[�h�[�L�[
	static int m_nKeyboardKey_2P[VIRTUAL_KEY_MAX];
	// �W���C�p�b�h�L�[
	static int m_JoypadKey[VIRTUAL_KEY_MAX];
	// �W���C�p�b�h�̃X�e�B�b�N
	static int m_JoypadStick[VIRTUAL_STICK_MAX];

	// �L�[�{�[�h�̃|�C���^
	CInputKeyboard* m_pKeyboard;
	// �W���C�p�b�h�̃|�C���^
	CJoypad* m_pJoypad;
};

#endif	// _VIRTUALCONTROLLER_H_