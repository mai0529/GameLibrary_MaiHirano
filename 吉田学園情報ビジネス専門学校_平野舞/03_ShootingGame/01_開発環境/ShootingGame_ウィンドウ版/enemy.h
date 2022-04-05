//-------------------------------------------
//
//�G�̏��[enemy.h]
//Author:���앑
//
//-------------------------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_

//�C���N���[�h�t�@�C��
#include "main.h"

//�}�N����`
#define MAX_ENEMY		(128)		//�G�̍ő吔
#define ENEMY_WIDTH		(60.0f)		//�G�̕�
#define ENEMY_HEIGHT	(70.0f)		//�G�̍���

//�G�̏��
typedef enum
{
	ENEMYSTATE_NORMAL = 0,		//�ʏ���
	ENEMYSTATE_DAMAGE,			//�_���[�W���
	ENEMYSTATE_MAX
}ENEMYSTATE;

//�O���t�@�C���p�G�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	int nType;			//���
}EnemyFile;

//�G�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	int nType;				//���
	ENEMYSTATE state;		//���
	int nCounterState;		//��ԊǗ��J�E���^�[
	int nLife;				//�̗�
	bool bUse;				//�g�p���Ă��邩�ǂ���
}Enemy;

//�v���g�^�C�v�錾
void InitEnemy(void);							//����������
void UninitEnemy(void);							//�I������
void UpdateEnemy(void);							//�X�V����
void DrawEnemy(void);							//�`�揈��
void SetEnemy(D3DXVECTOR3 pos, int nType);		//�ݒ菈��
void StateEnemy(int nCntEnemy);					//��ԊǗ�����
void HitEnemy(int nCntEnemy, int nDamage);		//�q�b�g����
void LoadEnemy(void);							//�O���t�@�C���̓ǂݍ��ݏ���
Enemy * GetEnemy(void);							//���̎擾

#endif