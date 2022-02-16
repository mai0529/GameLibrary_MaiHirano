// ------------------------------------------
//
//�v���C���[�\�����[player.h]
//Author:���앑
//
//-------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

//�C���N���[�h�t�@�C��
#include "main.h"

//�}�N����`
#define PLAYER_DIS		(3.5f)		//���f���̈ړ�����
#define MAX_MODELPARTS	(30)		//���f���̃p�[�c��

//�v���C���[�̏��
typedef enum
{
	PLAYERSTATE_NORMAL = 0,		//�ʏ���
	PLAYERSTATE_DAMAGE,			//�_���[�W���
	PLAYERSTATE_DATH,			//���S���
	PLAYERSTATE_MAX
}PLAYERSTATE;

//�O���t�@�C���̍\����
typedef struct
{
	int nIndex;		//�C���f�b�N�X
	int nParent;	//�e�C���f�b�N�X
	float fPosX;	//�ʒuX
	float fPosY;	//�ʒuY
	float fPosZ;	//�ʒuZ
	float fRotX;	//����X
	float fRotY;	//����Y
	float fRotZ;	//����Z
}PlayerFile;

//���f���̍\����
typedef struct
{
	LPD3DXMESH pMesh;				//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;			//�}�e���A�����ւ̃|�C���^
	DWORD nNumMat;					//�}�e���A�����̐�
	LPDIRECT3DTEXTURE9 pTexture;	//�e�N�X�`���̓ǂݍ���
	D3DXMATRIX mtxWorld;			//���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;				//�ʒu
	D3DXVECTOR3 rot;				//����
	int nIdxModelParent;			//�e���f���̃C���f�b�N�X
}ModelParts;

//�v���C���[�\���́@
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 move;			//�ړ���
	D3DXVECTOR3 posOld;			//�O�̈ʒu
	D3DXVECTOR3 rot;			//����
	D3DXVECTOR3 rotDest;		//�ړI�̊p�x
	D3DXMATRIX mtxWorld;		//���[���h�}�g���b�N�X
	D3DXVECTOR3 size;			//�T�C�Y
	D3DXVECTOR3 vtxMin;			//�ŏ����_�l
	D3DXVECTOR3 vtxMax;			//�ő咸�_�l
	ModelParts aModel[MAX_MODELPARTS];		//���f���̃p�[�c��
	bool bUse;					//�g�p���邩�ǂ���
	PLAYERSTATE state;			//��ԊǗ�
	int nCntState;				//��ԊǗ��J�E���^�[
	int nLife;					//���C�t
	int nIdxShadow;				//�e�̔ԍ�
}Player;

//Motion�\����
typedef struct
{
	int nLoop;		//���[�v����
	int nNumKey;	//�L�[��
}MotionSet;

//Key�\���́@
typedef struct
{
	float fPosX;	//�ʒuX
	float fPosY;	//�ʒuY
	float fPosZ;	//�ʒuZ
	float fRotX;	//����X
	float fRotY;	//����Y
	float fRotZ;	//����Z
}Key;

//�v���g�^�C�v�錾
void InitPlayer(void);			//����������
void UninitPlayer(void);		//�I������
void UpdatePlayer(void);		//�X�V����
void DrawPlayer(void);			//�`�揈��
void MovePlayer(void);			//�v���C���[�̈ړ�����
void MotionPlayer(int nMotion);	//���[�V��������
void StatePlayer(void);			//��ԏ���
void HitPlayer(int nDamage);	//�q�b�g����
float GetPlayerRot(void);		//�v���C���[�̊p�x���擾
Player * GetPlayer(void);		//�v���C���[���̎擾
void LoadPlayerFile(void);		//�O���t�@�C�����̓ǂݍ���

#endif