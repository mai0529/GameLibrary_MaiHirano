//-------------------------------------------
//
//�A�C�e�����[item.cpp]
//Author:���앑
//
//-------------------------------------------

//�C���N���[�h�t�@�C��
#include "item.h"

//�O���[�o���錾
LPDIRECT3DTEXTURE9 g_pTextureItem[NUM_ITEM] = {};			//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;				//���_�o�b�t�@�ւ̃|�C���^
Item g_Item[MAX_ITEM];										//�A�C�e���̏��
int g_nItemNumber;

//-------------------------------------------
//�A�C�e���̏���������
//-------------------------------------------
void InitItem(void) 
{
	int nCntItem;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/item003.png",
		&g_pTextureItem[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/item001.png",
		&g_pTextureItem[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/item002.png",
		&g_pTextureItem[2]);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_Item[nCntItem].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);			//�ʒu
		g_Item[nCntItem].PosOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�O��̈ʒu
		g_Item[nCntItem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
		g_Item[nCntItem].fWidth = 0.0f;								//��
		g_Item[nCntItem].fHeigth = 0.0f;							//����
		g_Item[nCntItem].nType = ITEM_CANDY;						//���
		g_Item[nCntItem].bUse = false;								//�g�p���邩���Ȃ���
	}
	g_nItemNumber = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x - (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y - ITEM_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x + (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y - ITEM_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x - (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x + (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y, 0.0f);

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
	g_pVtxBuffItem->Unlock();

	SetItem(D3DXVECTOR3(1740.0f, 200.0f, 0.0f), ITEM_CAKE);
	SetItem(D3DXVECTOR3(2665.0f, 150.0f, 0.0f), ITEM_CAKE);
}

//-------------------------------------------
//�A�C�e���̏I������
//-------------------------------------------
void UninitItem(void)
{
	int nCntItem;

	for (nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureItem[nCntItem] != NULL)
		{
			g_pTextureItem[nCntItem]->Release();
			g_pTextureItem[nCntItem] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//-------------------------------------------
//�A�C�e���̍X�V����
//-------------------------------------------
void UpdateItem(void)
{
	int nCntItem;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_Item[nCntItem].bUse == true)
		{
			//�O��̈ʒu���X�V
			g_Item[nCntItem].PosOld = g_Item[nCntItem].pos;

			//�d��
			g_Item[nCntItem].move.y += ITEM_G;

			//�ʒu���X�V
			g_Item[nCntItem].pos.x += g_Item[nCntItem].move.x;
			g_Item[nCntItem].pos.y += g_Item[nCntItem].move.y;

			//�u���b�N�Ƃ̓����蔻��
			CollisionBlock(&g_Item[nCntItem].pos, &g_Item[nCntItem].PosOld, &g_Item[nCntItem].move, (ITEM_WIDTH / 2),ITEM_HEIGHT);

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x - (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y - ITEM_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x + (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y - ITEM_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x - (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Item[nCntItem].pos.x + (ITEM_WIDTH / 2), g_Item[nCntItem].pos.y, 0.0f);
		}
		pVtx += 4;		//���_�f�[�^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//-------------------------------------------
//�A�C�e���̕`�揈��
//-------------------------------------------
void DrawItem(void)
{
	int nCntItem;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_Item[nCntItem].bUse == true)
		{//�u���b�N���g�p����Ă���ꍇ
		 //�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_pTextureItem[g_Item[nCntItem].nType]);
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, 2);
		}
	}
}

//-------------------------------------------
//�A�C�e���̐ݒ菈��
//-------------------------------------------
void SetItem(D3DXVECTOR3 pos, ITEM nType)
{
	int nCntItem;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_Item[nCntItem].bUse == false)
		{//�u���b�N���g�p����Ă��Ȃ��ꍇ
			g_Item[nCntItem].pos = pos;
			g_Item[nCntItem].nType = nType;
			g_Item[nCntItem].bUse = true;
			break;
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//-------------------------------------------
//�A�C�e���̎擾
//-------------------------------------------
Item * GetItem(void)
{
	return g_Item;
}

//-------------------------------------------
//�A�C�e���̓����蔻�菈��
//-------------------------------------------
void CollisionItem(D3DXVECTOR3 * pPos, float fWidth, float fHeigtht)
{
	int nCntItem;

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_Item[nCntItem].bUse == true)
		{//�A�C�e�����g���Ă���Ƃ�
			if (pPos->x + (fWidth / 2) >= g_Item[nCntItem].pos.x - (ITEM_WIDTH / 2)
				&& pPos->x - (fWidth / 2) <= g_Item[nCntItem].pos.x + (ITEM_WIDTH / 2)
				&& pPos->y >= g_Item[nCntItem].pos.y - ITEM_HEIGHT
				&& pPos->y - fHeigtht <= g_Item[nCntItem].pos.y)
			{
				//�T�E���h�̍Đ�
				PlaySound(SOUND_LABEL_SE_ITEM);
				DeleteItem(nCntItem);
			}
		}
	}
}

//-------------------------------------------
//�A�C�e����ޕʏ���
//-------------------------------------------
void DeleteItem(int nCntItem)
{
	Player *pPlayer = GetPlayer();
	Life *pLife = GetLife();

	if (g_Item[nCntItem].nType == ITEM_CANDY)
	{//��
		AddScore(350);
	}
	else if (g_Item[nCntItem].nType == ITEM_POTION )
	{//�񕜖�
		pPlayer->nLife += 1;
		for (int nCount = 0; nCount < MAX_LIFE; nCount++, pLife++)
		{
			if (pLife->bUse == false)
			{
				pLife->bUse = true;
				break;
			}
		}
	}
	else if (g_Item[nCntItem].nType == ITEM_CAKE)
	{//�P�[�L
		AddScore(777);
		g_nItemNumber++;
	}

	if (g_nItemNumber == 5)
	{//�P�[�L��S���������
		AddScore(2000);
	}

	//���o
	SetExplosion(D3DXVECTOR3(g_Item[nCntItem].pos.x, g_Item[nCntItem].pos.y - (ITEM_HEIGHT / 2), 0.0f), D3DXCOLOR(0.7f, 0.4f, 0.4f, 0.7f));

	//�A�C�e�����\���ɂ���
	g_Item[nCntItem].bUse = false;
}

//-------------------------------------------
//�P�[�L�̐����擾
//-------------------------------------------
int GetnCount(void)
{
	return g_nItemNumber;
}