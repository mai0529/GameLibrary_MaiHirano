//---------------------------------------------------------------------------------
//
// �Q�[������[game.cpp]
// Author : ���앑
//
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//---------------------------------------------------------------------------------
#include "game.h"				// �Q�[��
#include "application.h"		// �A�v���P�[�V����
#include "common.h"				// ���ʂ̗񋓌^
#include "renderer.h"			// �����_�����O
#include "object2D.h"			// 2D�I�u�W�F�N�g
#include "player.h"				// �v���C���[
#include "bullet.h"				// �e
#include "life.h"				// ���C�t
#include "bg.h"					// �w�i
#include "effect.h"				// �G�t�F�N�g
#include "wall.h"				// ��
#include "skill.h"				// �X�L��
#include "ResourceManager.h"	// ���\�[�X�}�l�[�W���[
#include "VirtualController.h"	// ���z�R���g���[���[
#include "time.h"				// �^�C�}�[
#include "enemyManager.h"		// �G�}�l�[�W���[
#include "itemManager.h"		// �A�C�e���}�l�[�W���[
#include "sound.h"				// ��
#include "enemy.h"				// �G
#include "TextureFileName.h"	// �摜�̃t�@�C����
#include "fade.h"				// �t�F�[�h

//---------------------------------------------------------------------------------
// �e�N�X�`����
//---------------------------------------------------------------------------------
char* CGame::m_cFileName[] =
{
	// �w�i
	TEX_BG_GAME,
	// ��
	TEX_WALL,

	// 1P
	TEX_PLAYER_ONE,
	// 2P
	TEX_PLAYER_SECOND,

	// �e
	TEX_BULLET,
	// ����
	TEX_LIFE,
	// �X�L��
	TEX_SKILL,

	// �A�C�e��( �{�� )
	TEX_ITEM_BOM,
	// �A�C�e��( ���ז� )
	TEX_ITEM_OBSTACLE,

	// �G( ������ )
	TEX_ENEMY_RABBIT,
	// �G( �˂� )
	TEX_ENEMY_CAT,
	// �G( ���� )
	TEX_ENEMY_DOG,
	// �G( �܂� )
	TEX_ENEMY_CIRCLE,
	// �G( �ق� )
	TEX_ENEMY_STAR,
	// �G( ���_ )
	TEX_ENEMY_DEATH,
	// �G( �{�X )
	TEX_ENEMY_BOSS,

	// �G�t�F�N�g
	TEX_EFFECT,
	nullptr
};

//---------------------------------------------------------------------------------
// �ÓI�����o�ϐ��錾
//---------------------------------------------------------------------------------
// �Q�[��
CGame* CGame::m_Instance = nullptr;
// �v���C���[
CPlayer* CGame::m_pPlayer[MAX_PLAYER] = { nullptr };
// ���C�t
CLife* CGame::m_pLife[MAX_PLAYER] = { nullptr };
// �X�L���̃|�C���^
CSkill* CGame::m_pSkill[MAX_PLAYER] = { nullptr };

//---------------------------------------------------------------------------------
//	�R���X�g���N�^
//---------------------------------------------------------------------------------
CGame::CGame()
{

}

//---------------------------------------------------------------------------------
//	�f�X�g���N�^
//---------------------------------------------------------------------------------
CGame::~CGame()
{

}

//---------------------------------------------------------------------------------
// �C���X�^���X�̐���
//---------------------------------------------------------------------------------
void CGame::CreateInstance()
{
	if (m_Instance == nullptr)
	{// nullptr��������
		// �������̐���
		m_Instance = new CGame;
	}
}

//---------------------------------------------------------------------------------
// �C���X�^���X�̎擾
//---------------------------------------------------------------------------------
CGame* CGame::GetInstance()
{
	if (m_Instance != nullptr)
	{// nullptr�ł͂Ȃ�������
		return m_Instance;
	}

	return nullptr;
}

