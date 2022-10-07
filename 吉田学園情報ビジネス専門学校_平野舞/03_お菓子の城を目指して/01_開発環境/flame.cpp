//-------------------------------------------
//
//�����[flame.cpp]
//Author:���앑
//
//-------------------------------------------

//�C���N���[�h�t�@�C��
#include "flame.h"

//�O���[�o���錾
LPDIRECT3DTEXTURE9 g_pTextureFlame = NULL;				//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFlame = NULL;			//���_�o�b�t�@�ւ̃|�C���^
Flame g_aFlame[MAX_FLAME];								//�A�C�e���̏��

//-------------------------------------------
//���̏���������
//-------------------------------------------
void InitFlame(void)
{
	int nCntFlame;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/light000.png",
		&g_pTextureFlame);

	for (nCntFlame = 0; nCntFlame < MAX_FLAME; nCntFlame++)
	{
		g_aFlame[nCntFlame].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
		g_aFlame[nCntFlame].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
		g_aFlame[nCntFlame].nNumber =0;									//���Ԗڂ�
		g_aFlame[nCntFlame].bUse = false;								//�g�p���邩���Ȃ���
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_FLAME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFlame,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffFlame->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntFlame = 0; nCntFlame < MAX_FLAME; nCntFlame++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aFlame[nCntFlame].pos.x - (FLAME_WIDTH / 2), g_aFlame[nCntFlame].pos.y - (FLAME_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aFlame[nCntFlame].pos.x + (FLAME_WIDTH / 2), g_aFlame[nCntFlame].pos.y - (FLAME_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aFlame[nCntFlame].pos.x - (FLAME_WIDTH / 2), g_aFlame[nCntFlame].pos.y + (FLAME_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aFlame[nCntFlame].pos.x + (FLAME_WIDTH / 2), g_aFlame[nCntFlame].pos.y + (FLAME_HEIGHT / 2), 0.0f);

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
	g_pVtxBuffFlame->Unlock();

	SetFlame(D3DXVECTOR3(50.0f,  0.0f, 0.0f),D3DXVECTOR3(1.2f,1.0f,0.0f),0);
	SetFlame(D3DXVECTOR3(200.0f, 0.0f, 0.0f),D3DXVECTOR3(0.5f,0.8f,0.0f),0);
	SetFlame(D3DXVECTOR3(400.0f, 0.0f, 0.0f),D3DXVECTOR3(1.5f,1.2f,0.0f), 0);
	SetFlame(D3DXVECTOR3(1530.0f,0.0f, 0.0f),D3DXVECTOR3(-0.4f,0.3f,0.0f),0);
	SetFlame(D3DXVECTOR3(1750.0f,0.0f, 0.0f),D3DXVECTOR3(-0.7f,0.5f,0.0f),0);
	SetFlame(D3DXVECTOR3(2030.0f,0.0f, 0.0f),D3DXVECTOR3(-0.3f,0.4f, 0.0f), 0);
	SetFlame(D3DXVECTOR3(3010.0f,0.0f, 0.0f),D3DXVECTOR3(-0.8f,0.8f, 0.0f), 0);
	SetFlame(D3DXVECTOR3(4570.0f,0.0f, 0.0f),D3DXVECTOR3(-0.4f,0.2f, 0.0f), 0);
	SetFlame(D3DXVECTOR3(5940.0f,0.0f, 0.0f),D3DXVECTOR3(-0.5f,0.3f, 0.0f), 0);
	SetFlame(D3DXVECTOR3(6340.0f,0.0f, 0.0f),D3DXVECTOR3(-0.4f,0.2f, 0.0f), 0);
	SetFlame(D3DXVECTOR3(7140.0f,0.0f, 0.0f),D3DXVECTOR3(-0.3f,0.2f,0.0f),0);
	SetFlame(D3DXVECTOR3(8480.0f,395.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),1);
}

//-------------------------------------------
//���̏I������
//-------------------------------------------
void UninitFlame(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureFlame != NULL)
	{
		g_pTextureFlame->Release();
		g_pTextureFlame = NULL;
	}


	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffFlame != NULL)
	{
		g_pVtxBuffFlame->Release();
		g_pVtxBuffFlame = NULL;
	}
}

