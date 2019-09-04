//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 麦英泳
//
//=============================================================================
#include "player.h"
#include "camera.h"
#include "input.h"
#include "debugproc.h"
#include "hitjudge.h"
#include "enemy.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define	BODY_PLAYER		"data/mere god/body.x"	// 読み込むモデル名
#define	HEAD_PLAYER		"data/mere god/head.x"	// 読み込むモデル名
#define	HAND_L_PLAYER		"data/mere god/hand_L.x"	// 読み込むモデル名
#define	HAND_R_PLAYER		"data/mere god/hand_R.x"	// 読み込むモデル名
#define	LEG_L_PLAYER		"data/mere god/leg_L.x"	// 読み込むモデル名
#define	LEG_R_PLAYER		"data/mere god/leg_R.x"	// 読み込むモデル名

#define	SWORD_PLAYER	"data/mere god/sword.x"		// 読み込むモデル名

#define	TEXTURE_PLAYER	"data/mere god/knight.png"		// 読み込むモデル名
#define	TEXTURE_SWORD	"data/mere god/kenn.png"		// 読み込むモデル名

#define	PLAYER_RADIUS		(15.0f)						// 半径

#define	VALUE_MOVE_PLAYER	(0.195f)					// 移動速度
#define	RATE_MOVE_PLAYER	(0.025f)					// 移動慣性係数

#define	VALUE_ROTATE_PLAYER	(D3DX_PI * 0.025f)			// 回転速度 4.5度
#define	RATE_ROTATE_PLAYER	(0.10f)						// 回転慣性係数


extern HWND hWnd;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void WriteAnime();
void AnimeWalk(KEY g_anime[]);
void AnimeKen(KEY g_anime[]);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTexturePlayer;		// テクスチャ読み込み場所
LPDIRECT3DTEXTURE9	g_pD3DTextureSword;		// テクスチャ読み込み場所
PLAYER				g_player;					// プレイヤーワーク
D3DXMATRIX mtxWorld;
extern ENEMY g_enemy;

int g_mode = MODE_EDIT;//編輯モードかどうか

int g_conId = 0;	//デフォルトのコントロールID

float g_motionTime = 0.0f;	// アニメーション全体時間　歩く
float g_motionTime2 = 0.0f;	// アニメーション全体時間　剣

int g_keyMax;				//キーフレームの数

bool g_animeState = 0;		//運動状態かどうか　歩く
bool g_animeStateKen = 0;

float g_cancelTime = 0.0f;// 最初状態に戻る時間 歩く

D3DXMATRIX mtxBuff;

