//=============================================================================
//
// �^�C�g�������̃w�b�_�[�t�@�C��
// Author : ���c ����
//
//=============================================================================
#ifndef _TITLE_H_			//���̃}�N����`������Ȃ�������
#define _TITLE_H_			//2�d�C���N���[�h�h�~�̃}�N����`

//======================================================
//	�񋓌^�̒�`
//======================================================
//�^�C�g�����̃e�N�X�`���ԍ�
typedef enum
{
	TITLENUM_BG = 0,			//�w�i
	TITLENUM_TITLE,				//�^�C�g��
	TITLENUM_PRESSENTER,		//PressEnter
	TITLENUM_SELECTGAME,		//�I����(�Q�[��)
	TITLENUM_SELECTTUTORIAL,	//�I����(�`���[�g���A��)
	TITLENUM_MAX
}TITLENUM;

//======================================================
//	�\���̂̒�`
//======================================================
//�e�^�C�g�����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXVECTOR2 size;		//�傫��
	D3DXCOLOR color;		//�F
	bool bUse;				//�g�p���Ă��邩�ǂ���
}Title;

//���j���[��ʏ��
typedef struct
{
	bool bGameStartPush;	//�X�^�[�g���o�̌J��Ԃ��h�~
	int nCntColorA;			//���l�̐ݒ�J�E���^�[
	int nSelect;			//�Q�[���̑I�����ڃJ�E���^�[
	int nCntEnter;			//���j���[�I�����p
}MenuInfo;
//======================================================
//	�v���g�^�C�v�錾
//======================================================
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);
void SetTitle(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, D3DXCOLOR color);

#endif