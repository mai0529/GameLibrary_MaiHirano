//=============================================================================
//
//	�|�[�Y��ʏ��� [pause.cpp]
//	Author : ���c ����
//
//=============================================================================

//======================================================
//	�C���N���[�h
//======================================================
#include "main.h"
#include "game.h"
#include "bg.h"
#include "time.h"
#include "sound.h"
#include "fade.h"
#include "input.h"
#include "particle.h"

//======================================================
//	�}�N����`
//======================================================
#define	PAUSE_IMAGE_MAX			(4)			//�|�[�Y��ʂɕK�v�ȉ摜��
#define	PAUSE_SELECT_MAX		(3)			//�|�[�Y��ʂɕK�v�ȑI��
#define PAUSE_UI_SIZE_X			(1000.0f)	//�|�[�Y���UI��X�T�C�Y
#define PAUSE_UI_SIZE_Y			(400.0f)	//�|�[�Y���UI��Y�T�C�Y
#define PAUSE_SELECT_SIZE_X		(200.0f)	//�|�[�Y��ʂ̑I�����ڂ�X�T�C�Y
#define PAUSE_SELECT_SIZE_Y		(200.0f)	//�|�[�Y��ʂ̑I�����ڂ�Y�T�C�Y

//======================================================
//	�O���[�o���ϐ�
//======================================================
LPDIRECT3DTEXTURE9 g_pTexturePause[PAUSE_IMAGE_MAX] = { NULL };	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause[3] = { NULL };			//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_PausePos[2];		//�|�[�Y��ʂ̈ʒu
bool g_bPause;					//�Q�[���̃|�[�Y(�ꎞ��~)����
float g_fColPauseA[PAUSE_IMAGE_MAX + 1];	//�|�[�Y�A���t�@�l
int g_nPauseSelecting;						//�|�[�Y��ʒ��ɑI���������ڂ̕ϐ�
int g_nCntCol;			//�|�[�Y��ʂ̃t�F�[�h�̏o�����p
int g_nColPoseCnt;		//�|�[�Y��ʒ��ɑI�����Ă��鍀�ڂ��`�J�`�J������p�ϐ�
int g_nFade;			//�t�F�[�h�܂ł̗]�C

