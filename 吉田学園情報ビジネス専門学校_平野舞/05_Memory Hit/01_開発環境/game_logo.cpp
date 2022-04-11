//=============================================================================
//
// ���S���� [game_logo.cpp]
// Author : ���c ����
//
//=============================================================================
#include "main.h"
#include "game_logo.h"
#include "shadow.h"
#include "sound.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturelogo[MAX_LOGO] = { NULL };	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufflogo = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Logo g_aLogo[MAX_LOGO];		//���S�\��
LogoInfo g_LogoInfo;		//���S���

//======================================================
//		�Q�[�����̃��S����������
//======================================================
void InitLogo(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���S���̏�����
	ZeroMemory(&g_aLogo, sizeof(g_aLogo));
	ZeroMemory(&g_LogoInfo, sizeof(LogoInfo));

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Ready.png",
		&g_pTexturelogo[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Start000.png",
		&g_pTexturelogo[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/memorize000.png",
		&g_pTexturelogo[2]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/search000.png",
		&g_pTexturelogo[3]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/finish000.png",
		&g_pTexturelogo[4]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBufflogo,
		NULL);

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBufflogo->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntLogo = 0; nCntLogo < MAX_LOGO; nCntLogo++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aLogo[nCntLogo].pos.x - LOGO_SIZE_X, g_aLogo[nCntLogo].pos.y - LOGO_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aLogo[nCntLogo].pos.x + LOGO_SIZE_X, g_aLogo[nCntLogo].pos.y - LOGO_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aLogo[nCntLogo].pos.x - LOGO_SIZE_X, g_aLogo[nCntLogo].pos.y + LOGO_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aLogo[nCntLogo].pos.x + LOGO_SIZE_X, g_aLogo[nCntLogo].pos.y + LOGO_SIZE_Y, 0.0f);

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
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBufflogo->Unlock();
}

//======================================================
//		�Q�[�����̃��S�̏I������
//======================================================
void UninitLogo(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < MAX_LOGO; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTexturelogo[nCnt] != NULL)
		{
			g_pTexturelogo[nCnt]->Release();
			g_pTexturelogo[nCnt] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBufflogo != NULL)
	{
		g_pVtxBufflogo->Release();
		g_pVtxBufflogo = NULL;
	}
}

//======================================================
//		�Q�[�����̃��S�̍X�V����
//======================================================
void UpdateLogo(void)
{
	g_LogoInfo.nCnt++;

	if (g_LogoInfo.nCnt == 20)
	{
		SetLogo(LOGONUM_READY, 70);

		//�T�E���h�Đ�
		PlaySound(SOUND_LABEL_SE_READY);
	}
	if (g_LogoInfo.nCnt == 100)
	{
		SetLogo(LOGONUM_START, 70);
		SetShadow(0);		//�e�̐ݒ�

		//�T�E���h�Đ�
		PlaySound(SOUND_LABEL_SE_GO);
	}

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBufflogo->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntLogo = 0; nCntLogo < MAX_LOGO; nCntLogo++)
	{
		if (g_aLogo[nCntLogo].bUse == true)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aLogo[nCntLogo].pos.x - LOGO_SIZE_X, g_aLogo[nCntLogo].pos.y - LOGO_SIZE_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aLogo[nCntLogo].pos.x + LOGO_SIZE_X, g_aLogo[nCntLogo].pos.y - LOGO_SIZE_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aLogo[nCntLogo].pos.x - LOGO_SIZE_X, g_aLogo[nCntLogo].pos.y + LOGO_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aLogo[nCntLogo].pos.x + LOGO_SIZE_X, g_aLogo[nCntLogo].pos.y + LOGO_SIZE_Y, 0.0f);
		}

		if (g_aLogo[nCntLogo].nLife != -1)
		{
			g_aLogo[nCntLogo].nLife--;
		}
		if (g_aLogo[nCntLogo].nLife == 0)
		{//������0
			g_aLogo[nCntLogo].bUse = false;
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBufflogo->Unlock();
}

//======================================================
//		�Q�[�����̃��S�̕`�揈��
//======================================================
void DrawLogo(void)
{
	for (int nCntLogo = 0; nCntLogo < MAX_LOGO; nCntLogo++)
	{
		if (g_aLogo[nCntLogo].bUse == true)
		{
			//�f�o�C�X�̎擾
			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBufflogo, 0, sizeof(VERTEX_2D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexturelogo[g_aLogo[nCntLogo].nType]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
				0,				//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);				//�v���~�e�B�u�i�|���S���j��
		}
	}
}

//======================================================
//		�Q�[�����̃��S�̐ݒ菈��
//======================================================
void SetLogo(int nType,int nLife)
{
	for (int nCntLogo = 0; nCntLogo < MAX_LOGO; nCntLogo++)
	{
		if (!g_aLogo[nCntLogo].bUse)
		{
			g_aLogo[nCntLogo].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
			g_aLogo[nCntLogo].nType = nType;
			g_aLogo[nCntLogo].nLife = nLife;
			g_aLogo[nCntLogo].bUse = true;

			VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

			// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBufflogo->Lock(0, 0, (void**)&pVtx, 0);

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aLogo[nCntLogo].pos.x - LOGO_SIZE_X, g_aLogo[nCntLogo].pos.y - LOGO_SIZE_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aLogo[nCntLogo].pos.x + LOGO_SIZE_X, g_aLogo[nCntLogo].pos.y - LOGO_SIZE_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aLogo[nCntLogo].pos.x - LOGO_SIZE_X, g_aLogo[nCntLogo].pos.y + LOGO_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aLogo[nCntLogo].pos.x + LOGO_SIZE_X, g_aLogo[nCntLogo].pos.y + LOGO_SIZE_Y, 0.0f);

			//���_�o�b�t�@���A�����b�N
			g_pVtxBufflogo->Unlock();

			break;
		}
	}
}