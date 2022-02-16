//------------------------------------------ -
//
//�Q�[�����U���g����[result.cpp]
//Author:���앑
//
//-------------------------------------------
#include "result.h"
#include "input.h"
#include "sound.h"
#include "fade.h"

//�}�N����`
#define RESULT_WIDTH	(320.0f)	//��
#define RESULT_HEIGHT	(170.0f)	//����

//�O���[�o���錾
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;				//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;		//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posResult;								//�^�C�g���̈ʒu

//-------------------------------------------
//����������
//-------------------------------------------
void InitResult(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/gameclear_logo001.png",
		&g_pTextureResult);

	g_posResult = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���W�̏�����

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(640.0f - RESULT_WIDTH, 360.0f - RESULT_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(640.0f + RESULT_WIDTH, 360.0f - RESULT_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(640.0f - RESULT_WIDTH, 360.0f + RESULT_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(640.0f + RESULT_WIDTH, 360.0f + RESULT_HEIGHT, 0.0f);

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
	g_pVtxBuffResult->Unlock();

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM002);
}

//-------------------------------------------
//�I������
//-------------------------------------------
void UninitResult(void)
{
	//�T�E���h�̒�~
	StopSound();

	//�e�N�X�`���̔j��
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}

//-------------------------------------------
//�X�V����
//-------------------------------------------
void UpdateResult(void)
{
	//����L�[(ENTER�L�[)�������ꂽ���ǂ���
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{//���[�h�ݒ�
		SetFade(MODE_TITLE);
	}
}

//-------------------------------------------
//�`�揈��
//-------------------------------------------
void DrawResult(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureResult);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}