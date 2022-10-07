//-------------------------------------------
//
// メニューの情報[menu.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _MENU_H_		// 二重インクルード防止
#define _MENU_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include "object2D.h"	// 2Dオブジェクト

//-------------------------------------------
// クラス
//-------------------------------------------
class CMenu : public CObject2D
{
public:
	// 状態
	enum MENU_STATE
	{
		// 決定されていない
		MENU_STATE_NO_DECISION = 0,
		// 決定された
		MENU_STATE_DECISION,
		// 点滅
		MENU_STATE_BLINK,
		// 種類の最大数
		MENU_STATE_MAX
	};

public:
	// コンストラクタ
	CMenu();
	// デストラクタ
	~CMenu() override;

	// 生成
	static CMenu* Create(const D3DXVECTOR3& pos);

	// 初期化
	HRESULT Init(const D3DXVECTOR3& pos) override;
	// 終了
	void Uninit() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

	// 状態の設定
	void SetState(MENU_STATE state);
	// 状態の取得
	MENU_STATE GetState();

private:
	// 状態
	void State();

	// 決定した
	void Decision();
	// 点滅
	void Blink();

private:
	// アイテムの種類
	MENU_STATE m_state;
	// カウント
	int m_nCount;
};

#endif		// _MENU_H_