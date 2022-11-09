//-------------------------------------------
//
// 壁の情報[wall.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _WALL_H_		// 二重インクルード防止
#define _WALL_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include "object2D.h"	// 2Dオブジェクト

//-------------------------------------------
// クラス
//-------------------------------------------
class CWall : public CObject2D
{
private:
	// コンストラクタ
	CWall();

public:
	// デストラクタ
	~CWall() override;

	// インスタンスの生成
	static void CreateInstance();
	// インスタンスの取得
	static CWall* GetInstance();

	// 初期化
	HRESULT Init() override;
	// 終了
	void Uninit() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

private:
	// 壁のポインタ
	static CWall* m_pWall;
};

#endif		// _PLAYER_H_