//-------------------------------------------
//
//�G�̏���[enemy.cpp]
//Author:���앑
//
//-------------------------------------------

//�C���N���[�h�t�@�C��
#include "enemy.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureEnemy[NUM_ENEMY] = {};	//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;			//���_�o�b�t�@�ւ̃|�C���^
Enemy g_aEnemy[MAX_ENEMY];								//�G�̏��
int g_nNumEnemy = 0;									//�G�̑���

//-------------------------------------------
//�G�̏���������
//-------------------------------------------
void InitEnemy(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	int nCntEnemy;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/enemy000.png",
		&g_apTextureEnemy[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/enemy001.png",
		&g_apTextureEnemy[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/enemy002.png",
		&g_apTextureEnemy[2]);

	//�G�̏��̏�����
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu�̏�����
		g_aEnemy[nCntEnemy].PosOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�O�ʒu���̏�����
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ��ʂ̏�����
		g_aEnemy[nCntEnemy].nNumber = 0;								//���Ԗڂ�
		g_aEnemy[nCntEnemy].nType = ENEMY_GHOST;						//��ނ̏�����
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
		g_aEnemy[nCntEnemy].nCounterState = 60;
		g_aEnemy[nCntEnemy].nCounterAnim = 0;
		g_aEnemy[nCntEnemy].nPatternAnim = 0;
		g_aEnemy[nCntEnemy].nLife = 0;									//�����̏�����
		g_aEnemy[nCntEnemy].bUse = false;								//�g�p�̏�����
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
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - (ENEMY_WIDTH / 2), g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (ENEMY_WIDTH / 2), g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - (ENEMY_WIDTH / 2), g_aEnemy[nCntEnemy].pos.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (ENEMY_WIDTH / 2), g_aEnemy[nCntEnemy].pos.y, 0.0f);

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

	//���΂�
	SetEnemy(D3DXVECTOR3(1280.0f, 420.0f, 0.0f), D3DXVECTOR3(-0.9f, 0.0f, 0.0f), ENEMY_GHOST, 1, 0);
	SetEnemy(D3DXVECTOR3(2670.0f, 400.0f, 0.0f), D3DXVECTOR3(-1.3f, 0.0f, 0.0f), ENEMY_GHOST, 1, 0);
	SetEnemy(D3DXVECTOR3(4090.0f, 620.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMY_GHOST, 1, 1);
	SetEnemy(D3DXVECTOR3(5690.0f, 300.0f, 0.0f), D3DXVECTOR3(-0.6f, 0.0f, 0.0f), ENEMY_GHOST, 1, 0);
	SetEnemy(D3DXVECTOR3(6990.0f, 300.0f, 0.0f), D3DXVECTOR3(-0.4f, 0.0f, 0.0f), ENEMY_GHOST, 1, 0);
	SetEnemy(D3DXVECTOR3(8300.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMY_GHOST, 1, 1);

	//�[��
	SetEnemy(D3DXVECTOR3(700.0f, 650.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), ENEMY_BONE, 11, 0);
	SetEnemy(D3DXVECTOR3(1800.0f, 650.0f, 0.0f), D3DXVECTOR3(-1.2f, 0.0f, 0.0f), ENEMY_BONE, 11, 0);
	SetEnemy(D3DXVECTOR3(2200.0f, 650.0f, 0.0f), D3DXVECTOR3(-0.8f, 0.0f, 0.0f), ENEMY_BONE, 11, 0);
	SetEnemy(D3DXVECTOR3(3200.0f, 650.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f), ENEMY_BONE, 11, 0);
	SetEnemy(D3DXVECTOR3(8200.0f, 650.0f, 0.0f), D3DXVECTOR3(-0.3f, 0.0f, 0.0f), ENEMY_BONE, 11, 0);

	//�T
	SetEnemy(D3DXVECTOR3(1380.0f, 650.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), ENEMY_WOLF, 2, 0);
	SetEnemy(D3DXVECTOR3(2700.0f, 650.0f, 0.0f), D3DXVECTOR3(-1.7f, 0.0f, 0.0f), ENEMY_WOLF, 2, 0);
	SetEnemy(D3DXVECTOR3(3800.0f, 650.0f, 0.0f), D3DXVECTOR3(-1.3f, 0.0f, 0.0f), ENEMY_WOLF, 2, 0);
	SetEnemy(D3DXVECTOR3(4200.0f, 650.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f), ENEMY_WOLF, 2, 0);
	SetEnemy(D3DXVECTOR3(4200.0f, 650.0f, 0.0f), D3DXVECTOR3(-0.3f, 0.0f, 0.0f), ENEMY_WOLF, 2, 0);
	SetEnemy(D3DXVECTOR3(4500.0f, 650.0f, 0.0f), D3DXVECTOR3(-0.2f, 0.0f, 0.0f), ENEMY_WOLF, 2, 0);

	for (int nCount = 0; nCount < 10; nCount++)
	{
		SetEnemy(D3DXVECTOR3(6400.0f + (-100.0f * nCount), 650.0f, 0.0f), D3DXVECTOR3(-0.2f, 0.0f, 0.0f), ENEMY_WOLF, 2, 0);
	}

	for (int nCount = 0; nCount < 10; nCount++)
	{
		SetEnemy(D3DXVECTOR3(7200.0f + (-100.0f * nCount), 650.0f, 0.0f), D3DXVECTOR3(-0.2f, 0.0f, 0.0f), ENEMY_WOLF, 2, 0);
	}
}

//-------------------------------------------
//�G�̏I������
//-------------------------------------------
void UninitEnemy(void)
{
	int nCntEnemy;

	//�e�N�X�`���̔j��
	for (nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
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

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//�G���g�p����Ă���
			//�O��̈ʒu���X�V
			g_aEnemy[nCntEnemy].PosOld = g_aEnemy[nCntEnemy].pos;

			//�J�E���^�[�𑝂₷
			g_aEnemy[nCntEnemy].nCounterAnim++;

			if (g_aEnemy[nCntEnemy].nCounterAnim % 10 == 0)
			{
				g_aEnemy[nCntEnemy].nPatternAnim++;
			}
			if (g_aEnemy[nCntEnemy].nPatternAnim == 4)
			{
				g_aEnemy[nCntEnemy].nPatternAnim = 0;
			}

			if (g_aEnemy[nCntEnemy].nType == ENEMY_GHOST)
			{//���΂�
				//�e�N�X�`���̍X�V
				pVtx[0].tex = D3DXVECTOR2((1.0f / 4) * g_aEnemy[nCntEnemy].nPatternAnim, 0.0f);
				pVtx[1].tex = D3DXVECTOR2((1.0f / 4) * (g_aEnemy[nCntEnemy].nPatternAnim + 1), 0.0f);
				pVtx[2].tex = D3DXVECTOR2((1.0f / 4) * g_aEnemy[nCntEnemy].nPatternAnim, (1.0f / 2));
				pVtx[3].tex = D3DXVECTOR2((1.0f / 4) * (g_aEnemy[nCntEnemy].nPatternAnim + 1), (1.0f / 2));
			}
			else
			{//���̃L����
				pVtx[0].tex = D3DXVECTOR2((1.0f / 3) * g_aEnemy[nCntEnemy].nPatternAnim, 0.0f);
				pVtx[1].tex = D3DXVECTOR2((1.0f / 3) * (g_aEnemy[nCntEnemy].nPatternAnim + 1), 0.0f);
				pVtx[2].tex = D3DXVECTOR2((1.0f / 3) * g_aEnemy[nCntEnemy].nPatternAnim, (1.0f / 2));
				pVtx[3].tex = D3DXVECTOR2((1.0f / 3) * (g_aEnemy[nCntEnemy].nPatternAnim + 1), (1.0f / 2));
			}

			//�ʒu���X�V
			g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].move.x;
			g_aEnemy[nCntEnemy].pos.y += g_aEnemy[nCntEnemy].move.y;

			if (g_aEnemy[nCntEnemy].nType == ENEMY_BONE || g_aEnemy[nCntEnemy].nType == ENEMY_WOLF)
			{//�d��
				g_aEnemy[nCntEnemy].move.y += ENEMY_G;
				//�u���b�N�Ƃ̓����蔻��
				CollisionBlock(&g_aEnemy[nCntEnemy].pos, &g_aEnemy[nCntEnemy].PosOld, &g_aEnemy[nCntEnemy].move, (ENEMY_WIDTH / 2), ENEMY_HEIGHT);
			}

			if (g_aEnemy[nCntEnemy].nType == ENEMY_GHOST)
			{
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
			}
			if (g_aEnemy[nCntEnemy].nNumber == 1)
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(0.8f, 0.6f, 0.6f, 0.7f);
				pVtx[1].col = D3DXCOLOR(0.8f, 0.6f, 0.6f, 0.7f);
				pVtx[2].col = D3DXCOLOR(0.8f, 0.6f, 0.6f, 0.7f);
				pVtx[3].col = D3DXCOLOR(0.8f, 0.6f, 0.6f, 0.7f);
			}

			//��ԊǗ�
			//StateEnemy(nCntEnemy);

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

				if (g_aEnemy[nCntEnemy].pos.x < 0 || g_aEnemy[nCntEnemy].pos.y < SCREEN_HEIGHT)
				{
					g_aEnemy[nCntEnemy].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
				}

			}

			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - (ENEMY_WIDTH / 2), g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (ENEMY_WIDTH / 2), g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - (ENEMY_WIDTH / 2), g_aEnemy[nCntEnemy].pos.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (ENEMY_WIDTH / 2), g_aEnemy[nCntEnemy].pos.y, 0.0f);
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
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, ENEMY nType,int nLife,int nNumber)
{	
	int nCntEnemy;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{//�G���g�p����Ă��Ȃ��ꍇ
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].move = move;
			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].nLife = nLife;
			g_aEnemy[nCntEnemy].nNumber = nNumber;
			g_aEnemy[nCntEnemy].bUse = true;

			break;
		}
		pVtx += 4;		//���_�f�[�^���S���i�߂�
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

	pVtx += 4 * nCntEnemy;

	if (g_aEnemy[nCntEnemy].bUse == true)
	{
		g_aEnemy[nCntEnemy].nLife -= nDamage;
		if (g_aEnemy[nCntEnemy].nLife == 0)
		{
			g_aEnemy[nCntEnemy].bUse = false;
			//���o
			PlaySound(SOUND_LABEL_SE_HIT);
			SetExplosion(D3DXVECTOR3 (g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y - (ENEMY_HEIGHT / 2),0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f));
			g_nNumEnemy--;
		}
		else
		{
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
			g_aEnemy[nCntEnemy].nCounterState = 10;
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
	return &g_aEnemy[0];
}

//-------------------------------------------
//�G�̓����蔻��
//-------------------------------------------
void CollisionEnemy(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove,float fWidth, float fHeigtht)
{
	Player *pPlayer = GetPlayer();

	int nCntEnemy;

	if (pPlayer->bDisp == true && pPlayer->state == PLAYERSTATE_NORMAL)
	{
		for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
		{
			if (g_aEnemy[nCntEnemy].bUse == true)
			{
				if (g_aEnemy[nCntEnemy].nType == ENEMY_BONE)
				{//�[��
					if (pPos->x + (fWidth / 2) >= g_aEnemy[nCntEnemy].pos.x - (ENEMY_WIDTH / 2)
						&& pPos->x - (fWidth / 2) <= g_aEnemy[nCntEnemy].pos.x + (ENEMY_WIDTH / 2))
					{
						if (pPosOld->y <= g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT
							&& pPos->y >= g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT)
						{//�G�̓��ɓ���������
							pMove->y -= 20.0f;
							HitEnemy(nCntEnemy, g_aEnemy[nCntEnemy].nLife);
							AddScore(400);
						}
						else if (pPosOld->y - fHeigtht >= g_aEnemy[nCntEnemy].pos.y
							&& pPos->y - fHeigtht <= g_aEnemy[nCntEnemy].pos.y)
						{//���ɓ���������
							HitPlayer(1);
						}
					}
					if (pPos->y - fHeigtht <= g_aEnemy[nCntEnemy].pos.y
						&&pPos->y > g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT)
					{
						if (pPosOld->x - (fWidth / 2) >= g_aEnemy[nCntEnemy].pos.x + (ENEMY_WIDTH / 2) - g_aEnemy[nCntEnemy].move.x
							&& pPos->x - (fWidth / 2) <= g_aEnemy[nCntEnemy].pos.x + (ENEMY_WIDTH / 2) - g_aEnemy[nCntEnemy].move.x)
						{//���ɓ���������
							HitPlayer(1);
						}
						else if (pPosOld->x + (fWidth / 2) <= g_aEnemy[nCntEnemy].pos.x - (ENEMY_WIDTH / 2) - g_aEnemy[nCntEnemy].move.x
							&& pPos->x + (fWidth / 2) >= g_aEnemy[nCntEnemy].pos.x - (ENEMY_WIDTH / 2) - g_aEnemy[nCntEnemy].move.x)
						{//�E�ɓ���������
							HitPlayer(1);
						}
					}
				}
				else if ((pPos->x + (fWidth / 2) >= g_aEnemy[nCntEnemy].pos.x - (ENEMY_WIDTH / 2)
					&& pPos->x - (fWidth / 2) <= g_aEnemy[nCntEnemy].pos.x + (ENEMY_WIDTH / 2)
					&& pPos->y >= g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT
					&& pPos->y - fHeigtht <= g_aEnemy[nCntEnemy].pos.y))
				{//���̑�
					if (g_aEnemy[nCntEnemy].nType == ENEMY_GHOST)
					{//���΂�
						HitPlayer(pPlayer->nLife);
					}
					else if (g_aEnemy[nCntEnemy].nType == ENEMY_WOLF)
					{//�T
						HitPlayer(1);
					}
				}
			}
		}
	}
}

//-------------------------------------------
//�G�̈ړ�����
//-------------------------------------------
void MoveEnemy(int nCntEnemy)
{
	BLOCK *pBlock = GetBlock();
	if (g_aEnemy[nCntEnemy].pos.x < pBlock->pos.x)
	{

	}
}

//-------------------------------------------
//�G�̏�ԊǗ�����
//-------------------------------------------
//void StateEnemy(int nCntEnemy)
//{
//	//���_���ւ̃|�C���^
//	VERTEX_2D *pVtx;
//
//	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
//
//	//�G�̈ʒu���̍X�V
//	switch (g_aEnemy[nCntEnemy].state)
//	{
//	case ENEMYSTATE_NORMAL:
//		break;
//	case ENEMYSTATE_DAMAGE:
//		g_aEnemy[nCntEnemy].nCounterState--;
//		if (g_aEnemy[nCntEnemy].nCounterState <= 0)
//		{
//			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
//			//���_�J���[�̐ݒ�
//			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		}
//		break;
//	}
//
//		//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuffEnemy->Unlock();
//}