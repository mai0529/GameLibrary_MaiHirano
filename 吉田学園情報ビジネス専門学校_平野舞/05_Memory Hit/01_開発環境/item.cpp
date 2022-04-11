//=============================================================================
//
// �A�C�e������ [item.cpp]
// Author : ���c ����
//
//=============================================================================

//======================================================
// �C���N���[�h
//======================================================
#include "main.h"
#include "item.h"
#include "particle.h"
#include "fade.h"
#include "sound.h"
#include <stdio.h>
#include "score.h"

//======================================================
// �O���[�o���ϐ�
//======================================================
LPDIRECT3DTEXTURE9 g_pTextureItem[MAX_ITEM_TEX] = { NULL };			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Item g_aItem[MAX_ITEM];							//�u���b�N�̏��

//================================================
//	�u���b�N�̏���������
//================================================
void InitItem(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Item_001.png", &g_pTextureItem[0]);		//�ʏ�A�C�e��1
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Item_002.png", &g_pTextureItem[1]);		//�ʏ�A�C�e��2
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Item_003.png", &g_pTextureItem[2]);		//�ʏ�A�C�e��3
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Item_007.png", &g_pTextureItem[3]);		//�ʏ�A�C�e��4
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Item_004_SR.png", &g_pTextureItem[4]);		//���A�A�C�e��1
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Item_005_SR.png", &g_pTextureItem[5]);		//���A�A�C�e��2
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Item_007_SR.png", &g_pTextureItem[6]);		//���A�A�C�e��3

	//�u���b�N�̏��̏�����
	ZeroMemory(&g_aItem, sizeof(g_aItem));

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_ITEM; nCntBlock++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntBlock].pos.x, g_aItem[nCntBlock].pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntBlock].pos.x, g_aItem[nCntBlock].pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntBlock].pos.x, g_aItem[nCntBlock].pos.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntBlock].pos.x, g_aItem[nCntBlock].pos.y, 0.0f);

		//rhw�̐ݒ�(1.0f�ŌŒ�)
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

		pVtx += 4;		//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//======================================================
//	�u���b�N�̏I������
//======================================================
void UninitItem(void)
{
	for (int nCnt = 0; nCnt > MAX_ITEM_TEX; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureItem != NULL)
		{
			g_pTextureItem[nCnt]->Release();
			g_pTextureItem[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//======================================================
//	�u���b�N�̍X�V����
//======================================================
void UpdateItem(void)
{
}

//======================================================
//	�u���b�N�̕`�揈��
//======================================================
void DrawItem(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntBlock = 0; nCntBlock < MAX_ITEM; nCntBlock++)
	{
		if (g_aItem[nCntBlock].bUse == true)
		{//�e���g�p����Ă���

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureItem[g_aItem[nCntBlock].nType]);

			//�v���C���[�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
				nCntBlock * 4,								//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);		//�v���~�e�B�u�i�|���S���j��
		}
	}
}

//======================================================
//	�u���b�N�̐ݒ菈��
//======================================================
void SetItem(D3DXVECTOR3 pos, int nType, float ItemPosX, float ItemPosY)
{
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++)
	{
		if (g_aItem[nCnt].bUse == false)
		{//�u���b�N���g�p����Ă��Ȃ��ꍇ

			g_aItem[nCnt].pos = pos;
			g_aItem[nCnt].nType = nType;
			g_aItem[nCnt].BoxNum = D3DXVECTOR2(ItemPosX, ItemPosY);

			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCnt].pos.x - (ITEM_SIZE / 2), g_aItem[nCnt].pos.y - (ITEM_SIZE / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCnt].pos.x + (ITEM_SIZE / 2), g_aItem[nCnt].pos.y - (ITEM_SIZE / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCnt].pos.x - (ITEM_SIZE / 2), g_aItem[nCnt].pos.y + (ITEM_SIZE / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCnt].pos.x + (ITEM_SIZE / 2), g_aItem[nCnt].pos.y + (ITEM_SIZE / 2), 0.0f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			g_aItem[nCnt].bUse = true;

			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//----------------------------------------
//�@�A�C�e���̓����蔻��
//----------------------------------------
void CollisionItem(D3DXVECTOR3 pos, float size)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntFrame = 0; nCntFrame < MAX_ITEM; nCntFrame++)
	{
		if (g_aItem[nCntFrame].bUse == true)
		{
			if (g_aItem[nCntFrame].pos.x + ITEM_SIZE >= pos.x &&
				g_aItem[nCntFrame].pos.x - ITEM_SIZE <= pos.x &&
				g_aItem[nCntFrame].pos.y - ITEM_SIZE <= pos.y &&
				g_aItem[nCntFrame].pos.y + ITEM_SIZE >= pos.y)
			{
				g_aItem[nCntFrame].state = ITEMSTATE_ON;
			}
			else
			{
				g_aItem[nCntFrame].state = ITEMSTATE_OFF;
			}
		}

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//----------------------------------------
//�@�A�C�e���̓����蔻��
//----------------------------------------
void SelectItem(void)
{
	bool bPenalty = true;		//�y�i���e�B����p

	for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++)
	{
		if (g_aItem[nCnt].bUse && !g_aItem[nCnt].bSelect)
		{
			if (g_aItem[nCnt].state == ITEMSTATE_ON)
			{
				if (g_aItem[nCnt].nType == 4 || g_aItem[nCnt].nType == 5 || g_aItem[nCnt].nType == 6)
				{//���F�̃A�C�e��
					AddScore(3);
					bPenalty = false;		//�y�i���e�B���󂯂Ȃ�
					g_aItem[nCnt].bSelect = true;		//�d�����đI�����Ȃ��悤�ɂ���
				}
				else
				{//���ʂ̃A�C�e��
					AddScore(1);
					bPenalty = false;		//�y�i���e�B���󂯂Ȃ�
					g_aItem[nCnt].bSelect = true;		//�d�����đI�����Ȃ��悤�ɂ���
				}
			}
		}
		else if (g_aItem[nCnt].bUse && g_aItem[nCnt].bSelect)
		{
			bPenalty = false;		//�y�i���e�B���󂯂Ȃ�
		}
	}

	if (bPenalty)
	{//�y�i���e�B���肪�L���Ȃ�
		AddScore(-3);
	}
}

//======================================================
//	�u���b�N�̏����擾
//======================================================
Item *GetItem(void)
{
	return &g_aItem[0];
}