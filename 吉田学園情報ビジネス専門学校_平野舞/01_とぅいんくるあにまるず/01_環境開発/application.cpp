//---------------------------------------------------------------------------------
//
// �A�v���P�[�V�����̏���[application.cpp]
// Author : ���앑
//
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//---------------------------------------------------------------------------------
#include <stdio.h>				// �O���t�@�C���ǂݍ��ݗp
#include "witchResults.h"		// ���ʕ\��
#include "application.h"		// �A�v���P�[�V����
#include "renderer.h"			// �����_�����O
#include "sound.h"				// ��
#include "VirtualController.h"	// ���z�R���g���[���[
#include "title.h"				// �^�C�g��
#include "game.h"				// �Q�[��
#include "result.h"				// ���U���g
#include "fade.h"				// �t�F�[�h
#include "tutorial.h"			// �`���[�g���A��

//---------------------------------------------------------------------------------
// �ÓI�����o�ϐ��錾
//---------------------------------------------------------------------------------
// �����_�����O�|�C���^
CRenderer* CApplication::m_pRenderer = nullptr;
// ���[�h
CApplication::MODE CApplication::m_mode = MODE_TITLE;

//---------------------------------------------------------------------------------
//	�R���X�g���N�^
//---------------------------------------------------------------------------------
CApplication::CApplication()
{

}

//---------------------------------------------------------------------------------
//	�f�X�g���N�^
//---------------------------------------------------------------------------------
CApplication::~CApplication()
{

}

//---------------------------------------------------------------------------------
//	������
//---------------------------------------------------------------------------------
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// ���z�R���g���[���[
	CVController::CreateInstance();
	CVController::GetInstance()->Init(hInstance, hWnd);

	// ��
	CSound::Create();
	CSound::GetInstace()->Init(hWnd);

	// �����_�����O�̃������𐶐�����
	m_pRenderer = new CRenderer;

	if (m_pRenderer == nullptr)
	{// nullptr��������
		return -1;
	}

	// �����_�����O�̏�����
	m_pRenderer->Init(hWnd, bWindow);

	// ���[�h�ݒ�
	SetMode(m_mode);

	return S_OK;
}

//---------------------------------------------------------------------------------
//	�I��
//---------------------------------------------------------------------------------
void CApplication::Uninit()
{
	// �^�C�g��
	CTitle::GetInstance()->Uninit();

	// �Q�[��
	CGame::GetInstance()->Uninit();

	// ���U���g
	CResult::GetInstance()->Uninit();

	// ��
	CSound::GetInstace()->Uninit();

	// ���z�R���g���[���[
	CVController::GetInstance()->Uninit();

	// �����_�����O
	if (m_pRenderer != nullptr)
	{// nullptr�ł͂Ȃ�������
		// �I��
		m_pRenderer->Uninit();

		// ��������j��
		delete m_pRenderer;

		// nullptr�ɖ߂�
		m_pRenderer = nullptr;
	}
}

//---------------------------------------------------------------------------------
//	�X�V
//---------------------------------------------------------------------------------
void CApplication::Update()
{
	// ���z�R���g���[���[
	CVController::GetInstance()->Update();

	// �e��ʂ̍X�V
	switch (m_mode)
	{
		// �^�C�g��
	case MODE_TITLE:
		CTitle::GetInstance()->Update();
		break;
		// �`���[�g���A��
	case MODE_TUTORIAL:
		CTutorial::GetInstance()->Update();
		break;
		// �Q�[��
	case MODE_GAME:
		CGame::GetInstance()->Update();
		break;
		// ���U���g
	case MODE_RESULT:
		CResult::GetInstance()->Update();
		break;
		// ���̑�
	default:
		break;
	}

	if (m_pRenderer != nullptr)
	{// �����_�����O
		m_pRenderer->Update();
	}
}

//---------------------------------------------------------------------------------
//	�`��
//---------------------------------------------------------------------------------
void CApplication::Draw()
{
	if (m_pRenderer != nullptr)
	{// �����_�����O
		m_pRenderer->Draw();
	}
}

//---------------------------------------------------------------------------------
//	�����_�����O�|�C���^�̎擾
//---------------------------------------------------------------------------------
CRenderer* CApplication::GetRenderer()
{
	return m_pRenderer;
}

//---------------------------------------------------------------------------------
// ���[�h�̐ݒ�
//---------------------------------------------------------------------------------
void CApplication::SetMode(MODE mode)
{
	// �e��ʂ̏I��
	switch (m_mode)
	{
		// �^�C�g��
	case MODE_TITLE:
		CTitle::GetInstance()->Uninit();
		break;
		// �`���[�g���A��
	case MODE_TUTORIAL:
		CTutorial::GetInstance()->Uninit();
		break;
		// �Q�[��
	case MODE_GAME:
		// ���ʕ\���̃C���X�^���X�𐶐�
		CWitchResult::CreateInstance();
		CWitchResult::GetInstance()->SetWinner();

		CGame::GetInstance()->Uninit();
		break;
		// ���U���g
	case MODE_RESULT:
		CResult::GetInstance()->Uninit();
		break;
		// ���̑�
	default:
		break;
	}

	m_mode = mode;

	// �e��ʂ̊J�n
	switch (mode)
	{
		// �^�C�g��
	case MODE_TITLE:
		// �C���X�^���X�𐶐�����
		CTitle::CreateInstance();

		// ������
		CTitle::GetInstance()->Init();
		break;
		// �`���[�g���A��
	case MODE_TUTORIAL:
		// �C���X�^���X�𐶐�
		CTitle::CreateInstance();

		// ������
		CTutorial::GetInstance()->Init();
		break;
		// �Q�[��
	case MODE_GAME:
		//�@�C���X�^���X�𐶐�����
		CGame::CreateInstance();

		// ������
		CGame::GetInstance()->Init();
		break;
		// ���U���g
	case MODE_RESULT:
		// �C���X�^���X�𐶐�
		CResult::CreateInstance();
		// ������
		CResult::GetInstance()->Init();
		break;
		// ���̑�
	default:
		break;
	}
}

//---------------------------------------------------------------------------------
// ���[�h�̎擾
//---------------------------------------------------------------------------------
CApplication::MODE CApplication::GetMode()
{
	return m_mode;
}