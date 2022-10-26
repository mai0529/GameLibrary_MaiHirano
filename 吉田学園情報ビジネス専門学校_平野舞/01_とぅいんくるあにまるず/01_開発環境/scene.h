//-------------------------------------------
//
// �V�[�����[scene.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _SCENE_H_		// ��d�C���N���[�h�h�~
#define _SCENE_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include <d3dx9.h>		// �`�揈���ɕK�v

//-------------------------------------------
// �N���X
//-------------------------------------------
class CScene
{
private:
	// �R���X�g���N�^
	CScene();
public:
	// �f�X�g���N�^
	~CScene();

	// �C���X�^���X�̐���
	static void CreateInstance();
	// �C���X�^���X�̎擾
	static CScene* GetInstance();

	//// ������
	//virtual HRESULT Init();
	//// �I��
	//virtual void Uninit();
	//// �X�V
	//virtual void Update();

private:
	// �^�C�g���N���X�̃|�C���^
	static CScene* m_Instance;
};

#endif		// _SCENE_H_