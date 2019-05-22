//=============================================================================
//
// 爆発処理 [explosion.h]
// Author : 麦英泳
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

//**************************************
// 種類
//**************************************
enum
{
	EXPLOSIONTYPE_BULLET_PLAYER = 0,	// プレイヤーの弾の爆発
	EXPLOSIONTYPE_BULLET_ENEMY,			// 敵の弾の爆発
	EXPLOSIONTYPE_MAX
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);

int SetExplosion(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nType = EXPLOSIONTYPE_BULLET_PLAYER);//引数をデフォルトする方法

#endif
