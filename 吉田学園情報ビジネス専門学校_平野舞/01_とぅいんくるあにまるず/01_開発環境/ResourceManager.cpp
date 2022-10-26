//---------------------------------------------------------------------------------
//
// リソースマネージャーの処理[ResourceManager.cpp]
// Author : 平野舞
//
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// インクルードファイル
//---------------------------------------------------------------------------------
#include "application.h"		// アプリケーション
#include "renderer.h"			// レンダリング
#include "ResourceManager.h"	// リソースマネージャー
#include "texture.h"			// テクスチャ

//---------------------------------------------------------------------------------
// 静的メンバ変数宣言
//---------------------------------------------------------------------------------
// リソースマネージャー
CResourceManager* CResourceManager::m_Instance = nullptr;

//---------------------------------------------------------------------------------
//	コンストラクタ
//---------------------------------------------------------------------------------
CResourceManager::CResourceManager()
{
	for (int nCntTexture = 0; nCntTexture < MAX_TEXTURE; nCntTexture++)
	{
		m_pTexture[nCntTexture] = nullptr;
	}
}

//---------------------------------------------------------------------------------
//	デストラクタ
//---------------------------------------------------------------------------------
CResourceManager::~CResourceManager()
{

}

//---------------------------------------------------------------------------------
// インスタンスの生成
//---------------------------------------------------------------------------------
void CResourceManager::CreateInstance()
{
	if (m_Instance == nullptr)
	{// nullptrだったら
		m_Instance = new CResourceManager;
	}
}

//---------------------------------------------------------------------------------
// インスタンスの取得
//---------------------------------------------------------------------------------
CResourceManager* CResourceManager::GetInstance()
{
	return m_Instance;
}

//---------------------------------------------------------------------------------
// テクスチャの読み込み
//---------------------------------------------------------------------------------
void CResourceManager::LoadTexture(char* cFileName)
{
	for (int nCntTexture = 0; nCntTexture < MAX_TEXTURE; nCntTexture++)
	{
		if (m_pTexture[nCntTexture] == nullptr)
		{// nullptrだったら
			// メモリを生成
			m_pTexture[nCntTexture] = new CRsTexture;
			// ファイル名の読み込み
			m_pTexture[nCntTexture]->LoadFile(cFileName);
			// テクスチャの読み込み
			m_pTexture[nCntTexture]->SetTexture();
			// ハッシュ値の設定
			m_pTexture[nCntTexture]->SetHashCode(GetHashCode(cFileName));

			break;
		}
	}
}

//---------------------------------------------------------------------------------
// テクスチャの読み込み( 複数 )
//---------------------------------------------------------------------------------
void CResourceManager::LoadTexture(char* cFileName[])
{
	for (int nCntTexture = 0; cFileName[nCntTexture] != nullptr; nCntTexture++)
	{
		LoadTexture(cFileName[nCntTexture]);
	}
}

//---------------------------------------------------------------------------------
// テクスチャの破棄
//---------------------------------------------------------------------------------
void CResourceManager::UnloadTexture(char* cFileName)
{
	for (int nCntTexture = 0; nCntTexture < MAX_TEXTURE; nCntTexture++)
	{
		if (m_pTexture[nCntTexture] != nullptr)
		{
			// ハッシュ値を比べる
			if (m_pTexture[nCntTexture]->GetHashCode() == GetHashCode(cFileName))
			{
				// 終了
				m_pTexture[nCntTexture]->Uninit();

				// メモリを破棄する
				delete m_pTexture[nCntTexture];

				// nullptrに戻す
				m_pTexture[nCntTexture] = nullptr;

				break;
			}
		}
	}
}

//---------------------------------------------------------------------------------
// テクスチャの破棄( 複数 )
//---------------------------------------------------------------------------------
void CResourceManager::UnloadTexture(char* cFileName[])
{
	for (int nCntTexture = 0; cFileName[nCntTexture] != nullptr; nCntTexture++)
	{
		UnloadTexture(cFileName[nCntTexture]);
	}
}

//---------------------------------------------------------------------------------
// 全てのテクスチャの破棄
//---------------------------------------------------------------------------------
void CResourceManager::AllUnloadTexture()
{
	for (int nCntTexture = 0; nCntTexture < MAX_TEXTURE; nCntTexture++)
	{
		if (m_pTexture[nCntTexture] != nullptr)
		{
			// 終了
			m_pTexture[nCntTexture]->Uninit();

			// メモリを破棄する
			delete m_pTexture[nCntTexture];

			// nullptrに戻す
			m_pTexture[nCntTexture] = nullptr;
		}
	}

	if (m_Instance != nullptr)
	{// nullptrではなかったら
		// メモリを破棄
		delete m_Instance;

		// nullptrにする
		m_Instance = nullptr;
	}
}

//---------------------------------------------------------------------------------
// テクスチャの取得
//---------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CResourceManager::GetTexture(char* cFileName)
{
	for (int nCntTexture = 0; nCntTexture < MAX_TEXTURE; nCntTexture++)
	{
		if (m_pTexture[nCntTexture] != nullptr)
		{
			// ハッシュ値を比べる
			if (m_pTexture[nCntTexture]->GetHashCode() == GetHashCode(cFileName))
			{
				return m_pTexture[nCntTexture]->GetTexture();
			}
		}
	}

	return nullptr;
}

//---------------------------------------------------------------------------------
// ハッシュ値の生成
//---------------------------------------------------------------------------------
uint32_t CResourceManager::GetHashCode(char* cFileName)
{
	if (cFileName == nullptr)
	{
		return -1;
	}

	uint32_t crc = 0xffffffff;

	size_t length = strlen(cFileName);
	for (size_t nCount = 0; nCount < length; nCount++)
	{
		crc = CRC32TAB[(crc ^ cFileName[nCount]) & 0Xff] ^ (crc >> 8);
	}

	return crc ^ 0xffffffff;
}