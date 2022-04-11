//-------------------------------------------------
//
//�����[flame.h]
//Author:���앑
//
//-------------------------------------------------

#ifndef _FLAME_H_
#define _FLAME_H_

//�C���N���[�h�t�@�C��
#include "main.h"
#include "item.h"
#include "score.h"

//�}�N����`
#define MAX_FLAME		(128)			//�A�C�e���̍ő吔
#define FLAME_HEIGHT	(70.0f)			//����
#define FLAME_WIDTH		(70.0f)			//��

//���̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	int nNumber;			//���Ԗڂ�
	bool bUse;				//�g�p���邩���Ȃ���
}Flame;

//�v���g�^�C�v�錾
void InitFlame(void);
void UninitFlame(void);
void UpdateFlame(void);
void DrawFlame(void);
void SetFlame(D3DXVECTOR3 pos, D3DXVECTOR3 move,int nNumber);
void CollisionFlame(D3DXVECTOR3 * pPos, float fWidth, float fHeigtht);
Flame *GetFlame(void);

#endif

