//-----------------------------------------------------------------------------------------------
//
// �w�i�̏���[bg.cpp]
// Author : ���앑
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------------------------
#include "bg.h"					// �w�i
#include "object2D.h"			// 2D�I�u�W�F�N�g
#include "application.h"		// �A�v���P�[�V����
#include "renderer.h"			// �����_�����O
#include "VirtualController.h"	// ���z�R���g���[���[
#include "TextureFileName.h"	// �摜�̃t�@�C����

//-----------------------------------------------------------------------------------------------
// �萔�錾
//-----------------------------------------------------------------------------------------------
// �w�i�̈ړ��X�s�[�h
static const float BG_SPPED = -0.001f;

//-----------------------------------------------------------------------------------------------
//�@�R���X�g���N�^
//-----------------------------------------------------------------------------------------------
CBg::CBg()
	:m_fTexV(0), m_page(TUTORIAL_PAGE_NONE)
{
	for (int nCntBg = 0; nCntBg < MAX_TEXTURE; nCntBg++)
	{
		m_paObject2D[nCntBg] = nullptr;
	}
}

//-----------------------------------------------------------------------------------------------
//�@�f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CBg::~CBg()
{

}

//-----------------------------------------------------------------------------------------------
// ����
//-----------------------------------------------------------------------------------------------
CBg* CBg::Create()
{
	// �|�C���^��錾
	CBg* pBG = new CBg;

	if (pBG != nullptr)
	{// nullptr�ł͂Ȃ�������
		// ����������
		pBG->Init(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2.0f, CRenderer::SCREEN_HEIGHT / 2.0f, 0.0f));
	}

	return pBG;
}

//-----------------------------------------------------------------------------------------------
//�@������
//-----------------------------------------------------------------------------------------------
HRESULT CBg::Init(const D3DXVECTOR3& pos)
{
	// �I�u�W�F�N�g2D�𐶐�
	m_paObject2D[0] = CObject2D::Create(pos, D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT, 0.0f));

	// �e�N�X�`���A�e�̐ݒ�
	switch (CApplication::GetMode())
	{
		// �^�C�g��
	case CApplication::MODE_TITLE:
		m_paObject2D[0]->LoadTexture(TEX_BG_TITLE);
		SetObjectParent(CObject::OBJECT_PARENT_TITLE);
		break;
		// �`���[�g���A��
	case CApplication::MODE_TUTORIAL:
		m_paObject2D[0]->LoadTexture(TEX_BG_TUTORIAL_ONE);
		// �I�u�W�F�N�g2D�𐶐�
		m_paObject2D[1] = CObject2D::Create(pos, D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT, 0.0f));
		m_paObject2D[1]->LoadTexture(TEX_BG_TOTORIAL_SECOND);
		SetObjectParent(CObject::OBJECT_PARENT_TUTORIAL);
		// 1�y�[�W�ڂ�\��
		m_page = TUTORIAL_PAGE_ONE;
		break;
		// �Q�[��
	case CApplication::MODE_GAME:
		m_paObject2D[0]->LoadTexture(TEX_BG_GAME);
		SetObjectParent(CObject::OBJECT_PARENT_GAME);
		break;
		// ���U���g
	case CApplication::MODE_RESULT:
		m_paObject2D[0]->LoadTexture(TEX_BG_RESULT);
		SetObjectParent(CObject::OBJECT_PARENT_RESULT);
		break;
		// ���̑�
	default:
		break;
	}

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
//�@�I��
//-----------------------------------------------------------------------------------------------
void CBg::Uninit()
{
	for (int nCntBg = 0; nCntBg < MAX_TEXTURE; nCntBg++)
	{
		if (m_paObject2D[nCntBg] != nullptr)
		{// nullptr�ł͂Ȃ�������
			// �I������
			m_paObject2D[nCntBg]->Uninit();
		}
	}
}

//-----------------------------------------------------------------------------------------------
//�@�X�V
//-----------------------------------------------------------------------------------------------
void CBg::Update()
{
	if (GetObjectParent() == CObject::OBJECT_PARENT_TUTORIAL)
	{// �`���[�g���A�����[�h��������
		State();
	}

	if (GetObjectParent() == CObject::OBJECT_PARENT_GAME)
	{// �Q�[�����[�h��������
		// U���W�̈ʒu�����Z
		m_fTexV += BG_SPPED;

		// ���W�̍X�V
		m_paObject2D[0]->SetTexPos(0.0f, m_fTexV);
	}
}

//-----------------------------------------------------------------------------------------------
//�@�`��
//-----------------------------------------------------------------------------------------------
void CBg::Draw()
{

}

//-----------------------------------------------------------------------------------------------
// �y�[�W�̐ݒ�
//-----------------------------------------------------------------------------------------------
void CBg::SetPage(TUTORIAL_PAGE page)
{
	m_page = page;
}

//-----------------------------------------------------------------------------------------------
// ���
//-----------------------------------------------------------------------------------------------
void CBg::State()
{
	switch (m_page)
	{
		// 1�y�[�W��
	case TUTORIAL_PAGE_ONE:
		m_paObject2D[0]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_paObject2D[1]->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		break;
		// 2�y�[�W��
	case TUTORIAL_PAGE_SECOND:
		m_paObject2D[0]->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		m_paObject2D[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;
		// ���̑�
	default:
		break;
	}
}