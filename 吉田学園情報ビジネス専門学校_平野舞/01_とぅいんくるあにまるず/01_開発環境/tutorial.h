//-------------------------------------------
//
// チュートリアル情報[tutorial.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _TUTORIAL_H_		// 二重インクルード防止
#define _TUTORIAL_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include <d3dx9.h>		// 描画処理に必要

//-------------------------------------------
// 前方宣言
//-------------------------------------------
// 背景
class CBg;
// オブジェクト2D
class CObject2D;

//-------------------------------------------
// クラス
//-------------------------------------------
class CTutorial
{
private:
	// コンストラクタ
	CTutorial();
public:
	// デストラクタ
	~CTutorial();

	// インスタンスの生成
	static void CreateInstance();
	// インスタンスの取得
	static CTutorial* GetInstance();

	// 初期化
	HRESULT Init();
	// 終了
	void Uninit();
	// 更新
	void Update();

private:
	// タイトルクラスのポインタ
	static CTutorial* m_Instance;
	// テクスチャ名
	static char* m_cFileName[];

	// 背景のポインタ
	CBg* m_pBg;
	// オブジェクト2Dのポインタ
	CObject2D* m_pObject2D;

	// a値を足すかどうかフラグ
	bool m_bColAdd;
};

#endif		// _TUTORIAL_H_