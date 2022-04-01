//-------------------------------------------
//
//��Q�����[obstacle.h]
//Author:���앑
//
//-------------------------------------------
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

//�C���N���[�h�t�@�C��
#include "main.h"

//�}�N����`
#define MAX_OBSTACLE	(16)			//��Q���̍ő吔
#define OBSTACLE_WIDTH	(100.0f)		//��
#define OBSTACLE_HEIGHT	(150.0f)		//����

//��Q���̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	bool bUse;				//�g�p���邩�ǂ���
}Obstacle;

//�v���g�^�C�v�錾
void InitObstacle(void);			//����������
void UninitObstacle(void);			//�I������
void UpdateObstacle(void);			//�X�V����
void DrawObstacle(void);			//�`�揈��
void SetObstacle(D3DXVECTOR3 pos);	//�ݒ菈��
Obstacle * GetObstacle(void);		//�擾����

void CollisionObstacle(D3DXVECTOR3 * pPos, float fWidth, float fHeigtht);		//�����蔻��

#endif
