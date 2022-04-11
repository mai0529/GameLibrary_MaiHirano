//-------------------------------------------
//
//	�X�R�A����
//	Author:���슲��
//
//-------------------------------------------
#include "main.h"
#include "score.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureScoreLogo = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScoreLogo = NULL;	//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posScore[2];								//�X�R�A�̈ʒu
D3DXVECTOR3 g_posScoreLogo;							//�X�R�A���S�̈ʒu
int g_nScore;										//�X�R�A�̒l

//----------------------------------------
//  �X�R�A�̏������ݒ菈��
//----------------------------------------
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();			//�f�o�C�X�̎擾

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &g_pTextureScore);

	//���S�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Score_rogo.png", &g_pTextureScoreLogo);


	for (int nCntScore = 0; nCntScore < 2; nCntScore++)
	{
		g_posScore[nCntScore] = D3DXVECTOR3(SCORE_SIZE_X * nCntScore + 1050.0f, 500.0f, 0.0f);
	}
	g_posScoreLogo = D3DXVECTOR3(1100.0f, 500.0f, 0.0f);	//�X�R�A���S�̈ʒu������
	g_nScore = 0;			//�l�̏�����

	//�X�R�A�̒��_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	//�X�R�A���S�̒��_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScoreLogo,
		NULL);

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	{//�X�R�A
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_posScore[nCnt].x - (SCORE_SIZE_X / 2.0f), g_posScore[nCnt].y - (SCORE_SIZE_Y / 2.0f), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posScore[nCnt].x + (SCORE_SIZE_X / 2.0f), g_posScore[nCnt].y - (SCORE_SIZE_Y / 2.0f), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posScore[nCnt].x - (SCORE_SIZE_X / 2.0f), g_posScore[nCnt].y + (SCORE_SIZE_Y / 2.0f), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posScore[nCnt].x + (SCORE_SIZE_X / 2.0f), g_posScore[nCnt].y + (SCORE_SIZE_Y / 2.0f), 0.0f);

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
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			pVtx += 4;  //���_�f�[�^�̃|�C���^���S���i�߂�
		}
		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffScore->Unlock();
	}

	{//�X�R�A���S
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffScoreLogo->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posScoreLogo.x - 250.0f, g_posScoreLogo.y - 120.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posScoreLogo.x + 250.0f, g_posScoreLogo.y - 120.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posScoreLogo.x - 250.0f, g_posScoreLogo.y + 120.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posScoreLogo.x + 250.0f, g_posScoreLogo.y + 120.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffScoreLogo->Unlock();
	}
}

//----------------------------------------
//�@�X�R�A�̏I������
//----------------------------------------
void UninitScore(void)
{
	{//�X�R�A
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

	{//�X�R�A���S
		//�e�N�X�`���̔j��
		if (g_pTextureScoreLogo != NULL)
		{
			g_pTextureScoreLogo->Release();
			g_pTextureScoreLogo = NULL;
		}
		//���_�o�b�t�@�̔j��
		if (g_pVtxBuffScoreLogo != NULL)
		{
			g_pVtxBuffScoreLogo->Release();
			g_pVtxBuffScoreLogo = NULL;
		}
	}
}

//----------------------------------------
//  �v���C���[�̍X�V����
//----------------------------------------
void UpdateScore(void)
{
	SetScore(g_nScore);
}

//----------------------------------------
//  �X�R�A�̕`�揈��
//----------------------------------------
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	{//�X�R�A���S�̕`��
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffScoreLogo, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureScoreLogo);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
			0,		//�`�悷��ŏ��̒��_�C���f�b�N�X
			2);				//�v���~�e�B�u�i�|���S���j��
	}

	{//�X�R�A�̕`��
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureScore);

		for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
				4 * nCnt,		//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);				//�v���~�e�B�u�i�|���S���j��
		}
	}
}

//----------------------------------------
//  �X�R�A�̐ݒ菈��
//----------------------------------------
void SetScore(int nScore)
{
	int aPosTexU[MAX_SCORE];		//�e���̐������i�[

	//�X�R�A����
	g_nScore = nScore;

	if (g_nScore <= 0)
	{//�X�R�A��0�ȉ�
		g_nScore = 0;		//0�ɖ߂�
	}

	aPosTexU[0] = g_nScore % 100 / 10;
	aPosTexU[1] = g_nScore % 10 / 1;

	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[nCnt], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f * (aPosTexU[nCnt] + 1), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[nCnt], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f * (aPosTexU[nCnt] + 1), 1.0f);

		pVtx += 4;  //���_�f�[�^�̃|�C���^���S���i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffScore->Unlock();
}

//----------------------------------------
//  �X�R�A�̉��Z����
//----------------------------------------
void AddScore(int nValue)
{
	//�X�R�A�ɒl�ǉ�
	g_nScore += nValue;
}

//----------------------------------------
//  �X�R�A���擾
//----------------------------------------
int GetScore(void)
{
	return g_nScore;
}