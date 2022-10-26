//-------------------------------------------
//
// �^�C�g�����[title.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _TITLE_H_		// ��d�C���N���[�h�h�~
#define _TITLE_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include <d3dx9.h>		// �`�揈���ɕK�v

//-------------------------------------------
// �O���錾
//-------------------------------------------
// ���j���[
class CMenu;

//-------------------------------------------
// �N���X
//-------------------------------------------
class CTitle
{
public:
	// �I����
	enum TITLE_SELECT
	{
		// �����Ȃ�
		TITLE_SELECT_NONE = 0,
		// �Q�[��
		TITLE_SELECT_GAME,
		// �`���[�g���A��
		TITLE_SELECT_TUTORIAL,
		// �ő吔
		TITLE_SELECT_MAX
	};

private:
	// ���j���[�Z���N�g�̍ő吔
	static const int MAX_MENU_SELECT = 2;

private:
	// �R���X�g���N�^
	CTitle();
public:
	// �f�X�g���N�^
	~CTitle();

	// �C���X�^���X�̐���
	static void CreateInstance();
	// �C���X�^���X�̎擾
	static CTitle* GetInstance();

	// ������
	HRESULT Init();
	// �I��
	void Uninit();
	// �X�V
	void Update();

private:
	// �^�C�g���N���X�̃|�C���^
	static CTitle* m_Instance;
	// �e�N�X�`����
	static char* m_cFileName[];
	// ���j���[
	static CMenu* m_pMenu[MAX_MENU_SELECT];

	// �I����
	TITLE_SELECT m_select;
};

#endif		// _TITLE_H_
