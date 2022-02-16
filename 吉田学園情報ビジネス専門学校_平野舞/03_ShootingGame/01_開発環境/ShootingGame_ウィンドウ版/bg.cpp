//-------------------------------------------
//
//�w�i�X�N���[������[bg.cpp](������)
//Author:���앑
//
//-------------------------------------------
#include "bg.h"

//�}�N����`
#define NUM_BG		(3)				//�w�i�̐�
#define BG_WIDTH	(640.0f)		//��
#define BG_HEIGHT	(360.0f)		//����

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureBG[NUM_BG] = {};		//�e�N�X�`��(�O����)�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;		//���_�o�b�t�@�ւ̃|�C���^
float g_aPosTexV[NUM_BG];							//�e�N�X�`�����W�̊J�n�ʒu(V�l)


//-------------------------------------------
//����������
//-------------------------------------------
void InitBG(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bg100.png",
		&g_apTextureBG[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bg101.png",
		&g_apTextureBG[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bg102.png",
		&g_apTextureBG[2]);

	g_aPosTexV[NUM_BG] = 0.0f;		//���W�̏�����
	
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(640.0f - BG_WIDTH ,360.0f - BG_HEIGHT,0.0f);
	pVtx[1].pos = D3DXVECTOR3(640.0f + BG_WIDTH ,360.0f - BG_HEIGHT,0.0f);
	pVtx[2].pos = D3DXVECTOR3(640.0f - BG_WIDTH ,360.0f + BG_HEIGHT,0.0f);
	pVtx[3].pos = D3DXVECTOR3(640.0f + BG_WIDTH ,360.0f + BG_HEIGHT,0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBG->Unlock();
}

//-------------------------------------------
//�I������
//-------------------------------------------
void UninitBG(void)
{
	//�e�N�X�`���̔j��
	if (g_apTextureBG[NUM_BG] != NULL)
	{
		g_apTextureBG[NUM_BG]->Release();
		g_apTextureBG[NUM_BG] = NULL;
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



	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBG->Unlock();
}

//-------------------------------------------
//�`�揈��
//-------------------------------------------
void DrawBG(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_apTextureBG[0]);
	pDevice->SetTexture(0, g_apTextureBG[1]);
	pDevice->SetTexture(0, g_apTextureBG[2]);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}