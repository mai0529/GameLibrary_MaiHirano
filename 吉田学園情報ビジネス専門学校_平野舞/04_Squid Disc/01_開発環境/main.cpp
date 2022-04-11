//===================================================================
//
//3Dアクション(main.cpp)
//Author:大原隆俊
//
//===================================================================
//===================================================================
//インクルードファイル
//===================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "camera.h"
#include "meshfield.h"
#include "shadow.h"
#include "wall.h"
#include "light.h"
#include"fade.h"
#include"sound.h"
#include"TITLE.h"
#include"result.h"
#include"game.h"
#include"SETUMEI.h"
#include"vec.h"
#include"controller.h"
#include"Sousa.h"
//===================================================================
//グローバル変数
//===================================================================
LPDIRECT3D9		g_pD3D = NULL;					//Direct3Dオブジェクトへのポインター
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;		//Device3Dデバイスへのポインタ
MODE g_mode = MODE_TITLE;						//現存のモード
MODE g_NextMode = MODE_MAX;						//次のモード

//===================================================================
//メイン関数
//===================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lCmdLine, int nCmdShow)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };		//画面サイズの構造体

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),				//WNDCLASSEXのメモリサイズ
		CS_CLASSDC,						//ウィンドウのスタイル
		WindowProc,						//ウィンドウプロシージャ
		0,
		0,
		hInstance,						//インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),//タスクバーアイコン
		LoadCursor(NULL,IDC_ARROW),		//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),		//クライアント領域の背景色
		NULL,							//メニューバー
		CLASS_NAME,						//ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION)	//ファイルアイコン

	};
	HWND hWnd;		//ウィンドウハンドル
	MSG msg;		//メッセージを格納する変数

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウ生成
	hWnd = CreateWindowEx(
		0,							//拡張ウィンドウスタイル
		CLASS_NAME,					//ウィンドウクラスの名前
		WINDOW_NAME,				//ウィンドウの名前
		WS_OVERLAPPEDWINDOW,		//ウィンドウスタイル
		CW_USEDEFAULT,				//ウィンドウの左上x座標
		CW_USEDEFAULT,				//ウィンドウの左上y座標
		(rect.right - rect.left),	//ウィンドウの幅
		(rect.bottom - rect.top),	//ウィンドウの高さ		
		NULL,						//親ウィンドウのハンドル
		NULL,						//メニューハンドルor子ウィンドウID
		hInstance,					//インスタンスハンドル
		NULL);						//ウィンドウ生成データ

	//初期化処理(ダメだった時の処理)
	if (FAILED(Init(hInstance, hWnd, FALSE)))
	{//初期化失敗
		return -1;
	}

	//ウィンドウ表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windowsの処理
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージを受け取ったらメッセージループを抜ける
				break;
			}

			else
			{
				//メッセージの設定
				TranslateMessage(&msg);		//仮想キーメッセージを文字メッセージへ変換
				DispatchMessage(&msg);		//ウィンドウプロシージャーへメッセージを送出
			}
		}

		else
		{//DirectXの処理
			//更新処理
			Update();
			//描画処理
			Draw();
		}
	}

	//終了処理
	Uninit();

	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//===================================================================
//ウィンドウプロシージャー
//===================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		//WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:	//キー降下のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE:		//escキーが押された

			DestroyWindow(hWnd);//ウィンドウを破棄する([WM_DESTROY]メッセージを送る)

			break;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//===================================================================
//初期化処理
//===================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;			//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;	//プレゼンテーションパラメータ

	//Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));		//パラメータゼロクリア
	d3dpp.BackBufferWidth = SCREEN_WIDTH;	//ゲーム画面幅
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;	//ゲーム画面
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//Direct3Dデバイスの生成（描画処理と頂点処理をハードウェアで行う）
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))

	{
		//Direct3Dデバイスの生成（描画処理はハードウェア、頂点処理はCPUで行う）
		if (FAILED((g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice))))

		{
			//Direct3Dデバイスの生成（描画処理と頂点処理をCPUで行う）
			if (FAILED((g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice))))

			{
				return E_FAIL;
			}
		}
	}

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//テクスチャステージステートパラメータの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);


	//キーボード初期化処理
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//ジョイパッドの初期化
	InitJoypad();

	//コントローラーの初期化
	InitController();

	//サウンドの初期化処理
	InitSound(hWnd);

	//モードの設定
	SetMode(g_mode);

	//モードの設定
	lnitFade(g_mode);

	SetVec(300.0f, 600.0f);

	//各種オブジェクトの初期化処理
	return S_OK;
}

