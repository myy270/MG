//=============================================================================
//
// タイマー処理 [timer.h]
// Author : 麦英泳
//
//=============================================================================
#ifndef _TIMER_H_
#define _TIMER_H_

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTimer(void);
void UninitTimer(void);
void UpdateTimer(void);
void DrawTimer(void);

void EnableTimer(bool bEnable);
void ResetTimer(int nTime = 999);

int GetTimer();
bool GetTimeOut();

#endif
