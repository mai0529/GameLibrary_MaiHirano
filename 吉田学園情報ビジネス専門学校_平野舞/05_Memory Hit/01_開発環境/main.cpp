//===================================================================
//
//		2D�A�N�V����[main.cpp]
//		Author:���c ����
//
//===================================================================

//======================================================
// �C���N���[�h
//======================================================
#include "main.h"
#include "input.h"
#include "bg.h"
#include "sound.h"
#include "title.h"
#include "game.h"
#include "tutorial.h"
#include "fade.h"
#include "result.h"
#include "ranking.h"

//======================================================
// �O���[�o���ϐ�
//======================================================
LPDIRECT3D9	g_pD3D = NULL;						//Directx3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;			//Directx3D�f�o�C�X�ւ̃|�C���^
MODE g_mode = MODE_TITLE;						//���݂̃��[�h

//==================================================
//	���C���֐�
//==================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,							//�E�C���h�E�̃X�^�C��
		WindowProc,							//�E�C���h�E�v���V�[�W��
		0,									//0�ɂ���(�ʏ�͎g�p���Ȃ�)
		0,									//0�ɂ���(�ʏ�͎g�p���Ȃ�)
		hInstance,							//�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),		//�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),			//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),			//�N���C�A���g�̈�̔w�i�F
		NULL,								//���j���[�o�[
		CLASS_NAME,							//�E�C���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION)		//�t�@�C���̃A�C�R��
	};

	HWND hWnd;				//�E�C���h�E�n���h��(���ʎq)
	MSG msg;				//���b�Z�[�W���i�[����ϐ�
	DWORD dwCurrentTime;	//���ݎ���
	DWORD dwExeLastTime;	//�Ō�ɏ�����������

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };			//��ʃT�C�Y�̍\����

	//�E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPED, FALSE);

	//�E�C���h�E�𐶐�
	hWnd = CreateWindowEx(0,			//�g���E�B���h�E�X�^�C��
		CLASS_NAME,						//�E�B���h�E�N���X�̖��O
		WINDOW_NAME,					//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,			//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,					//�E�B���h�E�̍���x���W
		CW_USEDEFAULT,					//�E�B���h�E�̍��゙���W
		(rect.right - rect.left),		//�E�B���h�E�̕�
		(rect.bottom - rect.top),		//�E�B���h�E�̍���
		NULL,							//�e�E�B���h�E�̃n���h��
		NULL,							//���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,						//�C���X�^���X�n���h��
		NULL);							//�E�B���h�E�쐬�f�[�^

	//����������
	if (FAILED(Init(hInstance, hWnd, TRUE)))	//�E�C���h�E�\���FTRUE,�t���X�N���[���\���FFALSE
	{//�����������s�����ꍇ
		return -1;
	}

	//����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;					//����������
	dwExeLastTime = timeGetTime();		//���ݎ������擾(�ۑ�)

	//�E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);			//�E�B���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);					//�N���C�A���g�̈�̍X�V

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windows�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}
			else
			{//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);		//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�ɕϊ�
				DispatchMessage(&msg);		//�E�B���h�E�v���V�[�W���Ƀ��b�Z�[�W�𑗏o
			}
		}
		else
		{//Directx�̏���
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwExeLastTime) >= (1000 / 60))
			{//60����1�b�o��
				dwExeLastTime = dwCurrentTime;		//�����J�n�̎���[���ݎ���]��ۑ�

				//�X�V����
				Update();

				//�`�揈��
				Draw();
			}
		}
	}
	//�I������
	Uninit();

	//����\��߂�
	timeEndPeriod(1);

	//�E�C���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}

