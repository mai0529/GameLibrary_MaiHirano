//-------------------------------------------
//
//���C�����[main.h]
//Author:���앑
//
//-------------------------------------------
#ifndef _MAIN_H_
#define _MAIN_H_

//�C���N���[�h�t�@�C��
#include <windows.h>
#include <stdio.h>
#include "d3dx9.h"	
#define DIRECTINPUT_VERSION	(0x800)		//�r���h���̌x���Ώ��p
#include "dinput.h"						//���͏����ɕK�v
#include "xaudio2.h"					//�T�E���h�����ɕK�v
#include <stdlib.h>
#include <time.h>
#include "xinput.h"						//�W���C�p�b�h�����ɕK�v

//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xinput.lib")		//�W���C�p�b�h�����ɕK�v

//�}�N����`
#define SCREEN_WIDTH		(1280)
#define SCREEN_HEIGHT		(720)
#define FVF_VERTEX_2D		(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define CLASS_NAME		"WindowClass"						//�E�C���h�E�N���X�̖��O
#define WINDOW_NAME		"�V���[�e�B���O�Q�[������"			//�E�C���h�E�̖��O

//���_���2D�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;		//���_���W
	float rhw;				//���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;			//���_�J���[
	D3DXVECTOR2 tex;		//�e�N�X�`�����W
} VERTEX_2D;

//���(���[�h)�̎��
typedef enum
{
	MODE_TITLE = 0,		//�^�C�g�����
	MODE_SETUMEI,		//�Q�[������
	MODE_GAME,			//�Q�[�����
	MODE_RESULT,		//���U���g���
	MODE_GAMEOVER,		//�Q�[���I�[�o�[���
	MODE_RANKING,		//�����L���O���
	MODE_MAX
}MODE;

//�v���g�^�C�v�錾
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);

#endif