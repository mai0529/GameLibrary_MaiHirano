//---------------------------------------------------------------------------------
//
// �|�[�Y�̏���[pause.cpp]
// Author : ���앑
//
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//---------------------------------------------------------------------------------
#include "pause.h"				// �|�[�Y
#include "application.h"		// �A�v���P�[�V����
#include"renderer.h"			// �����_�����O
#include "object2D.h"			// �I�u�W�F�N�g2D
#include "ResourceManager.h"	// ���\�[�X�}�l�[�W���[
#include "TextureFileName.h"	// �摜�̃t�@�C����
#include "VirtualController.h"	// ���z�R���g���[���[
#include "fade.h"				// �t�F�[�h
#include "sound.h"				// ��
#include "menu.h"				// ���j���[
#include "game.h"				// �Q�[��
#include "bg.h"					// �w�i

//---------------------------------------------------------------------------------
// �}�N����`
//---------------------------------------------------------------------------------
// �R���g���[��
#define PLAYER_CONTROLLER		(0)

//---------------------------------------------------------------------------------
// �萔�錾
//---------------------------------------------------------------------------------
// ���j���[�̕�
static const float WIDTH_MENU = 600.0f;
// ���j���[�̍���
static const float HEIGHT_MENU = 200.0f;
// x���̈ʒu
static const float POS_X_MENU_SELECT = (float)CRenderer::SCREEN_WIDTH / 2.0f;
// y���̈ʒu
static const float POS_Y_MENU_SELECT = (float)CRenderer::SCREEN_HEIGHT / 2.0f - 90.0f;
// �I���̊Ԋu
static const float POS_DIS_MENU_SELECT = 180.0f;

//---------------------------------------------------------------------------------
// �e�N�X�`����
//---------------------------------------------------------------------------------
char* CPause::m_cFileName[] =
{
	// �w�i
	TEX_BG_PAUSE,
	// �Q�[���𑱂���
	TEX_MENU_GAME_PLAY,
	// �Q�[������蒼��
	TEX_MENU_GAME_REPLAY,
	// ���j���[�ɖ߂�
	TEX_MENU_SELECT,
	nullptr
};

//---------------------------------------------------------------------------------
// �ÓI�����o�ϐ��錾
//---------------------------------------------------------------------------------
// �^�C�g���N���X�̃|�C���^
CPause* CPause::m_Instance = nullptr;
// ���j���[�̃|�C���^
CMenu* CPause::m_pMenu[MAX_MENU_SELECT] = { nullptr };

//---------------------------------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------------------------------
CPause::CPause()
	:m_select(EPAUSE_SELECT_NONE)
{

}

//---------------------------------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------------------------------
CPause::~CPause()
{

}

//---------------------------------------------------------------------------------
// �C���X�^���X�̐���
//---------------------------------------------------------------------------------
void CPause::CreateInstance()
{
	if (m_Instance == nullptr)
	{// nullptr��������
	 // �������𐶐�
		m_Instance = new CPause;
	}
}

//---------------------------------------------------------------------------------
// �C���X�^���X�̎擾
//---------------------------------------------------------------------------------
CPause* CPause::GetInstance()
{
	if (m_Instance != nullptr)
	{// nullptr�ł͂Ȃ�������
		return m_Instance;
	}

	return nullptr;
}

//---------------------------------------------------------------------------------
// �C���X�^���X�̍폜
//---------------------------------------------------------------------------------
void CPause::DeleteInstance()
{
	// ��������j��
	delete m_Instance;

	// nullptr�ɂ���
	m_Instance = nullptr;
}

//---------------------------------------------------------------------------------
// ������
//---------------------------------------------------------------------------------
HRESULT CPause::Init()
{
	// �e�N�X�`���̓ǂݍ���
	CResourceManager::GetInstance()->LoadTexture(m_cFileName);

	// �w�i
	CBg::Create(CBg::ETYPE_BG_PAUSE);

	// �Z���N�g�̏�����
	m_select = EPAUSE_SELECT_GAME_PLAY;

	// ���j���[
	MenuInit();

	return S_OK;
}

//---------------------------------------------------------------------------------
// �I��
//---------------------------------------------------------------------------------
void CPause::Uninit()
{
	// �e�̍폜
	CObject::ReleaseParent(CObject::EOBJECT_PARENT_PAUSE);
}

//---------------------------------------------------------------------------------
// �X�V
//---------------------------------------------------------------------------------
void CPause::Update()
{
	// ���j���[
	MenuUpdate();

	// ���j���[�̌���
	MenuDecision();
}

