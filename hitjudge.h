//=============================================================================
//
// 当たり判定処理 [hitjudge.h]
// Author : HAL東京　GP11C295　樋沼　勇太
//
//=============================================================================
#ifndef _HITJUDGE_H_
#define _HITJUDGE_H_

#include "main.h"
#include "bullet.h"
#include "enemy.h"
#include "player.h"



//**************************************************************************
// マクロ定義
//**************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//BOOL HitjudgeForModel(MODEL *obj1, MODEL *obj2);

// レイによる衝突判定
// 主にスカイドームとの衝突判定に使う

// ポリゴンの頂点を見つける
HRESULT FindVerticesOnPoly(LPD3DXMESH pMesh, DWORD dwPolyIndex, D3DXVECTOR3* pvVertices);

// 正面に対象のメッシュがある？
// その距離は？
BOOL Collide(D3DXVECTOR3 vStart, D3DXVECTOR3 vDir, FLOAT* pfDistance, D3DXVECTOR3* pvNormal, PART *pThing3D, D3DXMATRIX *tempMatrix);

// ドームとの当たり判定をCollide()を使い判定する
// 1回目はベクトルをズラす
// 2回目はmoveを0にする
D3DXVECTOR3 CollideGeo(SRT* m_A, SRT* m_B, D3DXVECTOR3 move, PART* pThingB3D);
#define HIT_SKYDOME_FIRST (15.0)
#define HIT_SKYDOME_SECOND (14.9)
// 一定値ズラす
D3DXVECTOR3 Slip(D3DXVECTOR3 L, D3DXVECTOR3 N);

#endif

