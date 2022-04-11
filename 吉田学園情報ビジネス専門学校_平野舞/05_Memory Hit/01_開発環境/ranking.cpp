//-------------------------------------------
//
//�����L���O����[ranking.cpp]
//Author:���앑
//
//-------------------------------------------

//�C���N���[�h�t�@�C��
#include "ranking.h"
#include "input.h"
#include <stdio.h>
#include "fade.h"
#include "score.h"
#include "game.h"
#include "sound.h"

//�}�N����`
#define MAX_RANKY				(5)			//Y�̐�
#define RANKING_WIDTH			(50)		//���ʂ̕�
#define RANKING_HEIGHT			(100)		//���ʂ̍���
#define MAX_TEX					(2)			//�摜�̖���

//�O���[�o���錾
LPDIRECT3DTEXTURE9 g_pTextureRank[MAX_TEX] = {};			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank[MAX_TEX] = {};		//���_�o�b�t�@�ւ̃|�C���^
Rank g_RankScore[MAX_RANKY];								//�����L���O�X�R�A���
bool g_bRankingPush;		//�����L���O���o�̌J��Ԃ��h�~

//-------------------------------------------
//����������
//-------------------------------------------
void InitRanking(void)
{
	//�X�R�A�\���̂̏�����
	for (int nCntY = 0; nCntY < MAX_RANKY; nCntY++)
	{
		for (int nCntX = 0; nCntX < MAX_RANKX; nCntX++)
		{
			g_RankScore[nCntY].pos[nCntX] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
		}
		g_RankScore[nCntY].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�J���[
		g_RankScore[nCntY].fWidth = 0.0f;								//���Ԋu
		g_RankScore[nCntY].fHeigth = 0.0f;								//�c�Ԋu
	}

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_bRankingPush = false;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ranking000.jpg",
		&g_pTextureRank[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number000.png",
		&g_pTextureRank[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 ,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRank[0],
		NULL);

		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANKX * 5,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffRank[1],
			NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//----------------------------�w�i------------------------------------

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRank[0]->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRank[0]->Unlock();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRank[1]->Lock(0, 0, (void**)&pVtx, 0);

	//----------------------------���l------------------------------------
	for (int nCntY = 0; nCntY < MAX_RANKY; nCntY++)
	{
		for (int nCntX = 0; nCntX < MAX_RANKX; nCntX++)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_RankScore[nCntY].pos[nCntX].x - (RANKING_WIDTH / 2.0f) + (nCntX * g_RankScore[nCntY].fWidth), g_RankScore[nCntY].pos[nCntX].y - (RANKING_HEIGHT / 2.0f) + (nCntY * g_RankScore[nCntY].fHeigth), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_RankScore[nCntY].pos[nCntX].x + (RANKING_WIDTH / 2.0f) + (nCntX * g_RankScore[nCntY].fWidth), g_RankScore[nCntY].pos[nCntX].y - (RANKING_HEIGHT / 2.0f) + (nCntY * g_RankScore[nCntY].fHeigth), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_RankScore[nCntY].pos[nCntX].x - (RANKING_WIDTH / 2.0f) + (nCntX * g_RankScore[nCntY].fWidth), g_RankScore[nCntY].pos[nCntX].y + (RANKING_HEIGHT / 2.0f) + (nCntY * g_RankScore[nCntY].fHeigth), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_RankScore[nCntY].pos[nCntX].x + (RANKING_WIDTH / 2.0f) + (nCntX * g_RankScore[nCntY].fWidth), g_RankScore[nCntY].pos[nCntX].y + (RANKING_HEIGHT / 2.0f) + (nCntY * g_RankScore[nCntY].fHeigth), 0.0f);

			//rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(g_RankScore[nCntY].color.r, g_RankScore[nCntY].color.g, g_RankScore[nCntY].color.b, g_RankScore[nCntY].color.a);
			pVtx[1].col = D3DXCOLOR(g_RankScore[nCntY].color.r, g_RankScore[nCntY].color.g, g_RankScore[nCntY].color.b, g_RankScore[nCntY].color.a);
			pVtx[2].col = D3DXCOLOR(g_RankScore[nCntY].color.r, g_RankScore[nCntY].color.g, g_RankScore[nCntY].color.b, g_RankScore[nCntY].color.a);
			pVtx[3].col = D3DXCOLOR(g_RankScore[nCntY].color.r, g_RankScore[nCntY].color.g, g_RankScore[nCntY].color.b, g_RankScore[nCntY].color.a);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			pVtx += 4;		//���_�f�[�^���S���i�߂�
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRank[1]->Unlock();

	//�����L���O�ݒ�
	SetRanking(D3DXVECTOR3(400.0f,100.0f,0.0f), D3DXCOLOR(1.0f,0.0f,0.0f,1.0f),70.0f,140.0f);
}

//-------------------------------------------
//�I������
//-------------------------------------------
void UninitRanking(void)
{
	//�T�E���h��~
	StopSound();

	for (int nCount = 0; nCount < MAX_TEX; nCount++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureRank[nCount] != NULL)
		{				 
			g_pTextureRank[nCount]->Release();
			g_pTextureRank[nCount] = NULL;
		}
	}

	for (int nCount = 0; nCount < MAX_TEX; nCount++)
	{
		//���_�o�b�t�@�̔j��
		if (g_pVtxBuffRank[nCount] != NULL)
		{				 
			g_pVtxBuffRank[nCount]->Release();
			g_pVtxBuffRank[nCount] = NULL;
		}
	}
}

//-------------------------------------------
//�X�V����
//-------------------------------------------
void UpdateRanking(void)
{
	if (g_bRankingPush == false)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A, PLAYER_1) == true || GetJoypadTrigger(JOYKEY_START, PLAYER_1) == true)
		{//ENTER�L�[����������

			//���[�h�ݒ�
			SetFade(MODE_TITLE);

			g_bRankingPush = true;
		}
	}
}

