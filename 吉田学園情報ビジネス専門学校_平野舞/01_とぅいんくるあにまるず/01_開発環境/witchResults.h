//-------------------------------------------
//
// ���ʕ\�����[witchResults.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _WITCHRESULTS_H_		// ��d�C���N���[�h�h�~
#define _WITCHRESULTS_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include "object.h"		// �I�u�W�F�N�g

//-------------------------------------------
// �O���錾
//-------------------------------------------
// �I�u�W�F�N�g2D
class CObject2D;

//-------------------------------------------
// �N���X
//-------------------------------------------
class CWitchResult
{
private:
	// �e�N�X�`���̍ő吔
	static const int MAX_TEX = 4;

private:
	// �R���X�g���N�^
	CWitchResult();
public:
	// �f�X�g���N�^
	~CWitchResult();

	// �C���X�^���X�̐���
	static void CreateInstance();
	// �C���X�^���X�̎擾
	static CWitchResult* GetInstance();

	// �ǂ��������҂�
	void SetWinner();

	// ������
	HRESULT Init(const D3DXVECTOR3& pos);
	// �I��
	void Uninit();
	// �X�V
	void Update();
	// �`��
	void Draw();


private:
	// �^�C�g���N���X�̃|�C���^
	static CWitchResult* m_Instance;

	// �I�u�W�F�N�g2D�̃|�C���^
	CObject2D* m_paObject2D[MAX_TEX];
	// ����
	int m_nWinner;
};

#endif		// _RESULT_H_