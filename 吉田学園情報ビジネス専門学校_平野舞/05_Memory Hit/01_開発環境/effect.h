//-------------------------------------------
//
//�G�t�F�N�g���[effect.h]
//Author:���앑
//
//-------------------------------------------
#ifndef _EFFECT_H_
#define _EFFECT_H_

//�C���N���[�h�t�@�C��
#include "main.h"

//�G�t�F�N�g�̎��
typedef enum
{
	EFFECT_EFE1 = 0,		//�܂�
	EFFECT_EFE2,			//��
	EFFECT_EFE3,			//�ڂ�ڂ�
	EFFECT_EFE4,			//�܂�
	EFFECT_EFE5,			//�ԉ�
	EFFECT_MAX
}EFFECT;

//�G�t�F�N�g�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXCOLOR col;			//�F
	float fSize;			//���a(�傫��)
	int nLife;				//����(�\������)
	int nType;				//���
	int nSelect;			//�I��
	bool bUse;				//�g�p���Ă��邩�ǂ���
}Effect;

//�v���g�^�C�v�錾
void InitEffect(void);		//����������
void UninitEffect(void);	//�I������
void UpdateEffect(void);	//�X�V����
void DrawEffect(void);		//�`�揈��
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fSize, int nLife, EFFECT nType,int nSelect);		//�ݒ菈��
void SelectEffect(int nCount,int nSelect);		//�G�t�F�N�g�����̎��
void LoadEffectFile(void);			//�O���t�@�C�����̓ǂݍ���

#endif
