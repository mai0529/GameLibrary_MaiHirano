//----------------------------------------
//　ベクトルの処理
//　Author：橋野幹生
//----------------------------------------
#include "vec.h"

//ベクトルの構造体
typedef struct
{
	D3DXVECTOR3 start;
	D3DXVECTOR3 end;
	D3DXVECTOR3 vec;
	float size;
	D3DXVECTOR3 nor;
}VECTOR;

VECTOR g_vecA[4];

//---------------------------------------------------
//	ベクトルの設定
//---------------------------------------------------
void SetVec(float X, float Z)
{
	g_vecA[0].start = D3DXVECTOR3(-X, 0.0f, Z);		//上
	g_vecA[0].end = D3DXVECTOR3(X, 0.0f, Z);		//上

	g_vecA[1].start = D3DXVECTOR3( X, 0.0f, -Z);	//下
	g_vecA[1].end = D3DXVECTOR3(-X, 0.0f, -Z);		//下

	g_vecA[2].start = D3DXVECTOR3( X, 0.0f,  Z);	//右
	g_vecA[2].end = D3DXVECTOR3(X, 0.0f, -Z);		//右

	g_vecA[3].start = D3DXVECTOR3(-X, 0.0f, -Z);	//左
	g_vecA[3].end = D3DXVECTOR3(-X, 0.0f, Z);		//左

}

//---------------------------------------------------
//	ベクトルの当たり判定
//---------------------------------------------------
void CollisionVec(D3DXVECTOR3 pos, D3DXVECTOR3 posold, bool *bUse, float *move, D3DXVECTOR3 *rot)
{
	float nVectorData;

	//エリアの広さを持ってきて、それを参考に当たり判定用の方向ベクトルを作る
	for (int nCnt = 0; nCnt < 4; ++nCnt)
	{
		//------------------------------------------------<<vecA
		//成分計算
		g_vecA[nCnt].vec.x = g_vecA[nCnt].end.x - g_vecA[nCnt].start.x;
		g_vecA[nCnt].vec.z = g_vecA[nCnt].end.z - g_vecA[nCnt].start.z;

		//大きさの計算
		g_vecA[nCnt].size = (float)sqrt(g_vecA[nCnt].vec.x * g_vecA[nCnt].vec.x + g_vecA[nCnt].vec.z * g_vecA[nCnt].vec.z);

		//ベクトルの正規化
		g_vecA[nCnt].vec.x = g_vecA[nCnt].vec.x / g_vecA[nCnt].size;
		g_vecA[nCnt].vec.z = g_vecA[nCnt].vec.z / g_vecA[nCnt].size;

		//------------------------------------------------<<vecB

		//始点
		D3DXVECTOR3 start;
		//終点
		D3DXVECTOR3 end;

		start = D3DXVECTOR3(pos.x, pos.y, pos.z);
		end = D3DXVECTOR3(g_vecA[nCnt].vec.x - posold.x, posold.y, g_vecA[nCnt].vec.z - posold.z);

		//成分
		D3DXVECTOR3 vecB;

		//成分計算
		vecB.x = start.x - g_vecA[nCnt].start.x;
		vecB.z = start.z - g_vecA[nCnt].start.z;

		//大きさ計算
		float magnitude = (float)sqrt(vecB.x * vecB.x + vecB.z * vecB.z);

		//ベクトルの正規化
		vecB.x = vecB.x / magnitude;
		vecB.z = vecB.z / magnitude;

		//----------------------------------------------------------<<弾の進行
		//進行ベクトル
		D3DXVECTOR3 progress_vector;

		//成分計算
		progress_vector.x = end.x - start.x;
		progress_vector.z = end.z - start.z;

		//大きさ計算
		float progress_magnitude = (float)sqrt(progress_vector.x * progress_vector.x + progress_vector.z * progress_vector.z);

		//ベクトルの正規化
		progress_vector.x = progress_vector.x / progress_magnitude;
		progress_vector.z = progress_vector.z / progress_magnitude;

		//外積を利用した当たり判定
		nVectorData = (g_vecA[nCnt].vec.z * vecB.x) - (g_vecA[nCnt].vec.x * vecB.z);

		//正なら右側、負なら左側
		if (nVectorData < 0.0f)
		{//当たったら
			if (nCnt == 1 || nCnt == 0)
			{//移動量を反対に
				*move *= -1;
			}

			//角度を反対に
			rot->y *= -1;
		}
	}
}
