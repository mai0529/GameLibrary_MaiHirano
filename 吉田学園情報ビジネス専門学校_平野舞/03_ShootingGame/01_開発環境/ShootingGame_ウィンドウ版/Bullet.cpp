//-------------------------------------------
//
//�e�̏���[Bullet.cpp]
//Author:���앑
//
//-------------------------------------------

//�C���N���[�h�t�@�C��
#include "Bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "input.h"
#include "sound.h"
#include "effect.h"
#include "score.h"
#include "player.h"
#include "item.h"

//�}�N����`
#define MAX_BULLET			(128)		//�e�̍ő吔
#define BULLET_WIDTH		(20.0f)		//�e�̕�
#define BULLET_HEIGHT		(20.0f)		//�e�̍���
#define BULLET_ENEMY		(45.0f)		//�G�̓����蔻��
#define NUM_BULLET			(2)			//�e�̎��

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBullet[NUM_BULLET] = {};		//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;			//���_�o�b�t�@�ւ̃|�C���^
Bullet g_aBullet[MAX_BULLET];								//�e�̏��

//-------------------------------------------
//�e�̏���������
//-------------------------------------------
void InitBullet(void)
{
	//�e�̏��̏�����
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 0;
		g_aBullet[nCntBullet].type = BULLETTYPE_PLAYER;
		g_aBullet[nCntBullet].bUse = false;
	}

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bullet000.png",
		&g_pTextureBullet[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bullet001.png",
		&g_pTextureBullet[1]);
	
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

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_WIDTH, g_aBullet[nCntBullet].pos.y - BULLET_HEIGHT, g_aBullet[nCntBullet].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_WIDTH, g_aBullet[nCntBullet].pos.y - BULLET_HEIGHT, g_aBullet[nCntBullet].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_WIDTH, g_aBullet[nCntBullet].pos.y + BULLET_HEIGHT, g_aBullet[nCntBullet].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_WIDTH, g_aBullet[nCntBullet].pos.y + BULLET_HEIGHT, g_aBullet[nCntBullet].pos.z);

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
	//�e�N�X�`���̔j��
	for (int nCntBullet = 0; nCntBullet < NUM_BULLET; nCntBullet++)
	{
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
	//�G�̏����擾
	Enemy *pEnemy = GetEnemy();

	//�X�R�A�A�b�v�A�C�e���̏����擾
	int nScoreUp = GetScoreUpItem();

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//�e���g�p����Ă���
		 //�e�̈ʒu���̍X�V
			g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;

			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_WIDTH, g_aBullet[nCntBullet].pos.y - BULLET_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_WIDTH, g_aBullet[nCntBullet].pos.y - BULLET_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_WIDTH, g_aBullet[nCntBullet].pos.y + BULLET_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_WIDTH, g_aBullet[nCntBullet].pos.y + BULLET_HEIGHT, 0.0f);

			//�G�t�F�N�g�ݒu
			SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 5.0f, 15);

			for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
			{
				if (pEnemy->bUse == true)
				{//�G���g�p����Ă���
					if (g_aBullet[nCntBullet].pos.x + BULLET_WIDTH >= (pEnemy->pos.x - ENEMY_WIDTH) + 30.0f
						&& g_aBullet[nCntBullet].pos.x - BULLET_WIDTH <= (pEnemy->pos.x + ENEMY_WIDTH) + 30.0f
						&& g_aBullet[nCntBullet].pos.y + BULLET_HEIGHT >= (pEnemy->pos.y - ENEMY_HEIGHT) + 20.0f
						&& g_aBullet[nCntBullet].pos.y - BULLET_HEIGHT <= (pEnemy->pos.y + ENEMY_HEIGHT) + 20.0f)
					{ //�G�̓����蔻��
						HitEnemy(nCntEnemy, 1);		//�G�̃q�b�g����
						AddScore(200, nScoreUp);	//�X�R�A�̒ǉ�
						g_aBullet[nCntBullet].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
					}
				}
			}

			if (g_aBullet[nCntBullet].pos.x > SCREEN_WIDTH)
			{//�e����ʊO�ɏo����
				g_aBullet[nCntBullet].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
			}

			//�����̃J�E���g�_�E��
			g_aBullet[nCntBullet].nLife -= 1;
			if (g_aBullet[nCntBullet].nLife == 0)
			{//������0�ɂȂ�����
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
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
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
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BULLETTYPE type)
{	
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{//�e���g�p����Ă��Ȃ��ꍇ
			g_aBullet[nCntBullet].pos = pos;		//�ʒu
			g_aBullet[nCntBullet].move = move;		//�ړ���
			g_aBullet[nCntBullet].nLife = nLife;	//���C�t
			g_aBullet[nCntBullet].type = type;		//���
			g_aBullet[nCntBullet].bUse = true;		//�e���g�p���Ă����Ԃɂ���
			break;
		}
	}
}