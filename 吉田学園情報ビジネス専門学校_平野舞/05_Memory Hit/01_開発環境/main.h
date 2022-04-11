#ifndef _MAIN_H_		//���̃}�N����`������Ȃ�������
#define _MAIN_H_		//��d�C���N���[�h�h�~�̃}�N����`

//======================================================
// �C���N���[�h
//======================================================
#include <windows.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION			(0x0800)			//�r���h���̌x���Ώ��p�}�N��
#include "dinput.h"										//���͏����ɕK�v
#include "xinput.h"										//Joypad���͏����ɕK�v
#include "xaudio2.h"									//�T�E���h�����ɕK�v
#include <assert.h>										//�A�T�[�g�ɕK�v
#include <stdio.h>										//�e�L�X�g�t�@�C����ǂݍ��ނ̂ɕK�v

//======================================================
// ���C�u�����̃����N
//======================================================
#pragma comment(lib,"d3d9.lib")							//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")						//d3d9.lib�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")						//directx�R���|�[�l���g
#pragma comment(lib,"winmm.lib")						//�V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib")						//���͏����ɕK�v

//======================================================
// �}�N����`
//======================================================
#define CLASS_NAME			"WindowClass"				//�E�C���h�E�N���X��
#define WINDOW_NAME			"Human Box"					//�E�C���h�E�̖��O�i�L���v�V�����\���j
#define SCREEN_WIDTH		(1280)						//�E�B���h�E��
#define SCREEN_HEIGHT   	(720)						//�E�B���h�E����
#define FVF_VERTEX_2D		(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//======================================================
//	���_���[2D]�̍\���̂��`
//======================================================
typedef struct
{
	D3DXVECTOR3 pos;		//���_���W
	float rhw;				//���W�ϊ��p�̌W��(1.0f�ŌŒ�)
	D3DCOLOR col;			//���_�J���[
	D3DXVECTOR2 tex;		//�e�N�X�`�����W
}VERTEX_2D;

//======================================================
//	���(���[�h)�̎��
//======================================================
typedef enum
{
	MODE_TITLE = 0,			//�^�C�g�����
	MODE_GAME,				//�Q�[�����
	MODE_TUTORIAL,			//�`���[�g���A�����
	MODE_RESULT,			//���U���g���
	MODE_RANK,				//�����L���O���
	MODE_MAX
}MODE;

//======================================================
//	�v���g�^�C�v�錾
//======================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);

#endif