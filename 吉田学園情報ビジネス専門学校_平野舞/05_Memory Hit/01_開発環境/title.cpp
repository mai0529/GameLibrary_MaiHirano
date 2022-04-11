//=============================================================================
//
//	�^�C�g������ [title.cpp]
//	Author : ���c ����
//
//=============================================================================

//======================================================
//	�C���N���[�h
//======================================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "game.h"

//======================================================
//	�}�N����`
//======================================================
#define MAX_TITLE			(5)			//�^�C�g����ʂŕK�v�ȉ摜��
#define TITLE_SIZE_X		(900.0f)	//�^�C�g���̑傫��X
#define TITLE_SIZE_Y		(150.0f)	//�^�C�g���̑傫��Y

//======================================================
//	�O���[�o���ϐ�
//======================================================
LPDIRECT3DTEXTURE9 g_pTextureTitle[MAX_TITLE] = { NULL };		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;					//���_�o�b�t�@�ւ̃|�C���^
Title g_aTitle[MAX_TITLE];		//�^�C�g�����
MenuInfo g_Menu;				//���j���[�I���ɕK�v�ȏ��

//======================================================
//	�^�C�g����ʂ̏���������
//======================================================
void InitTitle(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/TITLE.jpg",
		&g_pTextureTitle[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Title000.png",
		&g_pTextureTitle[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/TitlePress000.png",
		&g_pTextureTitle[2]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/TitleMenu000.png",
		&g_pTextureTitle[3]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/TitleMenu002.png",
		&g_pTextureTitle[4]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TITLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	//�\���̏��̏�����
	ZeroMemory(&g_aTitle, sizeof(g_aTitle));
	ZeroMemory(&g_Menu, sizeof(MenuInfo));

	SetTitle(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));			//�w�i
	SetTitle(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / -4.0f, 0.0f), D3DXVECTOR3(0.0f, 5.0f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.5f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//�^�C�g��
	SetTitle(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 1.4f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 6.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	//PressEnter
	SetTitle(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 1.6f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 7.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	//�I����(3D�Q�[��)
	SetTitle(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 1.2f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 7.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	//�I����(�`���[�g���A��)

	g_Menu.nSelect = 3;
	
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aTitle[nCnt].pos.x - (g_aTitle[nCnt].size.x / 2), g_aTitle[nCnt].pos.y - (g_aTitle[nCnt].size.y / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aTitle[nCnt].pos.x + (g_aTitle[nCnt].size.x / 2), g_aTitle[nCnt].pos.y - (g_aTitle[nCnt].size.y / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aTitle[nCnt].pos.x - (g_aTitle[nCnt].size.x / 2), g_aTitle[nCnt].pos.y + (g_aTitle[nCnt].size.y / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aTitle[nCnt].pos.x + (g_aTitle[nCnt].size.x / 2), g_aTitle[nCnt].pos.y + (g_aTitle[nCnt].size.y / 2), 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(g_aTitle[nCnt].color);
		pVtx[1].col = D3DXCOLOR(g_aTitle[nCnt].color);
		pVtx[2].col = D3DXCOLOR(g_aTitle[nCnt].color);
		pVtx[3].col = D3DXCOLOR(g_aTitle[nCnt].color);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;		//���_���̃|�C���^��i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTitle->Unlock();

	//�T�E���h�Đ�
	PlaySound(SOUND_LABEL_BGM000);
}

//======================================================
//	�^�C�g����ʂ̏I������
//======================================================
void UninitTitle(void)
{
	//�T�E���h��~
	StopSound();

	for (int nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureTitle[nCnt] != NULL)
		{
			g_pTextureTitle[nCnt]->Release();
			g_pTextureTitle[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}

//======================================================
//	�^�C�g����ʂ̍X�V����
//======================================================
void UpdateTitle(void)
{
	//--------------------------
	//	���j���[�I�����
	//--------------------------
	if (g_Menu.nCntEnter)
	{//�I�������j���[
		if (GetKeyboardTrigger(DIK_UP) || GetKeyboardTrigger(DIK_W) || GetJoypadTrigger(JOYKEY_UP, PLAYER_1))
		{//���L�[����
			g_Menu.nSelect--;

			//�I�����̐F���Z�b�g(�Â�����)
			g_aTitle[TITLENUM_SELECTGAME].color = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
			g_aTitle[TITLENUM_SELECTTUTORIAL].color = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);

			if (g_Menu.nSelect < TITLENUM_SELECTGAME)
			{//�I����������܂ōs������A���ɖ߂�
				g_Menu.nSelect = TITLENUM_SELECTTUTORIAL;
			}

			//�T�E���h�Đ�
			PlaySound(SOUND_LABEL_SE_SELECT1);
		}
		else if (GetKeyboardTrigger(DIK_DOWN) || GetKeyboardTrigger(DIK_S) || GetJoypadTrigger(JOYKEY_DOWN, PLAYER_1))
		{//���L�[����
			g_Menu.nSelect++;

			//�I�����̐F���Z�b�g(�Â�����)
			g_aTitle[TITLENUM_SELECTGAME].color = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
			g_aTitle[TITLENUM_SELECTTUTORIAL].color = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);

			if (g_Menu.nSelect > TITLENUM_SELECTTUTORIAL)
			{//�I�����������܂ōs������A��ɖ߂�
				g_Menu.nSelect = TITLENUM_SELECTGAME;
			}

			//�T�E���h�Đ�
			PlaySound(SOUND_LABEL_SE_SELECT1);
		}
		else if (GetKeyboardTrigger(DIK_RETURN) || GetKeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(JOYKEY_A, PLAYER_1) || GetJoypadTrigger(JOYKEY_START, PLAYER_1))
		{//Enter�L�[����
			if (g_Menu.nSelect == TITLENUM_SELECTGAME && !g_Menu.bGameStartPush)
			{//�Q�[���X�^�[�g�̍��ڂ�I��

				//�T�E���h�Đ�
				PlaySound(SOUND_LABEL_SE_SELECT2);

				//��ʑJ��
				SetFade(MODE_GAME);

				//�X�^�[�g���o�̌J��Ԃ��h�~
				g_Menu.bGameStartPush = true;
			}
			else if (g_Menu.nSelect == TITLENUM_SELECTTUTORIAL && !g_Menu.bGameStartPush)
			{//�`���[�g���A�����ڂ�I��

				//�T�E���h�Đ�
				PlaySound(SOUND_LABEL_SE_SELECT2);

				//��ʑJ��
				SetFade(MODE_TUTORIAL);

				//�X�^�[�g���o�̌J��Ԃ��h�~
				g_Menu.bGameStartPush = true;
			}
		}
		//�I�����ڂ𖾂邭����
		g_aTitle[g_Menu.nSelect].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	//--------------------------
	//	PressEnter���
	//--------------------------
	else if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_A, PLAYER_1) || GetJoypadTrigger(JOYKEY_START, PLAYER_1) && !g_Menu.nCntEnter)
	{//Enter�L�[�AA�L�[�ASTART�L�[����(PressEnter���\������Ă����)
		if (g_aTitle[TITLENUM_TITLE].pos.y < SCREEN_HEIGHT / 4.0f)
		{//�^�C�g��������̈ʒu�܂ŗ��Ă��Ȃ��ꍇ
			g_aTitle[TITLENUM_TITLE].pos.y = SCREEN_HEIGHT / 4.0f;		//�^�C�g��������̈ʒu�ɐݒ肷��
		}
		else
		{
			//PreesEnter������
			g_aTitle[TITLENUM_PRESSENTER].bUse = false;

			//�I�������o��������
			g_aTitle[TITLENUM_SELECTGAME].color = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
			g_aTitle[TITLENUM_SELECTTUTORIAL].color = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);

			//�I�������j���[�Ɉڍs����
			g_Menu.nCntEnter = 1;

			//�T�E���h�Đ�
			PlaySound(SOUND_LABEL_SE_SELECT2);
		}
	}
	else if (!g_Menu.nCntEnter)
	{
		if (g_aTitle[TITLENUM_TITLE].pos.y >= SCREEN_HEIGHT / 4.0f)
		{//�^�C�g��������̈ʒu�܂ŗ����ꍇ

			//PressEnter��_�ł�����
			if (g_Menu.nCntColorA == 0)
			{//���l���Z
				g_aTitle[TITLENUM_PRESSENTER].color.a -= 0.03f;
				if (g_aTitle[TITLENUM_PRESSENTER].color.a <= 0.0f)
				{
					g_Menu.nCntColorA = 1;
				}
			}
			else if (g_Menu.nCntColorA == 1)
			{//���l���Z
				g_aTitle[TITLENUM_PRESSENTER].color.a += 0.03f;
				if (g_aTitle[TITLENUM_PRESSENTER].color.a >= 1.0f)
				{
					g_Menu.nCntColorA = 0;
				}
			}
		}
		else
		{//�^�C�g�����ォ��o��(�~�낷)
			g_aTitle[TITLENUM_TITLE].pos += g_aTitle[TITLENUM_TITLE].move;
		}
	}

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aTitle[nCnt].pos.x - (g_aTitle[nCnt].size.x / 2), g_aTitle[nCnt].pos.y - (g_aTitle[nCnt].size.y / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aTitle[nCnt].pos.x + (g_aTitle[nCnt].size.x / 2), g_aTitle[nCnt].pos.y - (g_aTitle[nCnt].size.y / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aTitle[nCnt].pos.x - (g_aTitle[nCnt].size.x / 2), g_aTitle[nCnt].pos.y + (g_aTitle[nCnt].size.y / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aTitle[nCnt].pos.x + (g_aTitle[nCnt].size.x / 2), g_aTitle[nCnt].pos.y + (g_aTitle[nCnt].size.y / 2), 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(g_aTitle[nCnt].color);
		pVtx[1].col = D3DXCOLOR(g_aTitle[nCnt].color);
		pVtx[2].col = D3DXCOLOR(g_aTitle[nCnt].color);
		pVtx[3].col = D3DXCOLOR(g_aTitle[nCnt].color);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;		//���_���̃|�C���^��i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTitle->Unlock();
}

//======================================================
//	�^�C�g����ʂ̕`�揈��
//======================================================
void DrawTitle(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		if (g_aTitle[nCnt].bUse)
		{
			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureTitle[nCnt]);

			//�v���C���[�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
				nCnt * 4,	//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);			//�v���~�e�B�u�i�|���S���j��
		}
	}
}

//======================================================
//	�^�C�g���̐ݒ菈��
//======================================================
void SetTitle(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, D3DXCOLOR color)
{
	for (int nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		if (!g_aTitle[nCnt].bUse)
		{
			g_aTitle[nCnt].pos = pos;			//�ʒu��ݒ�
			g_aTitle[nCnt].move = move;			//�ړ��ʂ�ݒ�
			g_aTitle[nCnt].size = size;			//�T�C�Y(�傫��)��ݒ�
			g_aTitle[nCnt].color = color;		//�F��ݒ�
			g_aTitle[nCnt].bUse = true;			//�g�p��Ԃɂ���

			break;
		}
	}
}