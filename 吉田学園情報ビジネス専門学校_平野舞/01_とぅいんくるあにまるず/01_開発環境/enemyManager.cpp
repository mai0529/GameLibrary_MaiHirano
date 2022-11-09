//---------------------------------------------------------------------------------
//
// �G�}�l�[�W���[�̏���[enemyManager.cpp]
// Author : ���앑
//
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//---------------------------------------------------------------------------------
#include <stdio.h>				// �O���t�@�C���ǂݍ��ݗp
#include "enemyManager.h"		// �G�}�l�[�W���[
#include "enemyRabbit.h"		// �������^�G
#include "enemyCat.h"			// �˂��^�G
#include "enemyDog.h"			// ���ʌ^�G
#include "enemyCircle.h"		// �ۂ̂��ז��G
#include "enemyStar.h"			// ���̂��ז��G
#include "enemyDeath.h"			// ���_
#include "enemyBoss.h"			// �{�X
#include "time.h"				// �^�C�}�[

//---------------------------------------------------------------------------------
// �萔�錾
//---------------------------------------------------------------------------------
// �e�L�X�g�t�@�C��
#define TEXT_ENEMY		("data/TEXT/enemy.txt")

// 1P����2P���̋���
static const float ENEMY_DIS = 700.0f;
// ���Z�b�g����
static const int ENEMY_RESET_TIME = 3;
// ���_�̔����^�C�~���O
static const int ENEMY_DEATH_TIME = 10;

//---------------------------------------------------------------------------------
// �ÓI�����o�ϐ��錾
//---------------------------------------------------------------------------------
// �G�}�l�[�W���[�̃|�C���^
CEnemyManager* CEnemyManager::m_Instance = nullptr;

//---------------------------------------------------------------------------------
//	�R���X�g���N�^
//---------------------------------------------------------------------------------
CEnemyManager::CEnemyManager()
	:m_nCntFileEnemy(0), m_nNowCntEnemy(0),m_bCreate(false)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		// �o���J�E���^�[
		m_aFile[nCntEnemy].nCntApper = 0;
		// �ʒu
		m_aFile[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// �F
		m_aFile[nCntEnemy].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// ���x
		m_aFile[nCntEnemy].fSpeed = 0.0f;
		// ����
		m_aFile[nCntEnemy].nLife = 0;
		// ���
		m_aFile[nCntEnemy].nType = CEnemy::ENEMY_TYPE_RABBIT;
	}

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{// �G�̃|�C���^
		m_pEnemy[nCntEnemy] = nullptr;
	}
}

//---------------------------------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------------------------------
CEnemyManager::~CEnemyManager()
{

}

//---------------------------------------------------------------------------------
// �C���X�^���X�̐���
//---------------------------------------------------------------------------------
void CEnemyManager::CreateInstance()
{
	if (m_Instance == nullptr)
	{// nullptr��������
		// �������𐶐�
		m_Instance = new CEnemyManager;
	}
}

//---------------------------------------------------------------------------------
// �C���X�^���X�̎擾
//---------------------------------------------------------------------------------
CEnemyManager* CEnemyManager::GetInstance()
{
	if (m_Instance != nullptr)
	{// nullptr�ł͂Ȃ�������
		return m_Instance;
	}

	return nullptr;
}

