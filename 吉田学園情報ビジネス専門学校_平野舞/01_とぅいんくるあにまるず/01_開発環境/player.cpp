//-----------------------------------------------------------------------------------------------
//
// プレイヤーの処理[player.cpp]
// Author : 平野舞
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// インクルードファイル
//-----------------------------------------------------------------------------------------------
#include "player.h"				// プレイヤー
#include "application.h"		// アプリケーション
#include "game.h"				// ゲーム
#include "renderer.h"			// レンダリング
#include "VirtualController.h"	// 仮想コントローラー
#include "bullet.h"				// 弾
#include "enemy.h"				// 敵
#include "life.h"				// ライフ
#include "particle.h"			// パーティクル
#include "wall.h"				// 壁
#include "item.h"				// アイテム
#include "itemManager.h"		// アイテムマネージャー
#include "skill.h"				// スキル
#include "fade.h"				// フェード
#include "sound.h"				// 音
#include "TextureFileName.h"	// 画像のファイル名

//-----------------------------------------------------------------------------------------------
// 定数宣言
//-----------------------------------------------------------------------------------------------
// 幅
static const float PLAYER_WIDTH = 60.0f;
// 高さ
static const float PLAYER_HEIGHT = 80.0f;
// 移動距離
static const float PLAYER_DIS = 0.8f;
// 慣性(減衰)
static const float PLAYER_INTERTIA = 0.08f;
// 寿命の最大数
static const int PLAYER_MAX_LIFE = 3;
// 点滅カウンター
static const int PLAYER_BLINK = 60;
// 点滅の割合
static const int PLAYER_RATIO = 20;
// 死亡カウンター
static const int PLAYER_DEATH_COUNT = 60;

//-----------------------------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------------------------
CPlayer::CPlayer()
	: m_pSkill(nullptr), m_posOld(0.0f,0.0f,0.0f),m_move(0.0f,0.0f,0.0f), m_nLife(0), m_state(PLAYER_STATE_NONE), m_nCntBlink(0), m_nCntDeath(0)
{

}

//-----------------------------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------------------------
CPlayer::~CPlayer()
{

}

//-----------------------------------------------------------------------------------------------
// 生成
//
//const D3DXVECTOR3& pos → 生成する座標位置
//-----------------------------------------------------------------------------------------------
CPlayer* CPlayer::Create(MULTI_TYPE player,const D3DXVECTOR3& pos)
{
	// ポインタクラスを宣言
	CPlayer* pPlayer = new CPlayer;

	if (pPlayer != nullptr)
	{// もしnullptrではなかったら
		 // 1Pか2Pか
		pPlayer->SetPlayerType(player);
		// 位置
		pPlayer->SetPosition(pos);
		// 初期化
		pPlayer->Init();
	}

	return pPlayer;
}

