//-------------------------------------------
//
// �A�C�e���̏��[item.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _ITEM_H_		// ��d�C���N���[�h�h�~
#define _ITEM_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include "object2D.h"	// 2D�I�u�W�F�N�g

//-------------------------------------------
// �N���X
//-------------------------------------------
class CItem : public CObject2D
{
public:
	enum ITEM_TYPE
	{
		// ���e
		ITEM_TYPE_BOM = 0,
		// ���ז�����
		ITEM_TYPE_OBSTACLE,
		// ��ނ̍ő吔
		ITEM_TYPE_MAX
	};

public:
	// �R���X�g���N�^
	CItem();
	// �f�X�g���N�^
	~CItem() override;

	// ����
	static CItem* Create(const D3DXVECTOR3& pos);

	// ������
	HRESULT Init(const D3DXVECTOR3& pos) override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

	// �i�[��̔ԍ��̐ݒ�
	void SetID(int nID);
	// �i�[��̔ԍ��擾
	int GetID();

	// �ړ��ʂ�ݒ�
	void SetMove(const D3DXVECTOR3& move);

	// ��ނ̐ݒ�
	void SetItemType(ITEM_TYPE type);
	// ��ނ̎擾
	ITEM_TYPE GetItemType();

private:
	// �i�[��̔ԍ�
	int m_nID;
	// �ړ���
	D3DXVECTOR3 m_move;
	// �A�C�e���̎��
	ITEM_TYPE m_type;
};

#endif		// _ITEM_H_