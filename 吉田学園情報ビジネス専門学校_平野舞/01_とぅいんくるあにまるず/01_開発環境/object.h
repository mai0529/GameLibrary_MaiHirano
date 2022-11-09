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

//-------------------------------------------
// �N���X
//-------------------------------------------
class CObject
{
public:
	// �e
	enum EOBJECT_PARENT
	{
		// �Ȃ�
		EOBJECT_PARENT_NONE = 0,
		// �^�C�g��
		EOBJECT_PARENT_TITLE,
		// �`���[�g���A��
		EOBJECT_PARENT_TUTORIAL,
		// �Q�[��
		EOBJECT_PARENT_GAME,
		// �|�[�Y
		EOBJECT_PARENT_PAUSE,
		// ���U���g
		EOBJECT_PARENT_RESULT,
		// �ő吔
		EOBJECT_PARENT_MAX
	};

	// �I�u�W�F�N�g���
	enum EOBJECT_TYPE
	{
		// �����Ȃ�
		OBJECT_TYPE_NONE = 0,
		// �v���C���[
		EOBJECT_TYPE_PLAYER,
		// ���C�t
		EOBJECT_TYPE_LIFE,
		// �X�L��
		EOBJECT_TYPE_SKILL,
		// �G
		EOBJECT_TYPE_ENEMY,
		// �e
		EOBJECT_TYPE_BULLET,
		// �A�C�e��
		EOBJECT_TYPE_ITEM,
		// ��
		EOBJECT_TYPE_WALL,
		// �G�t�F�N�g
		EOBJECT_TYPE_EFFECT,
		// �p�[�e�B�N��
		EOBJECT_TYPE_PARTICLE,
		// ���j���[
		EOBJECT_TYPE_MENU,
		//��ނ̍ő吔
		EOBJECT_TYPE_MAX
	};

	// �D�揇��
	enum EOBJECT_PRIORITY
	{
		// �w��Ȃ�
		OBJECT_PRIORITY_NONE = 4,
		// �t�F�[�h
		OBJECT_PRIORITY_FADE,
		// �ő吔
		OBJECT_PRIORITY_MAX
	};

public:
	// �I�u�W�F�N�g�̍ő吔
	static const int MAX_OBJECT = 300;
	// �D�揇�ʂ̍ő吔
	static const int NUM_PRIORITY = 6;

public:
	// �R���X�g���N�^
	explicit CObject(int nPriority = 3);
	// �f�X�g���N�^
	virtual ~CObject();

	// ������
	virtual HRESULT Init() = 0;
	// �I��
	virtual void Uninit() = 0;
	// �X�V
	virtual void Update() = 0;
	// �`��
	virtual void Draw() = 0;

	// ���ׂẴ������̊J��
	static void ReleaseAll();
	// ���ׂĂ��X�V
	static void UpdateAll();
	// ���ׂĂ�`��
	static void DrawAll();

	// �e�̍폜
	static void ReleaseParent(EOBJECT_PARENT parent);

	// �i�s���Ă��邩�ǂ����̐ݒ�
	static void SetPause(bool bPause);
	// �i�s���Ă��邩�ǂ����̏����擾
	static bool GetPause();

	// �D�揇�ʂ̐ݒ�
	void SetPriority(int nPriority);
	// �D�揇�ʂ̎擾
	int GetPriority();

	// �I�u�W�F�N�g�̎�ނ�ݒ�
	void SetObjectType(EOBJECT_TYPE objectType);
	// �I�u�W�F�N�g�̎�ނ��擾
	EOBJECT_TYPE GetObjectType() const;

	// �e��ݒ�
	void SetObjectParent(EOBJECT_PARENT parent);
	// �e���擾
	EOBJECT_PARENT GetObjectParent();

	// �I�u�W�F�N�g�̃|�C���^���擾
	static CObject* GetObject(int nCntObject, int nPriority = 3);

protected:
	//�I�u�W�F�N�g�̍폜
	void Release();

private:
	// �|�C���^�N���X
	static CObject* m_apObject[NUM_PRIORITY][MAX_OBJECT];
	// ��
	static int m_nNumAll;
	// �i�s���Ă��邩�ǂ���
	static bool m_bPause;

	// �i�[��̔ԍ�
	int m_nID;
	// �D�揇��
	int m_nPriority;
	// �I�u�W�F�N�g�̎��
	EOBJECT_TYPE m_ObjectType;
	// �e
	EOBJECT_PARENT m_parent;
};

#endif		// _OBJECT_H_