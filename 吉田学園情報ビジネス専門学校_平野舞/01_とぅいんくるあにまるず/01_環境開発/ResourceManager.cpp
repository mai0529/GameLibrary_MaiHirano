//---------------------------------------------------------------------------------
//
// ���\�[�X�}�l�[�W���[�̏���[ResourceManager.cpp]
// Author : ���앑
//
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//---------------------------------------------------------------------------------
#include "application.h"		// �A�v���P�[�V����
#include "renderer.h"			// �����_�����O
#include "ResourceManager.h"	// ���\�[�X�}�l�[�W���[
#include "texture.h"			// �e�N�X�`��

//---------------------------------------------------------------------------------
// �ÓI�����o�ϐ��錾
//---------------------------------------------------------------------------------
// ���\�[�X�}�l�[�W���[
CResourceManager* CResourceManager::m_Instance = nullptr;

//---------------------------------------------------------------------------------
//	�R���X�g���N�^
//---------------------------------------------------------------------------------
CResourceManager::CResourceManager()
{
	for (int nCntTexture = 0; nCntTexture < MAX_TEXTURE; nCntTexture++)
	{
		m_pTexture[nCntTexture] = nullptr;
	}
}

//---------------------------------------------------------------------------------
//	�f�X�g���N�^
//---------------------------------------------------------------------------------
CResourceManager::~CResourceManager()
{

}

//---------------------------------------------------------------------------------
// �C���X�^���X�̐���
//---------------------------------------------------------------------------------
void CResourceManager::CreateInstance()
{
	if (m_Instance == nullptr)
	{// nullptr��������
		m_Instance = new CResourceManager;
	}
}

//---------------------------------------------------------------------------------
// �C���X�^���X�̎擾
//---------------------------------------------------------------------------------
CResourceManager* CResourceManager::GetInstance()
{
	return m_Instance;
}

//---------------------------------------------------------------------------------
// �e�N�X�`���̓ǂݍ���
//---------------------------------------------------------------------------------
void CResourceManager::LoadTexture(char* cFileName)
{
	for (int nCntTexture = 0; nCntTexture < MAX_TEXTURE; nCntTexture++)
	{
		if (m_pTexture[nCntTexture] == nullptr)
		{// nullptr��������
			// �������𐶐�
			m_pTexture[nCntTexture] = new CRsTexture;
			// �t�@�C�����̓ǂݍ���
			m_pTexture[nCntTexture]->LoadFile(cFileName);
			// �e�N�X�`���̓ǂݍ���
			m_pTexture[nCntTexture]->SetTexture();
			// �n�b�V���l�̐ݒ�
			m_pTexture[nCntTexture]->SetHashCode(GetHashCode(cFileName));

			break;
		}
	}
}

//---------------------------------------------------------------------------------
// �e�N�X�`���̓ǂݍ���( ���� )
//---------------------------------------------------------------------------------
void CResourceManager::LoadTexture(char* cFileName[])
{
	for (int nCntTexture = 0; cFileName[nCntTexture] != nullptr; nCntTexture++)
	{
		LoadTexture(cFileName[nCntTexture]);
	}
}

//---------------------------------------------------------------------------------
// �e�N�X�`���̔j��
//---------------------------------------------------------------------------------
void CResourceManager::UnloadTexture(char* cFileName)
{
	for (int nCntTexture = 0; nCntTexture < MAX_TEXTURE; nCntTexture++)
	{
		if (m_pTexture[nCntTexture] != nullptr)
		{
			// �n�b�V���l���ׂ�
			if (m_pTexture[nCntTexture]->GetHashCode() == GetHashCode(cFileName))
			{
				// �I��
				m_pTexture[nCntTexture]->Uninit();

				// ��������j������
				delete m_pTexture[nCntTexture];

				// nullptr�ɖ߂�
				m_pTexture[nCntTexture] = nullptr;

				break;
			}
		}
	}
}

//---------------------------------------------------------------------------------
// �e�N�X�`���̔j��( ���� )
//---------------------------------------------------------------------------------
void CResourceManager::UnloadTexture(char* cFileName[])
{
	for (int nCntTexture = 0; cFileName[nCntTexture] != nullptr; nCntTexture++)
	{
		UnloadTexture(cFileName[nCntTexture]);
	}
}

//---------------------------------------------------------------------------------
// �S�Ẵe�N�X�`���̔j��
//---------------------------------------------------------------------------------
void CResourceManager::AllUnloadTexture()
{
	for (int nCntTexture = 0; nCntTexture < MAX_TEXTURE; nCntTexture++)
	{
		if (m_pTexture[nCntTexture] != nullptr)
		{
			// �I��
			m_pTexture[nCntTexture]->Uninit();

			// ��������j������
			delete m_pTexture[nCntTexture];

			// nullptr�ɖ߂�
			m_pTexture[nCntTexture] = nullptr;
		}
	}

	if (m_Instance != nullptr)
	{// nullptr�ł͂Ȃ�������
		// ��������j��
		delete m_Instance;

		// nullptr�ɂ���
		m_Instance = nullptr;
	}
}

//---------------------------------------------------------------------------------
// �e�N�X�`���̎擾
//---------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CResourceManager::GetTexture(char* cFileName)
{
	for (int nCntTexture = 0; nCntTexture < MAX_TEXTURE; nCntTexture++)
	{
		if (m_pTexture[nCntTexture] != nullptr)
		{
			// �n�b�V���l���ׂ�
			if (m_pTexture[nCntTexture]->GetHashCode() == GetHashCode(cFileName))
			{
				return m_pTexture[nCntTexture]->GetTexture();
			}
		}
	}

	return nullptr;
}

//---------------------------------------------------------------------------------
// �n�b�V���l�̐���
//---------------------------------------------------------------------------------
uint32_t CResourceManager::GetHashCode(char* cFileName)
{
	if (cFileName == nullptr)
	{
		return -1;
	}

	uint32_t crc = 0xffffffff;

	size_t length = strlen(cFileName);
	for (size_t nCount = 0; nCount < length; nCount++)
	{
		crc = CRC32TAB[(crc ^ cFileName[nCount]) & 0Xff] ^ (crc >> 8);
	}

	return crc ^ 0xffffffff;
}