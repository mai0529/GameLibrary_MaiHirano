//-------------------------------------------
//
//�G�̏���[enemy.cpp]
//Author:���앑
//
//-------------------------------------------

//�C���N���[�h�t�@�C��
#include "sound.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"
#include "fade.h"
#include "Sweet.h"
#include "player.h"
#include "Bullet.h"

//�}�N����`
#define NUM_ENEMY			(4)			//�G�̎�ނ̍ő吔

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureEnemy[NUM_ENEMY] = {};	//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;			//���_�o�b�t�@�ւ̃|�C���^
Enemy g_aEnemy[MAX_ENEMY];								//�G�̏��

//�O���t�@�C���p�̃O���[�o���錾
EnemyFile g_enemyFile[MAX_ENEMY][128];					//�O���t�@�C���p�̓G���
char g_EnemyTex[4][128];								//�e�N�X�`���ǂݍ��ݗp
int g_nCntEnemy;										//�J�E���^

//-------------------------------------------
//�G�̏���������
//-------------------------------------------
void InitEnemy(void)
{
	//�O���t�@�C���̓ǂݍ���
	LoadEnemy();

	//�G�̏��̏�����
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu�̏�����
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ��ʂ̏�����
		g_aEnemy[nCntEnemy].nType = 0;									//��ނ̏�����
		g_aEnemy[nCntEnemy].bUse = false;								//�g�p�̏�����
		g_aEnemy[nCntEnemy].nLife = 2;									//�����̏�����
	}

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCntTex = 0; nCntTex < NUM_ENEMY; nCntTex++)
	{//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			&g_EnemyTex[nCntTex][0],
			&g_apTextureEnemy[nCntTex]);
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

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
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

	//���ݎ������V�[�h(��)�ɂ���
	srand((unsigned int)time(NULL));

	//�����_���p�̕ϐ���錾
	int nAddPosX;
	int nSubPosX;
	int nAddPosY;
	int nSubPosY;

	//�����_���z�u�p�̕ϐ���錾
	int nPosX;
	int nPosY;

	for (int nCount = 0; nCount < g_nCntEnemy; nCount++)
	{
		nAddPosX = rand() % 150 + 150;		//150�`300�������_���Ŏw��
		nAddPosY = rand() % 80 + 20;		//20�`100�������_���Ŏw��

		nSubPosX = rand() % 150 - 200;		//-200�`0�������_���Ŏw��
		nSubPosY = rand() % 80 - 100;		//-100�`0�������_���Ŏw��

		nPosX = nAddPosX + nSubPosX;		//x���W�̃����_��
		nPosY = nAddPosY + nSubPosY;		//y���W�̃����_��

		//�G��ݒu
		SetEnemy(D3DXVECTOR3(g_enemyFile[nCount][0].pos.x + nPosX, g_enemyFile[nCount][0].pos.y + nPosY, g_enemyFile[nCount][0].pos.z),
			g_enemyFile[nCount][0].nType);
	}
}

//-------------------------------------------
//�G�̏I������
//-------------------------------------------
void UninitEnemy(void)
{
	//�e�N�X�`���̔j��
	for (int nCntEnemy = 0; nCntEnemy < 4; nCntEnemy++)
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
	//�v���C���[���̎擾
	Player *pPlayer = GetPlayer();

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//�G���g�p����Ă���
			//�G�̏�ԊǗ�
			StateEnemy(nCntEnemy);

			//�G�̈ʒu���̍X�V
			g_aEnemy[nCntEnemy].move.x = 3.0f;

			//�ړ��ʂ��ʒu�Ɍ��Z
			g_aEnemy[nCntEnemy].pos.x -= g_aEnemy[nCntEnemy].move.x;

			//�e�̏���
			//float fDistance =g_aEnemy[nCntEnemy].pos.x - pPlayer->pos.x ;
			//
			//if (fDistance >= 100.0f)
			//{
			//	SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(-10.0f, 0.0f, 0.0f), 50.0f, BULLETTYPE_ENEMY);
			//}

			//���َq�̓����蔻��
			CollisionSweet(&g_aEnemy[nCntEnemy].pos, ENEMY_WIDTH, ENEMY_HEIGHT);

			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT, g_aEnemy[nCntEnemy].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT, g_aEnemy[nCntEnemy].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y + ENEMY_HEIGHT, g_aEnemy[nCntEnemy].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y + ENEMY_HEIGHT, g_aEnemy[nCntEnemy].pos.z);

			if (g_aEnemy[nCntEnemy].pos.y < 0)
			{//��ʊO�ɏo����
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
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
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
void SetEnemy(D3DXVECTOR3 pos, int nType)
{	
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{//�G���g�p����Ă��Ȃ��ꍇ
			g_aEnemy[nCntEnemy].pos = pos;		//�ʒu
			g_aEnemy[nCntEnemy].nType = nType;	//���
			g_aEnemy[nCntEnemy].bUse = true;	//�g�p����
		
			break;
		}
	}
}

