//-------------------------------------------
//
//�u���b�N�̏���[block.cpp]
//Author:���앑
//
//-------------------------------------------

//�C���N���[�h�t�@�C��
#include "block.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTextureBlock[BLOCK_NUM] = {};	//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;			//���_�o�b�t�@�ւ̃|�C���^
BLOCK g_aBlock[MAX_BLOCK];								//�u���b�N�̏��

//-------------------------------------------
//�u���b�N�̏���������
//-------------------------------------------
void InitBlock(void)
{
	int nCntBlock;
	
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/block001.jpg",
		&g_apTextureBlock[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/block002.jpg",
		&g_apTextureBlock[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/block004.png",
		&g_apTextureBlock[2]);

	//�u���b�N�̏��̏�����
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu�̏�����
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ��ʂ̏�����
		g_aBlock[nCntBlock].nType = BLOCK_BRICK;						//��ނ̏�����
		g_aBlock[nCntBlock].nNumber = 0;								//���Ԗڂ�
		g_aBlock[nCntBlock].nLife = 0;									//�����̏�����
		g_aBlock[nCntBlock].fWidth = 0;									//���̏�����
		g_aBlock[nCntBlock].fHeigth = 0;								//�����̏�����
		g_aBlock[nCntBlock].nCounterState = 60;							//��ԊǗ��̏�����
		g_aBlock[nCntBlock].bUse = false;								//�g�p�̏�����
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + BLOCK_WIDTH, g_aBlock[nCntBlock].pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + BLOCK_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + BLOCK_WIDTH , g_aBlock[nCntBlock].pos.y + BLOCK_HEIGHT, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;		//���_�f�[�^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();

	//�u���b�N�̐ݒu
	//X���ړ�
	//SetBlock(D3DXVECTOR3(1080.0f, 500.0f, 0.0f), D3DXVECTOR3(-0.7f, 0.0f, 0.0f), BLOCK_WIDTH * 2, BLOCK_HEIGHT / 2, BLOCK_CONCRETE,1,0);
	//Y���ړ�									
	//SetBlock(D3DXVECTOR3(700.0f, 720.0f, 0.0f), D3DXVECTOR3(-0.6f, -0.7f, 0.0f), BLOCK_WIDTH * 2, BLOCK_HEIGHT, BLOCK_CONCRETE,1);
	//����										  
	SetBlock(D3DXVECTOR3(260.0f, 500.0f, 0.0f),  D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_CONCRETE,1,0);
	SetBlock(D3DXVECTOR3(300.0f, 500.0f, 0.0f),  D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION,1,0);
	SetBlock(D3DXVECTOR3(340.0f, 500.0f, 0.0f),  D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_CONCRETE,1,0);
															
	//2�ڂ̃n�e�i�u���b�N									 
	SetBlock(D3DXVECTOR3(1550.0f, 520.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_CONCRETE, 1,0);
	SetBlock(D3DXVECTOR3(1590.0f, 520.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_CONCRETE, 1,0);
	SetBlock(D3DXVECTOR3(1630.0f, 520.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1,0);
															
	//�P�[�L�����ɍs�����߂̃u���b�N						
	SetBlock(D3DXVECTOR3(1320.0f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 3, BLOCK_HEIGHT, BLOCK_CONCRETE, 1,0);
	SetBlock(D3DXVECTOR3(1500.0f, 350.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 3, BLOCK_HEIGHT, BLOCK_CONCRETE, 1,0);
	SetBlock(D3DXVECTOR3(1680.0f, 200.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 3, BLOCK_HEIGHT, BLOCK_CONCRETE, 1,0);
															
	//3�ڂ̃n�e�i�u���b�N									 
	SetBlock(D3DXVECTOR3(1800.0f, 450.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_CONCRETE, 1,0);
	SetBlock(D3DXVECTOR3(1840.0f, 450.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1,1);
	SetBlock(D3DXVECTOR3(1880.0f, 450.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_CONCRETE, 1,0);
															
	//4�ڂ̃n�e�i�u���b�N									 
	SetBlock(D3DXVECTOR3(2500.0f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_CONCRETE, 1, 0);
	SetBlock(D3DXVECTOR3(2540.0f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 2);
	SetBlock(D3DXVECTOR3(2580.0f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_CONCRETE, 1, 0);

	//5�`7�ڂ̃n�e�i�u���b�N
	SetBlock(D3DXVECTOR3(3040.0f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);
	SetBlock(D3DXVECTOR3(3080.0f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 1);
	SetBlock(D3DXVECTOR3(3120.0f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);
																
	//���̃R���N���u���b�N							
	SetBlock(D3DXVECTOR3(3700.0f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 20, BLOCK_HEIGHT, BLOCK_CONCRETE, 1, 0);

	//5�`7�ڂ̃n�e�i�u���b�N
	SetBlock(D3DXVECTOR3(3900.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_CONCRETE, 1, 0);
	SetBlock(D3DXVECTOR3(3940.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);
	SetBlock(D3DXVECTOR3(3980.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 1);
	SetBlock(D3DXVECTOR3(4020.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);
	SetBlock(D3DXVECTOR3(4060.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);
	SetBlock(D3DXVECTOR3(4100.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 2);
	SetBlock(D3DXVECTOR3(4140.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);
	SetBlock(D3DXVECTOR3(4180.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 2, BLOCK_HEIGHT, BLOCK_CONCRETE, 1, 0);
	SetBlock(D3DXVECTOR3(4260.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);
	SetBlock(D3DXVECTOR3(4300.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 1);
	SetBlock(D3DXVECTOR3(4340.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_CONCRETE, 1, 0);

	//?�u���b�N�̊Ԃɂ���R���N��
	SetBlock(D3DXVECTOR3(2655.0f, 150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH , BLOCK_HEIGHT, BLOCK_CONCRETE, 1, 0);
	SetBlock(D3DXVECTOR3(2735.0f, 300.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 2, BLOCK_HEIGHT, BLOCK_CONCRETE, 1, 0);
	SetBlock(D3DXVECTOR3(2850.0f, 450.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 3, BLOCK_HEIGHT, BLOCK_CONCRETE, 1, 0);

	//�R���N���u���b�N
	for (int nCount = 0; nCount < 4; nCount++)
	{
		SetBlock(D3DXVECTOR3(5000.0f + (320 * nCount), 510.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 3, BLOCK_HEIGHT, BLOCK_CONCRETE, 1, 0);
		SetBlock(D3DXVECTOR3(5160.0f + (320 * nCount), 430.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 3, BLOCK_HEIGHT, BLOCK_CONCRETE, 1, 0);
	}

	SetBlock(D3DXVECTOR3(5650.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);
	SetBlock(D3DXVECTOR3(5250.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 2);
	SetBlock(D3DXVECTOR3(6030.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);
	SetBlock(D3DXVECTOR3(6200.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);


	SetBlock(D3DXVECTOR3(6400.0f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 15, BLOCK_HEIGHT, BLOCK_CONCRETE, 1, 0);

	//8�`14�ڂ̃n�e�i�u���b�N
	SetBlock(D3DXVECTOR3(6550.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);
	SetBlock(D3DXVECTOR3(6590.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);
	SetBlock(D3DXVECTOR3(6630.0f, 320.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);
	SetBlock(D3DXVECTOR3(6670.0f, 320.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);
	SetBlock(D3DXVECTOR3(6710.0f, 280.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);
	SetBlock(D3DXVECTOR3(6750.0f, 280.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);

	SetBlock(D3DXVECTOR3(6790.0f, 240.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 5, BLOCK_HEIGHT, BLOCK_CONCRETE, 1, 0);
	for (int nCount = 0; nCount < 3; nCount++)
	{
		SetBlock(D3DXVECTOR3(6830.0f + (BLOCK_WIDTH * nCount), 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_QUESTION, 1, 0);
	}

	//�S�[����O
	for (int nCount = 0; nCount < 7; nCount++)
	{//�K�i
		SetBlock(D3DXVECTOR3(8200.0f + (40 * nCount), 650.0f - (40 * nCount), 0.0f), D3DXVECTOR3(-0.0f, 0.0f, 0.0f), BLOCK_WIDTH,BLOCK_HEIGHT * nCount, BLOCK_CONCRETE, 1,0);
	}
	for (int nCount = 0; nCount < 7; nCount++)
	{//�K�i
		SetBlock(D3DXVECTOR3(8700.0f - (40 * nCount), 650.0f - (40 * nCount), 0.0f), D3DXVECTOR3(-0.0f, 0.0f, 0.0f), BLOCK_WIDTH, BLOCK_HEIGHT * nCount, BLOCK_CONCRETE, 1, 0);
	}
																
	//��														
	SetBlock(D3DXVECTOR3(0.0f, 650.0f, 0.0f),    D3DXVECTOR3(-0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 20, BLOCK_HEIGHT * 2, BLOCK_BRICK, 1,0);
	SetBlock(D3DXVECTOR3(950.0f, 650.0f, 0.0f),  D3DXVECTOR3(-0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 32, BLOCK_HEIGHT * 2, BLOCK_BRICK,  1,0);
	SetBlock(D3DXVECTOR3(2400.0f, 650.0f, 0.0f), D3DXVECTOR3(-0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 21, BLOCK_HEIGHT * 2, BLOCK_BRICK, 1, 0);
	SetBlock(D3DXVECTOR3(3400.0f, 650.0f, 0.0f), D3DXVECTOR3(-0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 32, BLOCK_HEIGHT * 2, BLOCK_BRICK, 1, 0);
	SetBlock(D3DXVECTOR3(4860.0f, 650.0f, 0.0f), D3DXVECTOR3(-0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 60, BLOCK_HEIGHT * 2, BLOCK_BRICK, 1, 0);
	SetBlock(D3DXVECTOR3(7460.0f, 650.0f, 0.0f), D3DXVECTOR3(-0.0f, 0.0f, 0.0f), BLOCK_WIDTH * 48, BLOCK_HEIGHT * 2, BLOCK_BRICK, 1, 0);

}

//-------------------------------------------
//�u���b�N�̏I������
//-------------------------------------------
void UninitBlock(void)
{
	int nCntBlock;

	for (nCntBlock = 0; nCntBlock < BLOCK_NUM; nCntBlock++)
	{
		//�e�N�X�`���̔j��
		if (g_apTextureBlock[nCntBlock] != NULL)
		{
			g_apTextureBlock[nCntBlock]->Release();
			g_apTextureBlock[nCntBlock] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}

//-------------------------------------------
//�u���b�N�̍X�V����
//-------------------------------------------
void UpdateBlock(void)
{
	int nCntBlock;
	float nWnumber;
	float nHnumber;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{//�u���b�N���g�p����Ă���ꍇ
			//StateBlock(nCntBlock);

			//�u���b�N�̈ʒu���̍X�V
			switch (g_aBlock[nCntBlock].state)
			{
			case BLOCKSTATE_NORMAL:
				break;
			case BLOCKSTATE_DAMAGE:
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);

				g_aBlock[nCntBlock].nCounterState--;
				if (g_aBlock[nCntBlock].nCounterState >= 0)
				{
					g_aBlock[nCntBlock].pos.y = g_aBlock[nCntBlock].pos.y - 1.0f;
				}
				else
				{//���̈ʒu�ɖ߂�
					g_aBlock[nCntBlock].pos.y = g_aBlock[nCntBlock].pos.y + 10.0f;
					g_aBlock[nCntBlock].state = BLOCKSTATE_NORMAL;
				}
				break;
			}

			//�ʒu���X�V
			g_aBlock[nCntBlock].pos.x += g_aBlock[nCntBlock].move.x;
			g_aBlock[nCntBlock].pos.y += g_aBlock[nCntBlock].move.y;
			
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeigth, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeigth, 0.0f);
		
			//�����̔{��
			nWnumber = g_aBlock[nCntBlock].fWidth / BLOCK_WIDTH;
			nHnumber = g_aBlock[nCntBlock].fHeigth / BLOCK_HEIGHT;

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f * nWnumber, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f * nHnumber);
			pVtx[3].tex = D3DXVECTOR2(1.0f * nWnumber, 1.0f * nHnumber);
		}
		pVtx += 4;		//���_�f�[�^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}

//-------------------------------------------
//�u���b�N�̕`�揈��
//-------------------------------------------
void DrawBlock(void)
{
	int nCntBlock;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{//�u���b�N���g�p����Ă���ꍇ
			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_apTextureBlock[g_aBlock[nCntBlock].nType]);
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBlock * 4, 2);
		}
	}
}

//-------------------------------------------
//�u���b�N�̐ݒ菈��
//-------------------------------------------
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeigtht, Block nType,int nLife ,int nNumber)
{	
	int nCntBlock;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{//�u���b�N���g�p����Ă��Ȃ��ꍇ
			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].move = move;
			g_aBlock[nCntBlock].fWidth = fWidth;
			g_aBlock[nCntBlock].fHeigth = fHeigtht;
			g_aBlock[nCntBlock].nType = nType;
			g_aBlock[nCntBlock].nLife = nLife;
			g_aBlock[nCntBlock].nNumber = nNumber;
			g_aBlock[nCntBlock].bUse = true;	

			break;
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}

//-------------------------------------------
//�u���b�N�̓����蔻��
//-------------------------------------------
bool CollisionBlock(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove, float fWidth, float fHeigtht)
{
	int nCntBlock;

	bool bIsLanding = false;		//���n���Ă��邩�ǂ���

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{//�u���b�N���g���Ă���Ƃ�
			if (pPos->x + (fWidth / 2) >= g_aBlock[nCntBlock].pos.x &&
				pPos->x - (fWidth / 2) <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth)
			{//�����̓����蔻��
				if (pPosOld->y <= g_aBlock[nCntBlock].pos.y&&
					pPos->y >= g_aBlock[nCntBlock].pos.y)
				{//��̓����蔻��
					bIsLanding = true;
					pPos->y = g_aBlock[nCntBlock].pos.y;
					pMove->y = 0.0f;
					//�ړ��ʂ̍X�V
					pPos->x += g_aBlock[nCntBlock].move.x;
					//pPos->y += g_aBlock[nCntBlock].move.y;
				}
				else if (pPosOld->y - fHeigtht >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeigth &&
					pPos->y - fHeigtht <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeigth)
				{//���̓����蔻��
					pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeigth + fHeigtht;
					pMove->y = 0.0f;
					QuestionBlock(nCntBlock);
				}
			}
			if (pPos->y - fHeigtht <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeigth &&
				pPos->y > g_aBlock[nCntBlock].pos.y )
			{//�����̓����蔻��
				if (pPosOld->x - (fWidth / 2) >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth - g_aBlock[nCntBlock].move.x &&
					pPos->x - (fWidth / 2) <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth  - g_aBlock[nCntBlock].move.x)
				{//���̓����蔻��
					pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + (fWidth / 2) - g_aBlock[nCntBlock].move.x;
					pMove->x = 0.0f;
				}
				else if (pPosOld->x + (fWidth / 2) <= g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].move.x &&
					pPos->x + (fWidth / 2) >= g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].move.x )
				{//�E�̓����蔻��
					pPos->x = g_aBlock[nCntBlock].pos.x - (fWidth / 2) + g_aBlock[nCntBlock].move.x ;
					pMove->x = 0.0f;
				}
			}
		}
	}

	return bIsLanding;
}

//-------------------------------------------
//�n�e�i�u���b�N�̏���
//-------------------------------------------
void QuestionBlock(int nCntBlock)
{
	if (g_aBlock[nCntBlock].nType == BLOCK_QUESTION)
	{
		if (g_aBlock[nCntBlock].nLife != 0)
		{
			PlaySound(SOUND_LABEL_SE_BLOCK);

			//�u���b�N�̏�ɃA�C�e���𐶐�����
			g_aBlock[nCntBlock].nLife = 0;
			HitBlock(nCntBlock);
			if(g_aBlock[nCntBlock].nNumber == 1)
			{//�G
			SetEnemy(D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y - BLOCK_HEIGHT, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), ENEMY_WOLF, 2,0);
			}
			else if (g_aBlock[nCntBlock].nNumber == 2)
			{//�񕜖�
				SetItem(D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y - BLOCK_HEIGHT, 0.0f), ITEM_POTION);
			}
			else
			{//��
				SetItem(D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y - BLOCK_HEIGHT, 0.0f), ITEM_CANDY);
			}
		}
	}
}

//-------------------------------------------
//�u���b�N�̃q�b�g����
//-------------------------------------------
void HitBlock(int nCntBlock)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * nCntBlock;

	if (g_aBlock[nCntBlock].bUse == true)
	{
		if (g_aBlock[nCntBlock].nLife <= 0)
		{
			g_aBlock[nCntBlock].state = BLOCKSTATE_DAMAGE;
			g_aBlock[nCntBlock].nCounterState = 10;

			//���_�J���[�̕ύX
			pVtx[0].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}

//-------------------------------------------
//�u���b�N�̎擾
//-------------------------------------------
BLOCK * GetBlock(void)
{
	return &g_aBlock[0];
}
//-------------------------------------------
//�u���b�N�̏�ԊǗ�����
//-------------------------------------------
//void StateBlock(int nCntBlock)
//{
//	//���_���ւ̃|�C���^
//	VERTEX_2D *pVtx;
//
//	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);
//
//	//�u���b�N�̈ʒu���̍X�V
//	switch (g_aBlock[nCntBlock].state)
//	{
//	case BLOCKSTATE_NORMAL:
//		break;
//	case BLOCKSTATE_DAMAGE:
//		//���_�J���[�̐ݒ�
//		pVtx[0].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
//		pVtx[1].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
//		pVtx[2].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
//		pVtx[3].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
//
//			g_aBlock[nCntBlock].nCounterState--;
//			if(g_aBlock[nCntBlock].nCounterState >= 0)
//			{
//				g_aBlock[nCntBlock].pos.y = g_aBlock[nCntBlock].pos.y - 1.0f;
//			}
//			else
//			{//���̈ʒu�ɖ߂�
//				g_aBlock[nCntBlock].pos.y = g_aBlock[nCntBlock].pos.y + 10.0f;
//				g_aBlock[nCntBlock].state = BLOCKSTATE_NORMAL;
//			}
//		break;
//	}
//	//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuffBlock->Unlock();
//}