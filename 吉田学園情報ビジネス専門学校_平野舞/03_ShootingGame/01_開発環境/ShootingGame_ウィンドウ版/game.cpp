//-------------------------------------------
//
//�Q�[������[game.cpp]
//Author:���앑
//
//-------------------------------------------

//�C���N���[�h�t�@�C��
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
#include "time.h"
#include "Sweet.h"
#include "life.h"
#include "obstacle.h"
#include "item.h"

//-------------------------------------------
//����������
//-------------------------------------------
void InitGame(void)
{
	//�w�i�̏���������
	InitBG();

	//�X�R�A�̏���������
	InitScore();

	//�^�C���̏���������
	InitTime();

	//���C�t�̏���������
	InitLife();

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

	//��Q���̏���������
	InitObstacle();

	//���َq�̏���������
	InitSweet();

	//�A�C�e���̏���������
	InitItem();
	
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

	//�^�C���̏I������
	UninitTime();

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

	//��Q���̏I������
	UninitObstacle();

	//���C�t�̏I������
	UninitLife();

	//���َq�̏I������
	UninitSweet();

	//�A�C�e���̏I������
	UninitItem();
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

	//�^�C���̍X�V����
	UpdateTime();

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

	//��Q���̍X�V����
	UpdateObstacle();

	//�A�C�e���̍X�V����
	UpdateItem();

	//���َq�̍X�V����
	UpdateSweet();

	//���C�t�̍X�V����
	UpdateLife();
}

//-------------------------------------------
//�`�揈��
//-------------------------------------------
void DrawGame(void)
{
	//�w�i�̕`�揈��
	DrawBG();

	//���َq�̕`�揈��
	DrawSweet();

	//���C�t�̕`�揈��
	DrawLife();

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

	//��Q���̕`�揈��
	DrawObstacle();

	//�A�C�e���̕`�揈��
	DrawItem();

	//�X�R�A�̕`�揈��
	DrawScore();

	//�^�C���̕`�揈��
	DrawTime();
}