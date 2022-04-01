//-------------------------------------------
//
//�L���L�����[twinkle.cpp]
//Author:���앑
//
//-------------------------------------------

//�C���N���[�h�t�@�C��
#include "twinkle.h"

//�O���[�o���錾
LPDIRECT3DTEXTURE9 g_pTextureTwinkle = NULL;				//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTwinkle = NULL;			//���_�o�b�t�@�ւ̃|�C���^
Twinkle g_aTwinkle[MAX_TWINKLE];							//�A�C�e���̏��

//-------------------------------------------
//�L���L���̏���������
//-------------------------------------------
void InitTwinkle(void)
{
	int nCntTwinkle;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/light000.png",
		&g_pTextureTwinkle);

	for (nCntTwinkle = 0; nCntTwinkle < MAX_TWINKLE; nCntTwinkle++)
	{
		g_aTwinkle[nCntTwinkle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
		g_aTwinkle[nCntTwinkle].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
		g_aTwinkle[nCntTwinkle].nNumber =0;									//���Ԗڂ�
		g_aTwinkle[nCntTwinkle].bUse = false;								//�g�p���邩���Ȃ���
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TWINKLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTwinkle,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTwinkle->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTwinkle = 0; nCntTwinkle < MAX_TWINKLE; nCntTwinkle++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aTwinkle[nCntTwinkle].pos.x - (TWINKLE_WIDTH / 2), g_aTwinkle[nCntTwinkle].pos.y - (TWINKLE_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aTwinkle[nCntTwinkle].pos.x + (TWINKLE_WIDTH / 2), g_aTwinkle[nCntTwinkle].pos.y - (TWINKLE_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aTwinkle[nCntTwinkle].pos.x - (TWINKLE_WIDTH / 2), g_aTwinkle[nCntTwinkle].pos.y + (TWINKLE_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aTwinkle[nCntTwinkle].pos.x + (TWINKLE_WIDTH / 2), g_aTwinkle[nCntTwinkle].pos.y + (TWINKLE_HEIGHT / 2), 0.0f);

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
	g_pVtxBuffTwinkle->Unlock();

	SetTwinkle(D3DXVECTOR3(50.0f,  0.0f, 0.0f),D3DXVECTOR3(1.2f,1.0f,0.0f),0);
	SetTwinkle(D3DXVECTOR3(200.0f, 0.0f, 0.0f),D3DXVECTOR3(0.5f,0.8f,0.0f),0);
	SetTwinkle(D3DXVECTOR3(400.0f, 0.0f, 0.0f),D3DXVECTOR3(1.5f,1.2f,0.0f), 0);
	SetTwinkle(D3DXVECTOR3(1530.0f,0.0f, 0.0f),D3DXVECTOR3(-0.4f,0.3f,0.0f),0);
	SetTwinkle(D3DXVECTOR3(1750.0f,0.0f, 0.0f),D3DXVECTOR3(-0.7f,0.5f,0.0f),0);
	SetTwinkle(D3DXVECTOR3(2030.0f,0.0f, 0.0f),D3DXVECTOR3(-0.3f,0.4f, 0.0f), 0);
	SetTwinkle(D3DXVECTOR3(3010.0f,0.0f, 0.0f),D3DXVECTOR3(-0.8f,0.8f, 0.0f), 0);
	SetTwinkle(D3DXVECTOR3(4570.0f,0.0f, 0.0f),D3DXVECTOR3(-0.4f,0.2f, 0.0f), 0);
	SetTwinkle(D3DXVECTOR3(5940.0f,0.0f, 0.0f),D3DXVECTOR3(-0.5f,0.3f, 0.0f), 0);
	SetTwinkle(D3DXVECTOR3(6340.0f,0.0f, 0.0f),D3DXVECTOR3(-0.4f,0.2f, 0.0f), 0);
	SetTwinkle(D3DXVECTOR3(7140.0f,0.0f, 0.0f),D3DXVECTOR3(-0.3f,0.2f,0.0f),0);
	SetTwinkle(D3DXVECTOR3(8480.0f,395.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),1);
}

//-------------------------------------------
//�L���L���̏I������
//-------------------------------------------
void UninitTwinkle(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureTwinkle != NULL)
	{
		g_pTextureTwinkle->Release();
		g_pTextureTwinkle = NULL;
	}


	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTwinkle != NULL)
	{
		g_pVtxBuffTwinkle->Release();
		g_pVtxBuffTwinkle = NULL;
	}
}

//-------------------------------------------
//�L���L���̍X�V����
//-------------------------------------------
void UpdateTwinkle(void)
{
	int nCntTwinkle;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTwinkle->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTwinkle = 0; nCntTwinkle < MAX_TWINKLE; nCntTwinkle++)
	{
		if (g_aTwinkle[nCntTwinkle].bUse == true)
		{
			//�ʒu���X�V
			g_aTwinkle[nCntTwinkle].pos.x += g_aTwinkle[nCntTwinkle].move.x;
			g_aTwinkle[nCntTwinkle].pos.y += g_aTwinkle[nCntTwinkle].move.y;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aTwinkle[nCntTwinkle].pos.x - (TWINKLE_WIDTH / 2), g_aTwinkle[nCntTwinkle].pos.y - (TWINKLE_HEIGHT / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aTwinkle[nCntTwinkle].pos.x + (TWINKLE_WIDTH / 2), g_aTwinkle[nCntTwinkle].pos.y - (TWINKLE_HEIGHT / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aTwinkle[nCntTwinkle].pos.x - (TWINKLE_WIDTH / 2), g_aTwinkle[nCntTwinkle].pos.y + (TWINKLE_HEIGHT / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aTwinkle[nCntTwinkle].pos.x + (TWINKLE_WIDTH / 2), g_aTwinkle[nCntTwinkle].pos.y + (TWINKLE_HEIGHT / 2), 0.0f);

		}
		pVtx += 4;		//���_�f�[�^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTwinkle->Unlock();
}

//-------------------------------------------
//�A�C�e���̕`�揈��
//-------------------------------------------
void DrawTwinkle(void)
{
	int nCntTwinkle;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTwinkle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureTwinkle);

	for (nCntTwinkle = 0; nCntTwinkle < MAX_TWINKLE; nCntTwinkle++)
	{
		if (g_aTwinkle[nCntTwinkle].bUse == true)
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTwinkle * 4, 2);
		}
	}
}

