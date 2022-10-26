//-------------------------------------------
//
// テクスチャの情報[texture.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _TEXTURE_H_		// 二重インクルード防止
#define _TEXTURE_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include <d3dx9.h>		// 描画処理に必要

//-------------------------------------------
// クラス
//-------------------------------------------
class CRsTexture
{
private:
	// 最大文字数
	static const int MAX_NAME = 128;

public:
	// コンストラクタ
	CRsTexture();
	// デストラクタ
	~CRsTexture();

	// テクスチャの設定
	HRESULT SetTexture();
	// テクスチャ情報の取得
	LPDIRECT3DTEXTURE9 GetTexture();
	//テクスチャ名の読み込み
	void LoadFile(char* cFileName);
	// テクスチャの破棄
	void Uninit();

	// ハッシュ値の設定
	void SetHashCode(unsigned int HashCode);
	// ハッシュ値の取得
	unsigned int GetHashCode();

private:
	// テクスチャポインタ
	LPDIRECT3DTEXTURE9 m_pTexture;
	// テクスチャ名
	char* m_cFileName;
	// ハッシュ値
	unsigned int m_HashCode;
};

#endif // _TEXTURE_H_