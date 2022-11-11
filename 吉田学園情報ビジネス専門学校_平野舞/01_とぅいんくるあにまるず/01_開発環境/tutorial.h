//-------------------------------------------
//
// �`���[�g���A�����[tutorial.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _TUTORIAL_H_		// ��d�C���N���[�h�h�~
#define _TUTORIAL_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include <d3dx9.h>		// �`�揈���ɕK�v

//-------------------------------------------
// �O���錾
//-------------------------------------------
// �w�i
class CBg;
// �I�u�W�F�N�g2D
class CObject2D;

//-------------------------------------------
// �N���X
//-------------------------------------------
class CTutorial
{
private:
	// �R���X�g���N�^
	CTutorial();
public:
	// �f�X�g���N�^
	~CTutorial();

	// �C���X�^���X�̐���
	static void CreateInstance();
	// �C���X�^���X�̎擾
	static CTutorial* GetInstance();

	// ������
	HRESULT Init();
	// �I��
	void Uninit();
	// �X�V
	void Update();

private:
	// �^�C�g���N���X�̃|�C���^
	static CTutorial* m_Instance;
	// �e�N�X�`����
	static char* m_cFileName[];

	// �w�i�̃|�C���^
	CBg* m_pBg;
	// �I�u�W�F�N�g2D�̃|�C���^
	CObject2D* m_pObject2D;

	// a�l�𑫂����ǂ����t���O
	bool m_bColAdd;
};

#endif		// _TUTORIAL_H_