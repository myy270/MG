//=============================================================================
//
// パーティクル処理 [particle.h]
// Author : 
//
//=============================================================================
#ifndef _RAIN_H_
#define _RAIN_H_

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitRain(void);
void UninitRain(void);
void UpdateRain(void);
void DrawRain(void);

int SetRain(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fSizeX, float fSizeY, int nLife,float beilv);

#endif
