//=============================================================================
//
// エネミー処理 [enemy.cpp]
// Author : 麦英泳
//
//=============================================================================
#include "player.h"
#include "enemy.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "bullet.h"
#include "effect.h"
#include "item.h"
#include "score.h"
//#include "sound.h"
#include "debugproc.h"
#include "timer.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	BODY_ENEMY		"data/MODEL/bearBodyPink.x"	// 読み込むモデル名
#define	HEAD_ENEMY		"data/MODEL/bearHeadPink.x"	// 読み込むモデル名
#define	HAND_ENEMY		"data/MODEL/bearHandPink.x"	// 読み込むモデル名
#define	LEG_ENEMY		"data/MODEL/bearLegPink.x"	// 読み込むモデル名
#define	ICE_BLOCK		"data/MODEL/iceBlock.x"		// 読み込むモデル名



#define	ENEMY_RADIUS		(15.0f)						// 半径

#define	VALUE_MOVE_ENEMY	(0.195f)					// 移動速度
#define	RATE_MOVE_ENEMY	(0.025f)						// 移動慣性係数

#define	VALUE_ROTATE_ENEMY	(D3DX_PI * 0.025f)			// 回転速度 4.5度
#define	RATE_ROTATE_ENEMY	(0.10f)						// 回転慣性係数

#define	VALUE_MOVE_BULLET_ENEMY	(7.5f)						// 弾の移動速度

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

static void AnimeWalk();
void AI();
int AI2();
int AI3();

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureEnemy;		// テクスチャ読み込み場所
ENEMY				g_enemy;					// エネミーワーク

static int g_conId = 0;//コントロールID
 
static float g_motionTime = 0.0f;// アニメーション全体時間
static int g_keyMax;
static bool g_animeState = 0;
 
static float g_cancelTime = 0.0f;// 最初状態に戻る時間

bool g_up;//AI行動
bool g_down;//AI行動
bool g_left;//AI行動
bool g_right;//AI行動

bool g_ai;//AIモード

