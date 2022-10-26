//-----------------------------------------------------------------------------------------------
//
// ���̂��ז��G�̏���[enemyStar.cpp]
// Author : ���앑
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------------------------
#include "enemyStar.h"			// ���̂��ז��G
#include "application.h"		// �A�v���P�[�V����
#include "renderer.h"			// �����_�����O
#include "game.h"				// �Q�[��
#include "player.h"				// �v���C���[
#include "TextureFileName.h"	// �摜�̃t�@�C����

//-----------------------------------------------------------------------------------------------
// �萔�錾
//-----------------------------------------------------------------------------------------------
// ��
static const float ENEMY_STAR_WIDTH = 50.0f;
// ����
static const float ENEMY_STAR_HEIGHT = 50.0f;
// �ړ���
static const float ENEMY_STAR_MOVING = -4.0f;
// �t���[����
static const int ENEMY_STAR_FRAME = 120;
// �d��
static const float ENEMY_STAR_GRAVITY = 0.1f;

//-----------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------------------------
CEnemyStar::CEnemyStar()
	:m_move(0.0f,0.0f,0.0f), m_bSetMove(false)
{

}

//-----------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CEnemyStar::~CEnemyStar()
{

}

//-----------------------------------------------------------------------------------------------
// ����
//-----------------------------------------------------------------------------------------------
CEnemyStar* CEnemyStar::Create(const D3DXVECTOR3& pos)
{
	// �|�C���^�N���X��錾
	CEnemyStar* pEnemyStar = new CEnemyStar;

	if (pEnemyStar != nullptr)
	{// ����nullptr�ł͂Ȃ�������
	 // ������
		pEnemyStar->Init(pos);
	}

	return pEnemyStar;
}

//-----------------------------------------------------------------------------------------------
// ������
//
// const D3DXVECTOR3& pos �� �ŏ��ɕ\��������W�ʒu
//-----------------------------------------------------------------------------------------------
HRESULT CEnemyStar::Init(const D3DXVECTOR3& pos)
{
	// �e�N�X�`���̐ݒ�
	CObject2D::LoadTexture(TEX_ENEMY_STAR);
	//�T�C�Y
	CEnemy::SetSize(D3DXVECTOR3(ENEMY_STAR_WIDTH, ENEMY_STAR_HEIGHT, 0.0f));
	// ���
	CEnemy::SetEnemyType(ENEMY_TYPE_STAR);

	CEnemy::Init(pos);

	// ���_�J���[
	CObject2D::SetColor(D3DXCOLOR(3.0f, 1.0f, 0.0f, 1.0f));

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �I��
//-----------------------------------------------------------------------------------------------
void CEnemyStar::Uninit()
{
	CEnemy::Uninit();
}

//-----------------------------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------------------------
void CEnemyStar::Update()
{
	if (!m_bSetMove)
	{// �ړ��ʂ�ݒ肵�Ă��Ȃ�������
		Move();
	}

	// �d�͉��Z
	m_move.y += ENEMY_STAR_GRAVITY;

	// �ړ��ʂ�ݒ�
	CEnemy::SetMove(m_move);

	CEnemy::Update();
}

//-----------------------------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------------------------
void CEnemyStar::Draw()
{
	CEnemy::Draw();
}

//-----------------------------------------------------------------------------------------------
// ����
//-----------------------------------------------------------------------------------------------
void CEnemyStar::Move()
{
	// �ʒu���擾
	D3DXVECTOR3 pos = CObject2D::GetPosition();

	//�ʒu�̍�
	D3DXVECTOR3 posDis = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �v���C���[�̃|�C���^
	CPlayer* pPlayer = nullptr;

	// �v���C���[�̈ʒu
	D3DXVECTOR3 PlayerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	switch (CObject2D::GetPlayerType())
	{
		// 1P��
	case MULTI_TYPE_ONE:
		// �v���C���[�̏����擾
		pPlayer = CGame::GetPlayer(MULTI_TYPE_SECOND -1);
		break;
		// 2P��
	case MULTI_TYPE_SECOND:
		// �v���C���[�̏����擾
		pPlayer = CGame::GetPlayer(MULTI_TYPE_ONE - 1);
		break;
		// ���̑�
	default:
		break;
	}

	// �ʒu�̎擾
	PlayerPos = pPlayer->GetPosition();

	// �����̍�
	posDis = PlayerPos - pos;

	// �ړ��ʂ̉��Z
	m_move.x = posDis.x / ENEMY_STAR_FRAME;
	m_move.y = (posDis.y - (0.5f * ENEMY_STAR_FRAME * ENEMY_STAR_FRAME * ENEMY_STAR_GRAVITY)) / ENEMY_STAR_FRAME;

	// �ړ��ʂ�ݒ肵��
	m_bSetMove = true;
}