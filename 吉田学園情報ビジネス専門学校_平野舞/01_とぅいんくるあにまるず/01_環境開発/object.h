//-------------------------------------------
//
// オブジェクトの情報[object.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _OBJECT_H_		// 二重インクルード防止
#define _OBJECT_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include <d3dx9.h>		// 描画処理に必要
#include "common.h"		// 共通

//-------------------------------------------
// クラス
//-------------------------------------------
class CObject
{
public:
	// 親
	enum OBJECT_PARENT
	{
		// なし
		OBJECT_PARENT_NONE = 0,
		// タイトル
		OBJECT_PARENT_TITLE,
		// チュートリアル
		OBJECT_PARENT_TUTORIAL,
		// ゲーム
		OBJECT_PARENT_GAME,
		// リザルト
		OBJECT_PARENT_RESULT,
		// 最大数
		OBJECT_PARENT_MAX
	};

public:
	// オブジェクトの最大数
	static const int MAX_OBJECT = 300;

public:
	// コンストラクタ
	CObject();
	// デストラクタ
	virtual ~CObject();

	// 初期化
	virtual HRESULT Init(const D3DXVECTOR3& pos) = 0;
	// 終了
	virtual void Uninit() = 0;
	// 更新
	virtual void Update() = 0;
	// 描画
	virtual void Draw() = 0;

	// すべてのメモリの開放
	static void ReleseAll();
	// すべてを更新
	static void UpdateAll();
	// すべてを描画
	static void DrawAll();

	// 親の削除
	static void ReleseParent(OBJECT_PARENT parent);

	// オブジェクトの種類を設定
	void SetObjectType(OBJECT_TYPE objectType);
	// オブジェクトの種類を取得
	OBJECT_TYPE GetObjectType() const;

	// 親を設定
	void SetObjectParent(OBJECT_PARENT parent);
	// 親を取得
	OBJECT_PARENT GetObjectParent();

	// オブジェクトのポインタを取得
	static CObject* GetObject(int nCntObject);

protected:
	//オブジェクトの削除
	void Relese();

private:
	// ポインタクラス
	static CObject* m_apObject[MAX_OBJECT];
	// 個数
	static int m_nNumAll;

	// 格納先の番号
	int m_nID;
	// 優先順位
	int m_nPriority;
	// オブジェクトの種類
	OBJECT_TYPE m_ObjectType;
	// 親
	OBJECT_PARENT m_parent;
};

#endif		// _OBJECT_H_