static KEY g_anime[] =
{
	{
		15,
		{
			{// part 0
				D3DXVECTOR3(1.5000f,1.5000f,1.5000f),//S
				D3DXVECTOR3(0.0000f,0.0000f,0.0000f),//R
				D3DXVECTOR3(0.0000f,22.4000f,0.0000f),//T
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
				D3DXVECTOR3(0.0000f,3.1416f,0.0000f),//R
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
				D3DXVECTOR3(0.7069f,3.1416f,0.0000f),//R
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
				D3DXVECTOR3(-1.0996f,3.1416f,0.0000f),//R
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
				D3DXVECTOR3(0.7069f,3.1416f,0.0000f),//R
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

		}
	},///////////////////////////////////////////////////////////////////////////////////

};



//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy(void)
{
	

	if (GetPlayMode() == PLAY_MODE_SINGLE)
	{
		g_ai = false;
	}
	else if (GetPlayMode() == PLAY_MODE_DOUBLE)
	{
		g_ai = false;
	}




	g_keyMax = sizeof(g_anime) / sizeof(KEY);

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_enemy.part[0].partFile = (char *)BODY_ENEMY;//親は一番先にしなければならない
	g_enemy.part[1].partFile = (char *)HEAD_ENEMY;//(const char *)から(char *)に変換
	g_enemy.part[2].partFile = (char *)HAND_ENEMY;//左手
	g_enemy.part[3].partFile = (char *)HAND_ENEMY;//右手
	g_enemy.part[4].partFile = (char *)LEG_ENEMY;//左足
	g_enemy.part[5].partFile = (char *)LEG_ENEMY;//右足

	g_enemy.part[6].partFile = (char *)ICE_BLOCK;//氷

	for (int i = 0; i < PART_MAX_ENEMY; i++)//パーツ番号
	{
		// Xファイルの読み込み
		if(FAILED(D3DXLoadMeshFromX(g_enemy.part[i].partFile,
									D3DXMESH_SYSTEMMEM,
									pDevice,
									NULL,
									&g_enemy.part[i].pMatBuff,
									NULL,
									&g_enemy.part[i].nNumMat,
									&g_enemy.part[i].pMesh)))
		{
			return E_FAIL;
		}

		switch (i)
		{
		case 0:
		{//体
			g_enemy.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);//xyz必ず同じように
			g_enemy.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_enemy.part[i].srt.pos = D3DXVECTOR3(90.0f, 22.4000f, 0.0f);//足が地面に触れるよう、15.0

			g_enemy.part[i].parent = NULL;//体の親はNULLにする
			break;
		}
		case 1:
		{//頭
			g_enemy.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_enemy.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_enemy.part[i].srt.pos = D3DXVECTOR3(0.0f, 6.5f, 0.0f);

			g_enemy.part[i].parent = &g_enemy.part[0];//体を親にする
			break;
		}
		case 2:
		{//左手
			g_enemy.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_enemy.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_enemy.part[i].srt.pos = D3DXVECTOR3(5.0f, 5.0f, 0.0f);

			g_enemy.part[i].parent = &g_enemy.part[0];//体を親にする
			break;
		}
		case 3:
		{//右手
			g_enemy.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_enemy.part[i].srt.rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
			g_enemy.part[i].srt.pos = D3DXVECTOR3(-5.0f, 5.0f, 0.0f);

			g_enemy.part[i].parent = &g_enemy.part[0];//体を親にする
			break;
		}
		case 4:
		{//左足
			g_enemy.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_enemy.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_enemy.part[i].srt.pos = D3DXVECTOR3(3.064f, -4.873f, -0.409f);

			g_enemy.part[i].parent = &g_enemy.part[0];//体を親にする
			break;
		}
		case 5:
		{//右足
			g_enemy.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_enemy.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_enemy.part[i].srt.pos = D3DXVECTOR3(-3.064f, -4.873f, -0.409f);

			g_enemy.part[i].parent = &g_enemy.part[0];//体を親にする
			break;
		}

		default:
		{
			g_enemy.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_enemy.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_enemy.part[i].srt.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			g_enemy.part[i].parent = &g_enemy.part[0];//体を親にする
			break;
		}

		}

		if (i != 6)
		{
			g_enemy.part[i].use = true;
		}
		else
		{
			g_enemy.part[i].use = false;
		}
	}

	g_enemy.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_enemy.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_enemy.fRadius = ENEMY_RADIUS;
	// 影を設定 //体を基準に
	g_enemy.nIdxShadow = SetShadow(g_enemy.part[0].srt.pos, g_enemy.fRadius * 2.0f, g_enemy.fRadius * 2.0f);


	g_enemy.holdItem = ITEMTYPE_COIN;
	g_enemy.state = NORMAL;
	g_enemy.stateTime = 0;

#if 0
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
								TEXTURE_ENEMY,		// ファイルの名前
								&g_pD3DTextureEnemy);	// 読み込むメモリー
#endif

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	for (int i = 0; i < PART_MAX_ENEMY; i++)//パーツ番号
	{
		if (g_enemy.part[i].pMesh != NULL)
		{// メッシュの開放
			g_enemy.part[i].pMesh->Release();
			g_enemy.part[i].pMesh = NULL;
		}

		if (g_enemy.part[i].pMatBuff != NULL)
		{// マテリアルの開放
			g_enemy.part[i].pMatBuff->Release();
			g_enemy.part[i].pMatBuff = NULL;
		}
	}

	if (g_pD3DTextureEnemy != NULL)
	{// テクスチャの開放
		g_pD3DTextureEnemy->Release();
		g_pD3DTextureEnemy = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_ADD))
	{//AIモードの切替　即ち、シングルモードとダブルモードの切替
		g_ai = !g_ai;
		g_left = g_right = g_up = g_down = 0;
		SetPlayMode((PLAY_MODE)!GetPlayMode());

		if (GetPlayMode() == PLAY_MODE_DOUBLE)
		{
			SetCameraMode(CAMERA_MODE_FAR);

		}
	}
