//-------------------------------------------
//
//�X�R�A����[score.cpp]
//Author:���앑
//
//-------------------------------------------

//�C���N���[�h�t�@�C��
#include "score.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;			//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posScore[8];							//�X�R�A�̈ʒu
int g_nScore;										//�X�R�A�̒l

//-------------------------------------------
//����������
//-------------------------------------------
void InitScore(void)
{
	int nCount;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number001.png",
		&g_pTextureScore);

	for (nCount = 0; nCount < SCORE_MAX; nCount++)
	{
		g_posScore[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�ʒu������������
	}
		g_nScore = 0;													//�l������������
		
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCount = 0; nCount < 8; nCount++)
	{
		//�X�R�A�̐ݒu�ꏊ
		g_posScore[nCount] = D3DXVECTOR3(1070.0f + (25.0f * nCount), 30.0f, 0.0f);
	}

	for (nCount = 0; nCount < SCORE_MAX; nCount++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posScore[nCount].x - (SCORE_WIDTH / 2), g_posScore[nCount].y - (SCORE_HEIGHT / 2), 0);
		pVtx[1].pos = D3DXVECTOR3(g_posScore[nCount].x + (SCORE_WIDTH / 2), g_posScore[nCount].y - (SCORE_HEIGHT / 2), 0);
		pVtx[2].pos = D3DXVECTOR3(g_posScore[nCount].x - (SCORE_WIDTH / 2), g_posScore[nCount].y + (SCORE_HEIGHT / 2), 0);
		pVtx[3].pos = D3DXVECTOR3(g_posScore[nCount].x + (SCORE_WIDTH / 2), g_posScore[nCount].y + (SCORE_HEIGHT / 2), 0);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(0.0f, 0.8f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.8f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.8f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.8f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;		//���_�f�[�^���S���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();

	SetScore(0);
}

//-------------------------------------------
//�I������
//-------------------------------------------
void UninitScore(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffScore != NULL)
	{	
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//-------------------------------------------
//�X�V����
//-------------------------------------------
void UpdateScore(void)
{
	//(���̂Ƃ���Ȃ�)
}

//-------------------------------------------
//�`�揈��
//-------------------------------------------
void DrawScore(void)
{
	int nCntScore;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntScore = 0; nCntScore < SCORE_MAX; nCntScore++)
	{
		//�e�N�X�`���ݒ�
		pDevice->SetTexture(0, g_pTextureScore);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
	}
}

//-------------------------------------------
//�X�R�A�̐ݒ菈��
//-------------------------------------------
void SetScore(int nScore)
{
	int aPosTexU[SCORE_MAX];			//�e���̐������i�[
	int nCountScore;

	g_nScore = nScore;

	aPosTexU[0] = g_nScore % 100000000 / 10000000;
	aPosTexU[1] = g_nScore % 10000000 / 1000000;
	aPosTexU[2] = g_nScore % 1000000 / 100000;
	aPosTexU[3] = g_nScore % 100000 / 10000;
	aPosTexU[4] = g_nScore % 10000 / 1000;
	aPosTexU[5] = g_nScore % 1000 / 100;
	aPosTexU[6] = g_nScore % 100 / 10;
	aPosTexU[7] = g_nScore % 10 / 1;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	for (nCountScore = 0; nCountScore < SCORE_MAX; nCountScore++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[nCountScore], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f * aPosTexU[nCountScore] + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[nCountScore], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f * aPosTexU[nCountScore] + 0.1f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

//-------------------------------------------
//�X�R�A�̉��Z����
//-------------------------------------------
void AddScore(int nValue)
{
	int aPosTexU[SCORE_MAX];		//�e���̐������i�[
	int nCountScore;

	g_nScore += nValue;

	aPosTexU[0] = g_nScore % 100000000 / 10000000;
	aPosTexU[1] = g_nScore % 10000000 / 1000000;
	aPosTexU[2] = g_nScore % 1000000 / 100000;
	aPosTexU[3] = g_nScore % 100000 / 10000;
	aPosTexU[4] = g_nScore % 10000 / 1000;
	aPosTexU[5] = g_nScore % 1000 / 100;
	aPosTexU[6] = g_nScore % 100 / 10;
	aPosTexU[7] = g_nScore % 10 / 1;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	for (nCountScore = 0; nCountScore < SCORE_MAX; nCountScore++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[nCountScore], 0.0f);
		pVtx[1].tex = D3DXVECTOR2((0.1f * aPosTexU[nCountScore]) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[nCountScore], 1.0f);
		pVtx[3].tex = D3DXVECTOR2((0.1f * aPosTexU[nCountScore]) + 0.1f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

//-------------------------------------------
//�X�R�A�̎擾
//-------------------------------------------
int GetScore(void)
{
	return g_nScore;
}