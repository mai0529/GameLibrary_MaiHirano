//-------------------------------------------
//
//�^�C�}�[����[time.cpp]
//Author:���앑
//
//-------------------------------------------

//�C���N���[�h�t�@�C��
#include "time.h"
#include "game_logo.h"
#include "fade.h"
#include "shadow.h"
#include "sound.h"

//�}�N����`
#define TIME_WIDTH		(20.0f)		//�^�C���̕�
#define TIME_HEIGHT		(45.0f)		//�^�C���̍���

//�O���[�o���錾
LPDIRECT3DTEXTURE9 g_pTextureTime[2] = {};			//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime[2] = {};		//���_�o�b�t�@�ւ̃|�C���^
Time g_aTime;										//�^�C�}�[�̏��
int g_nCntLogoSet;			//���S��\������܂ł̃J�E���^�[
bool g_bFinish;				//�Q�[�����I��������ǂ���

//-------------------------------------------
//�^�C�}�[�̏���������
//-------------------------------------------
void InitTime(void)
{
	//�\���̂̏�����
	for (int nCount = 0; nCount < NUM_TIME; nCount++)
	{
		g_aTime.pos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
	}
	g_aTime.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);			//�J���[
	g_aTime.nTime = 0;			//���b�Ԃ�
	g_aTime.nFlame = 60;		//60�t���[��
	g_aTime.bUse = false;		//�g�p���Ȃ�

	//�J�E���^�[�p�ϐ������Z�b�g
	g_bFinish = false;
	g_nCntLogoSet = 0;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//--------------------------�w�i-----------------------------------
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Time_rogo.png",
		&g_pTextureTime[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime[0],
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTime[0]->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(1100 - (200.0f / 2.0f), 90.0f - (70.0f / 2.0f), 0);
	pVtx[1].pos = D3DXVECTOR3(1100 + (200.0f / 2.0f), 90.0f - (70.0f / 2.0f), 0);
	pVtx[2].pos = D3DXVECTOR3(1100 - (200.0f / 2.0f), 90.0f + (70.0f / 2.0f), 0);
	pVtx[3].pos = D3DXVECTOR3(1100 + (200.0f / 2.0f), 90.0f + (70.0f / 2.0f), 0);

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
	g_pVtxBuffTime[0]->Unlock();

	//--------------------------���l-----------------------------------
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number000.png",
		&g_pTextureTime[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_TIME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime[1],
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTime[1]->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < NUM_TIME; nCount++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aTime.pos[nCount].x - (TIME_WIDTH / 2.0f) + (nCount * 25.0f), g_aTime.pos[nCount].y - (TIME_HEIGHT / 2.0f), 0);
		pVtx[1].pos = D3DXVECTOR3(g_aTime.pos[nCount].x + (TIME_WIDTH / 2.0f) + (nCount * 25.0f), g_aTime.pos[nCount].y - (TIME_HEIGHT / 2.0f), 0);
		pVtx[2].pos = D3DXVECTOR3(g_aTime.pos[nCount].x - (TIME_WIDTH / 2.0f) + (nCount * 25.0f), g_aTime.pos[nCount].y + (TIME_HEIGHT / 2.0f), 0);
		pVtx[3].pos = D3DXVECTOR3(g_aTime.pos[nCount].x + (TIME_WIDTH / 2.0f) + (nCount * 25.0f), g_aTime.pos[nCount].y + (TIME_HEIGHT / 2.0f), 0);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(g_aTime.color.r, g_aTime.color.g, g_aTime.color.b, g_aTime.color.a);
		pVtx[1].col = D3DXCOLOR(g_aTime.color.r, g_aTime.color.g, g_aTime.color.b, g_aTime.color.a);
		pVtx[2].col = D3DXCOLOR(g_aTime.color.r, g_aTime.color.g, g_aTime.color.b, g_aTime.color.a);
		pVtx[3].col = D3DXCOLOR(g_aTime.color.r, g_aTime.color.g, g_aTime.color.b, g_aTime.color.a);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;		//���_����4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime[1]->Unlock();
}

//-------------------------------------------
//�^�C�}�[�̏I������
//-------------------------------------------
void UninitTime(void)
{
	for (int nCount = 0; nCount < 2; nCount++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureTime[nCount] != NULL)
		{
			g_pTextureTime[nCount]->Release();
			g_pTextureTime[nCount] = NULL;
		}
	}

	for (int nCount = 0; nCount < 2; nCount++)
	{
		//���_�o�b�t�@�̔j��
		if (g_pVtxBuffTime[nCount] != NULL)
		{
			g_pVtxBuffTime[nCount]->Release();
			g_pVtxBuffTime[nCount] = NULL;
		}
	}

}