#endif

	if (g_ai)
	{
		AI3();
	}
	

	{
		D3DXVECTOR3 rotCamera;
		float fDiffRotY;

		// カメラの向き取得
		rotCamera = GetRotCamera();

		g_animeState = 0;//運動状態をリセット


		if ((GetTimeOut() == 0) && (g_enemy.state != FROZEN))
		{//移動
			if (g_ai ? g_left : GetKeyboardPress(DIK_LEFT) || IsButtonPress(1, BUTTON_LEFT) || IsButtonPress(1, BUTTON_LSTICK_LEFT))
			{
				g_animeState = 1;//動く状態にする

				if (g_ai ? g_up : GetKeyboardPress(DIK_UP) || IsButtonPress(1, BUTTON_UP) || IsButtonPress(1, BUTTON_LSTICK_UP))
				{// 左前移動
					g_enemy.move.x -= sinf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_ENEMY;
					g_enemy.move.z -= cosf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_ENEMY;

					g_enemy.rotDest.y = rotCamera.y + D3DX_PI * 0.75f;
				}
				else if (g_ai ? g_down : GetKeyboardPress(DIK_DOWN) || IsButtonPress(1, BUTTON_DOWN) || IsButtonPress(1, BUTTON_LSTICK_DOWN))
				{// 左後移動
					g_enemy.move.x -= sinf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_ENEMY;
					g_enemy.move.z -= cosf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_ENEMY;

					g_enemy.rotDest.y = rotCamera.y + D3DX_PI * 0.25f;
				}
				else
				{// 左移動
					g_enemy.move.x -= sinf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_ENEMY;
					g_enemy.move.z -= cosf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_ENEMY;

					g_enemy.rotDest.y = rotCamera.y + D3DX_PI * 0.50f;
				}
			}
			else if (g_ai ? g_right : GetKeyboardPress(DIK_RIGHT) || IsButtonPress(1, BUTTON_RIGHT) || IsButtonPress(1, BUTTON_LSTICK_RIGHT))
			{
				g_animeState = 1;//動く状態にする

				if (g_ai ? g_up : GetKeyboardPress(DIK_UP) || IsButtonPress(1, BUTTON_UP) || IsButtonPress(1, BUTTON_LSTICK_UP))
				{// 右前移動
					g_enemy.move.x -= sinf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_ENEMY;
					g_enemy.move.z -= cosf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_ENEMY;

					g_enemy.rotDest.y = rotCamera.y - D3DX_PI * 0.75f;
				}
				else if (g_ai ? g_down : GetKeyboardPress(DIK_DOWN) || IsButtonPress(1, BUTTON_DOWN) || IsButtonPress(1, BUTTON_LSTICK_DOWN))
				{// 右後移動
					g_enemy.move.x -= sinf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_ENEMY;
					g_enemy.move.z -= cosf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_ENEMY;

					g_enemy.rotDest.y = rotCamera.y - D3DX_PI * 0.25f;
				}
				else
				{// 右移動
					g_enemy.move.x -= sinf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_ENEMY;
					g_enemy.move.z -= cosf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_ENEMY;

					g_enemy.rotDest.y = rotCamera.y - D3DX_PI * 0.50f;
				}
			}
			else if (g_ai ? g_up : GetKeyboardPress(DIK_UP) || IsButtonPress(1, BUTTON_UP) || IsButtonPress(1, BUTTON_LSTICK_UP))
			{
				g_animeState = 1;//動く状態にする

				// 前移動
				g_enemy.move.x -= sinf(D3DX_PI + rotCamera.y) * VALUE_MOVE_ENEMY;
				g_enemy.move.z -= cosf(D3DX_PI + rotCamera.y) * VALUE_MOVE_ENEMY;

				g_enemy.rotDest.y = D3DX_PI + rotCamera.y;
			}
			else if (g_ai ? g_down : GetKeyboardPress(DIK_DOWN) || IsButtonPress(1, BUTTON_DOWN) || IsButtonPress(1, BUTTON_LSTICK_DOWN))
			{
				g_animeState = 1;//動く状態にする

				// 後移動
				g_enemy.move.x -= sinf(rotCamera.y) * VALUE_MOVE_ENEMY;
				g_enemy.move.z -= cosf(rotCamera.y) * VALUE_MOVE_ENEMY;

				g_enemy.rotDest.y = rotCamera.y;
			}

		}

		AnimeWalk();

		// 目的の角度までの差分
		fDiffRotY = g_enemy.rotDest.y - g_enemy.part[0].srt.rot.y;//体を基準に
		if (fDiffRotY > D3DX_PI)
		{
			fDiffRotY -= D3DX_PI * 2.0f;
		}
		if (fDiffRotY < -D3DX_PI)
		{
			fDiffRotY += D3DX_PI * 2.0f;
		}

		// 目的の角度まで慣性をかける　段々目的の角度に変化する
		g_enemy.part[0].srt.rot.y += fDiffRotY * RATE_ROTATE_ENEMY;//体に反映
		if (g_enemy.part[0].srt.rot.y > D3DX_PI)
		{
			g_enemy.part[0].srt.rot.y -= D3DX_PI * 2.0f;
		}
		if (g_enemy.part[0].srt.rot.y < -D3DX_PI)
		{
			g_enemy.part[0].srt.rot.y += D3DX_PI * 2.0f;
		}

		/// 位置移動を反映
		g_enemy.part[0].srt.pos.x += g_enemy.move.x;//体に反映
		g_enemy.part[0].srt.pos.y += g_enemy.move.y;
		g_enemy.part[0].srt.pos.z += g_enemy.move.z;

		//移動範囲　//体を基準に
		{
			if (g_enemy.part[0].srt.pos.x < -630.0f)
			{
				g_enemy.part[0].srt.pos.x = -630.0f;
			}
			if (g_enemy.part[0].srt.pos.x > 630.0f)
			{
				g_enemy.part[0].srt.pos.x = 630.0f;
			}
			if (g_enemy.part[0].srt.pos.y < 10.0f)
			{
				g_enemy.part[0].srt.pos.y = 10.0f;
			}
			if (g_enemy.part[0].srt.pos.y > 150.0f)
			{
				g_enemy.part[0].srt.pos.y = 150.0f;
			}
			if (g_enemy.part[0].srt.pos.z > 630.0f)
			{
				g_enemy.part[0].srt.pos.z = 630.0f;
			}
			if (g_enemy.part[0].srt.pos.z < -630.0f)
			{
				g_enemy.part[0].srt.pos.z = -630.0f;
			}
		}

		// 移動量に慣性をかける　運動エネルギーを一部損して保存する、次のフレームに使う
		//損の部分イコール次のフレームに獲得の運動エネルギーの場合、速度が最大(6.05f)になって、等速直線運動になる
		g_enemy.move.x += (0.0f - g_enemy.move.x) * RATE_MOVE_ENEMY;//即ち、g_enemy.move.x = g_enemy.move.x * (1 - RATE_MOVE_ENEMY;)
		g_enemy.move.y += (0.0f - g_enemy.move.y) * RATE_MOVE_ENEMY;
		g_enemy.move.z += (0.0f - g_enemy.move.z) * RATE_MOVE_ENEMY;

	}

