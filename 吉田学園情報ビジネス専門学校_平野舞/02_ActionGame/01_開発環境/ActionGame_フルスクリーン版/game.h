#ifndef _GAME_H_
#define _GAME_H_

//インクルードファイル
#include "main.h"
#include "fade.h"
#include "bg.h"
#include "player.h"
#include "block.h"
#include "Bullet.h"
#include "enemy.h"
#include "input.h"
#include "score.h"
#include "sound.h"
#include "item.h"
#include "flame.h"
#include "time.h"
#include "goal.h"
#include "explosion.h"
#include "life.h"

//プロトタイプ宣言
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);

#endif
