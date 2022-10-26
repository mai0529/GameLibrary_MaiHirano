//-------------------------------------------
//
// �t�F�[�h���[fade.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _FADE_H_		// ��d�C���N���[�h�h�~
#define _FADE_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include <d3dx9.h>			// �`�揈���ɕK�v
#include "application.h"	// �A�v���P�[�V����

//-------------------------------------------
// �O���錾
//-------------------------------------------
class CObject2D;

//-------------------------------------------
// �N���X
//-------------------------------------------
class CFade
{
public:
	enum FADE
	{
		// �������Ă��Ȃ����
		FADE_NONE = 0,
		// �t�F�[�h�C�����
		FADE_IN,
		// �t�F�[�h�A�E�g���
		FADE_OUT,
		// �t�F�[�h�̍ő吔
		FADE_MAX
	};

private:
	// �R���X�g���N�^
	explicit CFade();
public:
	// �f�X�g���N�^
	~CFade();

	// �C���X�^���X�̐���
	static void CreateInstance();
	// �C���X�^���X�̎擾
	static CFade* GetInstance();

	// ������
	void Init(CApplication::MODE modeNext);
	// �I��
	void Uninit();
	// �X�V
	void Update();

	// �ݒ�
	void SetFade(CApplication::MODE modeNext);
	// ���̎擾
	FADE GetFade();

private:
	// �t�F�[�h�N���X�̃|�C���^
	static CFade* m_Instance;
	// 2D�I�u�W�F�N�g�̃|�C���^
	static CObject2D* m_pObject2D;
	// �t�F�[�h�̏��
	FADE m_fade;
	// ���̃��[�h
	CApplication::MODE m_modeNext;
};

#endif		// _TITLE_H_