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
#include "VirtualController.h"	// ���z�R���g���[���[
#include "ResourceManager.h"	// ���\�[�X�}�l�[�W���[
#include "bg.h"					// �w�i
#include "fade.h"				// �t�F�[�h
#include "sound.h"				// ��
#include "TextureFileName.h"	// �摜�̃t�@�C����

//---------------------------------------------------------------------------------
// �e�N�X�`����
//---------------------------------------------------------------------------------
char* CTutorial::m_cFileName[] =
{
	// 1���ڂ̔w�i
	TEX_BG_TUTORIAL_ONE,
	// 2���ڂ̔w�i
	TEX_BG_TOTORIAL_SECOND,
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
	// ����
	// ���\�[�X�}�l�[�W���[�̃C���X�^���X�𐶐�
	CResourceManager::CreateInstance();
	// �e�N�X�`���̓ǂݍ���
	CResourceManager::GetInstance()->LoadTexture(m_cFileName);

	// �w�i
	m_pBg = CBg::Create();

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
		// �e�̍폜
		CObject::ReleseParent(CObject::OBJECT_PARENT_TUTORIAL);

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
	if ((CVController::GetInstance()->GetTrigger(MULTI_TYPE_ONE - 1, CVController::VIRTUAL_KEY_LEFT)
		|| CVController::GetInstance()->GetTrigger(MULTI_TYPE_SECOND - 1, CVController::VIRTUAL_KEY_LEFT)))
	{// ��
		m_pBg->SetPage(CBg::TUTORIAL_PAGE_ONE);
	}
	else if (CVController::GetInstance()->GetTrigger(MULTI_TYPE_ONE - 1, CVController::VIRTUAL_KEY_RIGHT)
		|| CVController::GetInstance()->GetTrigger(MULTI_TYPE_SECOND - 1, CVController::VIRTUAL_KEY_RIGHT))
	{// �E
		m_pBg->SetPage(CBg::TUTORIAL_PAGE_SECOND);
	}

	if (CVController::GetInstance()->GetTrigger(MULTI_TYPE_ONE - 1, CVController::VIRTUAL_KEY_START)
		|| CVController::GetInstance()->GetTrigger(MULTI_TYPE_ONE - 1, CVController::VIRTUAL_KEY_A))
	{// ENETER�L�[�ASTART�{�^���������ꂽ��
	 // �Q�[����ʂɈڍs
		CApplication::SetMode(CApplication::MODE_TITLE);

		// ���̍Đ�
			CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_DECISION_CAT);
			CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_DECISION_DOG);
	}
}