// 弾発射
#ifdef _DEBUG
	if (0)
	{
		if ((GetTimeOut() == 0) && (g_enemy.state != FROZEN))
		{
			if (GetKeyboardTrigger(DIK_NUMPAD1))
			{
				D3DXVECTOR3 pos;
				D3DXVECTOR3 move;

				//体を基準に
				pos.x = g_enemy.part[0].srt.pos.x - sinf(g_enemy.part[0].srt.rot.y) * g_enemy.fRadius;//飛行機頭部の辺りに設定
				pos.y = g_enemy.part[0].srt.pos.y;
				pos.z = g_enemy.part[0].srt.pos.z - cosf(g_enemy.part[0].srt.rot.y) * g_enemy.fRadius;

				//回転角度がプラスの時、時計回り
				//sinf、cosfの符号がちょうど移動量の符号と相反する、だから-sinf、-cosf
				move.x = -sinf(g_enemy.part[0].srt.rot.y) * VALUE_MOVE_BULLET_ENEMY;//体を基準に
				move.y = 0.0f;
				move.z = -cosf(g_enemy.part[0].srt.rot.y) * VALUE_MOVE_BULLET_ENEMY;

				SetBullet(pos, move, 4.0f, 4.0f, 60 * 4);

				// SE再生
				//PlaySound(SOUND_LABEL_SE_SHOT);
			}
		}
	}
