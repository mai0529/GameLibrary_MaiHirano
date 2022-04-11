//=============================================================================
//
// �Q�[����ʏ��� [game.cpp]
// Author : ���c ����
//
//=============================================================================

//======================================================
// �C���N���[�h
//======================================================
#include "main.h"
#include "game.h"
#include "bg.h"
#include "time.h"
#include "sound.h"
#include "fade.h"
#include "input.h"
#include "particle.h"
#include "pause.h"
#include "game_logo.h"
#include "item.h"
#include "shadow.h"
#include "Frame.h"
#include "select.h"
#include <stdlib.h>
#include <time.h>
#include "score.h"
#include "time.h"
#include "effect.h"

//======================================================
// �O���[�o���ϐ�
//======================================================
int g_nCntSelect;			//�I����ʂ��o���܂ł̃J�E���^�[

//======================================================
// �Q�[����ʂ̏���������
//======================================================
void InitGame(void)
{
	//�J�E���^�[���Z�b�g
	g_nCntSelect = 0;

	//�����̎�𐶐�����
	srand((unsigned int)time(NULL));

	//�w�i�̏���������
	InitBg();

	//�u���b�N�̏���������
	InitItem();

	//---------------------------------------------------------
	//	�A�C�e���z�u
	//---------------------------------------------------------
	for (int nCntSet = 0; nCntSet <= 10; nCntSet++)
	{
		float posX = (float)(rand() % 5);
		float posY = (float)(rand() % 5);
		SetItem(D3DXVECTOR3(350.0f + (650.0f / 5) * posX, 100.0f + (650.0f / 5) * posY, 0.0f), rand() % 7, posX, posY);
	}

	//---------------------------------------------------------
	//	�A�C�e���z�u�����܂�
	//---------------------------------------------------------

	//�|�[�Y�̏���������
	InitPause();

	//�p�[�e�B�N���̏���������
	InitParticle();

	//�Q�[�����̃��S�\��������
	InitLogo();

	//�Q�[�����̃t�F�[�h������
	InitShadow();

	//�I�������̏�����
	InitFrame();
	InitSelect();

	//�X�R�A�̏�����
	InitScore();

	//�^�C�}�[�̏�����
	InitTime();

	//�G�t�F�N�g�̏�����
	InitEffect();

	//�T�E���h�Đ�
	PlaySound(SOUND_LABEL_BGM001);
}

//======================================================
//	�Q�[����ʂ̏I������
//======================================================
void UninitGame(void)
{
	//�T�E���h��~
	StopSound();

	//�w�i�̏I������
	UninitBg();

	//�u���b�N�̏I������
	UninitItem();

	//�p�[�e�B�N���̏I������
	UninitParticle();

	//�|�[�Y�̏I������
	UninitPause();

	//�Q�[�����̃��S�\���I������
	UninitLogo();

	//�Q�[�����̃t�F�[�h�I��
	UninitShadow();

	//�I�������̏I��
	UninitFrame();
	UninitSelect();

	//�^�C�}�[�̏I��
	UninitTime();

	//�G�t�F�N�g�̏I��
	UninitEffect();
}

//======================================================
//	�Q�[����ʂ̍X�V����
//======================================================
void UpdateGame(void)
{
	if (!UpdatePause())
	{//�|�[�Y���łȂ����

		//�w�i�̍X�V����
		UpdateBg();

		//�u���b�N�̍X�V����
		UpdateItem();

		//�p�[�e�B�N���̍X�V����
		UpdateParticle();

		//�Q�[�����̃��S�\���X�V
		UpdateLogo();

		//�Q�[�����̃t�F�[�h�X�V
		UpdateShadow();

		//�X�R�A�����̍X�V
		UpdateScore();

		g_nCntSelect++;

		if (g_nCntSelect == 399)
		{
			SetTime(D3DXVECTOR3(SCREEN_WIDTH - 200, 90.0f, 0.0f), D3DXCOLOR(0.0f, 0.5f, 0.5f, 1.0f), 10);
		}
		if (g_nCntSelect >= 400)
		{
			if (!FinishGame())
			{
				//�I�������̍X�V
				UpdateFrame();
				UpdateSelect();

				//�G�t�F�N�g�����̍X�V
				UpdateEffect();
			}

			//�^�C�}�[�����̍X�V
			UpdateTime();

			g_nCntSelect = 400;
		}
	}
}

//======================================================
//	�Q�[����ʂ̕`�揈��
//======================================================
void DrawGame(void)
{
	//�w�i�̕`�揈��
	DrawBg();

	//�A�C�e���̕`�揈��
	DrawItem();

	//�Q�[�����̃t�F�[�h������
	DrawShadow();

	//�p�[�e�B�N���̕`�揈��
	DrawParticle();

	//�|�[�Y�̕`�揈��
	DrawPause();

	//�Q�[�����̃��S�\���`��
	DrawLogo();

	if (g_nCntSelect >= 400)
	{
		//�G�t�F�N�g�̕`�揈��
		DrawEffect();

		//�I�������̕`�揈��
		DrawFrame();
		DrawSelect();

		//�^�C�}�[�̕`�揈��
		DrawTime();
	}

	if (FinishGame())
	{
		//�A�C�e���̕`�揈��
		DrawItem();

		//�X�R�A�̕`�揈��
		DrawScore();
	}
}