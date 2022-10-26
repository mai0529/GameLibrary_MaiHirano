//-------------------------------------------
//
// �e�̏��[bullet.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _BULLET_H_		// ��d�C���N���[�h�h�~
#define _BULLET_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include "object2D.h"		// 2D�I�u�W�F�N�g

//-------------------------------------------
// �O���錾
//-------------------------------------------
class CEffect;		// �G�t�F�N�g

//-------------------------------------------
// �N���X
//-------------------------------------------
class CBullet : public CObject2D
{
public:
	// �R���X�g���N�^
	CBullet();
	// �f�X�g���N�^
	~CBullet() override;

	// ����
	static CBullet* Create(MULTI_TYPE playerType,const D3DXVECTOR3& pos);

	// ������
	HRESULT Init(const D3DXVECTOR3& pos) override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

private:
	// �����蔻��
	void Collision(const D3DXVECTOR3& pos);

private:
	// �G�t�F�N�g�̃|�C���^
	static CEffect* m_pEffect;

	// �ړ���
	D3DXVECTOR3 m_move;
	// ����
	int m_nLife;
};

#endif		// _BULLET_H_
