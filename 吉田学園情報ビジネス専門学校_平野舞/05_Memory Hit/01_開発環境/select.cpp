#include "select.h"
#include "input.h"
#include "Frame.h"
#include "game.h"
#include "item.h"
#include "sound.h"
#include "particle.h"
#include "effect.h"

//�}�N����`	
#define SIZE_SELECT		(50.0f)	//�I���w�̃T�C�Y
#define SPEED_SELECT	(5.0f)	//�I���w�̃X�s�[�h

//
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
}Select;

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureSelect = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSelect = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Select g_Select;

//----------------------------------------
//  �I���̏������ݒ菈��
//----------------------------------------
void InitSelect(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\select_001.png",
		&g_pTextureSelect);

	//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffSelect,
			NULL);

	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//�ʒu�̏�����
	g_Select.pos = D3DXVECTOR3((SCREEN_WIDTH / 2.0f), (SCREEN_HEIGHT / 2.0f), 0.0f);

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSelect->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_Select.pos.x - SIZE_SELECT, g_Select.pos.y - SIZE_SELECT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Select.pos.x + SIZE_SELECT, g_Select.pos.y - SIZE_SELECT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Select.pos.x - SIZE_SELECT, g_Select.pos.y + SIZE_SELECT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Select.pos.x + SIZE_SELECT, g_Select.pos.y + SIZE_SELECT, 0.0f);

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
	g_pVtxBuffSelect->Unlock();
}

//----------------------------------------
//  �I���̏I������
//----------------------------------------
void UninitSelect(void)
{
	//�w�e�N�X�`���̔j��
	if (g_pTextureSelect != NULL)
	{
		g_pTextureSelect->Release();
		g_pTextureSelect = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSelect != NULL)
	{
		g_pVtxBuffSelect->Release();
		g_pVtxBuffSelect = NULL;
	}
}

