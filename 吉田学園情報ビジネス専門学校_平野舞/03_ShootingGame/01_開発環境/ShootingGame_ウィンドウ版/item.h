//-------------------------------------------------
//
//�A�C�e�����[item.h]
//Author:���앑
//
//-------------------------------------------------
#ifndef _ITEM_H_
#define _ITEM_H_

//�C���N���[�h�t�@�C��
#include "main.h"
#include "block.h"
#include "score.h"
#include "player.h"
#include "explosion.h"
#include "life.h"
#include "sound.h"

//�}�N����`
#define NUM_ITEM		(3)				//�A�C�e���̐�
#define MAX_ITEM		(128)			//�A�C�e���̍ő吔
#define ITEM_HEIGHT		(30.0f)			//����
#define ITEM_WIDTH		(50.0f)			//��
#define ITEM_G			(0.7f)			//�A�C�e���̏d��

//�A�C�e���̎��
typedef enum
{
	ITEM_CANDY = 0,			//��
	ITEM_POTION,			//�񕜖�
	ITEM_CAKE,				//�P�[�L
	ITEM_MAX
}ITEM;

//�A�C�e���̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 PosOld;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	float fWidth;			//��
	float fHeigth;			//����
	ITEM nType;				//���
	bool bUse;				//�g�p���邩���Ȃ���
}Item;

//�v���g�^�C�v�錾
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos, ITEM nType);
Item * GetItem(void);
void CollisionItem(D3DXVECTOR3 * pPos, float fWidth, float fHeigtht);
void DeleteItem(int nCntItem);
int GetnCount(void);

#endif