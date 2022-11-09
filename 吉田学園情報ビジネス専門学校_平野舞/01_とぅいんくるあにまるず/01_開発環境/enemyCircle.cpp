//-----------------------------------------------------------------------------------------------
//
// ������܌^�G�̏���[enemyCircle.cpp]
// Author : ���앑
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------------------------
#include "enemyCircle.h"	// �ۂ̂��ז��G
#include "application.h"	// �A�v���P�[�V����
#include "renderer.h"		// �����_�����O
#include "game.h"			// �Q�[��
#include "player.h"			// �v���C���[
#include "TextureFileName.h"	// �摜�̃t�@�C����

//-----------------------------------------------------------------------------------------------
// �萔�錾
//-----------------------------------------------------------------------------------------------
// ��
static const float ENEMY_CIRCLE_WIDTH = 50.0f;
// ����
static const float ENEMY_CIRCLE_HEIGHT = 50.0f;
// �ړ���
static const float ENEMY_CIRCLE_MOVING = 4.0f;


//-----------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------------------------
CEnemyCircle::CEnemyCircle()
	:m_bSetMove(false),m_bAttack(false)
{

}

//-----------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CEnemyCircle::~CEnemyCircle()
{

}

//-----------------------------------------------------------------------------------------------
// ����
//-----------------------------------------------------------------------------------------------
CEnemyCircle* CEnemyCircle::Create(const D3DXVECTOR3& pos)
{
	// �|�C���^�N���X��錾
	CEnemyCircle* pEnemyCircle = new CEnemyCircle;

	if (pEnemyCircle != nullptr)
	{// ����nullptr�ł͂Ȃ�������
		// �ʒu
		pEnemyCircle->SetPosition(pos);
		// ������
		pEnemyCircle->Init();
	}

	return pEnemyCircle;
}

//-----------------------------------------------------------------------------------------------
// ������
//
// const D3DXVECTOR3& pos �� �ŏ��ɕ\��������W�ʒu
//-----------------------------------------------------------------------------------------------
HRESULT CEnemyCircle::Init()
{
	// �e�N�X�`���̐ݒ�
	CObject2D::LoadTexture(TEX_ENEMY_CIRCLE);
	//�T�C�Y
	CEnemy::SetSize(D3DXVECTOR3(ENEMY_CIRCLE_WIDTH, ENEMY_CIRCLE_HEIGHT, 0.0f));
	// ���
	CEnemy::SetEnemyType(ENEMY_TYPE_CIRCLE);

	CEnemy::Init();

	// ���_�J���[
	CObject2D::SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �I��
//-----------------------------------------------------------------------------------------------
void CEnemyCircle::Uninit()
{
	CEnemy::Uninit();
}

//-----------------------------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------------------------
void CEnemyCircle::Update()
{
	if (!m_bSetMove)
	{// �ړ��ʂ�ݒ�
		switch (CObject2D::GetPlayerType())
		{
			// 1P��
		case MULTI_TYPE_ONE:
			CEnemy::SetMove(D3DXVECTOR3(ENEMY_CIRCLE_MOVING, -ENEMY_CIRCLE_MOVING, 0.0f));
			break;
			//2P��
		case MULTI_TYPE_SECOND:
			CEnemy::SetMove(D3DXVECTOR3(-ENEMY_CIRCLE_MOVING, -ENEMY_CIRCLE_MOVING, 0.0f));
			break;
		default:
			break;
		}

		// �ړ��ʂ�ݒ肵��
		m_bSetMove = true;
	}

	if (!m_bAttack)
	{// ��ʏ�ɓ������Ă��Ȃ�������
		// �ړ�
		Move();
	}

	CEnemy::Update();
}

//-----------------------------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------------------------
void CEnemyCircle::Draw()
{
	CEnemy::Draw();
}

//-----------------------------------------------------------------------------------------------
// ����
//-----------------------------------------------------------------------------------------------
void CEnemyCircle::Move()
{
	// �ʒu���擾
	D3DXVECTOR3 pos = CObject2D::GetPosition();

	// �ړ��ʂ̏�����
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �����̍�
	D3DXVECTOR3 posDis = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �v���C���[�̃|�C���^
	CPlayer* pPlayer = nullptr;

	switch (CObject2D::GetPlayerType())
	{
		// 1P��
	case MULTI_TYPE_ONE:
		// �v���C���[�����擾
		pPlayer = CGame::GetPlayer(MULTI_TYPE_SECOND - 1);
		break;
		// 2P��
	case MULTI_TYPE_SECOND:
		// �v���C���[�����擾
		pPlayer = CGame::GetPlayer(MULTI_TYPE_ONE - 1);
		break;
		// ���̑�
	default:
		break;
	}

	if (pos.y - (ENEMY_CIRCLE_HEIGHT / 2.0f) < 0.0f)
	{// ��ʏ�ɓ���������
		// �����̍������߂�
		posDis = pPlayer->GetPosition() - CEnemy::GetPosition();

		// ���K��
		D3DXVec3Normalize(&posDis, &posDis);

		// �ړ���
		move.x = posDis.x * ENEMY_CIRCLE_MOVING;
		move.y = posDis.y * ENEMY_CIRCLE_MOVING;

		// ��ʂ̏�ɓ�������
		m_bAttack = true;

		// �ړ��ʂ�ݒ�
		CEnemy::SetMove(move);
	}
}