//-----------------------------------------------------------------------------------------------
// 初期化
//
// const D3DXVECTOR3& pos → 最初に表示する座標位置
//-----------------------------------------------------------------------------------------------
HRESULT CPlayer::Init()
{
	// 寿命
	m_nLife = PLAYER_MAX_LIFE;
	// 点滅カウンター
	m_nCntBlink = PLAYER_BLINK;
	// 状態
	m_state = PLAYER_STATE_NORMAL;

	//オブジェクトタイプを設定
	SetObjectType(EOBJECT_TYPE::EOBJECT_TYPE_PLAYER);

	// テクスチャの設定
	switch (CObject2D::GetPlayerType())
	{
		// 1P
	case MULTI_TYPE_ONE:
		CObject2D::LoadTexture(TEX_PLAYER_ONE);
		break;
		// 2P
	case MULTI_TYPE_SECOND:
		CObject2D::LoadTexture(TEX_PLAYER_SECOND);
		break;
	default:
		break;
	}
	
	// サイズ
	CObject2D::SetSize(D3DXVECTOR3(PLAYER_WIDTH, PLAYER_HEIGHT, 0.0f));

	CObject2D::Init();

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// 終了
//-----------------------------------------------------------------------------------------------
void CPlayer::Uninit()
{
	CObject2D::Uninit();
}

//-----------------------------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------------------------
void CPlayer::Update()
{
	// 状態
	State();

	if (m_nLife <= 0)
	{// 寿命が0以下なら
		return;
	}
	
	// 位置の取得
	D3DXVECTOR3 pos = CObject2D::GetPosition();

	// 前フレームの情報を保存
	m_posOld = pos;

	Shoot(CObject2D::GetPlayerType(), pos);
	Skill(CObject2D::GetPlayerType());
	Move(CObject2D::GetPlayerType());

	// 移動量の更新
	pos += m_move;

	// 移動量を更新(減衰させる)
	m_move.x += (0.0f - m_move.x) * PLAYER_INTERTIA;
	m_move.y += (0.0f - m_move.y) * PLAYER_INTERTIA;

	// 当たり判定
	if (m_state == PLAYER_STATE_NORMAL)
	{// 通常状態だったら
		CollisionEnemy(pos);
	}

	// アイテムの当たり判定
	CollisionItem(pos);

	// 壁の当たり判定
	pos = CollisionWall(pos);

	// 画面外当たり判定
	pos = OffScreen(pos);

	// 位置の更新
	CObject2D::SetPosition(pos);
	CObject2D::UpdatePos();
}

//-----------------------------------------------------------------------------------------------
// 描画
//-----------------------------------------------------------------------------------------------
void CPlayer::Draw()
{
	CObject2D::Draw();
}

//-----------------------------------------------------------------------------------------------
// 寿命の取得
//-----------------------------------------------------------------------------------------------
int CPlayer::GetLife()
{
	return m_nLife;
}

//-----------------------------------------------------------------------------------------------
// 状態
//-----------------------------------------------------------------------------------------------
void CPlayer::State()
{
	switch (m_state)
	{
		// 通常状態
	case PLAYER_STATE_NORMAL:
		break;
		// 無敵状態
	case PLAYER_STATE_INVINCIBLE:
		// 色を変更
		CObject2D::SetColor(D3DXCOLOR(0.7f, 1.0f, 0.0f, 1.0f));
		break;
		// ダメージ状態
	case PLAYER_STATE_DAMAGE:
		// 点滅する
		Blink();
		// カウントを減らす
		m_nCntBlink--;
		break;
		// 死亡状態
	case PLAYER_STATE_DEATH:
		// 親を設定
		CObject::SetObjectParent(CObject::EOBJECT_PARENT_PAUSE);

		// 動きを止める
		CObject::SetPause(true);

		// カウントを加算
		m_nCntDeath++;

		// プレイヤーの色を変える
		CObject2D::SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

		if (m_nCntDeath > PLAYER_DEATH_COUNT && CFade::GetInstance()->GetFade() == CFade::FADE_NONE)
		{// カウントが一定の値になってフェードしていなかったら
			// リザルト画面に移行
			CFade::GetInstance()->SetFade(CApplication::MODE_RESULT);
		}
		break;
	default:
		break;
	}
}

//-----------------------------------------------------------------------------------------------
// ヒット
//-----------------------------------------------------------------------------------------------
void CPlayer::Hit(int nDamage)
{
	// 寿命を減らす
	m_nLife -= nDamage;

	if (m_nLife > 0)
	{// ライフが0以上だったら
	 // ダメージ状態にする
		m_state = PLAYER_STATE_DAMAGE;

		// ライフのポインタ
		CLife* pLife = nullptr;

		//ライフ情報を取得
		pLife = CGame::GetLife(CObject2D::GetPlayerType());

		for (int nCntLife = PLAYER_MAX_LIFE - 1; nCntLife > m_nLife - 1; nCntLife--)
		{// ライフを減らす
			pLife->Delete(nCntLife);
		}
	}
	else if (m_nLife <= 0)
	{// ライフが0以下になったら
		// 死亡状態にする
		m_state = PLAYER_STATE_DEATH;
	}
}

//-----------------------------------------------------------------------------------------------
// 点滅
//-----------------------------------------------------------------------------------------------
void CPlayer::Blink()
{
	if (m_nCntBlink % PLAYER_RATIO == 0)
	{
		CObject2D::SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}

	if (m_nCntBlink % PLAYER_RATIO == 10)
	{
			CObject2D::SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}

	if (m_nCntBlink == 0)
	{// カウントが0になったら
		//色を元に戻す
		CObject2D::SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		// 通常状態に戻す
		m_state = PLAYER_STATE_NORMAL;

		// カウントを戻す
		m_nCntBlink = PLAYER_BLINK;
	}
}

//-----------------------------------------------------------------------------------------------
// 弾の発射
//
// int nPlayer			  → 1Pか2Pか
// const D3DXVECTOR3& pos → 弾が出る位置
//-----------------------------------------------------------------------------------------------
void CPlayer::Shoot(int nPlayer,const D3DXVECTOR3& pos)
{
	if (CVController::GetInstance()->GetTrigger(nPlayer,CVController::VIRTUAL_KEY_B))
	{// 弾が出る
		CBullet::Create(CObject2D::GetPlayerType(),pos);
		// 音の再生
		CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_BULLET);
	}
}

