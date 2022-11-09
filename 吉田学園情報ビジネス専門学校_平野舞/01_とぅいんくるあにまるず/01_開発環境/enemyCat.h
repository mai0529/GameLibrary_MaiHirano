//-------------------------------------------
//
// �˂��^�G�̏��[enemyCat.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _ENEMYCAT_H_		// ��d�C���N���[�h�h�~
#define _ENEMYCAT_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include "enemy.h"	// 2D�I�u�W�F�N�g

//-------------------------------------------
// �N���X
//-------------------------------------------
class CEnemyCat : public CEnemy
{
public:
	// �R���X�g���N�^
	CEnemyCat();
	// �f�X�g���N�^
	~CEnemyCat() override;

	// ����
	static CEnemyCat* Create(const D3DXVECTOR3& pos);
	
	// ������
	HRESULT Init() override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

private:
	// �ړ�
	void Move();

private:
	// �����ʒu
	D3DXVECTOR3 m_posStart;
	// ���S
	D3DXVECTOR3 m_Center;
	// �p�x
	float m_fAngle;
	// ���a
	float m_fRadius;
	// �����擾�������ǂ���
	bool m_bGet;
};

#endif		// _ENEMYCAT_H_