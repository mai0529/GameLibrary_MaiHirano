//-------------------------------------------
//
//�v���C���[����[player.cpp]
//Author:���앑
//
//-------------------------------------------

//�C���N���[�h�t�@�C��
#include "player.h"
#include "life.h"
#include "obstacle.h"
#include "input.h"
#include "Bullet.h"
#include "sound.h"
#include "explosion.h"
#include "enemy.h"
#include "fade.h"
#include "item.h"
#include "controller.h"

//�O���[�o���錾
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;			//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Player g_player;									//�v���C���[�̏��
bool g_PlayerFade;									//�t�F�[�h���Ă��邩�ǂ���

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
		"data/TEXTURE/player000.png",
		&g_pTexturePlayer);

	g_player.pos = D3DXVECTOR3(200.0f,200.0f, 0.0f);	//�ʒu�̏�����
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ��ʂ̏�����
	g_player.bDisp = true;								//�o����Ԃ̏�����
	g_player.nLife = 5;									//�v���C���[���C�t�̏�����
	g_player.state = PLAYERSTATE_APPEAR;				//�v���C���[��Ԃ̏�����
	g_player.nCounterState = 60;						//�v���C���[�o���J�E���^�[�̏�����
	g_PlayerFade = false;								//�t�F�[�h���Ă��Ȃ�

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
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - (PLAYER_WIDTH / 2.0f), g_player.pos.y - (PLAYER_HEIGHT / 2.0f), g_player.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + (PLAYER_WIDTH / 2.0f), g_player.pos.y - (PLAYER_HEIGHT / 2.0f), g_player.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - (PLAYER_WIDTH / 2.0f), g_player.pos.y + (PLAYER_HEIGHT / 2.0f), g_player.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + (PLAYER_WIDTH / 2.0f), g_player.pos.y + (PLAYER_HEIGHT / 2.0f), g_player.pos.z);

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

	SetLife(D3DXVECTOR3(g_player.pos.x, g_player.pos.y - 85.0f, g_player.pos.z), 5, 5);
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

	//�v���C���[�̏��
	StatePlayer();

	//�v���C���[�̈ړ�����
	MovePlayer();

	//�e�̔���
	if (GetKeyboardTrigger(DIK_SPACE) == true || GetControllerPressTrigger(0, XINPUT_GAMEPAD_A))
	{//SPACE�L�[�������ꂽ   
	 //�e�̐ݒ�
		SetBullet(g_player.pos, D3DXVECTOR3(10.0f, 0.0f, 0.0f), 100,BULLETTYPE_PLAYER);
		//�T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_SHOT);
	}

	//�ʒu���X�V
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;

	//�ړ��ʂ��X�V(����������)
	g_player.move.x += (0.0f - g_player.move.x) * 0.08f;
	g_player.move.y += (0.0f - g_player.move.y) * 0.08f;

	//�G���̎擾
	Enemy *pEnemy = GetEnemy();

	//�G�ƃv���C���[�̓����蔻��
	if (g_player.bDisp == true && g_player.state == PLAYERSTATE_NORMAL)
	{
		for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
		{
			if (pEnemy->bUse == true)
			{//�G���g�p����Ă���
				if (g_player.pos.x + (PLAYER_WIDTH / 2.0f) >= pEnemy->pos.x - ENEMY_WIDTH
					&& g_player.pos.x - (PLAYER_WIDTH / 2.0f) <= pEnemy->pos.x + ENEMY_WIDTH
					&& g_player.pos.y + (PLAYER_HEIGHT / 2.0f) >= pEnemy->pos.y - ENEMY_HEIGHT
					&& g_player.pos.y - (PLAYER_HEIGHT / 2.0f) <= pEnemy->pos.y + ENEMY_HEIGHT)
				{ //�G�̓����蔻��
					HitPlayer(1);
				}
			}
		}
	}

	//��Q�����̎擾
	Obstacle *pObstacle = GetObstacle();

	//��Q���ƃv���C���[�̓����蔻��
	if (g_player.bDisp == true && g_player.state == PLAYERSTATE_NORMAL)
	{
		for (int nCntObs = 0; nCntObs < MAX_OBSTACLE; nCntObs++, pObstacle++)
		{
			if (pObstacle->bUse == true)
			{//�G���g�p����Ă���
				if (g_player.pos.x + (PLAYER_WIDTH / 2.0f) >= pObstacle->pos.x - (OBSTACLE_WIDTH / 2.0f)
					&& g_player.pos.x - (PLAYER_WIDTH / 2.0f) <= pObstacle->pos.x + (OBSTACLE_WIDTH / 2.0f)
					&& g_player.pos.y + (PLAYER_HEIGHT / 2.0f) >= pObstacle->pos.y - (OBSTACLE_HEIGHT / 2.0f)
					&& g_player.pos.y - (PLAYER_HEIGHT / 2.0f) <= pObstacle->pos.y + (OBSTACLE_HEIGHT / 2.0f))
				{ //�G�̓����蔻��
					HitPlayer(1);
				}
			}
		}
	}

	//�A�C�e���̓����蔻��
	CollisionItem(&g_player.pos, PLAYER_WIDTH, PLAYER_HEIGHT);

	//��ʊO����
	Gamengai();

	//���C�t�Q�[�W�̈ʒu�X�V
	SetPositionLife(D3DXVECTOR3(g_player.pos.x, g_player.pos.y - 85.0f, g_player.pos.z));

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH, g_player.pos.y - PLAYER_HEIGHT,0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH, g_player.pos.y - PLAYER_HEIGHT,0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH, g_player.pos.y + PLAYER_HEIGHT,0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH, g_player.pos.y + PLAYER_HEIGHT,0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
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
//�v���C���[�̏�ԊǗ�����
//-------------------------------------------
void StatePlayer(void)
{
	switch (g_player.state)
	{
	case PLAYERSTATE_APPEAR:		//�v���C���[�̏o�����
		g_player.nCounterState--;		//�J�E���^�[�����炷
		FlashPlayer();					//�v���C���[�̓_��
		break;

	case PLAYERSTATE_NORMAL:		//�v���C���[�̒ʏ���
		break;

	case PLAYERSTATE_DAMAGE:		//�v���C���[�̃_���[�W���
		g_player.nCounterState--;		//�J�E���^�[�����炷
		FlashPlayer();					//�v���C���[�̓_��
		break;

	case PLAYERSTATE_DEATH:			//�v���C���[�̎��S���
		g_player.nCounterState--;		//�J�E���^�[�����炷

		if (g_player.nCounterState <= 0 && !g_PlayerFade)
		{//�J�E���^�[��0�ɂȂ�����
			SetFade(MODE_RESULT);		//���[�h�ݒ�(�Q�[����ʂɈڍs)
			g_PlayerFade;				//�t�F�[�h���Ă���
		}
		break;
	}
}