//---------------------------------------------------------------------------------
// �G�̐���
//
// MULTI_TYPE player �� 1P����2P����
// int nType		 �� �G�̎��
// D3DXVECTOR3 pos	 �� �����ʒu
// float fSpeed		 �� �ړ����x
// D3DXCOLOR col	 �� �J���[
// int nLife		 �� ����
//---------------------------------------------------------------------------------
void CEnemyManager::Create(CObject2D::MULTI_TYPE player,int nType, D3DXVECTOR3 pos, float fSpeed, D3DXCOLOR col,int nLife)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (m_pEnemy[nCntEnemy] == nullptr)
		{// nullptr��������
			switch (nType)
			{
				// ������( �ʏ� )
			case CEnemy::ENEMY_TYPE_RABBIT:
			{
				m_pEnemy[nCntEnemy] = CEnemyRabbit::Create(pos);
				// �ړ���
				m_pEnemy[nCntEnemy]->SetSpeed(fSpeed);
				// �F
				m_pEnemy[nCntEnemy]->SetColor(col);
			}
				break;
				// �˂�( �ʏ� )
			case CEnemy::ENEMY_TYPE_CAT:
			{
				m_pEnemy[nCntEnemy] = CEnemyCat::Create(pos);
				// �ړ���
				m_pEnemy[nCntEnemy]->SetSpeed(fSpeed);
				// �F
				m_pEnemy[nCntEnemy]->SetColor(col);
			}
			break;
			// ����( �ʏ� )
			case CEnemy::ENEMY_TYPE_DOG:
			{
				m_pEnemy[nCntEnemy] = CEnemyDog::Create(pos);
				// �ړ���
				m_pEnemy[nCntEnemy]->SetSpeed(fSpeed);
				// �F
				m_pEnemy[nCntEnemy]->SetColor(col);
			}
			break;
				// ��( ���ז� )
			case CEnemy::ENEMY_TYPE_CIRCLE:
			{
				m_pEnemy[nCntEnemy] = CEnemyCircle::Create(pos);
			}
				break;
				// ��( ���ז� )
			case CEnemy::ENEMY_TYPE_STAR:
			{
				m_pEnemy[nCntEnemy] = CEnemyStar::Create(pos);
			}
			break;
				// ���_( �����v���C�h�~ )
			case CEnemy::ENEMY_TYPE_DEATH:
			{
				m_pEnemy[nCntEnemy] = CEnemyDeath::Create(pos);
			}
				break;
				// �{�X
			case CEnemy::ENEMY_TYPE_BOSS:
			{
				m_pEnemy[nCntEnemy] = CEnemyBoss::Create(pos);
			}
			break;
			default:
				break;
			}

			// �i�[��ԍ�
			m_pEnemy[nCntEnemy]->SetID(nCntEnemy);
			// 1P��2P��
			m_pEnemy[nCntEnemy]->SetPlayerType(player);
			// ����
			m_pEnemy[nCntEnemy]->SetLife(nLife);

			break;
		}
	}
}

//---------------------------------------------------------------------------------
// ������
//---------------------------------------------------------------------------------
HRESULT CEnemyManager::Init()
{
	// �O���t�@�C���̓ǂݍ���
	Load();

	return S_OK;
}

//---------------------------------------------------------------------------------
// �I��
//---------------------------------------------------------------------------------
void CEnemyManager::Uninit()
{
	// ���g�̍폜
	Release();

	// nullptr�ɂ���
	m_Instance = nullptr;
}

//---------------------------------------------------------------------------------
// �X�V
//---------------------------------------------------------------------------------
void CEnemyManager::Update()
{
	if (m_nNowCntEnemy <= m_nCntFileEnemy && CTime::GetInstance()->GetTime() == m_aFile[m_nNowCntEnemy].nCntApper)
	{
		// 1P��
		CEnemyManager::Create(CObject2D::MULTI_TYPE_ONE, m_aFile[m_nNowCntEnemy].nType,m_aFile[m_nNowCntEnemy].pos,
			m_aFile[m_nNowCntEnemy].fSpeed, m_aFile[m_nNowCntEnemy].col, m_aFile[m_nNowCntEnemy].nLife);

		// 2P��
		CEnemyManager::Create(CObject2D::MULTI_TYPE_SECOND, m_aFile[m_nNowCntEnemy].nType, D3DXVECTOR3(m_aFile[m_nNowCntEnemy].pos.x + ENEMY_DIS, m_aFile[m_nNowCntEnemy].pos.y,0.0f),
			m_aFile[m_nNowCntEnemy].fSpeed,m_aFile[m_nNowCntEnemy].col, m_aFile[m_nNowCntEnemy].nLife);

		// �J�E���g�𑝂₷
		m_nNowCntEnemy++;
	}
	else if (m_nNowCntEnemy == m_nCntFileEnemy && CTime::GetInstance()->GetTime() == m_aFile[m_nNowCntEnemy - 1].nCntApper + ENEMY_RESET_TIME)
	{
		// �^�C�}�̃��Z�b�g
 		CTime::GetInstance()->ResetTime();
		// ���̓G�J�E���g�̏�����
		m_nNowCntEnemy = 0;
	}

	if (CTime::GetInstance()->GetTime() > 1 && CTime::GetInstance()->GetTime() % ENEMY_DEATH_TIME == 0 && !m_bCreate)
	{
		// ���_�̐���
		CEnemyManager::Create(CObject2D::MULTI_TYPE_ONE, CEnemy::ENEMY_TYPE_DEATH, D3DXVECTOR3(300.0f, 0.0f, 0.0f), 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1);
		CEnemyManager::Create(CObject2D::MULTI_TYPE_SECOND, CEnemy::ENEMY_TYPE_DEATH, D3DXVECTOR3(1000.0f,0.0f,0.0f), 0.0f, D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),1);
		m_bCreate = true;
	}
	if (CTime::GetInstance()->GetTime() % ENEMY_DEATH_TIME == 1 && m_bCreate)
	{
		m_bCreate = false;
	}
}

