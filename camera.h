//=============================================================================
//
// カメラ処理 [camera.h]
// Author : 麦英泳
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitCamera(void);
void UninitCamera(void);

void UpdateCamera(void);
void UpdateCamera2(void);

void SetCamera(void);

D3DXVECTOR3 GetRotCamera(void);
D3DXMATRIX GetMtxView(void);

//追跡時の視点の高さをセット
void SetChaseHightP(float hight);

//カメラの視点と注視点の距離をセット
void SetLengthIntervalCamera(float length);

CAMERA_MODE GetCameraMode();
void SetCameraMode(CAMERA_MODE val);
void SetPlayMode(PLAY_MODE val);
PLAY_MODE GetPlayMode();

bool GetCutScene();

void WinScene();

#endif