//===================================================================
//終了処理
//===================================================================
void Uninit(void)
{
	//各種オブジェクトの終了処理

	//キーボード終了処理
	UninitKeyboard();

	//ジョイパッドの終了処理
	UninitJoypad();

	//Direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3Dオブジェクトの破棄
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	
}

//===================================================================
//更新処理
//===================================================================
void Update(void)
{
	//キーボード更新処理
	UpdateKeyboard();

	//Joypadの更新処理
	UpdateJoypad();

	//コントローラーの更新処理
	UpdateController();

	switch (g_mode)
	{
	case MODE_TITLE:	//操作説明画面
		UpdateTITLE();
		break;

	//case MODE_SCENE:	//導入画面
	//	UpdateScene();
	//	break;

	//case MODE_TUTORIAL:	//チュートリアル画面
	//	UpdateTutorial();
	//	break;

	case MODE_GAME:		//ゲーム画面
		UpdateGAME();
		break;

	case MODE_END:		//終了画面
		UpdateResult();
		break;

	case MODE_SETUMEI:	//ゲーム説明画面
		UpdateSetumei();
		break;

	case MODE_SOUSA:	//操作説明画面
		UpdateSousa();
		break;
	}

	//ワイヤーフレームモードの設定
	if (GetKeyboardPress(DIK_F1) == true)
	{
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}

	if (GetKeyboardPress(DIK_F2) == true)
	{//元に戻す
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}

	//フェードの更新処理
	UpdateFade();
}

//===================================================================
//描画処理
//===================================================================
void Draw(void)
{
	Camera*pCamera = GetCamera();
	//画面クリア（バッファクリア、Zバッファのクリア）
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//描画開始が成功
		switch (g_mode)
		{
		case MODE_TITLE:	//操作説明画面
			DrawTITLE();
			break;

		//case MODE_SCENE:	//導入画面
		//	DrawScene();
		//	break;

		//case MODE_TUTORIAL:	//チュートリアル画面
		//	DrawTutorial();
		//	break;

		case MODE_GAME:		//ゲーム画面
							//カメラの設定処理
			SetCamera(0);

			//g_pD3DDevice->SetViewport(&pCamera->viewport);
			////画面クリア(バックバッファ＆Zバッファのクリア)
			//g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

			DrawGAME();


			////カメラの設定処理
			//SetCamera(1
			//);


			//g_pD3DDevice->SetViewport(&(pCamera + 1)->viewport);
			////画面クリア(バックバッファ＆Zバッファのクリア)
			//g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
			//DrawGAME();
			break;

		case MODE_END:		//終了画面
			DrawResult();
			break;

		case MODE_SETUMEI:	//ゲーム説明画面
			DrawSetumei();
			break;

		case MODE_SOUSA:	//操作説明画面
			DrawSousa();
			break;
		}

		//フェードの描画処理
		DrawFade();

		//描画終了
		g_pD3DDevice->EndScene();
	}
	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//===================================================================
//デバイスの取得
//===================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//===================================================================
//モードの設定
//===================================================================
void SetMode(MODE mode)
{
	//現在の画面の終了処理
	switch (g_mode)
	{
	case MODE_TITLE:	//操作説明画面
		UninitTITLE();
		break;

	//case MODE_SCENE:	//導入画面
	//	UninitScene();
	//	break;

	//case MODE_TUTORIAL:	//チュートリアル画面
	//	UninitTutorial();
	//	break;

	case MODE_GAME:		//ゲーム画面
		UninitGAME();
		break;

	case MODE_END:		//終了画面
		UninitResult();
		break;

	case MODE_SETUMEI:	//ゲーム説明画面
		UninitSetumei();
		break;

	case MODE_SOUSA:	//操作説明画面
		UninitSousa();
		break;

	}

	//新しい画面の初期化処理
	switch (mode)
	{
	case MODE_TITLE:
		lnitTITLE();
		break;

	//case MODE_SCENE:	//導入画面
	//	InitScene();
	//	break;

	//case MODE_TUTORIAL:	//チュートリアル画面
	//	InitTutorial ();
	//	break;

	case MODE_GAME:		//ゲーム画面
		lnitGAME();
		break;

	case MODE_END:		//終了画面
		lnitResult();
		break;

	case MODE_SETUMEI:	//ゲーム説明画面
		lnitSetumei();
		break;

	case MODE_SOUSA:	//操作説明画面
		lnitSousa();
		break;
	}

	g_mode = mode;		//現在の画面を切り替える
}

//===================================================================
//Modeの予約
//===================================================================
void NextMode(MODE mode)
{
	g_NextMode = mode;	//次のモードを予約する
}

//===================================================================
//モードの取得
//===================================================================
MODE GetMode(void)
{
	return g_mode;
}