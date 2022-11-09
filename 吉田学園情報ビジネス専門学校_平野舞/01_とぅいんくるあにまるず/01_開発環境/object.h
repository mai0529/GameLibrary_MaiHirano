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

//-------------------------------------------
// クラス
//-------------------------------------------
class CObject
{
public:
	// 親
	enum EOBJECT_PARENT
	{
		// なし
		EOBJECT_PARENT_NONE = 0,
		// タイトル
		EOBJECT_PARENT_TITLE,
		// チュートリアル
		EOBJECT_PARENT_TUTORIAL,
		// ゲーム
		EOBJECT_PARENT_GAME,
		// ポーズ
		EOBJECT_PARENT_PAUSE,
		// リザルト
		EOBJECT_PARENT_RESULT,
		// 最大数
		EOBJECT_PARENT_MAX
	};

	// オブジェクト種類
	enum EOBJECT_TYPE
	{
		// 何もなし
		OBJECT_TYPE_NONE = 0,
		// プレイヤー
		EOBJECT_TYPE_PLAYER,
		// ライフ
		EOBJECT_TYPE_LIFE,
		// スキル
		EOBJECT_TYPE_SKILL,
		// 敵
		EOBJECT_TYPE_ENEMY,
		// 弾
		EOBJECT_TYPE_BULLET,
		// アイテム
		EOBJECT_TYPE_ITEM,
		// 壁
		EOBJECT_TYPE_WALL,
		// エフェクト
		EOBJECT_TYPE_EFFECT,
		// パーティクル
		EOBJECT_TYPE_PARTICLE,
		// メニュー
		EOBJECT_TYPE_MENU,
		//種類の最大数
		EOBJECT_TYPE_MAX
	};

	// 優先順位
	enum EOBJECT_PRIORITY
	{
		// 指定なし
		OBJECT_PRIORITY_NONE = 4,
		// フェード
		OBJECT_PRIORITY_FADE,
		// 最大数
		OBJECT_PRIORITY_MAX
	};

public:
	// オブジェクトの最大数
	static const int MAX_OBJECT = 300;
	// 優先順位の最大数
	static const int NUM_PRIORITY = 6;

public:
	// コンストラクタ
	explicit CObject(int nPriority = 3);
	// デストラクタ
	virtual ~CObject();

	// 初期化
	virtual HRESULT Init() = 0;
	// 終了
	virtual void Uninit() = 0;
	// 更新
	virtual void Update() = 0;
	// 描画
	virtual void Draw() = 0;

	// すべてのメモリの開放
	static void ReleaseAll();
	// すべてを更新
	static void UpdateAll();
	// すべてを描画
	static void DrawAll();

	// 親の削除
	static void ReleaseParent(EOBJECT_PARENT parent);

	// 進行しているかどうかの設定
	static void SetPause(bool bPause);
	// 進行しているかどうかの情報を取得
	static bool GetPause();

	// 優先順位の設定
	void SetPriority(int nPriority);
	// 優先順位の取得
	int GetPriority();

	// オブジェクトの種類を設定
	void SetObjectType(EOBJECT_TYPE objectType);
	// オブジェクトの種類を取得
	EOBJECT_TYPE GetObjectType() const;

	// 親を設定
	void SetObjectParent(EOBJECT_PARENT parent);
	// 親を取得
	EOBJECT_PARENT GetObjectParent();

	// オブジェクトのポインタを取得
	static CObject* GetObject(int nCntObject, int nPriority = 3);

protected:
	//オブジェクトの削除
	void Release();

private:
	// ポインタクラス
	static CObject* m_apObject[NUM_PRIORITY][MAX_OBJECT];
	// 個数
	static int m_nNumAll;
	// 進行しているかどうか
	static bool m_bPause;

	// 格納先の番号
	int m_nID;
	// 優先順位
	int m_nPriority;
	// オブジェクトの種類
	EOBJECT_TYPE m_ObjectType;
	// 親
	EOBJECT_PARENT m_parent;
};

#endif		// _OBJECT_H_