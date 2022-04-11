#include "Frame.h"
#include "input.h"

//�}�N����`	
#define MAX_X	(5)	//���̘g��
#define MAX_Y	(5)	//�c�̘g��
#define MAX_FRAME	(MAX_X * MAX_Y)	//�K�v�g��

typedef enum
{
	STATE_OFF = 0,
	STATE_ON
}Frame_State;

typedef enum
{
	TYPE_01 = 0,
	TYPE_02
}Frame_Type;

//
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 size;
	bool bUse;
	Frame_State state;
	Frame_Type type;
}Frame;

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureFrame[2] = {};			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFrame = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Frame g_aFrame[MAX_FRAME];

//----------------------------------------
//  �g�̏������ݒ菈��
//----------------------------------------
void InitFrame(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\waku_001.png",
		&g_pTextureFrame[0]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\waku_002.png",
		&g_pTextureFrame[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_FRAME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFrame,
		NULL);

	//�ʒu�̏�����
	for (int nCnt = 0; nCnt < MAX_FRAME; nCnt++)
	{
		g_aFrame[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aFrame[nCnt].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aFrame[nCnt].bUse = false;
		g_aFrame[nCnt].state = STATE_OFF;
		g_aFrame[nCnt].type = TYPE_01;
	}

	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffFrame->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_FRAME; nCnt++)
	{
		//���_���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aFrame[nCnt].pos.x - g_aFrame[nCnt].size.x, g_aFrame[nCnt].pos.y - g_aFrame[nCnt].size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aFrame[nCnt].pos.x + g_aFrame[nCnt].size.x, g_aFrame[nCnt].pos.y - g_aFrame[nCnt].size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aFrame[nCnt].pos.x - g_aFrame[nCnt].size.x, g_aFrame[nCnt].pos.y + g_aFrame[nCnt].size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aFrame[nCnt].pos.x + g_aFrame[nCnt].size.x, g_aFrame[nCnt].pos.y + g_aFrame[nCnt].size.y, 0.0f);

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

		pVtx += 4;			//���_�f�[�^�̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFrame->Unlock();
}

//----------------------------------------
//  �g�̏I������
//----------------------------------------
void UninitFrame(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (g_pTextureFrame[nCnt] != NULL)
		{
			g_pTextureFrame[nCnt]->Release();
			g_pTextureFrame[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffFrame != NULL)
	{
		g_pVtxBuffFrame->Release();
		g_pVtxBuffFrame = NULL;
	}
}

void SetFrame(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	for (int nCnt = 0; nCnt < MAX_FRAME; nCnt++)
	{
		if (g_aFrame[nCnt].bUse == false)
		{
			g_aFrame[nCnt].pos = pos;
			g_aFrame[nCnt].size = size;
			g_aFrame[nCnt].bUse = true;

			break;
		}
	}
}

//----------------------------------------
//  �g�̔z�u����
//----------------------------------------
void SetFramepos(void)
{
	float SIZE_X = 650.0f / MAX_X;
	float SIZE_Y = 650.0f / MAX_Y;

	for (int nCntY = 0; nCntY < MAX_Y; nCntY++)
	{
		for (int nCntX = 0; nCntX < MAX_X; nCntX++)
		{
			SetFrame(D3DXVECTOR3(350.0f + SIZE_X * nCntX, 100.0f + SIZE_Y * nCntY, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f));
		}
	}
}

//----------------------------------------
//�@�g�̍X�V����
//----------------------------------------
void UpdateFrame(void)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffFrame->Lock(0, 0, (void**)&pVtx, 0);

	SetFramepos();

	for (int nCnt = 0; nCnt < MAX_FRAME; nCnt++)
	{
		if (g_aFrame[nCnt].bUse == true)
		{
			//���_���W�ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aFrame[nCnt].pos.x - g_aFrame[nCnt].size.x, g_aFrame[nCnt].pos.y - g_aFrame[nCnt].size.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aFrame[nCnt].pos.x + g_aFrame[nCnt].size.x, g_aFrame[nCnt].pos.y - g_aFrame[nCnt].size.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aFrame[nCnt].pos.x - g_aFrame[nCnt].size.x, g_aFrame[nCnt].pos.y + g_aFrame[nCnt].size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aFrame[nCnt].pos.x + g_aFrame[nCnt].size.x, g_aFrame[nCnt].pos.y + g_aFrame[nCnt].size.y, 0.0f);

			if (g_aFrame[nCnt].state == STATE_OFF)
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
			else if (g_aFrame[nCnt].state == STATE_ON)
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
			}
		}

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFrame->Unlock();

}

//----------------------------------------
//  �g�̕`�揈��
//----------------------------------------
void DrawFrame(void)
{
	// �f�o�C�X�֌W
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();			//�f�o�C�X�̎擾

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffFrame, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntFrame = 0; nCntFrame < MAX_FRAME; nCntFrame++)
	{
		if (g_aFrame[nCntFrame].bUse == true)
		{//�G���g�p����Ă���
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureFrame[g_aFrame[nCntFrame].type]);

			//�|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntFrame * 4,
				2);
		}
	}
}

//----------------------------------------
//�@�g�̓����蔻��
//----------------------------------------
void CollisionFrame(D3DXVECTOR3 pos, float size)
{
	VERTEX_2D * pVtx;		//���_���ւ̃|�C���^

	//���_�������b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffFrame->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntFrame = 0; nCntFrame < MAX_FRAME; nCntFrame++)
	{
		if (g_aFrame[nCntFrame].bUse == true)
		{
			if (g_aFrame[nCntFrame].pos.x + g_aFrame[nCntFrame].size.x >= pos.x &&
				g_aFrame[nCntFrame].pos.x - g_aFrame[nCntFrame].size.x <= pos.x &&
				g_aFrame[nCntFrame].pos.y - g_aFrame[nCntFrame].size.y <= pos.y &&
				g_aFrame[nCntFrame].pos.y + g_aFrame[nCntFrame].size.y >= pos.y)
			{
				g_aFrame[nCntFrame].state = STATE_ON;
			}
			else
			{
				g_aFrame[nCntFrame].state = STATE_OFF;
			}
		}

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFrame->Unlock();
}

//----------------------------------------
//�@�g�̓����蔻��
//----------------------------------------
void SelectFrame(void)
{
	for (int nCnt = 0; nCnt < MAX_FRAME; nCnt++)
	{
		if (g_aFrame[nCnt].bUse == true)
		{
			if (g_aFrame[nCnt].state == STATE_ON)
			{
				g_aFrame[nCnt].type = TYPE_02;
			}
		}
	}
}
