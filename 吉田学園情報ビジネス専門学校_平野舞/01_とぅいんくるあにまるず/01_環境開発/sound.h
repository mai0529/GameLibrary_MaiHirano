//-------------------------------------------
//
// 音の情報[sound.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _SOUND_H_		// 二重インクルード防止
#define _SOUND_H_

//-------------------------------------------
// インクルード
//-------------------------------------------
#include <Windows.h>		// WindowsAPIに必要
#include "xaudio2.h"		// サウンド処理に必要
//
//-------------------------------------------
// 音クラス
//-------------------------------------------
class CSound
{
public:
	// サウンドファイル
	enum SOUND_LABEL
	{
		SOUND_LABEL_TITLE = 0,			// タイトル
		SOUND_LABEL_TUTORIAL,			// チュートリアル
		SOUND_LABEL_GAME,				// ゲーム
		SOUND_LABEL_RESULT,				// リザルト
		SOUND_LABEL_SE_BULLET,			// 弾
		SOUND_LABEL_SE_PLAYERDAMAGE,	// プレイヤーダメージ
		SOUND_LABEL_SE_SKILL,			// スキル
		SOUND_LABEL_SE_ITEM,			// アイテム
		SOUND_LABEL_SE_ENEMYDAMAGE,		// 敵ダメージ
		SOUND_LABEL_SE_DECISION_CAT,	// 決定_猫
		SOUND_LABEL_SE_DECISION_DOG,	// 決定_犬
		SOUND_LABEL_MAX,
	};

private:
	// パラメータ構造体
	struct PARAM
	{
		// ファイル名
		char* pFileName;
		// ループカウント
		int nCntLoop;
	};

private:
	// コンストラクタ
	CSound();
public:
	// デストラクタ
	~CSound();

	// インスタンスの生成
	static void Create();
	// インスタンスの取得
	static CSound* GetInstace();

	// 初期化
	HRESULT Init(HWND hWnd);
	// 終了
	void Uninit();
	// 再生
	HRESULT Play(SOUND_LABEL label);
	// 停止
	void Stop(SOUND_LABEL label);
	// 停止
	void Stop();

private:
	// サウンドのポインタ
	static CSound* m_Instance;

	// チャンクのチェック
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	// チャンクデータの読み込み
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	// XAudio2オブジェクトへのインターフェイス
	IXAudio2* m_pXAudio2;
	// マスターボイス
	IXAudio2MasteringVoice* m_pMasteringVoice;
	// ソースボイス
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX];
	// オーディオデータ
	BYTE* m_apDataAudio[SOUND_LABEL_MAX];
	// オーディオデータサイズ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];
	// パラメータ
	static PARAM m_aParam[SOUND_LABEL_MAX];
};

#endif