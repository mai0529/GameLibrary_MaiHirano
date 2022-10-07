//---------------------------------------------------------------------------------
//
// �^�C�g������[title.cpp]
// Author : ���앑
//
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//---------------------------------------------------------------------------------
#include "title.h"				// �^�C�g��
#include "application.h"		// �A�v���P�[�V����
#include "VirtualController.h"	// ���z�R���g���[���[
#include "ResourceManager.h"	// ���\�[�X�}�l�[�W���[
#include "bg.h"					// �w�i
#include "fade.h"				// �t�F�[�h
#include "sound.h"				// ��
#include "menu.h"				// ���j���[
#include "TextureFileName.h"	// �摜�̃t�@�C����

//---------------------------------------------------------------------------------
// �e�N�X�`����
//---------------------------------------------------------------------------------
char* CTitle::m_cFileName[] =
{
	// �w�i
	TEX_BG_TITLE,
	// �X�^�[�g���j���[
	TEX_MENU_START,
	// �`���[�g���A�����j���[
	TEX_MENU_TUTORIAL,
	nullptr
};

//---------------------------------------------------------------------------------
// �ÓI�����o�ϐ��錾
//---------------------------------------------------------------------------------
// �^�C�g���̃|�C���^
CTitle* CTitle::m_Instance = nullptr;
// ���j���[
CMenu* CTitle::m_pMenu[MAX_MENU_SELECT] = { nullptr };

//---------------------------------------------------------------------------------
//	�R���X�g���N�^
//---------------------------------------------------------------------------------
CTitle::CTitle()
	:m_select(TITLE_SELECT_NONE)
{

}

//---------------------------------------------------------------------------------
//	�f�X�g���N�^
//---------------------------------------------------------------------------------
CTitle::~CTitle()
{

}

//---------------------------------------------------------------------------------
// �C���X�^���X�̐���
//---------------------------------------------------------------------------------
void CTitle::CreateInstance()
{
	if (m_Instance == nullptr)
	{// nullptr��������
	 // �������̐���
		m_Instance = new CTitle;
	}
}

//---------------------------------------------------------------------------------
// �C���X�^���X�̎擾
//---------------------------------------------------------------------------------
CTitle* CTitle::GetInstance()
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
HRESULT CTitle::Init()
{
	// �Q�[���I��
	m_select = TITLE_SELECT_GAME;

	// ����
	// ���\�[�X�}�l�[�W���[�̃C���X�^���X�𐶐�
	CResourceManager::CreateInstance();
	// �e�N�X�`���̓ǂݍ���
	CResourceManager::GetInstance()->LoadTexture(m_cFileName);

	// �w�i
	CBg::Create();

	// �^�C�g�����j���[�I��
	m_pMenu[0] = CMenu::Create(D3DXVECTOR3(650.0f,520.0f,0.0f));
	m_pMenu[0]->LoadTexture(TEX_MENU_START);

	// �`���[�g���A�����j���[�I��
	m_pMenu[1] = CMenu::Create(D3DXVECTOR3(650.0f, 640.0f, 0.0f));
	m_pMenu[1]->LoadTexture(TEX_MENU_TUTORIAL);

	switch (m_select)
	{
		// �Q�[��
	case TITLE_SELECT_GAME:
		m_pMenu[0]->SetState(CMenu::MENU_STATE_DECISION);
		m_pMenu[1]->SetState(CMenu::MENU_STATE_NO_DECISION);
		break;
		// �`���[�g���A��
	case TITLE_SELECT_TUTORIAL:
		m_pMenu[0]->SetState(CMenu::MENU_STATE_NO_DECISION);
		m_pMenu[1]->SetState(CMenu::MENU_STATE_DECISION);
		break;
		// ���̑�
	default:
		break;
	}

	// ���̍Đ�
	CSound::GetInstace()->Play(CSound::SOUND_LABEL_TITLE);

	return S_OK;
}

//---------------------------------------------------------------------------------
//	�I��
//---------------------------------------------------------------------------------
void CTitle::Uninit()
{
	// ���̒�~
	CSound::GetInstace()->Stop();

	if (m_Instance != nullptr)
	{// nullptr�ł͂Ȃ�������
		// �e���폜
		CObject::ReleseParent(CObject::OBJECT_PARENT_TITLE);

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
void CTitle::Update()
{
	if (CVController::GetInstance()->GetTrigger(MULTI_TYPE_ONE - 1, CVController::VIRTUAL_KEY_DOWN)
		|| CVController::GetInstance()->GetTrigger(MULTI_TYPE_SECOND - 1, CVController::VIRTUAL_KEY_DOWN))
	{// ��
		if (m_select == TITLE_SELECT_GAME)
		{// �Q�[�����I������Ă�����
			// �`���[�g���A���ɂ���
			m_select = TITLE_SELECT_TUTORIAL;
			// ��Ԃ�ύX
			m_pMenu[0]->SetState(CMenu::MENU_STATE_NO_DECISION);
			m_pMenu[1]->SetState(CMenu::MENU_STATE_DECISION);
		}
	}
	else if (CVController::GetInstance()->GetTrigger(MULTI_TYPE_ONE - 1, CVController::VIRTUAL_KEY_UP)
		|| CVController::GetInstance()->GetTrigger(MULTI_TYPE_SECOND - 1, CVController::VIRTUAL_KEY_UP))
	{// ��
		if (m_select == TITLE_SELECT_TUTORIAL)
		{// �Q�[�����I������Ă�����
			// �Q�[���ɂ���
			m_select = TITLE_SELECT_GAME;
			// ��Ԃ�ύX
			m_pMenu[0]->SetState(CMenu::MENU_STATE_DECISION);
			m_pMenu[1]->SetState(CMenu::MENU_STATE_NO_DECISION);
		}
	}

	if (m_select == TITLE_SELECT_GAME)
	{// �Q�[�����I������Ă�����
		if (CVController::GetInstance()->GetTrigger(MULTI_TYPE_ONE - 1, CVController::VIRTUAL_KEY_START)
			|| CVController::GetInstance()->GetTrigger(MULTI_TYPE_ONE - 1, CVController::VIRTUAL_KEY_A))
		{// ENETER�L�[,START�{�^�� �AA�{�^���������ꂽ��
		 // �Q�[����ʂɈڍs
			CApplication::SetMode(CApplication::MODE_GAME);

			// ���̍Đ�
			CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_DECISION_CAT);
			CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_DECISION_DOG);
		}
	}
	else if (m_select == TITLE_SELECT_TUTORIAL)
	{// �`���[�g���A�����I������Ă�����
		if (CVController::GetInstance()->GetTrigger(MULTI_TYPE_ONE - 1, CVController::VIRTUAL_KEY_START)
			|| CVController::GetInstance()->GetTrigger(MULTI_TYPE_ONE - 1, CVController::VIRTUAL_KEY_A))
		{// ENETER�L�[,START�{�^���AA�{�^���������ꂽ��
		 // �`���[�g���A����ʂɈڍs
			CApplication::SetMode(CApplication::MODE_TUTORIAL);

			// ���̍Đ�
			CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_DECISION_CAT);
			CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_DECISION_DOG);

		}
	}
}