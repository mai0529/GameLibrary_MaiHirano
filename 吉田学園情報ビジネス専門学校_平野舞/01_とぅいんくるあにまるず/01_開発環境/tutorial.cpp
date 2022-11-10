//---------------------------------------------------------------------------------
//
// �`���[�g���A������[tutorial.cpp]
// Author : ���앑
//
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//---------------------------------------------------------------------------------
#include "tutorial.h"			// �`���[�g���A��
#include "application.h"		// �A�v���P�[�V����
#include "renderer.h"			// �����_�����O
#include "VirtualController.h"	// ���z�R���g���[���[
#include "ResourceManager.h"	// ���\�[�X�}�l�[�W���[
#include "bg.h"					// �w�i
#include "fade.h"				// �t�F�[�h
#include "sound.h"				// ��
#include "TextureFileName.h"	// �摜�̃t�@�C����
#include "object2D.h"			// �I�u�W�F�N�g

//---------------------------------------------------------------------------------
// �萔�錾
//---------------------------------------------------------------------------------
// ���̉摜��
static const float ARROW_WIDTH = 90.0f;
// ���̉摜����
static const float ARROW_HEIGHT = 300.0f;
// �����̈ʒu(x��)
static const float ARROW_LEFT_POS_X = 40.0f;
// �E���̈ʒu(x��)
static const float ARROW_RIGHT_POS_X = 1240.0f;
// ���̈ʒu(y��)
static const float ARROW_POS_Y = CRenderer::SCREEN_HEIGHT / 2.0f;

//---------------------------------------------------------------------------------
// �e�N�X�`����
//---------------------------------------------------------------------------------
char* CTutorial::m_cFileName[] =
{
	// 1���ڂ̔w�i
	TEX_BG_TUTORIAL_ONE,
	// 2���ڂ̔w�i
	TEX_BG_TOTORIAL_SECOND,
	// ���-�E-
	TEX_TUTORIAL_ARROW_RIGHT,
	// ���-��-
	TEX_TUTORIAL_ARROW_LEFT,
	nullptr
};

//---------------------------------------------------------------------------------
// �ÓI�����o�ϐ��錾
//---------------------------------------------------------------------------------
// �^�C�g���̃|�C���^
CTutorial* CTutorial::m_Instance = nullptr;
// �w�i�̃|�C���^
CBg* CTutorial::m_pBg = nullptr;

//---------------------------------------------------------------------------------
//	�R���X�g���N�^
//---------------------------------------------------------------------------------
CTutorial::CTutorial()
{

}

//---------------------------------------------------------------------------------
//	�f�X�g���N�^
//---------------------------------------------------------------------------------
CTutorial::~CTutorial()
{

}

//---------------------------------------------------------------------------------
// �C���X�^���X�̐���
//---------------------------------------------------------------------------------
void CTutorial::CreateInstance()
{
	if (m_Instance == nullptr)
	{// nullptr��������
	 // �������̐���
		m_Instance = new CTutorial;
	}
}

//---------------------------------------------------------------------------------
// �C���X�^���X�̎擾
//---------------------------------------------------------------------------------
CTutorial* CTutorial::GetInstance()
{
	if (m_Instance != nullptr)
	{// nullptr�ł͂Ȃ�������
		return m_Instance;
	}

	return nullptr;
}

//---------------------------------------------------------------------------------
//	������
//---------------------------------------------------------------------------------
HRESULT CTutorial::Init()
{
	// �|�[�Y���ł͂Ȃ�
	CObject::SetPause(false);

	// ����
	// ���\�[�X�}�l�[�W���[�̃C���X�^���X�𐶐�
	CResourceManager::CreateInstance();
	// �e�N�X�`���̓ǂݍ���
	CResourceManager::GetInstance()->LoadTexture(m_cFileName);

	// �w�i
	m_pBg = CBg::Create(CBg::ETYPE_BG_TUTORIAL);

	// ���̕\��
	CObject2D::Create(TEX_TUTORIAL_ARROW_RIGHT, D3DXVECTOR3(ARROW_RIGHT_POS_X, ARROW_POS_Y, 0.0f), D3DXVECTOR3(ARROW_WIDTH, ARROW_HEIGHT, 0.0f));
	CObject2D::Create(TEX_TUTORIAL_ARROW_LEFT,D3DXVECTOR3(ARROW_LEFT_POS_X, ARROW_POS_Y,0.0f), D3DXVECTOR3(ARROW_WIDTH, ARROW_HEIGHT, 0.0f));

	// ���̍Đ�
	CSound::GetInstace()->Play(CSound::SOUND_LABEL_TUTORIAL);

	return S_OK;
}

//---------------------------------------------------------------------------------
//	�I��
//---------------------------------------------------------------------------------
void CTutorial::Uninit()
{
	// ���̒�~
	CSound::GetInstace()->Stop();

	if (m_Instance != nullptr)
	{// nullptr�ł͂Ȃ�������
	 // �I�u�W�F�N�g�̔j��
		CObject::ReleaseAll();

		// �e�N�X�`���̔j��
		CResourceManager::GetInstance()->AllUnloadTexture();

		// ��������j������
		delete m_Instance;

		// nullptr�ɂ���
		m_Instance = nullptr;
	}
}

//---------------------------------------------------------------------------------
//	�X�V
//---------------------------------------------------------------------------------
void CTutorial::Update()
{
	if ((CVController::GetInstance()->GetTrigger(0, CVController::VIRTUAL_KEY_LEFT)
		|| CVController::GetInstance()->GetTrigger(0, CVController::VIRTUAL_KEY_LEFT)))
	{// ��
		m_pBg->SetPage(CBg::TUTORIAL_PAGE_ONE);
	}
	else if (CVController::GetInstance()->GetTrigger(0, CVController::VIRTUAL_KEY_RIGHT)
		|| CVController::GetInstance()->GetTrigger(0, CVController::VIRTUAL_KEY_RIGHT))
	{// �E
		m_pBg->SetPage(CBg::TUTORIAL_PAGE_SECOND);
	}

	if (CFade::GetInstance()->GetFade() == CFade::FADE_NONE
		&& (CVController::GetInstance()->GetTrigger(0, CVController::VIRTUAL_KEY_START)
			|| CVController::GetInstance()->GetTrigger(0, CVController::VIRTUAL_KEY_A)))
	{// ENETER�L�[�ASTART�{�^���������ꂽ��
		 // �Q�[����ʂɈڍs
		CFade::GetInstance()->SetFade(CApplication::MODE_TITLE);

		// ���̍Đ�
		CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_DECISION_CAT);
		CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_DECISION_DOG);
		return;
	}
}