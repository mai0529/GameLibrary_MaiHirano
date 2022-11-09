//-----------------------------------------------------------------------------------------------
//
// �v���C���[�̏���[player.cpp]
// Author : ���앑
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------------------------
#include "player.h"				// �v���C���[
#include "application.h"		// �A�v���P�[�V����
#include "game.h"				// �Q�[��
#include "renderer.h"			// �����_�����O
#include "VirtualController.h"	// ���z�R���g���[���[
#include "bullet.h"				// �e
#include "enemy.h"				// �G
#include "life.h"				// ���C�t
#include "particle.h"			// �p�[�e�B�N��
#include "wall.h"				// ��
#include "item.h"				// �A�C�e��
#include "itemManager.h"		// �A�C�e���}�l�[�W���[
#include "skill.h"				// �X�L��
#include "fade.h"				// �t�F�[�h
#include "sound.h"				// ��
#include "TextureFileName.h"	// �摜�̃t�@�C����

//-----------------------------------------------------------------------------------------------
// �萔�錾
//-----------------------------------------------------------------------------------------------
// ��
static const float PLAYER_WIDTH = 60.0f;
// ����
static const float PLAYER_HEIGHT = 80.0f;
// �ړ�����
static const float PLAYER_DIS = 0.8f;
// ����(����)
static const float PLAYER_INTERTIA = 0.08f;
// �����̍ő吔
static const int PLAYER_MAX_LIFE = 3;
// �_�ŃJ�E���^�[
static const int PLAYER_BLINK = 60;
// �_�ł̊���
static const int PLAYER_RATIO = 20;
// ���S�J�E���^�[
static const int PLAYER_DEATH_COUNT = 60;

//-----------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------------------------
CPlayer::CPlayer()
	: m_pSkill(nullptr), m_posOld(0.0f,0.0f,0.0f),m_move(0.0f,0.0f,0.0f), m_nLife(0), m_state(PLAYER_STATE_NONE), m_nCntBlink(0), m_nCntDeath(0)
{

}

//-----------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CPlayer::~CPlayer()
{

}

//-----------------------------------------------------------------------------------------------
// ����
//
//const D3DXVECTOR3& pos �� ����������W�ʒu
//-----------------------------------------------------------------------------------------------
CPlayer* CPlayer::Create(MULTI_TYPE player,const D3DXVECTOR3& pos)
{
	// �|�C���^�N���X��錾
	CPlayer* pPlayer = new CPlayer;

	if (pPlayer != nullptr)
	{// ����nullptr�ł͂Ȃ�������
		 // 1P��2P��
		pPlayer->SetPlayerType(player);
		// �ʒu
		pPlayer->SetPosition(pos);
		// ������
		pPlayer->Init();
	}

	return pPlayer;
}

