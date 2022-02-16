//-------------------------------------------
//
//���U���g����[result.cpp]
//Author:���앑
//
//-------------------------------------------

//�C���N���[�h�t�@�C��
#include "result.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureResult[2] = {};			//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult[3] = {};		//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posRank[8];								//�X�R�A�̈ʒu
Result g_nResult;										//�X�R�A�̒l

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
		"data/TEXTURE/result007.jpg",
		&g_pTextureResult[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number001.png",
		&g_pTextureResult[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult[0],
		NULL);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult[1],
		NULL);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult[2],
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//�w�i
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult[0]->Lock(0, 0, (void**)&pVtx, 0);

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

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult[0]->Unlock();

	//�X�R�A
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult[1]->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < 8; nCount++)
	{//�X�R�A�̐ݒu
		g_posRank[nCount] = D3DXVECTOR3(450.0f + (70.0f * nCount), 260.0f, 0.0f);
	}

	for (int nCount = 0; nCount < 8; nCount++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posRank[nCount].x - (RESULT_WIDTH / 2), g_posRank[nCount].y - (RESULT_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posRank[nCount].x + (RESULT_WIDTH / 2), g_posRank[nCount].y - (RESULT_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posRank[nCount].x - (RESULT_WIDTH / 2), g_posRank[nCount].y + (RESULT_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posRank[nCount].x + (RESULT_WIDTH / 2), g_posRank[nCount].y + (RESULT_HEIGHT / 2), 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult[1]->Unlock();

	//�P�[�L
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult[2]->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(700.0f - (RESULT_WIDTH / 2.0f), 500.0f - (RESULT_HEIGHT / 2.0f), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(700.0f + (RESULT_WIDTH / 2.0f), 500.0f - (RESULT_HEIGHT / 2.0f), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(700.0f - (RESULT_WIDTH / 2.0f), 500.0f + (RESULT_HEIGHT / 2.0f), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(700.0f + (RESULT_WIDTH / 2.0f), 500.0f + (RESULT_HEIGHT / 2.0f), 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult[2]->Unlock();

	SetResult();

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

	for (int nCount = 0; nCount < 2 ; nCount++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureResult[nCount] != NULL)
		{
			g_pTextureResult[nCount]->Release();
			g_pTextureResult[nCount] = NULL;
		}
	}

	for (int nCount = 0; nCount < 3; nCount++)
	{
		//���_�o�b�t�@�̔j��
		if (g_pVtxBuffResult[nCount] != NULL)
		{
			g_pVtxBuffResult[nCount]->Release();
			g_pVtxBuffResult[nCount] = NULL;
		}
	}
}

//-------------------------------------------
//�X�V��������
//-------------------------------------------
void UpdateResult(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		PlaySound(SOUND_LABEL_SE000);
		//���[�h�ݒ�
		SetFade(MODE_RANKING);
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
	pDevice->SetStreamSource(0, g_pVtxBuffResult[0], 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�w�i
	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureResult[0]);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�X�R�A
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult[1], 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntX = 0; nCntX < 8; nCntX++)
	{
		//�e�N�X�`���ݒ�
		pDevice->SetTexture(0, g_pTextureResult[1]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntX * 4, 2);
	}

	//�P�[�L��
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult[2], 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureResult[1]);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//-------------------------------------------
//���Z�b�g����
//-------------------------------------------
void ResetResult(void)
{
	g_nResult.nScore = 0;		//�X�R�A�̃��Z�b�g
	g_nResult.nData = 0;		//�P�[�L�̐��̃��Z�b�g
}

//-------------------------------------------
//�ݒ菈��
//-------------------------------------------
void SetResult(void)
{
	//�X�R�A�̏��
	g_nResult.nScore = GetScore();
	int aPosTexU[8];

	aPosTexU[0] = g_nResult.nScore % 100000000 / 10000000;
	aPosTexU[1] = g_nResult.nScore % 10000000 / 1000000;
	aPosTexU[2] = g_nResult.nScore % 1000000 / 100000;
	aPosTexU[3] = g_nResult.nScore % 100000 / 10000;
	aPosTexU[4] = g_nResult.nScore % 10000 / 1000;
	aPosTexU[5] = g_nResult.nScore % 1000 / 100;
	aPosTexU[6] = g_nResult.nScore % 100 / 10;
	aPosTexU[7] = g_nResult.nScore % 10 / 1;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult[1]->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	for (int nCount = 0; nCount < SCORE_MAX; nCount++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[nCount], 0.0f);
		pVtx[1].tex = D3DXVECTOR2((0.1f * aPosTexU[nCount]) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[nCount], 1.0f);
		pVtx[3].tex = D3DXVECTOR2((0.1f * aPosTexU[nCount]) + 0.1f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult[1]->Unlock();

	//�P�[�L�̐��̏��
	g_nResult.nData = GetnCount();
	int aPosTexU2;

	aPosTexU2 = g_nResult.nData % 10 / 1;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult[2]->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU2, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((0.1f * aPosTexU2) + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU2, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((0.1f * aPosTexU2) + 0.1f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult[2]->Unlock();
}