//走るキー情報
KEY g_animeWalk[] =
{
	{
		15,
		{
			{// part 0
				D3DXVECTOR3(1.5000f,1.5000f,1.5000f),//S この拡大は全部のパーツに反映する
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,22.4000f,0.0000f),//T　地面との距離（この数値は自分でテストして得るもの）
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,6.5000f,0.0000f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(5.0000f,5.0000f,0.0000f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-5.0000f,5.0000f,0.0000f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(3.0640f,-4.8730f,-0.4090f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-3.0640f,-4.8730f,-0.4090f),//T
			},

			{// part 6
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0f, -7.18f, -0.79f),//T
			},


		}
	},///////////////////////////////////////////////////////////////////////////////////

	{
		30,
		{
			{// part 0
				D3DXVECTOR3(1.5000f,1.5000f,1.5000f),//S
				D3DXVECTOR3(-0.0385f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,22.4000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,6.5000f,0.0000f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(1.4923f,0.0000f,0.0000f),//R
				D3DXVECTOR3(5.0000f,5.0000f,0.0000f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-0.7069f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-5.0000f,5.0000f,0.0000f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-1.0854f,0.0000f,0.0000f),//R
				D3DXVECTOR3(3.0640f,-4.8730f,-0.4090f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.9425f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-3.0640f,-4.8730f,-0.4090f),//T
			},

			{// part 6
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0f, -7.18f, -0.79f),//T
			},


		}
	},///////////////////////////////////////////////////////////////////////////////////

	{
		30,
		{
			{// part 0
				D3DXVECTOR3(1.5000f,1.5000f,1.5000f),//S
				D3DXVECTOR3(-0.0385f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,22.4000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,6.5000f,0.0000f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-0.8639f,0.0000f,0.0000f),//R
				D3DXVECTOR3(5.0000f,5.0000f,0.0000f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(1.0996f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-5.0000f,5.0000f,0.0000f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.9425f,0.0000f,0.0000f),//R
				D3DXVECTOR3(3.0640f,-4.8730f,-0.4090f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-1.0854f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-3.0640f,-4.8730f,-0.4090f),//T
			},

			{// part 6
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0f, -7.18f, -0.79f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////

	{
		30,
		{
			{// part 0
				D3DXVECTOR3(1.5000f,1.5000f,1.5000f),//S
				D3DXVECTOR3(-0.0385f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,22.4000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,6.5000f,0.0000f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(1.4923f,0.0000f,0.0000f),//R
				D3DXVECTOR3(5.0000f,5.0000f,0.0000f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-0.7069f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-5.0000f,5.0000f,0.0000f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(-1.0854f,0.0000f,0.0000f),//R
				D3DXVECTOR3(3.0640f,-4.8730f,-0.4090f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.9425f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-3.0640f,-4.8730f,-0.4090f),//T
			},

			{// part 6
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0f, -7.18f, -0.79f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////

};

KEY g_animeKen[] =
{
	{
		30,
		{
			{// part 0
				D3DXVECTOR3(2.0000f,2.0000f,2.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,28.0000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,7.0600f,0.0900f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 6
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-0.9200f,-7.1900f,-0.7900f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////

	{
		30,
		{
			{// part 0
				D3DXVECTOR3(2.0000f,2.0000f,2.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,28.0000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,7.0600f,0.0900f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 6
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(12.5664f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-0.9200f,-7.1900f,-65.1650f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////

	{
		30,
		{
			{// part 0
				D3DXVECTOR3(2.0000f,2.0000f,2.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,28.0000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,7.0600f,0.0900f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 6
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(25.1326f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-0.9200f,-7.1900f,-55.1650f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////

	{
		30,
		{
			{// part 0
				D3DXVECTOR3(2.0000f,2.0000f,2.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,28.0000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,7.0600f,0.0900f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 6
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(37.7775f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-0.9200f,-7.1900f,-65.1650f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////

	{
		30,
		{
			{// part 0
				D3DXVECTOR3(2.0000f,2.0000f,2.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,28.0000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,7.0600f,0.0900f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 6
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(50.2655f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-0.9200f,-7.1900f,-55.1650f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////

	{
		30,
		{
			{// part 0
				D3DXVECTOR3(2.0000f,2.0000f,2.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,28.0000f,0.0000f),//T
			},

			{// part 1
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,7.0600f,0.0900f),//T
			},

			{// part 2
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 3
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-7.0100f,4.8200f,-0.4900f),//T
			},

			{// part 4
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 5
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-2.0000f,-4.0000f,0.0000f),//T
			},

			{// part 6
				D3DXVECTOR3(1.0000f,1.0000f,1.0000f),//S
				D3DXVECTOR3(62.9106f,0.0000f,0.0000f),//R
				D3DXVECTOR3(-0.9200f,-7.1900f,-65.1650f),//T
			},

		}
	},///////////////////////////////////////////////////////////////////////////////////


};

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{
	

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_player.part[0].partFile = (char *)BODY_PLAYER;//親は一番先にしなければならない
	g_player.part[1].partFile = (char *)HEAD_PLAYER;//(const char *)から(char *)に変換
	g_player.part[2].partFile = (char *)HAND_L_PLAYER;//左手
	g_player.part[3].partFile = (char *)HAND_R_PLAYER;//右手
	g_player.part[4].partFile = (char *)LEG_L_PLAYER;//左足
	g_player.part[5].partFile = (char *)LEG_R_PLAYER;//右足

	g_player.part[6].partFile = (char *)SWORD_PLAYER;//右手の剣

	for (int i = 0; i < PART_MAX; i++)//パーツ番号
	{
		// Xファイルの読み込み
		if(FAILED(D3DXLoadMeshFromX(g_player.part[i].partFile,
									D3DXMESH_SYSTEMMEM,
									pDevice,
									NULL,
									&g_player.part[i].pMatBuff,
									NULL,
									&g_player.part[i].nNumMat,
									&g_player.part[i].pMesh)))
		{
			MessageBox(hWnd, _T("Xファイルの読み込みに失敗しました"), _T("error"), MB_OK | MB_ICONERROR);
			return E_FAIL;
		}

		switch (i)
		{//初期値
		case 0:
		{//体
			g_player.part[i].srt.scl = D3DXVECTOR3(2.0f, 2.0f, 2.0f);//xyz必ず同じように
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(0.0f, 28.0f, 0.0f);// pos.yは足が地面に触れるような数値

			g_player.part[i].parent = NULL;//体の親はNULLにする
			break;
		}
		case 1:
		{//頭
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(0.0f, 7.06f,  0.09f);

			g_player.part[i].parent = &g_player.part[0];//体を親にする
			break;
		}
		case 2:
		{//左手
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(7.01f, 4.82f, -0.49f);

			g_player.part[i].parent = &g_player.part[0];//体を親にする
			break;
		}
		case 3:
		{//右手
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(-7.01f, 4.82f, -0.49f);

			g_player.part[i].parent = &g_player.part[0];//体を親にする
			break;
		}
		case 4:
		{//左足
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(2.0f, -4.00f, 0.0f);

			g_player.part[i].parent = &g_player.part[0];//体を親にする
			break;
		}
		case 5:
		{//右足
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(-2.0f, -4.00f, 0.0f);

			g_player.part[i].parent = &g_player.part[0];//体を親にする
			break;
		}
		case 6:
		{//右手の剣
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	
			g_player.part[i].srt.pos = D3DXVECTOR3(-0.92f, -7.19f, -0.79f);	//ここの数値要注意、特にｚの符号

			g_player.part[i].parent = &g_player.part[3];//右手を親にする！！
			break;
		}

		}

		g_player.part[i].use = true;

	}

	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.fRadius = PLAYER_RADIUS;	//影のサイズ用、当たり判定用　

	g_player.state = NORMAL;
	

#if 1
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
								TEXTURE_PLAYER,			// ファイルの名前
								&g_pD3DTexturePlayer);	// 読み込むメモリー

		// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_SWORD,				// ファイルの名前
								&g_pD3DTextureSword);	// 読み込むメモリー


#endif

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	for (int i = 0; i < PART_MAX; i++)//パーツ番号
	{
		if (g_player.part[i].pMesh != NULL)
		{// メッシュの開放
			g_player.part[i].pMesh->Release();
			g_player.part[i].pMesh = NULL;
		}

		if (g_player.part[i].pMatBuff != NULL)
		{// マテリアルの開放
			g_player.part[i].pMatBuff->Release();
			g_player.part[i].pMatBuff = NULL;
		}
	}

	if (g_pD3DTexturePlayer != NULL)
	{// テクスチャの開放
		g_pD3DTexturePlayer->Release();
		g_pD3DTexturePlayer = NULL;
	}

	SAFE_RELEASE(g_pD3DTextureSword);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
#ifdef _DEBUG
	//モードの入力
	if (GetKeyboardPress(DIK_1))
	{
		g_mode = MODE_PLAY;
	}
	if (GetKeyboardPress(DIK_2))
	{
		g_mode = MODE_EDIT;
	}
	if (GetKeyboardPress(DIK_3))
	{
		g_mode = MODE_INGAME;
	}


	//コントロールIDの入力
	if (GetKeyboardPress(DIK_NUMPAD0))
	{
		g_conId = 0;
	}
	else if (GetKeyboardPress(DIK_NUMPAD1))
	{
		g_conId = 1;
	}
	else if (GetKeyboardPress(DIK_NUMPAD2))
	{
		g_conId = 2;
	}
	else if (GetKeyboardPress(DIK_NUMPAD3))
	{
		g_conId = 3;
	}
	else if (GetKeyboardPress(DIK_NUMPAD4))
	{
		g_conId = 4;
	}
	else if (GetKeyboardPress(DIK_NUMPAD5))
	{
		g_conId = 5;
	}
	else if (GetKeyboardPress(DIK_NUMPAD6))
	{
		g_conId = 6;
	}


#endif





	switch (g_mode)
	{
	case MODE_PLAY:
	{
		//AnimeKen(g_animeKen);
		AnimeWalk(g_animeWalk);
		break;
	}

	case MODE_EDIT:
	{

#ifdef _DEBUG

		//モデルパーツのコントローラー（モーション作成ツール）
		//回転
		{
			//x軸回転
			if (GetKeyboardPress(DIK_Z))
			{
				g_player.part[g_conId].srt.rot.x += VALUE_ROTATE_PLAYER;
				//if (g_player.part[g_conId].srt.rot.x > D3DX_PI)
				//{
				//	g_player.part[g_conId].srt.rot.x -= D3DX_PI * 2.0f;
				//}
			}
			else if (GetKeyboardPress(DIK_X))
			{
				g_player.part[g_conId].srt.rot.x -= VALUE_ROTATE_PLAYER;
				//if (g_player.part[g_conId].srt.rot.x < -D3DX_PI)
				//{
				//	g_player.part[g_conId].srt.rot.x += D3DX_PI * 2.0f;
				//}
			}

			//y軸回転
			if (GetKeyboardPress(DIK_C))
			{
				g_player.part[g_conId].srt.rot.y += VALUE_ROTATE_PLAYER;
				if (g_player.part[g_conId].srt.rot.y > D3DX_PI)
				{
					g_player.part[g_conId].srt.rot.y -= D3DX_PI * 2.0f;
				}
			}
			else if (GetKeyboardPress(DIK_V))
			{
				g_player.part[g_conId].srt.rot.y -= VALUE_ROTATE_PLAYER;
				if (g_player.part[g_conId].srt.rot.y < -D3DX_PI)
				{
					g_player.part[g_conId].srt.rot.y += D3DX_PI * 2.0f;
				}
			}

			//z軸回転
			if (GetKeyboardPress(DIK_B))
			{
				g_player.part[g_conId].srt.rot.z += VALUE_ROTATE_PLAYER;
				if (g_player.part[g_conId].srt.rot.z > D3DX_PI)
				{
					g_player.part[g_conId].srt.rot.z -= D3DX_PI * 2.0f;
				}
			}
			else if (GetKeyboardPress(DIK_N))
			{
				g_player.part[g_conId].srt.rot.z -= VALUE_ROTATE_PLAYER;
				if (g_player.part[g_conId].srt.rot.z < -D3DX_PI)
				{
					g_player.part[g_conId].srt.rot.z += D3DX_PI * 2.0f;
				}
			}

		}

		//移動
		{
			//x軸移動
			if (GetKeyboardPress(DIK_A))
			{
				g_player.part[g_conId].srt.pos.x -= VALUE_MOVE_PLAYER;
			}
			else if (GetKeyboardPress(DIK_D))
			{
				g_player.part[g_conId].srt.pos.x += VALUE_MOVE_PLAYER;
			}

			//y軸移動
			if (GetKeyboardPress(DIK_F))
			{
				g_player.part[g_conId].srt.pos.y -= VALUE_MOVE_PLAYER;
			}
			else if (GetKeyboardPress(DIK_G))
			{
				g_player.part[g_conId].srt.pos.y += VALUE_MOVE_PLAYER;
			}

			//z軸移動
			if (GetKeyboardPress(DIK_S))
			{
				g_player.part[g_conId].srt.pos.z -= VALUE_MOVE_PLAYER;
			}
			else if (GetKeyboardPress(DIK_W))
			{
				g_player.part[g_conId].srt.pos.z += VALUE_MOVE_PLAYER;
			}
		}

		//縮小拡大
		{
			if (GetKeyboardPress(DIK_J))
			{
				g_player.part[g_conId].srt.scl.x -= 0.1f;
				g_player.part[g_conId].srt.scl.y -= 0.1f;
				g_player.part[g_conId].srt.scl.z -= 0.1f;
			}
			else if (GetKeyboardPress(DIK_K))
			{
				g_player.part[g_conId].srt.scl.x += 0.1f;
				g_player.part[g_conId].srt.scl.y += 0.1f;
				g_player.part[g_conId].srt.scl.z += 0.1f;
			}
		}


#endif		

		break;
	}

	case MODE_INGAME:
	{
		D3DXVECTOR3 rotCamera;
		float fDiffRotY;

		// カメラの向き取得
		rotCamera = GetRotCamera();

		g_animeState = 0;//運動状態をリセット

		//移動
		if (GetKeyboardPress(DIK_A) || IsButtonPress(0, BUTTON_LEFT) || IsButtonPress(0, BUTTON_LSTICK_LEFT))
		{
			g_animeState = 1;//動く状態にする

			if (GetKeyboardPress(DIK_W) || IsButtonPress(0, BUTTON_UP) || IsButtonPress(0, BUTTON_LSTICK_UP))
			{// 左前移動
				g_player.move.x -= sinf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_PLAYER;
				g_player.move.z -= cosf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_PLAYER;

				g_player.rotDest.y = rotCamera.y + D3DX_PI * 0.75f;
			}
			else if (GetKeyboardPress(DIK_S) || IsButtonPress(0, BUTTON_DOWN) || IsButtonPress(0, BUTTON_LSTICK_DOWN))
			{// 左後移動
				g_player.move.x -= sinf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
				g_player.move.z -= cosf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;

				g_player.rotDest.y = rotCamera.y + D3DX_PI * 0.25f;
			}
			else
			{// 左移動
				g_player.move.x -= sinf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_PLAYER;
				g_player.move.z -= cosf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_PLAYER;

				g_player.rotDest.y = rotCamera.y + D3DX_PI * 0.50f;
			}
		}
		else if (GetKeyboardPress(DIK_D) || IsButtonPress(0, BUTTON_RIGHT) || IsButtonPress(0, BUTTON_LSTICK_RIGHT))
		{
			g_animeState = 1;//動く状態にする

			if (GetKeyboardPress(DIK_W) || IsButtonPress(0, BUTTON_UP) || IsButtonPress(0, BUTTON_LSTICK_UP))
			{// 右前移動
				g_player.move.x -= sinf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_PLAYER;
				g_player.move.z -= cosf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_PLAYER;

				g_player.rotDest.y = rotCamera.y - D3DX_PI * 0.75f;
			}
			else if (GetKeyboardPress(DIK_S) || IsButtonPress(0, BUTTON_DOWN) || IsButtonPress(0, BUTTON_LSTICK_DOWN))
			{// 右後移動
				g_player.move.x -= sinf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
				g_player.move.z -= cosf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;

				g_player.rotDest.y = rotCamera.y - D3DX_PI * 0.25f;
			}
			else
			{// 右移動
				g_player.move.x -= sinf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_PLAYER;
				g_player.move.z -= cosf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_PLAYER;

				g_player.rotDest.y = rotCamera.y - D3DX_PI * 0.50f;
			}
		}
		else if (GetKeyboardPress(DIK_W) || IsButtonPress(0, BUTTON_UP) || IsButtonPress(0, BUTTON_LSTICK_UP))
		{
			g_animeState = 1;//動く状態にする

			// 前移動
			g_player.move.x -= sinf(D3DX_PI + rotCamera.y) * VALUE_MOVE_PLAYER;
			g_player.move.z -= cosf(D3DX_PI + rotCamera.y) * VALUE_MOVE_PLAYER;

			g_player.rotDest.y = D3DX_PI + rotCamera.y;
		}
		else if (GetKeyboardPress(DIK_S) || IsButtonPress(0, BUTTON_DOWN) || IsButtonPress(0, BUTTON_LSTICK_DOWN))
		{
			g_animeState = 1;//動く状態にする

			// 後移動
			g_player.move.x -= sinf(rotCamera.y) * VALUE_MOVE_PLAYER;
			g_player.move.z -= cosf(rotCamera.y) * VALUE_MOVE_PLAYER;

			g_player.rotDest.y = rotCamera.y;
		}


		AnimeWalk(g_animeWalk);
		AnimeKen(g_animeKen);

		// 目的の角度までの差分
		fDiffRotY = g_player.rotDest.y - g_player.part[0].srt.rot.y;//体を基準に
		if (fDiffRotY > D3DX_PI)
		{
			fDiffRotY -= D3DX_PI * 2.0f;
		}
		if (fDiffRotY < -D3DX_PI)
		{
			fDiffRotY += D3DX_PI * 2.0f;
		}

		// 目的の角度まで慣性をかける　段々目的の角度に変化する
		g_player.part[0].srt.rot.y += fDiffRotY * RATE_ROTATE_PLAYER;//体に反映
		if (g_player.part[0].srt.rot.y > D3DX_PI)
		{
			g_player.part[0].srt.rot.y -= D3DX_PI * 2.0f;
		}
		if (g_player.part[0].srt.rot.y < -D3DX_PI)
		{
			g_player.part[0].srt.rot.y += D3DX_PI * 2.0f;
		}

		/// 位置移動を反映
		g_player.part[0].srt.pos.x += g_player.move.x;//体に反映
		g_player.part[0].srt.pos.y += g_player.move.y;
		g_player.part[0].srt.pos.z += g_player.move.z;

		//移動範囲　//体を基準に
		{
			if (g_player.part[0].srt.pos.x < -630.0f)
			{
				g_player.part[0].srt.pos.x = -630.0f;
			}
			if (g_player.part[0].srt.pos.x > 630.0f)
			{
				g_player.part[0].srt.pos.x = 630.0f;
			}
			if (g_player.part[0].srt.pos.y < 10.0f)
			{
				g_player.part[0].srt.pos.y = 10.0f;
			}
			if (g_player.part[0].srt.pos.y > 150.0f)
			{
				g_player.part[0].srt.pos.y = 150.0f;
			}
			if (g_player.part[0].srt.pos.z > 630.0f)
			{
				g_player.part[0].srt.pos.z = 630.0f;
			}
			if (g_player.part[0].srt.pos.z < -630.0f)
			{
				g_player.part[0].srt.pos.z = -630.0f;
			}
		}

		// 移動量に慣性をかける　運動エネルギーを一部損して保存する、次のフレームに使う
		//損の部分イコール次のフレームに獲得の運動エネルギーの場合、速度が最大(6.05f)になって、等速直線運動になる
		g_player.move.x += (0.0f - g_player.move.x) * RATE_MOVE_PLAYER;//即ち、g_player.move.x = g_player.move.x * (1 - RATE_MOVE_PLAYER;)
		g_player.move.y += (0.0f - g_player.move.y) * RATE_MOVE_PLAYER;
		g_player.move.z += (0.0f - g_player.move.z) * RATE_MOVE_PLAYER;

		break;
	}



	}//switch end



//運動情報を書き出す
#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_F2))
	{
		WriteAnime();
	}
#endif

	PrintDebugProc("編輯モード：%d \n\n", g_mode);

	PrintDebugProc("コントロールのパーツ番号：%d \n\n", g_conId);

	PrintDebugProc("[S：(%f : %f : %f)]\n", g_player.part[g_conId].srt.scl.x, 
											g_player.part[g_conId].srt.scl.y, 
											g_player.part[g_conId].srt.scl.z);

	PrintDebugProc("[R：(%f : %f : %f)]\n", g_player.part[g_conId].srt.rot.x, 
											g_player.part[g_conId].srt.rot.y, 
											g_player.part[g_conId].srt.rot.z);

	PrintDebugProc("[T：(%f : %f : %f)]\n\n", g_player.part[g_conId].srt.pos.x, 
											g_player.part[g_conId].srt.pos.y, 
											g_player.part[g_conId].srt.pos.z);

	PrintDebugProc("目的向き：%f \n\n", g_player.rotDest.y);

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;

	D3DMATERIAL9 matDef;
	pDevice->GetMaterial(&matDef);// デフォルトのマテリアルを取得

	for (int i = 0; i < PART_MAX; i++)//パーツ番号
	{
		if (g_player.part[i].use)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&mtxWorld);

			// スケールを反映
			D3DXMatrixScaling(&mtxScl, g_player.part[i].srt.scl.x,
				g_player.part[i].srt.scl.y,
				g_player.part[i].srt.scl.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);
			
			g_player.part[i].mtxS = mtxScl;

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.part[i].srt.rot.y,
				g_player.part[i].srt.rot.x,
				g_player.part[i].srt.rot.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

			g_player.part[i].mtxR = mtxRot;

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, g_player.part[i].srt.pos.x,
				g_player.part[i].srt.pos.y,
				g_player.part[i].srt.pos.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

			g_player.part[i].mtxT = mtxTranslate;

			//親が存在する場合は親のワールドマトリクスを合成
			if (g_player.part[i].parent)
			{
				if ((i == SWORD_R)&&(g_animeStateKen))
				{
					D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxBuff);
					
				}
				else
				{
					D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &g_player.part[i].parent->mtxWorld);
				}
				
			}

			g_player.part[i].mtxWorld = mtxWorld;//ワールドマトリクスを保存

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

			// マテリアル情報に対するポインタを取得
			pD3DXMat = (D3DXMATERIAL*)g_player.part[i].pMatBuff->GetBufferPointer();


			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTexturePlayer);

			if (i == SWORD_R)
			{
				pDevice->SetTexture(0, g_pD3DTextureSword);

			}

			for (int nCntMat = 0; nCntMat < (int)g_player.part[i].nNumMat; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// 描画
				g_player.part[i].pMesh->DrawSubset(nCntMat);
			}

		}
	}

	pDevice->SetMaterial(&matDef);// マテリアルをデフォルトに戻す
}

//=============================================================================
// プレイヤーを取得
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &g_player;
}

//=============================================================================
// 位置取得
//=============================================================================
D3DXVECTOR3 GetPositionPlayer(void)
{
	return g_player.part[0].srt.pos;//体を基準に
}

//=============================================================================
// 向き取得
//=============================================================================
D3DXVECTOR3 GetRotationPlayer(void)
{
	return g_player.part[0].srt.rot;//体を基準に
}

//=============================================================================
// 目的の向き取得
//=============================================================================
D3DXVECTOR3 GetRotationDestPlayer(void)
{
	return g_player.rotDest;
}

//=============================================================================
// 移動量取得
//=============================================================================
D3DXVECTOR3 GetMovePlayer(void)
{
	return g_player.move;
}

// アニメ書き出し
void WriteAnime()
{
	FILE *fp;
	fp = fopen("animeKen4.txt", "a+");//"a+"は書き込みのモード。ファイルがないと、自動に作成
	if (fp == NULL)
	{
		return;
	}
		
	//\t　水平タブ
	fprintf(fp, "\t{\n");
	fprintf(fp, "\t\t60,\n");//60フレーム
	fprintf(fp, "\t\t{\n");

	for (int i = 0; i < PART_MAX; i++)
	{
		fprintf(fp, "\t\t\t{// part %d\n", i);
		fprintf(fp, "\t\t\t\tD3DXVECTOR3(%.4ff,%.4ff,%.4ff),//S\n", g_player.part[i].srt.scl.x,
																	g_player.part[i].srt.scl.y,
																	g_player.part[i].srt.scl.z);
																				  
		fprintf(fp, "\t\t\t\tD3DXVECTOR3(%.4ff,%.4ff,%.4ff),//R\n", g_player.part[i].srt.rot.x,
																	g_player.part[i].srt.rot.y,
																	g_player.part[i].srt.rot.z);
																				  
		fprintf(fp, "\t\t\t\tD3DXVECTOR3(%.4ff,%.4ff,%.4ff),//T\n", g_player.part[i].srt.pos.x,
																	g_player.part[i].srt.pos.y,
																	g_player.part[i].srt.pos.z);

		fprintf(fp, "\t\t\t},\n");
		fprintf(fp, "\n");
	}
	fprintf(fp, "\t\t}\n");
	fprintf(fp, "\t},///////////////////////////////////////////////////////////////////////////////////\n");
	fprintf(fp, "\n");

	fclose(fp);
}


void AnimeWalk(KEY g_anime[])
{
	g_keyMax = sizeof(g_animeWalk) / sizeof(KEY);//sizeof(g_anime)ではダメ

	switch (g_mode)
	{
	case MODE_PLAY:
	{
		//アニメーション 
		int i = (int)g_motionTime;  //現在のキーフレームナンバー

		//if (i > g_keyMax - 2)//最大キーフレームナンバーを超えたら
		//{
		//	i = g_keyMax - 2;//最大キーフレームナンバーにする
		//}

		//loopできるように
		if (i > g_keyMax - 2)//最大キーフレームナンバーを超えたら
		{
			i = 1;
			g_motionTime = 1.0f;
		}

		float dt = 1.0f / g_anime[i].frame;//補間の間隔時間

		g_motionTime += dt;

		if (g_motionTime > g_keyMax - 1.0f)//最大時間を超えたら
		{
			g_motionTime = g_keyMax - 1.0f;//最大最大時間にする
		}

		if (g_motionTime - i > 1.0f) //誤差を修正　想定の1.0を超えたら
		{
			i++;//次のキーフレームに入る
		}

		//if (GetKeyboardPress(DIK_SPACE))
		//{
		//	g_motionTime = 0.0f;	//リセット
		//	i = (int)g_motionTime;	//重要
		//}

		if (1)
		{
			//接続の補間は　[i] * 1.0です、[i + 1] * 0.0ではない
			for (int j = 0; j < PART_MAX; j++)//パーツ番号
			{
				// Scale
				//g_player.part[j].srt.scl.x = g_anime[i].key[j].scl.x +				// 前のキーフレーム位置
				//	(g_anime[i + 1].key[j].scl.x - g_anime[i].key[j].scl.x)			// 前のキーフレームと次のキーフレームの差分
				//	* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				//g_player.part[j].srt.scl.y = g_anime[i].key[j].scl.y +				// 前のキーフレーム位置
				//	(g_anime[i + 1].key[j].scl.y - g_anime[i].key[j].scl.y)			// 前のキーフレームと次のキーフレームの差分
				//	* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				//g_player.part[j].srt.scl.z = g_anime[i].key[j].scl.z +				// 前のキーフレーム位置
				//	(g_anime[i + 1].key[j].scl.z - g_anime[i].key[j].scl.z)			// 前のキーフレームと次のキーフレームの差分
				//	* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				// Rotation
				g_player.part[j].srt.rot.x = g_anime[i].key[j].rot.x +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].rot.x - g_anime[i].key[j].rot.x)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				g_player.part[j].srt.rot.y = g_anime[i].key[j].rot.y +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].rot.y - g_anime[i].key[j].rot.y)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				g_player.part[j].srt.rot.z = g_anime[i].key[j].rot.z +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].rot.z - g_anime[i].key[j].rot.z)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				// Position
				//g_player.part[j].srt.pos.x = g_anime[i].key[j].pos.x +				// 前のキーフレーム位置
				//	(g_anime[i + 1].key[j].pos.x - g_anime[i].key[j].pos.x)			// 前のキーフレームと次のキーフレームの差分
				//	* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				//g_player.part[j].srt.pos.y = g_anime[i].key[j].pos.y +				// 前のキーフレーム位置
				//	(g_anime[i + 1].key[j].pos.y - g_anime[i].key[j].pos.y)			// 前のキーフレームと次のキーフレームの差分
				//	* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				//g_player.part[j].srt.pos.z = g_anime[i].key[j].pos.z +				// 前のキーフレーム位置
				//	(g_anime[i + 1].key[j].pos.z - g_anime[i].key[j].pos.z)			// 前のキーフレームと次のキーフレームの差分
				//	* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける
			}
		}

		break;
	}

	case MODE_INGAME:
	{
		//アニメーション 
		int i = (int)g_motionTime;  //現在のキーフレームナンバー

		//loopできるように
		if (i > g_keyMax - 2)//最大キーフレームナンバーを超えたら
		{
			i = 1;
			g_motionTime = 1.0f;
		}

		float dt = 1.0f / g_anime[i].frame;//補間の間隔時間

		g_motionTime += dt;

		if (g_motionTime > g_keyMax - 1.0f)//最大時間を超えたら
		{
			g_motionTime = g_keyMax - 1.0f;//最大時間にする
		}

		if (g_motionTime - i > 1.0f) //誤差を修正　想定の1.0を超えたら
		{
			i++;//次のキーフレームに入る
		}

		if (g_animeState == 0)
		{
			g_motionTime = 0.0f;	//リセット
			i = (int)g_motionTime;	//重要

			if (g_player.state != FROZEN)
			{
				g_cancelTime += dt;//0番キーフレームのtimeを使う
			}

			if (g_cancelTime > 1.0f)//最大時間を超えたら
			{
				g_cancelTime = 1.0f;//最大最大時間にする
			}

			//接続の補間は　[i] * 1.0です、[i + 1] * 0.0ではない
			for (int j = 0; j < PART_MAX; j++)//パーツ番号
			{//最初のキーの状態に戻る
				// Scale
				//g_player.part[j].srt.scl.x = g_player.part[j].srt.scl.x +	
				//	(g_anime[0].key[j].scl.x - g_player.part[j].srt.scl.x)	
				//	* g_cancelTime;											

				//g_player.part[j].srt.scl.y = g_player.part[j].srt.scl.y +	
				//	(g_anime[0].key[j].scl.y - g_player.part[j].srt.scl.y)	
				//	* g_cancelTime;											

				//g_player.part[j].srt.scl.z = g_player.part[j].srt.scl.z +	
				//	(g_anime[0].key[j].scl.z - g_player.part[j].srt.scl.z)	
				//	* g_cancelTime;											

				// Rotation
				g_player.part[j].srt.rot.x = g_player.part[j].srt.rot.x +
					(g_anime[0].key[j].rot.x - g_player.part[j].srt.rot.x)
					* g_cancelTime;

				//g_player.part[j].srt.rot.y = g_player.part[j].srt.rot.y +	
				//	(g_anime[0].key[j].rot.y - g_player.part[j].srt.rot.y)	
				//	* g_cancelTime;											

				g_player.part[j].srt.rot.z = g_player.part[j].srt.rot.z +
					(g_anime[0].key[j].rot.z - g_player.part[j].srt.rot.z)
					* g_cancelTime;

				// Position
				//g_player.part[j].srt.pos.x = g_player.part[j].srt.pos.x +	
				//	(g_anime[0].key[j].pos.x - g_player.part[j].srt.pos.x)	
				//	* g_cancelTime;											

				//g_player.part[j].srt.pos.y = g_player.part[j].srt.pos.y +	
				//	(g_anime[0].key[j].pos.y - g_player.part[j].srt.pos.y)	
				//	* g_cancelTime;											

				//g_player.part[j].srt.pos.z = g_player.part[j].srt.pos.z +	
				//	(g_anime[0].key[j].pos.z - g_player.part[j].srt.pos.z)	
				//	* g_cancelTime;											
			}

		}
		else
		{
			g_cancelTime = 0.0f;	//リセット

			//接続の補間は　[i] * 1.0です、[i + 1] * 0.0ではない
			for (int j = 0; j < PART_MAX; j++)//パーツ番号
			{
				// Scale
				//g_player.part[j].srt.scl.x = g_anime[i].key[j].scl.x +				// 前のキーフレーム位置
				//	(g_anime[i + 1].key[j].scl.x - g_anime[i].key[j].scl.x)			// 前のキーフレームと次のキーフレームの差分
				//	* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				//g_player.part[j].srt.scl.y = g_anime[i].key[j].scl.y +				// 前のキーフレーム位置
				//	(g_anime[i + 1].key[j].scl.y - g_anime[i].key[j].scl.y)			// 前のキーフレームと次のキーフレームの差分
				//	* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				//g_player.part[j].srt.scl.z = g_anime[i].key[j].scl.z +				// 前のキーフレーム位置
				//	(g_anime[i + 1].key[j].scl.z - g_anime[i].key[j].scl.z)			// 前のキーフレームと次のキーフレームの差分
				//	* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				// Rotation
				g_player.part[j].srt.rot.x = g_anime[i].key[j].rot.x +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].rot.x - g_anime[i].key[j].rot.x)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				//g_player.part[j].srt.rot.y = g_anime[i].key[j].rot.y +				// 前のキーフレーム位置
				//	(g_anime[i + 1].key[j].rot.y - g_anime[i].key[j].rot.y)			// 前のキーフレームと次のキーフレームの差分
				//	* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				g_player.part[j].srt.rot.z = g_anime[i].key[j].rot.z +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].rot.z - g_anime[i].key[j].rot.z)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				// Position
				//g_player.part[j].srt.pos.x = g_anime[i].key[j].pos.x +				// 前のキーフレーム位置
				//	(g_anime[i + 1].key[j].pos.x - g_anime[i].key[j].pos.x)			// 前のキーフレームと次のキーフレームの差分
				//	* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				//g_player.part[j].srt.pos.y = g_anime[i].key[j].pos.y +				// 前のキーフレーム位置
				//	(g_anime[i + 1].key[j].pos.y - g_anime[i].key[j].pos.y)			// 前のキーフレームと次のキーフレームの差分
				//	* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				//g_player.part[j].srt.pos.z = g_anime[i].key[j].pos.z +				// 前のキーフレーム位置
				//	(g_anime[i + 1].key[j].pos.z - g_anime[i].key[j].pos.z)			// 前のキーフレームと次のキーフレームの差分
				//	* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける
			}

		}

		break;
	}

	}//end switch


}

void AnimeKen(KEY g_anime[])
{
	if (g_animeStateKen == 0)
	{
		if (GetKeyboardPress(DIK_L))
		{
			g_animeStateKen = 1;//動く状態にする	
			
			D3DXMatrixIdentity(&mtxBuff);
			D3DXMatrixMultiply(&mtxBuff, &mtxBuff, &g_player.part[SWORD_R].parent->mtxT);
			D3DXMatrixMultiply(&mtxBuff, &mtxBuff, &g_player.part[SWORD_R].parent->parent->mtxWorld);//剣を投げる時の、親の行列情報を保存
		}

	}

	if (g_animeStateKen)
	{
		g_keyMax = sizeof(g_animeKen) / sizeof(KEY);//sizeof(g_anime)ではダメ

		//アニメーション 
		int i = (int)g_motionTime2;  //i:現在のキーフレームナンバー

		float dt = 1.0f / g_anime[i].frame;//補間の間隔時間

		//完成したら、元の状態に戻る
		if (i > g_keyMax - 2)//最大キーフレームナンバーを超えたら
		{
			i = 0;
			g_motionTime2 = 0.0f;

			g_animeStateKen = 0;
			dt = 0;
		}

		g_motionTime2 += dt;

		if (g_motionTime2 > g_keyMax - 1.0f)//最大時間を超えたら
		{
			g_motionTime2 = g_keyMax - 1.0f;//最大最大時間にする

		}

		if (g_motionTime2 - i > 1.0f) //誤差を修正　想定の1.0を超えたら
		{
			i++;//次のキーフレームに入る
		}


		//接続の補間は　[i] * 1.0です、[i + 1] * 0.0ではない

		int j = SWORD_R;

		// Rotation
		FrameFeedVec(&g_player.part[j].srt.rot, g_anime[i].key[j].rot, g_anime[i + 1].key[j].rot, g_motionTime2 - i);

		// Position
		AnimePosAndHitjudge(&g_player.part[j].srt.pos, mtxWorld, mtxBuff, g_anime[i].key[j].pos , g_anime[i + 1].key[j].pos, g_motionTime2 - i, PART_MAX_ENEMY, g_enemy.part[i], HIT_THROW_SWORD);

		// PrintDebugProc("aaaaaa：%f ,%f ,%f  \n", current_pos.x, current_pos.y, current_pos.z);

	}//

}


void FrameFeedVec(D3DXVECTOR3 *af_vec, D3DXVECTOR3 bf_vec, D3DXVECTOR3 move_vec, float motionTime)
{
	af_vec->x = bf_vec.x +				// 前のキーフレーム位置
		(move_vec.x - bf_vec.x)			// 前のキーフレームと次のキーフレームの差分
		* (motionTime);					// に　全体アニメ時間の小数点以下の割合をかける

	af_vec->y = bf_vec.y +				// 前のキーフレーム位置
		(move_vec.y - bf_vec.y)			// 前のキーフレームと次のキーフレームの差分
		* (motionTime);					// に　全体アニメ時間の小数点以下の割合をかける

	af_vec->z = bf_vec.z +				// 前のキーフレーム位置
		(move_vec.z - bf_vec.z)			// 前のキーフレームと次のキーフレームの差分
		* (motionTime);					// に　全体アニメ時間の小数点以下の割合をかける
	
}


