//-------------------------------------------
//
// �����_�����O[renderer.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _RENDERER_H_		// ��d�C���N���[�h�h�~
#define _RENDERER_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include <d3dx9.h>		// �`�揈���ɕK�v

//-------------------------------------------
// �N���X
//-------------------------------------------
class CRenderer
{
public:		// �萔
	// �X�N���[���̕�
	static const int SCREEN_WIDTH;
	// �X�N���[���̍���
	static const int SCREEN_HEIGHT;

public:		// �֐�
	// �R���X�g���N�^
	CRenderer();
	// �f�X�g���N�^
	~CRenderer();

	// ������
	HRESULT Init(HWND hWnd, BOOL bWindow);
	// �I��
	void Uninit();
	// �X�V
	void Update();
	// �`��
	void Draw();
	// Device�̎擾
	LPDIRECT3DDEVICE9 GetDevice();

private:	// �֐�
#ifdef _DEBUG
	// FPS�\��
	void DrawFPS();
#endif // _DEBUG

private:	// �ϐ�
	// Direct3D�I�u�W�F�N�g
	LPDIRECT3D9 m_pD3D;
	// Device�I�u�W�F�N�g
	LPDIRECT3DDEVICE9 m_pD3DDevice;

#ifdef _DEBUG
	// �t�H���g
	LPD3DXFONT m_pFont;
#endif // _DEBUG
};

#endif		// _RENDERER_H_