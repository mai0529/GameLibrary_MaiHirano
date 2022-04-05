//-------------------------------------------
//
//�A�C�e������[item.cpp]
//Author:���앑
//
//-------------------------------------------

//�C���N���[�h�t�@�C��
#include "item.h"
#include "score.h"
#include "time.h"

//�}�N����`
#define MAX_ITEM		(8)			//�A�C�e���̍ő吔
#define ITEM_WIDTH		(80.0f)		//�A�C�e���̕�
#define ITEM_HEIGHT		(60.0f)		//�A�C�e���̍���

//�O���[�o���錾
LPDIRECT3DTEXTURE9 g_pTextureItem = NULL;			//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Item g_item[MAX_ITEM];								//�A�C�e���̏��
int g_nItemScore;									//�X�R�AUP
bool g_bCollisionItem;								//�����������ǂ���
int g_nTimeItem;

//-------------------------------------------
//����������
//-------------------------------------------
void InitItem(void)
{
	//���ݎ������V�[�h(��)�ɂ���
	srand((unsigned int)time(NULL));

	//����������
		for (int nCount = 0; nCount < MAX_ITEM; nCount++)
		{
			g_item[nCount].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
			g_item[nCount].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ���
			g_item[nCount].bUse = false;							//�g�p���Ȃ�
		}
		g_nItemScore = 0;											//�X�R�AUP
		g_bCollisionItem = false;									//�������Ă��Ȃ�
		g_nTimeItem = rand() % 30 + 30;

		//�f�o�C�X�ւ̃|�C���^
		LPDIRECT3DDEVICE9 pDevice;

		//�f�o�C�X�̎擾
		pDevice = GetDevice();

		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data/TEXTURE/item000.png",
			&g_pTextureItem);

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

		for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
		{
			//���_���W�̐ݒ�
			pVtx[2].pos = D3DXVECTOR3(g_item[nCntItem].pos.x - (ITEM_WIDTH / 2.0f), g_item[nCntItem].pos.y + (ITEM_HEIGHT / 2.0f), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_item[nCntItem].pos.x + (ITEM_WIDTH / 2.0f), g_item[nCntItem].pos.y + (ITEM_HEIGHT / 2.0f), 0.0f);
			pVtx[0].pos = D3DXVECTOR3(g_item[nCntItem].pos.x - (ITEM_WIDTH / 2.0f), g_item[nCntItem].pos.y - (ITEM_HEIGHT / 2.0f), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_item[nCntItem].pos.x + (ITEM_WIDTH / 2.0f), g_item[nCntItem].pos.y - (ITEM_HEIGHT / 2.0f), 0.0f);

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
		}

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffItem->Unlock();		
}

//-------------------------------------------
//�I������
//-------------------------------------------
void UninitItem(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureItem != NULL)
	{
		g_pTextureItem->Release();
		g_pTextureItem = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//-------------------------------------------
//�X�V����
//-------------------------------------------
void UpdateItem(void)
{
	//�^�C�����l��
	int nGetTime = GetTime();

	//���ݎ������V�[�h(��)�ɂ���
	srand((unsigned int)time(NULL));

	int nPosY = rand() % 600 + 50;

	if (nGetTime == g_nTimeItem)
	{
		//�A�C�e���̐ݒ�
		SetItem(D3DXVECTOR3(1300.0f, nPosY, 0.0f));
	}

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntObs = 0; nCntObs < MAX_ITEM; nCntObs++)
	{
		if (g_item[nCntObs].bUse == true)
		{
			//�ʒu���̍X�V
			g_item[nCntObs].move.x = 3.0f;
			g_item[nCntObs].pos.x -= g_item[nCntObs].move.x;

			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_item[nCntObs].pos.x - (ITEM_WIDTH / 2.0f), g_item[nCntObs].pos.y - (ITEM_HEIGHT / 2.0f), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_item[nCntObs].pos.x + (ITEM_WIDTH / 2.0f), g_item[nCntObs].pos.y - (ITEM_HEIGHT / 2.0f), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_item[nCntObs].pos.x - (ITEM_WIDTH / 2.0f), g_item[nCntObs].pos.y + (ITEM_HEIGHT / 2.0f), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_item[nCntObs].pos.x + (ITEM_WIDTH / 2.0f), g_item[nCntObs].pos.y + (ITEM_HEIGHT / 2.0f), 0.0f);

			if (g_item[nCntObs].pos.x < 0)
			{//��ʊO�ɏo����
				g_item[nCntObs].bUse = false;
			}
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//-------------------------------------------
//�`�揈��
//-------------------------------------------
void DrawItem(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_item[nCntItem].bUse == true)
		{//�G���g�p����Ă���ꍇ
		 //�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_pTextureItem);
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, 2);
		}
	}
}

//-------------------------------------------
//�ݒ菈��
//-------------------------------------------
void SetItem(D3DXVECTOR3 pos)
{
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_item[nCntItem].bUse == false)
		{//��Q�����g�p����Ă��Ȃ��ꍇ
			g_item[nCntItem].pos = pos;		//�ʒu
			g_item[nCntItem].bUse = true;	//�g�p����

			break;
		}
	}
}

//-------------------------------------------
//�����蔻�菈��
//-------------------------------------------
void CollisionItem(D3DXVECTOR3 * pPos, float fWidth, float fHeigtht)
{
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_item[nCntItem].bUse == true)
		{//��Q�����g���Ă���Ƃ�
			if (pPos->x + (fWidth / 2.0f) >= g_item[nCntItem].pos.x - (ITEM_WIDTH / 2.0f)
				&& pPos->x - (fWidth / 2.0f) <= g_item[nCntItem].pos.x + (ITEM_WIDTH / 2.0f)
				&& pPos->y + (fHeigtht / 2.0f) >= g_item[nCntItem].pos.y - (ITEM_HEIGHT / 2.0f)
				&& pPos->y - (fHeigtht / 2.0f) <= g_item[nCntItem].pos.y + (ITEM_HEIGHT / 2.0f))
			{
				if (g_bCollisionItem == false)
				{
					g_item[nCntItem].bUse = false;		//�g�p���Ȃ�
					g_nItemScore += 100;				//�X�R�A100UP
					g_bCollisionItem = true;			//��������
				}
			}
		}
	}

	//g_bCollisionItem = false;		//�ۗ�
}

//-------------------------------------------
//�X�R�A�A�b�v�A�C�e���̎擾����
//-------------------------------------------
int GetScoreUpItem(void)
{
	return g_nItemScore;
}