//-------------------------------------------
//�L���L���̐ݒ菈��
//-------------------------------------------
void SetTwinkle(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nNumber)
{
	int nCntTwinkle;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTwinkle->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTwinkle = 0; nCntTwinkle < MAX_TWINKLE; nCntTwinkle++)
	{
		if (g_aTwinkle[nCntTwinkle].bUse == false)
		{//�u���b�N���g�p����Ă��Ȃ��ꍇ
			g_aTwinkle[nCntTwinkle].pos = pos;
			g_aTwinkle[nCntTwinkle].move = move;
			g_aTwinkle[nCntTwinkle].nNumber = nNumber;
			g_aTwinkle[nCntTwinkle].bUse = true;
			break;
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTwinkle->Unlock();
}

//-------------------------------------------
//�L���L���̓����蔻�菈��
//-------------------------------------------
void CollisionTwinkle(D3DXVECTOR3 * pPos, float fWidth, float fHeigtht)
{
	int nCntTwinkle;

	for (nCntTwinkle = 0; nCntTwinkle < MAX_TWINKLE; nCntTwinkle++)
	{
		if (g_aTwinkle[nCntTwinkle].bUse == true)
		{//�L���L�����g���Ă���Ƃ�
			if (pPos->x + (fWidth / 2) >= g_aTwinkle[nCntTwinkle].pos.x - (TWINKLE_WIDTH / 2)
				&& pPos->x - (fWidth / 2) <= g_aTwinkle[nCntTwinkle].pos.x + (TWINKLE_WIDTH / 2)
				&& pPos->y >= g_aTwinkle[nCntTwinkle].pos.y - (TWINKLE_HEIGHT / 2)
				&& pPos->y - fHeigtht <= g_aTwinkle[nCntTwinkle].pos.y + (TWINKLE_HEIGHT / 2))
			{
				if (g_aTwinkle[nCntTwinkle].nNumber == 1)
				{
					SetItem(D3DXVECTOR3(g_aTwinkle[nCntTwinkle].pos.x, g_aTwinkle[nCntTwinkle].pos.y, 0.0f), ITEM_CAKE);
				}
				else
				{
					SetItem(D3DXVECTOR3(g_aTwinkle[nCntTwinkle].pos.x, g_aTwinkle[nCntTwinkle].pos.y, 0.0f), ITEM_CANDY);
				}
				g_aTwinkle[nCntTwinkle].bUse = false;
			}
		}
	}
}

//-------------------------------------------
//�L���L���̎擾
//-------------------------------------------
Twinkle *GetTwinkle(void)
{
	return &g_aTwinkle[0];
}