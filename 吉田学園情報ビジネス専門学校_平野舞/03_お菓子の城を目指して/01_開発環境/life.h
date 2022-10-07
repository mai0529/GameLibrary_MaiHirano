//-------------------------------------------
//
//���C�t���[life.h]
//Author:���앑
//
//-------------------------------------------

#ifndef _LIFE_H_
#define _LIFE_H_

//�C���N���[�h�t�@�C��
#include "main.h"
#include "player.h"

//�}�N����`
#define MAX_LIFE			(6)			//���C�t�̍ő吔
#define LIFE_WIDTH			(50.0f)		//���C�t�̕�
#define LIFE_HEIGHT			(50.0f)		//���C�t�̍���

//�e�����̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	bool bUse;				//�g�p���Ă��邩�ǂ���
}Life;

//�v���g�^�C�v�錾
void InitLife(void);
void UninitLife(void);
void UpdateLife(void);
void DrawLife(void);
void SetLife(D3DXVECTOR3 pos);
void AddLife(int nValue);
Life * GetMaxLife(void);
Life * GetLife(void);

#endif