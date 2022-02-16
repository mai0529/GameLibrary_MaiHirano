//-------------------------------------------
//
//�e�̔��ˏ���[Bullet.cpp]
//Author:���앑
//
//-------------------------------------------

//�C���N���[�h�t�@�C��
#include "Bullet.h"
#include "enemy.h"
#include "input.h"
#include "sound.h"
#include "score.h"
#include "player.h"
#include "flame.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBullet[NUM_BULLET] = {};		//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;			//���_�o�b�t�@�ւ̃|�C���^
Bullet g_aBullet[MAX_BULLET];								//�e�̏��

//-------------------------------------------
//�e�̏���������
//-------------------------------------------
void InitBullet(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	int nCntBullet;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bullet001.png",
		&g_pTextureBullet[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bullet002.png",
		&g_pTextureBullet[1]);

	//�e�̏��̏�����
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife =0;
		g_aBullet[nCntBullet].type = BULLETTYPE_PLAYER;
		g_aBullet[nCntBullet].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - (BULLET_WIDTH / 2), g_aBullet[nCntBullet].pos.y - (BULLET_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (BULLET_WIDTH / 2), g_aBullet[nCntBullet].pos.y - (BULLET_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - (BULLET_WIDTH / 2), g_aBullet[nCntBullet].pos.y + (BULLET_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (BULLET_WIDTH / 2), g_aBullet[nCntBullet].pos.y + (BULLET_HEIGHT / 2), 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
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
	g_pVtxBuffBullet->Unlock();
}

//-------------------------------------------
//�e�̏I������
//-------------------------------------------
void UninitBullet(void)
{
	int nCntBullet;

	for (nCntBullet = 0; nCntBullet < NUM_BULLET; nCntBullet++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureBullet[nCntBullet] != NULL)
		{
			g_pTextureBullet[nCntBullet]->Release();
			g_pTextureBullet[nCntBullet] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//-------------------------------------------
//�e�̍X�V����
//-------------------------------------------
void UpdateBullet(void)
{
	int nCntBullet;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//�e���g�p����Ă���
		 //�e�̈ʒu���̍X�V
			g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;

			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - (BULLET_WIDTH / 2), g_aBullet[nCntBullet].pos.y - (BULLET_HEIGHT / 2), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (BULLET_WIDTH / 2), g_aBullet[nCntBullet].pos.y - (BULLET_HEIGHT / 2), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - (BULLET_WIDTH / 2), g_aBullet[nCntBullet].pos.y + (BULLET_HEIGHT / 2), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (BULLET_WIDTH / 2), g_aBullet[nCntBullet].pos.y + (BULLET_HEIGHT / 2), 0.0f);

			Enemy *pEnemy = GetEnemy();
			int nCntEnemy;

			for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
			{
				if (pEnemy->bUse == true)
				{//�G���g�p����Ă���
					if (g_aBullet[nCntBullet].pos.x >= pEnemy->pos.x - (ENEMY_WIDTH / 2)
						&& g_aBullet[nCntBullet].pos.x <= pEnemy->pos.x + (ENEMY_WIDTH / 2)
						&& g_aBullet[nCntBullet].pos.y >= pEnemy->pos.y - ENEMY_HEIGHT
						&& g_aBullet[nCntBullet].pos.y <= pEnemy->pos.y)
					{ //�G�̓����蔻��
						if (pEnemy->nType == ENEMY_WOLF)
						{//�T
							HitEnemy(nCntEnemy, 1);
							AddScore(200);
						}
						else if (pEnemy->nType == ENEMY_BONE)
						{//�[��
							if (pEnemy->nLife != 1)
							{//10��܂ł̓X�R�A���炦��
								HitEnemy(nCntEnemy, 1);
								AddScore(10);
							}
						}
						else if (pEnemy->nNumber == 1)
						{
							HitEnemy(nCntEnemy, 1);
							SetItem(pEnemy->pos, ITEM_CAKE);
						}
						g_aBullet[nCntBullet].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
					}
				}
			}

			//���̓����蔻��
			CollisionFlame(&g_aBullet[nCntBullet].pos, BULLET_WIDTH, BULLET_HEIGHT);

			if (g_aBullet[nCntBullet].pos.x > SCREEN_WIDTH)
			{
				g_aBullet[nCntBullet].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
			}

			//�����̃J�E���g�_�E��
			g_aBullet[nCntBullet].nLife -= 1;
			if (g_aBullet[nCntBullet].nLife == 0)
			{
				g_aBullet[nCntBullet].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
			}
		}

		pVtx += 4;		//���_�f�[�^���S���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//-------------------------------------------
//�e�̕`�揈��
//-------------------------------------------
void DrawBullet(void)
{
	int nCntBullet;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//�e���g�p����Ă���ꍇ
				//�e�N�X�`���ݒ�
				pDevice->SetTexture(0, g_pTextureBullet[g_aBullet[nCntBullet].type]);
				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}
}

//-------------------------------------------
//�e�̐ݒ菈��
//-------------------------------------------
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTYPE type)
{	
	int nCntBullet;

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{//�e���g�p����Ă��Ȃ��ꍇ
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].nLife = 100;
			g_aBullet[nCntBullet].type = type;
			g_aBullet[nCntBullet].bUse = true;		//�e���g�p���Ă����Ԃɂ���
			PlaySound(SOUND_LABEL_SE_SHOT);
			break;
		}
	}
}