//-------------------------------------------
//
//�����L���O���[ranking.h]
//Author:���앑
//
//-------------------------------------------

#ifndef _RANKING_H_
#define _RANKING_H_

//�C���N���[�h�t�@�C��
#include "main.h"

//�}�N����`
#define MAX_RANKX				(2)			//X�̐�

//�����L���O�\����
typedef struct
{
	D3DXVECTOR3 pos[MAX_RANKX];	//�ʒu
	D3DXCOLOR color;			//�J���[
	float fWidth;				//���Ԋu
	float fHeigth;				//�c�Ԋu
	int nScore;					//�X�R�A
}Rank;

//�v���g�^�C�v�錾
void InitRanking(void);		//����������
void UninitRanking(void);	//�I������
void UpdateRanking(void);	//�X�V����
void DrawRanking(void);		//�`�揈��
void ResetRanking(void);	//���Z�b�g����
void SetRanking(D3DXVECTOR3 pos, D3DXCOLOR color,float width, float heigth);		//�ݒ菈��

#endif