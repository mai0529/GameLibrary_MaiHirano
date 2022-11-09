//-------------------------------------------
//
// 結果表示情報[witchResults.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _WITCHRESULTS_H_		// 二重インクルード防止
#define _WITCHRESULTS_H_

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
class CWitchResult
{
private:
	// テクスチャの最大数
	static const int MAX_TEX = 4;

private:
	// コンストラクタ
	CWitchResult();
public:
	// デストラクタ
	~CWitchResult();

	// インスタンスの生成
	static void CreateInstance();
	// インスタンスの取得
	static CWitchResult* GetInstance();

	// どっちが勝者か
	void SetWinner();

	// 初期化
	HRESULT Init(const D3DXVECTOR3& pos);
	// 終了
	void Uninit();
	// 更新
	void Update();
	// 描画
	void Draw();


private:
	// タイトルクラスのポインタ
	static CWitchResult* m_Instance;

	// オブジェクト2Dのポインタ
	CObject2D* m_paObject2D[MAX_TEX];
	// 勝者
	int m_nWinner;
};

#endif		// _RESULT_H_