// ------------------------------------------
//
//���C�t�\������[life.cpp]
//Author:���앑
//
//-------------------------------------------

//�C���N���[�h�t�@�C��
#include "life.h"

//�}�N����`
#define MAX_WIDTH		(70.0f)		//��
#define MAX_HEIGHT		(28.0f)		//����

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_apTextureLife[2] = {};			//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife[2] = {};		//���_�o�b�t�@�ւ̃|�C���^
Life g_aLife;										//���C�t���

//-------------------------------------------
//����������
//-------------------------------------------
void InitLife(void)
{
	//������
		g_aLife.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
		g_aLife.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
		g_aLife.nMaxLife = 0;								//�ő僉�C�t��
		g_aLife.nNowLife = 0;								//���̃��C�t��
		g_aLife.bUse = false;								//�g�p���Ȃ�

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���(�Q�[�W)
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/life001.png",
		&g_apTextureLife[0]);

	//�e�N�X�`���̓ǂݍ���(�g)
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/life000.png",
		&g_apTextureLife[1]);

	for (int nCount = 0; nCount < 2; nCount++)
	{
		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffLife[nCount],
			NULL);
	}

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	for (int nCount = 0; nCount < 2; nCount++)
	{
		//���_�o�b�t�@�����b�N
		g_pVtxBuffLife[nCount]->Lock(0, 0, (void**)&pVtx, 0);

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aLife.pos.x - (MAX_WIDTH / 2), g_aLife.pos.y - (MAX_HEIGHT / 2.0f), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aLife.pos.x + (MAX_WIDTH / 2), g_aLife.pos.y - (MAX_HEIGHT / 2.0f), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aLife.pos.x - (MAX_WIDTH / 2), g_aLife.pos.y + (MAX_HEIGHT / 2.0f), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aLife.pos.x + (MAX_WIDTH / 2), g_aLife.pos.y + (MAX_HEIGHT / 2.0f), 0.0f);

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

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffLife[nCount]->Unlock();
	}
}

//-------------------------------------------
//�I������
//-------------------------------------------
void UninitLife(void)
{
	for (int nCntLife = 0; nCntLife < 2; nCntLife++)
	{//�e�N�X�`���̔j��
		if (g_apTextureLife[nCntLife] != NULL)
		{
			g_apTextureLife[nCntLife]->Release();
			g_apTextureLife[nCntLife] = NULL;
		}
	}

	for (int nCntLife = 0; nCntLife < 2; nCntLife++)
	{//���_�o�b�t�@�̔j��
		if (g_pVtxBuffLife[nCntLife] != NULL)
		{
			g_pVtxBuffLife[nCntLife]->Release();
			g_pVtxBuffLife[nCntLife] = NULL;
		}
	}
}

//-------------------------------------------
//�X�V����
//-------------------------------------------
void UpdateLife(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	for (int nCount = 0; nCount < 2; nCount++)
	{
		//���_�o�b�t�@�����b�N
		g_pVtxBuffLife[nCount]->Lock(0, 0, (void**)&pVtx, 0);

		if (g_aLife.bUse == true)
		{//�g�p���Ă�����
			//�e�N�X�`�����W�̍X�V
			pVtx[0].tex = D3DXVECTOR2(0.0f + (0.5f / g_aLife.nMaxLife) * (g_aLife.nMaxLife - g_aLife.nNowLife), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.5f + (0.5f / g_aLife.nMaxLife) * (g_aLife.nMaxLife - g_aLife.nNowLife), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (0.5f / g_aLife.nMaxLife) * (g_aLife.nMaxLife - g_aLife.nNowLife), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f + (0.5f / g_aLife.nMaxLife) * (g_aLife.nMaxLife - g_aLife.nNowLife), 1.0f);

			if (g_aLife.nNowLife == 0)
			{//���C�t��0�ɂȂ�����
				g_aLife.bUse = false;		//�g�p���Ȃ�
			}

			//�ʒu�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_aLife.pos.x - (MAX_WIDTH / 2), g_aLife.pos.y - (MAX_HEIGHT / 2.0f), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aLife.pos.x + (MAX_WIDTH / 2), g_aLife.pos.y - (MAX_HEIGHT / 2.0f), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aLife.pos.x - (MAX_WIDTH / 2), g_aLife.pos.y + (MAX_HEIGHT / 2.0f), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aLife.pos.x + (MAX_WIDTH / 2), g_aLife.pos.y + (MAX_HEIGHT / 2.0f), 0.0f);

			pVtx += 4;		//���_�f�[�^���S���i�߂�
		}

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffLife[nCount]->Unlock();
	}
}

//-------------------------------------------
//�`�揈��
//-------------------------------------------
void DrawLife(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCount = 0; nCount < 2; nCount++)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffLife[nCount], 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		if (g_aLife.bUse == true)
		{//���َq���g�p����Ă���ꍇ
		 //�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_apTextureLife[nCount]);
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}
}

//-------------------------------------------
//�ݒ菈��
//-------------------------------------------
void SetLife(D3DXVECTOR3 pos, int nMax, int nNow)
{
	for (int nCount = 0; nCount < 2; nCount++)
	{
		if (g_aLife.bUse == false)
		{//�g�p���Ă��Ȃ�������
			g_aLife.pos = pos;			//�ʒu
			g_aLife.nMaxLife = nMax;	//�ő僉�C�t��
			g_aLife.nNowLife = nNow;	//���̃��C�t��
			g_aLife.bUse = true;		//�g�p����

			break;
		}
	}
}

//-------------------------------------------
//���C�t�̌��Z����
//-------------------------------------------
void SubLife(int nCntLife,int nReduce)
{
		if (g_aLife.bUse == true)
		{//���̗̑͂���_���[�W�����炷
			g_aLife.nNowLife -= nReduce;
		}
}

//-------------------------------------------
//���C�t�Q�[�W�̈ʒu�̍X�V����
//-------------------------------------------
void SetPositionLife(D3DXVECTOR3 pos)
{
	if (g_aLife.bUse == true)
	{//�g�p���Ă�����
		g_aLife.pos = pos;
	}
}