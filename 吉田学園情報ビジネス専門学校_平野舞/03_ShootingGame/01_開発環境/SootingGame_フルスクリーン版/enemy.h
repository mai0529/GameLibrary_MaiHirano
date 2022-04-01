//-------------------------------------------------
//
//�G���[enemy.h]
//Author:���앑
//
//-------------------------------------------------

#ifndef _ENEMY_H_
#define _ENEMY_H_

//�C���N���[�h�t�@�C��
#include "main.h"
#include "score.h"
#include "block.h"
#include "player.h"
#include "explosion.h"

//�}�N����`
#define MAX_ENEMY			(128)		//�G�̍ő吔
#define NUM_ENEMY			(3)			//�G�̎�ނ̍ő吔
#define ENEMY_WIDTH			(60.0f)		//�G�̕�
#define ENEMY_HEIGHT		(70.0f)		//�G�̍���
#define ENEMY_G				(0.7f)		//�G�̏d��

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
	ENEMY_GHOST = 0,			//���΂�	
	ENEMY_BONE,					//�[��
	ENEMY_WOLF,					//�T
	ENEMY_MAX
}ENEMY;

//�G�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 PosOld;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	int nNumber;			//���Ԗڂ�
	ENEMY nType;			//���
	ENEMYSTATE state;		//���
	int nCounterState;		//��ԊǗ��J�E���^�[
	int nCounterAnim;		//�e�N�X�`���J�E���^�[
	int nPatternAnim;		//�e�N�X�`���p�^�[��No.
	int nLife;				//�̗�
	bool bUse;				//�g�p���Ă��邩�ǂ���
}Enemy;

//�v���g�^�C�v�錾
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
//void StateEnemy(int nCntEnemy);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, ENEMY nType,int nLife, int nNumber);
void HitEnemy(int nCntEnemy, int nDamage);
Enemy * GetEnemy(void);
void CollisionEnemy(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld , D3DXVECTOR3 * pMove,float fWidth, float fHeigtht);
void MoveEnemy(int nCntEnemy);

#endif