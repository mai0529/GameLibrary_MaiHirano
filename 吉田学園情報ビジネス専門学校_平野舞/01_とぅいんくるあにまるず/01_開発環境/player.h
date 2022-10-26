//-------------------------------------------
//
// �v���C���[�̏��[player.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _PLAYER_H_		// ��d�C���N���[�h�h�~
#define _PLAYER_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include "object2D.h"		// 2D�I�u�W�F�N�g

//-------------------------------------------
// �O���錾
//-------------------------------------------
// �X�L��
class CSkill;

//-------------------------------------------
// �N���X
//-------------------------------------------
class CPlayer : public CObject2D
{
private:
	// �v���C���[�̏��
	enum PLAYER_STATE
	{
		// �ʏ���
		PLAYER_STATE_NORMAL = 0,
		// ���G���
		PLAYER_STATE_INVINCIBLE,
		// �_���[�W���
		PLAYER_STATE_DAMAGE,
		// ���S���
		PLAYER_STATE_DEATH,
		// ��Ԃ̍ő吔
		PLAYER_STATE_MAX
	};

public:
	// �R���X�g���N�^
	CPlayer();
	// �f�X�g���N�^
	~CPlayer() override;

	// ����
	static CPlayer* Create(MULTI_TYPE player,const D3DXVECTOR3& pos);

	// ������
	HRESULT Init(const D3DXVECTOR3& pos) override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

	//�����̎擾
	int GetLife();

private:
	// ���
	void State();
	// �q�b�g
	void Hit(int nDamage);
	// �_��
	void Blink();

	// �e�̔���
	void Shoot(int nPlayer,const D3DXVECTOR3& pos);
	// �X�L������
	void Skill(int nPlayer);
	// �ړ�
	void Move(int nPlayer);

	// �G�Ƃ̓����蔻��
	void CollisionEnemy(const D3DXVECTOR3& pos);
	// �A�C�e���Ƃ̓����蔻��
	void CollisionItem(const D3DXVECTOR3& pos);
	// �ǂƂ̓����蔻��
	D3DXVECTOR3 CollisionWall(D3DXVECTOR3 pos);
	// ��ʊO�����蔻��
	D3DXVECTOR3 OffScreen(D3DXVECTOR3 pos);

private:
	// �X�L��
	CSkill* m_pSkill;
	// �O�t���[���̈ʒu
	D3DXVECTOR3 m_posOld;
	// �ړ���
	D3DXVECTOR3 m_move;
	// ����
	int m_nLife;
	// �v���C���[�̏��
	PLAYER_STATE m_state;
	// �_�ŃJ�E���^�[
	int m_nCntBlink;
};

#endif		// _PLAYER_H_