//-----------------------------------------------------------------------------------------------
// スキル発動
//
// int nPlayer → 1Pか2Pか
//-----------------------------------------------------------------------------------------------
void CPlayer::Skill(int nPlayer)
{
	if (CVController::GetInstance()->GetTrigger(nPlayer, CVController::VIRTUAL_KEY_A))
	{// スキル
		m_pSkill = CGame::GetSkill(nPlayer);
		m_pSkill->Skill(CObject2D::GetPlayerType());

		// 音の再生
		CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_SKILL);
	}
}

//-----------------------------------------------------------------------------------------------
// 移動
//
// int nPlayer → 何Pか
//-----------------------------------------------------------------------------------------------
void CPlayer::Move(int nPlayer)
{
	// コントローラースティック情報を取得
	D3DXVECTOR3 Stick = CVController::GetInstance()->GetStickDir(nPlayer);

	if (CVController::GetInstance()->GetPress(nPlayer, CVController::VIRTUAL_KEY_RIGHT)
		|| CVController::GetInstance()->GetStickPress(nPlayer, CVController::VIRTUAL_STICK_RIGHT))
	{
		if (CVController::GetInstance()->GetPress(nPlayer,CVController::VIRTUAL_KEY_UP))
		{// 右上
			m_move.x += sinf(D3DX_PI / 4.0f * 3.0f) * PLAYER_DIS;
			m_move.y += cosf(D3DX_PI / 4.0f * 3.0f) * PLAYER_DIS;
		}
		else if (CVController::GetInstance()->GetPress(nPlayer,CVController::VIRTUAL_KEY_DOWN))
		{// 右下
			m_move.x += sinf(D3DX_PI / 4.0f) * PLAYER_DIS;
			m_move.y += cosf(D3DX_PI / 4.0f) * PLAYER_DIS;
		}
		else if (CVController::GetInstance()->GetStickPress(nPlayer, CVController::VIRTUAL_STICK_UP) ||
			CVController::GetInstance()->GetStickPress(nPlayer, CVController::VIRTUAL_STICK_DOWN))
		{// コントローラーの斜め
			m_move.x += Stick.x * PLAYER_DIS;
			m_move.y -= Stick.y * PLAYER_DIS;
		}
		else
		{// 右
			m_move.x += sinf(D3DX_PI / 2.0f) * PLAYER_DIS;
			m_move.y += cosf(D3DX_PI / 2.0f) * PLAYER_DIS;
		}
	}
	else if (CVController::GetInstance()->GetPress(nPlayer,CVController::VIRTUAL_KEY_LEFT)
		|| CVController::GetInstance()->GetStickPress(nPlayer,CVController::VIRTUAL_STICK_LEFT))
	{
		if (CVController::GetInstance()->GetPress(nPlayer,CVController::VIRTUAL_KEY_UP))
		{// 左上
			m_move.x += sinf(-D3DX_PI / 4.0f * 3.0f) * PLAYER_DIS;
			m_move.y += cosf(-D3DX_PI / 4.0f * 3.0f) * PLAYER_DIS;
		}
		else if (CVController::GetInstance()->GetPress(nPlayer,CVController::VIRTUAL_KEY_DOWN))
		{// 左下
			m_move.x += sinf(-D3DX_PI / 4.0f) * PLAYER_DIS;
			m_move.y += cosf(-D3DX_PI / 4.0f) * PLAYER_DIS;
		}
		else if (CVController::GetInstance()->GetStickPress(nPlayer,CVController::VIRTUAL_STICK_UP) ||
		CVController::GetInstance()->GetStickPress(nPlayer,CVController::VIRTUAL_STICK_DOWN))
		{// コントローラーの斜め
			m_move.x += Stick.x * PLAYER_DIS;
			m_move.y -= Stick.y * PLAYER_DIS;
		}
		else
		{// 左
			m_move.x += sinf(-D3DX_PI / 2.0f) * PLAYER_DIS;
			m_move.y += cosf(-D3DX_PI / 2.0f) * PLAYER_DIS;
		}
	}
	else if (CVController::GetInstance()->GetPress(nPlayer,CVController::VIRTUAL_KEY_UP)
		|| CVController::GetInstance()->GetStickPress(nPlayer,CVController::VIRTUAL_KEY_UP))
	{// 上
		m_move.x += sinf(D3DX_PI) * PLAYER_DIS;
		m_move.y += cosf(D3DX_PI) * PLAYER_DIS;
	}
	else if (CVController::GetInstance()->GetPress(nPlayer,CVController::VIRTUAL_KEY_DOWN)
		|| CVController::GetInstance()->GetStickPress(nPlayer,CVController::VIRTUAL_STICK_DOWN))
	{// 下
		m_move.x += sinf(0.0f) * PLAYER_DIS;
		m_move.y += cosf(0.0f) * PLAYER_DIS;
	}
}