//======================================================
//	�|�[�Y��ʂ̏���������
//======================================================
void InitPause(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e���ڂ̏�����
	g_PausePos[0] = D3DXVECTOR3(SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 2.0f, 0.0f);				//�|�[�Y��ʂ̑I�����ڈʒu�̏�����
	g_PausePos[1] = D3DXVECTOR3(SCREEN_WIDTH / 2.0f, (SCREEN_HEIGHT / 2.0f) - 20.0f, 0.0f);		//�|�[�Y���UI�̈ʒu�̏�����
	g_nCntCol = 0;			//�|�[�Y��ʂ̃t�F�[�h�̏o�����p
	g_nFade = 0;			//�t�F�[�h�܂ł̗]�C
	g_nPauseSelecting = 2;	//�Q�[���𑱂����I���ɏ�����
	g_nColPoseCnt = 0;		//�|�[�Y��ʒ��ɑI�����Ă��鍀�ڂ��`�J�`�J������p�̏�����
	g_bPause = false;		//�|�[�Y����

	//�|�[�Y��ʂ�����������
	for (int nCnt = 0; nCnt < PAUSE_IMAGE_MAX + 1; nCnt++)
	{
		g_fColPauseA[nCnt] = 0.0f;	//�|�[�Y�A���t�@�l������
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Pause000.png",
		&g_pTexturePause[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Pause001.png",
		&g_pTexturePause[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Pause002.png",
		&g_pTexturePause[2]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/PauseUI000.png",
		&g_pTexturePause[3]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,		//��ʑS�̂̃o�b�t�@
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause[0],
		NULL);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,		//�|�[�YUI�̃o�b�t�@
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause[1],
		NULL);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * PAUSE_SELECT_MAX,		//�|�[�Y�I�����ڂ̃o�b�t�@
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause[2],
		NULL);

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause[0]->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_fColPauseA[0]);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_fColPauseA[0]);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_fColPauseA[0]);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_fColPauseA[0]);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPause[0]->Unlock();


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause[1]->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_PausePos[1].x - (PAUSE_UI_SIZE_X / 2), g_PausePos[1].y - (PAUSE_UI_SIZE_Y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_PausePos[1].x + (PAUSE_UI_SIZE_X / 2), g_PausePos[1].y - (PAUSE_UI_SIZE_Y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_PausePos[1].x - (PAUSE_UI_SIZE_X / 2), g_PausePos[1].y + (PAUSE_UI_SIZE_Y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_PausePos[1].x + (PAUSE_UI_SIZE_X / 2), g_PausePos[1].y + (PAUSE_UI_SIZE_Y / 2), 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fColPauseA[1]);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fColPauseA[1]);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fColPauseA[1]);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fColPauseA[1]);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPause[1]->Unlock();


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause[2]->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < PAUSE_SELECT_MAX; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3((g_PausePos[0].x + 200.0f * nCnt) - (PAUSE_SELECT_SIZE_X / 2), g_PausePos[0].y - (PAUSE_SELECT_SIZE_Y / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3((g_PausePos[0].x + 200.0f * nCnt) + (PAUSE_SELECT_SIZE_X / 2), g_PausePos[0].y - (PAUSE_SELECT_SIZE_Y / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3((g_PausePos[0].x + 200.0f * nCnt) - (PAUSE_SELECT_SIZE_X / 2), g_PausePos[0].y + (PAUSE_SELECT_SIZE_Y / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3((g_PausePos[0].x + 200.0f * nCnt) + (PAUSE_SELECT_SIZE_X / 2), g_PausePos[0].y + (PAUSE_SELECT_SIZE_Y / 2), 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fColPauseA[2 + nCnt]);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fColPauseA[2 + nCnt]);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fColPauseA[2 + nCnt]);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fColPauseA[2 + nCnt]);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;  //���_�f�[�^�̃|�C���^���S���i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPause[2]->Unlock();
}

//======================================================
//	�|�[�Y��ʂ̏I������
//======================================================
void UninitPause(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < PAUSE_IMAGE_MAX; nCnt++)
	{
		if (g_pTexturePause[nCnt] != NULL)
		{
			g_pTexturePause[nCnt]->Release();
			g_pTexturePause[nCnt] = NULL;
		}
	}

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		//���_�o�b�t�@�̔j��
		if (g_pVtxBuffPause[nCnt] != NULL)
		{
			g_pVtxBuffPause[nCnt]->Release();
			g_pVtxBuffPause[nCnt] = NULL;
		}
	}
}

