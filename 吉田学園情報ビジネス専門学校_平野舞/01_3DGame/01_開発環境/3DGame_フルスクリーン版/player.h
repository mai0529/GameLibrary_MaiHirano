// ------------------------------------------
//
//プレイヤー表示情報[player.h]
//Author:平野舞
//
//-------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

//インクルードファイル
#include "main.h"

//マクロ定義
#define PLAYER_DIS		(3.5f)		//モデルの移動距離
#define MAX_MODELPARTS	(30)		//モデルのパーツ数

//プレイヤーの状態
typedef enum
{
	PLAYERSTATE_NORMAL = 0,		//通常状態
	PLAYERSTATE_DAMAGE,			//ダメージ状態
	PLAYERSTATE_DATH,			//死亡状態
	PLAYERSTATE_MAX
}PLAYERSTATE;

//外部ファイルの構造体
typedef struct
{
	int nIndex;		//インデックス
	int nParent;	//親インデックス
	float fPosX;	//位置X
	float fPosY;	//位置Y
	float fPosZ;	//位置Z
	float fRotX;	//向きX
	float fRotY;	//向きY
	float fRotZ;	//向きZ
}PlayerFile;

//モデルの構造体
typedef struct
{
	LPD3DXMESH pMesh;				//メッシュ情報へのポインタ
	LPD3DXBUFFER pBuffMat;			//マテリアル情報へのポインタ
	DWORD nNumMat;					//マテリアル情報の数
	LPDIRECT3DTEXTURE9 pTexture;	//テクスチャの読み込み
	D3DXMATRIX mtxWorld;			//ワールドマトリックス
	D3DXVECTOR3 pos;				//位置
	D3DXVECTOR3 rot;				//向き
	int nIdxModelParent;			//親モデルのインデックス
}ModelParts;

//プレイヤー構造体　
typedef struct
{
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 move;			//移動量
	D3DXVECTOR3 posOld;			//前の位置
	D3DXVECTOR3 rot;			//向き
	D3DXVECTOR3 rotDest;		//目的の角度
	D3DXMATRIX mtxWorld;		//ワールドマトリックス
	D3DXVECTOR3 size;			//サイズ
	D3DXVECTOR3 vtxMin;			//最小頂点値
	D3DXVECTOR3 vtxMax;			//最大頂点値
	ModelParts aModel[MAX_MODELPARTS];		//モデルのパーツ数
	bool bUse;					//使用するかどうか
	PLAYERSTATE state;			//状態管理
	int nCntState;				//状態管理カウンター
	int nLife;					//ライフ
	int nIdxShadow;				//影の番号
}Player;

//Motion構造体
typedef struct
{
	int nLoop;		//ループ判定
	int nNumKey;	//キー数
}MotionSet;

//Key構造体　
typedef struct
{
	float fPosX;	//位置X
	float fPosY;	//位置Y
	float fPosZ;	//位置Z
	float fRotX;	//向きX
	float fRotY;	//向きY
	float fRotZ;	//向きZ
}Key;

//プロトタイプ宣言
void InitPlayer(void);			//初期化処理
void UninitPlayer(void);		//終了処理
void UpdatePlayer(void);		//更新処理
void DrawPlayer(void);			//描画処理
void MovePlayer(void);			//プレイヤーの移動処理
void MotionPlayer(int nMotion);	//モーション処理
void StatePlayer(void);			//状態処理
void HitPlayer(int nDamage);	//ヒット処理
float GetPlayerRot(void);		//プレイヤーの角度を取得
Player * GetPlayer(void);		//プレイヤー情報の取得
void LoadPlayerFile(void);		//外部ファイル情報の読み込み

#endif