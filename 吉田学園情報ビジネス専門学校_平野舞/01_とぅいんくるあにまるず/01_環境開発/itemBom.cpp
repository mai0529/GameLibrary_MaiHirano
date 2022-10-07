//-----------------------------------------------------------------------------------------------
//
// ���e�^�A�C�e���̏���[enemyBom.cpp]
// Author : ���앑
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------------------------
#include "itemBom.h"			// ���e�^�A�C�e��
#include "application.h"		// �A�v���P�[�V����
#include "renderer.h"			// �����_�����O
#include "enemyManager.h"		// �G�}�l�[�W���[
#include "enemy.h"				// �G
#include "particle.h"			// �p�[�e�B�N��
#include "TextureFileName.h"	// �摜�̃t�@�C����

//-----------------------------------------------------------------------------------------------
// �萔�錾
//-----------------------------------------------------------------------------------------------
// �ړ���
static const float ITEM_BOM_MOVING = 1.0f;
// ���x
static const float ITEM_BOM_SPEED = 2.0f;
// �ړ�����
static const float ITEM_BOM_MOVE = 2.0f;
// �t���[����
static const int ITEM_BOM_FRAME = 90;

//-----------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------------------------
CItemBom::CItemBom()
	:m_nCntMove(0)
{

}

//-----------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CItemBom::~CItemBom()
{

}

//-----------------------------------------------------------------------------------------------
// ����
//-----------------------------------------------------------------------------------------------
CItemBom* CItemBom::Create(const D3DXVECTOR3& pos)
{
	// �|�C���^�N���X��錾
	CItemBom* pItemBom = new CItemBom;

	if (pItemBom != nullptr)
	{// ����nullptr�ł͂Ȃ�������
	 // ������
		pItemBom->Init(pos);
	}

	return pItemBom;
}

//-----------------------------------------------------------------------------------------------
// ������
//
// const D3DXVECTOR3& pos �� �ŏ��ɕ\��������W�ʒu
//-----------------------------------------------------------------------------------------------
HRESULT CItemBom::Init(const D3DXVECTOR3& pos)
{
	// �e�N�X�`���̐ݒ�
	CObject2D::LoadTexture(TEX_ITEM_BOM);

	CItem::Init(pos);

	// ��ނ�ݒ�
	CItem::SetItemType(ITEM_TYPE_BOM);

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �I��
//-----------------------------------------------------------------------------------------------
void CItemBom::Uninit()
{
	CItem::Uninit();
}

//-----------------------------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------------------------
void CItemBom::Update()
{
	D3DXVECTOR3 move = Move();

	// �ړ��ʂ�ݒ�
	CItem::SetMove(move);

	CItem::Update();
}

//-----------------------------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------------------------
void CItemBom::Draw()
{
	CItem::Draw();
}

//-----------------------------------------------------------------------------------------------
// �G��S������
//-----------------------------------------------------------------------------------------------
void CItemBom::DeleteEnemy(MULTI_TYPE player)
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
					break;
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------------------------
// �ړ�
//-----------------------------------------------------------------------------------------------
D3DXVECTOR3 CItemBom::Move()
{
	// �ړ��ʂ̏�����
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �ړ���
	move.x = cosf((D3DX_PI / 2.0f) / ITEM_BOM_FRAME * m_nCntMove) * ITEM_BOM_MOVE;
	move.y = ITEM_BOM_MOVING;

	// �J�E���g�̉��Z
	m_nCntMove++;

	return move;
}