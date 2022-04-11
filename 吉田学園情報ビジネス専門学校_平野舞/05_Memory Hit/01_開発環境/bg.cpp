//=============================================================================
//
// �w�i���� [bg.cpp]
// Author : ���c ����
//
//=============================================================================

//======================================================
//	�C���N���[�h
//======================================================
#include "main.h"
#include "bg.h"

//======================================================
//	�O���[�o���ϐ�
//======================================================
LPDIRECT3DTEXTURE9 g_pTextureBg[MAX_BG] = { NULL };			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBg[MAX_BG] = { NULL };	//���_�o�b�t�@�ւ̃|�C���^
int g_nCounterAnimBg;										//�w�i�̃A�j���[�V�����J�E���^�[
int g_nPatternAnimBg;										//�w�i�̃A�j���[�V�����p�^�[��

//======================================================
//	�w�i�̏���������
//======================================================
void InitBg(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/BrickBg000.jpg", &g_pTextureBg[0]);
	
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffBg[nCnt],
			NULL);
	}

	g_nCounterAnimBg = 0;
	g_nPatternAnimBg = 0;

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffBg[nCnt]->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos.x = 0.0f;
		pVtx[0].pos.y = 0.0f;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = SCREEN_WIDTH;
		pVtx[1].pos.y = 0.0f;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = 0.0f;
		pVtx[2].pos.y = SCREEN_HEIGHT;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = SCREEN_WIDTH;
		pVtx[3].pos.y = SCREEN_HEIGHT;
		pVtx[3].pos.z = 0.0f;

		//rhw�̐ݒ�(1.0f�ŌŒ�)
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffBg[nCnt]->Unlock();
	}
}

//======================================================
//	�w�i�̏I������
//======================================================
void UninitBg(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		if (g_pTextureBg[nCnt] != NULL)
		{
			g_pTextureBg[nCnt]->Release();
			g_pTextureBg[nCnt] = NULL;
		}
	}
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		//���_�o�b�t�@�̔j��
		if (g_pVtxBuffBg[nCnt] != NULL)
		{
			g_pVtxBuffBg[nCnt]->Release();
			g_pVtxBuffBg[nCnt] = NULL;
		}
	}
}

//======================================================
//	�w�i�̍X�V����
//======================================================
void UpdateBg(void)
{
}

//======================================================
//	�w�i�̕`�揈��
//======================================================
void DrawBg(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffBg[nCnt], 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBg[nCnt]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
			0,											//�`�悷��ŏ��̒��_�C���f�b�N�X
			2);											//�v���~�e�B�u�i�|���S���j��
	}
}