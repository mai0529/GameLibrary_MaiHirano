//---------------------------------------------------------------------------------
//
// ���_�̏���[enemyDeath.cpp]
// Author : ���앑
//
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//---------------------------------------------------------------------------------
#include "enemyDeath.h"		// ���_
#include "game.h"			// �Q�[��
#include "player.h"			// �v���C���[
#include "TextureFileName.h"	// �摜�̃t�@�C����

//---------------------------------------------------------------------------------
// �萔�錾
//---------------------------------------------------------------------------------
// ��
static const float ENEMY_DEATH_WIDTH = 80.0f;
// ����
static const float ENEMY_DEATH_HEIGHT = 80.0f;
// ���x
static const float ENEMY_DEATH_SPEED = 1.7f;
// ���Z���x
static const float ENEMY_DEATH_ADD_SPEED = 0.2f;

//---------------------------------------------------------------------------------
// �ÓI�����o�ϐ��錾
//---------------------------------------------------------------------------------
int CEnemyDeath::m_nCntAppea = 0;

//---------------------------------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------------------------------
CEnemyDeath::CEnemyDeath()
	:m_fSpeed(0.0f)
{
	// �o���񐔂����Z
	m_nCntAppea++;
}

//---------------------------------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------------------------------
CEnemyDeath::~CEnemyDeath()
{
	m_nCntAppea = 0;
}

//---------------------------------------------------------------------------------
// ����
//
// const D3DXVECTOR3& pos �� �ŏ��ɕ\��������W�ʒu
//---------------------------------------------------------------------------------
CEnemyDeath* CEnemyDeath::Create(const D3DXVECTOR3& pos)
{
	// �������𐶐�
	CEnemyDeath* pEnemyDeath = new CEnemyDeath;

	if (pEnemyDeath != nullptr)
	{// nullptr�ł͂Ȃ�������
		// �ʒu
		pEnemyDeath->SetPosition(pos);
		// ������
		pEnemyDeath->Init();
	}

	return pEnemyDeath;
}

//---------------------------------------------------------------------------------
// ������
//
// const D3DXVECTOR3& pos �� �ŏ��ɕ\��������W�ʒu
//---------------------------------------------------------------------------------
HRESULT CEnemyDeath::Init()
{
	// ���x
	m_fSpeed = ENEMY_DEATH_SPEED;

	// �e�N�X�`���̐ݒ�
	CObject2D::LoadTexture(TEX_ENEMY_DEATH);
	//�T�C�Y
	CEnemy::SetSize(D3DXVECTOR3(ENEMY_DEATH_WIDTH, ENEMY_DEATH_HEIGHT, 0.0f));
	// ���
	CEnemy::SetEnemyType(ENEMY_TYPE_DEATH);

	CEnemy::Init();

	return S_OK;
}

//---------------------------------------------------------------------------------
// �I��
//---------------------------------------------------------------------------------
void CEnemyDeath::Uninit()
{
	CEnemy::Uninit();
}

//---------------------------------------------------------------------------------
// �X�V
//---------------------------------------------------------------------------------
void CEnemyDeath::Update()
{
	// �ړ��ʂ̏�����
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �z�[�~���O����
	D3DXVECTOR3 PosDis = Homing();

	// �ړ��ʂ����Z
	move = PosDis * (m_fSpeed + (((m_nCntAppea - 1) / 2) * ENEMY_DEATH_ADD_SPEED));

	// �ړ��ʂ�ݒ�
	CEnemy::SetMove(move);

	CEnemy::Update();
}

//---------------------------------------------------------------------------------
// �`��
//---------------------------------------------------------------------------------
void CEnemyDeath::Draw()
{
	CEnemy::Draw();
}

//---------------------------------------------------------------------------------
// �z�[�~���O
//---------------------------------------------------------------------------------
D3DXVECTOR3 CEnemyDeath::Homing()
{
	// �v���C���[�̃|�C���^
	CPlayer* pPlayer = nullptr;

	pPlayer = CGame::GetPlayer(CObject2D::GetPlayerType());

	// �v���C���[�̈ʒu���擾
	D3DXVECTOR3 PlayerPos = pPlayer->GetPosition();

	// ���_�̏ꏊ���擾
	D3DXVECTOR3 EnemyPos = GetPosition();

	// �����̍������߂�
	D3DXVECTOR3 PosDis = PlayerPos - EnemyPos;

	// ���K������
	D3DXVec3Normalize(&PosDis, &PosDis);

	return PosDis;
}