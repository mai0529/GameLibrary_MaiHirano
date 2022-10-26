//-----------------------------------------------------------------------------------------------
//
// 2D�|���S������[object2D.cpp]
// Author : ���앑
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------------------------
#include "object2D.h"			// 2D�I�u�W�F�N�g
#include "application.h"		// �A�v���P�[�V����
#include "renderer.h"			// �����_�����O
#include "main.h"				// ���C��
#include "ResourceManager.h"	// ���\�[�X�}�l�[�W���[

//-----------------------------------------------------------------------------------------------
// �R���X�g���N�^
//
// int nPriority �� �`��D�揇�ʂ��w��
//-----------------------------------------------------------------------------------------------
CObject2D::CObject2D(int nPriority /* = 3 */)
	:CObject(nPriority),m_pVtxBuffer(nullptr), m_pos(0.0f, 0.0f, 0.0f), m_size(0.0f, 0.0f, 0.0f), m_col(0.0f, 0.0f, 0.0f, 0.0f)
{

}

//-----------------------------------------------------------------------------------------------
//�@�f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CObject2D::~CObject2D()
{

}

//-----------------------------------------------------------------------------------------------
//�@����
//
// char* cFileName		   �� �摜�̖��O(�p�X���܂�)
// const D3DXVECTOR3& pos  �� ����������W�̈ʒu
// const D3DXVECTOR3& size �� ��������|���S���̑傫��
//-----------------------------------------------------------------------------------------------
CObject2D* CObject2D::Create(char* cFileName,const D3DXVECTOR3& pos, const D3DXVECTOR3& size, int nPriority /*= 3*/)
{
	// �|�C���^�N���X��錾
	CObject2D* pObject2D = new CObject2D(nPriority);

	if (pObject2D != nullptr)
	{// ����nullptr�ł͂Ȃ�������
		// �摜�̐ݒ�
		pObject2D->LoadTexture(cFileName);
		// �|���S���T�C�Y��ݒ�
		pObject2D->SetSize(size);

		// ������
		pObject2D->Init(pos);
	}

	return pObject2D;
}

//-----------------------------------------------------------------------------------------------
// ������
//
// const D3DXVECTOR3& pos �� �ŏ��ɕ\��������W�ʒu
//-----------------------------------------------------------------------------------------------
HRESULT CObject2D::Init(const D3DXVECTOR3& pos)
{
	SetPosition(pos);

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffer,
		nullptr);

	// ���_�o�b�t�@�̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���|�C���^���擾
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - (m_size.x / 2.0f), pos.y - (m_size.y / 2.0f), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + (m_size.x / 2.0f), pos.y - (m_size.y / 2.0f), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - (m_size.x / 2.0f), pos.y + (m_size.y / 2.0f), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + (m_size.x / 2.0f), pos.y + (m_size.y / 2.0f), 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR( 1.0f,1.0f,1.0f,1.0f );
	pVtx[1].col = D3DXCOLOR( 1.0f,1.0f,1.0f,1.0f );
	pVtx[2].col = D3DXCOLOR( 1.0f,1.0f,1.0f,1.0f );
	pVtx[3].col = D3DXCOLOR( 1.0f,1.0f,1.0f,1.0f );

	// �e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuffer->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
//�@�|���S���I��
//-----------------------------------------------------------------------------------------------
void CObject2D::Uninit()
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuffer != nullptr)
	{
		m_pVtxBuffer->Release();
		m_pVtxBuffer = nullptr;
	}

	// �I�u�W�F�N�g�̔j��
	Release();
}

//-----------------------------------------------------------------------------------------------
//�@�|���S���X�V
//-----------------------------------------------------------------------------------------------
void CObject2D::Update()
{

}

