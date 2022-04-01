//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_BGM002,			// BGM2
	SOUND_LABEL_BGM003,			// BGM3
	SOUND_LABEL_SE000,			// ���艹
	SOUND_LABEL_SE_SHOT,		// �e���ˉ�
	SOUND_LABEL_SE_ITEM,		// �q�b�g��
	SOUND_LABEL_SE_HIT,			// ������
	SOUND_LABEL_SE_DAMAGE,		// �G�Ɠ���������
	SOUND_LABEL_SE_BLOCK,		// �u���b�N�Ɠ���������
	SOUND_LABEL_SE_GOAL,		// �S�[��������
	SOUND_LABEL_SE_WALK,		// ������
	SOUND_LABEL_SE_FALL,		// ��������
	SOUND_LABEL_SE_JUMP,		// �W�����v��
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
