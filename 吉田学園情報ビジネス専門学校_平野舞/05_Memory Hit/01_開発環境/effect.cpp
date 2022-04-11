//-------------------------------------------
//
//�G�t�F�N�g����[effect.cpp]
//Author:���앑
//
//-------------------------------------------
#include "effect.h"

//�}�N����`
#define MAX_EFFECT		(4096)			//�G�t�F�N�g�̍ő吔
#define MAX_TEXEFFECT	(20)			//�G�t�F�N�g�摜�̍ő吔

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureEffect[MAX_TEXEFFECT] = {};	//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;			//���_�o�b�t�@�ւ̃|�C���^
Effect g_aEffect[MAX_EFFECT];								//�G�t�F�N�g�̏��

//�O���t�@�C���ǂݍ��ݗp�̃O���[�o���ϐ��錾
char g_cReadEffect[256];									//�����ǂݍ��ݗp
char g_cTexName[30][256];									//�摜���ǂݍ��ݗp
int g_nNumEffect;											//�摜�̐��l���p

//-------------------------------------------
//�G�t�F�N�g�̏���������
//-------------------------------------------
void InitEffect(void)
{
	//�O���t�@�C���ǂݍ���
	LoadEffectFile();

	//�G�t�F�N�g�\���̂̏�����
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
		g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//�J���[
		g_aEffect[nCntEffect].fSize = 0.0f;								//�T�C�Y
		g_aEffect[nCntEffect].nLife = 0;								//���C�t
		g_aEffect[nCntEffect].nSelect = 0;								//�����̑I��
		g_aEffect[nCntEffect].nType = EFFECT_EFE1;						//���
		g_aEffect[nCntEffect].bUse = false;								//�g�p���Ȃ�
	}

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCount = 0; nCount < g_nNumEffect; nCount++)
	{//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			&g_cTexName[nCount][0],
			&g_pTextureEffect[nCount]);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - (g_aEffect[nCntEffect].fSize / 2.0f), g_aEffect[nCntEffect].pos.y - (g_aEffect[nCntEffect].fSize / 2.0f), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + (g_aEffect[nCntEffect].fSize / 2.0f), g_aEffect[nCntEffect].pos.y - (g_aEffect[nCntEffect].fSize / 2.0f), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - (g_aEffect[nCntEffect].fSize / 2.0f), g_aEffect[nCntEffect].pos.y + (g_aEffect[nCntEffect].fSize / 2.0f), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + (g_aEffect[nCntEffect].fSize / 2.0f), g_aEffect[nCntEffect].pos.y + (g_aEffect[nCntEffect].fSize / 2.0f), 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r,g_aEffect[nCntEffect].col.g,g_aEffect[nCntEffect].col.b, g_aEffect[nCntEffect].col.a);
		pVtx[1].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r,g_aEffect[nCntEffect].col.g,g_aEffect[nCntEffect].col.b, g_aEffect[nCntEffect].col.a);
		pVtx[2].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r,g_aEffect[nCntEffect].col.g,g_aEffect[nCntEffect].col.b, g_aEffect[nCntEffect].col.a);
		pVtx[3].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r,g_aEffect[nCntEffect].col.g,g_aEffect[nCntEffect].col.b, g_aEffect[nCntEffect].col.a);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;		//���_�f�[�^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//-------------------------------------------
//�G�t�F�N�g�̏I������
//-------------------------------------------
void UninitEffect(void)
{
	for (int nCount = 0; nCount < g_nNumEffect; nCount++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureEffect[nCount] != NULL)
		{
			g_pTextureEffect[nCount]->Release();
			g_pTextureEffect[nCount] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//-------------------------------------------
//�G�t�F�N�g�̍X�V����
//-------------------------------------------
void UpdateEffect(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{//�G�t�F�N�g���g�p����Ă���

			//�����̑I������
			SelectEffect(nCntEffect, g_aEffect[nCntEffect].nSelect);

			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - (g_aEffect[nCntEffect].fSize / 2.0f), g_aEffect[nCntEffect].pos.y - (g_aEffect[nCntEffect].fSize / 2.0f), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + (g_aEffect[nCntEffect].fSize / 2.0f), g_aEffect[nCntEffect].pos.y - (g_aEffect[nCntEffect].fSize / 2.0f), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - (g_aEffect[nCntEffect].fSize / 2.0f), g_aEffect[nCntEffect].pos.y + (g_aEffect[nCntEffect].fSize / 2.0f), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + (g_aEffect[nCntEffect].fSize / 2.0f), g_aEffect[nCntEffect].pos.y + (g_aEffect[nCntEffect].fSize / 2.0f), 0.0f);

			//���_�J���[�̍X�V
			pVtx[0].col = g_aEffect[nCntEffect].col;
			pVtx[1].col = g_aEffect[nCntEffect].col;
			pVtx[2].col = g_aEffect[nCntEffect].col;
			pVtx[3].col = g_aEffect[nCntEffect].col;

			if (g_aEffect[nCntEffect].nLife <= 0 || g_aEffect[nCntEffect].fSize <= 0 || g_aEffect[nCntEffect].col.a <= 0.0f)
			{//�����A�T�C�Y�Aa�l��0�ɂȂ�����
				g_aEffect[nCntEffect].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
			}
		}
		pVtx += 4;		//���_�f�[�^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//-------------------------------------------
//�G�t�F�N�g�̕`�揈��
//-------------------------------------------
void DrawEffect(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{//�G�t�F�N�g���g�p����Ă���ꍇ

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_pTextureEffect[g_aEffect[nCntEffect].nType]);

			//a�u���C���f�B���O�����Z�����ɐݒ�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);
		}
	}

	//a�u���C���f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//-------------------------------------------
//�G�t�F�N�g�̐ݒ菈��
//
//D3DXVECTOR3 pos �� �ʒu���w��
//D3DXCOLOR col�@ �� �F���w��
//int nLife		  �� �\������(����)
//float fSize	  �� �T�C�Y���w��
//int nType	�@	�@�� �摜�̎��	
//int nSelect	  �� �����̑I��
//
//-------------------------------------------
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fSize, int nLife, EFFECT nType, int nSelect)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{//�g�p���Ă��Ȃ�������
			g_aEffect[nCntEffect].pos = pos;			//�ʒu
			g_aEffect[nCntEffect].col = col;			//�J���[
			g_aEffect[nCntEffect].nLife = nLife;		//���C�t
			g_aEffect[nCntEffect].fSize = fSize;		//�T�C�Y
			g_aEffect[nCntEffect].nType = nType;		//�摜�̎��
			g_aEffect[nCntEffect].nSelect = nSelect;	//�����̎��
			g_aEffect[nCntEffect].bUse = true;			//�g�p����

			//�ʒu�ƃT�C�Y�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - (g_aEffect[nCntEffect].fSize / 2.0f), g_aEffect[nCntEffect].pos.y - (g_aEffect[nCntEffect].fSize / 2.0f), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + (g_aEffect[nCntEffect].fSize / 2.0f), g_aEffect[nCntEffect].pos.y - (g_aEffect[nCntEffect].fSize / 2.0f), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - (g_aEffect[nCntEffect].fSize / 2.0f), g_aEffect[nCntEffect].pos.y + (g_aEffect[nCntEffect].fSize / 2.0f), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + (g_aEffect[nCntEffect].fSize / 2.0f), g_aEffect[nCntEffect].pos.y + (g_aEffect[nCntEffect].fSize / 2.0f), 0.0f);

			//���_�J���[�̍X�V
			pVtx[0].col = g_aEffect[nCntEffect].col;
			pVtx[1].col = g_aEffect[nCntEffect].col;
			pVtx[2].col = g_aEffect[nCntEffect].col;
			pVtx[3].col = g_aEffect[nCntEffect].col;

			break;
		}
		pVtx += 4;		//�f�[�^����i�߂�
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffEffect->Unlock();
}

