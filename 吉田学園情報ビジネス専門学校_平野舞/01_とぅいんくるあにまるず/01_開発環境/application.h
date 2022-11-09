//-------------------------------------------
//
// �A�v���P�[�V�������[application.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _APPLICATION_H_		// ��d�C���N���[�h�h�~
#define _APPLICATION_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include <d3dx9.h>		// �`�揈���ɕK�v

//-------------------------------------------
// �O���錾
//-------------------------------------------
// �����_�����O
class CRenderer;

//-------------------------------------------
// �N���X
//-------------------------------------------
class CApplication
{
public:
	// �e���
	enum MODE
	{

		// �^�C�g��
		MODE_TITLE = 0,
		// �`���[�g���A��
		MODE_TUTORIAL,
		// �Q�[��
		MODE_GAME,
		// �|�[�Y
		MODE_PAUSE,
		// ���U���g
		MODE_RESULT,
		// ���[�h�̍ő吔
		MODE_MAX
	};

public:
	// �R���X�g���N�^
	CApplication();
	// �f�X�g���N�^
	~CApplication();

	// ������
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	// �I��
	void Uninit();
	// �X�V
	void Update();
	// �`��
	void Draw();

	// �����_�����O�|�C���^�̎擾
	static CRenderer* GetRenderer();

	// ���[�h�̐ݒ�
	static void SetMode(MODE mode);
	// ���[�h�̎擾
	static MODE GetMode();

private:
	// �����_�����O�̃|�C���^
	static CRenderer* m_pRenderer;
	// ���[�h
	static MODE m_mode;
};

#endif		// _APPLICATION_H_