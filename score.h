//=============================================================================
//
// スコア処理 [score.h]
// Author : 麦英泳
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

void ChangeScore(int value);//敵の
void ChangeScore2(int value);//プレイヤーの

void compScore(); //プレイヤー勝つ場合true 

OBJECT GetWinner();
#endif
