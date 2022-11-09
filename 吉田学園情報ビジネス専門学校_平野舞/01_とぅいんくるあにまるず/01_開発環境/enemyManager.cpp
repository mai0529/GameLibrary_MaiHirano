//---------------------------------------------------------------------------------
//
// 敵マネージャーの処理[enemyManager.cpp]
// Author : 平野舞
//
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// インクルードファイル
//---------------------------------------------------------------------------------
#include <stdio.h>				// 外部ファイル読み込み用
#include "enemyManager.h"		// 敵マネージャー
#include "enemyRabbit.h"		// うさぎ型敵
#include "enemyCat.h"			// ねこ型敵
#include "enemyDog.h"			// いぬ型敵
#include "enemyCircle.h"		// 丸のお邪魔敵
#include "enemyStar.h"			// 星のお邪魔敵
#include "enemyDeath.h"			// 死神
#include "enemyBoss.h"			// ボス
#include "time.h"				// タイマー

//---------------------------------------------------------------------------------
// 定数宣言
//---------------------------------------------------------------------------------
// テキストファイル
#define TEXT_ENEMY		("data/TEXT/enemy.txt")

// 1P側と2P側の距離
static const float ENEMY_DIS = 700.0f;
// リセット時間
static const int ENEMY_RESET_TIME = 3;
// 死神の発生タイミング
static const int ENEMY_DEATH_TIME = 10;

//---------------------------------------------------------------------------------
// 静的メンバ変数宣言
//---------------------------------------------------------------------------------
// 敵マネージャーのポインタ
CEnemyManager* CEnemyManager::m_Instance = nullptr;

//---------------------------------------------------------------------------------
//	コンストラクタ
//---------------------------------------------------------------------------------
CEnemyManager::CEnemyManager()
	:m_nCntFileEnemy(0), m_nNowCntEnemy(0),m_bCreate(false)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		// 出現カウンター
		m_aFile[nCntEnemy].nCntApper = 0;
		// 位置
		m_aFile[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// 色
		m_aFile[nCntEnemy].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// 速度
		m_aFile[nCntEnemy].fSpeed = 0.0f;
		// 寿命
		m_aFile[nCntEnemy].nLife = 0;
		// 種類
		m_aFile[nCntEnemy].nType = CEnemy::ENEMY_TYPE_RABBIT;
	}

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{// 敵のポインタ
		m_pEnemy[nCntEnemy] = nullptr;
	}
}

//---------------------------------------------------------------------------------
// デストラクタ
//---------------------------------------------------------------------------------
CEnemyManager::~CEnemyManager()
{

}

//---------------------------------------------------------------------------------
// インスタンスの生成
//---------------------------------------------------------------------------------
void CEnemyManager::CreateInstance()
{
	if (m_Instance == nullptr)
	{// nullptrだったら
		// メモリを生成
		m_Instance = new CEnemyManager;
	}
}

//---------------------------------------------------------------------------------
// インスタンスの取得
//---------------------------------------------------------------------------------
CEnemyManager* CEnemyManager::GetInstance()
{
	if (m_Instance != nullptr)
	{// nullptrではなかったら
		return m_Instance;
	}

	return nullptr;
}

