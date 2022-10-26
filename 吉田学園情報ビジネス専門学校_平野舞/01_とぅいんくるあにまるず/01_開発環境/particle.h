//-------------------------------------------
//
// �p�[�e�B�N���̏��[particle.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _PARTICLE_H_		// ��d�C���N���[�h�h�~
#define _PARTICLE_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include "object.h"		// �I�u�W�F�N�g
#include "common.h"		// ����

//-------------------------------------------
// �O���錾
//-------------------------------------------
// �G�t�F�N�g
class CEffect;

//-------------------------------------------
// �N���X
//-------------------------------------------
class CParticle : public CObject
{
public:
	// �R���X�g���N�^
	CParticle();
	// �f�X�g���N�^
	virtual ~CParticle();

	// ����
	static CParticle* Create(const D3DXVECTOR3& pos);

	// ������
	HRESULT Init(const D3DXVECTOR3& pos) override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

private:
	// �A��
	void Chain(MULTI_TYPE type, const D3DXVECTOR3& pos);
	// �G�Ƃ̓����蔻��
	void CollisionEnemy(const D3DXVECTOR3& pos);

private:
	// �e�N�X�`���̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pTexture;
	// �A����
	static int m_nChain;
	// ��������
	static int m_nCreateTime;
	// �O��̐�������
	static int m_nCreateTimeOld;

	// �G�t�F�N�g�̃|�C���^
	CEffect* m_paEffect;
	// �ʒu
	D3DXVECTOR3 m_pos;
	// ����
	int m_nLife;
	// �T�C�Y
	float m_AddSize;
};

#endif		// _PARTICLE_H_