//---------------------------------------------------------------------------------
//	������
//---------------------------------------------------------------------------------
HRESULT CGame::Init()
{
	// ����
	// ���\�[�X�}�l�[�W���[�̃C���X�^���X�𐶐�
	CResourceManager::CreateInstance();
	// �e�N�X�`���̓ǂݍ���
	CResourceManager::GetInstance()->LoadTexture(m_cFileName);

	// �^�C�}�̃C���X�^���X�𐶐�
	CTime::CreateInstance();
	CTime::GetInstance()->Init();

	// �w�i
	CBg::Create();

	// ��
	CWall::CreateInstance();
	CWall::GetInstance()->Init(D3DXVECTOR3((float)CRenderer::SCREEN_WIDTH / 2.0f, (float)CRenderer::SCREEN_HEIGHT / 2.0f, 0.0f));

	// �v���C���[
	m_pPlayer[0] = CPlayer::Create(MULTI_TYPE_ONE, D3DXVECTOR3(300.0f, 600.0f, 0.0f));
	m_pPlayer[1] = CPlayer::Create(MULTI_TYPE_SECOND, D3DXVECTOR3(1000.0f, 600.0f, 0.0f));

	// �G�}�l�[�W���[�̃C���X�^���X�𐶐�
	CEnemyManager::CreateInstance();
	CEnemyManager::GetInstance()->Init();

	// �A�C�e���}�l�[�W���[�̃C���X�^���X�𐶐�
	CItemManager::CreateInstance();
	CItemManager::GetInstance()->Init();

	// ���C�t
	m_pLife[0] = CLife::Create(D3DXVECTOR3(25.0f, 690.0f, 0.0f));
	m_pLife[1] = CLife::Create(D3DXVECTOR3(725.0f, 690.0f, 0.0f));

	// �X�L��
	m_pSkill[0] = CSkill::Create(D3DXVECTOR3(525.0f, 690.0f, 0.0f));
	m_pSkill[1] = CSkill::Create(D3DXVECTOR3(1225.0f, 690.0f, 0.0f));

	// ���̍Đ�
	CSound::GetInstace()->Play(CSound::SOUND_LABEL_GAME);

	return S_OK;
}

//---------------------------------------------------------------------------------
//	�I��
//---------------------------------------------------------------------------------
void CGame::Uninit()
{
	// ���̒�~
	CSound::GetInstace()->Stop();

	if (m_Instance != nullptr)
	{// nullptr�ł͂Ȃ�������
		// �G�}�l�[�W���[��j������
		CEnemyManager::GetInstance()->Uninit();

		// �A�C�e���}�l�[�W���[��j������
		CItemManager::GetInstance()->Uninit();

		// �^�C�}��j������
		CTime::GetInstance()->Uninit();

		// �e�N�X�`���̔j��
		CResourceManager::GetInstance()->AllUnloadTexture();

		// ��������j������
		delete m_Instance;

		// nullptr�ɂ���
		m_Instance = nullptr;
	}
}

//---------------------------------------------------------------------------------
//	�X�V
//---------------------------------------------------------------------------------
void CGame::Update()
{
	// �^�C�}�[�̍X�V
	CTime::GetInstance()->Update();

	// �G�}�l�[�W���[�̍X�V
	CEnemyManager::GetInstance()->Update();

	// �A�C�e���}�l�[�W���[�̍X�V
	CItemManager::GetInstance()->Update();

#ifdef _DEBUG
	if (CVController::GetInstance()->GetTrigger(MULTI_TYPE_ONE - 1, CVController::VIRTUAL_KEY_START))
	{
		// ���U���g�Ɉڍs
		CFade::GetInstance()->SetFade(CApplication::MODE_RESULT);

		// ���̍Đ�
		CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_DECISION_CAT);
		CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_DECISION_DOG);

		return;
	}
#endif	//_DEBUG
}

//---------------------------------------------------------------------------------
//	�v���C���[�|�C���^�̎擾
//---------------------------------------------------------------------------------
CPlayer* CGame::GetPlayer(int nCntPlayer)
{
	return m_pPlayer[nCntPlayer];
}

//---------------------------------------------------------------------------------
// ���C�t�̃|�C���^���擾
//---------------------------------------------------------------------------------
CLife* CGame::GetLife(int nCntLife)
{
	return m_pLife[nCntLife];
}

//---------------------------------------------------------------------------------
// �X�L���̃|�C���^���擾
//---------------------------------------------------------------------------------
CSkill* CGame::GetSkill(int nCntSkill)
{
	return m_pSkill[nCntSkill];
}