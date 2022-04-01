//-------------------------------------------------
//
//���َq���[Sweet.h]
//Author:���앑
//
//-------------------------------------------------
#ifndef _SWEET_H_
#define _SWEET_H_

//�C���N���[�h�t�@�C��
#include "main.h"

//�}�N����`
#define MAX_SWEET		(5)				//�A�C�e���̍ő吔
#define SWEET_HEIGHT	(120.0f)		//����
#define SWEET_WIDTH		(170.0f)		//��

//�A�C�e���̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	bool bUse;				//�g�p���邩���Ȃ���
}Sweet;

//�v���g�^�C�v�錾
void InitSweet(void);
void UninitSweet(void);
void UpdateSweet(void);
void DrawSweet(void);
void SetSweet(D3DXVECTOR3 pos);
Sweet * GetSweet(void);
void CollisionSweet(D3DXVECTOR3 * pPos, float fWidth, float fHeigtht);

#endif