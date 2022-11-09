//-------------------------------------------
//
// カウントダウン情報[countDown.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _COUNTDOWN_H_		// 二重インクルード防止
#define _COUNTDOWN_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include "object2D.h"	// 2Dオブジェクト

//-------------------------------------------
// クラス
//-------------------------------------------
class CCountDown : public CObject2D
{
public:
	// コンストラクタ
	CCountDown();
	// デストラクタ
	~CCountDown() override;

	// 生成
	static CCountDown* Create(const D3DXVECTOR3& pos);

	// 初期化
	HRESULT Init() override;
	// 終了
	void Uninit() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

private:
	// フレーム数のカウンター
	int m_nCntFrame;
	// カウントダウン用カウンター
	int m_nCountDown;
};

#endif		// _COUNTDOWN_H_