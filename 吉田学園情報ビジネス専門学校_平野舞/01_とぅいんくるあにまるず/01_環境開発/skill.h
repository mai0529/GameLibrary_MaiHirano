//-------------------------------------------
//
// �X�L�����[skill.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _SKILL_H_		// ��d�C���N���[�h�h�~
#define _SKILL_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include "object2D.h"	// 2D�I�u�W�F�N�g

//-------------------------------------------
// �N���X
//-------------------------------------------
class CSkill : public CObject2D
{
public:
	// �R���X�g���N�^
	CSkill();
	// �f�X�g���N�^
	~CSkill() override;

	// ����
	static CSkill* Create(const D3DXVECTOR3& pos);

	// ������
	HRESULT Init(const D3DXVECTOR3& pos) override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

	// �h��X�L��
	void Defense();
	// �X�L��
	void Skill(MULTI_TYPE player);

	// ���G��Ԃ��ǂ������擾
	bool GetInvincible();

private:
	// �\�����邩�ǂ���
	bool m_bDis;
	// �X�L�����g�p�������ǂ���
	bool m_bUse;
	// �G�J�E���g
	int m_nCntEnemy;
	// ���G��Ԃ��ǂ���
	bool m_bInvincible;
	// ���G����
	int m_nInvincible;
};

#endif		// _SKILL_H_