//-------------------------------------------
//�^�C�}�[�̍X�V����
//-------------------------------------------
void UpdateTime(void)
{
	int nTimePos[NUM_TIME];		//�^�C���̃e�N�X�`���ʒu

	if (g_aTime.nTime != 0)
	{//�^�C�}�[��0�ł͂Ȃ�������
		g_aTime.nFlame--;		//�t���[���������炷
	}

	if (g_aTime.nFlame <= 0)
	{//�t���[������0��菬�����Ȃ�����
		g_aTime.nTime--;				//�^�C�}�[��1���炷				
		g_aTime.nFlame = 60;			//�t���[������60�ɖ߂�
	}

	if (g_aTime.nTime == 0 && !g_bFinish)
	{//�^�C�}�[��0�ɂȂ�����
		SetLogo(LOGONUM_FINISH, 90);
		SetShadow(1);
		g_bFinish = true;

		//�T�E���h�Đ�
		PlaySound(SOUND_LABEL_SE_FINISH);
	}
	else if (g_bFinish)
	{
		g_nCntLogoSet++;

		if (g_nCntLogoSet == 300)
		{
			SetFade(MODE_RESULT);
		}
	}

	//�����̃e�N�X�`�����i�[
	nTimePos[0] = g_aTime.nTime % 1000 / 100;
	nTimePos[1] = g_aTime.nTime % 100 / 10;
	nTimePos[2] = g_aTime.nTime % 10;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTime[1]->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTime = 0; nCntTime < NUM_TIME; nCntTime++)
	{//�e�N�X�`�����W�̍X�V
		pVtx[0].tex = D3DXVECTOR2(0.1f * nTimePos[nCntTime], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f * nTimePos[nCntTime] + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f * nTimePos[nCntTime], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f * nTimePos[nCntTime] + 0.1f, 1.0f);

		//���_�J���[�̍X�V
		pVtx[0].col = D3DXCOLOR(g_aTime.color.r, g_aTime.color.g, g_aTime.color.b, g_aTime.color.a);
		pVtx[1].col = D3DXCOLOR(g_aTime.color.r, g_aTime.color.g, g_aTime.color.b, g_aTime.color.a);
		pVtx[2].col = D3DXCOLOR(g_aTime.color.r, g_aTime.color.g, g_aTime.color.b, g_aTime.color.a);
		pVtx[3].col = D3DXCOLOR(g_aTime.color.r, g_aTime.color.g, g_aTime.color.b, g_aTime.color.a);

		//���_���W�̍X�V
		pVtx[0].pos = D3DXVECTOR3(g_aTime.pos[nCntTime].x - (TIME_WIDTH / 2.0f) + (nCntTime * 25.0f), g_aTime.pos[nCntTime].y - (TIME_HEIGHT / 2.0f), 0);
		pVtx[1].pos = D3DXVECTOR3(g_aTime.pos[nCntTime].x + (TIME_WIDTH / 2.0f) + (nCntTime * 25.0f), g_aTime.pos[nCntTime].y - (TIME_HEIGHT / 2.0f), 0);
		pVtx[2].pos = D3DXVECTOR3(g_aTime.pos[nCntTime].x - (TIME_WIDTH / 2.0f) + (nCntTime * 25.0f), g_aTime.pos[nCntTime].y + (TIME_HEIGHT / 2.0f), 0);
		pVtx[3].pos = D3DXVECTOR3(g_aTime.pos[nCntTime].x + (TIME_WIDTH / 2.0f) + (nCntTime * 25.0f), g_aTime.pos[nCntTime].y + (TIME_HEIGHT / 2.0f), 0);

		pVtx += 4;		//�f�[�^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime[1]->Unlock();
}

//-------------------------------------------
//�^�C�}�[�̕`�揈��
//-------------------------------------------
void DrawTime(void)
{
	for (int nCount = 0; nCount < 2; nCount++)
	{
		if (g_aTime.bUse == true)
		{//�g�p���Ă�����
			//�f�o�C�X�ւ̃|�C���^
			LPDIRECT3DDEVICE9 pDevice;

			//�f�o�C�X�̎擾
			pDevice = GetDevice();

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffTime[nCount], 0, sizeof(VERTEX_2D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			for (int nCntTime = 0; nCntTime < NUM_TIME; nCntTime++)
			{
				//�e�N�X�`���ݒ�
				pDevice->SetTexture(0, g_pTextureTime[nCount]);

				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTime * 4, 2);
			}
		}
	}
}

//-------------------------------------------
//�^�C�}�[�̐ݒ菈��
//
//D3DXVECTOR3 pos �� �^�C�}�[�̈ʒu���w��
//D3DXCOLOR color �� �^�C�}�[�̐��l�̐F���w��
//int nTime�@�� �^�C�}�[�̎��Ԃ��w��
//
//-------------------------------------------
void SetTime(D3DXVECTOR3 pos, D3DXCOLOR color,int nTime)
{
	if (g_aTime.bUse == false)
	{//�g�p���Ă��Ȃ�������
		for (int nCount = 0; nCount < NUM_TIME; nCount++)
		{
			g_aTime.pos[nCount] = pos;		//�ʒu
		}
		g_aTime.color = color;			//�J���[
		g_aTime.nTime = nTime;			//����
		g_aTime.bUse = true;			//�g�p����
	}
}

//-------------------------------------------
//�Q�[���̏I������
//-------------------------------------------
bool FinishGame(void)
{
	return g_bFinish;
}