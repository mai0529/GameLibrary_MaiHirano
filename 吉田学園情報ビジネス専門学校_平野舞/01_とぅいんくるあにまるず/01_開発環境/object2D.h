//-------------------------------------------
//
// 2D�|���S��[object2D.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _OBJECT2D_H_		// ��d�C���N���[�h�h�~
#define _OBJECT2D_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include "object.h"		// �I�u�W�F�N�g

//-------------------------------------------
// �N���X
//-------------------------------------------
class CObject2D: public CObject
{
public:
	// ���_�t�H�[�}�b�g
	const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	// ���_�f�[�^
	struct VERTEX_2D
	{
		D3DXVECTOR3 pos;		// ���_���W
		float rhw;				// ���W�ϊ��p�W��
		D3DCOLOR col;			// ���_�J���[
		D3DXVECTOR2 tex;		// �e�N�X�`�����W
	};

	// 1P��2P��
	enum MULTI_TYPE
	{
	 // �����Ȃ�
		MULTI_TYPE_NONE = -1,
		// 1P
		MULTI_TYPE_ONE,
		// 2P
		MULTI_TYPE_SECOND,
		// �v���C���[���̍ő吔
		COMMAND_TYPE_MAX
	};

public:
	// �R���X�g���N�^
	explicit CObject2D(int nPriority = 3);
	// �f�X�g���N�^
	~CObject2D() override;

	// ����
	static CObject2D* Create(char* cFileName,const D3DXVECTOR3& pos, const D3DXVECTOR3& size, int nPriority = 3);

	// ������
	HRESULT Init() override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

	// �ʒu�̐ݒ�
	void SetPosition(const D3DXVECTOR3& pos);
	// �ʒu�̎擾
	const D3DXVECTOR3& GetPosition() const;

	// �|���S���T�C�Y�̐ݒ�
	void SetSize(D3DXVECTOR3 size);
	// �|���S���T�C�Y�̎擾
	const D3DXVECTOR3& GetSize() const;

	// ���_�J���[�̐ݒ�
	void SetColor(D3DXCOLOR col);
	// ���_�J���[�̎擾
	D3DXCOLOR GetColor();

	// 1P��2P����ݒ�
	void SetPlayerType(MULTI_TYPE playerType);
	// 1P��2P�����擾
	MULTI_TYPE GetPlayerType();

	// �e�N�X�`���A�j���[�V�������W�̐ݒ�
	void SetTexAnim(int nDivisionU, int nDivisionV, int nNowPatternU, int nNowPatternV);

	// �A�j���[�V�������W�̐ݒ�
	void SetTexPos(float fTexU, float fTexV);

	// �ʒu�̍X�V
	void UpdatePos();

	// �e�N�X�`���̐ݒ�
	void LoadTexture(char* cFileName);

private:
	// ���_�o�b�t�@�̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;
	// �ʒu
	D3DXVECTOR3 m_pos;
	// �T�C�Y
	D3DXVECTOR3 m_size;
	// �J���[
	D3DXCOLOR m_col;

	// �e�N�X�`����
	char* m_cFileName;
	// 1P��2P���ǂ���
	MULTI_TYPE m_PlayerType;
};

#endif		// _OBJECT2D_H_