//-------------------------------------------
//���̍X�V����
//-------------------------------------------
void UpdateFlame(void)
{
	int nCntFlame;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffFlame->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntFlame = 0; nCntFlame < MAX_FLAME; nCntFlame++)
	{
		if (g_aFlame[nCntFlame].bUse == true)
		{
			//�ʒu���X�V
			g_aFlame[nCntFlame].pos.x += g_aFlame[nCntFlame].move.x;
			g_aFlame[nCntFlame].pos.y += g_aFlame[nCntFlame].move.y;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aFlame[nCntFlame].pos.x - (FLAME_WIDTH / 2), g_aFlame[nCntFlame].pos.y - (FLAME_HEIGHT / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aFlame[nCntFlame].pos.x + (FLAME_WIDTH / 2), g_aFlame[nCntFlame].pos.y - (FLAME_HEIGHT / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aFlame[nCntFlame].pos.x - (FLAME_WIDTH / 2), g_aFlame[nCntFlame].pos.y + (FLAME_HEIGHT / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aFlame[nCntFlame].pos.x + (FLAME_WIDTH / 2), g_aFlame[nCntFlame].pos.y + (FLAME_HEIGHT / 2), 0.0f);

		}
		pVtx += 4;		//���_�f�[�^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFlame->Unlock();
}

//-------------------------------------------
//�A�C�e���̕`�揈��
//-------------------------------------------
void DrawFlame(void)
{
	int nCntFlame;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffFlame, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureFlame);

	for (nCntFlame = 0; nCntFlame < MAX_FLAME; nCntFlame++)
	{
		if (g_aFlame[nCntFlame].bUse == true)
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntFlame * 4, 2);
		}
	}
}

//-------------------------------------------
//���̐ݒ菈��
//-------------------------------------------
void SetFlame(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nNumber)
{
	int nCntFlame;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffFlame->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntFlame = 0; nCntFlame < MAX_FLAME; nCntFlame++)
	{
		if (g_aFlame[nCntFlame].bUse == false)
		{//�u���b�N���g�p����Ă��Ȃ��ꍇ
			g_aFlame[nCntFlame].pos = pos;
			g_aFlame[nCntFlame].move = move;
			g_aFlame[nCntFlame].nNumber = nNumber;
			g_aFlame[nCntFlame].bUse = true;
			break;
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFlame->Unlock();
}

//-------------------------------------------
//���̓����蔻�菈��
//-------------------------------------------
void CollisionFlame(D3DXVECTOR3 * pPos, float fWidth, float fHeigtht)
{
	int nCntFlame;

	for (nCntFlame = 0; nCntFlame < MAX_FLAME; nCntFlame++)
	{
		if (g_aFlame[nCntFlame].bUse == true)
		{//�����g���Ă���Ƃ�
			if (pPos->x + (fWidth / 2) >= g_aFlame[nCntFlame].pos.x - (FLAME_WIDTH / 2)
				&& pPos->x - (fWidth / 2) <= g_aFlame[nCntFlame].pos.x + (FLAME_WIDTH / 2)
				&& pPos->y >= g_aFlame[nCntFlame].pos.y - (FLAME_HEIGHT / 2)
				&& pPos->y - fHeigtht <= g_aFlame[nCntFlame].pos.y + (FLAME_HEIGHT / 2))
			{
				if (g_aFlame[nCntFlame].nNumber == 1)
				{
					SetItem(D3DXVECTOR3(g_aFlame[nCntFlame].pos.x, g_aFlame[nCntFlame].pos.y, 0.0f), ITEM_CAKE);
				}
				else
				{
					SetItem(D3DXVECTOR3(g_aFlame[nCntFlame].pos.x, g_aFlame[nCntFlame].pos.y, 0.0f), ITEM_CANDY);
				}
				g_aFlame[nCntFlame].bUse = false;
			}
		}
	}
}

//-------------------------------------------
//���̎擾
//-------------------------------------------
Flame *GetFlame(void)
{
	return &g_aFlame[0];
}