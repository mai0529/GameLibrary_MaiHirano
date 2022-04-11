//=============================================================================
//
//	�u���b�N�����̃w�b�_�[�t�@�C��
//	Author: SHUGO KURODA
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

//======================================================
//	�}�N����`
//======================================================
#define MAX_ITEM			(128)		//�u���b�N�̍ő吔
#define MAX_ITEM_TEX		(7)			//�u���b�N�̍ő�e�N�X�`����
#define ITEM_SIZE			(60.0f)		//�A�C�e���̃T�C�Y

//======================================================
//	�񋓌^
//======================================================
//�v���C���[�ԍ�
typedef enum
{
	ITEMSTATE_ON = 0,
	ITEMSTATE_OFF,
	ITEMSTATE_MAX
}ITEMSTATE;

//======================================================
//	�\����
//======================================================
//�A�C�e���\����
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu
	int nType;						//���
	ITEMSTATE state;				//���
	D3DXVECTOR2 BoxNum;				//�����Ă���g�̔ԍ�
	bool bUse;						//�g�p���Ă��邩�ǂ���
	bool bSelect;					//�I���������ǂ���
}Item;

//======================================================
//	�v���g�^�C�v�錾
//======================================================
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos, int nType, float ItemPosX, float ItemPosY);
void CollisionItem(D3DXVECTOR3 pos, float size);
void SelectItem(void);
Item *GetItem(void);

#endif