//=============================================================================
// �p�[�e�B�N�������̃w�b�_�[�t�@�C��
// Author : ���c ����
//=============================================================================
#ifndef _PARTICLE_H_	//���̃}�N����`������Ȃ�������
#define _PARTICLE_H_	//2�d�C���N���[�h�h�~�̃}�N����`

//======================================================
//	�}�N����`
//======================================================
#define MAX_PARTICLE	(1024)		//�p�[�e�B�N���̍ő吔

//�p�[�e�B�N���̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXCOLOR col;		//�F
	float fRadius;		//���a
	int nLife;			//����
	bool bUse;			//�g�p���Ă��邩�ǂ���
}Particle;

//======================================================
//	�v���g�^�C�v�錾
//======================================================
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos);

#endif