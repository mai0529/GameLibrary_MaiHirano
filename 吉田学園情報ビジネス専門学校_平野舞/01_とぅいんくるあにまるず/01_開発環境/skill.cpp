//-----------------------------------------------------------------------------------------------
//
// �X�L������[skill.cpp]
// Author : ���앑
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------------------------
#include "skill.h"			// �X�L��
#include "enemy.h"			// �G
#include "enemyManager.h"	// �G�}�l�[�W���[
#include "particle.h"		// �p�[�e�B�N��
#include "TextureFileName.h"	// �摜�̃t�@�C����

//-----------------------------------------------------------------------------------------------
// �萔�錾
//-----------------------------------------------------------------------------------------------
// ��
static const float SKILL_WIDTH = 50.0f;
// ����
static const float SKILL_HEIGHT = 50.0f;
// ���G����
static const int SKILL_TIME = 300;

//-----------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------------------------
CSkill::CSkill()
	:m_bDis(false), m_bUse(false), m_nCntEnemy(0), m_bInvincible(false), m_nInvincible(0)
{

}

//-----------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CSkill::~CSkill()
{

}

//-----------------------------------------------------------------------------------------------
// ����
//-----------------------------------------------------------------------------------------------
CSkill* CSkill::Create(const D3DXVECTOR3& pos)
{
	// �|�C���^�N���X�錾
	CSkill* pSkill = new CSkill;

	if (pSkill != nullptr)
	{// nullptr�ł͂Ȃ�������
		// ����������
		pSkill->Init(pos);
	}

	return pSkill;
}

//-----------------------------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------------------------
HRESULT CSkill::Init(const D3DXVECTOR3& pos)
{
	// �\������
	m_bDis = true;
	// ���G����
	m_nInvincible = SKILL_TIME;
	//�I�u�W�F�N�g�^�C�v��ݒ�
	SetObjectType(EOBJECT_TYPE::EOBJECT_TYPE_SKILL);
	// �e�̐ݒ�
	SetObjectParent(EOBJECT_PARENT::EOBJECT_PARENT_GAME);
	// �e�N�X�`���̐ݒ�
	CObject2D::LoadTexture(TEX_SKILL);
	// �T�C�Y
	CObject2D::SetSize(D3DXVECTOR3(SKILL_WIDTH, SKILL_HEIGHT, 0.0f));

	CObject2D::Init(pos);

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �I��
//-----------------------------------------------------------------------------------------------
void CSkill::Uninit()
{
	CObject2D::Uninit();
}

//-----------------------------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------------------------
void CSkill::Update()
{
	if (m_bInvincible)
	{// ���G��Ԃ�������
		// �J�E���g�����炷
		m_nInvincible--;
	}

	if (m_nInvincible <= 0)
	{// �J�E���g��0�ȉ��ɂȂ�����
		// ���G��Ԃł͂Ȃ�
		m_bInvincible = false;
	}
}

//-----------------------------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------------------------
void CSkill::Draw()
{
	if (m_bDis)
	{
		CObject2D::Draw();
	}
}

//-----------------------------------------------------------------------------------------------
// �h��X�L��
//-----------------------------------------------------------------------------------------------
void CSkill::Defense()
{
	if (!m_bUse)
	{
		// ���G���
		m_bInvincible = true;
		// �\�����Ȃ�
		m_bDis = false;
		// �X�L�����g�p����
		m_bUse = true;
	}
}

//-----------------------------------------------------------------------------------------------
// �X�L��
//-----------------------------------------------------------------------------------------------
void CSkill::Skill(MULTI_TYPE player)
{
	if (m_bUse)
	{// �X�L�����g�p���Ă�����
		return;
	}

	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		// �I�u�W�F�N�g�̃|�C���^
		CObject* pObject = nullptr;

		// �I�u�W�F�N�g���擾
		pObject = CObject::GetObject(nCntObject);

		if (pObject != nullptr)
		{// nulltpr�ł͂Ȃ�������
			if (pObject->GetObjectType() == EOBJECT_TYPE_ENEMY)
			{// ��ނ��G��������
			 // �_�E���L���X�g
				CEnemy* pEnemy = (CEnemy*)pObject;
				D3DXVECTOR3 EnemyPos = pEnemy->GetPosition();

				switch (pEnemy->GetEnemyType())
				{
					// ���ז��G
				case CEnemy::ENEMY_TYPE_CIRCLE:
				case CEnemy::ENEMY_TYPE_STAR:
					if (player != pEnemy->GetPlayerType())
					{
						// �G�̏I��
						CEnemyManager::GetInstance()->DeleteEnemy(pEnemy->GetID());

						// ����( �p�[�e�B�N�� )�̐���
						CParticle::Create(EnemyPos);
					}

					// �G�̐������Z����
					m_nCntEnemy++;
					break;
					// ���_
				case CEnemy::ENEMY_TYPE_DEATH:
					break;
					// ���̑��̓G
				default:
					if (player == pEnemy->GetPlayerType())
					{
						// �G�̏I��
						CEnemyManager::GetInstance()->DeleteEnemy(pEnemy->GetID());

						// ����( �p�[�e�B�N�� )�̐���
						CParticle::Create(EnemyPos);
					}
					// �G�̐������Z����
					m_nCntEnemy++;
					break;
				}
			}
		}
	}

	for (int nCntEnemy = 0; nCntEnemy < (m_nCntEnemy / 4); nCntEnemy++)
	{
		// �ʒu�������_���Ŏw��
		float fPosX = 0.0f;
		float fPosY = rand() % 400 + 200.0f;

		// �G�̎�ނ������_���Ŏw��
		int nEnemyType = rand() % 2 + 3;

		switch (player)
		{
			// 1P
		case MULTI_TYPE_ONE:
			fPosX = rand() % 400 + 100.0f;
			break;
			// 2P
		case MULTI_TYPE_SECOND:
			fPosX = rand() % 400 + 700.0f;
			break;
			// ���̑�
		default:
			break;
		}

		// �G�̔���
		CEnemyManager::GetInstance()->Create(player,nEnemyType, D3DXVECTOR3(fPosX, fPosY,0.0f), 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),1);
	}

	// �\�����Ȃ�
	m_bDis = false;
	// �X�L�����g�p����
	m_bUse = true;
}

//-----------------------------------------------------------------------------------------------
// ���G��Ԃ��ǂ������擾
//-----------------------------------------------------------------------------------------------
bool CSkill:: GetInvincible()
{
	return m_bInvincible;
}