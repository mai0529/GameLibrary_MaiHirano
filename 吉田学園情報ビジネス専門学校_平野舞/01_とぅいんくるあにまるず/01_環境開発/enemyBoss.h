//-------------------------------------------
//
// �{�X�G�̏��[enemyBoss.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _ENEMYBOSS_H_		// ��d�C���N���[�h�h�~
#define _ENEMYBOSS_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include "enemy.h"	// 2D�I�u�W�F�N�g

//-------------------------------------------
// �N���X
//-------------------------------------------
class CEnemyBoss : public CEnemy
{
public:
	// �R���X�g���N�^
	CEnemyBoss();
	// �f�X�g���N�^
	~CEnemyBoss() override;

	// ����
	static CEnemyBoss* Create(const D3DXVECTOR3& pos);
	
	// ������
	HRESULT Init(const D3DXVECTOR3& pos) override;
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
	// �A�j���[�V�����p�J�E���g
	int m_nCntAnim;
	// ���݂̃A�j���[�V����
	int m_nNowPatternAnim;
};

#endif		// _ENEMYBOSS_H_