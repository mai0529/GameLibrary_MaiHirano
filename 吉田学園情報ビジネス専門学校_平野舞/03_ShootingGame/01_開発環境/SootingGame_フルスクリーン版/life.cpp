//-------------------------------------------
//
//���C�t�\������[life.cpp](������)
//Author:���앑
//
//-------------------------------------------

//�C���N���[�h�t�@�C��
#include "life.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureLife = NULL;			//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Life g_aLife[MAX_LIFE];								//�e�̏��

//-------------------------------------------
//���C�t�̏���������
//-------------------------------------------
void InitLife(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	int nCntLife;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/heart.png",
		&g_pTextureLife);

	//�e�̏��̏�����
	for (nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		g_aLife[nCntLife].pos = D3DXVECTOR3(35.0f + (30.0f *  nCntLife), 25.0f, 0.0f);
		g_aLife[nCntLife].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_LIFE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x - (LIFE_WIDTH / 2), g_aLife[nCntLife].pos.y - (LIFE_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x + (LIFE_WIDTH / 2), g_aLife[nCntLife].pos.y - (LIFE_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x - (LIFE_WIDTH / 2), g_aLife[nCntLife].pos.y + (LIFE_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x + (LIFE_WIDTH / 2), g_aLife[nCntLife].pos.y + (LIFE_HEIGHT / 2), 0.0f);

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

		pVtx += 4;		//���_�f�[�^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLife->Unlock();

	for (int nCount = 0; nCount < 3; nCount++)
	{
		SetLife(D3DXVECTOR3(35.0f + (30.0f * nCount), 25.0f, 0.0f));
	}
}

//-------------------------------------------
//���C�t�̏I������
//-------------------------------------------
void UninitLife(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureLife != NULL)
	{
		g_pTextureLife->Release();
		g_pTextureLife = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}
}

//-------------------------------------------
//���C�t�̍X�V����
//-------------------------------------------
void UpdateLife(void)
{
	int nCntLife;
	Player *pPlayer = GetPlayer();

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		if (g_aLife[nCntLife].bUse == true)
		{//���C�t���g�p����Ă���
			//if (pPlayer->nLife += 1)
			//{//���C�t����������
			//	SetLife(D3DXVECTOR3(g_aLife[nCntLife].pos.x + 30.0f, 25.0f, 0.0f));

			//}
			//else if (pPlayer->nLife -= 1)
			//{//���C�t����������
			//	g_aLife[pPlayer->nLife + 1].bUse = false;
			//}

		 //���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x - (LIFE_WIDTH / 2), g_aLife[nCntLife].pos.y - (LIFE_HEIGHT / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x + (LIFE_WIDTH / 2), g_aLife[nCntLife].pos.y - (LIFE_HEIGHT / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x - (LIFE_WIDTH / 2), g_aLife[nCntLife].pos.y + (LIFE_HEIGHT / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aLife[nCntLife].pos.x + (LIFE_WIDTH / 2), g_aLife[nCntLife].pos.y + (LIFE_HEIGHT / 2), 0.0f);
		}
		pVtx += 4;		//���_�f�[�^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLife->Unlock();
}

//-------------------------------------------
//���C�t�̕`�揈��
//-------------------------------------------
void DrawLife(void)
{
	int nCntLife;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureLife);

	for (nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		if (g_aLife[nCntLife].bUse == true)
		{//�e���g�p����Ă���ꍇ
		 //�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLife * 4, 2);
		}
	}
}

//-------------------------------------------
//���C�t�̐ݒ菈��
//-------------------------------------------
void SetLife(D3DXVECTOR3 pos)
{
	int nCntLife;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		if (g_aLife[nCntLife].bUse == false)
		{//���C�t���g�p����Ă��Ȃ��ꍇ
			g_aLife[nCntLife].pos = pos;
			g_aLife[nCntLife].bUse = true;

			break;
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLife->Unlock();
}

//-------------------------------------------
//���C�t�̐ݒ菈��
//-------------------------------------------
void AddLife(int nValue)
{

}

//-------------------------------------------
//���C�t�̎擾
//-------------------------------------------
Life * GetMaxLife(void)
{
	return &g_aLife[MAX_LIFE - 1];
}

//-------------------------------------------
//���C�t�̎擾
//-------------------------------------------
Life * GetLife(void)
{
	return &g_aLife[0];
}