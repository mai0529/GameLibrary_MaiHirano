//---------------------------------------------------------------------------------
//
// �A�C�e���}�l�[�W���[�̏���[itemManager.cpp]
// Author : ���앑
//
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// �萔�錾
//---------------------------------------------------------------------------------
// �e�L�X�g�t�@�C��
#define TEXT_ITEM		("data/TEXT/item.txt")

//---------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//---------------------------------------------------------------------------------
#include <stdio.h>				// �O���t�@�C���ǂݍ��ݗp
#include "itemManager.h"		// �A�C�e���}�l�[�W���[
#include "itemBom.h"			// ���e�^�A�C�e��
#include "itemObstacle.h"		// ���ז��^�A�C�e��
#include "time.h"				// �^�C�}�[

//---------------------------------------------------------------------------------
// �萔�錾
//---------------------------------------------------------------------------------
// 1P����2P���̋���
static const float ITEM_DIS = 700.0f;

//---------------------------------------------------------------------------------
// �ÓI�����o�ϐ��錾
//---------------------------------------------------------------------------------
// �G�}�l�[�W���[�̃|�C���^
CItemManager* CItemManager::m_Instance = nullptr;

//---------------------------------------------------------------------------------
//	�R���X�g���N�^
//---------------------------------------------------------------------------------
CItemManager::CItemManager()
	:m_nCntFileItem(0), m_nNowCntItem(0)
{
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		// �o���J�E���g
		m_aFile[nCntItem].nCntApper = 0;
		// �ʒu
		m_aFile[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// ���
		m_aFile[nCntItem].nType = CItem::ITEM_TYPE_BOM;
	}

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		m_pItem[nCntItem] = nullptr;
	}
}

//---------------------------------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------------------------------
CItemManager::~CItemManager()
{

}

//---------------------------------------------------------------------------------
// �C���X�^���X�̐���
//---------------------------------------------------------------------------------
void CItemManager::CreateInstance()
{
	if (m_Instance == nullptr)
	{// nullptr��������
	 // �������𐶐�
		m_Instance = new CItemManager;
	}
}

//---------------------------------------------------------------------------------
// �C���X�^���X�̎擾
//---------------------------------------------------------------------------------
CItemManager* CItemManager::GetInstance()
{
	if (m_Instance != nullptr)
	{// nullptr�ł͂Ȃ�������
		return m_Instance;
	}

	return nullptr;
}

//---------------------------------------------------------------------------------
// �A�C�e���̐���
//---------------------------------------------------------------------------------
void CItemManager::Create(MULTI_TYPE player, int nType, D3DXVECTOR3 pos)
{
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (m_pItem[nCntItem] == nullptr)
		{// nullptr��������
			switch (nType)
			{
				// ���e
			case CItem::ITEM_TYPE_BOM:
				m_pItem[nCntItem] = CItemBom::Create(pos);
				break;
				// ���ז�
			case CItem::ITEM_TYPE_OBSTACLE:
				m_pItem[nCntItem] = CItemObstacle::Create(pos);
				break;
				// ���̑�
			default:
				break;
			}

			// �i�[��̔ԍ�
			m_pItem[nCntItem]->SetID(nCntItem);

			// 1P����2P����
			m_pItem[nCntItem]->SetPlayerType(player);

			break;
		}
	}
}

//---------------------------------------------------------------------------------
// ������
//---------------------------------------------------------------------------------
void CItemManager::Init()
{
	// �O���t�@�C���̓ǂݍ���
	Load();
}

//---------------------------------------------------------------------------------
// �I��
//---------------------------------------------------------------------------------
void CItemManager::Uninit()
{
	if (m_Instance != nullptr)
	{// nullptr�ł͂Ȃ�������
	 // ���������폜����
		delete m_Instance;

		// nullptr�ɂ���
		m_Instance = nullptr;
	}
}

//---------------------------------------------------------------------------------
// �X�V
//---------------------------------------------------------------------------------
void CItemManager::Update()
{
	if (m_nNowCntItem <= m_nCntFileItem && CTime::GetInstance()->GetTime() == m_aFile[m_nNowCntItem].nCntApper)
	{
		// 1P��
		CItemManager::Create(MULTI_TYPE_ONE, m_aFile[m_nNowCntItem].nType, m_aFile[m_nNowCntItem].pos);
		// 2P��
		CItemManager::Create(MULTI_TYPE_SECOND, m_aFile[m_nNowCntItem].nType, D3DXVECTOR3(m_aFile[m_nNowCntItem].pos.x + ITEM_DIS, m_aFile[m_nNowCntItem].pos.y, 0.0f));

		// �J�E���g�𑝂₷
		m_nNowCntItem++;
	}
}