//-----------------------------------------------------------------------------------------------
// 敵との当たり判定
//
// const D3DXVECTOR3& pos → 当たり判定の位置( プレイヤーの位置 )
//-----------------------------------------------------------------------------------------------
void CPlayer::CollisionEnemy(const D3DXVECTOR3& pos)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		// オブジェクトのポインタ
		CObject* pObject = nullptr;

		// オブジェクトを取得
		pObject = CObject::GetObject(nCntObject);

		if (pObject == nullptr)
		{// nulltprだったら
			continue;
		}
		else if (pObject->GetObjectType() != EOBJECT_TYPE_ENEMY)
		{// 種類が敵以外だったら
			continue;
		}

		// ダウンキャスト
		CEnemy* pEnemy = (CEnemy*)pObject;

		// 位置を取得する
		D3DXVECTOR3 EnemyPos = pEnemy->GetPosition();
		D3DXVECTOR3 EnemySize = pEnemy->GetSize();

		if ((EnemyPos.x + EnemySize.x / 2.0f >= pos.x - (PLAYER_WIDTH / 2.0f)
			&& EnemyPos.x - EnemySize.x / 2.0f <= pos.x + (PLAYER_WIDTH / 2.0f)
			&& EnemyPos.y + EnemySize.y / 2.0f >= pos.y - (PLAYER_HEIGHT / 2.0f)
			&& EnemyPos.y - EnemySize.y / 2.0f <= pos.y + (PLAYER_HEIGHT / 2.0f)))
		{// 当たり判定
			if (pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE_DEATH && pEnemy->GetPlayerType() == GetPlayerType())
			{// 死神だったら
				Hit(m_nLife);
				// 音の再生
				CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_PLAYERDAMAGE);
			}
			else if ((pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE_CIRCLE || pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE_STAR)
				&& pEnemy->GetPlayerType() != GetPlayerType())
			{// お邪魔だったら
				Hit(1);
				// 音の再生
				CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_PLAYERDAMAGE);
			}
			else if (pEnemy->GetEnemyType() != CEnemy::ENEMY_TYPE_DEATH && pEnemy->GetEnemyType() != CEnemy::ENEMY_TYPE_CIRCLE
				&& pEnemy->GetEnemyType() != CEnemy::ENEMY_TYPE_STAR)
			{// 他の敵
				Hit(1);
				// 音の再生
				CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_PLAYERDAMAGE);
			}
			break;
		}
	}
}

