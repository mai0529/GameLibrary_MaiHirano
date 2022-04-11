//-------------------------------------------
//
//�^�C�����[time.h]
//Author:���앑
//
//-------------------------------------------
#ifndef _TIME_H_
#define _TIME_H_

//�C���N���[�h�t�@�C��
#include "main.h"

//�}�N����`
#define NUM_TIME		(3)			//�^�C���̍ő包��

//�^�C�}�[�̍\����
typedef struct
{
	D3DXVECTOR3 pos[NUM_TIME];		//�ʒu
	D3DXCOLOR color;				//�J���[
	int nTime;						//���Ԏw��
	int nFlame;						//�t���[����
	bool bUse;						//�g�p���Ă��邩�ǂ���
}Time;

//�v���g�^�C�v�錾
void InitTime(void);		//����������
void UninitTime(void);		//�I������
void UpdateTime(void);		//�X�V����
void DrawTime(void);		//�`�揈��
void SetTime(D3DXVECTOR3 pos, D3DXCOLOR color, int nTime);		//�^�C�}�[�̐ݒ�
bool FinishGame(void);

#endif