//-------------------------------------------
//�G�̏�ԊǗ�����
//-------------------------------------------
void StateEnemy(int nCntEnemy)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//pVtx�̃f�[�^���
	pVtx += 4 * nCntEnemy;

	switch (g_aEnemy[nCntEnemy].state)
	{
	case ENEMYSTATE_NORMAL:		//�ʏ���
		break;
	case ENEMYSTATE_DAMAGE:		//�_���[�W���
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

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
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

	//pVtx�̃f�[�^���
	pVtx += 4 * nCntEnemy;

	if (g_aEnemy[nCntEnemy].bUse == true)
	{
		g_aEnemy[nCntEnemy].nLife -= nDamage;		//���C�t��1���炷

		if (g_aEnemy[nCntEnemy].nLife == 0)
		{//���C�t��0�ɂȂ�����
			SetExplosion(g_aEnemy[nCntEnemy].pos, 255);		//�����̏���	
			g_aEnemy[nCntEnemy].bUse = false;				//�g�p���Ȃ�
		}
		else
		{
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;		//�_���[�W��Ԃɂ���
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
//�O���t�@�C���̓ǂݍ��ݏ���
//-------------------------------------------
void LoadEnemy(void)
{
	char cData[128];
	int nCntTex = 0;		//�e�N�X�`���̃J�E���^
	g_nCntEnemy = 0;		//�G�̃J�E���^

	FILE * pFile;

	pFile = fopen("data/enemy.txt", "r");		//�t�@�C�����J��

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		while (1)
		{
			fscanf(pFile, "%s", &cData[0]);

			if (strcmp(&cData[0], "ENEMY_TEXNAME") == 0)
			{//�e�N�X�`������ǂݍ���
				fscanf(pFile, "%s", &cData[0]);
				fscanf(pFile, "%s", &g_EnemyTex[nCntTex][0]);
				nCntTex++;		//�J�E���^�𑝂₷
			}
			else if (strcmp(&cData[0], "PLACESET") == 0)
			{//�o���ꏊ�̓ǂݍ���
				do
				{
					fscanf(pFile, "%s", &cData[0]);

					if (strcmp(&cData[0], "POS") == 0)
					{//�ꏊ��ǂݍ���
						fscanf(pFile, "%s", &cData[0]);
						fscanf(pFile, "%f", &g_enemyFile[g_nCntEnemy][0].pos.x);
						fscanf(pFile, "%f", &g_enemyFile[g_nCntEnemy][0].pos.y);
						fscanf(pFile, "%f", &g_enemyFile[g_nCntEnemy][0].pos.z);
					}
					else if (strcmp(&cData[0], "TYPE") == 0)
					{//��ނ�ǂݍ���
						fscanf(pFile, "%s", &cData[0]);
						fscanf(pFile, "%d", &g_enemyFile[g_nCntEnemy][0].nType);
					}
				} while (strcmp(&cData[0], "END_PLACESSET") != 0);
				g_nCntEnemy++;
			}

			if (strcmp(&cData[0], "END_ENEMYSET") == 0)
			{
				break;
			}
		}
		fclose(pFile);			//�t�@�C�������
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("�t�@�C�����J���܂���ł���");
	}
}

//-------------------------------------------
//�G�̎擾
//-------------------------------------------
Enemy * GetEnemy(void)
{
	return &g_aEnemy[0];
}

