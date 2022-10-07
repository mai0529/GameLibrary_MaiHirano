//-----------------------------------------------------------------------------------------------
//
// �p�[�e�B�N���̏���[particle.cpp]
// Author : ���앑
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------------------------
#include "particle.h"		// �p�[�e�B�N��
#include "effect.h"			// �G�t�F�N�g
#include "application.h"	// �A�v���P�[�V����
#include "renderer.h"		// �����_�����O
#include "object2D.h"		// 2D�I�u�W�F�N�g
#include "enemyManager.h"	// �G�}�l�[�W���[
#include "enemy.h"			// �G
#include "time.h"			// �^�C�}

//-----------------------------------------------------------------------------------------------
// �萔�錾
//-----------------------------------------------------------------------------------------------
// ��
static const float PARTICLE_WIDTH = 13.0f;
// ����
static const float PARTICLE_HEIGHT = 13.0f;
// �p�x
static const int PARTICLE_ANGLE = 628;
// ����
static const int PARTICLE_MAX_LIFE = 40;
//�~�̓����蔻��̔��a
static const float COLLISION_RADIUS = 60.0f;

//-----------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//-----------------------------------------------------------------------------------------------
// �e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 CParticle::m_pTexture = nullptr;
// �A����
int CParticle::m_nChain = 0;
// ��������
int CParticle::m_nCreateTime = 0;
// �O��̐�������
int CParticle::m_nCreateTimeOld = 0;

//-----------------------------------------------------------------------------------------------
//�@�R���X�g���N�^
//-----------------------------------------------------------------------------------------------
CParticle::CParticle()
	:m_paEffect(nullptr), m_pos(0.0f,0.0f,0.0f),m_nLife(0), m_AddSize(0.0f)
{

}

//-----------------------------------------------------------------------------------------------
//�@�f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CParticle::~CParticle()
{

}

//-----------------------------------------------------------------------------------------------
// ����
//-----------------------------------------------------------------------------------------------
CParticle* CParticle::Create(const D3DXVECTOR3& pos)
{
	// �|�C���^��錾
	CParticle* pParticle = new CParticle;

	if (pParticle != nullptr)
	{// nullptr�ł͂Ȃ�������
	 // ����������
		pParticle->Init(D3DXVECTOR3(pos));
	}

	return pParticle;
}

//-----------------------------------------------------------------------------------------------
//�@������
//-----------------------------------------------------------------------------------------------
HRESULT CParticle::Init(const D3DXVECTOR3& pos)
{
	// �ʒu
	m_pos = pos;
	// ����
	m_nLife = PARTICLE_MAX_LIFE;
	// �I�u�W�F�N�g�̎�ނ�ݒ�
	SetObjectType(OBJECT_TYPE::OBJECT_TYPE_PARTICLE);

	// �O��̐������Ԃ�ݒ�
	m_nCreateTimeOld = m_nCreateTime;

	// �������Ԃ��擾
	m_nCreateTime = CTime::GetInstance()->GetTime();

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
//�@�I��
//-----------------------------------------------------------------------------------------------
void CParticle::Uninit()
{
	// �I�u�W�F�N�g�̔j��
	Relese();
}

//-----------------------------------------------------------------------------------------------
//�@�X�V
//-----------------------------------------------------------------------------------------------
void CParticle::Update()
{
	// �����Ŋp�x��ݒ�
	int fAngle = rand() % PARTICLE_ANGLE;

	// �����ŐF��ݒ�
	float fColR = (rand() % 100) / 100.0f;
	float fColG = (rand() % 100) / 100.0f;
	float fColB = (rand() % 100) / 100.0f;

	// �G�t�F�N�g
	m_paEffect = CEffect::Create(m_pos);
	// �I�u�W�F�N�g�̎�ނ�ݒ�
	m_paEffect->SetObjectType(OBJECT_TYPE::OBJECT_TYPE_PARTICLE);
	// �e�̐ݒ�
	m_paEffect->SetObjectParent(OBJECT_PARENT::OBJECT_PARENT_GAME);
	// �T�C�Y��ݒ�
	m_paEffect->SetSize(D3DXVECTOR3(PARTICLE_WIDTH + m_AddSize, PARTICLE_HEIGHT + m_AddSize, 0.0f));
	// �p�x��ݒ�
	m_paEffect->SetAngle(fAngle / 100.0f);
	// �F�̐ݒ�
	m_paEffect->SetColor(D3DXCOLOR(fColR, fColG, fColB, 1.0f));

	if (m_nCreateTime - m_nCreateTimeOld > 2)
	{// ��莞�Ԃ��o������
		// �A����������
		m_nChain = 0;
	}

	// �����蔻��
	CollisionEnemy(m_pos);

	// �T�C�Y��傫������
	m_AddSize += 0.2f;

	// ���������炷
	m_nLife--;

	if (m_nLife == 0)
	{// ������0�ɂȂ�����
		// �I������
		Uninit();
	}
}

//-----------------------------------------------------------------------------------------------
//�@�`��
//-----------------------------------------------------------------------------------------------
void CParticle::Draw()
{

}

//-----------------------------------------------------------------------------------------------
// �A��
//-----------------------------------------------------------------------------------------------
void CParticle::Chain(MULTI_TYPE type, const D3DXVECTOR3& pos)
{
	if (m_nCreateTime - m_nCreateTimeOld <= 2)
	{// ���Z����
		m_nChain++;
	}

	if (m_nChain > 1 && m_nChain % 4 == 0)
	{// 4�̔{���ɂȂ�����
	 // �G�̎�ނ������_���Ŏw��
		int nEnemyType = rand() % 2 + 3;

		// ���ז��G�̔���
		CEnemyManager::GetInstance()->Create(type, nEnemyType,pos,0,D3DXCOLOR(1.0f,1.0f,0.0f,1.0f),1);
	}
}

//-----------------------------------------------------------------------------------------------
// �G�Ƃ̓����蔻��
//-----------------------------------------------------------------------------------------------
void CParticle::CollisionEnemy(const D3DXVECTOR3& pos)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		// �I�u�W�F�N�g�̃|�C���^
		CObject* pObject = nullptr;

		// �I�u�W�F�N�g���擾
		pObject = CObject::GetObject(nCntObject);

		if (pObject != nullptr)
		{// nulltpr�ł͂Ȃ�������
			if (pObject->GetObjectType() == OBJECT_TYPE_ENEMY)
			{// ��ނ��G��������
			 // �_�E���L���X�g
				CEnemy* pEnemy = (CEnemy*)pObject;

				if (pEnemy->GetEnemyType() != CEnemy::ENEMY_TYPE_CIRCLE && pEnemy->GetEnemyType() != CEnemy::ENEMY_TYPE_STAR)
				{ // �G�����ז��ȊO��������
					// �ʒu���擾����
					D3DXVECTOR3 pEnemyPos = pEnemy->GetPosition();

					// 1P����2P�������擾����
					MULTI_TYPE Type = pEnemy->GetPlayerType();

					// �����̍������߂�
					D3DXVECTOR3 PosDis = pEnemyPos - pos;

					// ���������߂�
					float fLength = D3DXVec3Length(&PosDis);

					if (COLLISION_RADIUS >= fLength)
					{// �����������̍������Z��������
						//�G�̏I��
						CEnemyManager::GetInstance()->DeleteEnemy(pEnemy->GetID());
						// ����( �p�[�e�B�N�� )����
						CParticle::Create(pEnemyPos);
						// �A��
						Chain(Type, pEnemyPos);
						break;
					}
				}
			}
		}
	}
}