#endif

	// 影の位置設定
	{//体を基準に
		SetPositionShadow(g_enemy.nIdxShadow, D3DXVECTOR3(g_enemy.part[0].srt.pos.x, 0.1f, g_enemy.part[0].srt.pos.z));
		//高さにより、影のサイズが変化する
		float fSizeX = 20.0f + (g_enemy.part[0].srt.pos.y - 10.0f) * 0.05f;
		if(fSizeX < 20.0f)
		{
			fSizeX = 20.0f;
		}
		float fSizeY = 20.0f + (g_enemy.part[0].srt.pos.y - 10.0f) * 0.05f;
		if(fSizeY < 20.0f)
		{
			fSizeY = 20.0f;
		}

		SetVertexShadow(g_enemy.nIdxShadow, fSizeX, fSizeY);
		//高さにより、影の透明度が変化する
		float colA = (200.0f - (g_enemy.part[0].srt.pos.y - 10.0f)) / 400.0f;
		if(colA < 0.0f)
		{
			colA = 0.0f;
		}
		SetColorShadow(g_enemy.nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));
	}

	//移動距離が1より大きい場合、ジェットの煙ある
	if((g_enemy.move.x * g_enemy.move.x
	+ g_enemy.move.y * g_enemy.move.y
	+ g_enemy.move.z * g_enemy.move.z) > 1.0f)
	{
		D3DXVECTOR3 pos;
		//体を基準に
		pos.x = g_enemy.part[0].srt.pos.x + sinf(g_enemy.part[0].srt.rot.y) * g_enemy.fRadius;//飛行機尾部の辺りに設定
		pos.y = g_enemy.part[0].srt.pos.y + 2.0f;
		pos.z = g_enemy.part[0].srt.pos.z + cosf(g_enemy.part[0].srt.rot.y) * g_enemy.fRadius;

		// エフェクトの設定
		SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							D3DXCOLOR(0.85f, 0.05f, 0.65f, 0.50f), 14.0f, 14.0f, 20);//紫
		SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							D3DXCOLOR(0.65f, 0.85f, 0.05f, 0.30f), 10.0f, 10.0f, 20);//黄
		SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							D3DXCOLOR(0.45f, 0.45f, 0.05f, 0.15f), 5.0f, 5.0f, 20);//黄
	}

	// アイテムとの当たり判定
	{
		ITEM *pItem;

		// アイテムを取得
		pItem = GetItem();
		for(int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
		{
			if(pItem->bUse == true)
			{
				float fLength;

				//バウンディングサークル BC //体を基準に
				fLength = (g_enemy.part[0].srt.pos.x - pItem->pos.x) * (g_enemy.part[0].srt.pos.x - pItem->pos.x)
							+ (g_enemy.part[0].srt.pos.y - pItem->pos.y) * (g_enemy.part[0].srt.pos.y - pItem->pos.y)
							+ (g_enemy.part[0].srt.pos.z - pItem->pos.z) * (g_enemy.part[0].srt.pos.z - pItem->pos.z);
				if(fLength < (g_enemy.fRadius + pItem->fRadius) * (g_enemy.fRadius + pItem->fRadius))
				{
					if (g_enemy.holdItem && (pItem->nType != ITEMTYPE_COIN))
					{//功能アイテム持っている場合、ほかの功能アイテムには行かない

					}
					else
					{
						if (pItem->nType == ITEMTYPE_ICEBLOCK)
						{
							g_enemy.holdItem = ITEMTYPE_ICEBLOCK;

						}
						else if (pItem->nType == ITEMTYPE_COIN)
						{
							// スコア加算
							ChangeScore(100);

							// SE再生
							//PlaySound(SOUND_LABEL_SE_COIN);
						}

						// アイテム消去
						DeleteItem(nCntItem);
					}
				}
			}
		}
	}


	if ((GetTimeOut() == 0) && (g_enemy.state != FROZEN))
	{//凍結アイテムを使う
		if (g_ai)
		{
			if ((g_enemy.holdItem == ITEMTYPE_ICEBLOCK))
			{//AIは凍結アイテムを拾ったら、直ぐ使う				
				Freeze(OBJECT_PLAYER);

			}
		}
		else 
		{
			if (GetKeyboardTrigger(DIK_NUMPAD1) || IsButtonTrigger(1, BUTTON_CIRCLE))
			{
				Freeze(OBJECT_PLAYER);
			}
		}	
	}

	//凍結状態
	if (g_enemy.state == FROZEN)
	{
		if (g_enemy.stateTime == 0)
		{
			g_enemy.state = NORMAL;
			g_enemy.part[6].use = false;
		}
		else
		{
			g_enemy.stateTime--;
			g_enemy.part[6].use = true;

		}
	}

	//PrintDebugProc("エネミー////////////////////\n");
	//PrintDebugProc("コントロールのパーツ番号：%d \n", g_conId);

	//PrintDebugProc("[S：(%f : %f : %f)]\n", g_enemy.part[g_conId].srt.scl.x, 
	//										g_enemy.part[g_conId].srt.scl.y, 
	//										g_enemy.part[g_conId].srt.scl.z);

	//PrintDebugProc("[R：(%f : %f : %f)]\n", g_enemy.part[g_conId].srt.rot.x, 
	//										g_enemy.part[g_conId].srt.rot.y, 
	//										g_enemy.part[g_conId].srt.rot.z);

	//PrintDebugProc("[T：(%f : %f : %f)]\n", g_enemy.part[g_conId].srt.pos.x, 
	//										g_enemy.part[g_conId].srt.pos.y, 
	//										g_enemy.part[g_conId].srt.pos.z);

	//PrintDebugProc("目的向き：%f \n", g_enemy.rotDest.y);

	

	//PrintDebugProc("up ：%d \n", g_up);
	//PrintDebugProc("down ：%d \n", g_down);
	//PrintDebugProc("left ：%d \n", g_left);
	//PrintDebugProc("right ：%d \n", g_right);
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;
	D3DXMATERIAL *pD3DXMat;

	D3DMATERIAL9 matDef;
	pDevice->GetMaterial(&matDef);// デフォルトのマテリアルを取得

	for (int i = 0; i < PART_MAX_ENEMY; i++)//パーツ番号
	{
		if (g_enemy.part[i].use)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&mtxWorld);

			// スケールを反映
			D3DXMatrixScaling(&mtxScl, g_enemy.part[i].srt.scl.x,
				g_enemy.part[i].srt.scl.y,
				g_enemy.part[i].srt.scl.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_enemy.part[i].srt.rot.y,
				g_enemy.part[i].srt.rot.x,
				g_enemy.part[i].srt.rot.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, g_enemy.part[i].srt.pos.x,
				g_enemy.part[i].srt.pos.y,
				g_enemy.part[i].srt.pos.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

			//親が存在する場合は親のワールドマトリクスを合成
			if (g_enemy.part[i].parent)
			{
				D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &g_enemy.part[i].parent->mtxWorld);
			}

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

			// マテリアル情報に対するポインタを取得
			pD3DXMat = (D3DXMATERIAL*)g_enemy.part[i].pMatBuff->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_enemy.part[i].nNumMat; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, g_pD3DTextureEnemy);

				// 描画
				g_enemy.part[i].pMesh->DrawSubset(nCntMat);
			}
			g_enemy.part[i].mtxWorld = mtxWorld;//ワールドマトリクスを保存
		}
	}

	pDevice->SetMaterial(&matDef);// マテリアルをデフォルトに戻す
}