//---------------------------------------------------------------------------------
// �`��
//---------------------------------------------------------------------------------
void CEnemyManager::Draw()
{

}

//---------------------------------------------------------------------------------
// �G�̍폜
//---------------------------------------------------------------------------------
void CEnemyManager::DeleteEnemy(int nCntEnemy)
{
	int nID = nCntEnemy;

	if (m_pEnemy[nID] != nullptr)
	{// nullptr�ł͂Ȃ�������

		// �I��
		m_pEnemy[nID]->Uninit();

		// nullptr�ɂ���
		m_pEnemy[nID] = nullptr;
	}
}

//---------------------------------------------------------------------------------
// �O���t�@�C���̓ǂݍ���
//---------------------------------------------------------------------------------
void CEnemyManager::Load()
{
	char cData[125];

	// �t�@�C�����J��
	FILE* pFile = fopen(TEXT_ENEMY, "r");

	if (pFile == nullptr)
	{// �t�@�C�����J���Ȃ�������
		printf("�t�@�C�����J���܂���ł����B");
		return;
	}

	while (1)
	{
		// ������ǂݍ���
		fscanf(pFile, "%s", &cData[0]);

		if (strcmp(&cData[0], "ENEMYSET") == 0)
		{// ENEMYSET�̕�������������
			do
			{
				// ������ǂݍ���
				fscanf(pFile, "%s", &cData[0]);

				if (strcmp(&cData[0], "DETAILSET") == 0)
				{
					do
					{
						// ������ǂݍ���
						fscanf(pFile, "%s", &cData[0]);

						if (strcmp(&cData[0], "COUNTER") == 0)
						{// �o���J�E���^�[
							fscanf(pFile, "%s", &cData[0]);
							fscanf(pFile, "%d", &m_aFile[m_nCntFileEnemy].nCntApper);
						}
						else if (strcmp(&cData[0], "POS") == 0)
						{// �ʒu
							fscanf(pFile, "%s", &cData[0]);
							fscanf(pFile, "%f", &m_aFile[m_nCntFileEnemy].pos.x);
							fscanf(pFile, "%f", &m_aFile[m_nCntFileEnemy].pos.y);
							fscanf(pFile, "%f", &m_aFile[m_nCntFileEnemy].pos.z);
						}
						else if (strcmp(&cData[0], "COL") == 0)
						{// �F
							fscanf(pFile, "%s", &cData[0]);
							fscanf(pFile, "%f", &m_aFile[m_nCntFileEnemy].col.r);
							fscanf(pFile, "%f", &m_aFile[m_nCntFileEnemy].col.g);
							fscanf(pFile, "%f", &m_aFile[m_nCntFileEnemy].col.b);
							fscanf(pFile, "%f", &m_aFile[m_nCntFileEnemy].col.a);
						}
						else if (strcmp(&cData[0], "SPEED") == 0)
						{// ���x
							fscanf(pFile, "%s", &cData[0]);
							fscanf(pFile, "%f", &m_aFile[m_nCntFileEnemy].fSpeed);
						}
						else if (strcmp(&cData[0], "LIFE") == 0)
						{// ���C�t
						 // ������ǂݍ���
							fscanf(pFile, "%s", &cData[0]);
							fscanf(pFile, "%d", &m_aFile[m_nCntFileEnemy].nLife);
						}
						else if (strcmp(&cData[0], "TYPE") == 0)
						{// ���
							fscanf(pFile, "%s", &cData[0]);
							fscanf(pFile, "%d", &m_aFile[m_nCntFileEnemy].nType);
						}
					} while (strcmp(&cData[0], "END_DETAILSET") != 0);

					// �J�E���g����
					m_nCntFileEnemy++;
				}
			} while (strcmp(&cData[0], "END_ENEMYSET") != 0);
		}

		if (strcmp(&cData[0], "END_SCRIPT") == 0)
		{// END_ENEMYSET�̕�������������
			break;
		}
	}
}