//---------------------------------------------------------------------------------
// 敵の生成
//
// MULTI_TYPE player → 1P側か2P側か
// int nType		 → 敵の種類
// D3DXVECTOR3 pos	 → 発生位置
// float fSpeed		 → 移動速度
// D3DXCOLOR col	 → カラー
// int nLife		 → 寿命
//---------------------------------------------------------------------------------
void CEnemyManager::Create(CObject2D::MULTI_TYPE player,int nType, D3DXVECTOR3 pos, float fSpeed, D3DXCOLOR col,int nLife)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (m_pEnemy[nCntEnemy] == nullptr)
		{// nullptrだったら
			switch (nType)
			{
				// うさぎ( 通常 )
			case CEnemy::ENEMY_TYPE_RABBIT:
			{
				m_pEnemy[nCntEnemy] = CEnemyRabbit::Create(pos);
				// 移動量
				m_pEnemy[nCntEnemy]->SetSpeed(fSpeed);
				// 色
				m_pEnemy[nCntEnemy]->SetColor(col);
			}
				break;
				// ねこ( 通常 )
			case CEnemy::ENEMY_TYPE_CAT:
			{
				m_pEnemy[nCntEnemy] = CEnemyCat::Create(pos);
				// 移動量
				m_pEnemy[nCntEnemy]->SetSpeed(fSpeed);
				// 色
				m_pEnemy[nCntEnemy]->SetColor(col);
			}
			break;
			// いぬ( 通常 )
			case CEnemy::ENEMY_TYPE_DOG:
			{
				m_pEnemy[nCntEnemy] = CEnemyDog::Create(pos);
				// 移動量
				m_pEnemy[nCntEnemy]->SetSpeed(fSpeed);
				// 色
				m_pEnemy[nCntEnemy]->SetColor(col);
			}
			break;
				// 丸( お邪魔 )
			case CEnemy::ENEMY_TYPE_CIRCLE:
			{
				m_pEnemy[nCntEnemy] = CEnemyCircle::Create(pos);
			}
				break;
				// 星( お邪魔 )
			case CEnemy::ENEMY_TYPE_STAR:
			{
				m_pEnemy[nCntEnemy] = CEnemyStar::Create(pos);
			}
			break;
				// 死神( 無限プレイ防止 )
			case CEnemy::ENEMY_TYPE_DEATH:
			{
				m_pEnemy[nCntEnemy] = CEnemyDeath::Create(pos);
			}
				break;
				// ボス
			case CEnemy::ENEMY_TYPE_BOSS:
			{
				m_pEnemy[nCntEnemy] = CEnemyBoss::Create(pos);
			}
			break;
			default:
				break;
			}

			// 格納先番号
			m_pEnemy[nCntEnemy]->SetID(nCntEnemy);
			// 1Pか2Pか
			m_pEnemy[nCntEnemy]->SetPlayerType(player);
			// 寿命
			m_pEnemy[nCntEnemy]->SetLife(nLife);

			break;
		}
	}
}

//---------------------------------------------------------------------------------
// 初期化
//---------------------------------------------------------------------------------
HRESULT CEnemyManager::Init()
{
	// 外部ファイルの読み込み
	Load();

	return S_OK;
}

//---------------------------------------------------------------------------------
// 終了
//---------------------------------------------------------------------------------
void CEnemyManager::Uninit()
{
	// 自身の削除
	Release();

	// nullptrにする
	m_Instance = nullptr;
}

//---------------------------------------------------------------------------------
// 更新
//---------------------------------------------------------------------------------
void CEnemyManager::Update()
{
	if (m_nNowCntEnemy <= m_nCntFileEnemy && CTime::GetInstance()->GetTime() == m_aFile[m_nNowCntEnemy].nCntApper)
	{
		// 1P側
		CEnemyManager::Create(CObject2D::MULTI_TYPE_ONE, m_aFile[m_nNowCntEnemy].nType,m_aFile[m_nNowCntEnemy].pos,
			m_aFile[m_nNowCntEnemy].fSpeed, m_aFile[m_nNowCntEnemy].col, m_aFile[m_nNowCntEnemy].nLife);

		// 2P側
		CEnemyManager::Create(CObject2D::MULTI_TYPE_SECOND, m_aFile[m_nNowCntEnemy].nType, D3DXVECTOR3(m_aFile[m_nNowCntEnemy].pos.x + ENEMY_DIS, m_aFile[m_nNowCntEnemy].pos.y,0.0f),
			m_aFile[m_nNowCntEnemy].fSpeed,m_aFile[m_nNowCntEnemy].col, m_aFile[m_nNowCntEnemy].nLife);

		// カウントを増やす
		m_nNowCntEnemy++;
	}
	else if (m_nNowCntEnemy == m_nCntFileEnemy && CTime::GetInstance()->GetTime() == m_aFile[m_nNowCntEnemy - 1].nCntApper + ENEMY_RESET_TIME)
	{
		// タイマのリセット
 		CTime::GetInstance()->ResetTime();
		// 今の敵カウントの初期化
		m_nNowCntEnemy = 0;
	}

	if (CTime::GetInstance()->GetTime() > 1 && CTime::GetInstance()->GetTime() % ENEMY_DEATH_TIME == 0 && !m_bCreate)
	{
		// 死神の生成
		CEnemyManager::Create(CObject2D::MULTI_TYPE_ONE, CEnemy::ENEMY_TYPE_DEATH, D3DXVECTOR3(300.0f, 0.0f, 0.0f), 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1);
		CEnemyManager::Create(CObject2D::MULTI_TYPE_SECOND, CEnemy::ENEMY_TYPE_DEATH, D3DXVECTOR3(1000.0f,0.0f,0.0f), 0.0f, D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),1);
		m_bCreate = true;
	}
	if (CTime::GetInstance()->GetTime() % ENEMY_DEATH_TIME == 1 && m_bCreate)
	{
		m_bCreate = false;
	}
}

