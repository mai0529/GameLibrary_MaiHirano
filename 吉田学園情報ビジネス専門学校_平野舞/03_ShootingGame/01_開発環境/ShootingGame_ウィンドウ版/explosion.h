//-------------------------------------------
//
//�e�̔������[explosion.h]
//Author:���앑
//
//-------------------------------------------

#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//�C���N���[�h�t�@�C��
#include "main.h"

//�}�N����`
#define MAX_EXPLOSION			(128)		//�e�̍ő吔
#define EXPLOSION_WIDTH			(40.0f)		//�e�̕�
#define EXPLOSION_HEIGHT		(40.0f)		//�e�̍���
#define EXPLOSION_CNTANIM		(3)			//�A�j���[�V�������x

//�e�����̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXCOLOR col;			//�F
	int nCounterAnim;		//�A�j���[�V�����J�E���^�[
	int nPatternAnim;		//�A�j���[�V�����p�^�[��No.
	bool bUse;				//�g�p���Ă��邩�ǂ���
}Explosion;

//�v���g�^�C�v�錾
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col);

#endif