//-----------------------------------------------------------------------------------------------
// �A�C�e���̏���
//
// ITEM_TYPE type �� �A�C�e���̎��
//-----------------------------------------------------------------------------------------------
void CItemManager::Item(int nCntItem,MULTI_TYPE player, CItem::ITEM_TYPE type)
{
	switch (type)
	{
	case CItem::ITEM_TYPE_BOM:		// ���e
	{
		// �����擾
		CItemBom* pBom = CItemManager::GetInstance()->GetItemBom(nCntItem);

		if (pBom != nullptr)
		{// nullptr�ł͂Ȃ�������
			// �폜
			pBom->DeleteEnemy(player);
		}
	}
		break;
	case CItem::ITEM_TYPE_OBSTACLE:	// ���ז�
	{
		// �����擾
		CItemObstacle* pObstacle = CItemManager::GetInstance()->GetItemObstacle(nCntItem);

		if (pObstacle != nullptr)
		{// nullptr�ł͂Ȃ�������
			// ���ז��G�𐶐�
			pObstacle->GenerationEnemy(player, pObstacle->GetPosition());
		}
	}
		break;
	default:
		break;
	}
}

//---------------------------------------------------------------------------------
// �A�C�e���̍폜
//---------------------------------------------------------------------------------
void CItemManager::ItemDelete(int nCntItem)
{
	if (m_pItem[nCntItem] != nullptr)
	{// nullptr�ł͂Ȃ�������
		// �I��
		m_pItem[nCntItem]->Uninit();

		// nullptr�ɂ���
		m_pItem[nCntItem] = nullptr;
	}

}

//---------------------------------------------------------------------------------
// �A�C�e���̃|�C���^�����擾
//---------------------------------------------------------------------------------
CItemBom* CItemManager::GetItemBom(int nCntItem)
{
	if (m_pItem[nCntItem] != nullptr && m_pItem[nCntItem]->GetItemType() == CItem::ITEM_TYPE_BOM)
	{// nullptr�ł͂Ȃ��A��ނ����e��������
		CItemBom* pBom = (CItemBom*)m_pItem[nCntItem];

		return pBom;
	}

	return nullptr;
}

//---------------------------------------------------------------------------------
// ���ז��A�C�e���̃|�C���^�����擾
//---------------------------------------------------------------------------------
CItemObstacle* CItemManager::GetItemObstacle(int nCntItem)
{
	if (m_pItem[nCntItem] != nullptr && m_pItem[nCntItem]->GetItemType() == CItem::ITEM_TYPE_OBSTACLE)
	{// nullptr�ł͂Ȃ��A��ނ����e��������
		CItemObstacle* pObstacle = (CItemObstacle*)m_pItem[nCntItem];

		return pObstacle;
	}

	return nullptr;
}

//---------------------------------------------------------------------------------
// �O���t�@�C���ǂݍ��ݗp
//---------------------------------------------------------------------------------
void CItemManager::Load()
{
	char cData[125];

	// �t�@�C�����J��
	FILE* pFile = fopen(TEXT_ITEM, "r");

	if (pFile == nullptr)
	{// �t�@�C�����J���Ȃ�������
		printf("�t�@�C�����J���܂���ł����B");
		return;
	}

	while (1)
	{
		// ������ǂݍ���
		fscanf(pFile, "%s", &cData[0]);

		if (strcmp(&cData[0], "ITEMSET") == 0)
		{// ENEMYSET�̕�������������
			do
			{
				// ������ǂݍ���
				fscanf(pFile, "%s", &cData[0]);

				if (strcmp(&cData[0], "COUNTER") == 0)
				{// �o���J�E���^�[
					fscanf(pFile, "%s", &cData[0]);
					fscanf(pFile, "%d", &m_aFile[m_nCntFileItem].nCntApper);
				}
				else if (strcmp(&cData[0], "POS") == 0)
				{// �ʒu
					fscanf(pFile, "%s", &cData[0]);
					fscanf(pFile, "%f", &m_aFile[m_nCntFileItem].pos.x);
					fscanf(pFile, "%f", &m_aFile[m_nCntFileItem].pos.y);
					fscanf(pFile, "%f", &m_aFile[m_nCntFileItem].pos.z);
				}
				else if (strcmp(&cData[0], "TYPE") == 0)
				{// ���
					fscanf(pFile, "%s", &cData[0]);
					fscanf(pFile, "%d", &m_aFile[m_nCntFileItem].nType);
				}
			} while (strcmp(&cData[0], "END_ITEMSET") != 0);
			// �J�E���g����
			m_nCntFileItem++;
		}
		if (strcmp(&cData[0], "END_SCRIPT") == 0)
		{// END_ENEMYSET�̕�������������
			break;
		}
	}
}