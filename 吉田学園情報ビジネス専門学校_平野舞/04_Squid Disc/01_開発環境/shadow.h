//===================================================================
//
//3Dアクション(shadow.h)
//Author:大原隆俊
//
//===================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

//===================================================================
//マクロ定数
//===================================================================
#define MAX_SHADOW	(128)	//影の最大数

//===================================================================
//影の構造体設定
//===================================================================
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//方向
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	bool bUse;				//使用しているか
}Shadow;

//===================================================================
//プロトタイプ宣言
//===================================================================
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);
void UnsetShadow(int nIdxShadow);

#endif 