//=============================================================================
//
// 空、滑走路処理 [field_sky.h]
// Author : HAL東京　GP11C295　樋沼　勇太
//
//=============================================================================
#ifndef _FIELD_STAR_H_
#define _FIELD_STAR_H_

#include "main.h"

//*************キャラクターデータ変数の用意*****************************
#define		NUM_FIELD	(6)

//*************モデルーデータ変数の用意*****************************
#define		NUM_SKYMODEL	(2)

namespace warpzoneNS
{
	// warpzone の中心座標
	// 2次元ベクトルで距離を抽出、一定以下の距離でフラグオン
	const D3DXVECTOR3 warp0 = D3DXVECTOR3(0, 0, 0); // 地面の星
	const D3DXVECTOR3 warp1 = D3DXVECTOR3(333, 0, 476);
	const D3DXVECTOR3 warp2 = D3DXVECTOR3(-330, 0, 476);
	const D3DXVECTOR3 warp3 = D3DXVECTOR3(-558, 0, -176);
	const D3DXVECTOR3 warp4 = D3DXVECTOR3(-14, 0, -572);
	const D3DXVECTOR3 warp5 = D3DXVECTOR3(539, 0, -191);

	// warpzoneからwarpする距離（キャラの中心-warpzoneの中心） 2次元ベクトルの距離
	const float into_warpzone = 10;
}

struct MODEL3D
{
	//xファイル情報
	LPD3DXBUFFER		pMatBuff;			// メッシュのマテリアル情報を格納
	DWORD				nNumMat;			// マテリアル情報の総数
	LPD3DXMESH			pMesh;				// ID3DXMeshインターフェイスへのポインタ
	LPDIRECT3DTEXTURE9 pD3DTextureModel;
};

struct MODEL
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scl;
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxRot;
	bool use;
	MODEL3D model3d;

};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitFieldStar(void);
void initModelPos(D3DXVECTOR3* pos, int i); // ワープゾーンの座標をセット
HRESULT initModeldata(MODEL3D* model3d, const char* modeldata); // モデルの読み込み

void UninitFieldStar(void);
void UpdateFieldStar(void);
void DrawFieldStarModel(void);

void playerWarp(int i);
bool checkClearStage(int i);
float distanceVec2(D3DXVECTOR2 A, D3DXVECTOR2 B);

// クリア時呼び出し、現状のmodeを引数に入れる
void returnClearTrue(MODE mode);

#endif