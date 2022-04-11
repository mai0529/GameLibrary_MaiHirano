//-------------------------------------------------
//
//�v���C���[���[player.h]
//Author:���앑
//
//-------------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

//�C���N���[�h�t�@�C��
#include "main.h"
#include "fade.h"
#include "input.h"
#include "block.h"
#include "enemy.h"
#include "Bullet.h"
#include "score.h"
#include "item.h"
#include "goal.h"
#include "life.h"
#include "bg.h"
#include "twinkle.h"
#include "sound.h"

//�}�N����`
#define PLAYER_WIDTH			(60.0f)			//�v���C���[�̕�
#define PLAYER_HEIGHT			(80.0f)			//�v���C���[�̍���
#define PLAYER_DIS				(2.5f)			//�ړ�����
#define PLAYER_JUMP				(15.0f)			//�W�����v�̍���
#define PLAYER_G				(0.65f)			//�d��
#define PLAYER_GROUND			(660)			//�n�ʂ̍���
#define PLAYERTEX_U				(4)				//U�����̃p�^�[����
#define PLAYERTEX_V				(2)				//V�����̃p�^�[����
#define PLAYER_MOVE				(1.0f)			//�ړ����Ă��邩�ǂ����̔��萔

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
	D3DXVECTOR3 posOld;		//�O��̈ʒu
	D3DXVECTOR3 move;		//�ړ���
	int nCounterAnim;		//�J�E���^�[
	int nPatternAnim;		//�p�^�[���ԍ�
	int nDirectionMove;		//����
	bool bIsJumping;		//�W�����v�����ǂ���
	PLAYERSTATE state;		//�v���C���[�̏��
	int nCounterState;		//��ԊǗ��J�E���^�[
	int nLife;				//�̗�
	bool bDisp;				//�\�����邩���Ȃ���
}Player;

//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void StatePlayer(void);
void HitPlayer(int nDamage);
Player * GetPlayer(void);
void OffScreen(void);
void MovePlayer(void);
void Scroll(void);
void Jumping(void);

#endif