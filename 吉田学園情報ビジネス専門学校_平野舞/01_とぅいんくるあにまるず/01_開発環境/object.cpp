//-----------------------------------------------------------------------------------------------
//
// �I�u�W�F�N�g����[object.cpp]
// Author : ���앑
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------------------------
#include "object.h"		// �I�u�W�F�N�g

//-----------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ��錾
//-----------------------------------------------------------------------------------------------
// �I�u�W�F�N�g�̃|�C���^
CObject* CObject::m_apObject[NUM_PRIORITY][MAX_OBJECT] = { nullptr };
// ��
int CObject::m_nNumAll = 0;
// �i�s���Ă��邩�ǂ���
bool CObject::m_bPause = false;

//-----------------------------------------------------------------------------------------------
// �R���X�g���N�^
//
// int nPriority �� �`��D�揇��
//-----------------------------------------------------------------------------------------------
CObject::CObject(int nPriority  /* = 3 */)
	:m_ObjectType(OBJECT_TYPE_NONE), m_parent(EOBJECT_PARENT_NONE)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nPriority][nCntObject] == nullptr)
		{// nullptr��������
			// �|�C���^���i�[
			m_apObject[nPriority][nCntObject] = this;

			// �i�[��̔ԍ�
			m_nID = nCntObject;

			// �D�揇�ʂ�ݒ�
			CObject::SetPriority(nPriority);

			// ���𑝂₷
			m_nNumAll++;

			break;
		}
	}
}

//-----------------------------------------------------------------------------------------------
//�@�f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CObject::~CObject()
{

}

//-----------------------------------------------------------------------------------------------
//�@���ׂẴ����������
//-----------------------------------------------------------------------------------------------
void CObject::ReleaseAll()
{
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != nullptr && nCntPriority != OBJECT_PRIORITY_FADE)
			{// nullptr�ł͂Ȃ�������
				// �I��
				m_apObject[nCntPriority][nCntObject]->Uninit();

				// �������̊J��
				delete m_apObject[nCntPriority][nCntObject];

				// nullptr�ɂ���
				m_apObject[nCntPriority][nCntObject] = nullptr;
			}
		}
	}
}

//-----------------------------------------------------------------------------------------------
//�@���ׂĂ��X�V
//-----------------------------------------------------------------------------------------------
void CObject::UpdateAll()
{
	if (!CObject::GetPause())
	{// �|�[�Y���Ă��Ȃ����
		for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
		{
			for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
			{
				if (m_apObject[nCntPriority][nCntObject] != nullptr)
				{// nullptr�ł͂Ȃ�������,�i�s���Ă�����
				 // �X�V
					m_apObject[nCntPriority][nCntObject]->Update();
				}
			}
		}
	}
	else if (CObject::GetPause())
	{// �|�[�Y����������
		for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
		{
			for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
			{
				if (m_apObject[nCntPriority][nCntObject] != nullptr && m_apObject[nCntPriority][nCntObject]->GetObjectParent() == EOBJECT_PARENT_PAUSE)
				{// nullptr�ł͂Ȃ�������,�i�s���Ă�����
				 // �X�V
					m_apObject[nCntPriority][nCntObject]->Update();
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------------------------
//�@���ׂĂ�`��
//-----------------------------------------------------------------------------------------------
void CObject::DrawAll()
{
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != nullptr)
			{// nullptr�ł͂Ȃ�������
			 // �`��
				m_apObject[nCntPriority][nCntObject]->Draw();
			}
		}
	}
}

//-----------------------------------------------------------------------------------------------
// �e�̍폜
//
// OBJECT_PARENT parent �� �e�w��
//-----------------------------------------------------------------------------------------------
void CObject::ReleaseParent(EOBJECT_PARENT parent)
{
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != nullptr)
			{// �e����v�Anullptr�ł͂Ȃ�������
				if (m_apObject[nCntPriority][nCntObject]->GetObjectParent() == parent)
				{// �e����v���Ă�����
					// �I��
					m_apObject[nCntPriority][nCntObject]->Uninit();

					// �������̊J��
					//delete m_apObject[nCntPriority][nCntObject];

					// nullptr�ɂ���
					m_apObject[nCntPriority][nCntObject] = nullptr;
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------------------------
// �i�s���Ă��邩�ǂ����̐ݒ�
//
// bool bPause �� true:�|�[�Y��/ false:�|�[�Y���Ă��Ȃ�
//-----------------------------------------------------------------------------------------------
void CObject::SetPause(bool bPause)
{
	m_bPause = bPause;
}

//-----------------------------------------------------------------------------------------------
// �i�s���Ă��邩�ǂ����̏����擾
//-----------------------------------------------------------------------------------------------
bool CObject::GetPause()
{
	return m_bPause;
}

//-----------------------------------------------------------------------------------------------
// �D�揇�ʂ̐ݒ�
//
// int nPriority �� �`��D�揇�ʂ��w��
//-----------------------------------------------------------------------------------------------
void CObject::SetPriority(int nPriority)
{
	m_nPriority = nPriority;
}

//-----------------------------------------------------------------------------------------------
// �D�揇�ʂ̎擾
//-----------------------------------------------------------------------------------------------
int CObject::GetPriority()
{
	return m_nPriority;
}

//-----------------------------------------------------------------------------------------------
// �I�u�W�F�N�g�̎�ނ�ݒ�
//
// OBJECT_TYPE objectType �� �I�u�W�F�N�g�̎�ނ��w�� 
//-----------------------------------------------------------------------------------------------
void CObject::SetObjectType(EOBJECT_TYPE objectType)
{
	m_ObjectType = objectType;
}

//-----------------------------------------------------------------------------------------------
// �I�u�W�F�N�g�̎�ނ��擾
//-----------------------------------------------------------------------------------------------
CObject::EOBJECT_TYPE CObject::GetObjectType() const
{
	return m_ObjectType;
}

//-----------------------------------------------------------------------------------------------
// �e��ݒ�
//
// OBJECT_PARENT parent �� �I�u�W�F�N�g�̐e���w��
//-----------------------------------------------------------------------------------------------
void CObject::SetObjectParent(EOBJECT_PARENT parent)
{
	m_parent = parent;
}

//-----------------------------------------------------------------------------------------------
// �e���擾
//-----------------------------------------------------------------------------------------------
CObject::EOBJECT_PARENT CObject::GetObjectParent()
{
	return m_parent;
}

//-----------------------------------------------------------------------------------------------
// �I�u�W�F�N�g�̃|�C���^���擾
//
// int nCntObject �� ���Ԗڂ��w��
// int nPriority ���@�`��D�揇�ʂ��w��
//-----------------------------------------------------------------------------------------------
CObject* CObject::GetObject(int nCntObject, int nPriority /* = 3 */)
{
	return m_apObject[nPriority][nCntObject];
}

//-----------------------------------------------------------------------------------------------
//�@�I�u�W�F�N�g�̔j��
//-----------------------------------------------------------------------------------------------
void CObject::Release()
{
	if (m_apObject[m_nPriority][m_nID] != nullptr)
	{// nullptr�ł͂Ȃ�������
		// �ϐ����i�[
		int nID = m_nID;

		// �D��x���i�[
		int nPriority = m_nPriority;

		// �������̊J��
		delete m_apObject[nPriority][nID];

		// nullptr�ɖ߂�
		m_apObject[nPriority][nID] = nullptr;

		// �ő�������炷
		m_nNumAll--;
	}
}