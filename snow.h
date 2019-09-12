//=============================================================================
//
// パーティクル処理 [particle.h]
// Author : 
//
//=============================================================================
#ifndef _SNOW_H_
#define _SNOW_H_

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSnow(void);
void UninitSnow(void);
void UpdateSnow(void);
void DrawSnow(void);

int SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fSizeX, float fSizeY, int nLife);

#endif
