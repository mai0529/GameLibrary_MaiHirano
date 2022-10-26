//-----------------------------------------------------------------------------------------------
//
// �e�̏���[bullet.cpp]
// Author : ���앑
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------------------------
#include "bullet.h"			// �v���C���[
#include "application.h"	// �A�v���P�[�V����
#include "renderer.h"		// �����_�����O
#include "enemy.h"			// �G
#include "sound.h"			// ��
#include "TextureFileName.h"	// �摜�̃t�@�C����

//-----------------------------------------------------------------------------------------------
// �ϐ��ϐ�
//-----------------------------------------------------------------------------------------------
// ��
static const float BULLET_WIDTH = 40.0f;
// ����
static const float BULLET_HEIGHT = 40.0f;
// �ړ���
static const float BULLET_MOVING = -4.0f;
// ����
static const int BULLET_LIFE = 100;

//-----------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//-----------------------------------------------------------------------------------------------
// �G�t�F�N�g�̃|�C���^
CEffect* CBullet::m_pEffect = nullptr;

//-----------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------------------------
CBullet::CBullet()
	:m_move(0.0f, 0.0f, 0.0f), m_nLife(0)
{

}

//-----------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CBullet::~CBullet()
{

}

//-----------------------------------------------------------------------------------------------
// ����
//
// const D3DXVECTOR3& pos �� ����������W�ʒu
//-----------------------------------------------------------------------------------------------
CBullet* CBullet::Create(MULTI_TYPE playerType, const D3DXVECTOR3& pos)
{
	// �|�C���^�N���X��錾
	CBullet* pBullet = new CBullet;

	if (pBullet != nullptr)
	{// ����nullptr�ł͂Ȃ�������
		// 1P��2P��
		pBullet->SetPlayerType(playerType);
	 // ������
		pBullet->Init(pos);
	}

	return pBullet;
}

//-----------------------------------------------------------------------------------------------
// ������
//
// const D3DXVECTOR3& pos �� �ŏ��ɕ\��������W�ʒu
//-----------------------------------------------------------------------------------------------
HRESULT CBullet::Init(const D3DXVECTOR3& pos)
{
	// �ړ���
	m_move.y = BULLET_MOVING;
	// ����
	m_nLife = BULLET_LIFE;

	// �I�u�W�F�N�g�̎��
	CObject::SetObjectType(EOBJECT_TYPE_BULLET);
	// �I�u�W�F�N�g�̐e
	CObject::SetObjectParent(EOBJECT_PARENT_GAME);

	// �e�N�X�`���̐ݒ�
	CObject2D::LoadTexture(TEX_BULLET);

	// �T�C�Y
	CObject2D::SetSize(D3DXVECTOR3(BULLET_WIDTH, BULLET_HEIGHT, 0.0f));

	CObject2D::Init(pos);

	// �F�̐ݒ�
	switch (CObject2D::GetPlayerType())
	{
		// 1P
	case MULTI_TYPE_ONE:
		CObject2D::SetColor(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
		break;
		// 2P
	case MULTI_TYPE_SECOND:
		CObject2D::SetColor(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
		break;
	}

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �I��
//-----------------------------------------------------------------------------------------------
void CBullet::Uninit()
{
	CObject2D::Uninit();
}

//-----------------------------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------------------------
void CBullet::Update()
{
	// �ʒu�̎擾
	D3DXVECTOR3 pos = CObject2D::GetPosition();

	// �ړ��ʂ̍X�V
	pos += m_move;

	// �����蔻��
	Collision(pos);

	//���C�t�����炵�Ă���
	m_nLife--;

	if (m_nLife <= 0)
	{// ���C�t��0�ɂȂ�����
		// �I������
		Uninit();
	}
	else
	{
		// �ʒu�̍X�V
		CObject2D::SetPosition(pos);
		CObject2D::UpdatePos();
	}
}

//-----------------------------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------------------------
void CBullet::Draw()
{
	CObject2D::Draw();
}

//-----------------------------------------------------------------------------------------------
// �����蔻��
//-----------------------------------------------------------------------------------------------
void CBullet::Collision(const D3DXVECTOR3& pos)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		// �I�u�W�F�N�g�̃|�C���^
		CObject* pObject = nullptr;

		// �I�u�W�F�N�g���擾
		pObject = CObject::GetObject(nCntObject);

		if (pObject == nullptr)
		{// nulltpr��������
			break;
		}

		if (pObject->GetObjectType() == EOBJECT_TYPE_ENEMY)
		{// ��ނ��G�ł͂Ȃ�������
			// �_�E���L���X�g
			CEnemy* pEnemy = (CEnemy*)pObject;

			// �ʒu�̎擾
			D3DXVECTOR3 EnemyPos = pEnemy->GetPosition();
			D3DXVECTOR3 EnemySize = pEnemy->GetSize();

			if ((EnemyPos.x + EnemySize.x >= pos.x - (BULLET_WIDTH / 2.0f)
				&& EnemyPos.x - EnemySize.x <= pos.x + (BULLET_WIDTH / 2.0f)
				&& EnemyPos.y + EnemySize.y >= pos.y - (BULLET_HEIGHT / 2.0f)
				&& EnemyPos.y - EnemySize.y <= pos.y + (BULLET_HEIGHT / 2.0f)))
			{// �����蔻��
				if ((pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE_CIRCLE || pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE_STAR)
					&& pEnemy->GetPlayerType() != GetPlayerType())
				{// ���ז��G��������
				 // ���C�t��0�ɂ���
					m_nLife = 0;

					// �G�Ƀq�b�g
					pEnemy->Hit(1);

					// ���̍Đ�
					CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_ENEMYDAMAGE);
					break;
				}
				else if (pEnemy->GetEnemyType() != CEnemy::ENEMY_TYPE_CIRCLE && pEnemy->GetEnemyType() != CEnemy::ENEMY_TYPE_STAR
					&& CObject2D::GetPlayerType() == pEnemy->GetPlayerType())
				{ // �G�����ז��ȊO��������
					// ���C�t��0�ɂ���
					m_nLife = 0;

					// �G�Ƀq�b�g
					pEnemy->Hit(1);

					// ���̍Đ�
					CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_ENEMYDAMAGE);
					break;
				}
			}
		}
	}
}