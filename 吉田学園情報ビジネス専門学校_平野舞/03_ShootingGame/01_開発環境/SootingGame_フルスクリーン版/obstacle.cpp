//-------------------------------------------
//
//��Q������[obstacle.cpp]
//Author:���앑
//
//-------------------------------------------

//�C���N���[�h�t�@�C��
#include "obstacle.h"
#include "score.h"
#include "time.h"
#include "player.h"

//�O���[�o���錾
LPDIRECT3DTEXTURE9 g_pTextureObstacle = NULL;			//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffObstacle = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Obstacle g_Obstacle[MAX_OBSTACLE];						//��Q���̏��
	
//-------------------------------------------
//����������
//-------------------------------------------
void InitObstacle(void)
{
	//����������
	for (int nCount = 0; nCount < MAX_OBSTACLE; nCount++)
	{
		g_Obstacle[nCount].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
		g_Obstacle[nCount].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ���
		g_Obstacle[nCount].bUse = false;							//�g�p���Ȃ�
	}

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/obstacle.png",
		&g_pTextureObstacle);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_OBSTACLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffObstacle,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffObstacle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntObs = 0; nCntObs < MAX_OBSTACLE; nCntObs++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_Obstacle[nCntObs].pos.x - (OBSTACLE_WIDTH / 2.0f), g_Obstacle[nCntObs].pos.y - (OBSTACLE_HEIGHT / 2.0f), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Obstacle[nCntObs].pos.x + (OBSTACLE_WIDTH / 2.0f), g_Obstacle[nCntObs].pos.y - (OBSTACLE_HEIGHT / 2.0f), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Obstacle[nCntObs].pos.x - (OBSTACLE_WIDTH / 2.0f), g_Obstacle[nCntObs].pos.y + (OBSTACLE_HEIGHT / 2.0f), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Obstacle[nCntObs].pos.x + (OBSTACLE_WIDTH / 2.0f), g_Obstacle[nCntObs].pos.y + (OBSTACLE_HEIGHT / 2.0f), 0.0f);

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
	g_pVtxBuffObstacle->Unlock();
}

//-------------------------------------------
//�I������
//-------------------------------------------
void UninitObstacle(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureObstacle != NULL)
	{
		g_pTextureObstacle->Release();
		g_pTextureObstacle = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffObstacle != NULL)
	{
		g_pVtxBuffObstacle->Release();
		g_pVtxBuffObstacle = NULL;
	}
}

//-------------------------------------------
//�X�V����
//-------------------------------------------
void UpdateObstacle(void)
{
	//�^�C�����l��
	int nGetTime = GetTime();

	//��Q����ݒu
	if (nGetTime == 55 || nGetTime == 45)
	{
		//���ݎ������V�[�h(��)�ɂ���
		srand((unsigned int)time(NULL));

		int nPosY = rand() % 500 + 50;		//������50�`650���w��
		SetObstacle(D3DXVECTOR3(1300.0f, nPosY, 0.0f));
	}

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffObstacle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntObs = 0; nCntObs < MAX_OBSTACLE; nCntObs++)
	{
		if (g_Obstacle[nCntObs].bUse)
		{
			//�ʒu���̍X�V
			g_Obstacle[nCntObs].move.x = 3.0f;
			g_Obstacle[nCntObs].pos.x -= g_Obstacle[nCntObs].move.x;

			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_Obstacle[nCntObs].pos.x - (OBSTACLE_WIDTH / 2.0f), g_Obstacle[nCntObs].pos.y - (OBSTACLE_HEIGHT / 2.0f), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Obstacle[nCntObs].pos.x + (OBSTACLE_WIDTH / 2.0f), g_Obstacle[nCntObs].pos.y - (OBSTACLE_HEIGHT / 2.0f), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Obstacle[nCntObs].pos.x - (OBSTACLE_WIDTH / 2.0f), g_Obstacle[nCntObs].pos.y + (OBSTACLE_HEIGHT / 2.0f), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Obstacle[nCntObs].pos.x + (OBSTACLE_WIDTH / 2.0f), g_Obstacle[nCntObs].pos.y + (OBSTACLE_HEIGHT / 2.0f), 0.0f);

			if (g_Obstacle[nCntObs].pos.x < 0)
			{//��ʊO�ɏo����
				g_Obstacle[nCntObs].bUse = false;
			}
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffObstacle->Unlock();
}

//-------------------------------------------
//�`�揈��
//-------------------------------------------
void DrawObstacle(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffObstacle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntObs = 0; nCntObs < MAX_OBSTACLE; nCntObs++)
	{
		if (g_Obstacle[nCntObs].bUse)
		{//�G���g�p����Ă���ꍇ
		 //�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_pTextureObstacle);
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntObs * 4, 2);
		}
	}
}

//-------------------------------------------
//�ݒ菈��
//-------------------------------------------
void SetObstacle(D3DXVECTOR3 pos)
{
	for (int nCntObs = 0; nCntObs < MAX_OBSTACLE; nCntObs++)
	{
		if (!g_Obstacle[nCntObs].bUse)
		{//��Q�����g�p����Ă��Ȃ��ꍇ
			g_Obstacle[nCntObs].pos = pos;		//�ʒu
			g_Obstacle[nCntObs].bUse;			//�g�p����

			break;
		}
	}
}

//-------------------------------------------
//���̎擾����
//-------------------------------------------
Obstacle * GetObstacle(void)
{
	return &g_Obstacle[0];
}

//-------------------------------------------
//�����蔻�菈��
//-------------------------------------------
void CollisionObstacle(D3DXVECTOR3 * pPos, float fWidth, float fHeigtht)
{
	for (int nCntObs = 0; nCntObs < MAX_OBSTACLE; nCntObs++)
	{
		if (g_Obstacle[nCntObs].bUse)
		{//��Q�����g���Ă���Ƃ�
			if (pPos->x - (fWidth / 2.0f) >= g_Obstacle[nCntObs].pos.x - (OBSTACLE_WIDTH / 2.0f)
				&& pPos->x + (fWidth / 2.0f) <= g_Obstacle[nCntObs].pos.x + (OBSTACLE_WIDTH / 2.0f)
				&& pPos->y + (fHeigtht / 2.0f) >= g_Obstacle[nCntObs].pos.y - (OBSTACLE_HEIGHT / 2.0f)
				&& pPos->y - (fHeigtht / 2.0f) <= g_Obstacle[nCntObs].pos.y + (OBSTACLE_HEIGHT / 2.0f))
			{
				HitPlayer(1);		//�q�b�g����
			}
		}
	}
}