//-----------------------------------------------------------------------------------------------
//�@�|���S���`��
//-----------------------------------------------------------------------------------------------
void CObject2D::Draw()
{
	LPDIRECT3DTEXTURE9 pTexture = CResourceManager::GetInstance()->GetTexture(m_cFileName);

	// �����_�����O�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���ݒ�
	pDevice->SetTexture(0, pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//-----------------------------------------------------------------------------------------------
//�@�ʒu�̐ݒ�
//
// const D3DXVECTOR3& pos �� �\�����������W�ʒu
//-----------------------------------------------------------------------------------------------
void CObject2D::SetPosition(const D3DXVECTOR3& pos)
{
	// �ʒu
	m_pos = pos;
}

//-----------------------------------------------------------------------------------------------
//�@�ʒu�̎擾
//-----------------------------------------------------------------------------------------------
const D3DXVECTOR3& CObject2D::GetPosition() const
{
	return m_pos;
}

//-----------------------------------------------------------------------------------------------
//�@�T�C�Y�̐ݒ�
//
// D3DXVECTOR3 size �� �|���S���̑傫��
//-----------------------------------------------------------------------------------------------
void CObject2D::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//-----------------------------------------------------------------------------------------------
// �T�C�Y�̎擾
//-----------------------------------------------------------------------------------------------
const D3DXVECTOR3& CObject2D::GetSize() const
{
	return m_size;
}

//-----------------------------------------------------------------------------------------------
// 1P��2P����ݒ�
//-----------------------------------------------------------------------------------------------
void CObject2D::SetPlayerType(MULTI_TYPE playerType)
{
	m_PlayerType = playerType;
}

//-----------------------------------------------------------------------------------------------
// 1P��2P�����擾
//-----------------------------------------------------------------------------------------------
MULTI_TYPE CObject2D::GetPlayerType()
{
	return m_PlayerType;
}

//-----------------------------------------------------------------------------------------------
//�@�F�̐ݒ�
//
// D3DXCOLOR col �� �F
//-----------------------------------------------------------------------------------------------
void CObject2D::SetColor(D3DXCOLOR col)
{
	m_col = col;

	// ���_�o�b�t�@�̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���|�C���^���擾
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].col = D3DXCOLOR(col.r , col.g , col.b , col.a );
	pVtx[1].col = D3DXCOLOR(col.r , col.g , col.b , col.a );
	pVtx[2].col = D3DXCOLOR(col.r , col.g , col.b , col.a );
	pVtx[3].col = D3DXCOLOR(col.r , col.g , col.b , col.a );

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuffer->Unlock();
}

//-----------------------------------------------------------------------------------------------
// ���_�J���[�̎擾
//-----------------------------------------------------------------------------------------------
D3DXCOLOR CObject2D::GetColor()
{
	return m_col;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//�@�e�N�X�`���A�j���[�V�������W�̐ݒ�
//
// int nDivisionX	�� U���W�̕�����
// int nDivisionV	�� V���W�̕�����
// int nNowPatternX �� U���W�̌��݂̃A�j���[�V�����ԍ�
// int nNowPatternV �� V���W�̌��݂̃A�j���[�V�����ԍ�
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CObject2D::SetTexAnim(int nDivisionU, int nDivisionV, int nNowPatternU, int nNowPatternV)
{
	// ���_�o�b�t�@�̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���|�C���^���擾
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].tex = D3DXVECTOR2(((1.0f / nDivisionU) * nNowPatternU), ((1.0f / nDivisionV) * nNowPatternV));
	pVtx[1].tex = D3DXVECTOR2(((1.0f / nDivisionU) * nNowPatternU) + (1.0f / nDivisionU), ((1.0f / nDivisionV) * nNowPatternV));
	pVtx[2].tex = D3DXVECTOR2(((1.0f / nDivisionU) * nNowPatternU), ((1.0f / nDivisionV) * nNowPatternV) + (1.0f / nDivisionV));
	pVtx[3].tex = D3DXVECTOR2(((1.0f / nDivisionU) * nNowPatternU) + (1.0f / nDivisionU), ((1.0f / nDivisionV) * nNowPatternV) + (1.0f / nDivisionV));

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuffer->Unlock();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �A�j���[�V�������W�̐ݒ�
//
// float fTexU �� U���W
// float fTexV �� V���W
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CObject2D::SetTexPos(float fTexU, float fTexV)
{
	// ���_�o�b�t�@�̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���|�C���^���擾
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].tex = D3DXVECTOR2(fTexU, fTexV);
	pVtx[1].tex = D3DXVECTOR2(fTexU + 1.0f, fTexV);
	pVtx[2].tex = D3DXVECTOR2(fTexU, fTexV + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fTexU + 1.0f, fTexV + 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuffer->Unlock();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// �ʒu�̍X�V
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void CObject2D::UpdatePos()
{
	// ���_�o�b�t�@�̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���|�C���^���擾
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2.0f), m_pos.y - (m_size.y / 2.0f), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2.0f), m_pos.y - (m_size.y / 2.0f), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2.0f), m_pos.y + (m_size.y / 2.0f), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2.0f), m_pos.y + (m_size.y / 2.0f), 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuffer->Unlock();
}

//-----------------------------------------------------------------------------------------------
// �e�N�X�`���̐ݒ�
//
// char* cFileName �� �t�@�C����
//-----------------------------------------------------------------------------------------------
void CObject2D::LoadTexture(char* cFileName)
{
	m_cFileName = cFileName;
}