//-------------------------------------------
//
// �I�u�W�F�N�g�̏��[object.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _OBJECT_H_		// ��d�C���N���[�h�h�~
#define _OBJECT_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include <d3dx9.h>		// �`�揈���ɕK�v
#include "common.h"		// ����

//-------------------------------------------
// �N���X
//-------------------------------------------
class CObject
{
public:
	// �e
	enum OBJECT_PARENT
	{
		// �Ȃ�
		OBJECT_PARENT_NONE = 0,
		// �^�C�g��
		OBJECT_PARENT_TITLE,
		// �`���[�g���A��
		OBJECT_PARENT_TUTORIAL,
		// �Q�[��
		OBJECT_PARENT_GAME,
		// ���U���g
		OBJECT_PARENT_RESULT,
		// �ő吔
		OBJECT_PARENT_MAX
	};

public:
	// �I�u�W�F�N�g�̍ő吔
	static const int MAX_OBJECT = 300;

public:
	// �R���X�g���N�^
	CObject();
	// �f�X�g���N�^
	virtual ~CObject();

	// ������
	virtual HRESULT Init(const D3DXVECTOR3& pos) = 0;
	// �I��
	virtual void Uninit() = 0;
	// �X�V
	virtual void Update() = 0;
	// �`��
	virtual void Draw() = 0;

	// ���ׂẴ������̊J��
	static void ReleseAll();
	// ���ׂĂ��X�V
	static void UpdateAll();
	// ���ׂĂ�`��
	static void DrawAll();

	// �e�̍폜
	static void ReleseParent(OBJECT_PARENT parent);

	// �I�u�W�F�N�g�̎�ނ�ݒ�
	void SetObjectType(OBJECT_TYPE objectType);
	// �I�u�W�F�N�g�̎�ނ��擾
	OBJECT_TYPE GetObjectType() const;

	// �e��ݒ�
	void SetObjectParent(OBJECT_PARENT parent);
	// �e���擾
	OBJECT_PARENT GetObjectParent();

	// �I�u�W�F�N�g�̃|�C���^���擾
	static CObject* GetObject(int nCntObject);

protected:
	//�I�u�W�F�N�g�̍폜
	void Relese();

private:
	// �|�C���^�N���X
	static CObject* m_apObject[MAX_OBJECT];
	// ��
	static int m_nNumAll;

	// �i�[��̔ԍ�
	int m_nID;
	// �D�揇��
	int m_nPriority;
	// �I�u�W�F�N�g�̎��
	OBJECT_TYPE m_ObjectType;
	// �e
	OBJECT_PARENT m_parent;
};

#endif		// _OBJECT_H_