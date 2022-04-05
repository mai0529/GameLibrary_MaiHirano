//-------------------------------------------
//
//�v���C���[����[player.cpp]
//Author:���앑
//
//-------------------------------------------

//�C���N���[�h�t�@�C��
#include "player.h"
#include "controller.h"

//�O���[�o���錾
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;				//�e�N�X�`���|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Player g_player;										//�v���C���[�̏��
bool g_bPlayerFade;										//�t�F�[�h���Ă��邩�ǂ���						

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
		"data/TEXTURE/player004.png",
		&g_pTexturePlayer);

	g_player.pos = D3DXVECTOR3(100.0f, 650.0f, 0.0f);		//�ʒu�̏�����
	g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�O�ʒu���̏�����
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړ��ʂ̏�����
	g_player.nCounterAnim = 0;								//�J�E���^�[�̏�����
	g_player.nPatternAnim = 0;								//�p�^�[���ԍ��̏�����
	g_player.nDirectionMove = 0;							//�����̏�����
	g_player.bIsJumping = false;							//�W�����v���̏�����
	g_player.state = PLAYERSTATE_APPEAR;					//�����\���̏�����
	g_player.nCounterState = 100;							//��ԊǗ��J�E���^�[�̏�����
	g_player.nLife = 3;										//�����̏�����
	g_player.bDisp = true;									//�\������
	g_bPlayerFade = false;									//�t�F�[�h���Ă��Ȃ�

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
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - (PLAYER_WIDTH / 2), g_player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + (PLAYER_WIDTH / 2), g_player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - (PLAYER_WIDTH / 2), g_player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + (PLAYER_WIDTH / 2), g_player.pos.y, 0.0f);

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
	pVtx[0].tex = D3DXVECTOR2((1.0f / PLAYERTEX_U) , (1.0f / PLAYERTEX_V));
	pVtx[1].tex = D3DXVECTOR2((1.0f / PLAYERTEX_U) , (1.0f / PLAYERTEX_V));
	pVtx[2].tex = D3DXVECTOR2((1.0f / PLAYERTEX_U) , (1.0f / PLAYERTEX_V));
	pVtx[3].tex = D3DXVECTOR2((1.0f / PLAYERTEX_U) , (1.0f / PLAYERTEX_V));

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

	//�v���C���[�̏��
	StatePlayer();

	//�O��̈ʒu���X�V
	g_player.posOld = g_player.pos;

	//�e�N�X�`�����W�̍X�V
	pVtx[0].tex = D3DXVECTOR2((1.0f / PLAYERTEX_U) * g_player.nPatternAnim, (1.0f / PLAYERTEX_V) * g_player.nDirectionMove);
	pVtx[1].tex = D3DXVECTOR2((1.0f / PLAYERTEX_U) * (g_player.nPatternAnim + 1), (1.0f / PLAYERTEX_V) * g_player.nDirectionMove);
	pVtx[2].tex = D3DXVECTOR2((1.0f / PLAYERTEX_U) * g_player.nPatternAnim, (1.0f / PLAYERTEX_V) * (g_player.nDirectionMove + 1));
	pVtx[3].tex = D3DXVECTOR2((1.0f / PLAYERTEX_U) * (g_player.nPatternAnim + 1), (1.0f / PLAYERTEX_V) *(g_player.nDirectionMove + 1));

	//�d��
	g_player.move.y += PLAYER_G;

	//�ʒu���X�V
	g_player.pos += g_player.move;

	//�ړ��ʂ��X�V(����������)
	g_player.move.x += (0.0f - g_player.move.x) * 0.5f;

	//�ړ��ƃe�N�X�`��
	MovePlayer();

	//�u���b�N�Ƃ̓����蔻��
	g_player.bIsJumping = !CollisionBlock(&g_player.pos, &g_player.posOld, &g_player.move, (PLAYER_WIDTH / 2), PLAYER_HEIGHT);

	//�G�Ƃ̓����蔻��
	CollisionEnemy(&g_player.pos, &g_player.posOld, &g_player.move, (PLAYER_WIDTH / 2.0f), (PLAYER_HEIGHT / 1.3f));

	//�X�N���[������
	Scroll();

	//�u���b�N�Ƃ̓����蔻��
	g_player.bIsJumping = !CollisionBlock(&g_player.pos, &g_player.posOld, &g_player.move, (PLAYER_WIDTH / 2), PLAYER_HEIGHT);

	//�W�����v�ړ�
	Jumping();

	//�G�Ƃ̓����蔻��
	CollisionEnemy(&g_player.pos, &g_player.posOld, &g_player.move, (PLAYER_WIDTH / 2.0f), (PLAYER_HEIGHT / 1.3f));

	//�A�C�e���Ƃ̓����蔻��
	CollisionItem(&g_player.pos, (PLAYER_WIDTH / 3), PLAYER_HEIGHT);

	//��Ƃ̓����蔻��
	CollisionGoal(&g_player.pos, (PLAYER_WIDTH / 3), PLAYER_HEIGHT);

	//��ʊO����
	OffScreen();

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - (PLAYER_WIDTH / 2), g_player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + (PLAYER_WIDTH / 2), g_player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - (PLAYER_WIDTH / 2), g_player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + (PLAYER_WIDTH / 2), g_player.pos.y, 0.0f);

	if (g_player.pos.y >= SCREEN_HEIGHT && !g_bPlayerFade)
	{//��ʊO�ɂȂ�����
	 //���[�h�ݒ�
			PlaySound(SOUND_LABEL_SE_FALL);		//SE�̍Đ�
			SetFade(MODE_GAMEOVER);				//�Q�[���I�[�o�[���
			g_bPlayerFade = true;				//�t�F�[�h���Ă���
	}

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

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0,g_pTexturePlayer);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//-------------------------------------------
//�v���C���[�̏�ԊǗ�����
//-------------------------------------------
void StatePlayer(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_player.state)
	{
	case PLAYERSTATE_APPEAR:		//�o��
		g_player.nCounterState--;
		if (0 == g_player.nCounterState % 20)
		{
			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		if (10 == g_player.nCounterState % 20)
		{
			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
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
	case PLAYERSTATE_NORMAL:		//�ʏ�
		break;
	case PLAYERSTATE_DAMAGE:		//�_���[�W���󂯂��Ƃ�
		g_player.nCounterState--;
		//�_��
		if (0 == g_player.nCounterState % 20)
		{
			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		}
		if (1 == g_player.nCounterState % 20)
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
	case PLAYERSTATE_DEATH:			//���񂾂Ƃ�
		g_player.nCounterState--;
		if (g_player.nCounterState <= 0)
		{
			//���[�h�ݒ�(�Q�[����ʂɈڍs)
			SetFade(MODE_GAMECLEAR);
			return;
		}
		break;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}

//-------------------------------------------
//�v���C���[�̃q�b�g����
//-------------------------------------------
void HitPlayer(int nDamage)
{
	Life *pLife = GetMaxLife();

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	if (g_player.bDisp == true)
	{
		PlaySound(SOUND_LABEL_SE_DAMAGE);
		for (int nCount = MAX_LIFE - 1; nCount > 0; nCount--, pLife--)
		{
			if (pLife->bUse == true)
			{
				pLife->bUse = false;
				break;
			}
		}
		g_player.nLife -= nDamage;
		if (g_player.nLife <= 0)
		{//���C�t��0�ɂȂ�����a
			//�����̏���
			//SetExplosion(g_player.pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			g_player.bDisp = false;
			//���[�h�ݒ�(�Q�[����ʂɈڍs)
			SetFade(MODE_GAMEOVER);
		}
		else
		{
			g_player.state = PLAYERSTATE_DAMAGE;
			g_player.nCounterState = 100;
			//���_�J���[�̕ύX
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}

//-------------------------------------------
//�v���C���[�̎擾
//-------------------------------------------
Player * GetPlayer(void)
{
	return &g_player;
}

//-------------------------------------------
//�v���C���[�̈ړ�����
//-------------------------------------------
void MovePlayer(void)
{
	if (GetKeyboardPress(DIK_A) == true || GetControllerPress(0, XINPUT_GAMEPAD_DPAD_LEFT)
		|| GetControllerStickPress(0, STICK_LEFT))
	{//A�L�[�������ꂽ�A�E�ړ�
		g_player.nDirectionMove = 1;		//����
		//g_player.pos.x -= PLAYER_DIS;
		g_player.move.x += sinf(-D3DX_PI / 2.0f) * PLAYER_DIS;
		g_player.move.y += cosf(-D3DX_PI / 2.0f) * PLAYER_DIS;
	}
	else if (GetKeyboardPress(DIK_D) == true || GetControllerPress(0, XINPUT_GAMEPAD_DPAD_RIGHT)
		|| GetControllerStickPress(0, STICK_RIGHT))
	{//D�L�[�������ꂽ�A���ړ�
		g_player.nDirectionMove = 0;		//����
		//g_player.pos.x += PLAYER_DIS;
		g_player.move.x += sinf(D3DX_PI / 2.0f) * PLAYER_DIS;
		g_player.move.y += cosf(D3DX_PI / 2.0f) * PLAYER_DIS;
	}
	//�e����
	if (GetKeyboardTrigger(DIK_RETURN) == true || GetControllerPressTrigger(0, XINPUT_GAMEPAD_A))
	{//�e�̔���
		if (g_player.nDirectionMove == 0)
		{//D�L�[�����Ă�Ƃ�
			SetBullet(D3DXVECTOR3(g_player.pos.x, g_player.pos.y - (PLAYER_HEIGHT / 2), 0.0f), D3DXVECTOR3(10.0f, 0.0f, 0.0f), BULLETTYPE_PLAYER);
		}
		else if (g_player.nDirectionMove == 1)
		{//A�L�[�����Ă�Ƃ�
			SetBullet(D3DXVECTOR3(g_player.pos.x, g_player.pos.y - (PLAYER_HEIGHT / 2), 0.0f), D3DXVECTOR3(-10.0f, 0.0f, 0.0f), BULLETTYPE_PLAYER);
		}
	}
}

//-------------------------------------------
//�W�����v����
//-------------------------------------------
void Jumping(void)
{
	//�W�����v
	if (GetKeyboardTrigger(DIK_SPACE) == true || GetControllerPressTrigger(0, XINPUT_GAMEPAD_B))
	{//SPACE�L�[�������ꂽ
		if (g_player.bIsJumping == false)
		{
			PlaySound(SOUND_LABEL_SE_JUMP);
			g_player.bIsJumping = true;
			g_player.move.y -= PLAYER_JUMP;
			if (g_player.nPatternAnim == 0 || g_player.nPatternAnim == 2)
			{//�W�����v���̃|�[�Y
				g_player.nPatternAnim += 1;
			}
		}
	}

	if (g_player.bIsJumping != true)
	{//�W�����v���Ă��Ȃ�������
		if (g_player.move.x >= PLAYER_MOVE || g_player.move.x <= -PLAYER_MOVE)
		{//�ړ����Ă�����
			g_player.nCounterAnim++;

			//�J�E���^�[��10�ɂȂ�����
			if (g_player.nCounterAnim % 10 == 0)
			{//�p�^�[�����𑝂₷
				g_player.nPatternAnim++;
			}
			if (g_player.nPatternAnim == 4)
			{//�p�^�[������߂�
				g_player.nPatternAnim = 0;
			}
		}
		else
		{//�ړ���~
			if (g_player.nPatternAnim == 1 || g_player.nPatternAnim == 3)
			{//�p�^�[��1,3��������
				g_player.nPatternAnim += 1;

				if (g_player.nPatternAnim == 4)
				{//�p�^�[������߂�
					g_player.nPatternAnim = 0;
				}
			}
		}
	}
}

//-------------------------------------------
//�v���C���[�̉�ʊO����
//-------------------------------------------
void OffScreen(void)
{
	if (g_player.pos.x + (PLAYER_WIDTH / 2) > SCREEN_WIDTH)
	{//�E�[
		g_player.pos.x = SCREEN_WIDTH - (PLAYER_WIDTH / 2);

	}
	if (g_player.pos.x - (PLAYER_WIDTH / 2) < 0)
	{//���[
		g_player.pos.x = 0 + (PLAYER_WIDTH / 2);

	}
	if (g_player.pos.y - PLAYER_HEIGHT < 0)
	{//��
		(g_player.pos.y = 0 + PLAYER_HEIGHT);

	}
}

//-------------------------------------------
//�X�N���[������
//-------------------------------------------
void Scroll(void)
{
	//��ʃX�N���[��
	if (g_player.pos.x + (PLAYER_WIDTH / 2) >= SCREEN_WIDTH / 2)
	{//�����i��
		g_player.pos.x = (SCREEN_WIDTH / 2) - (PLAYER_WIDTH / 2);

		if (g_player.move.x > 0.0f)
		{//�v���C���[�̈ړ��ʂ�0�ȏゾ������
			//�u���b�N
			BLOCK *pBlock = GetBlock();
			for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pBlock++)
			{
				pBlock->pos.x -= g_player.move.x;
			}

			//�G
			Enemy *pEnemy = GetEnemy();
			for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
			{
				pEnemy->pos.x -= g_player.move.x;
			}

			//�w�i
			BG *pBG = GetBG();
			for (int nCntBG = 0; nCntBG < NUM_BG; nCntBG++, pBG++)
			{
				pBG->fTexU += g_player.move.x * 0.0001f;
			}

			//�S�[��
			Goal *pGoal = GetGoal();
			pGoal->pos.x -= g_player.move.x;

			//�A�C�e��
			Item *pItem = GetItem();
			for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
			{
				pItem->pos.x -= g_player.move.x;
			}

			Twinkle *pTwinkle = GetTwinkle();
			for (int nCntFlame = 0; nCntFlame < MAX_TWINKLE; nCntFlame++, pTwinkle++)
			{
				pTwinkle->pos.x -= g_player.move.x;
			}
		}
	}
}