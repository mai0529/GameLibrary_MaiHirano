//-------------------------------------------------
//
//�w�i���[bg.h]
//Author:���앑
//
//-------------------------------------------------
#ifndef _BG_H_
#define _BG_H_

#include "main.h"

//�}�N����`
#define NUM_BG		(3)				//�w�i�̐�
#define BG_HEIGHT	(100.0f)		//����

typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	float fTexU;
	float fTexV;
}BG;

//�v���g�^�C�v�錾
void InitBG(void);
void UninitBG(void);
void UpdateBG(void);
void DrawBG(void);
BG *GetBG(void);

#endif