//----------------------------------------
//  �I���w�̈ړ�����
//----------------------------------------
void MoveSelect(void)
{
	if (GetKeyboardPress(DIK_A) == true || GetJoypadPress(JOYKEY_LEFT,PLAYER_1) == true)
	{//A�L�[�������ꂽ
		SetEffect(D3DXVECTOR3(g_Select.pos.x, g_Select.pos.y, 0.0f), D3DXCOLOR(0.0f, 0.5f, 0.5f, 1.0f), 40.0f, 10, EFFECT_EFE1, 1);
		if (GetKeyboardPress(DIK_W) == true || GetJoypadPress(JOYKEY_UP, PLAYER_1) == true)
		{//W�L�[�Ɖ�����
			if (g_Select.pos.y >= SIZE_SELECT && g_Select.pos.x >= SIZE_SELECT)
			{
				g_Select.move.x += sinf(-D3DX_PI / 4.0f * 3.0f) * 0.8f;
				g_Select.move.y += cosf(-D3DX_PI / 4.0f * 3.0f) * 0.8f;
			}
		}
		else if (GetKeyboardPress(DIK_S) == true || GetJoypadPress(JOYKEY_DOWN, PLAYER_1) == true)
		{//S�L�[�Ɖ�����
			if (g_Select.pos.y <= SCREEN_HEIGHT - SIZE_SELECT && g_Select.pos.x >= SIZE_SELECT)
			{
				g_Select.move.x += sinf(-D3DX_PI / 4.0f * 1.0f) * 0.8f;
				g_Select.move.y += cosf(-D3DX_PI / 4.0f * 1.0f) * 0.8f;
			}
		}
		else
		{//A�L�[�̂�
			if (g_Select.pos.x >= SIZE_SELECT)
			{
				g_Select.move.x += sinf(-D3DX_PI / 2.0f) * 0.8f;
				g_Select.move.y += cosf(-D3DX_PI / 2.0f) * 0.8f;
			}
		}
	}
	else if (GetKeyboardPress(DIK_D) == true || GetJoypadPress(JOYKEY_RIGHT, PLAYER_1) == true)
	{//D�L�[�������ꂽ
		SetEffect(D3DXVECTOR3(g_Select.pos.x, g_Select.pos.y, 0.0f), D3DXCOLOR(0.0f, 0.5f, 0.5f, 1.0f), 40.0f, 10, EFFECT_EFE1, 1);
		if (GetKeyboardPress(DIK_W) == true || GetJoypadPress(JOYKEY_UP, PLAYER_1) == true)
		{//W�L�[�Ɖ�����
			if (g_Select.pos.x <= SCREEN_WIDTH - SIZE_SELECT && g_Select.pos.y >= SIZE_SELECT)
			{
				g_Select.move.x += sinf(D3DX_PI / 4.0f * 3.0f) * 0.8f;
				g_Select.move.y += cosf(D3DX_PI / 4.0f * 3.0f) * 0.8f;
			}
		}
		else if (GetKeyboardPress(DIK_S) == true || GetJoypadPress(JOYKEY_DOWN, PLAYER_1) == true)
		{//S�L�[�Ɖ�����
			if (g_Select.pos.x <= SCREEN_WIDTH - SIZE_SELECT && g_Select.pos.y <= SCREEN_HEIGHT - SIZE_SELECT)
			{
				g_Select.move.x += sinf(D3DX_PI / 4.0f * 1.0f) * 0.8f;
				g_Select.move.y += cosf(D3DX_PI / 4.0f * 1.0f) * 0.8f;
			}
		}
		else
		{//D�L�[�̂�
			if (g_Select.pos.x <= SCREEN_WIDTH - SIZE_SELECT)
			{
				g_Select.move.x += sinf(D3DX_PI / 2.0f) * 0.8f;
				g_Select.move.y += cosf(D3DX_PI / 2.0f) * 0.8f;
			}
		}
	}
	else if (GetKeyboardPress(DIK_S) == true || GetJoypadPress(JOYKEY_DOWN, PLAYER_1) == true)
	{//S�L�[�������ꂽ
		SetEffect(D3DXVECTOR3(g_Select.pos.x, g_Select.pos.y, 0.0f), D3DXCOLOR(0.0f, 0.5f, 0.5f, 1.0f), 40.0f, 10, EFFECT_EFE1, 1);
		if (g_Select.pos.y <= SCREEN_HEIGHT - SIZE_SELECT)
		{
			g_Select.move.x += sinf(0.0f) * 0.8f;
			g_Select.move.y += cosf(0.0f) * 0.8f;
		}
	}
	else if (GetKeyboardPress(DIK_W) == true || GetJoypadPress(JOYKEY_UP, PLAYER_1) == true)
	{//W�L�[�������ꂽ
		SetEffect(D3DXVECTOR3(g_Select.pos.x, g_Select.pos.y, 0.0f), D3DXCOLOR(0.0f, 0.5f, 0.5f, 1.0f), 40.0f, 10, EFFECT_EFE1, 1);
		if (g_Select.pos.y >= SIZE_SELECT)
		{
			g_Select.move.x += sinf(D3DX_PI) * 0.8f;
			g_Select.move.y += cosf(D3DX_PI) * 0.8f;
		}
	}

	if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A, PLAYER_1) == true)
	{
		SelectFrame();
		SelectItem();

		//�T�E���h�Đ�
		PlaySound(SOUND_LABEL_SE_SELECT1);
	}

	//�ʒu���X�V
	g_Select.pos.x += g_Select.move.x;
	g_Select.pos.y += g_Select.move.y;

	//�ړ��ʂ��X�V(����������)
	g_Select.move.x += (0.0f - g_Select.move.x) * 0.08f;
	g_Select.move.y += (0.0f - g_Select.move.y) * 0.08f;

	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSelect->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_Select.pos.x - SIZE_SELECT, g_Select.pos.y - SIZE_SELECT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Select.pos.x + SIZE_SELECT, g_Select.pos.y - SIZE_SELECT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Select.pos.x - SIZE_SELECT, g_Select.pos.y + SIZE_SELECT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Select.pos.x + SIZE_SELECT, g_Select.pos.y + SIZE_SELECT, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSelect->Unlock();
}

//----------------------------------------
//�@�I���̍X�V����
//----------------------------------------
void UpdateSelect(void)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSelect->Lock(0, 0, (void**)&pVtx, 0);

	//�ړ�����
	MoveSelect();

	//�I�����ƃA�C�e���̓����蔻��
	CollisionFrame(g_Select.pos, SIZE_SELECT);
	CollisionItem(g_Select.pos, SIZE_SELECT);

	//���_���W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_Select.pos.x - SIZE_SELECT, g_Select.pos.y - SIZE_SELECT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Select.pos.x + SIZE_SELECT, g_Select.pos.y - SIZE_SELECT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Select.pos.x - SIZE_SELECT, g_Select.pos.y + SIZE_SELECT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Select.pos.x + SIZE_SELECT, g_Select.pos.y + SIZE_SELECT, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSelect->Unlock();
}

//----------------------------------------
//  �I���̕`�揈��
//----------------------------------------
void DrawSelect(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffSelect, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureSelect);

		//�|���S���̐ݒ�
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

}