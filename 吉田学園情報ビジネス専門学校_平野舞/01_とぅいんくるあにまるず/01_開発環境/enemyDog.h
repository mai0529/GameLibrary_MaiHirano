//-------------------------------------------
//
// ���ʌ^�G�̏��[enemyDog.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _ENEMYDOG_H_		// ��d�C���N���[�h�h�~
#define _ENEMYDOG_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include "enemy.h"	// 2D�I�u�W�F�N�g

//-------------------------------------------
// �N���X
//-------------------------------------------
class CEnemyDog : public CEnemy
{
public:
	// �R���X�g���N�^
	CEnemyDog();
	// �f�X�g���N�^
	~CEnemyDog() override;

	// ����
	static CEnemyDog* Create(const D3DXVECTOR3& pos);
	
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
};

#endif		// _ENEMYDOG_H_