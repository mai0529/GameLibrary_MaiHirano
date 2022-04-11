#ifndef _BULLET_H_
#define _BULLET_H_

//�C���N���[�h�t�@�C��
#include "main.h"

//�}�N����`
#define MAX_BULLET			(128)		//�e�̍ő吔
#define BULLET_WIDTH		(20.0f)		//�e�̕�
#define BULLET_HEIGHT		(20.0f)		//�e�̍���
#define BULLET_ENEMY		(45.0f)		//�G�̓����蔻��
#define NUM_BULLET			(2)			//�e�̎��

//�e�̎��
typedef enum
{
	BULLETTYPE_PLAYER = 0,
	BULLETTYPE_ENEMY,
	BULLETTYPE_MAX
}BULLETTYPE;

//�e�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	int nLife;				//����
	BULLETTYPE type;		//�e�̎��
	bool bUse;				//�g�p���Ă��邩�ǂ���
}Bullet;

//�v���g�^�C�v�錾
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,BULLETTYPE type);

#endif