//=============================================================================
// ���S����
// Author : ���c ����
//=============================================================================
#ifndef _LOGO_H_
#define _LOGO_H_

//======================================================
//	�}�N����`
//======================================================
#define LOGO_SIZE_X		(200.0f)		//�Q�[�����̃��S��X�T�C�Y
#define LOGO_SIZE_Y		(50.0f)			//�Q�[�����̃��S��Y�T�C�Y
#define MAX_LOGO		(5)				//�Q�[�����̃��S�e�N�X�`����

//======================================================
//	�񋓌^�̒�`
//======================================================
//���S�̃e�N�X�`���ԍ�
typedef enum
{
	LOGONUM_READY = 0,		//Ready
	LOGONUM_START,			//Start
	LOGONUM_MEMORIZE,		//�o����
	LOGONUM_SEARCH,			//�T��
	LOGONUM_FINISH,			//���イ���[��
	LOGONUM_MAX
}TITLENUM;

//======================================================
//	�\���̒�`
//======================================================
//�v���C���[�\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	int nLife;			//����
	int nType;			//���
	bool bUse;			//�g�p���Ă��邩�ǂ���
}Logo;

//�v���C���[�\����
typedef struct
{
	int nCnt;			//�\������܂ł̃J�E���^�[
	bool bUse;			//�g�p���Ă��邩�ǂ���
}LogoInfo;

// �v���g�^�C�v�錾
void InitLogo(void);
void UninitLogo(void);
void UpdateLogo(void);
void DrawLogo(void);
void SetLogo(int nType, int nLife);

#endif