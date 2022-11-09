//-------------------------------------------
//
// ライフの情報[life.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _LIFE_H_		// 二重インクルード防止
#define _LIFE_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include "object.h"		// オブジェクト

//-------------------------------------------
// 前方宣言
//-------------------------------------------
// オブジェクト2D
class CObject2D;

//-------------------------------------------
// クラス
//-------------------------------------------
class CLife : public CObject
{
private:
	// ライフの最大数
	static const int MAX_LIFE = 3;

public:
	// コンストラクタ
	CLife();
	// デストラクタ
	~CLife() override;

	// 生成
	static CLife* Create(const D3DXVECTOR3& pos);

	// 初期化
	HRESULT Init();
	// 終了
	void Uninit() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

	// 削除する
	void Delete(int nCntLife);

	// 位置の設定
	void SetPosition(const D3DXVECTOR3& pos);
	// 位置の取得
	const D3DXVECTOR3& GetPosition();

private:
	// オブジェクト2Dのポインタ
	CObject2D* m_paObject2D[MAX_LIFE];

	// 位置
	D3DXVECTOR3 m_pos;
};

#endif		// _LIFE_H_