void SelectEffect(int nCount,int nSelect)
{
	switch (nSelect)
	{
	case 0:		//��������������
		g_aEffect[nCount].nLife -= 1;		//���������炵�Ă���
		break;

	case 1:		//�T�C�Y����������
		g_aEffect[nCount].fSize -= 1;		//�T�C�Y�����炵�Ă���
		break;

	case 2:		//a�l����������
		g_aEffect[nCount].col.a -= 0.05f;	//a�l�����炵�Ă���
		break;

	case 3:		//�T�C�Y�Ǝ���������
		g_aEffect[nCount].fSize -= 1;		//�T�C�Y�����炵�Ă���
		g_aEffect[nCount].nLife -= 1;		//���������炵�Ă���
		break;
	
	case 4:		//�T�C�Y��a�l������
		g_aEffect[nCount].fSize -= 1;		//�T�C�Y�����炵�Ă���
		g_aEffect[nCount].col.a -= 0.05f;	//a�l�����炵�Ă���
		break;
	
	case 5:		//������a�l������
		g_aEffect[nCount].nLife -= 1;		//���������炵�Ă���
		g_aEffect[nCount].col.a -= 0.05f;	//a�l�����炵�Ă���
		break;
	
	case 6:		//�����ƃT�C�Y��a�l������
		g_aEffect[nCount].fSize -= 1;		//�T�C�Y�����炵�Ă���
		g_aEffect[nCount].nLife -= 1;		//���������炵�Ă���
		g_aEffect[nCount].col.a -= 0.05f;	//a�l�����炵�Ă���
		break;
	
	default:
		assert(false);
		break;
	}
}

//-------------------------------------------
//�O���t�@�C���ǂݍ��ݏ���
//-------------------------------------------
void LoadEffectFile(void)
{
	FILE * pFile;		//�t�@�C���|�C���^��錾

	//�t�@�C�����J��
	pFile = fopen("data/effect.txt", "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		while (1)
		{
			fscanf(pFile, "%s", &g_cReadEffect[0]);		//������̓ǂݍ���

			if (strcmp(&g_cReadEffect[0], "NUM_EFFECT") == 0)
			{//���f���̐��ǂݍ���
				fscanf(pFile, "%s", &g_cReadEffect[0]);
				fscanf(pFile, "%d", &g_nNumEffect);		//������̓ǂݍ���
			}

			if (strcmp(&g_cReadEffect[0], "EFFECT_FILENAME") == 0)
			{//���f���t�@�C���ǂݍ���
				for (int nCount = 0; nCount < g_nNumEffect; nCount++)
				{
					while (strcmp(&g_cReadEffect[0], "EFFECT_FILENAME") != 0)
					{//���f���t�@�C���l�[���ł͂Ȃ��ꍇ
						fscanf(pFile, "%s", &g_cReadEffect[0]);
					}

					if (strcmp(&g_cReadEffect[0], "EFFECT_FILENAME") == 0)
					{//���f���t�@�C���l�[����������
						fscanf(pFile, "%s", &g_cReadEffect[0]);
						fscanf(pFile, "%s", &g_cTexName[nCount][0]);		//������̓ǂݍ���
					}
				}
			}
			if (strcmp(&g_cReadEffect[0], "END_SCRIPT") == 0)
			{//���̕����������甲����
				break;
			}
		}
		fclose(pFile);									//�t�@�C�������
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("�t�@�C�����J���܂���ł���");
	}
}