//-----------------------------------------------------------------------------------------------
// ������
//
// const D3DXVECTOR3& pos �� �ŏ��ɕ\��������W�ʒu
//-----------------------------------------------------------------------------------------------
HRESULT CPlayer::Init()
{
	// ����
	m_nLife = PLAYER_MAX_LIFE;
	// �_�ŃJ�E���^�[
	m_nCntBlink = PLAYER_BLINK;
	// ���
	m_state = PLAYER_STATE_NORMAL;

	//�I�u�W�F�N�g�^�C�v��ݒ�
	SetObjectType(EOBJECT_TYPE::EOBJECT_TYPE_PLAYER);

	// �e�N�X�`���̐ݒ�
	switch (CObject2D::GetPlayerType())
	{
		// 1P
	case MULTI_TYPE_ONE:
		CObject2D::LoadTexture(TEX_PLAYER_ONE);
		break;
		// 2P
	case MULTI_TYPE_SECOND:
		CObject2D::LoadTexture(TEX_PLAYER_SECOND);
		break;
	default:
		break;
	}
	
	// �T�C�Y
	CObject2D::SetSize(D3DXVECTOR3(PLAYER_WIDTH, PLAYER_HEIGHT, 0.0f));

	CObject2D::Init();

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �I��
//-----------------------------------------------------------------------------------------------
void CPlayer::Uninit()
{
	CObject2D::Uninit();
}

//-----------------------------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------------------------
void CPlayer::Update()
{
	// ���
	State();

	if (m_nLife <= 0)
	{// ������0�ȉ��Ȃ�
		return;
	}
	
	// �ʒu�̎擾
	D3DXVECTOR3 pos = CObject2D::GetPosition();

	// �O�t���[���̏���ۑ�
	m_posOld = pos;

	Shoot(CObject2D::GetPlayerType(), pos);
	Skill(CObject2D::GetPlayerType());
	Move(CObject2D::GetPlayerType());

	// �ړ��ʂ̍X�V
	pos += m_move;

	// �ړ��ʂ��X�V(����������)
	m_move.x += (0.0f - m_move.x) * PLAYER_INTERTIA;
	m_move.y += (0.0f - m_move.y) * PLAYER_INTERTIA;

	// �����蔻��
	if (m_state == PLAYER_STATE_NORMAL)
	{// �ʏ��Ԃ�������
		CollisionEnemy(pos);
	}

	// �A�C�e���̓����蔻��
	CollisionItem(pos);

	// �ǂ̓����蔻��
	pos = CollisionWall(pos);

	// ��ʊO�����蔻��
	pos = OffScreen(pos);

	// �ʒu�̍X�V
	CObject2D::SetPosition(pos);
	CObject2D::UpdatePos();
}

//-----------------------------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------------------------
void CPlayer::Draw()
{
	CObject2D::Draw();
}

//-----------------------------------------------------------------------------------------------
// �����̎擾
//-----------------------------------------------------------------------------------------------
int CPlayer::GetLife()
{
	return m_nLife;
}

//-----------------------------------------------------------------------------------------------
// ���
//-----------------------------------------------------------------------------------------------
void CPlayer::State()
{
	switch (m_state)
	{
		// �ʏ���
	case PLAYER_STATE_NORMAL:
		break;
		// ���G���
	case PLAYER_STATE_INVINCIBLE:
		// �F��ύX
		CObject2D::SetColor(D3DXCOLOR(0.7f, 1.0f, 0.0f, 1.0f));
		break;
		// �_���[�W���
	case PLAYER_STATE_DAMAGE:
		// �_�ł���
		Blink();
		// �J�E���g�����炷
		m_nCntBlink--;
		break;
		// ���S���
	case PLAYER_STATE_DEATH:
		// �e��ݒ�
		CObject::SetObjectParent(CObject::EOBJECT_PARENT_PAUSE);

		// �������~�߂�
		CObject::SetPause(true);

		// �J�E���g�����Z
		m_nCntDeath++;

		// �v���C���[�̐F��ς���
		CObject2D::SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

		if (m_nCntDeath > PLAYER_DEATH_COUNT && CFade::GetInstance()->GetFade() == CFade::FADE_NONE)
		{// �J�E���g�����̒l�ɂȂ��ăt�F�[�h���Ă��Ȃ�������
			// ���U���g��ʂɈڍs
			CFade::GetInstance()->SetFade(CApplication::MODE_RESULT);
		}
		break;
	default:
		break;
	}
}

//-----------------------------------------------------------------------------------------------
// �q�b�g
//-----------------------------------------------------------------------------------------------
void CPlayer::Hit(int nDamage)
{
	// ���������炷
	m_nLife -= nDamage;

	if (m_nLife > 0)
	{// ���C�t��0�ȏゾ������
	 // �_���[�W��Ԃɂ���
		m_state = PLAYER_STATE_DAMAGE;

		// ���C�t�̃|�C���^
		CLife* pLife = nullptr;

		//���C�t�����擾
		pLife = CGame::GetLife(CObject2D::GetPlayerType());

		for (int nCntLife = PLAYER_MAX_LIFE - 1; nCntLife > m_nLife - 1; nCntLife--)
		{// ���C�t�����炷
			pLife->Delete(nCntLife);
		}
	}
	else if (m_nLife <= 0)
	{// ���C�t��0�ȉ��ɂȂ�����
		// ���S��Ԃɂ���
		m_state = PLAYER_STATE_DEATH;
	}
}

//-----------------------------------------------------------------------------------------------
// �_��
//-----------------------------------------------------------------------------------------------
void CPlayer::Blink()
{
	if (m_nCntBlink % PLAYER_RATIO == 0)
	{
		CObject2D::SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}

	if (m_nCntBlink % PLAYER_RATIO == 10)
	{
			CObject2D::SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}

	if (m_nCntBlink == 0)
	{// �J�E���g��0�ɂȂ�����
		//�F�����ɖ߂�
		CObject2D::SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		// �ʏ��Ԃɖ߂�
		m_state = PLAYER_STATE_NORMAL;

		// �J�E���g��߂�
		m_nCntBlink = PLAYER_BLINK;
	}
}

//-----------------------------------------------------------------------------------------------
// �e�̔���
//
// int nPlayer			  �� 1P��2P��
// const D3DXVECTOR3& pos �� �e���o��ʒu
//-----------------------------------------------------------------------------------------------
void CPlayer::Shoot(int nPlayer,const D3DXVECTOR3& pos)
{
	if (CVController::GetInstance()->GetTrigger(nPlayer,CVController::VIRTUAL_KEY_B))
	{// �e���o��
		CBullet::Create(CObject2D::GetPlayerType(),pos);
		// ���̍Đ�
		CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_BULLET);
	}
}

