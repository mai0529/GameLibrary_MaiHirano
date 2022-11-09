//-------------------------------------------
//
// �w�i�̏��[bg.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _BG_H_		// ��d�C���N���[�h�h�~
#define _BG_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include "object.h"		// �I�u�W�F�N�g

//-------------------------------------------
// �O���錾
//-------------------------------------------
// �I�u�W�F�N�g2D
class CObject2D;

//-------------------------------------------
// �N���X
//-------------------------------------------
class CBg : public CObject
{
private:
	// �摜�̍ő吔
	static const int MAX_TEXTURE = 2;

public:
	// �w�i�̎��
	enum ETYPE_BG
	{
		// �����Ȃ�
		ETYPE_BG_NONE = -1,
		// �^�C�g��
		ETYPE_BG_TITLE,
		// �`���[�g���A��
		ETYPE_BG_TUTORIAL,
		// �Q�[��
		ETYPE_BG_GAME,
		// �|�[�Y
		ETYPE_BG_PAUSE,
		// ���U���g
		ETYPE_BG_RESULT,
		// ��ނ̍ő吔
		ETYPE_BG_MAX
	};

	// �I����
	enum TUTORIAL_PAGE
	{
		// �����Ȃ�
		TUTORIAL_PAGE_NONE = -1,
		// 1�y�[�W��
		TUTORIAL_PAGE_ONE,
		// 2�y�[�W��
		TUTORIAL_PAGE_SECOND,
		// �ő吔
		TUTORIAL_PAGE_MAX
	};

public:
	// �R���X�g���N�^
	CBg();
	// �f�X�g���N�^
	virtual ~CBg();

	// ����
	static CBg* Create(ETYPE_BG type);

	// ������
	HRESULT Init() override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;
	
	// ��ނ̐ݒ�
	void SetType(ETYPE_BG type);
	// ��ނ̎擾
	ETYPE_BG GetType();

	// �y�[�W�̐ݒ�
	void SetPage(TUTORIAL_PAGE page);
	// �y�[�W�̎擾
	TUTORIAL_PAGE GetPage();

private:
	// ���
	void State();

private:
	// �I�u�W�F�N�g2D�̃|�C���^
	CObject2D* m_paObject2D[MAX_TEXTURE];

	// �e�N�X�`����V���W(�c)
	float m_fTexV;
	// ���
	ETYPE_BG m_nType;
	// �`���[�g���A���̃y�[�W
	TUTORIAL_PAGE m_page;
};

#endif		// _BG_H_