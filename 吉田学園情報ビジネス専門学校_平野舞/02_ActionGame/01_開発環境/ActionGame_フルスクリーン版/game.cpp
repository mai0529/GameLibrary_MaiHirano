//-------------------------------------------
//
//�Q�[������[game.cpp]
//Author:���앑
//
//-------------------------------------------

//�C���N���[�h�t�@�C��
#include "game.h"

//-------------------------------------------
//����������
//-------------------------------------------
void InitGame(void)
{
	//�w�i�̏���������
	InitBG();

	//�S�[���̏���������
	InitGoal();

	//���C�t�̏���������
	InitLife();

	//�^�C�}�[�̏���������
	InitTime();

	//�X�R�A�̏���������
	InitScore();

	//�u���b�N�̏���������
	InitBlock();

	//���̏���������
	InitFlame();

	//�v���C���[�̏���������
	InitPlayer();

	//�e�̏���������
	InitBullet();

	//���������̏���������
	InitExplosion();

	//�A�C�e���̏���������
	InitItem();

	//�G�̏���������
	InitEnemy();
	
	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM001);
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

	//�S�[���̏I������
	UninitGoal();

	//���C�t�̏I������
	UninitLife();

	//�^�C�}�[�̏I������
	UninitTime();

	//�X�R�A�̏I������
	UninitScore();

	//�u���b�N�̏I������
	UninitBlock();

	//���̏I������
	UninitFlame();

	//�v���C���[�̏I������
	UninitPlayer();

	//�e�̏I������
	UninitBullet();

	//�����̏I������
	UninitExplosion();

	//�A�C�e���̏I������
	UninitItem();

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

	//�S�[���̍X�V����
	UpdateGoal();

	//���C�t�̍X�V����
	UpdateLife();

	//�^�C�}�[�̍X�V����
	UpdateTime();

	//�X�R�A�̍X�V����
	UpdateScore();

	//�u���b�N�̍X�V����
	UpdateBlock();

	//���̍X�V����
	UpdateFlame();

	//�v���C���[�̍X�V����
	UpdatePlayer();

	//�e�̍X�V����
	UpdateBullet();

	//�����̍X�V����
	UpdateExplosion();

	//�A�C�e���̍X�V����
	UpdateItem();

	//�G�̍X�V����
	UpdateEnemy();

	//if (GetKeyboardTrigger(DIK_RETURN) == true)
	//{//���[�h�ݒ�
	//	SetFade(MODE_GAMECLEAR);
	//}
}

//-------------------------------------------
//�`�揈��
//-------------------------------------------
void DrawGame(void)
{
	//�w�i�̕`�揈��
	DrawBG();

	//�S�[���̕`�揈��
	DrawGoal();

	//���C�t�̕`�揈��
	DrawLife();

	//�^�C�}�[�̕`�揈��
	DrawTime();

	//�X�R�A�̕`�揈��
	DrawScore();

	//�u���b�N�̕`�揈��
	DrawBlock();

	//���̕`�揈��
	DrawFlame();

	//�v���C���[�̕`�揈��
	DrawPlayer();

	//�e�̕`�揈��
	DrawBullet();

	//�����̕`�揈��
	DrawExplosion();

	//�A�C�e���̕`�揈��
	DrawItem();

	//�G�̕`�揈��
	DrawEnemy();
}