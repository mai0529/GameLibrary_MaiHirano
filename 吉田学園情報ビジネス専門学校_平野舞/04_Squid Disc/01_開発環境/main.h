//===================================================================
//
//3Dアクション(main.h)
//Author:大原隆俊
//
//===================================================================
#ifndef _MAIN_H_						//このマクロ定義がされてなかったら
#define _MAIN_H_						//2重インクルード防止のマクロ定義
#define DIRECTINPUT_VERSION (0x0800)	//ビルド時の警告対策用マクロ

//===================================================================
//インクルードファイル
//===================================================================
#include<windows.h>
#include"d3dx9.h"		//描画処理に必要
#include"dinput.h"
#include"xaudio2.h"		//サウンド処理に必要
#include"xinput.h"

//===================================================================
//ライブラリリンク
//===================================================================
#pragma comment(lib,"d3d9.lib")		//描画処理に必要
#pragma comment(lib,"d3dx9.lib")	//(d3d9.lib)の各様ライブラリ
#pragma comment(lib,"dxguid.lib")	//Directコンポーネント（部品）使用に必要
#pragma comment(lib,"winmm.lib")	//システム、時刻取得に必要
#pragma comment(lib,"dinput8.lib")	//入力処理に必要
#pragma comment(lib,"xinput.lib")

//===================================================================
//マクロ定義
//===================================================================
#define CLASS_NAME		"WindowClass"		//ウィンドウクラス名
#define WINDOW_NAME		"Squid Disc"
#define SCREEN_WIDTH	(1280)				//ウィンドウ幅
#define SCREEN_HEIGHT	(720)				//ウィンドウ高さ
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE |D3DFVF_TEX1)

//===================================================================
//頂点情報[3D]の構造体を定義
//===================================================================
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	D3DXVECTOR3 nor;	//頂点座標
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
} VERTEX_3D;

//頂点情報[2D]の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	float rhw;			//差表変換用係数（1.0固定）
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
} VERTEX_2D;

//===================================================================
//画面（モード）の種類
//===================================================================
typedef enum
{
	MODE_TITLE = 0,	//操作説明画面
	MODE_SCENE,		//導入画面
	MODE_TUTORIAL,	//チュートリアル画面
	MODE_GAME,		//ゲーム画面
	MODE_END,		//終了画面
	MODE_CLEAR,		//クリア画面
	MODE_SETUMEI,	//ゲーム説明
	MODE_SOUSA,		//操作説明
	MODE_MAX
}MODE;

typedef enum
{
	PLAYER_P1 = 0,
	PLAYER_P2
}PLAYER_TYPE;

//===================================================================
//プロトタイプ宣言
//===================================================================
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LPDIRECT3DDEVICE9 GetDevice(void);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void SetMode(MODE mode);
MODE GetMode(void);
void NextMode(MODE mode);

#endif 