//-------------------------------------------
//
// �e�N�X�`���̏��[texture.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _TEXTURE_H_		// ��d�C���N���[�h�h�~
#define _TEXTURE_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include <d3dx9.h>		// �`�揈���ɕK�v

//-------------------------------------------
// �N���X
//-------------------------------------------
class CRsTexture
{
private:
	// �ő啶����
	static const int MAX_NAME = 128;

public:
	// �R���X�g���N�^
	CRsTexture();
	// �f�X�g���N�^
	~CRsTexture();

	// �e�N�X�`���̐ݒ�
	HRESULT SetTexture();
	// �e�N�X�`�����̎擾
	LPDIRECT3DTEXTURE9 GetTexture();
	//�e�N�X�`�����̓ǂݍ���
	void LoadFile(char* cFileName);
	// �e�N�X�`���̔j��
	void Uninit();

	// �n�b�V���l�̐ݒ�
	void SetHashCode(unsigned int HashCode);
	// �n�b�V���l�̎擾
	unsigned int GetHashCode();

private:
	// �e�N�X�`���|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture;
	// �e�N�X�`����
	char* m_cFileName;
	// �n�b�V���l
	unsigned int m_HashCode;
};

#endif // _TEXTURE_H_