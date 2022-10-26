//-------------------------------------------
//
// ���̏��[sound.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _SOUND_H_		// ��d�C���N���[�h�h�~
#define _SOUND_H_

//-------------------------------------------
// �C���N���[�h
//-------------------------------------------
#include <Windows.h>		// WindowsAPI�ɕK�v
#include "xaudio2.h"		// �T�E���h�����ɕK�v
//
//-------------------------------------------
// ���N���X
//-------------------------------------------
class CSound
{
public:
	// �T�E���h�t�@�C��
	enum SOUND_LABEL
	{
		SOUND_LABEL_TITLE = 0,			// �^�C�g��
		SOUND_LABEL_TUTORIAL,			// �`���[�g���A��
		SOUND_LABEL_GAME,				// �Q�[��
		SOUND_LABEL_RESULT,				// ���U���g
		SOUND_LABEL_SE_BULLET,			// �e
		SOUND_LABEL_SE_PLAYERDAMAGE,	// �v���C���[�_���[�W
		SOUND_LABEL_SE_SKILL,			// �X�L��
		SOUND_LABEL_SE_ITEM,			// �A�C�e��
		SOUND_LABEL_SE_ENEMYDAMAGE,		// �G�_���[�W
		SOUND_LABEL_SE_DECISION_CAT,	// ����_�L
		SOUND_LABEL_SE_DECISION_DOG,	// ����_��
		SOUND_LABEL_MAX,
	};

private:
	// �p�����[�^�\����
	struct PARAM
	{
		// �t�@�C����
		char* pFileName;
		// ���[�v�J�E���g
		int nCntLoop;
	};

private:
	// �R���X�g���N�^
	CSound();
public:
	// �f�X�g���N�^
	~CSound();

	// �C���X�^���X�̐���
	static void Create();
	// �C���X�^���X�̎擾
	static CSound* GetInstace();

	// ������
	HRESULT Init(HWND hWnd);
	// �I��
	void Uninit();
	// �Đ�
	HRESULT Play(SOUND_LABEL label);
	// ��~
	void Stop(SOUND_LABEL label);
	// ��~
	void Stop();

private:
	// �T�E���h�̃|�C���^
	static CSound* m_Instance;

	// �`�����N�̃`�F�b�N
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	// �`�����N�f�[�^�̓ǂݍ���
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2* m_pXAudio2;
	// �}�X�^�[�{�C�X
	IXAudio2MasteringVoice* m_pMasteringVoice;
	// �\�[�X�{�C�X
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX];
	// �I�[�f�B�I�f�[�^
	BYTE* m_apDataAudio[SOUND_LABEL_MAX];
	// �I�[�f�B�I�f�[�^�T�C�Y
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];
	// �p�����[�^
	static PARAM m_aParam[SOUND_LABEL_MAX];
};

#endif