//-------------------------------------------
//�`�揈��
//-------------------------------------------
void DrawRanking(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRank[0], 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureRank[0]);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRank[1], 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	int nCount = 0;

	for (int nCntY = 0; nCntY < MAX_RANKY; nCntY++)
	{
		for (int nCntX = 0; nCntX < MAX_RANKX; nCntX++, nCount++)
		{
			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_pTextureRank[1]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
		}
	}
}

//-------------------------------------------
//�����L���O�̃��Z�b�g
//-------------------------------------------
void ResetRanking(void)
{
	FILE * pFile;		//�t�@�C���|�C���^

	//�t�@�C�����J��
	pFile = fopen("data/Ranking.txt", "r");
	if(pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		//�t�@�C�����烉���L���O��ǂݍ���
		for (int nCount = 0; nCount < MAX_RANKY; nCount++)
		{
			fscanf(pFile, "%d\n", &g_RankScore[nCount].nScore);
		}
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("�t�@�C�����J���܂���ł����B");
	}
}

//-------------------------------------------
//�����L���O�̐ݒ�
//
//D3DXVECTOR3 pos �� �ʒu���w��
//D3DXCOLOR color �� �F���w��
//float width	  �� �����̐����Ԋu���w��
//float heigth	  �� �c�̐����Ԋu���w��
//
//-------------------------------------------
void SetRanking(D3DXVECTOR3 pos, D3DXCOLOR color, float width, float heigth)
{
	int aPosTexU[MAX_RANKY][MAX_RANKX];			//�e���̐������i�[

	//###############################################################
	//�������Ɋl�������X�R�A��������
	//################################################################

	g_RankScore[5].nScore = GetScore();

	//�o�u���\�[�g
	for (int nCnt = 0; nCnt < MAX_RANKY; nCnt++)
	{
		for (int nCnt1 = nCnt + 1; nCnt1 < MAX_RANKY + 1; nCnt1++)
		{
			if (g_RankScore[nCnt].nScore < g_RankScore[nCnt1].nScore)
			{
				int nData = g_RankScore[nCnt].nScore;
				g_RankScore[nCnt].nScore = g_RankScore[nCnt1].nScore;
				g_RankScore[nCnt1].nScore = nData;
			}
		}
	}

	FILE * pFile;			//�t�@�C���|�C���^��錾

	//�����L���O���ʂ��t�@�C���ɏ����o��
	pFile = fopen("data/Ranking.txt", "w");
	if (pFile != NULL)
	{
		for (int nCount = 0; nCount < MAX_RANKY; nCount++)
		{
			//�t�@�C���Ƀ����L���O�������o��
			fprintf(pFile, "%d\n", g_RankScore[nCount].nScore);
		}
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("�t�@�C�����J���܂���ł����B");
	}

	//�e�N�X�`���ݒ�
	for (int nCntY = 0; nCntY < MAX_RANKY; nCntY++)
	{
		for (int nCntX = 0; nCntX < MAX_RANKX; nCntX++)
		{
			aPosTexU[nCntY][0] = g_RankScore[nCntY].nScore % 100 / 10;
			aPosTexU[nCntY][1] = g_RankScore[nCntY].nScore % 10 / 1;
		}
	}

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRank[1]->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntY = 0; nCntY < MAX_RANKY; nCntY++)
	{
		for (int nCntX = 0; nCntX < MAX_RANKX; nCntX++)
		{
			g_RankScore[nCntY].pos[nCntX] = pos;	//�ʒu
			g_RankScore[nCntY].color = color;		//�J���[
			g_RankScore[nCntY].fWidth = width;		//���Ԋu
			g_RankScore[nCntY].fHeigth = heigth;	//�c�Ԋu

			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_RankScore[nCntY].pos[nCntX].x - (RANKING_WIDTH / 2.0f) + (nCntX * g_RankScore[nCntY].fWidth), g_RankScore[nCntY].pos[nCntX].y - (RANKING_HEIGHT / 2.0f) + (nCntY * g_RankScore[nCntY].fHeigth), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_RankScore[nCntY].pos[nCntX].x + (RANKING_WIDTH / 2.0f) + (nCntX * g_RankScore[nCntY].fWidth), g_RankScore[nCntY].pos[nCntX].y - (RANKING_HEIGHT / 2.0f) + (nCntY * g_RankScore[nCntY].fHeigth), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_RankScore[nCntY].pos[nCntX].x - (RANKING_WIDTH / 2.0f) + (nCntX * g_RankScore[nCntY].fWidth), g_RankScore[nCntY].pos[nCntX].y + (RANKING_HEIGHT / 2.0f) + (nCntY * g_RankScore[nCntY].fHeigth), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_RankScore[nCntY].pos[nCntX].x + (RANKING_WIDTH / 2.0f) + (nCntX * g_RankScore[nCntY].fWidth), g_RankScore[nCntY].pos[nCntX].y + (RANKING_HEIGHT / 2.0f) + (nCntY * g_RankScore[nCntY].fHeigth), 0.0f);

			//���_�J���[�̍X�V
			pVtx[0].col = D3DXCOLOR(g_RankScore[nCntY].color.r, g_RankScore[nCntY].color.g, g_RankScore[nCntY].color.b, g_RankScore[nCntY].color.a);
			pVtx[1].col = D3DXCOLOR(g_RankScore[nCntY].color.r, g_RankScore[nCntY].color.g, g_RankScore[nCntY].color.b, g_RankScore[nCntY].color.a);
			pVtx[2].col = D3DXCOLOR(g_RankScore[nCntY].color.r, g_RankScore[nCntY].color.g, g_RankScore[nCntY].color.b, g_RankScore[nCntY].color.a);
			pVtx[3].col = D3DXCOLOR(g_RankScore[nCntY].color.r, g_RankScore[nCntY].color.g, g_RankScore[nCntY].color.b, g_RankScore[nCntY].color.a);

			//�e�N�X�`�����W�̍X�V
			pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntY][nCntX], 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntY][nCntX] + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntY][nCntX], 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f * aPosTexU[nCntY][nCntX] + 0.1f, 1.0f);

			pVtx += 4;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRank[1]->Unlock();
}
