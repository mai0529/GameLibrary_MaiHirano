//-------------------------------------------------
//
//�S�[�����[goal.h]
//Author:���앑
//
//-------------------------------------------------
#ifndef _GOAL_H_
#define _GOAL_H_

//�C���N���[�h�t�@�C��
#include "main.h"
#include "score.h"
#include "time.h"
#include "sound.h"

//�}�N����`
#define GOAL_HEIGHT		(300.0f)			//����
#define GOAL_WIDTH		(200.0f)			//��

typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	float fWidth;			//��
	float fHeigth;			//����
	bool bUse;				//�g�p���邩���Ȃ���
}Goal;

//�v���g�^�C�v�錾
void InitGoal(void);
void UninitGoal(void);
void UpdateGoal(void);
void DrawGoal(void);
void CollisionGoal(D3DXVECTOR3 * pPos, float fWidth, float fHeigtht);
Goal * GetGoal(void);

#endif
