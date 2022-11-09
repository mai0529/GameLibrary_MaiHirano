//-------------------------------------------
//
// ���_�̏��[enemyDeath.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _ENEMYDEATH_H_		// ��d�C���N���[�h�h�~
#define _ENEMYDEATH_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include "enemy.h"	// 2D�I�u�W�F�N�g

//-------------------------------------------
// �N���X
//-------------------------------------------
class CEnemyDeath : public CEnemy
{
public:
	// �R���X�g���N�^
	CEnemyDeath();
	// �f�X�g���N�^
	~CEnemyDeath() override;

	// ����
	static CEnemyDeath* Create(const D3DXVECTOR3& pos);

	// ������
	HRESULT Init() override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

private:
	// �z�[�~���O
	D3DXVECTOR3 Homing();

private:
	// �o����
	static int m_nCntAppea;

	// ���x
	float m_fSpeed;
};

#endif		// _ENEMYDEATH_H_