//=============================================================================
// エネミーを取得
//=============================================================================
ENEMY *GetEnemy(void)
{
	return &g_enemy;
}

//=============================================================================
// 位置取得
//=============================================================================
D3DXVECTOR3 GetPositionEnemy(void)
{
	return g_enemy.part[0].srt.pos;//体を基準に
}

//=============================================================================
// 向き取得
//=============================================================================
D3DXVECTOR3 GetRotationEnemy(void)
{
	return g_enemy.part[0].srt.rot;//体を基準に
}

//=============================================================================
// 目的の向き取得
//=============================================================================
D3DXVECTOR3 GetRotationDestEnemy(void)
{
	return g_enemy.rotDest;
}

//=============================================================================
// 移動量取得
//=============================================================================
D3DXVECTOR3 GetMoveEnemy(void)
{
	return g_enemy.move;
}


void AnimeWalk()
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

		if (g_enemy.state != FROZEN)
		{
			g_cancelTime += dt;//0番キーフレームのtimeを使う
		}

		if (g_cancelTime > 1.0f)//最大時間を超えたら
		{
			g_cancelTime = 1.0f;//最大最大時間にする
		}

		//接続の補間は　[i] * 1.0です、[i + 1] * 0.0ではない
		for (int j = 0; j < 6; j++)//パーツ番号
		{//最初状態に戻る
			// Scale
			g_enemy.part[j].srt.scl.x = g_enemy.part[j].srt.scl.x +		
				(g_anime[0].key[j].scl.x - g_enemy.part[j].srt.scl.x)	
				* g_cancelTime;											

			g_enemy.part[j].srt.scl.y =g_enemy.part[j].srt.scl.y +		
				(g_anime[0].key[j].scl.y -g_enemy.part[j].srt.scl.y)	
				* g_cancelTime;											

			g_enemy.part[j].srt.scl.z =g_enemy.part[j].srt.scl.z +		
				(g_anime[0].key[j].scl.z -g_enemy.part[j].srt.scl.z)	
				* g_cancelTime;											

			// Rotation
			g_enemy.part[j].srt.rot.x =g_enemy.part[j].srt.rot.x +		
				(g_anime[0].key[j].rot.x -g_enemy.part[j].srt.rot.x)	
				* g_cancelTime;											

			//g_enemy.part[j].srt.rot.y =g_enemy.part[j].srt.rot.y +	
			//	(g_anime[0].key[j].rot.y -g_enemy.part[j].srt.rot.y)	
			//	* g_cancelTime;											

			g_enemy.part[j].srt.rot.z =g_enemy.part[j].srt.rot.z +		
				(g_anime[0].key[j].rot.z -g_enemy.part[j].srt.rot.z)	
				* g_cancelTime;											

			// Position
			//g_enemy.part[j].srt.pos.x =g_enemy.part[j].srt.pos.x +	
			//	(g_anime[0].key[j].pos.x -g_enemy.part[j].srt.pos.x)	
			//	* g_cancelTime;											

			//g_enemy.part[j].srt.pos.y =g_enemy.part[j].srt.pos.y +	
			//	(g_anime[0].key[j].pos.y -g_enemy.part[j].srt.pos.y)	
			//	* g_cancelTime;											

			//g_enemy.part[j].srt.pos.z =g_enemy.part[j].srt.pos.z +	
			//	(g_anime[0].key[j].pos.z -g_enemy.part[j].srt.pos.z)	
			//	* g_cancelTime;											
		}

	}
	else
	{
		g_cancelTime = 0.0f;	//リセット

		//接続の補間は　[i] * 1.0です、[i + 1] * 0.0ではない
		for (int j = 0; j < 6; j++)//パーツ番号
		{
			// Scale
			g_enemy.part[j].srt.scl.x = g_anime[i].key[j].scl.x +				// 前のキーフレーム位置
				(g_anime[i + 1].key[j].scl.x - g_anime[i].key[j].scl.x)			// 前のキーフレームと次のキーフレームの差分
				* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

			g_enemy.part[j].srt.scl.y = g_anime[i].key[j].scl.y +				// 前のキーフレーム位置
				(g_anime[i + 1].key[j].scl.y - g_anime[i].key[j].scl.y)			// 前のキーフレームと次のキーフレームの差分
				* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

			g_enemy.part[j].srt.scl.z = g_anime[i].key[j].scl.z +				// 前のキーフレーム位置
				(g_anime[i + 1].key[j].scl.z - g_anime[i].key[j].scl.z)			// 前のキーフレームと次のキーフレームの差分
				* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

			// Rotation
			g_enemy.part[j].srt.rot.x = g_anime[i].key[j].rot.x +				// 前のキーフレーム位置
				(g_anime[i + 1].key[j].rot.x - g_anime[i].key[j].rot.x)			// 前のキーフレームと次のキーフレームの差分
				* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

			//g_enemy.part[j].srt.rot.y = g_anime[i].key[j].rot.y +				// 前のキーフレーム位置
			//	(g_anime[i + 1].key[j].rot.y - g_anime[i].key[j].rot.y)			// 前のキーフレームと次のキーフレームの差分
			//	* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

			g_enemy.part[j].srt.rot.z = g_anime[i].key[j].rot.z +				// 前のキーフレーム位置
				(g_anime[i + 1].key[j].rot.z - g_anime[i].key[j].rot.z)			// 前のキーフレームと次のキーフレームの差分
				* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

			// Position
			//g_enemy.part[j].srt.pos.x = g_anime[i].key[j].pos.x +				// 前のキーフレーム位置
			//	(g_anime[i + 1].key[j].pos.x - g_anime[i].key[j].pos.x)			// 前のキーフレームと次のキーフレームの差分
			//	* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

			//g_enemy.part[j].srt.pos.y = g_anime[i].key[j].pos.y +				// 前のキーフレーム位置
			//	(g_anime[i + 1].key[j].pos.y - g_anime[i].key[j].pos.y)			// 前のキーフレームと次のキーフレームの差分
			//	* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

			//g_enemy.part[j].srt.pos.z = g_anime[i].key[j].pos.z +				// 前のキーフレーム位置
			//	(g_anime[i + 1].key[j].pos.z - g_anime[i].key[j].pos.z)			// 前のキーフレームと次のキーフレームの差分
			//	* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける
		}

	}

}


