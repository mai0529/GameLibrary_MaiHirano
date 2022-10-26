//---------------------------------------------------------------------------------
//
// ���ʕ\������[witchResults.cpp]
// Author : ���앑
//
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//---------------------------------------------------------------------------------
#include "witchResults.h"		// ���ʕ\��
#include "application.h"		// �A�v���P�[�V����
#include "VirtualController.h"	// ���z�R���g���[���[
#include "ResourceManager.h"	// ���\�[�X�}�l�[�W���[
#include "bg.h"					// �w�i
#include "game.h"				// �Q�[��
#include "player.h"				// �v���C���[
#include "TextureFileName.h"	// �摜�̃t�@�C����

//-----------------------------------------------------------------------------------------------
// �萔�錾
//-----------------------------------------------------------------------------------------------
// ��
static const float RESULT_WIDTH = 200.0f;
// ����
static const float RESULT_HEIGHT = 200.0f;
// �v���C���[���U���g�̕�
static const float RESULT_PLAYER_WIDTH = 110.0f;
// �v���C���[���U���g�̍���
static const float RESULT_PLAYER_HEIGHT = 300.0f;

//---------------------------------------------------------------------------------
// �ÓI�����o�ϐ��錾
//---------------------------------------------------------------------------------
// �^�C�g���̃|�C���^
CWitchResult* CWitchResult::m_Instance = nullptr;

//---------------------------------------------------------------------------------
//	�R���X�g���N�^
//---------------------------------------------------------------------------------
CWitchResult::CWitchResult()
	:m_nWinner(0)
{
	for (int nCntResult = 0; nCntResult < MAX_TEX; nCntResult++)
	{
		m_paObject2D[nCntResult] = nullptr;
	}
}

//---------------------------------------------------------------------------------
//	�f�X�g���N�^
//---------------------------------------------------------------------------------
CWitchResult::~CWitchResult()
{

}

//---------------------------------------------------------------------------------
// �C���X�^���X�̐���
//---------------------------------------------------------------------------------
void CWitchResult::CreateInstance()
{
	if (m_Instance == nullptr)
	{// nullptr��������
	 // �������̐���
		m_Instance = new CWitchResult;
	}
}

//---------------------------------------------------------------------------------
// �C���X�^���X�̎擾
//---------------------------------------------------------------------------------
CWitchResult* CWitchResult::GetInstance()
{
	if (m_Instance != nullptr)
	{// nullptr�ł͂Ȃ�������
		return m_Instance;
	}

	return nullptr;
}

//-----------------------------------------------------------------------------------------------
// �ǂ��������҂�
//-----------------------------------------------------------------------------------------------
void CWitchResult::SetWinner()
{
	CPlayer* pPlayer_One = CGame::GetPlayer(0);
	CPlayer* pPlayer_Second = CGame::GetPlayer(1);

	if (pPlayer_One->GetLife() > pPlayer_Second->GetLife())
	{// 1P�̎���������������
		m_nWinner = MULTI_TYPE_ONE;
	}
	else if (pPlayer_One->GetLife() < pPlayer_Second->GetLife())
	{// 2P�̎���������������
		m_nWinner = MULTI_TYPE_SECOND;
	}
}

//---------------------------------------------------------------------------------
//	������
//---------------------------------------------------------------------------------
HRESULT CWitchResult::Init(const D3DXVECTOR3& pos)
{
	// �I�u�W�F�N�g2D�𐶐�
	m_paObject2D[0] = CObject2D::Create(nullptr,D3DXVECTOR3(pos.x, pos.y, 0.0f), D3DXVECTOR3(RESULT_WIDTH, RESULT_HEIGHT, 0.0f));
	m_paObject2D[1] = CObject2D::Create(nullptr,D3DXVECTOR3(pos.x + 700.0f, pos.y, 0.0f), D3DXVECTOR3(RESULT_WIDTH, RESULT_HEIGHT, 0.0f));
	m_paObject2D[2] = CObject2D::Create(nullptr,D3DXVECTOR3(pos.x - 300.0f, pos.y, 0.0f), D3DXVECTOR3(RESULT_PLAYER_WIDTH, RESULT_PLAYER_HEIGHT, 0.0f));
	m_paObject2D[3] = CObject2D::Create(nullptr,D3DXVECTOR3(pos.x + 400.0f, pos.y, 0.0f), D3DXVECTOR3(RESULT_PLAYER_WIDTH, RESULT_PLAYER_HEIGHT, 0.0f));

	for (int nCntResult = 0; nCntResult < MAX_TEX; nCntResult++)
	{
		// �I�u�W�F�N�g�̐e��ݒ�
		m_paObject2D[nCntResult]->SetObjectParent(CObject::EOBJECT_PARENT_RESULT);
	}

	// �e�N�X�`���ƐF�̐ݒ�
	switch (m_nWinner)
	{
		// 1P�̏���
	case MULTI_TYPE_ONE:
		m_paObject2D[0]->LoadTexture(TEX_RESULT_WIN);
		m_paObject2D[0]->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		m_paObject2D[1]->LoadTexture(TEX_RESULT_LOST);
		m_paObject2D[1]->SetColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));

		m_paObject2D[2]->LoadTexture(TEX_RESULT_1P_WIN);
		m_paObject2D[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_paObject2D[3]->LoadTexture(TEX_RESULT_2P_LOSE);
		m_paObject2D[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;
		// 2P�̏���
	case MULTI_TYPE_SECOND:
		m_paObject2D[0]->LoadTexture(TEX_RESULT_LOST);
		m_paObject2D[0]->SetColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
		m_paObject2D[1]->LoadTexture(TEX_RESULT_WIN); 
		m_paObject2D[1]->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

		m_paObject2D[2]->LoadTexture(TEX_RESULT_1P_LOSE);
		m_paObject2D[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_paObject2D[3]->LoadTexture(TEX_RESULT_2P_WIN);
		m_paObject2D[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;
		// ���̑�
	default:
		break;
	}

	return S_OK;
}

//---------------------------------------------------------------------------------
//	�I��
//---------------------------------------------------------------------------------
void CWitchResult::Uninit()
{
	if (m_Instance != nullptr)
	{// nullptr�ł͂Ȃ�������
		// ��������j������
		delete m_Instance;

		// nullptr�ɂ���
		m_Instance = nullptr;
	}
}

//---------------------------------------------------------------------------------
//	�X�V
//---------------------------------------------------------------------------------
void CWitchResult::Update()
{
	
}

//---------------------------------------------------------------------------------
// �`��
//---------------------------------------------------------------------------------
void CWitchResult::Draw()
{

}