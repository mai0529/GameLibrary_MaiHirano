//-------------------------------------------
//
//�v���C���[���[player.cpp]
//Author:���앑
//
//-------------------------------------------
#include "main.h"
#include "player.h"
#include "input.h"
#include "Bullet.h"
#include "sound.h"
#include "explosion.h"
#include "enemy.h"
#include "fade.h"

//�}�N����`
#define PLAYER_WIDTH		(60.0f)		//�v���C���[�̕�
#define PLAYER_HEIGHT		(75.0f)		//�v���C���[�̍���
#define PLAYER_DIS			(4.0f)		//�ړ�����
#define PLAYER_ENEMY		(80.0f)		//�����蔻��

//�O���[�o���錾
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;			//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Player g_player;									//�v���C���[�̏��
D3DXVECTOR3 g_moveBullet;							//�e�̏��

//-------------------------------------------
//�v���C���[�̏���������
//-------------------------------------------
void InitPlayer(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/player001.png",
		&g_pTexturePlayer);

	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu�̏�����
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ��ʂ̏�����
	g_player.bDisp = true;
	g_player.nLife = 5;
	g_player.state = PLAYERSTATE_APPEAR;
	g_player.nCounterState = 60;
	g_moveBullet = D3DXVECTOR3(10.0f, 0.0f, 0.0f);

	//���_�o�b�t�@�̐���
	pDevice -> CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer-> Lock(0, 0, (void**) &pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH, g_player.pos.y - PLAYER_HEIGHT, g_player.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH, g_player.pos.y - PLAYER_HEIGHT, g_player.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH, g_player.pos.y + PLAYER_HEIGHT, g_player.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH, g_player.pos.y + PLAYER_HEIGHT, g_player.pos.z);

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

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}

