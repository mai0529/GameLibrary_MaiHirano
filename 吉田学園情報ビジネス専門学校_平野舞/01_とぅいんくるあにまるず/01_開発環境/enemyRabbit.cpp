//-----------------------------------------------------------------------------------------------
//
// �������^�G�̏���[enemyRabbit.cpp]
// Author : ���앑
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------------------------
#include "enemyRabbit.h"	// �������^�G
#include "application.h"	// �A�v���P�[�V����
#include "renderer.h"		// �����_�����O
#include "time.h"			// �^�C�}
#include "wall.h"			// ��
#include "TextureFileName.h"	// �摜�̃t�@�C����

//-----------------------------------------------------------------------------------------------
// �萔�錾
//-----------------------------------------------------------------------------------------------
// ��
static const float ENEMY_RABBIT_WIDTH = 50.0f;
// ����
static const float ENEMY_RABBIT_HEIGHT = 50.0f;
// ���̈ړ�����
static const float ENEMY_RABBIT_WIDTH_MOVE = 2.0f;
// �c�̈ړ�����
static const float ENEMY_RABBIT_HEIGHT_MOVE = 60.0f;
// �t���[����
static const int ENEMY_RABBIT_FRAME = 60;
// �o���t���[����
static const int ENEMY_RABBIT_APPEA_FREAM = 120;

//-----------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------------------------
CEnemyRabbit::CEnemyRabbit()
	:m_fSpeed(0.0f), m_nCntMove(0),  m_nCntApeer(0),m_bGet(false)
{

}

//-----------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CEnemyRabbit::~CEnemyRabbit()
{

}

//-----------------------------------------------------------------------------------------------
// ����
//-----------------------------------------------------------------------------------------------
CEnemyRabbit* CEnemyRabbit::Create(const D3DXVECTOR3& pos)
{
	// �|�C���^�N���X��錾
	CEnemyRabbit* pEnemyRabbit = new CEnemyRabbit;

	if (pEnemyRabbit != nullptr)
	{// ����nullptr�ł͂Ȃ�������
		// ������
		pEnemyRabbit->Init(pos);
	}

	return pEnemyRabbit;
}

//-----------------------------------------------------------------------------------------------
// ������
//
// const D3DXVECTOR3& pos �� �ŏ��ɕ\��������W�ʒu
//-----------------------------------------------------------------------------------------------
HRESULT CEnemyRabbit::Init(const D3DXVECTOR3& pos)
{
	// �e�N�X�`���̐ݒ�
	CObject2D::LoadTexture(TEX_ENEMY_RABBIT);
	// �T�C�Y
	CEnemy::SetSize(D3DXVECTOR3(ENEMY_RABBIT_WIDTH, ENEMY_RABBIT_HEIGHT, 0.0f));
	// ���
	CEnemy::SetEnemyType(ENEMY_TYPE_RABBIT);

	CEnemy::Init(pos);

	// ���_�J���[
	CObject2D::SetColor(D3DXCOLOR(1.0f,0.5f,0.5f,1.0f));

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �I��
//-----------------------------------------------------------------------------------------------s
void CEnemyRabbit::Uninit()
{
	CEnemy::Uninit();
}

//-----------------------------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------------------------
void CEnemyRabbit::Update()
{
	if (CObject2D::GetPlayerType() == MULTI_TYPE_ONE)
	{// 1P���Ȃ�
		OneMove();
	}
	else if (CObject2D::GetPlayerType() == MULTI_TYPE_SECOND)
	{// 2P���Ȃ�
		SecondMove();
	}

	CEnemy::Update();
}

//-----------------------------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------------------------
void CEnemyRabbit::Draw()
{
	CEnemy::Draw();
}

//-----------------------------------------------------------------------------------------------
// 1P�ړ�
//-----------------------------------------------------------------------------------------------
void CEnemyRabbit::OneMove()
{
	// �ʒu�̎擾
	D3DXVECTOR3 pos = CEnemy::GetPosition();

	// �ړ��ʂ̏�����
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �ǂ̈ʒu�ƃT�C�Y���擾
	D3DXVECTOR3 posWall = CWall::GetInstance()->GetPosition();
	D3DXVECTOR3 sizeWall = CWall::GetInstance()->GetSize();

	if (!m_bGet)
	{// ���x���擾���Ă��Ȃ�������
		// ���x�̎擾
		m_fSpeed = CEnemy::GetSpeed();

		// �擾����
		m_bGet = true;
	}

	if (m_nCntApeer > ENEMY_RABBIT_APPEA_FREAM && pos.x + (ENEMY_RABBIT_WIDTH / 2.0f) > posWall.x - (sizeWall.x / 2.0f)
		|| m_nCntApeer > ENEMY_RABBIT_APPEA_FREAM && pos.x - (ENEMY_RABBIT_WIDTH / 2.0f) < 0.0f )
	{// x���W���ǂɓ����������A0.0f�ɂȂ�����
		// �ړ��X�s�[�h���t�����ɂ���
		m_fSpeed *= -1.0f;

		// y���W��60���ɂ���
		pos.y += ENEMY_RABBIT_HEIGHT_MOVE;

		// �ʒu�ݒ�
		CEnemy::SetPosition(pos);
	}

	// �ړ��ʂ̉��Z
	move.x = m_fSpeed;
	move.y = sinf((D3DX_PI / 2.0f) / ENEMY_RABBIT_FRAME * m_nCntMove) * ENEMY_RABBIT_WIDTH_MOVE;

	// �ړ��ʂ̐ݒ�
	CEnemy::SetMove(move);

	// �J�E���g�����Z
	m_nCntMove++;
	m_nCntApeer++;
}

//-----------------------------------------------------------------------------------------------
// 2P�ړ�
//-----------------------------------------------------------------------------------------------
void CEnemyRabbit::SecondMove()
{
	// �ʒu�̎擾
	D3DXVECTOR3 pos = CEnemy::GetPosition();

	// �ړ��ʂ̏�����
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �ǂ̈ʒu�ƃT�C�Y���擾
	D3DXVECTOR3 posWall = CWall::GetInstance()->GetPosition();
	D3DXVECTOR3 sizeWall = CWall::GetInstance()->GetSize();

	if (!m_bGet)
	{// �o�����Ԃƃ^�C�}��������������
	 // ���x�̎擾
		m_fSpeed = CEnemy::GetSpeed();

		// �擾����
		m_bGet = true;
	}

	if (m_nCntApeer > ENEMY_RABBIT_APPEA_FREAM && pos.x - (ENEMY_RABBIT_WIDTH / 2.0f) < posWall.x + (sizeWall.x / 2.0f) + 5.0f
		|| m_nCntApeer > ENEMY_RABBIT_APPEA_FREAM && pos.x + (ENEMY_RABBIT_WIDTH / 2.0f) > CRenderer::SCREEN_WIDTH)
	{// x���W���ǂɓ����������A1280.0f�ɂȂ�����
		// �ړ��X�s�[�h���t�����ɂ���
		m_fSpeed *= -1.0f;

		// y���W��60���ɂ���
		pos.y += ENEMY_RABBIT_HEIGHT_MOVE;

		// �ʒu�ݒ�
		CEnemy::SetPosition(pos);
	}

	// �ړ��ʂ̉��Z
	move.x = m_fSpeed;
	move.y = sinf((D3DX_PI / 2.0f) / ENEMY_RABBIT_FRAME * m_nCntMove) * ENEMY_RABBIT_WIDTH_MOVE;

	// �ړ��ʂ̐ݒ�
	CEnemy::SetMove(move);

	// �J�E���g�����Z
	m_nCntMove++;
	m_nCntApeer++;
}