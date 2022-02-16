//-------------------------------------------
//
//�����L���O����[ranking.cpp](������)
//Author:���앑
//
//-------------------------------------------
#include "ranking.h"

//�����L���O�\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	int nScore;			//�X�R�A
}RankScore;

//�}�N����`
#define RANKING_WIDTH			(50)		//���ʂ̕�
#define RANKING_HEIGHT			(100)		//���ʂ̍���
#define RANKINGSCORE_WIDTH		(50)		//�X�R�A�̕�
#define RANKINGSCORE_HEIGHT		(100)		//�X�R�A�̍���

//�O���[�o���錾
LPDIRECT3DTEXTURE9 g_pTextureRank = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureRankScore = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;			//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankScore = NULL;		//���_�o�b�t�@�ւ̃|�C���^
RankScore g_aRankScore[MAX_RANK];						//�����L���O�X�R�A���
int g_nRankUpdata = -1;									//�X�V�����NNo.
int g_nTimerRanking;									//�����L���O��ʕ\���^�C�}�[

//-------------------------------------------
//����������
//-------------------------------------------
void InitRanking(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ranking_rank.png",
		&g_pTextureRank);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRank,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(100 - RANKINGSCORE_WIDTH, 50 - RANKING_HEIGHT, 0);
	pVtx[1].pos = D3DXVECTOR3(100 + RANKINGSCORE_WIDTH, 50 - RANKING_HEIGHT, 0);
	pVtx[2].pos = D3DXVECTOR3(100 - RANKINGSCORE_WIDTH, 50 + RANKING_HEIGHT, 0);
	pVtx[3].pos = D3DXVECTOR3(100 + RANKINGSCORE_WIDTH, 50 + RANKING_HEIGHT, 0);

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
	g_pVtxBuffRank->Unlock();

	////�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,
	//	"data/TEXTURE/number000.png",
	//	&g_pTextureRankScore);

	////���_�o�b�t�@�̐���
	//pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
	//	D3DUSAGE_WRITEONLY,
	//	FVF_VERTEX_2D,
	//	D3DPOOL_MANAGED,
	//	&g_pVtxBuffRankScore,
	//	NULL);

	////���_���ւ̃|�C���^
	//VERTEX_2D *pVtx;

	////���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	//g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

	////���_���W�̐ݒ�
	//pVtx[0].pos = D3DXVECTOR3(500 - RANKING_WIDTH, 50 - RANKINGSCORE_HEIGHT, 0);
	//pVtx[1].pos = D3DXVECTOR3(500 + RANKING_WIDTH, 50 - RANKINGSCORE_HEIGHT, 0);
	//pVtx[2].pos = D3DXVECTOR3(500 - RANKING_WIDTH, 50 + RANKINGSCORE_HEIGHT, 0);
	//pVtx[3].pos = D3DXVECTOR3(500 + RANKING_WIDTH, 50 + RANKINGSCORE_HEIGHT, 0);

	////rhw�̐ݒ�
	//pVtx[0].rhw = 1.0f;
	//pVtx[1].rhw = 1.0f;
	//pVtx[2].rhw = 1.0f;
	//pVtx[3].rhw = 1.0f;

	////���_�J���[�̐ݒ�
	//pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	////�e�N�X�`�����W�̐ݒ�
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	////���_�o�b�t�@���A�����b�N����
	//g_pVtxBuffRankScore ->Unlock();

}

//-------------------------------------------
//�I������
//-------------------------------------------
void UninitRanking(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureRank != NULL)
	{
		g_pTextureRank->Release();
		g_pTextureRank = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRank != NULL)
	{
		g_pVtxBuffRank->Release();
		g_pVtxBuffRank = NULL;
	}

	////�e�N�X�`���̔j��
	//if (g_pTextureRankScore != NULL)
	//{
	//	g_pTextureRankScore->Release();
	//	g_pTextureRankScore = NULL;
	//}

	////���_�o�b�t�@�̔j��
	//if (g_pVtxBuffRankScore != NULL)
	//{
	//	g_pVtxBuffRankScore->Release();
	//	g_pVtxBuffRankScore = NULL;
	//}
}

//-------------------------------------------
//�X�V����
//-------------------------------------------
void UpdateRanking(void)
{
	if (g_nRankUpdata != -1)
	{

	}
	//if ()
	{

	}
}

//-------------------------------------------
//�`�揈��
//-------------------------------------------
void DrawRanking(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureRank);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//-------------------------------------------
//�����L���O�̃��Z�b�g
//-------------------------------------------
void ResetRanking(void)
{

}

//-------------------------------------------
//�����L���O�̐ݒ�
//-------------------------------------------
void SetRanking(int nScore)
{
	int nCntRank;

	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{

	}
}
