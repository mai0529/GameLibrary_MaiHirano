//-------------------------------------------
//
// �G�̏��[enemy.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _ENEMY_H_		// ��d�C���N���[�h�h�~
#define _ENEMY_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include "object2D.h"		// 2D�I�u�W�F�N�g

//-------------------------------------------
// �N���X
//-------------------------------------------
class CEnemy : public CObject2D
{
public:
	// �G�̎��
	enum ENEMY_TYPE
	{
		// ������
		ENEMY_TYPE_RABBIT = 0,
		// �˂�
		ENEMY_TYPE_CAT,
		// ����
		ENEMY_TYPE_DOG,
		// �ۂ̂��ז��G
		ENEMY_TYPE_CIRCLE,
		// ���̂��ז��G
		ENEMY_TYPE_STAR,
		// ���_
		ENEMY_TYPE_DEATH,
		// �{�X
		ENEMY_TYPE_BOSS,
		// ��ނ̍ő吔
		ENEMY_TYPE_MAX
	};

	enum ENEMY_STATE
	{
		// �ʏ���
		ENEMY_STATE_NORMAL = 0,
		// �_���[�W���
		ENEMY_STATE_DAMAGE,
		// ���S���
		ENEMY_STATE_DEATH,
		// ��Ԃ̍ő吔
		ENEMY_STATE_MAX
	};

public:
	// �R���X�g���N�^
	CEnemy();
	// �f�X�g���N�^
	~CEnemy() override;

	// ����
	static CEnemy* Create(const D3DXVECTOR3& pos);

	// ������
	HRESULT Init() override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

	// �q�b�g
	void Hit(int nDamage);

	// �i�[��̔ԍ���ݒ�
	void SetID(int nID);
	// �i�[��ԍ��̎擾
	int GetID();

	// �T�C�Y��ݒ�
	void SetSize(const D3DXVECTOR3& size);
	// �ړ��ʂ�ݒ�
	void SetMove(const D3DXVECTOR3& move);

	// ���x��ݒ�
	void SetSpeed(float fSpeed);
	// ���x���擾
	float GetSpeed();

	// �����̐ݒ�
	void SetLife(int nLife);
	// �����̎擾
	int GetLife();

	// ��ނ̐ݒ�
	void SetEnemyType(ENEMY_TYPE type);
	// ��ނ̎擾
	ENEMY_TYPE GetEnemyType();

	// ��Ԃ̎擾
	ENEMY_STATE GetState();

	// �o���o�ߎ��Ԃ��擾
	int GetAppeaTime();

private:
	// ���
	void State();
	// �_��
	void Blink();
	// �ǂ̓����蔻��
	bool CollisionWall(D3DXVECTOR3 pos);
	// ��ʊO����
	bool OffScreen(D3DXVECTOR3 pos);

private:
	// �i�[��̔ԍ�
	int m_nID;
	// �O�̈ʒu
	D3DXVECTOR3 m_posOld;
	// �T�C�Y
	D3DXVECTOR3 m_size;
	// �ړ���
	D3DXVECTOR3 m_move;
	// �J���[
	D3DXCOLOR m_col;
	// ���x
	float m_fSpeed;
	// ����
	int m_nLife;
	// �G�̎��
	ENEMY_TYPE m_type;
	// ���
	ENEMY_STATE m_state;
	// �o���o�߃J�E���g
	int m_nAppeaTime;
	// �_�ŃJ�E���^�[
	int m_nCntBlink;
};

#endif		// _ENEMY_H_