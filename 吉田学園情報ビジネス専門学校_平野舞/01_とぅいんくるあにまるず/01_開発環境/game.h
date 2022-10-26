//-------------------------------------------
//
// �Q�[�����[game.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _GAME_H_		// ��d�C���N���[�h�h�~
#define _GAME_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include <d3dx9.h>		// �`�揈���ɕK�v

//-------------------------------------------
// �O���錾
//-------------------------------------------
// �v���C���[
class CPlayer;
// ���C�t
class CLife;
// �X�L��
class CSkill;

//-------------------------------------------
// �N���X
//-------------------------------------------
class CGame
{
private:
	// �v���C���[�̍ő吔
	static const int MAX_PLAYER = 2;

private:
	// �R���X�g���N�^
	CGame();
public:
	// �f�X�g���N�^
	~CGame();

	// �C���X�^���X�̐���
	static void CreateInstance();
	// �C���X�^���X�̎擾
	static CGame* GetInstance();

	// ������
	HRESULT Init();
	// �I��
	void Uninit();
	// �X�V
	void Update();

	// �v���C���[�|�C���^�̎擾
	static CPlayer* GetPlayer(int nCntPlayer);
	// ���C�t�̃|�C���^���擾
	static CLife* GetLife(int nCntLife);
	// �X�L���̃|�C���^���擾
	static CSkill* GetSkill(int nCntSkill);

private:
	// �Q�[���N���X�̃|�C���^
	static CGame* m_Instance;
	// �e�N�X�`����
	static char* m_cFileName[];

	// �v���C���[�̃|�C���^
	static CPlayer* m_pPlayer[MAX_PLAYER];
	// ���C�t�̃|�C���^
	static CLife* m_pLife[MAX_PLAYER];
	// �X�L���̃|�C���^
	static CSkill* m_pSkill[MAX_PLAYER];
};

#endif		// _GAME_H_