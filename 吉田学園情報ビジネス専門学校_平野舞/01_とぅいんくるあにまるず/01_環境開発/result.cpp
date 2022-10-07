//---------------------------------------------------------------------------------
//
// ���U���g����[result.cpp]
// Author : ���앑
//
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//---------------------------------------------------------------------------------
#include "result.h"				// ���U���g
#include "application.h"		// �A�v���P�[�V����
#include "VirtualController.h"	// ���z�R���g���[���[
#include "ResourceManager.h"	// ���\�[�X�}�l�[�W���[
#include "bg.h"					// �w�i
#include "witchResults.h"		// ���ʕ\��
#include "fade.h"				// �t�F�[�h
#include "sound.h"				// ��
#include "TextureFileName.h"	// �摜�̃t�@�C����

//---------------------------------------------------------------------------------
// �e�N�X�`����
//---------------------------------------------------------------------------------
char* CResult::m_cFileName[] =
{
	// �w�i
	TEX_BG_RESULT,
	// WIN
	TEX_RESULT_WIN,
	// LOSE
	TEX_RESULT_LOST,
	// 1P����
	TEX_RESULT_1P_WIN,
	// 1P����
	TEX_RESULT_1P_LOSE,
	// 2P����
	TEX_RESULT_2P_WIN,
	// 2P����
	TEX_RESULT_2P_LOSE,
	nullptr
};

//-----------------------------------------------------------------------------------------------
// �萔�錾
//-----------------------------------------------------------------------------------------------
// ��
static const float RESULT_WIDTH = 200.0f;
// ����
static const float RESULT_HEIGHT = 200.0f;

//---------------------------------------------------------------------------------
// �ÓI�����o�ϐ��錾
//---------------------------------------------------------------------------------
// �^�C�g���̃|�C���^
CResult* CResult::m_Instance = nullptr;

//---------------------------------------------------------------------------------
//	�R���X�g���N�^
//---------------------------------------------------------------------------------
CResult::CResult()
{
	
}

//---------------------------------------------------------------------------------
//	�f�X�g���N�^
//---------------------------------------------------------------------------------
CResult::~CResult()
{

}

//---------------------------------------------------------------------------------
// �C���X�^���X�̐���
//---------------------------------------------------------------------------------
void CResult::CreateInstance()
{
	if (m_Instance == nullptr)
	{// nullptr��������
	 // �������̐���
		m_Instance = new CResult;
	}
}

//---------------------------------------------------------------------------------
// �C���X�^���X�̎擾
//---------------------------------------------------------------------------------
CResult* CResult::GetInstance()
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
HRESULT CResult::Init()
{
	// ����
	// ���\�[�X�}�l�[�W���[�̃C���X�^���X�𐶐�
	CResourceManager::CreateInstance();
	// �e�N�X�`���̓ǂݍ���
	CResourceManager::GetInstance()->LoadTexture(m_cFileName);

	// �w�i
	CBg::Create();

	// ���ʕ\��
	CWitchResult::GetInstance()->Init(D3DXVECTOR3(400.0f,350.0f,0.0f));

	// ���̍Đ�
	CSound::GetInstace()->Play(CSound::SOUND_LABEL_RESULT);

	return S_OK;
}

//---------------------------------------------------------------------------------
//	�I��
//---------------------------------------------------------------------------------
void CResult::Uninit()
{
	// ���̒�~
	CSound::GetInstace()->Stop();

	if (m_Instance != nullptr)
	{// nullptr�ł͂Ȃ�������
		 // �e���폜
		CObject::ReleseParent(CObject::OBJECT_PARENT_RESULT);

		// ���ʕ\��
		CWitchResult::GetInstance()->Uninit();

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
void CResult::Update()
{
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