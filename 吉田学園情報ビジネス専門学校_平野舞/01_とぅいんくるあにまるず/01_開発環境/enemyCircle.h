//-------------------------------------------
//
// ������܌^�G�̏��[enemyCircle.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _ENEMYCIRCLE_H_		// ��d�C���N���[�h�h�~
#define _ENEMYCIRCLE_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include "enemy.h"	// 2D�I�u�W�F�N�g

//-------------------------------------------
// �N���X
//-------------------------------------------
class CEnemyCircle : public CEnemy
{
public:	
	// �R���X�g���N�^
	CEnemyCircle();
	// �f�X�g���N�^
	~CEnemyCircle() override;

	// ����
	static CEnemyCircle* Create(const D3DXVECTOR3& pos);

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
	// �ړ��ʂ�ݒ肵�����ǂ���
	bool m_bSetMove;
	// ��ʏ�ɓ����������ǂ���
	bool m_bAttack;
};

#endif		// _ENEMYCIRCLE_H_