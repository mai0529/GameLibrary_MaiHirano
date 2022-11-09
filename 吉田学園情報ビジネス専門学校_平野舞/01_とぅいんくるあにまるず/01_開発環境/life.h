//-------------------------------------------
//
// ���C�t�̏��[life.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _LIFE_H_		// ��d�C���N���[�h�h�~
#define _LIFE_H_

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
class CLife : public CObject
{
private:
	// ���C�t�̍ő吔
	static const int MAX_LIFE = 3;

public:
	// �R���X�g���N�^
	CLife();
	// �f�X�g���N�^
	~CLife() override;

	// ����
	static CLife* Create(const D3DXVECTOR3& pos);

	// ������
	HRESULT Init();
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

	// �폜����
	void Delete(int nCntLife);

	// �ʒu�̐ݒ�
	void SetPosition(const D3DXVECTOR3& pos);
	// �ʒu�̎擾
	const D3DXVECTOR3& GetPosition();

private:
	// �I�u�W�F�N�g2D�̃|�C���^
	CObject2D* m_paObject2D[MAX_LIFE];

	// �ʒu
	D3DXVECTOR3 m_pos;
};

#endif		// _LIFE_H_