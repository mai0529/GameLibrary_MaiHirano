//-------------------------------------------
//
//���َq���[sweet.cpp]
//Author:���앑
//
//-------------------------------------------

//�C���N���[�h�t�@�C��
#include "sweet.h"
#include "fade.h"

//�O���[�o���錾
LPDIRECT3DTEXTURE9 g_pTextureSweet = NULL;			//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSweet = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Sweet g_Sweet[MAX_SWEET];							//�A�C�e���̏��
int g_nSweetNumber;									//�J�E���^�[
int g_nSweetFade;									//��ʑJ�ڗp�J�E���^�[

//-------------------------------------------
//���َq�̏���������
//-------------------------------------------
void InitSweet(void)
{
	int nCntSweet;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Sweet000.png",
		&g_pTextureSweet);

	for (nCntSweet = 0; nCntSweet < MAX_SWEET; nCntSweet++)
	{
		g_Sweet[nCntSweet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ʒu
		g_Sweet[nCntSweet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
		g_Sweet[nCntSweet].bUse = false;								//�g�p���邩���Ȃ���
	}
	g_nSweetNumber = 0;
	g_nSweetFade = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SWEET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSweet,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSweet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntSweet = 0; nCntSweet < MAX_SWEET; nCntSweet++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_Sweet[nCntSweet].pos.x - (SWEET_WIDTH / 2), g_Sweet[nCntSweet].pos.y - SWEET_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Sweet[nCntSweet].pos.x + (SWEET_WIDTH / 2), g_Sweet[nCntSweet].pos.y - SWEET_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Sweet[nCntSweet].pos.x - (SWEET_WIDTH / 2), g_Sweet[nCntSweet].pos.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Sweet[nCntSweet].pos.x + (SWEET_WIDTH / 2), g_Sweet[nCntSweet].pos.y, 0.0f);

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

		pVtx += 4;		//���_�f�[�^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSweet->Unlock();

	//���َq��z�u
	for (int nCount = 0; nCount < MAX_SWEET; nCount++)
	{
		SetSweet(D3DXVECTOR3(70.0f, 120.0f + (150.0f * nCount), 0.0f));
	}
}

//-------------------------------------------
//���َq�̏I������
//-------------------------------------------
void UninitSweet(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureSweet != NULL)
	{
		g_pTextureSweet->Release();
		g_pTextureSweet = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSweet != NULL)
	{
		g_pVtxBuffSweet->Release();
		g_pVtxBuffSweet = NULL;
	}
}

//-------------------------------------------
//���َq�̍X�V����
//-------------------------------------------
void UpdateSweet(void)
{
	if (g_nSweetNumber == MAX_SWEET)
	{
		if (g_nSweetFade == 0)
		{
			g_nSweetFade = 1;
			SetFade(MODE_GAMEOVER);
		}
	}
}

//-------------------------------------------
//���َq�̕`�揈��
//-------------------------------------------
void DrawSweet(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSweet, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntSweet = 0; nCntSweet < MAX_SWEET; nCntSweet++)
	{
		if (g_Sweet[nCntSweet].bUse == true)
		{//���َq���g�p����Ă���ꍇ
		 //�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_pTextureSweet);
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntSweet * 4, 2);
		}
	}
}

//-------------------------------------------
//���َq�̐ݒ菈��
//-------------------------------------------
void SetSweet(D3DXVECTOR3 pos)
{
	int nCntSweet;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSweet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntSweet = 0; nCntSweet < MAX_SWEET; nCntSweet++)
	{
		if (g_Sweet[nCntSweet].bUse == false)
		{//���َq���g�p����Ă��Ȃ��ꍇ
			g_Sweet[nCntSweet].pos = pos;		//�ʒu

												//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_Sweet[nCntSweet].pos.x - (SWEET_WIDTH / 2), g_Sweet[nCntSweet].pos.y - SWEET_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Sweet[nCntSweet].pos.x + (SWEET_WIDTH / 2), g_Sweet[nCntSweet].pos.y - SWEET_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Sweet[nCntSweet].pos.x - (SWEET_WIDTH / 2), g_Sweet[nCntSweet].pos.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Sweet[nCntSweet].pos.x + (SWEET_WIDTH / 2), g_Sweet[nCntSweet].pos.y, 0.0f);

			g_Sweet[nCntSweet].bUse = true;		//�g�p����
			break;
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSweet->Unlock();
}

//-------------------------------------------
//���َq�̏��̎擾
//-------------------------------------------
Sweet * GetSweet(void)
{
	return &g_Sweet[0];
}

//-------------------------------------------
//���َq�̓����蔻�菈��
//-------------------------------------------
void CollisionSweet(D3DXVECTOR3 * pPos, float fWidth, float fHeigtht)
{
	int nCntSweet;

	for (nCntSweet = 0; nCntSweet < MAX_SWEET; nCntSweet++)
	{
		if (g_Sweet[nCntSweet].bUse == true)
		{//�A�C�e�����g���Ă���Ƃ�
			if (pPos->x + (fWidth / 2.0f) >= g_Sweet[nCntSweet].pos.x - (SWEET_WIDTH / 2)
				&& pPos->x - (fWidth / 2.0f) <= g_Sweet[nCntSweet].pos.x + (SWEET_WIDTH / 2)
				&& pPos->y + (fHeigtht / 2.0f) >= g_Sweet[nCntSweet].pos.y - SWEET_HEIGHT
				&& pPos->y - (fHeigtht / 2.0f) <= g_Sweet[nCntSweet].pos.y)
			{
				g_Sweet[nCntSweet].bUse = false;		//�g�p���Ȃ�
				g_nSweetNumber++;						//�J�E���^�[�𑝂₷
			}
		}
	}
}