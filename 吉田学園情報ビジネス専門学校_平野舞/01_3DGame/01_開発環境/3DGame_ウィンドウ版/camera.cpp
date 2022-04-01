//-------------------------------------------
//�J��������[camera.cpp]
//Author:���앑
//
//-------------------------------------------

//�C���N���[�h�t�@�C��
#include "camera.h"
#include "fade.h"
#include "map.h"
#include "stage.h"

//�O���[�o���ϐ��錾
Camera g_camera[2];			//�J�������

//-------------------------------------------
//����������
//-------------------------------------------
void InitCamera(void)
{
		//--------------------------�J����1--------------------------------------------------------
		//�J�������̏�����
		g_camera[0].posV = D3DXVECTOR3(0.0f, 400.0f, -300.0f);		//���_�̏�����
		g_camera[0].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�����_�̏�����
		g_camera[0].posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړI�̎��_�̏�����
		g_camera[0].posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړI�̒����_�̏�����
		g_camera[0].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			//������̏�����
		g_camera[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//����(�p�x)�̏�����
		g_camera[0].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړI�̌���(�p�x)�̏�����
		g_camera[0].fDistance = sqrtf((g_camera[0].posV.x - g_camera[0].posR.x) * (g_camera[0].posV.x - g_camera[0].posR.x) +
			(g_camera[0].posV.z - g_camera[0].posR.z) * (g_camera[0].posV.z - g_camera[0].posR.z));			//�����̏�����

		//�r���[�|�[�g�\���̕ۑ�
		g_camera[0].viewport.X = 0.0f;					//�r���[�|�[�g�̊J�n�ʒu(X)
		g_camera[0].viewport.Y = 0.0f;					//�r���[�|�[�g�̊J�n�ʒu(Y)
		g_camera[0].viewport.Width = SCREEN_WIDTH;		//�r���[�|�[�g�̕�
		g_camera[0].viewport.Height = SCREEN_HEIGHT;	//�r���[�|�[�g�̍���
		g_camera[0].viewport.MinZ = 0.0f;				//�r���[�|�[�g�̍ŏ��T�C�Y
		g_camera[0].viewport.MaxZ = 1.0f;				//�r���[�|�[�g�̍ő�T�C�Y

		//--------------------------�J����2--------------------------------------------------------
			//�J�������̏�����
		g_camera[1].posV = D3DXVECTOR3(0.0f, 2800.0f, 0.0f);		//���_�̏�����
		g_camera[1].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�����_�̏�����
		g_camera[1].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			//������̏�����
		g_camera[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//����(�p�x)�̏�����
		g_camera[1].fDistance = sqrtf((g_camera[1].posV.x - g_camera[1].posR.x) * (g_camera[1].posV.x - g_camera[1].posR.x) +
			(g_camera[1].posV.z - g_camera[1].posR.z) * (g_camera[1].posV.z - g_camera[1].posR.z));			//�����̏�����

	//�r���[�|�[�g�\���̕ۑ�
		g_camera[1].viewport.X = 0.0f;					//�r���[�|�[�g�̊J�n�ʒu(X)
		g_camera[1].viewport.Y = 0.0f;					//�r���[�|�[�g�̊J�n�ʒu(Y)
		g_camera[1].viewport.Width = 250.0f;			//�r���[�|�[�g�̕�
		g_camera[1].viewport.Height = 250.0f;			//�r���[�|�[�g�̍���
		g_camera[1].viewport.MinZ = 0.0f;				//�r���[�|�[�g�̍ŏ��T�C�Y
		g_camera[1].viewport.MaxZ = 1.0f;				//�r���[�|�[�g�̍ő�T�C�Y
}

//-------------------------------------------
//�I������
//-------------------------------------------
void UninitCamera(void)
{
	//���ɂȂ�
}

//-------------------------------------------
//�X�V����
//-------------------------------------------
void UpdateCamera(void)
{
	//�J�����̐���
	//TurningCamera();

	//�J�����̈ړ�
	//MoveCamera();

	//�J�����̒Ǐ]
	//�v���C���[���̎擾
	Player * pPlayer = GetPlayer();

	//�����_
	g_camera[0].posRDest.x = pPlayer->pos.x + sinf(pPlayer->rot.y + D3DX_PI) * 30.0f;
	g_camera[0].posRDest.z = pPlayer->pos.z + cosf(pPlayer->rot.y + D3DX_PI) * 30.0f;

	//���_
	g_camera[0].posVDest.x = pPlayer->pos.x - sinf(g_camera[0].rot.y) * 300.0f;
	g_camera[0].posVDest.z = pPlayer->pos.z - cosf(g_camera[0].rot.y) * 300.0f;

	//���
	g_camera[0].posR.x += (g_camera[0].posRDest.x - g_camera[0].posR.x) * 0.07f;
	g_camera[0].posR.z += (g_camera[0].posRDest.z - g_camera[0].posR.z) * 0.07f;
	g_camera[0].posV.x += (g_camera[0].posVDest.x - g_camera[0].posV.x) * 0.07f;
	g_camera[0].posV.z += (g_camera[0].posVDest.z - g_camera[0].posV.z) * 0.07f;

	//�ړ��X�V
	g_camera[0].posR.x = g_camera[0].posV.x + sinf(g_camera[0].rot.y) * g_camera[0].fDistance;
	g_camera[0].posR.z = g_camera[0].posV.z + cosf(g_camera[0].rot.y) * g_camera[0].fDistance;

	//x�̊p�x���͈͂��璴�����ꍇ(�p�x�̐��K��)
	if (g_camera[0].rot.x < -D3DX_PI)
	{//�p�x��-3.14�����������Ȃ����ꍇ
		g_camera[0].rot.x += D3DX_PI * 2;
	}
	else if (g_camera[0].rot.x > D3DX_PI)
	{//�p�x��3.14�����傫���Ȃ����ꍇ
		g_camera[0].rot.x -= D3DX_PI * 2;
	}

	//y�̊p�x���͈͂��璴�����ꍇ(�p�x�̐��K��)
	if (g_camera[0].rot.y < -D3DX_PI)
	{//�p�x��-3.14�����������Ȃ����ꍇ
		g_camera[0].rot.y += D3DX_PI * 2;
	}
	else if (g_camera[0].rot.y > D3DX_PI)
	{//�p�x��3.14�����傫���Ȃ����ꍇ
		g_camera[0].rot.y -= D3DX_PI * 2;
	}

	//z�̊p�x���͈͂��璴�����ꍇ(�p�x�̐��K��)
	if (g_camera[0].rot.z < -D3DX_PI)
	{//�p�x��-3.14�����������Ȃ����ꍇ
		g_camera[0].rot.z += D3DX_PI * 2;
	}
	else if (g_camera[0].rot.z > D3DX_PI)
	{//�p�x��3.14�����傫���Ȃ����ꍇ
		g_camera[0].rot.z -= D3DX_PI * 2;
	}

	//-------------------2�ڂ̃J����---------------------------
	//�����_
	g_camera[1].posRDest.x = 750.5f + sinf(D3DX_PI) * -150.0f;
	g_camera[1].posRDest.z = 350.5f + cosf(D3DX_PI) * -150.0f;

	//���_
	g_camera[1].posVDest.x = 750.5f - sinf(g_camera[1].rot.y) * 250.0f;
	g_camera[1].posVDest.z = 350.5f - cosf(g_camera[1].rot.y) * 250.0f;

	//���
	g_camera[1].posR.x += (g_camera[1].posRDest.x - g_camera[1].posR.x) * 0.1f;
	g_camera[1].posR.z += (g_camera[1].posRDest.z - g_camera[1].posR.z) * 0.1f;
	g_camera[1].posV.x += (g_camera[1].posVDest.x - g_camera[1].posV.x) * 0.1f;
	g_camera[1].posV.z += (g_camera[1].posVDest.z - g_camera[1].posV.z) * 0.1f;
}

//-------------------------------------------
//�ݒ菈��
//-------------------------------------------
void SetCamera(int nCntCamere)
{
	//�f�o�C�X�̎擾nm
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera[nCntCamere].mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera[nCntCamere].mtxView, &g_camera[nCntCamere].posV, &g_camera[nCntCamere].posR, &g_camera[nCntCamere].vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera[nCntCamere].mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera[nCntCamere].mtxProjection);

	switch (nCntCamere)
	{
	case 0:		//nCntCamera��0��������
		//�v���W�F�N�V�����}�g���b�N�X�̍쐬
		D3DXMatrixPerspectiveFovLH(&g_camera[0].mtxProjection,
			D3DXToRadian(45.0f),								//����p
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,			//�A�X�y�N�g��
			10.0f,												//�j�A
			1000.0f);											//�t�@�[
		break;
	case 1:		//nCntCamera��1��������
		//�v���W�F�N�V�����}�g���b�N�X�̍쐬
		D3DXMatrixPerspectiveFovLH(&g_camera[1].mtxProjection,
			D3DXToRadian(20.0f),								//����p
			(float)250.0f / (float)250.0f,						//�A�X�y�N�g��
			0.0f,												//�j�A
			1280.0f);											//�t�@�[
		break;
	default:
		break;
	}

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera[nCntCamere].mtxProjection);
}

