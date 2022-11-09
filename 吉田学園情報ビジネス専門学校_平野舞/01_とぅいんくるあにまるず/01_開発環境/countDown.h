//-------------------------------------------
//
// �J�E���g�_�E�����[countDown.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _COUNTDOWN_H_		// ��d�C���N���[�h�h�~
#define _COUNTDOWN_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include "object2D.h"	// 2D�I�u�W�F�N�g

//-------------------------------------------
// �N���X
//-------------------------------------------
class CCountDown : public CObject2D
{
public:
	// �R���X�g���N�^
	CCountDown();
	// �f�X�g���N�^
	~CCountDown() override;

	// ����
	static CCountDown* Create(const D3DXVECTOR3& pos);

	// ������
	HRESULT Init() override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

private:
	// �t���[�����̃J�E���^�[
	int m_nCntFrame;
	// �J�E���g�_�E���p�J�E���^�[
	int m_nCountDown;
};

#endif		// _COUNTDOWN_H_