//-------------------------------------------------
//
//�S�[������[goal.h]
//Author:���앑
//
//-------------------------------------------------

//�C���N���[�h�t�@�C��
#include "goal.h"
#include "fade.h"

//�O���[�o���錾
LPDIRECT3DTEXTURE9 g_pTextureGoal = {};					//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGoal = NULL;			//���_�o�b�t�@�ւ̃|�C���^
Goal g_Goal;											//�S�[���̏��
int g_nContGoal = 0;

//-------------------------------------------
//��̏���������
//-------------------------------------------
void InitGoal(void)
{
	g_nContGoal = 0;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Goal000.png",
		&g_pTextureGoal);
		
	g_Goal.pos = D3DXVECTOR3(9000.0f, 650.0f, 0.0f);	//�ʒu�̏�����
	g_Goal.move = D3DXVECTOR3(-0.0f, 0.0f, 0.0f);		//�ړ��ʂ̏�����
	g_Goal.bUse= true;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGoal,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_Goal.pos.x - (GOAL_WIDTH / 2), g_Goal.pos.y - GOAL_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Goal.pos.x + (GOAL_WIDTH / 2), g_Goal.pos.y - GOAL_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Goal.pos.x - (GOAL_WIDTH / 2), g_Goal.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Goal.pos.x + (GOAL_WIDTH / 2), g_Goal.pos.y, 0.0f);

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
	pVtx[0].tex = D3DXVECTOR2(0.0f ,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f ,0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f ,1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f ,1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGoal->Unlock();
}

//-------------------------------------------
//��̏I������
//-------------------------------------------
void UninitGoal(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureGoal != NULL)
	{
		g_pTextureGoal->Release();
		g_pTextureGoal = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffGoal != NULL)
	{
		g_pVtxBuffGoal->Release();
		g_pVtxBuffGoal = NULL;
	}
}

//-------------------------------------------
//��̍X�V����
//-------------------------------------------
void UpdateGoal(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	//�ʒu���X�V
	g_Goal.pos.x += g_Goal.move.x;
	g_Goal.pos.y += g_Goal.move.y;

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_Goal.pos.x - (GOAL_WIDTH / 2), g_Goal.pos.y - GOAL_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Goal.pos.x + (GOAL_WIDTH / 2), g_Goal.pos.y - GOAL_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Goal.pos.x - (GOAL_WIDTH / 2), g_Goal.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Goal.pos.x + (GOAL_WIDTH / 2), g_Goal.pos.y, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGoal->Unlock();
}

//-------------------------------------------
//��̕`�揈��
//-------------------------------------------
void DrawGoal(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffGoal, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureGoal);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//-------------------------------------------
//��̓����蔻�菈��
//-------------------------------------------
void CollisionGoal(D3DXVECTOR3 * pPos, float fWidth, float fHeigtht)
{
	int nData = GetTime();

	if (g_Goal.bUse == true)
	{//����g���Ă���Ƃ�
		if (pPos->x + (fWidth / 2) >= g_Goal.pos.x - (GOAL_WIDTH / 2)
			&& pPos->x - (fWidth / 2) <= g_Goal.pos.x + (GOAL_WIDTH / 2)
			&& pPos->y >= g_Goal.pos.y - GOAL_HEIGHT
			&& pPos->y - fHeigtht <= g_Goal.pos.y)
		{
			if (g_nContGoal == 0)
			{
				PlaySound(SOUND_LABEL_SE_GOAL);
				AddScore(1700);
				AddScore(nData * 65);
				SetFade(MODE_GAMECLEAR);
				g_nContGoal = 1;
			}
		}
	}
}

//-------------------------------------------
//��̎擾
//-------------------------------------------
Goal * GetGoal(void)
{
	return &g_Goal;
}