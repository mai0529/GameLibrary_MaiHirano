//-------------------------------------------
//
//�Q�[����������[setumei.cpp]
//Author:���앑
//
//-------------------------------------------
#include "setumei.h"
#include "sound.h"
#include "input.h"
#include "fade.h"
#include "controller.h"

//�}�N����`
#define TITLE_WIDTH		(640.0f)	//��
#define TITLE_HEIGHT	(360.0f)	//����

//�O���[�o���錾
LPDIRECT3DTEXTURE9 g_pTextureSetumei = NULL;			//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSetumei = NULL;		//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posSetumei;								//�^�C�g���̈ʒu
bool g_SetumeiFade;										//�t�F�[�h���Ă��邩�ǂ���

//-------------------------------------------
//����������
//-------------------------------------------
void InitSetumei(void)
{
	g_posSetumei = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���W�̏�����
	g_SetumeiFade = false;								//�t�F�[�h���Ă��Ȃ�

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/setumei.png",
		&g_pTextureSetumei);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSetumei,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSetumei->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffSetumei->Unlock();

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM001);
}

//-------------------------------------------
//�I������
//-------------------------------------------
void UninitSetumei(void)
{
	//�T�E���h�̒�~
	StopSound();

	//�e�N�X�`���̔j��
	if (g_pTextureSetumei != NULL)
	{
		g_pTextureSetumei->Release();
		g_pTextureSetumei = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSetumei != NULL)
	{
		g_pVtxBuffSetumei->Release();
		g_pVtxBuffSetumei = NULL;
	}

}

//-------------------------------------------
//�X�V����
//-------------------------------------------
void UpdateSetumei(void)
{
	//����L�[(ENTER�L�[)�������ꂽ���ǂ���
	if (GetKeyboardTrigger(DIK_RETURN) == true && !g_SetumeiFade
		|| GetControllerPressTrigger(0, XINPUT_GAMEPAD_A) && !g_SetumeiFade)
	{
		SetFade(MODE_GAME);		//�Q�[����ʂɈڍs
		g_SetumeiFade = true;	//�t�F�[�h��
	}
}

//-------------------------------------------
//�`�揈��
//-------------------------------------------
void DrawSetumei(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSetumei, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureSetumei);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}