//-----------------------------------------------------------------------------------------------
// �X�L������
//
// int nPlayer �� 1P��2P��
//-----------------------------------------------------------------------------------------------
void CPlayer::Skill(int nPlayer)
{
	if (CVController::GetInstance()->GetTrigger(nPlayer, CVController::VIRTUAL_KEY_A))
	{// �X�L��
		m_pSkill = CGame::GetSkill(nPlayer);
		m_pSkill->Skill(CObject2D::GetPlayerType());

		// ���̍Đ�
		CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_SKILL);
	}
}

//-----------------------------------------------------------------------------------------------
// �ړ�
//
// int nPlayer �� ��P��
//-----------------------------------------------------------------------------------------------
void CPlayer::Move(int nPlayer)
{
	// �R���g���[���[�X�e�B�b�N�����擾
	D3DXVECTOR3 Stick = CVController::GetInstance()->GetStickDir(nPlayer);

	if (CVController::GetInstance()->GetPress(nPlayer, CVController::VIRTUAL_KEY_RIGHT)
		|| CVController::GetInstance()->GetStickPress(nPlayer, CVController::VIRTUAL_STICK_RIGHT))
	{
		if (CVController::GetInstance()->GetPress(nPlayer,CVController::VIRTUAL_KEY_UP))
		{// �E��
			m_move.x += sinf(D3DX_PI / 4.0f * 3.0f) * PLAYER_DIS;
			m_move.y += cosf(D3DX_PI / 4.0f * 3.0f) * PLAYER_DIS;
		}
		else if (CVController::GetInstance()->GetPress(nPlayer,CVController::VIRTUAL_KEY_DOWN))
		{// �E��
			m_move.x += sinf(D3DX_PI / 4.0f) * PLAYER_DIS;
			m_move.y += cosf(D3DX_PI / 4.0f) * PLAYER_DIS;
		}
		else if (CVController::GetInstance()->GetStickPress(nPlayer, CVController::VIRTUAL_STICK_UP) ||
			CVController::GetInstance()->GetStickPress(nPlayer, CVController::VIRTUAL_STICK_DOWN))
		{// �R���g���[���[�̎΂�
			m_move.x += Stick.x * PLAYER_DIS;
			m_move.y -= Stick.y * PLAYER_DIS;
		}
		else
		{// �E
			m_move.x += sinf(D3DX_PI / 2.0f) * PLAYER_DIS;
			m_move.y += cosf(D3DX_PI / 2.0f) * PLAYER_DIS;
		}
	}
	else if (CVController::GetInstance()->GetPress(nPlayer,CVController::VIRTUAL_KEY_LEFT)
		|| CVController::GetInstance()->GetStickPress(nPlayer,CVController::VIRTUAL_STICK_LEFT))
	{
		if (CVController::GetInstance()->GetPress(nPlayer,CVController::VIRTUAL_KEY_UP))
		{// ����
			m_move.x += sinf(-D3DX_PI / 4.0f * 3.0f) * PLAYER_DIS;
			m_move.y += cosf(-D3DX_PI / 4.0f * 3.0f) * PLAYER_DIS;
		}
		else if (CVController::GetInstance()->GetPress(nPlayer,CVController::VIRTUAL_KEY_DOWN))
		{// ����
			m_move.x += sinf(-D3DX_PI / 4.0f) * PLAYER_DIS;
			m_move.y += cosf(-D3DX_PI / 4.0f) * PLAYER_DIS;
		}
		else if (CVController::GetInstance()->GetStickPress(nPlayer,CVController::VIRTUAL_STICK_UP) ||
		CVController::GetInstance()->GetStickPress(nPlayer,CVController::VIRTUAL_STICK_DOWN))
		{// �R���g���[���[�̎΂�
			m_move.x += Stick.x * PLAYER_DIS;
			m_move.y -= Stick.y * PLAYER_DIS;
		}
		else
		{// ��
			m_move.x += sinf(-D3DX_PI / 2.0f) * PLAYER_DIS;
			m_move.y += cosf(-D3DX_PI / 2.0f) * PLAYER_DIS;
		}
	}
	else if (CVController::GetInstance()->GetPress(nPlayer,CVController::VIRTUAL_KEY_UP)
		|| CVController::GetInstance()->GetStickPress(nPlayer,CVController::VIRTUAL_KEY_UP))
	{// ��
		m_move.x += sinf(D3DX_PI) * PLAYER_DIS;
		m_move.y += cosf(D3DX_PI) * PLAYER_DIS;
	}
	else if (CVController::GetInstance()->GetPress(nPlayer,CVController::VIRTUAL_KEY_DOWN)
		|| CVController::GetInstance()->GetStickPress(nPlayer,CVController::VIRTUAL_STICK_DOWN))
	{// ��
		m_move.x += sinf(0.0f) * PLAYER_DIS;
		m_move.y += cosf(0.0f) * PLAYER_DIS;
	}
}

