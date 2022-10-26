//-------------------------------------------
//
// �G�t�F�N�g�̏��[effect.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _EFFECT_H_		// ��d�C���N���[�h�h�~
#define _EFFECT_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include "object2D.h"	// 2D�I�u�W�F�N�g

//-------------------------------------------
// �N���X
//-------------------------------------------
class CEffect : public CObject2D
{
public:
	// �R���X�g���N�^
	CEffect();
	// �f�X�g���N�^
	~CEffect() override;

	// ����
	static CEffect* Create(const D3DXVECTOR3& pos);

	// ������
	HRESULT Init(const D3DXVECTOR3& pos) override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

	// �T�C�Y�̐ݒ�
	void SetSizeEf(D3DXVECTOR3 size);
	// �p�x�̐ݒ�
	void SetAngle(float fAngle);
	// �����̐ݒ�
	void SetLife(int nLife);

private:
	// �ړ���
	D3DXVECTOR3 m_move;
	// �T�C�Y
	D3DXVECTOR3 m_size;
	// �p�x
	float m_fAngle;
	// ����
	int m_nLife;
};

#endif		// _PLAYER_H_