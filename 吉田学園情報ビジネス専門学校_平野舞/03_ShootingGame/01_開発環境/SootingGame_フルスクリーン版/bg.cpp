//-------------------------------------------
//
//�w�i����[bg.cpp]
//Author:���앑
//
//-------------------------------------------

//�C���N���[�h�t�@�C��
#include "bg.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureBG[NUM_BG] = {};			//�e�N�X�`��(�O����)�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;			//���_�o�b�t�@�ւ̃|�C���^
BG g_aBG[NUM_BG];

//-------------------------------------------
//����������
//-------------------------------------------
void InitBG(void)
{
	for (int nCount = 0; nCount < NUM_BG; nCount++)
	{
		g_aBG[nCount].fTexU = 0.0f;		//texU�̏�����
		g_aBG[nCount].fTexV = 0.0f;		//texV�̏�����	
	}
	//pos�̏�����
	g_aBG[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	g_aBG[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, 550.0f, 0.0f);
	g_aBG[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, 400.0f, 0.0f);


	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/sky002.jpg",
		&g_apTextureBG[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/city000.png",
		&g_apTextureBG[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/cloud000.png",
		&g_apTextureBG[2]);
	
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	float fWidth = 0.0f;
	float fHeight = 0.0f;

	for (int nCount = 0; nCount < NUM_BG; nCount++)
	{
		switch (nCount)
		{
		case 0:
			fWidth = SCREEN_WIDTH;
			fHeight = SCREEN_HEIGHT;
			break;
		case 1:
			fWidth = SCREEN_WIDTH;
			fHeight = 200;
			break;
		case 2:
			fWidth = SCREEN_WIDTH;
			fHeight = 100;
			break;
		default:
			break;
		}

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBG[nCount].pos.x - fWidth / 2, g_aBG[nCount].pos.y - fHeight / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBG[nCount].pos.x + fWidth / 2, g_aBG[nCount].pos.y - fHeight / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBG[nCount].pos.x - fWidth / 2, g_aBG[nCount].pos.y + fHeight / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBG[nCount].pos.x + fWidth / 2, g_aBG[nCount].pos.y + fHeight / 2, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(g_aBG[nCount].fTexU, 0.1f);
		pVtx[1].tex = D3DXVECTOR2(g_aBG[nCount].fTexU + 1.0f, 0.1f);
		pVtx[2].tex = D3DXVECTOR2(g_aBG[nCount].fTexU, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aBG[nCount].fTexU + 1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBG->Unlock();
}

//-------------------------------------------
//�I������
//-------------------------------------------
void UninitBG(void)
{
	int nCountBG;

	for (nCountBG = 0; nCountBG < NUM_BG; nCountBG++)
	{
		//�e�N�X�`���̔j��
		if (g_apTextureBG[nCountBG] != NULL)
		{
			g_apTextureBG[nCountBG]->Release();
			g_apTextureBG[nCountBG] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}
}

//-------------------------------------------
//�X�V����
//-------------------------------------------
void UpdateBG(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < NUM_BG; nCount++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(g_aBG[nCount].fTexU, 0.1f);
		pVtx[1].tex = D3DXVECTOR2(g_aBG[nCount].fTexU + 1.0f, 0.1f);
		pVtx[2].tex = D3DXVECTOR2(g_aBG[nCount].fTexU, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aBG[nCount].fTexU + 1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBG->Unlock();
}

//-------------------------------------------
//�`�揈��
//-------------------------------------------
void DrawBG(void)
{
	int nCntBG;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		//�e�N�X�`���ݒ�
		pDevice->SetTexture(0, g_apTextureBG[nCntBG]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBG * 4, 2);
	}
}

//-------------------------------------------
//�w�i�̎擾
//-------------------------------------------
BG *GetBG(void)
{
	return &g_aBG[0];
}