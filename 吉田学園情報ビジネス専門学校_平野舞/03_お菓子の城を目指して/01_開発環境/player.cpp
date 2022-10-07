//-------------------------------------------
//
//プレイヤー処理[player.cpp]
//Author:平野舞
//
//-------------------------------------------

//インクルードファイル
#include "player.h"
#include "controller.h"

//グローバル宣言
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;				//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;		//頂点バッファへのポインタ
Player g_player;										//プレイヤーの情報
bool g_bPlayerFade;										//フェードしているかどうか						

//-------------------------------------------
//プレイヤーの初期化処理
//-------------------------------------------
void InitPlayer(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/player004.png",
		&g_pTexturePlayer);

	g_player.pos = D3DXVECTOR3(100.0f, 650.0f, 0.0f);		//位置の初期化
	g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//前位置情報の初期化
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//移動量の初期化
	g_player.nCounterAnim = 0;								//カウンターの初期化
	g_player.nPatternAnim = 0;								//パターン番号の初期化
	g_player.nDirectionMove = 0;							//向きの初期化
	g_player.bIsJumping = false;							//ジャンプ中の初期化
	g_player.state = PLAYERSTATE_APPEAR;					//初期表示の初期化
	g_player.nCounterState = 100;							//状態管理カウンターの初期化
	g_player.nLife = 3;										//寿命の初期化
	g_player.bDisp = true;									//表示する
	g_bPlayerFade = false;									//フェードしていない

	//頂点バッファの生成
	pDevice -> CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer-> Lock(0, 0, (void**) &pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - (PLAYER_WIDTH / 2), g_player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + (PLAYER_WIDTH / 2), g_player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - (PLAYER_WIDTH / 2), g_player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + (PLAYER_WIDTH / 2), g_player.pos.y, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2((1.0f / PLAYERTEX_U) , (1.0f / PLAYERTEX_V));
	pVtx[1].tex = D3DXVECTOR2((1.0f / PLAYERTEX_U) , (1.0f / PLAYERTEX_V));
	pVtx[2].tex = D3DXVECTOR2((1.0f / PLAYERTEX_U) , (1.0f / PLAYERTEX_V));
	pVtx[3].tex = D3DXVECTOR2((1.0f / PLAYERTEX_U) , (1.0f / PLAYERTEX_V));

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}

//-------------------------------------------
//プレイヤーの終了処理
//-------------------------------------------
void UninitPlayer(void)
{
	//テクスチャの破棄
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//-------------------------------------------
//プレイヤーの更新処理
//-------------------------------------------
void UpdatePlayer(void)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//プレイヤーの状態
	StatePlayer();

	//前回の位置を更新
	g_player.posOld = g_player.pos;

	//テクスチャ座標の更新
	pVtx[0].tex = D3DXVECTOR2((1.0f / PLAYERTEX_U) * g_player.nPatternAnim, (1.0f / PLAYERTEX_V) * g_player.nDirectionMove);
	pVtx[1].tex = D3DXVECTOR2((1.0f / PLAYERTEX_U) * (g_player.nPatternAnim + 1), (1.0f / PLAYERTEX_V) * g_player.nDirectionMove);
	pVtx[2].tex = D3DXVECTOR2((1.0f / PLAYERTEX_U) * g_player.nPatternAnim, (1.0f / PLAYERTEX_V) * (g_player.nDirectionMove + 1));
	pVtx[3].tex = D3DXVECTOR2((1.0f / PLAYERTEX_U) * (g_player.nPatternAnim + 1), (1.0f / PLAYERTEX_V) *(g_player.nDirectionMove + 1));

	//重力
	g_player.move.y += PLAYER_G;

	//位置を更新
	g_player.pos += g_player.move;

	//移動量を更新(減衰させる)
	g_player.move.x += (0.0f - g_player.move.x) * 0.5f;

	//移動とテクスチャ
	MovePlayer();

	//ブロックとの当たり判定
	g_player.bIsJumping = !CollisionBlock(&g_player.pos, &g_player.posOld, &g_player.move, (PLAYER_WIDTH / 2), PLAYER_HEIGHT);

	//敵との当たり判定
	CollisionEnemy(&g_player.pos, &g_player.posOld, &g_player.move, (PLAYER_WIDTH / 2.0f), (PLAYER_HEIGHT / 1.3f));

	//スクロール処理
	Scroll();

	//ブロックとの当たり判定
	g_player.bIsJumping = !CollisionBlock(&g_player.pos, &g_player.posOld, &g_player.move, (PLAYER_WIDTH / 2), PLAYER_HEIGHT);

	//ジャンプ移動
	Jumping();

	//敵との当たり判定
	CollisionEnemy(&g_player.pos, &g_player.posOld, &g_player.move, (PLAYER_WIDTH / 2.0f), (PLAYER_HEIGHT / 1.3f));

	//アイテムとの当たり判定
	CollisionItem(&g_player.pos, (PLAYER_WIDTH / 3), PLAYER_HEIGHT);

	//城との当たり判定
	CollisionGoal(&g_player.pos, (PLAYER_WIDTH / 3), PLAYER_HEIGHT);

	//画面外処理
	OffScreen();

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - (PLAYER_WIDTH / 2), g_player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + (PLAYER_WIDTH / 2), g_player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - (PLAYER_WIDTH / 2), g_player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + (PLAYER_WIDTH / 2), g_player.pos.y, 0.0f);

	if (g_player.pos.y >= SCREEN_HEIGHT && !g_bPlayerFade)
	{//画面外になったら
	 //モード設定
			PlaySound(SOUND_LABEL_SE_FALL);		//SEの再生
			SetFade(MODE_GAMEOVER);				//ゲームオーバー画面
			g_bPlayerFade = true;				//フェードしている
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}