//---------------------------------------------------------------------------------
// 描画
//---------------------------------------------------------------------------------
void CEnemyManager::Draw()
{

}

//---------------------------------------------------------------------------------
// 敵の削除
//---------------------------------------------------------------------------------
void CEnemyManager::DeleteEnemy(int nCntEnemy)
{
	int nID = nCntEnemy;

	if (m_pEnemy[nID] != nullptr)
	{// nullptrではなかったら

		// 終了
		m_pEnemy[nID]->Uninit();

		// nullptrにする
		m_pEnemy[nID] = nullptr;
	}
}

//---------------------------------------------------------------------------------
// 外部ファイルの読み込み
//---------------------------------------------------------------------------------
void CEnemyManager::Load()
{
	char cData[125];

	// ファイルを開く
	FILE* pFile = fopen(TEXT_ENEMY, "r");

	if (pFile == nullptr)
	{// ファイルが開けなかったら
		printf("ファイルが開けませんでした。");
		return;
	}

	while (1)
	{
		// 文字を読み込む
		fscanf(pFile, "%s", &cData[0]);

		if (strcmp(&cData[0], "ENEMYSET") == 0)
		{// ENEMYSETの文字があったら
			do
			{
				// 文字を読み込む
				fscanf(pFile, "%s", &cData[0]);

				if (strcmp(&cData[0], "DETAILSET") == 0)
				{
					do
					{
						// 文字を読み込む
						fscanf(pFile, "%s", &cData[0]);

						if (strcmp(&cData[0], "COUNTER") == 0)
						{// 出現カウンター
							fscanf(pFile, "%s", &cData[0]);
							fscanf(pFile, "%d", &m_aFile[m_nCntFileEnemy].nCntApper);
						}
						else if (strcmp(&cData[0], "POS") == 0)
						{// 位置
							fscanf(pFile, "%s", &cData[0]);
							fscanf(pFile, "%f", &m_aFile[m_nCntFileEnemy].pos.x);
							fscanf(pFile, "%f", &m_aFile[m_nCntFileEnemy].pos.y);
							fscanf(pFile, "%f", &m_aFile[m_nCntFileEnemy].pos.z);
						}
						else if (strcmp(&cData[0], "COL") == 0)
						{// 色
							fscanf(pFile, "%s", &cData[0]);
							fscanf(pFile, "%f", &m_aFile[m_nCntFileEnemy].col.r);
							fscanf(pFile, "%f", &m_aFile[m_nCntFileEnemy].col.g);
							fscanf(pFile, "%f", &m_aFile[m_nCntFileEnemy].col.b);
							fscanf(pFile, "%f", &m_aFile[m_nCntFileEnemy].col.a);
						}
						else if (strcmp(&cData[0], "SPEED") == 0)
						{// 速度
							fscanf(pFile, "%s", &cData[0]);
							fscanf(pFile, "%f", &m_aFile[m_nCntFileEnemy].fSpeed);
						}
						else if (strcmp(&cData[0], "LIFE") == 0)
						{// ライフ
						 // 文字を読み込む
							fscanf(pFile, "%s", &cData[0]);
							fscanf(pFile, "%d", &m_aFile[m_nCntFileEnemy].nLife);
						}
						else if (strcmp(&cData[0], "TYPE") == 0)
						{// 種類
							fscanf(pFile, "%s", &cData[0]);
							fscanf(pFile, "%d", &m_aFile[m_nCntFileEnemy].nType);
						}
					} while (strcmp(&cData[0], "END_DETAILSET") != 0);

					// カウントする
					m_nCntFileEnemy++;
				}
			} while (strcmp(&cData[0], "END_ENEMYSET") != 0);
		}

		if (strcmp(&cData[0], "END_SCRIPT") == 0)
		{// END_ENEMYSETの文字があったら
			break;
		}
	}
}