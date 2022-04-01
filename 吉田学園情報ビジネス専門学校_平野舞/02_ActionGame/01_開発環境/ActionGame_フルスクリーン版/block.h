//-------------------------------------------------
//
//�u���b�N���[block.h]
//Author:���앑
//
//-------------------------------------------------
#ifndef _BLOCK_H_
#define _BLOCK_H_

//�C���N���[�h�t�@�C��
#include "main.h"
#include "item.h"
#include "input.h"
#include "enemy.h"
#include "sound.h"

//�}�N����`
#define BLOCK_NUM			(3)			//�u���b�N�̍ő���
#define MAX_BLOCK			(128)		//�u���b�N�̍ő吔
#define BLOCK_WIDTH			(40.0f)		//�u���b�N�̕�
#define BLOCK_HEIGHT		(40.0f)		//�u���b�N�̍���

typedef enum
{
	BLOCKSTATE_NORMAL = 0,		//�ʏ���
	BLOCKSTATE_DAMAGE,			//�_���[�W���
	BLOCKSTATE_MAX
}BLOCKSTATE;

//�u���b�N�̎��
typedef enum
{
	BLOCK_BRICK = 0,
	BLOCK_CONCRETE,
	BLOCK_QUESTION,
	BLOCK_MAX
}Block;

//�e�L�X�g�t�@�C���ǂݍ��ݍ\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	float fWidth;			//��
	float fHeigth;			//����
	int nType;			//���
	int nItem;				//�A�C�e���̎��
}BlockFile;

//�u���b�N�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	int nType;			//���
	int nItem;				//�A�C�e���̎��
	int nLife;				//����
	float fWidth;			//��
	float fHeigth;			//����
	BLOCKSTATE state;		//���
	int nCounterState;		//��ԊǗ�
	bool bUse;				//�g�p���Ă��邩�ǂ���
}BLOCK;

//�v���g�^�C�v�錾
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeigtht, int nType,int nNumber);
bool CollisionBlock(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove, float fWidth, float fHeigtht);
void QuestionBlock(int nCntBlock);
void HitBlock(int nCntBlock);
void LoadBlock(void);
BLOCK * GetBlock(void);

#endif