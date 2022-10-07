//-------------------------------------------
//
// 背景の情報[bg.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _BG_H_		// 二重インクルード防止
#define _BG_H_

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
class CBg : public CObject
{
private:
	// 画像の最大数
	static const int MAX_TEXTURE = 2;
public:
	// 選択肢
	enum TUTORIAL_PAGE
	{
		// 何もなし
		TUTORIAL_PAGE_NONE = 0,
		// 1ページ目
		TUTORIAL_PAGE_ONE,
		// 2ページ目
		TUTORIAL_PAGE_SECOND,
		// 最大数
		TUTORIAL_PAGE_MAX
	};

public:
	// コンストラクタ
	CBg();
	// デストラクタ
	virtual ~CBg();

	// 生成
	static CBg* Create();

	// 初期化
	HRESULT Init(const D3DXVECTOR3& pos) override;
	// 終了
	void Uninit() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;
	
	// ページの設定
	void SetPage(TUTORIAL_PAGE page);

private:
	// 状態
	void State();

private:
	// オブジェクト2Dのポインタ
	CObject2D* m_paObject2D[MAX_TEXTURE];

	// テクスチャのV座標(縦)
	float m_fTexV;
	// チュートリアルのページ
	TUTORIAL_PAGE m_page;
};

#endif		// _BG_H_