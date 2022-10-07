//-------------------------------------------
//
// シーン情報[scene.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _SCENE_H_		// 二重インクルード防止
#define _SCENE_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include <d3dx9.h>		// 描画処理に必要

//-------------------------------------------
// クラス
//-------------------------------------------
class CScene
{
private:
	// コンストラクタ
	CScene();
public:
	// デストラクタ
	~CScene();

	// インスタンスの生成
	static void CreateInstance();
	// インスタンスの取得
	static CScene* GetInstance();

	//// 初期化
	//virtual HRESULT Init();
	//// 終了
	//virtual void Uninit();
	//// 更新
	//virtual void Update();

private:
	// タイトルクラスのポインタ
	static CScene* m_Instance;
};

#endif		// _SCENE_H_