void FlashPlayer(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	if (0 == g_player.nCounterState % 10)
	{
		//���_�J���[�̕ύX
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	}
	if (1 == g_player.nCounterState % 10)
	{
		//���_�J���[�̕ύX
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
	}
	if (g_player.nCounterState <= 0)
	{
		g_player.state = PLAYERSTATE_NORMAL;
		//���_�J���[�̕ύX
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
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
	SubLife(0, nDamage);

	if (g_player.nLife <= 0 && !g_PlayerFade)
	{
		//�����̏���
		SetExplosion(g_player.pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		g_player.bDisp = false;
		//���[�h�ݒ�(�Q�[����ʂɈڍs)
		SetFade(MODE_GAMEOVER);
		g_PlayerFade;
	}
	else
	{
		g_player.state = PLAYERSTATE_DAMAGE;
		g_player.nCounterState = 120;
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
//�v���C���[�̈ړ�����
//-------------------------------------------
void MovePlayer(void)
{
	//�X�e�B�b�N�̏����擾
	D3DXVECTOR3 Stick = GetControllerStickDir(0);

	if (GetKeyboardPress(DIK_A) == true || GetControllerPress(0, XINPUT_GAMEPAD_DPAD_LEFT)
		|| GetControllerStickPress(0, STICK_LEFT))
	{//A�L�[�������ꂽ
		if (GetKeyboardPress(DIK_W) == true)
		{//AW�L�[�������ꍇ
			g_player.move.x += sinf(-D3DX_PI / 4.0f * 3.0f) * 0.8f;
			g_player.move.y += cosf(-D3DX_PI / 4.0f * 3.0f) * 0.8f;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//AS�L�[�������ꍇ
			g_player.move.x += sinf(-D3DX_PI / 4.0f) * 0.8f;
			g_player.move.y += cosf(-D3DX_PI / 4.0f) * 0.8f;
		}
		else
		{//A�L�[�̂�
			g_player.pos.x -= PLAYER_DIS;
			g_player.move.x += sinf(-D3DX_PI / 2.0f) * 0.8f;
			g_player.move.y += cosf(-D3DX_PI / 2.0f) * 0.8f;
		}
	}
	else if (GetKeyboardPress(DIK_D) == true || GetControllerPress(0, XINPUT_GAMEPAD_DPAD_RIGHT)
		|| GetControllerStickPress(0, STICK_RIGHT))
	{//D�L�[�������ꂽ
		if (GetKeyboardPress(DIK_W) == true)
		{//DW�L�[�������ꍇ
			g_player.move.x += sinf(D3DX_PI / 4.0f * 3.0f) * 0.8f;
			g_player.move.y += cosf(D3DX_PI / 4.0f * 3.0f) * 0.8f;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//DS�L�[�������ꍇ
			g_player.move.x += sinf(D3DX_PI / 4.0f) * 0.8f;
			g_player.move.y += cosf(D3DX_PI / 4.0f) * 0.8f;
		}
		else
		{//D�L�[�̂�
			g_player.move.x += sinf(D3DX_PI / 2.0f) * 0.8f;
			g_player.move.y += cosf(D3DX_PI / 2.0f) * 0.8f;
		}
	}
	else if (GetKeyboardPress(DIK_W) == true || GetControllerPress(0, XINPUT_GAMEPAD_DPAD_UP)
		|| GetControllerStickPress(0, STICK_UP))
	{//W�L�[�������ꂽ
			g_player.move.x += sinf(D3DX_PI) * 0.8f;
			g_player.move.y += cosf(D3DX_PI) * 0.8f;
	}
	else if (GetKeyboardPress(DIK_S) == true || GetControllerPress(0, XINPUT_GAMEPAD_DPAD_DOWN)
		|| GetControllerStickPress(0, STICK_DOWN))
	{//S�L�[�������ꂽ
			g_player.move.x += sinf(0.0f) * 0.8f;
			g_player.move.y += cosf(0.0f) * 0.8f;
	}
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

//-------------------------------------------
//�v���C���[�̎擾
//-------------------------------------------
Player * GetPlayer(void)
{
	return &g_player;
}