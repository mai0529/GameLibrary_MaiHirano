//-------------------------------------------
//
//�����L���O���[ranking.h](������)
//Author:���앑
//
//-------------------------------------------

#ifndef _RANKING_H_
#define _RANKING_H_

//�C���N���[�h�t�@�C��
#include "main.h"
#include "fade.h"
#include "input.h"
#include "score.h"
#include "sound.h"

//�}�N����`
#define MAX_RANKY				(5)			//Y�̐�
#define MAX_RANKX				(8)			//X�̐�
#define RANKING_WIDTH			(50)		//���ʂ̕�
#define RANKING_HEIGHT			(100)		//���ʂ̍���
#define MAX_TEX					(2)			//�摜�̖���

//�����L���O�\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	int nScore;			//�X�R�A
}Rank;

//�v���g�^�C�v�錾
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
void ResetRanking(void);
void SetRanking(void);

#endif