//-----------------------------------------------------------------------------------------------
// アイテムとの当たり判定
//
// const D3DXVECTOR3& pos → 当たり判定の位置( プレイヤーの位置 )
//-----------------------------------------------------------------------------------------------
void CPlayer::CollisionItem(const D3DXVECTOR3& pos)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		// オブジェクトのポインタ
		CObject* pObject = nullptr;

		// オブジェクトを取得
		pObject = CObject::GetObject(nCntObject);

		if (pObject == nullptr)
		{// nulltprだったら
			continue;
		}
		else if (pObject->GetObjectType() != EOBJECT_TYPE_ITEM)
		{// 種類がアイテム以外だったら
			continue;
		}

		// ダウンキャスト
		CItem* pItem = (CItem*)pObject;

		// 位置を取得する
		D3DXVECTOR3 ItemPos = pItem->GetPosition();
		D3DXVECTOR3 ItemSize = pItem->GetSize();

		if ((ItemPos.x + ItemSize.x / 2.0f >= pos.x - (PLAYER_WIDTH / 2.0f)
			&& ItemPos.x - ItemSize.x / 2.0f <= pos.x + (PLAYER_WIDTH / 2.0f)
			&& ItemPos.y + ItemSize.y / 2.0f >= pos.y - (PLAYER_HEIGHT / 2.0f)
			&& ItemPos.y - ItemSize.y / 2.0f <= pos.y + (PLAYER_HEIGHT / 2.0f)))
		{// 当たり判定
			// アイテムの処理
			CItemManager::GetInstance()->Item(pItem->GetID(), CObject2D::GetPlayerType(), pItem->GetItemType());

			// アイテムを終了する
			CItemManager::GetInstance()->ItemDelete(pItem->GetID());

			// 音の再生
			CSound::GetInstace()->Play(CSound::SOUND_LABEL_SE_ITEM);
		}
	}
}

//-----------------------------------------------------------------------------------------------
// 壁との当たり判定
//
// const D3DXVECTOR3& pos → 当たり判定の位置( プレイヤーの位置 )
//-----------------------------------------------------------------------------------------------
D3DXVECTOR3 CPlayer::CollisionWall(D3DXVECTOR3 pos)
{
	// 位置
	D3DXVECTOR3 posPlayer = pos;

	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		// オブジェクトのポインタ情報を取得
		CObject* pObject = CObject::GetObject(nCntObject);

		if (pObject == nullptr)
		{// nulltprだったら
			continue;
		}
		else if (pObject->GetObjectType() != EOBJECT_TYPE_WALL)
		{// 種類が壁以外だったら
			continue;
		}

		// ダウンキャスト
		CWall* pWall = (CWall*)pObject;

		// 位置を取得する
		D3DXVECTOR3 WallPos = pWall->GetPosition();
		D3DXVECTOR3 WallSize = pWall->GetSize();

		if (m_posOld.x - (PLAYER_WIDTH / 2.0f) >= WallPos.x + (WallSize.x / 2.0f)
			&& pos.x - (PLAYER_WIDTH / 2.0f) <= WallPos.x + (WallSize.x / 2.0f))
		{// 左
			posPlayer.x = WallPos.x + (WallSize.x / 2.0f) + (PLAYER_WIDTH / 2.0f);
		}
		else if (m_posOld.x + (PLAYER_WIDTH / 2.0f) <= WallPos.x - (WallSize.x / 2.0f)
			&& pos.x + (PLAYER_WIDTH / 2.0f) >= WallPos.x - (WallSize.x / 2.0f))
		{// 右
			posPlayer.x = WallPos.x - (WallSize.x / 2.0f) - (PLAYER_WIDTH / 2.0f);
		}
	}
	return posPlayer;
}

//-----------------------------------------------------------------------------------------------
// 画面外判定
//
// D3DXVECTOR3. pos → 当たり判定の位置( プレイヤーの位置 )
//-----------------------------------------------------------------------------------------------
D3DXVECTOR3 CPlayer::OffScreen(D3DXVECTOR3 pos)
{
	if (pos.y - (PLAYER_HEIGHT / 2.0f) < 0)
	{// 上
		pos.y = PLAYER_HEIGHT / 2.0f;
	}
	else if (pos.y + (PLAYER_HEIGHT / 2.0f) > CRenderer::SCREEN_HEIGHT)
	{// 下
		pos.y = CRenderer::SCREEN_HEIGHT - (PLAYER_HEIGHT / 2.0f);
	}

	if (pos.x - (PLAYER_WIDTH / 2.0f) < 0)
	{// 左
		pos.x = PLAYER_WIDTH / 2.0f;
	}
	else if (pos.x + (PLAYER_WIDTH / 2.0f) > CRenderer::SCREEN_WIDTH)
	{// 右
		pos.x = CRenderer::SCREEN_WIDTH - (PLAYER_WIDTH / 2.0f);
	}

	return pos;
}