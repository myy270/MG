//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : 麦英泳
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "item.h"

#define PART_MAX	(7)		// パーツの数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
struct SRT
{
	D3DXVECTOR3 scl;		// 拡大縮小	
	D3DXVECTOR3 rot;		// 現在の向き
	D3DXVECTOR3 pos;		// 現在の位置
};

//キーフレームの定義
struct KEY
{
	int			frame;			//このキーフレームの総フレーム数
	SRT			key[PART_MAX];	//キーフレームのデータ
};

struct PART
{
	char *partFile;
	//xファイル情報
	LPD3DXBUFFER		pMatBuff;			// メッシュのマテリアル情報を格納
	DWORD				nNumMat;			// マテリアル情報の総数
	LPD3DXMESH			pMesh;				// ID3DXMeshインターフェイスへのポインタ

	SRT			srt;		//Scaling Rotation Translation
	D3DXMATRIX	mtxWorld;
	PART		*parent;
	bool		use;
};

enum STATE
{
	NORMAL,
	FROZEN,
	STATE_MAX
};


struct PLAYER
{
	D3DXVECTOR3 move;		// 移動量
	D3DXVECTOR3 rotDest;	// 目的の向き
	float fRadius;			// 半径
	int nIdxShadow;			// 影ID
	PART part[PART_MAX];

	ITEMTYPE holdItem;

	STATE state;
	int stateTime;
};

enum PART_ID
{	
	BODY,
	HEAD,
	HAND,
	LEG,
	PART_ID_MAX
};

enum APPLIMODE
{
	MODE_PLAY,
	MODE_EDIT,
	APPLIMODE_MAX
};



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);

D3DXVECTOR3 GetPositionPlayer(void);
D3DXVECTOR3 GetRotationPlayer(void);
D3DXVECTOR3 GetRotationDestPlayer(void);
D3DXVECTOR3 GetMovePlayer(void);



#endif
