//-------------------------------------------
//
//�Q�[������[game.cpp](�����I�Ƀ��U���g�܂�)
//Author:���앑
//
//-------------------------------------------
#include "game.h"
#include "player.h"
#include "Bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "bg.h"
#include "input.h"
#include "score.h"
#include "sound.h"
#include "effect.h"
#include "fade.h"

//-------------------------------------------
//����������
//-------------------------------------------
void InitGame(void)
{
	//�w�i�̏���������
	InitBG();

	//�X�R�A�̏���������
	InitScore();

	//�e�̏���������
	InitBullet();

	//�G�t�F�N�g�̏���������
	InitEffect();

	//�v���C���[�̏���������
	InitPlayer();

	//�����̏���������
	InitExplosion();

	//�G�̏���������
	InitEnemy();
	
	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM000);
}

//-------------------------------------------
//�I������
//-------------------------------------------
void UninitGame(void)
{
	//�T�E���h�̒�~
	StopSound();

	//�w�i�̏I������
	UninitBG();

	//�X�R�A�̏I������
	UninitScore();

	//�e�̏I������
	UninitBullet();

	//�G�t�F�N�g�̏I������
	UninitEffect();

	//�v���C���[�̏I������
	UninitPlayer();

	//�����̏I������
	UninitExplosion();

	//�G�̏I������
	UninitEnemy();

}

//-------------------------------------------
//�X�V����
//-------------------------------------------
void UpdateGame(void)
{
	//�w�i�̍X�V����
	UpdateBG();

	//�X�R�A�̍X�V����
	UpdateScore();

	//�v���C���[�̍X�V����
	UpdatePlayer();

	//�e�̕`�揈��
	UpdateBullet();

	//�G�t�F�N�g�̍X�V����
	UpdateEffect();

	//�����̍X�V����
	UpdateExplosion();

	//�G�̍X�V����
	UpdateEnemy();

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{//���[�h�ݒ�
		SetFade(MODE_RESULT);
	}
}

//-------------------------------------------
//�`�揈��
//-------------------------------------------
void DrawGame(void)
{
	//�w�i�̕`�揈��
	DrawBG();

	//�X�R�A�̕`�揈��
	DrawScore();

	//�v���C���[�̕`�揈��
	DrawPlayer();

	//�e�̕`�揈��
	DrawBullet();

	//�G�t�F�N�g�̕`�揈��
	DrawEffect();

	//�����̕`�揈��
	DrawExplosion();

	//�G�̕`�揈��
	DrawEnemy();
}