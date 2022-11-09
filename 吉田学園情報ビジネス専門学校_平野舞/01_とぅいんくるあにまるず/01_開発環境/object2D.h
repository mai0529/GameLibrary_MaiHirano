//-------------------------------------------
//
// 2Dポリゴン[object2D.h]
// Author : 平野舞
//
//-------------------------------------------

#ifndef _OBJECT2D_H_		// 二重インクルード防止
#define _OBJECT2D_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include "object.h"		// オブジェクト

//-------------------------------------------
// クラス
//-------------------------------------------
class CObject2D: public CObject
{
public:
	// 頂点フォーマット
	const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	// 頂点データ
	struct VERTEX_2D
	{
		D3DXVECTOR3 pos;		// 頂点座標
		float rhw;				// 座標変換用係数
		D3DCOLOR col;			// 頂点カラー
		D3DXVECTOR2 tex;		// テクスチャ座標
	};

	// 1Pか2Pか
	enum MULTI_TYPE
	{
	 // 何もなし
		MULTI_TYPE_NONE = -1,
		// 1P
		MULTI_TYPE_ONE,
		// 2P
		MULTI_TYPE_SECOND,
		// プレイヤー数の最大数
		COMMAND_TYPE_MAX
	};

public:
	// コンストラクタ
	explicit CObject2D(int nPriority = 3);
	// デストラクタ
	~CObject2D() override;

	// 生成
	static CObject2D* Create(char* cFileName,const D3DXVECTOR3& pos, const D3DXVECTOR3& size, int nPriority = 3);

	// 初期化
	HRESULT Init() override;
	// 終了
	void Uninit() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

	// 位置の設定
	void SetPosition(const D3DXVECTOR3& pos);
	// 位置の取得
	const D3DXVECTOR3& GetPosition() const;

	// ポリゴンサイズの設定
	void SetSize(D3DXVECTOR3 size);
	// ポリゴンサイズの取得
	const D3DXVECTOR3& GetSize() const;

	// 頂点カラーの設定
	void SetColor(D3DXCOLOR col);
	// 頂点カラーの取得
	D3DXCOLOR GetColor();

	// 1Pか2Pかを設定
	void SetPlayerType(MULTI_TYPE playerType);
	// 1Pか2Pかを取得
	MULTI_TYPE GetPlayerType();

	// テクスチャアニメーション座標の設定
	void SetTexAnim(int nDivisionU, int nDivisionV, int nNowPatternU, int nNowPatternV);

	// アニメーション座標の設定
	void SetTexPos(float fTexU, float fTexV);

	// 位置の更新
	void UpdatePos();

	// テクスチャの設定
	void LoadTexture(char* cFileName);

private:
	// 頂点バッファのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;
	// 位置
	D3DXVECTOR3 m_pos;
	// サイズ
	D3DXVECTOR3 m_size;
	// カラー
	D3DXCOLOR m_col;

	// テクスチャ名
	char* m_cFileName;
	// 1Pか2Pかどうか
	MULTI_TYPE m_PlayerType;
};

#endif		// _OBJECT2D_H_