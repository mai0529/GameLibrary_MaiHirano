#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"

//�}�N����`
#define MAX_RANK	(5)		//�����N��

//�v���g�^�C�v�錾
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
void ResetRanking(void);
void SetRanking(int nScore);

#endif