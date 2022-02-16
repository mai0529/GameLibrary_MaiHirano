#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//�}�N����`
#define MAX_ENEMY		(128)		//�G�̍ő吔

//�G�̏��
typedef enum
{
	ENEMYSTATE_NORMAL = 0,		//�ʏ���
	ENEMYSTATE_DAMAGE,			//�_���[�W���
	ENEMYSTATE_MAX
}ENEMYSTATE;

//�G�̎��
typedef enum
{
	ENEMY_HEART = 0,		
	ENEMY_CLOVER,	
	ENEMY_SPADE,
	ENEMY_DIA,
	ENEMY_BLACKDIA,
	ENEMY_BLACKSPADE,
	ENEMY_MAX
}ENEMY;

//�G�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	ENEMY nType;			//���
	ENEMYSTATE state;		//���
	int nCounterState;		//��ԊǗ��J�E���^�[
	int nLife;				//�̗�
	bool bUse;				//�g�p���Ă��邩�ǂ���
}Enemy;

//�v���g�^�C�v�錾
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, ENEMY nType,int nLife);
void HitEnemy(int nCntEnemy, int nDamage);
Enemy * GetEnemy(void);

#endif