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

#define PART_MAX	(8)		// パーツの数　体、頭、左手、右手、左足、右足、右手の剣、氷

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
	LPDIRECT3DTEXTURE9 pD3DTextureModel;

	SRT			srt;		//Scaling Rotation Translation
	D3DXMATRIX	mtxS;
	D3DXMATRIX	mtxR;
	D3DXMATRIX	mtxT;
	D3DXMATRIX	mtxWorld;
	D3DXMATRIX  mtxRot;		// 樋沼追加
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

	ITEMTYPE holdItem;	//今持っているアイテム

	STATE state;	//異常状態かどうか
	int stateTime;	//異常状態の残り時間
};



enum PART_ID
{
	BODY,
	HEAD,
	HAND_L,
	HAND_R,
	LEG_L,
	LEG_R,
	SWORD_R,
	ICE,
	PART_ID_MAX
};

enum APPLIMODE
{
	MODE_PLAY,//作ったモーションを再生するモード
	MODE_EDIT,//モーションを作るモード
	MODE_INGAME,//実際プレイするときのモード
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

// コマ送りアニメーションの関数
// rotとpos共用
void FrameFeedVec(D3DXVECTOR3 *af_vec, D3DXVECTOR3 bf_vec, D3DXVECTOR3 move_vec, float motionTime);


#endif
