//=============================================================================
// �t�F�[�h�����̃w�b�_�[�t�@�C��
// Author : ���c ����
//=============================================================================
#ifndef _SHADOW_H_			//���̃}�N����`������Ȃ�������
#define _SHADOW_H_			//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

//�t�F�[�h�̏��
typedef enum
{
	SHADOW_NONE = 0,		//�������Ă��Ȃ����
	SHADOW_IN,			//�t�F�[�h�C�����
	SHADOW_OUT,			//�t�F�[�h�A�E�g
	SHADOW_MAX
}SHADOW;

//======================================================
//	�v���g�^�C�v�錾
//======================================================
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
void SetShadow(int nFinish);
SHADOW *GetShadow(void);

#endif