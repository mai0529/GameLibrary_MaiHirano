//-------------------------------------------
//
// �A�C�e���}�l�[�W���[�̏��[itemManager.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _ITEMMANAGER_H_		// ��d�C���N���[�h�h�~
#define _ITEMMANAGER_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include <d3dx9.h>		// �`�揈���ɕK�v

//-------------------------------------------
// �C���N���[�h
//-------------------------------------------
#include "object.h"		// �I�u�W�F�N�g
#include "object2D.h"	// �I�u�W�F�N�g2D
#include "item.h"		// �G

//-------------------------------------------
// �O���錾
//-------------------------------------------
// ���e�A�C�e��
class CItemBom;
// ���ז��A�C�e��
class CItemObstacle;

//-------------------------------------------
// �N���X
//-------------------------------------------
class CItemManager : public CObject
{
private:
	// �G�̍ő吔
	static const int MAX_ITEM = 20;

private:
	// �O���t�@�C���ǂݍ��݂̍\����
	struct File
	{
		// �o���J�E���^�[
		int nCntApper;
		// �ʒu
		D3DXVECTOR3 pos;
		// ���
		int nType;
	};

private:
	// �R���X�g���N�^
	CItemManager();

public:
	// �f�X�g���N�^
	~CItemManager();

	// �C���X�^���X�̐���
	static void CreateInstance();
	// �C���X�^���X�̎擾
	static CItemManager* GetInstance();

	// �G�̐���
	void Create(CObject2D::MULTI_TYPE player, int yType, D3DXVECTOR3 pos);

	// ������
	HRESULT Init() override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

	// �A�C�e���̏���
	void Item(int nCntItem, CObject2D::MULTI_TYPE player, CItem::ITEM_TYPE type);

	// �A�C�e���̍폜
	void ItemDelete(int nCntItem);

	// ���e�A�C�e���̃|�C���^�����擾
	CItemBom* GetItemBom(int nCntItem);
	// ���ז��A�C�e���̃|�C���^�����擾
	CItemObstacle* GetItemObstacle(int nCntItem);

private:
	// �O���t�@�C���ǂݍ��ݗp
	void Load();

private:
	// �O���t�@�C���ǂݍ��ݗp
	File m_aFile[MAX_ITEM];
	// �O���t�@�C���p�A�C�e���J�E���g
	int m_nCntFileItem;
	// ���̃A�C�e���̃J�E���g
	int m_nNowCntItem;

	// �G�}�l�[�W���[�̃|�C���^
	static CItemManager* m_Instance;
	// �A�C�e���N���X�̃|�C���^
	CItem* m_pItem[MAX_ITEM];
};

#endif // _ITEMMANAGER_H_