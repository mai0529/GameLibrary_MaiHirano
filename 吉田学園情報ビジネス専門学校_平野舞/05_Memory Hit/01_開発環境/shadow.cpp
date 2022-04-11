//=============================================================================
//
// �Q�[����ʂ̃t�F�[�h���� [shadow.cpp]
// Author : ���c ����
//
//=============================================================================

//======================================================
//	�C���N���[�h
//======================================================
#include "shadow.h"
#include "main.h"

//======================================================
//	�O���[�o���ϐ�
//======================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;	//���_�o�b�t�@�ւ̃|�C���^
SHADOW g_Shadow;									//�t�F�[�h�̏��
D3DXCOLOR g_colorShadow;							//�|���S���i�t�F�[�h�j�̐F
int g_nCntFinish;	

//======================================================
//	�t�F�[�h�̏���������
//======================================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_Shadow = SHADOW_OUT;			//�t�F�[�h�C����Ԃɂ���
	g_colorShadow = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	//��ʂ���������(�s����)

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DXCOLOR(g_colorShadow);
	pVtx[1].col = D3DXCOLOR(g_colorShadow);
	pVtx[2].col = D3DXCOLOR(g_colorShadow);
	pVtx[3].col = D3DXCOLOR(g_colorShadow);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffShadow->Unlock();
}

//======================================================
//	�t�F�[�h�̏I������
//======================================================
void UninitShadow(void)
{
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//======================================================
//	�t�F�[�h�̍X�V����
//======================================================
void UpdateShadow(void)
{
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	if (g_Shadow != SHADOW_NONE)
	{
		if (g_Shadow == SHADOW_OUT)
		{//�t�F�[�h�A�E�g���
			g_colorShadow.a += 0.006f;		//�|���S����s�����ɂ��Ă���
			if (g_colorShadow.a >= 1.0f)
			{
				g_colorShadow.a = 1.0f;
				g_Shadow = SHADOW_NONE;		//�t�F�[�h�C����Ԃ�
			}
		}
		else if (g_Shadow == SHADOW_IN)
		{//�t�F�[�h�C�����
			g_colorShadow.a -= 0.006f;		//�|���S���𓧖��ɂ��Ă���
			if (g_colorShadow.a <= 0.0f)
			{
				g_colorShadow.a = 0.0f;
				if (g_nCntFinish == 1)
				{
					g_Shadow = SHADOW_NONE;		//�������Ă��Ȃ���Ԃɂ���
				}
				else
				{
					g_Shadow = SHADOW_OUT;		//�t�F�[�h�A�E�g��Ԃɂ���
				}
			}
		}

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(g_colorShadow);
		pVtx[1].col = D3DXCOLOR(g_colorShadow);
		pVtx[2].col = D3DXCOLOR(g_colorShadow);
		pVtx[3].col = D3DXCOLOR(g_colorShadow);

		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffShadow->Unlock();
	}
}

//======================================================
//	�t�F�[�h�̕`�揈��
//======================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
		0,		//�`�悷��ŏ��̒��_�C���f�b�N�X
		2);		//�v���~�e�B�u�i�|���S���j��

}

//======================================================
//	�t�F�[�h�̐ݒ菈��
//======================================================
void SetShadow(int nFinish)
{
	g_nCntFinish = nFinish;
	g_Shadow = SHADOW_IN;		//�t�F�[�h�A�E�g��Ԃɂ���
	g_colorShadow = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	//��ʂ���������(�s����)
}

//======================================================
//	�t�F�[�h�̏����擾
//======================================================
SHADOW *GetShadow(void)
{
	return &g_Shadow;
}