//---------------------------------------------------------------------------------
// ���j���[�̏�����
//---------------------------------------------------------------------------------
void CPause::MenuInit()
{
	// �Q�[���𑱂���
	m_pMenu[0] = CMenu::Create(TEX_MENU_GAME_PLAY, D3DXVECTOR3(POS_X_MENU_SELECT, POS_Y_MENU_SELECT, 0.0f), D3DXVECTOR3(WIDTH_MENU, HEIGHT_MENU, 0.0f));
	// �Q�[������蒼��
	m_pMenu[1] = CMenu::Create(TEX_MENU_GAME_REPLAY, D3DXVECTOR3(POS_X_MENU_SELECT, POS_Y_MENU_SELECT + POS_DIS_MENU_SELECT, 0.0f), D3DXVECTOR3(WIDTH_MENU, HEIGHT_MENU, 0.0f));
	// ���[�h�I���ɖ߂�
	m_pMenu[2] = CMenu::Create(TEX_MENU_SELECT, D3DXVECTOR3(POS_X_MENU_SELECT, POS_Y_MENU_SELECT + (POS_DIS_MENU_SELECT * 2), 0.0f), D3DXVECTOR3(WIDTH_MENU, HEIGHT_MENU, 0.0f));

	for (int nCntMenu = 0; nCntMenu < MAX_MENU_SELECT; nCntMenu++)
	{// �e���|�[�Y�ɂ���
		m_pMenu[nCntMenu]->SetObjectParent(CObject::EOBJECT_PARENT_PAUSE);
	}

	switch (m_select)
	{
		// �Q�[���ɖ߂�
	case EPAUSE_SELECT_GAME_PLAY:
		m_pMenu[0]->SetState(CMenu::MENU_STATE_DECISION);
		m_pMenu[1]->SetState(CMenu::MENU_STATE_NO_DECISION);
		m_pMenu[2]->SetState(CMenu::MENU_STATE_NO_DECISION);
		break;
		// �Q�[������蒼��
	case EPAUSE_SELECT_GAME_REPLAY:
		m_pMenu[0]->SetState(CMenu::MENU_STATE_NO_DECISION);
		m_pMenu[1]->SetState(CMenu::MENU_STATE_DECISION);
		m_pMenu[2]->SetState(CMenu::MENU_STATE_NO_DECISION);
		break;
		// �I�����[�h�ɖ߂�
	case EPAUSE_SELECT_MENU_RETURN:
		m_pMenu[0]->SetState(CMenu::MENU_STATE_NO_DECISION);
		m_pMenu[1]->SetState(CMenu::MENU_STATE_NO_DECISION);
		m_pMenu[2]->SetState(CMenu::MENU_STATE_DECISION);
		break;
		// ���̑�
	default:
		break;
	}
}

//---------------------------------------------------------------------------------
// ���j���[�̍X�V
//---------------------------------------------------------------------------------
void CPause::MenuUpdate()
{
	if (CVController::GetInstance()->GetTrigger(PLAYER_CONTROLLER, CVController::VIRTUAL_KEY_DOWN))
	{// ���������ꂽ��
		if (m_select == EPAUSE_SELECT_GAME_PLAY)
		{// �Q�[���ɖ߂邪�I������Ă���
		 // �Q�[������蒼���ɂ���
			m_select = EPAUSE_SELECT_GAME_REPLAY;

			m_pMenu[0]->SetState(CMenu::MENU_STATE_NO_DECISION);
			m_pMenu[1]->SetState(CMenu::MENU_STATE_DECISION);
			m_pMenu[2]->SetState(CMenu::MENU_STATE_NO_DECISION);
		}
		else if (m_select == EPAUSE_SELECT_GAME_REPLAY)
		{// �Q�[������蒼����I�����Ă�����
		 // �I�����[�h�ɖ߂�ɂ���
			m_select = EPAUSE_SELECT_MENU_RETURN;

			m_pMenu[0]->SetState(CMenu::MENU_STATE_NO_DECISION);
			m_pMenu[1]->SetState(CMenu::MENU_STATE_NO_DECISION);
			m_pMenu[2]->SetState(CMenu::MENU_STATE_DECISION);
		}
	}
	else if (CVController::GetInstance()->GetTrigger(PLAYER_CONTROLLER, CVController::VIRTUAL_KEY_UP))
	{
		if (m_select == EPAUSE_SELECT_GAME_REPLAY)
		{// �Q�[������蒼����I�����Ă�����
		 // �Q�[����߂�ɂ���
			m_select = EPAUSE_SELECT_GAME_PLAY;

			m_pMenu[0]->SetState(CMenu::MENU_STATE_DECISION);
			m_pMenu[1]->SetState(CMenu::MENU_STATE_NO_DECISION);
			m_pMenu[2]->SetState(CMenu::MENU_STATE_NO_DECISION);
		}
		else if (m_select == EPAUSE_SELECT_MENU_RETURN)
		{// �I�����[�h�ɖ߂��I�����Ă�����
		 // �Q�[������蒼���ɂ���
			m_select = EPAUSE_SELECT_GAME_REPLAY;

			m_pMenu[0]->SetState(CMenu::MENU_STATE_NO_DECISION);
			m_pMenu[1]->SetState(CMenu::MENU_STATE_DECISION);
			m_pMenu[2]->SetState(CMenu::MENU_STATE_NO_DECISION);
		}
	}
}

//---------------------------------------------------------------------------------
// ���j���[�̌���
//---------------------------------------------------------------------------------
void CPause::MenuDecision()
{
	if (CFade::GetInstance()->GetFade() == CFade::FADE_NONE &&
		CVController::GetInstance()->GetTrigger(PLAYER_CONTROLLER, CVController::VIRTUAL_KEY_START))
	{
		if (m_select == EPAUSE_SELECT_GAME_PLAY)
		{//�|�[�Y���ł͂Ȃ�
			CObject::SetPause(false);
			// �I������
			Uninit();
		}
		else if (m_select == EPAUSE_SELECT_GAME_REPLAY)
		{// �Q�[������蒼�����I������Ă���
		 // �I������
			Uninit();
			// �Q�[������蒼��
			CFade::GetInstance()->SetFade(CApplication::MODE_GAME);
		}
		else if (m_select == EPAUSE_SELECT_MENU_RETURN)
		{// �I�����[�h�ɖ߂邪�I������Ă���
		 // �I������
			Uninit();
			// �Z���N�g���[�h�ɖ߂�
			CFade::GetInstance()->SetFade(CApplication::MODE_TITLE);
		}
	}
}