//-------------------------------------------
//�v���C���[�̏I������
//-------------------------------------------
void UninitPlayer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//-------------------------------------------
//�v���C���[�̍X�V����
//-------------------------------------------
void UpdatePlayer(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_player.state)
	{
	case PLAYERSTATE_APPEAR:
		g_player.nCounterState--;
		if (0 == g_player.nCounterState % 10)
		{
			//���_�J���[
			pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		}
		if (1 == g_player.nCounterState % 10)
		{
			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
		}
		if (g_player.nCounterState <= 0)
		{
			g_player.state = PLAYERSTATE_NORMAL;
			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		break;
	case PLAYERSTATE_NORMAL:
		break;
	case PLAYERSTATE_DAMAGE:
		g_player.nCounterState--;
		if (0 == g_player.nCounterState % 10)
		{
			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		}
		if (1 == g_player.nCounterState % 10)
		{
			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
		}
		if (g_player.nCounterState <= 0)
		{
			g_player.state = PLAYERSTATE_NORMAL;
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		break;
	case PLAYERSTATE_DEATH:
		g_player.nCounterState--;
		if (g_player.nCounterState <= 0)
		{
			//���[�h�ݒ�(�Q�[����ʂɈڍs)
			SetFade(MODE_RESULT);
			return;
		}
		break;
	}

	Enemy *pEnemy = GetEnemy();
	int nCntEnemy;

	if (g_player.bDisp == true && g_player.state == PLAYERSTATE_NORMAL)
	{
		for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
		{
			if (pEnemy->bUse == true)
			{//�G���g�p����Ă���
				if (g_player.pos.x >= pEnemy->pos.x - PLAYER_ENEMY
					&& g_player.pos.x <= pEnemy->pos.x + PLAYER_ENEMY
					&& g_player.pos.y >= pEnemy->pos.y - PLAYER_ENEMY
					&& g_player.pos.y <= pEnemy->pos.y + PLAYER_ENEMY)
				{ //�G�̓����蔻��
					HitPlayer(1);
				}
			}
		}
	}
	
	if (GetKeyboardPress(DIK_A) == true)
	{//A�L�[�������ꂽ
		if (GetKeyboardPress(DIK_W) == true)
		{//AW�L�[�������ꍇ
			/*g_player.pos.x += sinf(-D3DX_PI / 0.75f) * PLAYER_DIS;
			g_player.pos.y += cosf(-D3DX_PI / 0.75f) * PLAYER_DIS;*/
			g_player.move.x += sinf(-D3DX_PI / 4.0f * 3.0f) * 0.8f;
			g_player.move.y += cosf(-D3DX_PI / 4.0f * 3.0f) * 0.8f;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//AS�L�[�������ꍇ
			/*g_player.pos.x += sinf(-D3DX_PI / 4.0f * 3.0f) * PLAYER_DIS;
			g_player.pos.y += cosf(-D3DX_PI / 4.0f * 3.0f) * PLAYER_DIS;*/
			g_player.move.x += sinf(-D3DX_PI / 4.0f * 1.0f) * 0.8f;
			g_player.move.y += cosf(-D3DX_PI / 4.0f * 1.0f) * 0.8f;
		}
		else
		{//A�L�[�̂�
			g_player.pos.x -= PLAYER_DIS;
			g_player.move.x += sinf(-D3DX_PI / 2.0f) * 0.8f;
			g_player.move.y += cosf(-D3DX_PI / 2.0f) * 0.8f;
		}
	}

	else if (GetKeyboardPress(DIK_D) == true)
	{//D�L�[�������ꂽ
		if (GetKeyboardPress(DIK_W) == true)
		{//DW�L�[�������ꍇ
			/*g_player.pos.x += sinf(D3DX_PI * 0.75f) * PLAYER_DIS;
			g_player.pos.y += cosf(D3DX_PI * 0.75f) * PLAYER_DIS;*/
			g_player.move.x += sinf(D3DX_PI / 4.0f * 3.0f) * 0.8f;
			g_player.move.y += cosf(D3DX_PI / 4.0f * 3.0f) * 0.8f;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//DS�L�[�������ꍇ
			/*g_player.pos.x += sinf(D3DX_PI * 0.25f) * PLAYER_DIS;
			g_player.pos.y += cosf(D3DX_PI * 0.25f) * PLAYER_DIS;*/
			g_player.move.x += sinf(D3DX_PI / 4.0f * 1.0f) * 0.8f;
			g_player.move.y += cosf(D3DX_PI / 4.0f * 1.0f) * 0.8f;
		}
		else
		{//D�L�[�̂�
			/*g_player.pos.x += PLAYER_DIS;*/
			g_player.move.x += sinf(D3DX_PI / 2.0f) * 0.8f;
			g_player.move.y += cosf(D3DX_PI / 2.0f) * 0.8f;
		}
	}

	else if (GetKeyboardPress(DIK_W) == true)
	{//W�L�[�������ꂽ
		//if (GetKeyboardPress(DIK_D) == true)
		//{//WD�L�[�������ꍇ
		//	/*g_player.pos.x += sinf(D3DX_PI) * PLAYER_DIS;
		//	g_player.pos.y += cosf(D3DX_PI) * PLAYER_DIS;*/
		//	g_player.move.x += sinf(D3DX_PI / 4.0f * 4.0f) * 0.8f;
		//	g_player.move.y += cosf(D3DX_PI / 4.0f * 4.0f) * 0.8f;
		//}
		//else if (GetKeyboardPress(DIK_A) == true)
		//{//WA�L�[�������ꍇ
		//	/*g_player.pos.x += sinf(-D3DX_PI) * PLAYER_DIS;
		//	g_player.pos.y += cosf(-D3DX_PI) * PLAYER_DIS;*/
		//	g_player.move.x += sinf(D3DX_PI / 2.0f) * 0.8f;
		//	g_player.move.y += cosf(D3DX_PI / 2.0f) * 0.8f;
		//}
		if (GetKeyboardPress(DIK_W) == true)
		{//W�L�[�̂�
			/*g_player.pos.y -= PLAYER_DIS;*/
			g_player.move.x += sinf(D3DX_PI ) * 0.8f;
			g_player.move.y += cosf(D3DX_PI ) * 0.8f;
		}
	}

	else if (GetKeyboardPress(DIK_S) == true)
	{//S�L�[�������ꂽ
		//if (GetKeyboardPress(DIK_D) == true)
		//{//SD�L�[�������ꍇ
		//	g_player.pos.x += sinf(D3DX_PI * 0.5f) * PLAYER_DIS;
		//	g_player.pos.y += cosf(D3DX_PI * 0.5f) * PLAYER_DIS;
		//}
		//else if (GetKeyboardPress(DIK_A) == true)
		//{//SA�L�[�������ꍇ
		//	g_player.pos.x += sinf(-D3DX_PI * 0.5f) * PLAYER_DIS;
		//	g_player.pos.y += cosf(-D3DX_PI * 0.5f) * PLAYER_DIS;
		//}
		if(GetKeyboardPress(DIK_S) == true)
		{//S�L�[�̂�
			g_player.move.x += sinf(0.0f) * 0.8f;
			g_player.move.y += cosf(0.0f) * 0.8f;
		}
	}

	//�ʒu���X�V
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;

	//�ړ��ʂ��X�V(����������)
	g_player.move.x += (0.0f - g_player.move.x) * 0.08f;
	g_player.move.y += (0.0f - g_player.move.y) * 0.08f;

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH, g_player.pos.y - PLAYER_HEIGHT,0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH, g_player.pos.y - PLAYER_HEIGHT,0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH, g_player.pos.y + PLAYER_HEIGHT,0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH, g_player.pos.y + PLAYER_HEIGHT,0.0f);

	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{//SPACE�L�[�������ꂽ   
		//�e�̐ݒ�
		SetBullet(g_player.pos, g_moveBullet,BULLETTYPE_PLAYER);
		//�T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_SHOT);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();

	Gamengai();
}

//-------------------------------------------
//�v���C���[�̕`�揈��
//-------------------------------------------
void DrawPlayer(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	if (g_player.bDisp == true)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���ݒ�
		pDevice->SetTexture(0, g_pTexturePlayer);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//-------------------------------------------
//�v���C���[�̃q�b�g����
//-------------------------------------------
void HitPlayer(int nDamage)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	g_player.nLife -= nDamage;
	if (g_player.nLife <= 0)
	{
		//�����̏���
		SetExplosion(g_player.pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		g_player.bDisp = false;
		//���[�h�ݒ�(�Q�[����ʂɈڍs)
		SetFade(MODE_GAMEOVER);
	}
	else
	{
		g_player.state = PLAYERSTATE_DAMAGE;
		g_player.nCounterState = 60;
		//���_�J���[�̕ύX
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}

//-------------------------------------------
//�v���C���[�̎擾
//-------------------------------------------
void * GetPlayer(void)
{
	return &g_player;
}
 
//-------------------------------------------
//�v���C���[�̉�ʊO����
//-------------------------------------------
void Gamengai(void)
{
	if (g_player.pos.x + PLAYER_WIDTH > SCREEN_WIDTH)
	{//�E�[
		g_player.pos.x = SCREEN_WIDTH - PLAYER_WIDTH;

	}
	if (g_player.pos.x - PLAYER_WIDTH < 0)
	{//���[
		g_player.pos.x = 0 + PLAYER_WIDTH;

	}
	if (g_player.pos.y - PLAYER_HEIGHT < 0)
	{//��
		g_player.pos.y = 0 + PLAYER_HEIGHT;

	}
	if (g_player.pos.y + PLAYER_HEIGHT >  SCREEN_HEIGHT)
	{//��
		g_player.pos.y = SCREEN_HEIGHT - PLAYER_HEIGHT;

	}
}