//===================================================================
//
//3Dアクション(mob.h)
//Author:大原隆俊
//
//===================================================================
#ifndef _MOB_H_
#define _MOB_H_

//===================================================================
//マクロ定数
//===================================================================
#define MOB_SPEED		(0.5f)
#define MAX_MOB_PARTS	(10)
#define MAX_MOB_KEY				(4)
#define MAX_MOB_KEYSET			(3)
#define MAX_MOB_FLAME			(40.0f)

//===================================================================
//プレイヤーのキー構造体
//===================================================================
typedef struct
{
	D3DXVECTOR3 pos[MAX_MOB_PARTS];	//位置
	D3DXVECTOR3 rot[MAX_MOB_PARTS];	//向き
	float fMaxFlame;	//フレーム最大数
} MobKey;

//===================================================================
//プレイヤーのキーセット構造体
//===================================================================
typedef struct
{
	float fFlame;		//現在のフレーム
	bool bLoop;			//ループするか否か
	bool bUse;			//終了しているか否か
	int nNum_Key;		//キーの数
	int nUseKey;		//使用中のキー
	MobKey aMobKey[MAX_MOB_KEY];	//キー構造体
} MobKeySet;

//===================================================================
//プレイヤーのモーション構造体
//===================================================================
typedef struct
{
	int nUseKeySet;				//使用中のキーセット
	int nNumKeySet;				//キーセットの数
	MobKeySet aMobKeySet[MAX_MOB_KEYSET];	//キーセット構造体
} MobMotionSet;

//===================================================================
//プレイヤーのパーツ構造体
//===================================================================
typedef struct
{
	LPD3DXMESH pMesh;				//メッシュへのポインタ
	LPD3DXBUFFER pBuffMat;			//マテリアル情報へのポインタ
	DWORD nNumMat;					//マテリアル情報数
	D3DXMATRIX mtxWorld;			//ワールドマトリックス
	D3DXVECTOR3 pos;				//位置
	D3DXVECTOR3 rot;				//向き
	int nIdx;						//インデックス番号
	int nIdxModelParent;			//親モデルのインデックス
}MobModelParts;

//===================================================================
//モデル構造体
//===================================================================
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 posOld;						//ひとつ前の位置
	D3DXVECTOR3 move;						//移動量
	D3DXVECTOR3 rot;						//方向
	D3DXVECTOR3 size;						//大きさ
	D3DXVECTOR3 vtxMin;						//頂点の最小値
	D3DXVECTOR3 vtxMax;						//頂点の最大値
	D3DXMATRIX mtxWorld;					//ワールドマトリックス
	int IdxShadow;							//影の設置
	MobModelParts aModel[MAX_MOB_PARTS];	//モデルパーツ数
	bool bUse;								//使用しているか否か
	PLAYER_TYPE type;						//ディスク持ってる人
}MOB;

//===================================================================
//プロトタイプ宣言
//===================================================================
void InitMob(void);
void UninitMob(void);
void UpdateMob(void);
void DrawMob(void);

//===================================================================
//自作関数の宣言
//===================================================================
void SetMobMove(void);
MOB *GetMob(void);
void SetMob(D3DXVECTOR3 pos, D3DXVECTOR3 rot, PLAYER_TYPE type);
#endif 