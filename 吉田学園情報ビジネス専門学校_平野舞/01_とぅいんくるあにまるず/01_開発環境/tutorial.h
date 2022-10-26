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

	// オブジェクト2Dのポインタ
	static CBg* m_pBg;

	CObject2D* m_pObject2D;
};

#endif		// _TUTORIAL_H_