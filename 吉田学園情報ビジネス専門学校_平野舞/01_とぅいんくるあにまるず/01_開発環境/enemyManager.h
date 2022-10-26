//-------------------------------------------
//
// 敵マネージャーの情報[enemyManager.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _ENEMYMANAGER_H_		// 二重インクルード防止
#define _ENEMYMANAGER_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include <d3dx9.h>		// 描画処理に必要

//-------------------------------------------
// インクルード
//-------------------------------------------
#include "enemy.h"		// 敵
#include "common.h"		// 共通の列挙型

//-------------------------------------------
// クラス
//-------------------------------------------
class CEnemyManager
{
private:
	// 敵の最大数
	static const int MAX_ENEMY = 100;

private:
	// 外部ファイル読み込みの構造体
	struct File
	{
		// 出現カウンター
		int nCntApper;
		// 位置
		D3DXVECTOR3 pos;
		// 色
		D3DXCOLOR col;
		// 移動スピード
		float fSpeed;
		// 寿命
		int nLife;
		// 種類
		int nType;
	};

private:
	// コンストラクタ
	CEnemyManager();

public:
	// デストラクタ
	~CEnemyManager();

	// インスタンスの生成
	static void CreateInstance();
	// インスタンスの取得
	static CEnemyManager* GetInstance();

	// 敵の生成
	void Create(MULTI_TYPE player,int nType,D3DXVECTOR3 pos, float fSpeed,D3DXCOLOR col,int nLife);

	// 初期化
	void Init();
	// 終了
	void Uninit();
	// 更新
	void Update();

	// 敵の削除
	void DeleteEnemy(int nCntEnemy);

private:
	// 外部ファイル読み込み
	void Load();

private:
	// 外部ファイル構造体の情報
	File m_aFile[MAX_ENEMY];
	// テキストファイル用敵のカウント
	int m_nCntFileEnemy;
	// 今の敵のカウント
	int m_nNowCntEnemy;

	// 敵マネージャーのポインタ
	static CEnemyManager* m_Instance;
	// 敵クラスのポインタ
	CEnemy* m_pEnemy[MAX_ENEMY];
	// 生成したかどうか
	bool m_bCreate;
};

#endif // _ENEMYMANAGER_H_