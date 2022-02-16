//-------------------------------------------
//
//�Q�[���^�C�g������[title.cpp]
//Author:���앑
//
//-------------------------------------------
#include "title.h"
#include "sound.h"
#include "input.h"
#include "fade.h"

//�}�N����`
#define TITLE_WIDTH		(340.0f)	//��
#define TITLE_HEIGHT	(170.0f)	//����

//�O���[�o���錾
LPDIRECT3DTEXTURE9 g_pTextureTitle = NULL;			//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;		//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posTitle;								//�^�C�g���̈ʒu

//-------------------------------------------
//����������
//-------------------------------------------
void InitTitle(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/title_logo.png",
		&g_pTextureTitle);

	g_posTitle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���W�̏�����

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(640.0f - TITLE_WIDTH, 360.0f - TITLE_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(640.0f + TITLE_WIDTH, 360.0f - TITLE_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(640.0f - TITLE_WIDTH, 360.0f + TITLE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(640.0f + TITLE_WIDTH, 360.0f + TITLE_HEIGHT, 0.0f);

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
	g_pVtxBuffTitle->Unlock();

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM001);
}

//-------------------------------------------
//�I������
//-------------------------------------------
void UninitTitle(void)
{
	//�T�E���h�̒�~
	StopSound();

	//�e�N�X�`���̔j��
	if (g_pTextureTitle != NULL)
	{
		g_pTextureTitle->Release();
		g_pTextureTitle = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

}

//-------------------------------------------
//�X�V����
//-------------------------------------------
void UpdateTitle(void)
{
	//����L�[(ENTER�L�[)�������ꂽ���ǂ���
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{//���[�h�ݒ�
		SetFade(MODE_SETUMEI);
	}
}

//-------------------------------------------
//�`�揈��
//-------------------------------------------
void DrawTitle(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureTitle);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}