//-------------------------------------------
//プレイヤーの描画処理
//-------------------------------------------
void DrawPlayer(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0,g_pTexturePlayer);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//-------------------------------------------
//プレイヤーの状態管理処理
//-------------------------------------------
void StatePlayer(void)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_player.state)
	{
	case PLAYERSTATE_APPEAR:		//出現
		g_player.nCounterState--;
		if (0 == g_player.nCounterState % 20)
		{
			//頂点カラー
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		if (10 == g_player.nCounterState % 20)
		{
			//頂点カラー
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		}
		if (g_player.nCounterState <= 0)
		{
			g_player.state = PLAYERSTATE_NORMAL;
			//頂点カラー
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		break;
	case PLAYERSTATE_NORMAL:		//通常
		break;
	case PLAYERSTATE_DAMAGE:		//ダメージを受けたとき
		g_player.nCounterState--;
		//点滅
		if (0 == g_player.nCounterState % 20)
		{
			//頂点カラー
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		}
		if (1 == g_player.nCounterState % 20)
		{
			//頂点カラー
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
		}
		if (g_player.nCounterState <= 0)
		{
			g_player.state = PLAYERSTATE_NORMAL;
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		break;
	case PLAYERSTATE_DEATH:			//死んだとき
		g_player.nCounterState--;
		if (g_player.nCounterState <= 0)
		{
			//モード設定(ゲーム画面に移行)
			SetFade(MODE_GAMECLEAR);
			return;
		}
		break;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}

//-------------------------------------------
//プレイヤーのヒット処理
//-------------------------------------------
void HitPlayer(int nDamage)
{
	Life *pLife = GetMaxLife();

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	if (g_player.bDisp == true)
	{
		PlaySound(SOUND_LABEL_SE_DAMAGE);
		for (int nCount = MAX_LIFE - 1; nCount > 0; nCount--, pLife--)
		{
			if (pLife->bUse == true)
			{
				pLife->bUse = false;
				break;
			}
		}
		g_player.nLife -= nDamage;
		if (g_player.nLife <= 0)
		{//ライフが0になったらa
			//爆発の処理
			//SetExplosion(g_player.pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			g_player.bDisp = false;
			//モード設定(ゲーム画面に移行)
			SetFade(MODE_GAMEOVER);
		}
		else
		{
			g_player.state = PLAYERSTATE_DAMAGE;
			g_player.nCounterState = 100;
			//頂点カラーの変更
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}

//-------------------------------------------
//プレイヤーの取得
//-------------------------------------------
Player * GetPlayer(void)
{
	return &g_player;
}

//-------------------------------------------
//プレイヤーの移動処理
//-------------------------------------------
void MovePlayer(void)
{
	if (GetKeyboardPress(DIK_A) == true || GetControllerPress(0, XINPUT_GAMEPAD_DPAD_LEFT)
		|| GetControllerStickPress(0, STICK_LEFT))
	{//Aキーが押された、右移動
		g_player.nDirectionMove = 1;		//向き
		//g_player.pos.x -= PLAYER_DIS;
		g_player.move.x += sinf(-D3DX_PI / 2.0f) * PLAYER_DIS;
		g_player.move.y += cosf(-D3DX_PI / 2.0f) * PLAYER_DIS;
	}
	else if (GetKeyboardPress(DIK_D) == true || GetControllerPress(0, XINPUT_GAMEPAD_DPAD_RIGHT)
		|| GetControllerStickPress(0, STICK_RIGHT))
	{//Dキーが押された、左移動
		g_player.nDirectionMove = 0;		//向き
		//g_player.pos.x += PLAYER_DIS;
		g_player.move.x += sinf(D3DX_PI / 2.0f) * PLAYER_DIS;
		g_player.move.y += cosf(D3DX_PI / 2.0f) * PLAYER_DIS;
	}
	//弾撃ち
	if (GetKeyboardTrigger(DIK_RETURN) == true || GetControllerPressTrigger(0, XINPUT_GAMEPAD_A))
	{//弾の発射
		if (g_player.nDirectionMove == 0)
		{//Dキー押してるとき
			SetBullet(D3DXVECTOR3(g_player.pos.x, g_player.pos.y - (PLAYER_HEIGHT / 2), 0.0f), D3DXVECTOR3(10.0f, 0.0f, 0.0f), BULLETTYPE_PLAYER);
		}
		else if (g_player.nDirectionMove == 1)
		{//Aキー押してるとき
			SetBullet(D3DXVECTOR3(g_player.pos.x, g_player.pos.y - (PLAYER_HEIGHT / 2), 0.0f), D3DXVECTOR3(-10.0f, 0.0f, 0.0f), BULLETTYPE_PLAYER);
		}
	}
}

//-------------------------------------------
//ジャンプ処理
//-------------------------------------------
void Jumping(void)
{
	//ジャンプ
	if (GetKeyboardTrigger(DIK_SPACE) == true || GetControllerPressTrigger(0, XINPUT_GAMEPAD_B))
	{//SPACEキーが押された
		if (g_player.bIsJumping == false)
		{
			PlaySound(SOUND_LABEL_SE_JUMP);
			g_player.bIsJumping = true;
			g_player.move.y -= PLAYER_JUMP;
			if (g_player.nPatternAnim == 0 || g_player.nPatternAnim == 2)
			{//ジャンプ中のポーズ
				g_player.nPatternAnim += 1;
			}
		}
	}

	if (g_player.bIsJumping != true)
	{//ジャンプしていなかったら
		if (g_player.move.x >= PLAYER_MOVE || g_player.move.x <= -PLAYER_MOVE)
		{//移動していたら
			g_player.nCounterAnim++;

			//カウンターが10になったら
			if (g_player.nCounterAnim % 10 == 0)
			{//パターン数を増やす
				g_player.nPatternAnim++;
			}
			if (g_player.nPatternAnim == 4)
			{//パターン数を戻す
				g_player.nPatternAnim = 0;
			}
		}
		else
		{//移動停止
			if (g_player.nPatternAnim == 1 || g_player.nPatternAnim == 3)
			{//パターン1,3だったら
				g_player.nPatternAnim += 1;

				if (g_player.nPatternAnim == 4)
				{//パターン数を戻す
					g_player.nPatternAnim = 0;
				}
			}
		}
	}
}

//-------------------------------------------
//プレイヤーの画面外処理
//-------------------------------------------
void OffScreen(void)
{
	if (g_player.pos.x + (PLAYER_WIDTH / 2) > SCREEN_WIDTH)
	{//右端
		g_player.pos.x = SCREEN_WIDTH - (PLAYER_WIDTH / 2);

	}
	if (g_player.pos.x - (PLAYER_WIDTH / 2) < 0)
	{//左端
		g_player.pos.x = 0 + (PLAYER_WIDTH / 2);

	}
	if (g_player.pos.y - PLAYER_HEIGHT < 0)
	{//上
		(g_player.pos.y = 0 + PLAYER_HEIGHT);

	}
}

//-------------------------------------------
//スクロール処理
//-------------------------------------------
void Scroll(void)
{
	//画面スクロール
	if (g_player.pos.x + (PLAYER_WIDTH / 2) >= SCREEN_WIDTH / 2)
	{//半分進んだ
		g_player.pos.x = (SCREEN_WIDTH / 2) - (PLAYER_WIDTH / 2);

		if (g_player.move.x > 0.0f)
		{//プレイヤーの移動量が0以上だったら
			//ブロック
			BLOCK *pBlock = GetBlock();
			for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pBlock++)
			{
				pBlock->pos.x -= g_player.move.x;
			}

			//敵
			Enemy *pEnemy = GetEnemy();
			for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
			{
				pEnemy->pos.x -= g_player.move.x;
			}

			//背景
			BG *pBG = GetBG();
			for (int nCntBG = 0; nCntBG < NUM_BG; nCntBG++, pBG++)
			{
				pBG->fTexU += g_player.move.x * 0.0001f;
			}

			//ゴール
			Goal *pGoal = GetGoal();
			pGoal->pos.x -= g_player.move.x;

			//アイテム
			Item *pItem = GetItem();
			for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
			{
				pItem->pos.x -= g_player.move.x;
			}

			Twinkle *pTwinkle = GetTwinkle();
			for (int nCntFlame = 0; nCntFlame < MAX_TWINKLE; nCntFlame++, pTwinkle++)
			{
				pTwinkle->pos.x -= g_player.move.x;
			}
		}
	}
}