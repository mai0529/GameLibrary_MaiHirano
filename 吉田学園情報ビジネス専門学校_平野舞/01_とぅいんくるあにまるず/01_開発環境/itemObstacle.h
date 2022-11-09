//-------------------------------------------
//
// ���ז��^�A�C�e���̏��[itemObstacle.h]
// Author : ���앑
//
//-------------------------------------------

#ifndef _ITEMOBSTACLE_H_		// ��d�C���N���[�h�h�~
#define _ITEMOBSTACLE_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include "item.h"	// �A�C�e��

//-------------------------------------------
// �N���X
//-------------------------------------------
class CItemObstacle : public CItem
{
public:
	// �R���X�g���N�^
	CItemObstacle();
	// �f�X�g���N�^
	~CItemObstacle() override;

	// ����
	static CItemObstacle* Create(const D3DXVECTOR3& pos);

	// ������
	HRESULT Init() override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

	// �G�̔���
	void GenerationEnemy(MULTI_TYPE player,const D3DXVECTOR3& pos);
};

#endif		// _ITEMOBSTACLE_H_