//=============================================================================
//
// エネミー処理 [enemy.h]
// Author : 麦英泳
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "item.h"

#define PART_MAX_ENEMY	(7)		// パーツの数

//*****************************************************************************
// 構造体定義
//*****************************************************************************

struct ENEMY
{
	D3DXVECTOR3 move;		// 移動量
	D3DXVECTOR3 rotDest;	// 目的の向き
	float fRadius;			// 半径
	int nIdxShadow;			// 影ID
	PART part[PART_MAX_ENEMY];

	ITEMTYPE holdItem;

	STATE state;
	int stateTime;
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
ENEMY *GetEnemy(void);

D3DXVECTOR3 GetPositionEnemy(void);
D3DXVECTOR3 GetRotationEnemy(void);
D3DXVECTOR3 GetRotationDestEnemy(void);
D3DXVECTOR3 GetMoveEnemy(void);

#endif
