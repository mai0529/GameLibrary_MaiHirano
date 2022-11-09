//-------------------------------------------
//
// �|�[�Y�̏��[pause.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _PAUSE_H_		// ��d�C���N���[�h�h�~
#define _PAUSE_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include <d3dx9.h>		// �`�揈���ɕK�v

//-------------------------------------------
// �O���錾
//-------------------------------------------
// �I�u�W�F�N�g2D
class CObject2D;
// ���j���[
class CMenu;

//-------------------------------------------
// �N���X
//-------------------------------------------
class CPause
{
private:
	// ���j���[�Z���N�g�̍ő吔
	static const int MAX_MENU_SELECT = 3;

public:
	// �I����
	enum EPAUSE_SELECT
	{
		// �����Ȃ�
		EPAUSE_SELECT_NONE = 0,
		// �Q�[���ɖ߂�
		EPAUSE_SELECT_GAME_PLAY,
		// �Q�[������蒼��
		EPAUSE_SELECT_GAME_REPLAY,
		// �I�����ɖ߂�
		EPAUSE_SELECT_MENU_RETURN,
		// �ő吔
		EPAUSE_SELECT_MAX
	};

private:
	// �R���X�g���N�^
	CPause();
public:
	// �f�X�g���N�^
	~CPause();

	// �C���X�^���X�̐���
	static void CreateInstance();
	// �C���X�^���X�̎擾
	static CPause* GetInstance();
	// �C���X�^���X�̍폜
	void DeleteInstance();

	// ������
	HRESULT Init();
	// �I��
	void Uninit();
	// �X�V
	void Update();

private:
	// ���j���[�̏�����
	void MenuInit();
	// ���j���[�̍X�V
	void MenuUpdate();
	// ���j���[�̌���
	void MenuDecision();

private:
	// �e�N�X�`����
	static char* m_cFileName[];

	// �I�u�W�F�N�g2D�̃|�C���^
	CObject2D* m_pObject2D;
	// �^�C�g���N���X�̃|�C���^
	static CPause* m_Instance;
	// ���j���[�̃|�C���^
	static CMenu* m_pMenu[MAX_MENU_SELECT];

	// �I����
	EPAUSE_SELECT m_select;
};

#endif		// _PAUSE_H_