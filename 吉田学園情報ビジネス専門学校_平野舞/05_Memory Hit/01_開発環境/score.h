#ifndef _SCORE_H_		//���̃}�N����`������Ȃ�������
#define _SCORE_H_		//2�d�C���N���[�h�h�~�̃}�N����`

//�}�N����`
#define MAX_SCORE		(2)			//�ő�X�R�A��
#define SCORE_SIZE_X	(80.0f)		//�X�R�A�\�L�̃T�C�Y(x)
#define SCORE_SIZE_Y	(150.0f)	//�X�R�A�\�L�̃T�C�Y(y)

//�v���g�^�C�v�錾
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int nScore);
void AddScore(int nValue);
int GetScore(void);

#endif