//-------------------------------------------
//
// �������^�G�̏��[enemyRabbit.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _ENEMYRABBIT_H_		// ��d�C���N���[�h�h�~
#define _ENEMYRABBIT_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include "enemy.h"	// 2D�I�u�W�F�N�g

//-------------------------------------------
// �N���X
//-------------------------------------------
class CEnemyRabbit : public CEnemy
{
public:
	// �R���X�g���N�^
	CEnemyRabbit();
	// �f�X�g���N�^
	~CEnemyRabbit() override;

	// ����
	static CEnemyRabbit* Create(const D3DXVECTOR3& pos);
	
	// ������
	HRESULT Init(const D3DXVECTOR3& pos) override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

private:
	// 1P���ړ�
	void OneMove();
	// 2P���ړ�
	void SecondMove();

private:
	// ���x
	float m_fSpeed;
	// �J�E���g
	int m_nCntMove;
	// �o���J�E���g
	int m_nCntApeer;
	// �����擾�������ǂ���
	bool m_bGet;
};

#endif		// _ENEMYRABBIT_H_