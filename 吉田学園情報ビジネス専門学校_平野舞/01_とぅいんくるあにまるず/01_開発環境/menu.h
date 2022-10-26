//-------------------------------------------
//
// ���j���[�̏��[menu.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _MENU_H_		// ��d�C���N���[�h�h�~
#define _MENU_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include "object2D.h"	// 2D�I�u�W�F�N�g

//-------------------------------------------
// �N���X
//-------------------------------------------
class CMenu : public CObject2D
{
public:
	// ���
	enum MENU_STATE
	{
		// ���肳��Ă��Ȃ�
		MENU_STATE_NO_DECISION = 0,
		// ���肳�ꂽ
		MENU_STATE_DECISION,
		// �_��
		MENU_STATE_BLINK,
		// ��ނ̍ő吔
		MENU_STATE_MAX
	};

public:
	// �R���X�g���N�^
	CMenu();
	// �f�X�g���N�^
	~CMenu() override;

	// ����
	static CMenu* Create(const D3DXVECTOR3& pos);

	// ������
	HRESULT Init(const D3DXVECTOR3& pos) override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

	// ��Ԃ̐ݒ�
	void SetState(MENU_STATE state);
	// ��Ԃ̎擾
	MENU_STATE GetState();

private:
	// ���
	void State();

	// ���肵��
	void Decision();
	// �_��
	void Blink();

private:
	// �A�C�e���̎��
	MENU_STATE m_state;
	// �J�E���g
	int m_nCount;
};

#endif		// _MENU_H_