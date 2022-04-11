#include "main.h"
#include "result.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "score.h"
#include "game.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureResult[MAX_RESULT] = { NULL };	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult[MAX_RESULT] = {};	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureResultScore = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultScore = NULL;		//���_�o�b�t�@�ւ̃|�C���^
bool g_GameResultPush;				//���U���g���o�̌J��Ԃ��h�~
D3DXVECTOR3 g_resultpos;			//���U���g�̈ʒu
D3DXVECTOR3 g_resultscorepos[2];		//���U���g�X�R�A�̈ʒu
int g_nResultScore;

//======================================================
//		���U���g��ʂ̏���������
//======================================================
void InitResult(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Result.jpg",
		&g_pTextureResult[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/You_Score.png",
		&g_pTextureResult[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number000.png",
		&g_pTextureResultScore);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult[0],
		NULL);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult[1],
		NULL);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultScore,
		NULL);

	g_GameResultPush = false;			//�I�����o�J��Ԃ��h�~�̏�����
	g_resultpos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f), 500.0f, 0.0f);
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		g_resultscorepos[nCnt] = D3DXVECTOR3(SCORE_SIZE_X * nCnt + (SCREEN_WIDTH / 2.0f) - (SCORE_SIZE_X / 2.0f), 500.0f, 0.0f);
	}

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

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
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffResult[0]->Unlock();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult[1]->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_resultpos.x - (SCREEN_WIDTH / 2.0f), g_resultpos.y - (SCREEN_HEIGHT / 2.0f), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_resultpos.x + (SCREEN_WIDTH / 2.0f), g_resultpos.y - (SCREEN_HEIGHT / 2.0f), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_resultpos.x - (SCREEN_WIDTH / 2.0f), g_resultpos.y + (SCREEN_HEIGHT / 2.0f), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_resultpos.x + (SCREEN_WIDTH / 2.0f), g_resultpos.y + (SCREEN_HEIGHT / 2.0f), 0.0f);

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
	g_pVtxBuffResult[1]->Unlock();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResultScore->Lock(0, 0, (void**)&pVtx, 0);

	//�X�R�A�ݒ�
	int nResultScore = GetScore();

	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_resultscorepos[nCnt].x - (SCORE_SIZE_X / 2.0f), g_resultscorepos[nCnt].y - (SCORE_SIZE_Y / 2.0f), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_resultscorepos[nCnt].x + (SCORE_SIZE_X / 2.0f), g_resultscorepos[nCnt].y - (SCORE_SIZE_Y / 2.0f), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_resultscorepos[nCnt].x - (SCORE_SIZE_X / 2.0f), g_resultscorepos[nCnt].y + (SCORE_SIZE_Y / 2.0f), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_resultscorepos[nCnt].x + (SCORE_SIZE_X / 2.0f), g_resultscorepos[nCnt].y + (SCORE_SIZE_Y / 2.0f), 0.0f);

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

		int aPosTexU[MAX_SCORE];		//�e���̐������i�[

		aPosTexU[0] = nResultScore % 100 / 10;
		aPosTexU[1] = nResultScore % 10 / 1;

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexU[nCnt], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f * (aPosTexU[nCnt] + 1), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexU[nCnt], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f * (aPosTexU[nCnt] + 1), 1.0f);

		pVtx += 4;  //���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffResultScore->Unlock();

	//�T�E���h�Đ�
	PlaySound(SOUND_LABEL_BGM002);

}

//======================================================
//		���U���g��ʂ̏I������
//======================================================
void UninitResult(void)
{
	for (int nCnt = 0; nCnt < MAX_RESULT; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureResult[nCnt] != NULL)
		{
			g_pTextureResult[nCnt]->Release();
			g_pTextureResult[nCnt] = NULL;
		}
	}

	//�e�N�X�`���̔j��
	if (g_pTextureResultScore != NULL)
	{
		g_pTextureResultScore->Release();
		g_pTextureResultScore = NULL;
	}

	for (int nCnt = 0; nCnt < MAX_RESULT; nCnt++)
	{
		//���_�o�b�t�@�̔j��
		if (g_pVtxBuffResult[nCnt] != NULL)
		{
			g_pVtxBuffResult[nCnt]->Release();
			g_pVtxBuffResult[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffResultScore != NULL)
	{
		g_pVtxBuffResultScore->Release();
		g_pVtxBuffResultScore = NULL;
	}
}

//======================================================
//		���U���g��ʂ̍X�V����
//======================================================
void UpdateResult(void)
{
	if (g_GameResultPush == false)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A, PLAYER_1) == true || GetJoypadTrigger(JOYKEY_START, PLAYER_1) == true)
		{//�G���^�[�L�[�������ꂽ��
			//���[�h�ڍs
			SetFade(MODE_RANK);

			//���U���g���o�̌J��Ԃ��h�~
			g_GameResultPush = true;
		}
	}
}

//======================================================
//		���U���g��ʂ̕`�揈��
//======================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_RESULT; nCnt++)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffResult[nCnt], 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureResult[nCnt]);

		//�v���C���[�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
			0,		//�`�悷��ŏ��̒��_�C���f�b�N�X
			2);		//�v���~�e�B�u�i�|���S���j��
	}

	{//���U���g�X�R�A�̕`��
	 //���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffResultScore, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureResultScore);

		for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
				4 * nCnt,		//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);				//�v���~�e�B�u�i�|���S���j��
		}
	}
}