//-------------------------------------------
//
//�A�C�e�����[item.h]
//Author:���앑
//
//-------------------------------------------
#ifndef _ITEM_H_
#define _ITEM_H_

//�C���N���[�h�t�@�C��
#include "main.h"

//�A�C�e���̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	bool bUse;				//�g�p���邩���Ȃ���
}Item;

//�v���g�^�C�v�錾
void InitItem(void);		//����������
void UninitItem(void);		//�I������
void UpdateItem(void);		//�X�V����
void DrawItem(void);		//�`�揈��
void SetItem(D3DXVECTOR3 pos);			//�ݒ菈��
void CollisionItem(D3DXVECTOR3 * pPos, float fWidth, float fHeigtht);	//�����蔻��
int GetScoreUpItem(void);				//�X�R�A�A�b�v�A�C�e���̎擾

#endif