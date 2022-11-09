//-------------------------------------------
//
// �G�}�l�[�W���[�̏��[enemyManager.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _ENEMYMANAGER_H_		// ��d�C���N���[�h�h�~
#define _ENEMYMANAGER_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include <d3dx9.h>		// �`�揈���ɕK�v

//-------------------------------------------
// �C���N���[�h
//-------------------------------------------
#include "object.h"		// �I�u�W�F�N�g
#include "object2D.h"	// �I�u�W�F�N�g2D
#include "enemy.h"		// �G

//-------------------------------------------
// �N���X
//-------------------------------------------
class CEnemyManager : public CObject
{
private:
	// �G�̍ő吔
	static const int MAX_ENEMY = 100;

private:
	// �O���t�@�C���ǂݍ��݂̍\����
	struct File
	{
		// �o���J�E���^�[
		int nCntApper;
		// �ʒu
		D3DXVECTOR3 pos;
		// �F
		D3DXCOLOR col;
		// �ړ��X�s�[�h
		float fSpeed;
		// ����
		int nLife;
		// ���
		int nType;
	};

private:
	// �R���X�g���N�^
	CEnemyManager();

public:
	// �f�X�g���N�^
	~CEnemyManager();

	// �C���X�^���X�̐���
	static void CreateInstance();
	// �C���X�^���X�̎擾
	static CEnemyManager* GetInstance();

	// �G�̐���
	void Create(CObject2D::MULTI_TYPE player,int nType,D3DXVECTOR3 pos, float fSpeed,D3DXCOLOR col,int nLife);

	// ������
	HRESULT Init() override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

	// �G�̍폜
	void DeleteEnemy(int nCntEnemy);

private:
	// �O���t�@�C���ǂݍ���
	void Load();

private:
	// �O���t�@�C���\���̂̏��
	File m_aFile[MAX_ENEMY];
	// �e�L�X�g�t�@�C���p�G�̃J�E���g
	int m_nCntFileEnemy;
	// ���̓G�̃J�E���g
	int m_nNowCntEnemy;

	// �G�}�l�[�W���[�̃|�C���^
	static CEnemyManager* m_Instance;
	// �G�N���X�̃|�C���^
	CEnemy* m_pEnemy[MAX_ENEMY];
	// �����������ǂ���
	bool m_bCreate;
};

#endif // _ENEMYMANAGER_H_