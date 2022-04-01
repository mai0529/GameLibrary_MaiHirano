#ifndef _MAIN_H_
#define _MAIN_H_

#include <windows.h>
#include <stdio.h>
#include "d3dx9.h"	
#define DIRECTINPUT_VERSION	(0x800)		//ビルド時の警告対処用
#include "dinput.h"						//入力処理に必要
#include "xaudio2.h"					//サウンド処理に必要

//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")

//マクロ定義
#define SCREEN_WIDTH		(1280)
#define SCREEN_HEIGHT		(720)
#define FVF_VERTEX_2D		(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define CLASS_NAME			"WindowClass"			//ウインドウクラスの名前
#define WINDOW_NAME			"アクションゲーム"		//ウインドウの名前

//頂点情報2Dの構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;		//頂点座標
	float rhw;				//座標変換用係数(1.0fで固定)
	D3DCOLOR col;			//頂点カラー
	D3DXVECTOR2 tex;		//テクスチャ座標
} VERTEX_2D;

//画面(モード)の種類
typedef enum
{
	MODE_TITLE = 0,		//タイトル画面
	MODE_TUTORIAL,		//チュートリアル画面
	MODE_GAME,			//ゲーム画面
	MODE_GAMECLEAR,		//リザルト画面
	MODE_GAMEOVER,		//ゲームオーバー画面
	MODE_RESULT,		//リザルト画面
	MODE_RANKING,		//ランキング画面
	MODE_MAX
}MODE;

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstence, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);

#endif