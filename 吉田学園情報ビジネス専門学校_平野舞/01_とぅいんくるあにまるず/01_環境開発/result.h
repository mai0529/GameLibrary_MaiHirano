//-------------------------------------------
//
// ���U���g���[result.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _RESULT_H_		// ��d�C���N���[�h�h�~
#define _RESULT_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include <d3dx9.h>		// �`�揈���ɕK�v

//-------------------------------------------
// �O���錾
//-------------------------------------------
// �I�u�W�F�N�g2D
class CObject2D;

//-------------------------------------------
// �N���X
//-------------------------------------------
class CResult
{
private:
	// �R���X�g���N�^
	CResult();
public:
	// �f�X�g���N�^
	~CResult();

	// �C���X�^���X�̐���
	static void CreateInstance();
	// �C���X�^���X�̎擾
	static CResult* GetInstance();

	// ������
	HRESULT Init();
	// �I��
	void Uninit();
	// �X�V
	void Update();

private:
	// �^�C�g���N���X�̃|�C���^
	static CResult* m_Instance;
	// �e�N�X�`����
	static char* m_cFileName[];
};

#endif		// _RESULT_H_