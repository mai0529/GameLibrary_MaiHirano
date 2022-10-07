//-------------------------------------------
//
// レンダリング[renderer.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _RENDERER_H_		// 二重インクルード防止
#define _RENDERER_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include <d3dx9.h>		// 描画処理に必要

//-------------------------------------------
// クラス
//-------------------------------------------
class CRenderer
{
public:		// 定数
	// スクリーンの幅
	static const int SCREEN_WIDTH;
	// スクリーンの高さ
	static const int SCREEN_HEIGHT;

public:		// 関数
	// コンストラクタ
	CRenderer();
	// デストラクタ
	~CRenderer();

	// 初期化
	HRESULT Init(HWND hWnd, BOOL bWindow);
	// 終了
	void Uninit();
	// 更新
	void Update();
	// 描画
	void Draw();
	// Deviceの取得
	LPDIRECT3DDEVICE9 GetDevice();

private:	// 関数
#ifdef _DEBUG
	// FPS表示
	void DrawFPS();
#endif // _DEBUG

private:	// 変数
	// Direct3Dオブジェクト
	LPDIRECT3D9 m_pD3D;
	// Deviceオブジェクト
	LPDIRECT3DDEVICE9 m_pD3DDevice;

#ifdef _DEBUG
	// フォント
	LPD3DXFONT m_pFont;
#endif // _DEBUG
};

#endif		// _RENDERER_H_