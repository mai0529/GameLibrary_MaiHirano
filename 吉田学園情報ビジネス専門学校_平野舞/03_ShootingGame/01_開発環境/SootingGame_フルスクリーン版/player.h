//-------------------------------------------
//
//�v���C���[���[player.h]
//Author:���앑
//
//-------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

//�C���N���[�h�t�@�C��
#include "main.h"

//�}�N����`
#define PLAYER_WIDTH		(80.0f)		//�v���C���[�̕�
#define PLAYER_HEIGHT		(80.0f)		//�v���C���[�̍���
#define PLAYER_DIS			(4.0f)		//�ړ�����
#define PLAYER_ENEMY		(80.0f)		//�����蔻��

//�v���C���[�̏��
typedef enum
{
	PLAYERSTATE_APPEAR = 0,		//�o�����(�_��)
	PLAYERSTATE_NORMAL,			//�ʏ���
	PLAYERSTATE_DAMAGE,			//�_���[�W���
	PLAYERSTATE_DEATH,			//���S���
	PLAYERSTATE_MAX				
}PLAYERSTATE;

//�v���C���[�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	PLAYERSTATE state;		//�v���C���[�̏��
	int nCounterState;		//��ԊǗ��J�E���^�[
	int nLife;				//�̗�
	bool bDisp;				//�\�����邩���Ȃ���
}Player;

//�v���g�^�C�v�錾
void InitPlayer(void);				//����������
void UninitPlayer(void);			//�I������
void UpdatePlayer(void);			//�X�V����
void DrawPlayer(void);				//�`�揈��
void StatePlayer(void);				//�v���C���[�̏�ԊǗ�
void FlashPlayer(void);				//�v���C���[�̓_�ŏ���
void HitPlayer(int nDamage);		//�v���C���[�̃q�b�g����
void MovePlayer(void);				//�v���C���[�̈ړ�����
void Gamengai(void);				//��ʊO����
Player * GetPlayer(void);			//�v���C���[���̎擾����

#endif