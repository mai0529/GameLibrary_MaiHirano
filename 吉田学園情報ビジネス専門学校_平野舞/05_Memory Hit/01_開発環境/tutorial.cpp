//=============================================================================
//
//	�`���[�g���A������ [tutorial.cpp]
//	Author : ���c ����
//
//=============================================================================

//======================================================
//	�C���N���[�h
//======================================================
#include "main.h"
#include "tutorial.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "game.h"

//======================================================
//	�O���[�o���ϐ�
//======================================================
LPDIRECT3DTEXTURE9 g_pTextureTutorial[MAX_TUTORIAL] = { NULL };			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;	//���_�o�b�t�@�ւ̃|�C���^
bool g_GameStartPushTutorial;		//�X�^�[�g���o�̌J��Ԃ��h�~
int g_nCnt;							//�`���[�g���A����ʐ؂�ւ��J�E���^�[
//Title g_aTitle[2];				//�^�C�g�����

//======================================================
//	�^�C�g����ʂ̏���������
//======================================================
void InitTutorial(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Tutorial000.jpg",
		&g_pTextureTutorial[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Tutorial001.jpg",
		&g_pTextureTutorial[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	//�^�C�g�����̏�����
	//ZeroMemory(&g_aTitle, sizeof(g_aTitle));

	g_GameStartPushTutorial = false;		//�X�^�[�g���o�J��Ԃ��h�~�̏�����
	g_nCnt = 0;

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTutorial->Unlock();

	//�T�E���h�Đ�
	PlaySound(SOUND_LABEL_BGM000);
}

//======================================================
//	�^�C�g����ʂ̏I������
//======================================================
void UninitTutorial(void)
{
	//�T�E���h��~
	StopSound();

	for (int nCnt = 0; nCnt < MAX_TUTORIAL; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureTutorial[nCnt] != NULL)
		{
			g_pTextureTutorial[nCnt]->Release();
			g_pTextureTutorial[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}
}

//======================================================
//	�^�C�g����ʂ̍X�V����
//======================================================
void UpdateTutorial(void)
{
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	if (!g_GameStartPushTutorial)
	{//�X�^�[�g���o�̌J��Ԃ��h�~
		if (g_nCnt == 0)
		{
			if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A, PLAYER_1) == true || GetJoypadTrigger(JOYKEY_START, PLAYER_1) == true)
			{//�G���^�[�L�[�������ꂽ��

				//�e�N�X�`����ς���
				g_nCnt++;

				//�T�E���h�Đ�
				PlaySound(SOUND_LABEL_SE_SELECT1);
			}
		}
		else if (g_nCnt == 1)
		{
			if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A, PLAYER_1) == true || GetJoypadTrigger(JOYKEY_START, PLAYER_1) == true)
			{//�G���^�[�L�[�������ꂽ��

				//�X�^�[�g���o�̌J��Ԃ��h�~
				g_GameStartPushTutorial = true;

				//���[�h�ڍs
				SetFade(MODE_TITLE);

				//�T�E���h�Đ�
				PlaySound(SOUND_LABEL_SE_SELECT2);
			}
		}
	}
}

//======================================================
//	�^�C�g����ʂ̕`�揈��
//======================================================
void DrawTutorial(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_TUTORIAL; nCnt++)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTutorial[g_nCnt]);

		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
			0,		//�`�悷��ŏ��̒��_�C���f�b�N�X
			2);		//�v���~�e�B�u�i�|���S���j��
	}
}