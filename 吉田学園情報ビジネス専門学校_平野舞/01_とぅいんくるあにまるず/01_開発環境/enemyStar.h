//-------------------------------------------
//
// ���̂��ז��G�̏��[enemyStar.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _ENEMYSTAR_H_		// ��d�C���N���[�h�h�~
#define _ENEMYSTAR_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include "enemy.h"	// 2D�I�u�W�F�N�g

//-------------------------------------------
// �N���X
//-------------------------------------------
class CEnemyStar : public CEnemy
{
public:	
	// �R���X�g���N�^
	CEnemyStar();
	// �f�X�g���N�^
	~CEnemyStar() override;

	// ����
	static CEnemyStar* Create(const D3DXVECTOR3& pos);

	// ������
	HRESULT Init() override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

private:
	// ����
	void Move();

private:
	// �ړ���
	D3DXVECTOR3 m_move;
	// �ړ��ʂ�ݒ肵�����ǂ���
	bool m_bSetMove;
};

#endif		// _ENEMYSTAR_H_