//-----------------------------------------------------------------------------------------------
// �G�Ƃ̓����蔻��
//
// const D3DXVECTOR3& pos �� �����蔻��̈ʒu( �v���C���[�̈ʒu )
//-----------------------------------------------------------------------------------------------
void CPlayer::CollisionEnemy(const D3DXVECTOR3& pos)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		// �I�u�W�F�N�g�̃|�C���^
		CObject* pObject = nullptr;

		// �I�u�W�F�N�g���擾
		pObject = CObject::GetObject(nCntObject);

		if (pObject == nullptr)
		{// nulltpr��������
			continue;
		}
		else if (pObject->GetObjectType() != EOBJECT_TYPE_ENEMY)
		{// ��ނ��G�ȊO��������
			continue;
		}

		// �_�E���L���X�g
		CEnemy* pEnemy = (CEnemy*)pObject;

		// �ʒu���擾����
		D3DXVECTOR3 EnemyPos = pEnemy->GetPosition();
		D3DXVECTOR3 EnemySize = pEnemy->GetSize();

		if ((EnemyPos.x + EnemySize.x / 2.0f >= pos.x - (PLAYER_WIDTH / 2.0f)
			&& EnemyPos.x - EnemySize.x / 2.0f <= pos.x + (PLAYER_WIDTH / 2.0f)
			&& EnemyPos.y + EnemySize.y / 2.0f >= pos.y - (PLAYER_HEIGHT / 2.0f)
			&& EnemyPos.y - EnemySize.y / 2.0f <= pos.y + (PLAYER_HEIGHT / 2.0f)))
		{// �����蔻��
			if (pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE_DEATH && pEnemy->GetPlayerType() == GetPlayerType())
			{// ���_��������
				Hit(m_nLife);
				// ���̍Đ�
				CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_PLAYERDAMAGE);
			}
			else if ((pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE_CIRCLE || pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE_STAR)
				&& pEnemy->GetPlayerType() != GetPlayerType())
			{// ���ז���������
				Hit(1);
				// ���̍Đ�
				CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_PLAYERDAMAGE);
			}
			else if (pEnemy->GetEnemyType() != CEnemy::ENEMY_TYPE_DEATH && pEnemy->GetEnemyType() != CEnemy::ENEMY_TYPE_CIRCLE
				&& pEnemy->GetEnemyType() != CEnemy::ENEMY_TYPE_STAR)
			{// ���̓G
				Hit(1);
				// ���̍Đ�
				CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_PLAYERDAMAGE);
			}
			break;
		}
	}
}

