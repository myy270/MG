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

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


#define HIT_WALL_FIRST (10.0)
#define HIT_WALL_SECOND (9.9)


void AnimePosAndHitjudge(D3DXVECTOR3 *af_vec, D3DXMATRIX world, D3DXMATRIX buff, D3DXVECTOR3 bf_vec, D3DXVECTOR3 move_vec, float motionTime, float part, PART opponent, float length);


// 武器の当たり判定
// m_A 前フレームのベクトル
// move 動いたあとのフレーム
// part 対象のpart を入れる （例　&g_enemy.part[i]） 胴体だけとかがいいなら、i は胴体の番号を入れる

// マクロには武器の長さ(float length の値)を追加していく
// 巨大化するなら #define HIT_GIANT_SLASH(10.0) にするとか
BOOL CollideAttack(D3DXVECTOR3* m_A, D3DXVECTOR3 move, PART* part, float length);
#define HIT_THROW_SWORD (1.0)

// ローカル座標をワールド座標に変換する
// world_pos を返り値にする

D3DXVECTOR3 ReturnLocalToWorldVec(D3DXMATRIX world, D3DXMATRIX buff, D3DXVECTOR3 local_pos );


//////////////////////↓使わない////////////////////////////////

// レイによる衝突判定
// 主にスカイドームとの衝突判定に使う

// ポリゴンの頂点を見つける
HRESULT FindVerticesOnPoly(LPD3DXMESH pMesh, DWORD dwPolyIndex, D3DXVECTOR3* pvVertices);

// 正面に対象のメッシュがある？
// その距離は？
BOOL Collide(D3DXVECTOR3 vStart, D3DXVECTOR3 vDir, FLOAT* pfDistance, D3DXVECTOR3* pvNormal, LPD3DXMESH *pThing3D, D3DXMATRIX *tempMatrix);


// ドームとの当たり判定をCollide()を使い判定する
// 1回目はベクトルをズラす
// 2回目はmoveを0にする

D3DXVECTOR3 CollideGeo(D3DXVECTOR3* m_A, D3DXVECTOR3 move, LPD3DXMESH* pThingB3D);
#define HIT_SKYDOME_FIRST (10.0)
#define HIT_SKYDOME_SECOND (9.9)
// 一定値ズラす
D3DXVECTOR3 Slip(D3DXVECTOR3 L, D3DXVECTOR3 N);


// 一定値ズラす
D3DXVECTOR3 Slip(D3DXVECTOR3 L, D3DXVECTOR3 N);
VOID RenderRay(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vStart, D3DXVECTOR3 vDir);

#endif

