//-------------------------------------------
//
// �^�C�}�[�̏��[time.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _TIME_H_		// ��d�C���N���[�h�h�~
#define _TIME_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include <d3dx9.h>		// �`�揈���ɕK�v

//-------------------------------------------
// �N���X
//-------------------------------------------
class CTime
{
private:
	// �R���X�g���N�^
	CTime();

public:
	// �f�X�g���N�^
	~CTime();

	// �C���X�^���X�̐���
	static void CreateInstance();
	// �C���X�^���X�̎擾
	static CTime* GetInstance();

	// ������
	void Init();
	// �I��
	void Uninit();
	// �X�V
	void Update();

	// �^�C�}�̕b�����擾
	int GetTime();
	// �^�C�}�̃��Z�b�g
	void ResetTime();

private:
	// �|�C���^
	static CTime* m_pTime;
	// �t���[����
	int m_nFrame;
	// �b��
	int m_nTime;
};

#endif		// _TIME_H_