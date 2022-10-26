//-----------------------------------------------------------------------------------------------
//
// オブジェクト処理[object.cpp]
// Author : 平野舞
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// インクルードファイル
//-----------------------------------------------------------------------------------------------
#include "object.h"		// オブジェクト

//-----------------------------------------------------------------------------------------------
// 静的メンバ変数宣言
//-----------------------------------------------------------------------------------------------
// オブジェクトのポインタ
CObject* CObject::m_apObject[NUM_PRIORITY][MAX_OBJECT] = { nullptr };
// 個数
int CObject::m_nNumAll = 0;
// 進行しているかどうか
bool CObject::m_bPause = false;

//-----------------------------------------------------------------------------------------------
// コンストラクタ
//
// int nPriority → 描画優先順位
//-----------------------------------------------------------------------------------------------
CObject::CObject(int nPriority  /* = 3 */)
	:m_ObjectType(OBJECT_TYPE_NONE), m_parent(EOBJECT_PARENT_NONE)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nPriority][nCntObject] == nullptr)
		{// nullptrだったら
			// ポインタを格納
			m_apObject[nPriority][nCntObject] = this;

			// 格納先の番号
			m_nID = nCntObject;

			// 優先順位を設定
			CObject::SetPriority(nPriority);

			// 個数を増やす
			m_nNumAll++;

			break;
		}
	}
}

//-----------------------------------------------------------------------------------------------
//　デストラクタ
//-----------------------------------------------------------------------------------------------
CObject::~CObject()
{

}

//-----------------------------------------------------------------------------------------------
//　すべてのメモリを解放
//-----------------------------------------------------------------------------------------------
void CObject::ReleaseAll()
{
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != nullptr && nCntPriority != OBJECT_PRIORITY_FADE)
			{// nullptrではなかったら
				// 終了
				m_apObject[nCntPriority][nCntObject]->Uninit();

				// メモリの開放
				delete m_apObject[nCntPriority][nCntObject];

				// nullptrにする
				m_apObject[nCntPriority][nCntObject] = nullptr;
			}
		}
	}
}

//-----------------------------------------------------------------------------------------------
//　すべてを更新
//-----------------------------------------------------------------------------------------------
void CObject::UpdateAll()
{
	if (!CObject::GetPause())
	{// ポーズしていない状態
		for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
		{
			for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
			{
				if (m_apObject[nCntPriority][nCntObject] != nullptr)
				{// nullptrではなかったら,進行していたら
				 // 更新
					m_apObject[nCntPriority][nCntObject]->Update();
				}
			}
		}
	}
	else if (CObject::GetPause())
	{// ポーズ中だったら
		for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
		{
			for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
			{
				if (m_apObject[nCntPriority][nCntObject] != nullptr && m_apObject[nCntPriority][nCntObject]->GetObjectParent() == EOBJECT_PARENT_PAUSE)
				{// nullptrではなかったら,進行していたら
				 // 更新
					m_apObject[nCntPriority][nCntObject]->Update();
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------------------------
//　すべてを描画
//-----------------------------------------------------------------------------------------------
void CObject::DrawAll()
{
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != nullptr)
			{// nullptrではなかったら
			 // 描画
				m_apObject[nCntPriority][nCntObject]->Draw();
			}
		}
	}
}

//-----------------------------------------------------------------------------------------------
// 親の削除
//
// OBJECT_PARENT parent → 親指定
//-----------------------------------------------------------------------------------------------
void CObject::ReleaseParent(EOBJECT_PARENT parent)
{
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != nullptr)
			{// 親が一致、nullptrではなかったら
				if (m_apObject[nCntPriority][nCntObject]->GetObjectParent() == parent)
				{// 親が一致していたら
					// 終了
					m_apObject[nCntPriority][nCntObject]->Uninit();

					// メモリの開放
					//delete m_apObject[nCntPriority][nCntObject];

					// nullptrにする
					m_apObject[nCntPriority][nCntObject] = nullptr;
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------------------------
// 進行しているかどうかの設定
//
// bool bPause → true:ポーズ中/ false:ポーズしていない
//-----------------------------------------------------------------------------------------------
void CObject::SetPause(bool bPause)
{
	m_bPause = bPause;
}

//-----------------------------------------------------------------------------------------------
// 進行しているかどうかの情報を取得
//-----------------------------------------------------------------------------------------------
bool CObject::GetPause()
{
	return m_bPause;
}

//-----------------------------------------------------------------------------------------------
// 優先順位の設定
//
// int nPriority → 描画優先順位を指定
//-----------------------------------------------------------------------------------------------
void CObject::SetPriority(int nPriority)
{
	m_nPriority = nPriority;
}

//-----------------------------------------------------------------------------------------------
// 優先順位の取得
//-----------------------------------------------------------------------------------------------
int CObject::GetPriority()
{
	return m_nPriority;
}

//-----------------------------------------------------------------------------------------------
// オブジェクトの種類を設定
//
// OBJECT_TYPE objectType → オブジェクトの種類を指定 
//-----------------------------------------------------------------------------------------------
void CObject::SetObjectType(EOBJECT_TYPE objectType)
{
	m_ObjectType = objectType;
}

//-----------------------------------------------------------------------------------------------
// オブジェクトの種類を取得
//-----------------------------------------------------------------------------------------------
CObject::EOBJECT_TYPE CObject::GetObjectType() const
{
	return m_ObjectType;
}

//-----------------------------------------------------------------------------------------------
// 親を設定
//
// OBJECT_PARENT parent → オブジェクトの親を指定
//-----------------------------------------------------------------------------------------------
void CObject::SetObjectParent(EOBJECT_PARENT parent)
{
	m_parent = parent;
}

//-----------------------------------------------------------------------------------------------
// 親を取得
//-----------------------------------------------------------------------------------------------
CObject::EOBJECT_PARENT CObject::GetObjectParent()
{
	return m_parent;
}

//-----------------------------------------------------------------------------------------------
// オブジェクトのポインタを取得
//
// int nCntObject → 何番目か指定
// int nPriority →　描画優先順位を指定
//-----------------------------------------------------------------------------------------------
CObject* CObject::GetObject(int nCntObject, int nPriority /* = 3 */)
{
	return m_apObject[nPriority][nCntObject];
}

//-----------------------------------------------------------------------------------------------
//　オブジェクトの破棄
//-----------------------------------------------------------------------------------------------
void CObject::Release()
{
	if (m_apObject[m_nPriority][m_nID] != nullptr)
	{// nullptrではなかったら
		// 変数を格納
		int nID = m_nID;

		// 優先度を格納
		int nPriority = m_nPriority;

		// メモリの開放
		delete m_apObject[nPriority][nID];

		// nullptrに戻す
		m_apObject[nPriority][nID] = nullptr;

		// 最大個数を減らす
		m_nNumAll--;
	}
}