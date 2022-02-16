//-------------------------------------------
//
//�G�̏���[enemy.cpp]
//Author:���앑
//
//-------------------------------------------
#include "sound.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"
#include "fade.h"

//�}�N����`
#define NUM_ENEMY			(6)			//�G�̍ő吔
#define ENEMY_WIDTH			(60.0f)		//�G�̕�
#define ENEMY_HEIGHT		(70.0f)		//�G�̍���

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureEnemy[NUM_ENEMY] = {};	//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;			//���_�o�b�t�@�ւ̃|�C���^
Enemy g_aEnemy[MAX_ENEMY];								//�G�̏��
int g_nNumEnemy = 0;									//�G�̑���
int g_CntEnemy = 0;										//�J�E���g

//-------------------------------------------
//�G�̏���������
//-------------------------------------------
void InitEnemy(void)
{
	g_CntEnemy = 0;

	////�T�E���h�̍Đ�
	//PlaySound(SOUND_LABEL_SE_HIT);

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	int nCntEnemy;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/enemy004.png",
		&g_apTextureEnemy[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/enemy005.png",
		&g_apTextureEnemy[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/enemy006.png",
		&g_apTextureEnemy[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/enemy007.png",
		&g_apTextureEnemy[3]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/enemy008.png",
		&g_apTextureEnemy[4]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/enemy009.png",
		&g_apTextureEnemy[5]);

	//�G�̏��̏�����
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu�̏�����
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ��ʂ̏�����
		g_aEnemy[nCntEnemy].nType = ENEMY_HEART;						//��ނ̏�����
		g_aEnemy[nCntEnemy].bUse = false;								//�g�p�̏�����
		g_aEnemy[nCntEnemy].nLife = 0;									//�����̏�����
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT, g_aEnemy[nCntEnemy].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT, g_aEnemy[nCntEnemy].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y + ENEMY_HEIGHT, g_aEnemy[nCntEnemy].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y + ENEMY_HEIGHT, g_aEnemy[nCntEnemy].pos.z);

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
	g_pVtxBuffEnemy->Unlock();
}

//-------------------------------------------
//�G�̏I������
//-------------------------------------------
void UninitEnemy(void)
{
	int nCntEnemy;

	//�e�N�X�`���̔j��
	for (nCntEnemy = 0; nCntEnemy < 4; nCntEnemy++)
	{
		if (g_apTextureEnemy[nCntEnemy] != NULL)
		{
			g_apTextureEnemy[nCntEnemy]->Release();
			g_apTextureEnemy[nCntEnemy] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//-------------------------------------------
//�G�̍X�V����
//-------------------------------------------
void UpdateEnemy(void)
{
	int nCntEnemy;

	//�J�E���g���Ă���
	g_CntEnemy++;

	if (g_CntEnemy == 25)
	{
		SetEnemy(D3DXVECTOR3(1380.0f, 50.0f, 0.0f), D3DXVECTOR3(-3.0f, 0.0f, 0.0f), ENEMY_HEART,2);
		SetEnemy(D3DXVECTOR3(1600.0f, 650.0f, 0.0f), D3DXVECTOR3(-1.6f, 0.0f, 0.0f), ENEMY_CLOVER,2);
		SetEnemy(D3DXVECTOR3(2200.0f, 250.0f, 0.0f), D3DXVECTOR3(-1.9f, 0.0f, 0.0f), ENEMY_SPADE,4);
		SetEnemy(D3DXVECTOR3(2600.0f, 500.0f, 0.0f), D3DXVECTOR3(-2.3f, 0.0f, 0.0f), ENEMY_DIA,4);
		SetEnemy(D3DXVECTOR3(2646.0f, 37.0f, 0.0f), D3DXVECTOR3(-1.6f, 0.0f, 0.0f), ENEMY_BLACKDIA,7);
		SetEnemy(D3DXVECTOR3(1460.0f, 454.0f, 0.0f), D3DXVECTOR3(-1.4f, 0.0f, 0.0f), ENEMY_BLACKSPADE,7);
	}
	if (g_CntEnemy == 100)
	{
		SetEnemy(D3DXVECTOR3(1792.0f, 634.0f, 0.0f), D3DXVECTOR3(-2.6f, 0.0f, 0.0f), ENEMY_HEART, 2);
		SetEnemy(D3DXVECTOR3(3245.0f, 235.0f, 0.0f), D3DXVECTOR3(-3.09f, 0.0f, 0.0f), ENEMY_CLOVER, 2);
		SetEnemy(D3DXVECTOR3(4565.0f, 100.0f, 0.0f), D3DXVECTOR3(-2.4f, 0.0f, 0.0f), ENEMY_HEART, 2);
		SetEnemy(D3DXVECTOR3(3634.0f, 132.0f, 0.0f), D3DXVECTOR3(-4.3f, 0.0f, 0.0f), ENEMY_CLOVER, 2);
	}
	if (g_CntEnemy == 300)
	{
		SetEnemy(D3DXVECTOR3(2280.0f, 70.0f, 0.0f), D3DXVECTOR3(-2.4f, 0.0f, 0.0f), ENEMY_HEART,2);
		SetEnemy(D3DXVECTOR3(1600.0f, 374.0f, 0.0f), D3DXVECTOR3(-4.5f, 0.0f, 0.0f), ENEMY_CLOVER,2);
		SetEnemy(D3DXVECTOR3(3000.0f, 124.0f, 0.0f), D3DXVECTOR3(-1.5f, 0.0f, 0.0f), ENEMY_SPADE,4);
		SetEnemy(D3DXVECTOR3(3954.0f, 47.0f, 0.0f), D3DXVECTOR3(-1.7f, 0.0f, 0.0f), ENEMY_DIA,4);
		SetEnemy(D3DXVECTOR3(3432.0f, 435.0f, 0.0f), D3DXVECTOR3(-2.3f, 0.0f, 0.0f), ENEMY_BLACKDIA, 7);
		SetEnemy(D3DXVECTOR3(2756.0f, 634.0f, 0.0f), D3DXVECTOR3(-1.7f, 0.0f, 0.0f), ENEMY_BLACKSPADE, 7);
	}
	if (g_CntEnemy == 1000)
	{
		SetEnemy(D3DXVECTOR3(1803.0f, 283.0f, 0.0f), D3DXVECTOR3(-3.09f, 0.0f, 0.0f), ENEMY_SPADE, 4);
		SetEnemy(D3DXVECTOR3(1350.0f, 543.0f, 0.0f), D3DXVECTOR3(-3.2f, 0.0f, 0.0f), ENEMY_DIA, 4);
		SetEnemy(D3DXVECTOR3(2540.0f, 253.0f, 0.0f), D3DXVECTOR3(-3.2f, 0.0f, 0.0f), ENEMY_SPADE, 4);
		SetEnemy(D3DXVECTOR3(3209.0f, 609.0f, 0.0f), D3DXVECTOR3(-3.1f, 0.0f, 0.0f), ENEMY_DIA, 4);
		SetEnemy(D3DXVECTOR3(5432.0f, 128.0f, 0.0f), D3DXVECTOR3(-2.07f, 0.0f, 0.0f), ENEMY_BLACKDIA, 7);
		SetEnemy(D3DXVECTOR3(3643.0f, 632.0f, 0.0f), D3DXVECTOR3(-2.5f, 0.0f, 0.0f), ENEMY_BLACKSPADE, 7);
	}
	if (g_CntEnemy == 2000)
	{
		SetEnemy(D3DXVECTOR3(4434.0f, 235.0f, 0.0f), D3DXVECTOR3(-4.9f, 0.0f, 0.0f), ENEMY_HEART, 2);
		SetEnemy(D3DXVECTOR3(3533.0f, 456.0f, 0.0f), D3DXVECTOR3(-4.4f, 0.0f, 0.0f), ENEMY_DIA, 4);
		SetEnemy(D3DXVECTOR3(2540.0f, 196.0f, 0.0f), D3DXVECTOR3(-3.8f, 0.0f, 0.0f), ENEMY_SPADE, 4);
		SetEnemy(D3DXVECTOR3(1653.0f, 524.0f, 0.0f), D3DXVECTOR3(-3.4f, 0.0f, 0.0f), ENEMY_BLACKDIA, 7);
		SetEnemy(D3DXVECTOR3(1990.0f, 364.0f, 0.0f), D3DXVECTOR3(-2.4f, 0.0f, 0.0f), ENEMY_BLACKDIA, 7);
		SetEnemy(D3DXVECTOR3(2978.0f, 333.0f, 0.0f), D3DXVECTOR3(-2.9f, 0.0f, 0.0f), ENEMY_BLACKSPADE, 7);
	}
	if (g_CntEnemy == 3450)
	{
		//���[�h�ݒ�(�Q�[����ʂɈڍs)
		SetFade(MODE_RESULT);
	}

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//�G���g�p����Ă���
			//�G�̈ʒu���̍X�V
			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL:
				break;
			case ENEMYSTATE_DAMAGE:
				g_aEnemy[nCntEnemy].nCounterState--;
				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
					//���_�J���[�̐ݒ�
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
				break;
			}
			g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].move.x;

			//���_���W�̍X�V(�e�N�X�`���̍X�V)
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT, g_aEnemy[nCntEnemy].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT, g_aEnemy[nCntEnemy].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y + ENEMY_HEIGHT, g_aEnemy[nCntEnemy].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y + ENEMY_HEIGHT, g_aEnemy[nCntEnemy].pos.z);

			if (g_aEnemy[nCntEnemy].pos.y < 0)
			{
				g_aEnemy[nCntEnemy].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
			}

		}
		pVtx += 4;		//���_�f�[�^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//-------------------------------------------
//�G�̕`�揈��
//-------------------------------------------
void DrawEnemy(void)
{
	int nCntEnemy;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//�G���g�p����Ă���ꍇ
		 //�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}
}

//-------------------------------------------
//�G�̐ݒ菈��
//-------------------------------------------
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, ENEMY nType,int nLife)
{	
	int nCntEnemy;

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{//�G���g�p����Ă��Ȃ��ꍇ
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].move = move;
			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].bUse = true;	
			g_aEnemy[nCntEnemy].nLife = nLife;
			g_nNumEnemy++;
			break;
		}
	}
}

//-------------------------------------------
//�G�̃q�b�g����
//-------------------------------------------
void HitEnemy(int nCntEnemy, int nDamage)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * nCntEnemy;

	if (g_aEnemy[nCntEnemy].bUse == true)
	{
		g_aEnemy[nCntEnemy].nLife -= nDamage;
		if (g_aEnemy[nCntEnemy].nLife == 0)
		{
			//�����̏���
			SetExplosion(g_aEnemy[nCntEnemy].pos, 255);
			g_aEnemy[nCntEnemy].bUse = false;
			g_nNumEnemy--;
			if (g_nNumEnemy <= 0)
			{
				//���[�h�ݒ�(�Q�[����ʂɈڍs)
				SetFade(MODE_RESULT);
			}
		}
		else
		{
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
			g_aEnemy[nCntEnemy].nCounterState = 5;
			//���_�J���[�̕ύX
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//-------------------------------------------
//�G�̎擾
//-------------------------------------------
Enemy * GetEnemy(void)
{
	return g_aEnemy;
}