//-------------------------------------------
//�J�����̐��񏈗�
//-------------------------------------------
void TurningCamera(void)
{
		//���_�̐���
		if (GetKeyboardPress(DIK_Z) == true)
		{//Z�L�[���������ꍇ�A���v���
			g_camera[0].rot.y += CAMERA_ANGLE;
			g_camera[0].posV.x = g_camera[0].posR.x - sinf(g_camera[0].rot.y) * g_camera[0].fDistance;
			g_camera[0].posV.z = g_camera[0].posR.z - cosf(g_camera[0].rot.y) * g_camera[0].fDistance;
		}
		else if (GetKeyboardPress(DIK_C) == true)
		{//C�L�[���������ꍇ�A�����v���
			g_camera[0].rot.y -= CAMERA_ANGLE;
			g_camera[0].posV.x = g_camera[0].posR.x - sinf(g_camera[0].rot.y) * g_camera[0].fDistance;
			g_camera[0].posV.z = g_camera[0].posR.z - cosf(g_camera[0].rot.y) * g_camera[0].fDistance;
		}
}

//-------------------------------------------
//�J�����̈ړ�����
//-------------------------------------------
void MoveCamera(void)
{
	if (GetKeyboardPress(DIK_A) == true)
	{//A�L�[���������獶�ɐi��
		g_camera[1].posV.x -= sinf(g_camera[1].rot.y + (D3DX_PI / 2.0f)) * CAMERA_DIS;
		g_camera[1].posV.z -= cosf(g_camera[1].rot.y + (D3DX_PI / 2.0f)) * CAMERA_DIS;

		if (GetKeyboardPress(DIK_W) == true)
		{//W�L�[���������獶�O�ɐi��
			g_camera[1].posV.x -= sinf(g_camera[1].rot.y + D3DX_PI) * CAMERA_DIS;
			g_camera[1].posV.z -= cosf(g_camera[1].rot.y + D3DX_PI) * CAMERA_DIS;
		}

		else if (GetKeyboardPress(DIK_S) == true)
		{//S�L�[���������獶���ɐi��
			g_camera[1].posV.x += sinf(g_camera[1].rot.y + D3DX_PI) * CAMERA_DIS;
			g_camera[1].posV.z += cosf(g_camera[1].rot.y + D3DX_PI) * CAMERA_DIS;
		}
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{//D�L�[����������E�ɐi��
		g_camera[1].posV.x += sinf(g_camera[1].rot.y + (D3DX_PI / 2.0f)) * CAMERA_DIS;
		g_camera[1].posV.z += cosf(g_camera[1].rot.y + (D3DX_PI / 2.0f)) * CAMERA_DIS;

		if (GetKeyboardPress(DIK_W) == true)
		{//W�L�[����������E�O�ɐi��
			g_camera[1].posV.x -= sinf(g_camera[1].rot.y + D3DX_PI) * CAMERA_DIS;
			g_camera[1].posV.z -= cosf(g_camera[1].rot.y + D3DX_PI) * CAMERA_DIS;
		}

		else if (GetKeyboardPress(DIK_S) == true)
		{//S�L�[����������E���ɐi��
			g_camera[1].posV.x += sinf(g_camera[1].rot.y + D3DX_PI) * CAMERA_DIS;
			g_camera[1].posV.z += cosf(g_camera[1].rot.y + D3DX_PI) * CAMERA_DIS;
		}
	}
	else if (GetKeyboardPress(DIK_W) == true)
	{//W�L�[����������O�ɐi��
		g_camera[1].posV.x -= sinf(g_camera[1].rot.y + D3DX_PI) * CAMERA_DIS;
		g_camera[1].posV.z -= cosf(g_camera[1].rot.y + D3DX_PI) * CAMERA_DIS;

		if (GetKeyboardPress(DIK_A) == true)
		{//A�L�[���������獶�O�ɐi��
			g_camera[1].posV.x -= sinf(g_camera[1].rot.y + (D3DX_PI / 2.0f)) * CAMERA_DIS;
			g_camera[1].posV.z -= cosf(g_camera[1].rot.y + (D3DX_PI / 2.0f)) * CAMERA_DIS;
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//D�L�[����������E�O�ɐi��
			g_camera[1].posV.x += sinf(g_camera[1].rot.y + (D3DX_PI / 2.0f)) * CAMERA_DIS;
			g_camera[1].posV.z += cosf(g_camera[1].rot.y + (D3DX_PI / 2.0f)) * CAMERA_DIS;
		}
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{//S�L�[������������ɐi��
		g_camera[1].posV.x += sinf(g_camera[1].rot.y + D3DX_PI) * CAMERA_DIS;
		g_camera[1].posV.z += cosf(g_camera[1].rot.y + D3DX_PI) * CAMERA_DIS;

		if (GetKeyboardPress(DIK_A) == true)
		{//A�L�[���������獶���ɐi��
			g_camera[1].posV.x -= sinf(g_camera[1].rot.y + (D3DX_PI / 2.0f)) * CAMERA_DIS;
			g_camera[1].posV.z -= cosf(g_camera[1].rot.y + (D3DX_PI / 2.0f)) * CAMERA_DIS;
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//D�L�[����������E���ɐi��
			g_camera[1].posV.x += sinf(g_camera[1].rot.y + (D3DX_PI / 2.0f)) * CAMERA_DIS;
			g_camera[1].posV.z += cosf(g_camera[1].rot.y + (D3DX_PI / 2.0f)) * CAMERA_DIS;
		}
	}
	//�ړ��X�V
	//g_camera[1].posR.x = g_camera[1].posV.x + sinf(g_camera[1].rot.y) * g_camera[1].fDistance;
	//g_camera[1].posR.z = g_camera[1].posV.z + cosf(g_camera[1].rot.y) * g_camera[1].fDistance;
}

//-------------------------------------------
//�J�����̎擾����
//-------------------------------------------
Camera * GetCamera(void)
{
	return &g_camera[0];
}