//左右上下を等確率で
void AI()
{
	int random;

	//左右を判断
	random = rand() % 3;

	if (random == 0)
	{
		g_left = 1;
		g_right = 0;
	}
	else if (random == 1)
	{
		g_left = 0;
		g_right = 1;
	}
	else if (random == 2)
	{
		g_left = 0;
		g_right = 0;
	}

	//上下を判断
	random = rand() % 3;

	if (random == 0)
	{
		g_up = 1;
		g_down = 0;
	}
	else if (random == 1)
	{
		g_up = 0;
		g_down = 1;
	}
	else if (random == 2)
	{
		g_up = 0;
		g_down = 0;
	}
}

//一番近いコインに向かう
int AI2()
{
	ITEM *item = GetItem();

	D3DXVECTOR3 vec;//作業用
	float disBuff = 0;//アイテムとの距離
	float dis = 9999999;//一番近い距離
	int result = -1;//距離一番近いコインの番号

	//距離一番近いコインの番号を取得
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, item++)
	{
		if ((item->bUse)&&(item->nType == ITEMTYPE_COIN))
		{
			vec = item->pos - g_enemy.part[0].srt.pos;
			disBuff = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);

			if (disBuff < dis)
			{
				dis = disBuff;
				result = nCntItem;
			}			
		}
	}

	if (result != -1)
	{
		item = GetItem();//リセット
		vec = (item + result)->pos - g_enemy.part[0].srt.pos;

		if (vec.x < 0)
		{
			g_left = 1;
			g_right = 0;
		}
		else if (vec.x == 0)
		{
			g_left = 0;
			g_right = 0;
		}
		else if (vec.x > 0)
		{
			g_left = 0;
			g_right = 1;
		}

		if (vec.z < 0)
		{
			g_up = 0;
			g_down = 1;
		}
		else if (vec.z == 0)
		{
			g_up = 0;
			g_down = 0;
		}
		else if (vec.z > 0)
		{
			g_up = 1;
			g_down = 0;
		}

	}
	else
	{
		g_left = g_right = g_up = g_down = 0;//止まる
	}

	PrintDebugProc("距離一番近いコインの番号 ：%d \n\n", result);

	return result;
	
}


