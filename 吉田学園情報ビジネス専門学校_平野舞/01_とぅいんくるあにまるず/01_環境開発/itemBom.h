//-------------------------------------------
//
// ���e�^�A�C�e���̏��[itemBom.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _ITEMBOM_H_		// ��d�C���N���[�h�h�~
#define _ITEMBOM_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include "item.h"	// �A�C�e��

//-------------------------------------------
// �N���X
//-------------------------------------------
class CItemBom : public CItem
{
public:
	// �R���X�g���N�^
	CItemBom();
	// �f�X�g���N�^
	~CItemBom() override;

	// ����
	static CItemBom* Create(const D3DXVECTOR3& pos);

	// ������
	HRESULT Init(const D3DXVECTOR3& pos) override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

	// �G��S������
	void DeleteEnemy(MULTI_TYPE player);

private:
	// �ړ�
	D3DXVECTOR3 Move();

private:
	// �ړ��J�E���g
	int m_nCntMove;
};

#endif		// _ITEMBOM_H_