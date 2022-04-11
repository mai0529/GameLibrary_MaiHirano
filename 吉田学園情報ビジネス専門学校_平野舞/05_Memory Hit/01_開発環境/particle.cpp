//=============================================================================
//
// �p�[�e�B�N������ [particle.cpp]
// Author : ���c ����
//
//=============================================================================

//======================================================
//	�C���N���[�h
//======================================================
#include "main.h"
#include "particle.h"

//======================================================
//	�O���[�o���ϐ�
//======================================================
LPDIRECT3DTEXTURE9 g_pTextureParticle = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffParticle = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Particle g_aParticle[MAX_PARTICLE];						//�p�[�e�B�N���̏��

//======================================================
//	�p�[�e�B�N���̏���������
//======================================================
void InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/particle000.png",
		&g_pTextureParticle);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PARTICLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffParticle,
		NULL);

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].bUse = false;
		g_aParticle[nCntParticle].fRadius = 0.0f;
		g_aParticle[nCntParticle].nLife = 0;

		//���_���W�̐ݒ�
		pVtx[0].pos = g_aParticle[nCntParticle].pos;
		pVtx[1].pos = g_aParticle[nCntParticle].pos;
		pVtx[2].pos = g_aParticle[nCntParticle].pos;
		pVtx[3].pos = g_aParticle[nCntParticle].pos;

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_aParticle[nCntParticle].col;
		pVtx[1].col = g_aParticle[nCntParticle].col;
		pVtx[2].col = g_aParticle[nCntParticle].col;
		pVtx[3].col = g_aParticle[nCntParticle].col;

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4; //�f�[�^���S���i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffParticle->Unlock();
}

//======================================================
//	�p�[�e�B�N���̏I������
//======================================================
void UninitParticle(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureParticle != NULL)
	{
		g_pTextureParticle->Release();
		g_pTextureParticle = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffParticle != NULL)
	{
		g_pVtxBuffParticle->Release();
		g_pVtxBuffParticle = NULL;
	}
}

//======================================================
//	�p�[�e�B�N���̍X�V����
//======================================================
void UpdateParticle(void)
{
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		if (g_aParticle[nCnt].bUse)
		{
			g_aParticle[nCnt].pos += g_aParticle[nCnt].move;	//�p�[�e�B�N���̈ʒu�X�V
			g_aParticle[nCnt].fRadius -= 1.0f;					//�p�[�e�B�N���̔��a������������

			//����
			g_aParticle[nCnt].move.x -= g_aParticle[nCnt].move.x * 0.1f;

			if (g_aParticle[nCnt].fRadius <= 0.0f)
			{//���a���O�ȉ��ɂȂ�����
				g_aParticle[nCnt].fRadius = 0.0f;
			}
			g_aParticle[nCnt].col.a -= 0.02f;		//�p�[�e�B�N���̓����x�̍X�V

			if (g_aParticle[nCnt].col.a <= 0.0f)
			{//�����x���O�ȉ��ɂȂ�����
				g_aParticle[nCnt].col.a = 0.0f;
			}
		}

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aParticle[nCnt].pos.x - g_aParticle[nCnt].fRadius, g_aParticle[nCnt].pos.y - g_aParticle[nCnt].fRadius, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aParticle[nCnt].pos.x + g_aParticle[nCnt].fRadius, g_aParticle[nCnt].pos.y - g_aParticle[nCnt].fRadius, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aParticle[nCnt].pos.x - g_aParticle[nCnt].fRadius, g_aParticle[nCnt].pos.y + g_aParticle[nCnt].fRadius, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aParticle[nCnt].pos.x + g_aParticle[nCnt].fRadius, g_aParticle[nCnt].pos.y + g_aParticle[nCnt].fRadius, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_aParticle[nCnt].col;
		pVtx[1].col = g_aParticle[nCnt].col;
		pVtx[2].col = g_aParticle[nCnt].col;
		pVtx[3].col = g_aParticle[nCnt].col;

		//���R����
		g_aParticle[nCnt].nLife--;			//�p�[�e�B�N���̃��C�t������
		if (g_aParticle[nCnt].nLife <= 0)
		{
			g_aParticle[nCnt].bUse = false;
		}

		pVtx += 4; //�f�[�^���S���i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffParticle->Unlock();
}

//======================================================
//	�p�[�e�B�N���̕`�揈��
//======================================================
void DrawParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffParticle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureParticle);

	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		if (g_aParticle[nCnt].bUse == true)
		{
			//�v���C���[�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
				nCnt * 4,		//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);				//�v���~�e�B�u�i�|���S���j��
		}
	}
}

//======================================================
//	�p�[�e�B�N���̐ݒ菈��
//======================================================
void SetParticle(D3DXVECTOR3 pos)
{
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == false)
		{
			g_aParticle[nCntParticle].pos = pos;
			g_aParticle[nCntParticle].move = D3DXVECTOR3(sinf((float)(rand() % 30) / 300 + 1) * (float)(rand() % 629 - 314) / 30.0f,
														 cosf((float)(rand() % 30) / 300 + 1) * (float)(rand() % 629 - 314) / 30.0f,
														 0.0f);
			g_aParticle[nCntParticle].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
			g_aParticle[nCntParticle].fRadius = 30.0f;
			g_aParticle[nCntParticle].nLife = 50;

			g_aParticle[nCntParticle].bUse = true;

			break;
		}
	}
}