//============================================================
//	�E�C���h�E�v���V�[�W��
//============================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:		//�E�C���h�E�j��̃��b�Z�[�W
							//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			//�E�C���h�E�̔j��
			DestroyWindow(hWnd);
			break;
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
//==========================================================
//	����������
//==========================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;			//�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;	//�v���[���e�[�V�����p�����[�^

	//Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferWidth = SCREEN_WIDTH;							//�Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							//�Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;							//�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;										//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						//�_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	d3dpp.EnableAutoDepthStencil = TRUE;							//�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						//�f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;										//�E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//�C���^�[�o��

	//Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_�������n�[�h�E�F�A�ōs��)
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		//directx3D�f�o�C�X����(�`�揈�����n�[�h�E�F�A���_������CPU�ōs��)
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			//directx3D�f�o�C�X����(�`�揈�����_������CPU�ōs��)
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�L�[�{�[�h�̏���������
	if (FAILED(InitInput(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//�T�E���h�̏�����
	InitSound(hWnd);

	//�t�F�[�h�̐ݒ�
	InitFade(g_mode);

	//�����L���O�̃��Z�b�g
	ResetRanking();

	return S_OK;
}

//======================================================
//	�I������
//======================================================
void Uninit(void)
{
	//����\��߂�
	timeEndPeriod(1);

	//�T�E���h�I������
	UninitSound();

	//�L�[�{�[�h�I������
	UninitInput();

	//�t�F�[�h�I������
	UninitFade();

	//Direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3D�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//======================================================
//	�X�V����
//======================================================
void Update(void)
{
	//�L�[�{�[�h�̍X�V����
	UpdateInput();

	switch (g_mode)
	{
	case MODE_TITLE:	//�^�C�g�����
		UpdateTitle();
		break;

	case MODE_TUTORIAL:	//�`���[�g���A�����
		UpdateTutorial();
		break;

	case MODE_GAME:		//�Q�[�����
		UpdateGame();
		break;

	case MODE_RESULT:	//�Q�[�����
		UpdateResult();
		break;

	case MODE_RANK:		//�����L���O���
		UpdateRanking();
		break;
	}
	//�t�F�[�h�X�V����
	UpdateFade();
}

//======================================================
//	�`�揈��
//======================================================
void Draw(void)
{
	//��ʃN���A(�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A)
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ

		switch (g_mode)
		{
		case MODE_TITLE:	//�^�C�g�����
			DrawTitle();
			break;

		case MODE_TUTORIAL:	//�`���[�g���A�����
			DrawTutorial();
			break;

		case MODE_GAME:		//�Q�[�����
			DrawGame();
			break;

		case MODE_RESULT:	//���U���g���
			DrawResult();
			break;

		case MODE_RANK:		//�����L���O���
			DrawRanking();
			break;
		}
		//�t�F�[�h�`�揈��
		DrawFade();

		//�`��I��
		g_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=======================================================
//	�f�o�C�X�̎擾
//=======================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//=======================================================
//	���[�h�̐ݒ�
//=======================================================
void SetMode(MODE mode)
{
	//���݂̉�ʂ̏I������
	switch (g_mode)
	{
	case MODE_TITLE:	//�^�C�g�����
		UninitTitle();
		break;

	case MODE_TUTORIAL:	//�`���[�g���A�����
		UninitTutorial();
		break;

	case MODE_GAME:		//�Q�[�����
		UninitGame();
		break;

	case MODE_RESULT:	//���U���g���
		UninitResult();
		break;

	case MODE_RANK:		//�����L���O���
		UninitRanking();
		break;
	}

	//�V������ʂ̏�����
	switch (mode)
	{
	case MODE_TITLE:	//�^�C�g�����
		InitTitle();
		break;

	case MODE_TUTORIAL:	//�`���[�g���A�����
		InitTutorial();
		break;

	case MODE_GAME:		//�Q�[�����
		InitGame();
		break;

	case MODE_RESULT:	//���U���g���
		InitResult();
		break;

	case MODE_RANK:		//�����L���O���
		InitRanking();
		break;
	}

	g_mode = mode;		//���݂̉�ʂ�؂�ւ���
}