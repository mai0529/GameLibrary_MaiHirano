//----------------------------------------
//　プレイヤー
//----------------------------------------
#ifndef _MODEL2_H_
#define _MODEL2_H_

#include "main.h"

//マクロ定義
#define MAX_PLAYER			(1)		//プレイヤーの最大数
#define PLAYER_SPEED		(3.0f)	//プレイヤーの移動速度
#define MAX_PARTS			(12)	//最大パーツ数

//モデルの構造体
typedef struct
{
	LPD3DXMESH pMesh;		//メッシュ情報へのポインタ
	LPD3DXBUFFER pBuffMat;	//マテリアル情報へのポインタ
	DWORD nNumMat;			//マテリアル情報の数
	D3DXMATRIX mtxWorld;	//ワールドマトリクス
	D3DXVECTOR3 pos;		//現在の位置
	D3DXVECTOR3 posOld;		//前回の位置
	D3DXVECTOR3 rot;		//角度
	int nIdxModelParent;	//親モデルのインデックス
}ModelParts;

/**/
typedef struct
{
	D3DXVECTOR3 pos;		//現在の位置
	D3DXVECTOR3 posOld;		//前回の位置
	D3DXVECTOR3 rot;		//向き
	D3DXVECTOR3 move;		//移動量
	D3DXMATRIX mtxWorld;	//ワールドマトリクス
	D3DXVECTOR3 vtxMin;		//頂点の最小値を取得用
	D3DXVECTOR3 vtxMax;		//頂点の最大値を取得用
	D3DXVECTOR3 size;		//サイズ保存用
}Test;

typedef enum
{
	ROT_UP = 0,
	ROT_DOWN,
	ROT_RIGHT,
	ROT_LEFT
}PlayerRot;

//プレイヤーの構造体
typedef struct
{
	D3DXVECTOR3 pos;		//現在の位置
	D3DXVECTOR3 posOld;		//前回の位置
	D3DXVECTOR3 rot;		//向き
	D3DXVECTOR3 move;		//移動量
	D3DXMATRIX mtxWorld;	//ワールドマトリクス
	float diff;				//差分用
	float rotDest;			//目的の角度
	int IdxShadow;			//影用
	D3DXVECTOR3 vtxMin;		//頂点の最小値を取得用
	D3DXVECTOR3 vtxMax;		//頂点の最大値を取得用
	D3DXVECTOR3 size;		//サイズ保存用
	ModelParts aModel[MAX_PARTS];	//モデルの情報[最大パーツ数分]
	bool bIsJumping;
	PlayerRot PlayerRot;
}Model2;

//プロトタイプ宣言
void InitPlayer(void);		//プレイヤーの初期化
void UninitPlayer(void);	//プレイヤーの終了
void UpdatePlayer(void);	//プレイヤーの更新
void DrawPlayer(void);		//プレイヤーの描画
void MovePlayer(void);		//プレイヤーの移動
Model2 * GetModel2(void);	//プレイヤーの情報
void MotionPlayer(int nMotion);		//プレイヤーのモーション設定
void SetMotion(int nSet);	//モーションを設定する

#endif
//
////=======================================
////   model.h
////=======================================
//#ifndef _MODEL2_H_
//#define _MODEL2_H_	
//#include "main.h"
//#include "game.h"
////マクロ定義
//#define SPEED (1.50f)
//#define MODEL_MAX (128)
//#define NUM_MODEL (2)
//typedef enum
//{
//	MODEL_TYPE_BUS = 0,
//	MODEL_TYPE_MAX2
//}MODEL_TYPE2;
////影の構造体
//typedef struct
//{
//	D3DXVECTOR3 move;
//	D3DXVECTOR3 pos;							//位置
//	D3DXCOLOR col;								//色
//	D3DXVECTOR3 rot;
//	D3DXVECTOR3 rotDestModel;
//	D3DXMATRIX mtxWorld;
//	D3DXVECTOR3 vtxMinModel;
//	D3DXVECTOR3 vtxMaxModel;
//	D3DXVECTOR3 scaleVector;
//	MODEL_TYPE2 type;
//	bool bUse;
//
//}MODEL2;
//
////プロトタイプ宣言
//void InitModel2(void);
//void UninitModel2(void);
//void UpdateModel2(void);
//void DrawModel2(void);
//void SetModel2(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL_TYPE2 type);
//void CollisionModel2(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld,/* D3DXVECTOR3 *pMove,*/ D3DXVECTOR3 size);
//MODEL2 *GetModel2(void);
//#endif