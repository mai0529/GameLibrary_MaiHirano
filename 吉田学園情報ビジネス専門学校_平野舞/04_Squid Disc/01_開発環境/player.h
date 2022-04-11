//===================================================================
//
//3Dアクション(player.h)
//Author:大原隆俊
//
//===================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//===================================================================
//マクロ定数
//===================================================================
#define PLAYER_SPEED		(0.5f)
#define MAX_PLAYER_PARTS	(10)
#define MAX_KEY				(4)
#define MAX_KEYSET			(3)
#define MAX_FLAME			(40.0f)

//===================================================================
//プレイヤーのキー構造体
//===================================================================
typedef struct
{
	D3DXVECTOR3 pos[MAX_PLAYER_PARTS];	//位置
	D3DXVECTOR3 rot[MAX_PLAYER_PARTS];	//向き
	float fMaxFlame;	//フレーム最大数
} Key;

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
	Key aKey[MAX_KEY];	//キー構造体
} KeySet;

//===================================================================
//プレイヤーのモーション構造体
//===================================================================
typedef struct
{
	int nUseKeySet;				//使用中のキーセット
	int nNumKeySet;				//キーセットの数
	KeySet aKeySet[MAX_KEYSET];	//キーセット構造体
} MotionSet;

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
}ModelParts;

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
	ModelParts aModel[MAX_PLAYER_PARTS];	//モデルパーツ数
	bool bUse;								//使用しているか否か
	PLAYER_TYPE type;						//ディスク持ってる人
}Player;

//===================================================================
//プロトタイプ宣言
//===================================================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

//===================================================================
//自作関数の宣言
//===================================================================
void SetMove(void);
Player *GetPlayer(void);
void SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, PLAYER_TYPE type);
#endif 