//一番近いコインに向かう上、アイテムを拾いに行ける
int AI3()
{
	ITEM *item = GetItem();

	D3DXVECTOR3 vec;//作業用
	float disBuff = 0;//アイテムとの距離
	float dis = 9999999;//一番近い距離
	int result = -1;//距離一番近いコインの番号

	//距離一番近いコインの番号を取得
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, item++)
	{
		if ((item->bUse))
		{
			vec = item->pos - g_enemy.part[0].srt.pos;
			disBuff = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);

			if (disBuff < dis)
			{
				if ((item->nType == ITEMTYPE_ICEBLOCK)&&(g_enemy.holdItem == ITEMTYPE_ICEBLOCK))
				{

				}
				else
				{
					dis = disBuff;
					result = nCntItem;
				}
			}
		}
	}

	if (result != -1)
	{
		item = GetItem();//リセット
		vec = (item + result)->pos - g_enemy.part[0].srt.pos;

		if (vec.x < 0)
		{
			g_left = 1;
			g_right = 0;
		}
		else if (vec.x == 0)
		{
			g_left = 0;
			g_right = 0;
		}
		else if (vec.x > 0)
		{
			g_left = 0;
			g_right = 1;
		}

		if (vec.z < 0)
		{
			g_up = 0;
			g_down = 1;
		}
		else if (vec.z == 0)
		{
			g_up = 0;
			g_down = 0;
		}
		else if (vec.z > 0)
		{
			g_up = 1;
			g_down = 0;
		}

	}
	else
	{
		g_left = g_right = g_up = g_down = 0;//止まる
	}


	PrintDebugProc("距離一番近いコインの番号 ：%d \n\n", result);

	return result;

}