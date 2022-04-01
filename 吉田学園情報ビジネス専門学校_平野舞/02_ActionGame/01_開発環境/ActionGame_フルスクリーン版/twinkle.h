//-------------------------------------------------
//
//�L���L�����[twinkle.h]
//Author:���앑
//
//-------------------------------------------------

#ifndef _TWINKLE_H_
#define _TWINKLE_H_

//�C���N���[�h�t�@�C��
#include "main.h"
#include "item.h"
#include "score.h"

//�}�N����`
#define MAX_TWINKLE		(128)			//�A�C�e���̍ő吔
#define TWINKLE_HEIGHT	(70.0f)			//����
#define TWINKLE_WIDTH		(70.0f)			//��

//�L���L���̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	int nNumber;			//���Ԗڂ�
	bool bUse;				//�g�p���邩���Ȃ���
}Twinkle;

//�v���g�^�C�v�錾
void InitTwinkle(void);
void UninitTwinkle(void);
void UpdateTwinkle(void);
void DrawTwinkle(void);
void SetTwinkle(D3DXVECTOR3 pos, D3DXVECTOR3 move,int nNumber);
void CollisionTwinkle(D3DXVECTOR3 * pPos, float fWidth, float fHeigtht);
Twinkle *GetTwinkle(void);

#endif

