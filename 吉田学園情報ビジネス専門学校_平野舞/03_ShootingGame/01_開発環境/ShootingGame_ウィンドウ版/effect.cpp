//-------------------------------------------
//
//�G�t�F�N�g����[effect.cpp]
//Author:���앑
//
//-------------------------------------------
#include "effect.h"

//�G�t�F�N�g�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXCOLOR col;			//�F
	float fRadius;			//���a(�傫��)
	int nLife;				//����(�\������)
	bool bUse;				//�g�p���Ă��邩�ǂ���
}Effect;

//�}�N����`
#define MAX_EFFECT			(4096)		//�G�t�F�N�g�̍ő吔
#define EFFECT_WIDTH		(20.0f)		//�e�̕�
#define EFFECT_HEIGHT		(20.0f)		//�e�̍���

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;			//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Effect g_aEffect[MAX_EFFECT];						//�G�t�F�N�g�̏��

//-------------------------------------------
//�G�t�F�N�g�̏���������
//-------------------------------------------
void InitEffect(void)
{
	int nCntEffect;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/effect000.jpg",
		&g_pTextureEffect);

	//�e�̏��̏�����
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(0.02f, 0.02f, 0.02f, 0.02f);
		g_aEffect[nCntEffect].fRadius = 5.0f;
		g_aEffect[nCntEffect].nLife = 15;
		g_aEffect[nCntEffect].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - EFFECT_WIDTH, g_aEffect[nCntEffect].pos.y - EFFECT_HEIGHT, g_aEffect[nCntEffect].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + EFFECT_WIDTH, g_aEffect[nCntEffect].pos.y - EFFECT_HEIGHT, g_aEffect[nCntEffect].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - EFFECT_WIDTH, g_aEffect[nCntEffect].pos.y + EFFECT_HEIGHT, g_aEffect[nCntEffect].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + EFFECT_WIDTH, g_aEffect[nCntEffect].pos.y + EFFECT_HEIGHT, g_aEffect[nCntEffect].pos.z);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(0.2f, 0.5f, 0.6f, 0.5f);
		pVtx[1].col = D3DXCOLOR(0.2f, 0.5f, 0.6f, 0.5f);
		pVtx[2].col = D3DXCOLOR(0.2f, 0.5f, 0.6f, 0.5f);
		pVtx[3].col = D3DXCOLOR(0.2f, 0.5f, 0.6f, 0.5f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;		//���_�f�[�^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//-------------------------------------------
//�G�t�F�N�g�̏I������
//-------------------------------------------
void UninitEffect(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//-------------------------------------------
//�G�t�F�N�g�̍X�V����
//-------------------------------------------
void UpdateEffect(void)
{
	int nCntEffect;
	//int nSiz = 5;
	float nData = 0.0;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//nSiz--;
		if (g_aEffect[nCntEffect].bUse == true)
		{//�G�t�F�N�g���g�p����Ă���
			//���_�J���[�̐ݒ�
			//g_aEffect[nCntEffect].col = 0.2 * 0.2 + nData * 1.0;
			//nData = g_aEffect[nCntEffect].col;
			/*nData = 0.02 * 0.02 + nData * 1.0;
			g_aEffect[nCntEffect].col = nData;*/

			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - EFFECT_WIDTH , g_aEffect[nCntEffect].pos.y - EFFECT_HEIGHT, g_aEffect[nCntEffect].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + EFFECT_WIDTH , g_aEffect[nCntEffect].pos.y - EFFECT_HEIGHT, g_aEffect[nCntEffect].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - EFFECT_WIDTH , g_aEffect[nCntEffect].pos.y + EFFECT_HEIGHT, g_aEffect[nCntEffect].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + EFFECT_WIDTH , g_aEffect[nCntEffect].pos.y + EFFECT_HEIGHT, g_aEffect[nCntEffect].pos.z);

			//����(�\������)
			g_aEffect[nCntEffect].nLife -= 1;
			if (g_aEffect[nCntEffect].nLife == 0)
			{
				g_aEffect[nCntEffect].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
			}
		}
		pVtx += 4;		//���_�f�[�^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//-------------------------------------------
//�G�t�F�N�g�̕`�揈��
//-------------------------------------------
void DrawEffect(void)
{
	int nCntEffect;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureEffect);

	//a�u���C���f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{//�e���g�p����Ă���ꍇ
		 //�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);
		}
	}

	//a�u���C���f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//-------------------------------------------
//�G�t�F�N�g�̐ݒ菈��
//-------------------------------------------
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife)
{
	int nCntEffect;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{//�e���g�p����Ă��Ȃ��ꍇ
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].nLife = nLife;
			g_aEffect[nCntEffect].bUse = true;
			break;
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}