//=======================================
//
//   Field.h
//  Author: テュアン
//
//=======================================
#ifndef _FIELD_H_
#define _FIELD_H_	

#include "main.h"
#include "game.h"

typedef enum
{
	Field_TYPE_WALL_RED = 0,
	Field_TYPE_WALL_BLUE,
	Field_TYPE_YUKA_RED,
	Field_TYPE_YUKA_BLUE,
	Field_TYPE_WALL_NAKA,
	Field_TYPE_KANSHA,
	Field_TYPE_MINIROBOT,
	Field_TYPE_ROBOT,
	Field_TYPE_MINION,
	Field_TYPE_BALLOON
}Field_TYPE;
//影の構造体
typedef struct
{
	D3DXVECTOR3 move;
	D3DXVECTOR3 pos;							//位置
	D3DXCOLOR col;								//色
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotDestField;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 vtxMinField;
	D3DXVECTOR3 vtxMaxField;
	D3DXVECTOR3 scaleVectorField;
	Field_TYPE type;
	bool bUse;

}Field;

//プロトタイプ宣言
void InitField(void);
void UninitField(void);
void UpdateField(void);
void DrawField(void);
void SetField(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scaleVectorField, Field_TYPE type);
bool CollisionField(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 size);
Field *GetField(void);

#endif