//-------------------------------------------
//
// �ǂ̏��[wall.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _WALL_H_		// ��d�C���N���[�h�h�~
#define _WALL_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include "object2D.h"	// 2D�I�u�W�F�N�g

//-------------------------------------------
// �N���X
//-------------------------------------------
class CWall : public CObject2D
{
private:
	// �R���X�g���N�^
	CWall();

public:
	// �f�X�g���N�^
	~CWall() override;

	// �C���X�^���X�̐���
	static void CreateInstance();
	// �C���X�^���X�̎擾
	static CWall* GetInstance();

	// ������
	HRESULT Init() override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

private:
	// �ǂ̃|�C���^
	static CWall* m_pWall;
};

#endif		// _PLAYER_H_