//======================================================
//	�|�[�Y��ʂ̍X�V����
//======================================================
bool UpdatePause(void)
{
	//P�L�[�܂���Start�{�^���������ꂽ�ꍇ
	if (GetKeyboardTrigger(DIK_P) == true || GetJoypadTrigger(JOYKEY_START, 0) && g_bPause == false)
	{
		//�Q�[�����~�߂�
		g_nCntCol = 0;
		g_bPause = true;
	}

	//�|�[�Y���̏ꍇ
	if (g_bPause == true)
	{
		if (g_nCntCol == 0)
		{//�o�b�N�̃Q�[����ʂ��Â�����
			g_fColPauseA[0] += 0.1f;
			if (g_fColPauseA[0] > 0.5f)
			{
				g_fColPauseA[0] = 0.5f;
				g_nCntCol = 1;
			}
		}
		else if (g_nCntCol == 1)
		{//�|�[�Y��ʂ��o��
			for (int nCnt = 1; nCnt < PAUSE_IMAGE_MAX + 1; nCnt++)
			{
				g_fColPauseA[nCnt] += 0.1f;
				if (g_fColPauseA[nCnt] > 1.0f)
				{
					g_fColPauseA[nCnt] = 1.0f;
					g_nCntCol = 2;
				}
			}
		}
		else if (g_nCntCol == 2)
		{//�|�[�Y�I�����
			if (GetKeyboardTrigger(DIK_LEFT) == true || GetJoypadTrigger(JOYKEY_LEFT, 0))
			{
				g_nPauseSelecting--;
				//�I�����Ă��Ȃ����ڂ̃��Z�b�g
				g_fColPauseA[2] = 1.0f;
				g_fColPauseA[3] = 1.0f;
				g_fColPauseA[4] = 1.0f;
				if (g_nPauseSelecting < 2)
				{
					g_nPauseSelecting = 4;
				}
			}
			else if (GetKeyboardTrigger(DIK_RIGHT) == true || GetJoypadTrigger(JOYKEY_RIGHT, 0))
			{
				g_nPauseSelecting++;
				//�I�����Ă��Ȃ����ڂ̃��Z�b�g
				g_fColPauseA[2] = 1.0f;
				g_fColPauseA[3] = 1.0f;
				g_fColPauseA[4] = 1.0f;
				if (g_nPauseSelecting > 4)
				{
					g_nPauseSelecting = 2;
				}
			}
			else if (GetKeyboardTrigger(DIK_RETURN) || GetKeyboardTrigger(DIK_SPACE) == true || GetJoypadTrigger(JOYKEY_A, 0))
			{
				if (g_nPauseSelecting == 2)
				{//�Q�[���𑱂���
					g_bPause = false;
				}
				else if (g_nPauseSelecting == 3)
				{//���g���C
					//DiedPlayer();
					SetFade(MODE_GAME);
				}
				else if (g_nPauseSelecting == 4)
				{//�^�C�g���ɖ߂�
					SetFade(MODE_TITLE);
				}
			}

			if (g_nColPoseCnt == 0)
			{//�I�𒆂̍��ڂ��`�J�`�J������
				g_fColPauseA[g_nPauseSelecting] -= 0.05f;
				if (g_fColPauseA[g_nPauseSelecting] < 0.0f)
				{
					g_fColPauseA[g_nPauseSelecting] = 0.0f;
					g_nColPoseCnt = 1;
				}
			}
			else if (g_nColPoseCnt == 1)
			{
				g_fColPauseA[g_nPauseSelecting] += 0.05f;
				if (g_fColPauseA[g_nPauseSelecting] > 1.0f)
				{
					g_fColPauseA[g_nPauseSelecting] = 1.0f;
					g_nColPoseCnt = 0;
				}
			}
		}
	}
	else
	{//�|�[�Y��ʂ��o���Ă��Ȃ��Ƃ�
		for (int nCnt = 0; nCnt < PAUSE_IMAGE_MAX + 1; nCnt++)
		{
			g_fColPauseA[nCnt] -= 0.1f;
			if (g_fColPauseA[nCnt] < 0.0f)
			{
				g_fColPauseA[nCnt] = 0.0f;
			}
		}
	}

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause[0]->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_fColPauseA[0]);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_fColPauseA[0]);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_fColPauseA[0]);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_fColPauseA[0]);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPause[0]->Unlock();


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause[1]->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fColPauseA[1]);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fColPauseA[1]);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fColPauseA[1]);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fColPauseA[1]);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPause[1]->Unlock();


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause[2]->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < PAUSE_SELECT_MAX; nCnt++)
	{
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fColPauseA[nCnt + 2]);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fColPauseA[nCnt + 2]);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fColPauseA[nCnt + 2]);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fColPauseA[nCnt + 2]);

		pVtx += 4;  //���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPause[2]->Unlock();

	return g_bPause;
}

//======================================================
//	�|�[�Y��ʂ̕`�揈��
//======================================================
void DrawPause(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause[0], 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
		0,		//�`�悷��ŏ��̒��_�C���f�b�N�X
		2);		//�v���~�e�B�u�i�|���S���j��


	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause[1], 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePause[3]);
	//�v���C���[�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
		0,		//�`�悷��ŏ��̒��_�C���f�b�N�X
		2);		//�v���~�e�B�u�i�|���S���j��


	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause[2], 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < PAUSE_SELECT_MAX; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePause[nCnt]);
		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
			4 * nCnt,	//�`�悷��ŏ��̒��_�C���f�b�N�X
			2);			//�v���~�e�B�u�i�|���S���j��
	}
}