//-----------------------------------------------------------------------------------------------
// �A�C�e���Ƃ̓����蔻��
//
// const D3DXVECTOR3& pos �� �����蔻��̈ʒu( �v���C���[�̈ʒu )
//-----------------------------------------------------------------------------------------------
void CPlayer::CollisionItem(const D3DXVECTOR3& pos)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		// �I�u�W�F�N�g�̃|�C���^
		CObject* pObject = nullptr;

		// �I�u�W�F�N�g���擾
		pObject = CObject::GetObject(nCntObject);

		if (pObject == nullptr)
		{// nulltpr��������
			continue;
		}
		else if (pObject->GetObjectType() != EOBJECT_TYPE_ITEM)
		{// ��ނ��A�C�e���ȊO��������
			continue;
		}

		// �_�E���L���X�g
		CItem* pItem = (CItem*)pObject;

		// �ʒu���擾����
		D3DXVECTOR3 ItemPos = pItem->GetPosition();
		D3DXVECTOR3 ItemSize = pItem->GetSize();

		if ((ItemPos.x + ItemSize.x / 2.0f >= pos.x - (PLAYER_WIDTH / 2.0f)
			&& ItemPos.x - ItemSize.x / 2.0f <= pos.x + (PLAYER_WIDTH / 2.0f)
			&& ItemPos.y + ItemSize.y / 2.0f >= pos.y - (PLAYER_HEIGHT / 2.0f)
			&& ItemPos.y - ItemSize.y / 2.0f <= pos.y + (PLAYER_HEIGHT / 2.0f)))
		{// �����蔻��
			// �A�C�e���̏���
			CItemManager::GetInstance()->Item(pItem->GetID(), CObject2D::GetPlayerType(), pItem->GetItemType());

			// �A�C�e�����I������
			CItemManager::GetInstance()->ItemDelete(pItem->GetID());

			// ���̍Đ�
			CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_ITEM);
		}
	}
}

//-----------------------------------------------------------------------------------------------
// �ǂƂ̓����蔻��
//
// const D3DXVECTOR3& pos �� �����蔻��̈ʒu( �v���C���[�̈ʒu )
//-----------------------------------------------------------------------------------------------
D3DXVECTOR3 CPlayer::CollisionWall(D3DXVECTOR3 pos)
{
	// �ʒu
	D3DXVECTOR3 posPlayer = pos;

	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		// �I�u�W�F�N�g�̃|�C���^�����擾
		CObject* pObject = CObject::GetObject(nCntObject);

		if (pObject == nullptr)
		{// nulltpr��������
			continue;
		}
		else if (pObject->GetObjectType() != EOBJECT_TYPE_WALL)
		{// ��ނ��ǈȊO��������
			continue;
		}

		// �_�E���L���X�g
		CWall* pWall = (CWall*)pObject;

		// �ʒu���擾����
		D3DXVECTOR3 WallPos = pWall->GetPosition();
		D3DXVECTOR3 WallSize = pWall->GetSize();

		if (m_posOld.x - (PLAYER_WIDTH / 2.0f) >= WallPos.x + (WallSize.x / 2.0f)
			&& pos.x - (PLAYER_WIDTH / 2.0f) <= WallPos.x + (WallSize.x / 2.0f))
		{// ��
			posPlayer.x = WallPos.x + (WallSize.x / 2.0f) + (PLAYER_WIDTH / 2.0f);
		}
		else if (m_posOld.x + (PLAYER_WIDTH / 2.0f) <= WallPos.x - (WallSize.x / 2.0f)
			&& pos.x + (PLAYER_WIDTH / 2.0f) >= WallPos.x - (WallSize.x / 2.0f))
		{// �E
			posPlayer.x = WallPos.x - (WallSize.x / 2.0f) - (PLAYER_WIDTH / 2.0f);
		}
	}
	return posPlayer;
}

//-----------------------------------------------------------------------------------------------
// ��ʊO����
//
// D3DXVECTOR3. pos �� �����蔻��̈ʒu( �v���C���[�̈ʒu )
//-----------------------------------------------------------------------------------------------
D3DXVECTOR3 CPlayer::OffScreen(D3DXVECTOR3 pos)
{
	if (pos.y - (PLAYER_HEIGHT / 2.0f) < 0)
	{// ��
		pos.y = PLAYER_HEIGHT / 2.0f;
	}
	else if (pos.y + (PLAYER_HEIGHT / 2.0f) > CRenderer::SCREEN_HEIGHT)
	{// ��
		pos.y = CRenderer::SCREEN_HEIGHT - (PLAYER_HEIGHT / 2.0f);
	}

	if (pos.x - (PLAYER_WIDTH / 2.0f) < 0)
	{// ��
		pos.x = PLAYER_WIDTH / 2.0f;
	}
	else if (pos.x + (PLAYER_WIDTH / 2.0f) > CRenderer::SCREEN_WIDTH)
	{// �E
		pos.x = CRenderer::SCREEN_WIDTH - (PLAYER_WIDTH / 2.0f);
	}

	return pos;
}