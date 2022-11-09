//-----------------------------------------------------------------------------------------------
//
// �˂��^�G�̏���[enemyCat.cpp]
// Author : ���앑
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------------------------
#include "enemyCat.h"		// �˂��^�G
#include "application.h"	// �A�v���P�[�V����
#include "renderer.h"		// �����_�����O
#include "time.h"			// �^�C��
#include "TextureFileName.h"	// �摜�̃t�@�C����

//-----------------------------------------------------------------------------------------------
// �萔�錾
//-----------------------------------------------------------------------------------------------
// ��
static const float ENEMY_CAT_WIDTH = 60.0f;
// ����
static const float ENEMY_CAT_HEIGHT = 50.0f;
// ���a
static const float ENEMY_CAT_RADIUS = 70.0f;
// ���S�����߂鎞��
static const int ENEMY_CAT_GETPOS_TIME = 3;
// ���n�߂鎞��
static const int ENEMY_CAT_START_TIME = 4;
// ���I��鎞��
static const int ENEMY_CAT_FINISH_TIME = 9;

//-----------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------------------------
CEnemyCat::CEnemyCat()
	:m_posStart(0.0f,0.0f,0.0f),m_Center(0.0f,0.0f,0.0f),m_fAngle(0.0f),m_fRadius(0.0f), m_bGet(false)
{

}

//-----------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CEnemyCat::~CEnemyCat()
{

}

//-----------------------------------------------------------------------------------------------
// ����
//-----------------------------------------------------------------------------------------------
CEnemyCat* CEnemyCat::Create(const D3DXVECTOR3& pos)
{
	// �|�C���^�N���X��錾
	CEnemyCat* pEnemyCat = new CEnemyCat;

	if (pEnemyCat != nullptr)
	{// ����nullptr�ł͂Ȃ�������
		// �ʒu
		pEnemyCat->SetPosition(pos);
		// ������
		pEnemyCat->Init();
	}

	return pEnemyCat;
}

//-----------------------------------------------------------------------------------------------
// ������
//
// const D3DXVECTOR3& pos �� �ŏ��ɕ\��������W�ʒu
//-----------------------------------------------------------------------------------------------
HRESULT CEnemyCat::Init()
{
	//�p�x
	m_fAngle = D3DX_PI;
	// ���a
	m_fRadius = ENEMY_CAT_RADIUS;

	// �e�N�X�`���̐ݒ�
	CObject2D::LoadTexture(TEX_ENEMY_CAT);
	// �T�C�Y
	CEnemy::SetSize(D3DXVECTOR3(ENEMY_CAT_WIDTH, ENEMY_CAT_HEIGHT, 0.0f));
	// ���
	CEnemy::SetEnemyType(ENEMY_TYPE_CAT);

	CEnemy::Init();

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �I��
//-----------------------------------------------------------------------------------------------s
void CEnemyCat::Uninit()
{
	CEnemy::Uninit();
}

//-----------------------------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------------------------
void CEnemyCat::Update()
{
	// �ړ�
	Move();

	// �p�x���X�V
	m_fAngle += D3DX_PI / 180.0f;

	// �p�x�̐��K��
	if (m_fAngle < -D3DX_PI)
	{
		m_fAngle += D3DX_PI * 2.0f;
	}
	else if (m_fAngle > D3DX_PI)
	{
		m_fAngle -= D3DX_PI * 2.0f;
	}

	CEnemy::Update();
}

//-----------------------------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------------------------
void CEnemyCat::Draw()
{
	CEnemy::Draw();
}

//-----------------------------------------------------------------------------------------------
// �ړ�
//-----------------------------------------------------------------------------------------------
void CEnemyCat::Move()
{
	// ���x�̎擾
	float fSpeed = CEnemy::GetSpeed();

	// �o�����Ԃ̎擾
	int nAppea = CEnemy::GetAppeaTime();

	// �ړ��ʂ̏�����
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �ʒu�̏�����
	D3DXVECTOR3 pos = CObject2D::GetPosition();

	if (!m_bGet)
	{// �����擾���Ă��Ȃ�������
		// �����ʒu���擾
		m_posStart = CEnemy::GetPosition();
	}

	
	if (CObject2D::GetPlayerType() == MULTI_TYPE_ONE && CTime::GetInstance()->GetTime() == nAppea + ENEMY_CAT_GETPOS_TIME)
	{// 1P���Ȃ�
		if (m_posStart.x > 300)
		{// ���S
			m_Center = D3DXVECTOR3(pos.x - 100.0f, pos.y, 0.0f);
		}
		else if (m_posStart.x <= 300)
		{
			m_Center = D3DXVECTOR3(pos.x + 50.0f, pos.y, 0.0f);
		}
	}
	else if (CObject2D::GetPlayerType() == MULTI_TYPE_SECOND && CTime::GetInstance()->GetTime() == nAppea + ENEMY_CAT_GETPOS_TIME)
	{// 2P���Ȃ�
		m_Center = D3DXVECTOR3(pos.x - 50.0f, pos.y, 0.0f);
	}

	if (CTime::GetInstance()->GetTime() >= nAppea + ENEMY_CAT_START_TIME && CTime::GetInstance()->GetTime() <= nAppea + ENEMY_CAT_FINISH_TIME)
	{// ���
		pos.x = (sinf(m_fAngle) * m_fRadius) + m_Center.x;
		pos.y = (cosf(m_fAngle) * m_fRadius) + m_Center.y;
	}
	else
	{
		move.y = fSpeed;
	}

	// �ړ��ʂ̐ݒ�
	CEnemy::SetMove(move);

	// �ʒu�̐ݒ�
	CObject2D::SetPosition(pos);
}