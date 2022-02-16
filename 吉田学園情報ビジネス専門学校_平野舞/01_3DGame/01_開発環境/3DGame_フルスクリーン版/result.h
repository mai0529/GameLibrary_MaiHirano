//-------------------------------------------
//
//���U���g���[result.h]
//Author:���앑
//
//-------------------------------------------

#ifndef _RESULT_H_
#define _RESULT_H_

//�C���N���[�h�t�@�C��
#include "main.h"

//�}�N����`
#define RESULT_WIDTH	(100.0f)		//���U���g�̕�
#define RESULT_HEIGHT	(150.0f)		//���U���g�̍���
#define RESULT_MAX		(2)			//���U���g�̍ő�摜
#define MAX_RESULTX		(8)			//X�̍ő吔

//���U���g�\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	int nTime;			//�X�R�A
}Result;

//�v���g�^�C�v�錾
void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);
void ResetResult(void);
void SetResult(void);

#endif