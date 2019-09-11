//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 麦英泳
//
//=============================================================================
#include "player.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "bullet.h"
#include "effect.h"
#include "item.h"
#include "score.h"
#include "sound.h"
#include "debugproc.h"
#include "timer.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	BODY_PLAYER		"data/MODEL/bearBody.x"	// 読み込むモデル名
#define	HEAD_PLAYER		"data/MODEL/bearHead.x"	// 読み込むモデル名
#define	HAND_PLAYER		"data/MODEL/bearHand.x"	// 読み込むモデル名
#define	LEG_PLAYER		"data/MODEL/bearLeg.x"	// 読み込むモデル名
#define	ICE_BLOCK		"data/MODEL/iceBlock.x"		// 読み込むモデル名



#define	PLAYER_RADIUS		(15.0f)						// 半径

#define	VALUE_MOVE_PLAYER	(0.195f)					// 移動速度
#define	RATE_MOVE_PLAYER	(0.025f)					// 移動慣性係数

#define	VALUE_ROTATE_PLAYER	(D3DX_PI * 0.025f)			// 回転速度 4.5度
#define	RATE_ROTATE_PLAYER	(0.10f)						// 回転慣性係数

#define	VALUE_MOVE_BULLET	(7.5f)						// 弾の移動速度

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void WriteAnime();
void AnimeWalk();


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTexturePlayer;		// テクスチャ読み込み場所
PLAYER				g_player;					// プレイヤーワーク

int g_mode = MODE_TITLE;//編輯モードかどうか
int g_conId = 0;//コントロールID

float g_motionTime = 0.0f;	// アニメーション全体時間
int g_keyMax;				//キーフレームの数
bool g_animeState = 0;		//動くかどうか

float g_cancelTime = 0.0f;// 最初状態に戻る時間


KEY g_anime[] =
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
HRESULT InitPlayer(void)
{
	

	g_keyMax = sizeof(g_anime) / sizeof(KEY);

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_player.part[0].partFile = (char *)BODY_PLAYER;//親は一番先にしなければならない
	g_player.part[1].partFile = (char *)HEAD_PLAYER;//(const char *)から(char *)に変換
	g_player.part[2].partFile = (char *)HAND_PLAYER;//左手
	g_player.part[3].partFile = (char *)HAND_PLAYER;//右手
	g_player.part[4].partFile = (char *)LEG_PLAYER;//左足
	g_player.part[5].partFile = (char *)LEG_PLAYER;//右足

	g_player.part[6].partFile = (char *)ICE_BLOCK;//氷

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
			return E_FAIL;
		}

		switch (i)
		{//初期値 pos.yは足が地面に触れるような数値
		case 0:
		{//体
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);//xyz必ず同じように
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(0.0f, 22.4f, 0.0f);//足が地面に触れるよう、15.0

			g_player.part[i].parent = NULL;//体の親はNULLにする
			break;
		}
		case 1:
		{//頭
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(0.0f, 6.5f, 0.0f);

			g_player.part[i].parent = &g_player.part[0];//体を親にする
			break;
		}
		case 2:
		{//左手
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(5.0f, 5.0f, 0.0f);

			g_player.part[i].parent = &g_player.part[0];//体を親にする
			break;
		}
		case 3:
		{//右手
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(-5.0f, 5.0f, 0.0f);

			g_player.part[i].parent = &g_player.part[0];//体を親にする
			break;
		}
		case 4:
		{//左足
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(3.064f, -4.873f, -0.409f);

			g_player.part[i].parent = &g_player.part[0];//体を親にする
			break;
		}
		case 5:
		{//右足
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(-3.064f, -4.873f, -0.409f);

			g_player.part[i].parent = &g_player.part[0];//体を親にする
			break;
		}

		default:
		{
			g_player.part[i].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_player.part[i].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_player.part[i].srt.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			g_player.part[i].parent = &g_player.part[0];//体を親にする
			break;
		}

		}

		if (i != 6)
		{
			g_player.part[i].use = true;
		}
		else
		{
			g_player.part[i].use = false;
		}
	}

	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.fRadius = PLAYER_RADIUS;
	// 影を設定 //体を基準に
	g_player.nIdxShadow = SetShadow(g_player.part[0].srt.pos, g_player.fRadius * 2.0f, g_player.fRadius * 2.0f);


	g_player.holdItem = ITEMTYPE_COIN;
	g_player.state = NORMAL;
	g_player.stateTime = 0;

#if 0
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
								TEXTURE_PLAYER,		// ファイルの名前
								&g_pD3DTexturePlayer);	// 読み込むメモリー
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
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
#ifdef _DEBUG
	//モードの入力
	//if (GetKeyboardPress(DIK_1))
	//{
	//	g_mode = MODE_PLAY;
	//}
	if (GetKeyboardPress(DIK_2))
	{
		g_mode = MODE_EDIT;
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
#endif





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
				g_player.part[j].srt.scl.x = g_anime[i].key[j].scl.x +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].scl.x - g_anime[i].key[j].scl.x)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				g_player.part[j].srt.scl.y = g_anime[i].key[j].scl.y +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].scl.y - g_anime[i].key[j].scl.y)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				g_player.part[j].srt.scl.z = g_anime[i].key[j].scl.z +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].scl.z - g_anime[i].key[j].scl.z)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

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
				g_player.part[j].srt.pos.x = g_anime[i].key[j].pos.x +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].pos.x - g_anime[i].key[j].pos.x)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				g_player.part[j].srt.pos.y = g_anime[i].key[j].pos.y +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].pos.y - g_anime[i].key[j].pos.y)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

				g_player.part[j].srt.pos.z = g_anime[i].key[j].pos.z +				// 前のキーフレーム位置
					(g_anime[i + 1].key[j].pos.z - g_anime[i].key[j].pos.z)			// 前のキーフレームと次のキーフレームの差分
					* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける
			}
		}

		break;
	}

	case MODE_EDIT:
	{
		D3DXVECTOR3 rotCamera;
		float fDiffRotY;

		// カメラの向き取得
		rotCamera = GetRotCamera();

		g_animeState = 0;//運動状態をリセット

		if((GetTimeOut() == 0) && (g_player.state != FROZEN))
		{//移動
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

#ifdef _DEBUG
			if (GetKeyboardPress(DIK_T))
			{// 上昇
				g_player.move.y += VALUE_MOVE_PLAYER;
			}
			if (GetKeyboardPress(DIK_Y))
			{// 下降
				g_player.move.y -= VALUE_MOVE_PLAYER;
			}

			if (GetKeyboardPress(DIK_U))
			{// 左回転
				g_player.rotDest.y -= VALUE_ROTATE_PLAYER;
				if (g_player.rotDest.y < -D3DX_PI)
				{
					g_player.rotDest.y += D3DX_PI * 2.0f;
				}
			}
			if (GetKeyboardPress(DIK_I))
			{// 右回転
				g_player.rotDest.y += VALUE_ROTATE_PLAYER;
				if (g_player.rotDest.y > D3DX_PI)
				{
					g_player.rotDest.y -= D3DX_PI * 2.0f;
				}
			}
#endif
		}

#ifdef _DEBUG
		//パーツの変形
		//x軸回転
		if (GetKeyboardPress(DIK_Z))
			{
				g_player.part[g_conId].srt.rot.x += VALUE_ROTATE_PLAYER;
				if (g_player.part[g_conId].srt.rot.x > D3DX_PI)
				{
					g_player.part[g_conId].srt.rot.x -= D3DX_PI * 2.0f;
				}

			}
		else if (GetKeyboardPress(DIK_X))
			{
				g_player.part[g_conId].srt.rot.x -= VALUE_ROTATE_PLAYER;
				if (g_player.part[g_conId].srt.rot.x < -D3DX_PI)
				{
					g_player.part[g_conId].srt.rot.x += D3DX_PI * 2.0f;
				}
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
#endif

		AnimeWalk();


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

// 弾発射
#ifdef _DEBUG
	if (0)
	{
		if ((GetTimeOut() == 0) && (g_player.state != FROZEN))
		{
			if (GetKeyboardTrigger(DIK_SPACE))
			{
				D3DXVECTOR3 pos;
				D3DXVECTOR3 move;

				//体を基準に
				pos.x = g_player.part[0].srt.pos.x - sinf(g_player.part[0].srt.rot.y) * g_player.fRadius;//飛行機頭部の辺りに設定
				pos.y = g_player.part[0].srt.pos.y;
				pos.z = g_player.part[0].srt.pos.z - cosf(g_player.part[0].srt.rot.y) * g_player.fRadius;

				//回転角度がプラスの時、時計回り
				//sinf、cosfの符号がちょうど移動量の符号と相反する、だから-sinf、-cosf
				move.x = -sinf(g_player.part[0].srt.rot.y) * VALUE_MOVE_BULLET;//体を基準に
				move.y = 0.0f;
				move.z = -cosf(g_player.part[0].srt.rot.y) * VALUE_MOVE_BULLET;

				SetBullet(pos, move, 4.0f, 4.0f, 60 * 4);

				// SE再生
				PlaySound(SOUND_LABEL_SE_SHOT);
			}
		}
	}
#endif

	// 影の位置設定
	{//体を基準に
		SetPositionShadow(g_player.nIdxShadow, D3DXVECTOR3(g_player.part[0].srt.pos.x, 0.1f, g_player.part[0].srt.pos.z));
		//高さにより、影のサイズが変化する
		float fSizeX = 20.0f + (g_player.part[0].srt.pos.y - 10.0f) * 0.05f;
		if(fSizeX < 20.0f)
		{
			fSizeX = 20.0f;
		}
		float fSizeY = 20.0f + (g_player.part[0].srt.pos.y - 10.0f) * 0.05f;
		if(fSizeY < 20.0f)
		{
			fSizeY = 20.0f;
		}

		SetVertexShadow(g_player.nIdxShadow, fSizeX, fSizeY);
		//高さにより、影の透明度が変化する
		float colA = (200.0f - (g_player.part[0].srt.pos.y - 10.0f)) / 400.0f;
		if(colA < 0.0f)
		{
			colA = 0.0f;
		}
		SetColorShadow(g_player.nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));
	}

	//移動距離が1より大きい場合、ジェットの煙ある
	if((g_player.move.x * g_player.move.x
	+ g_player.move.y * g_player.move.y
	+ g_player.move.z * g_player.move.z) > 1.0f)
	{
		D3DXVECTOR3 pos;
		//体を基準に
		pos.x = g_player.part[0].srt.pos.x + sinf(g_player.part[0].srt.rot.y) * g_player.fRadius;//飛行機尾部の辺りに設定
		pos.y = g_player.part[0].srt.pos.y + 2.0f;
		pos.z = g_player.part[0].srt.pos.z + cosf(g_player.part[0].srt.rot.y) * g_player.fRadius;

		// エフェクトの設定
		SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							D3DXCOLOR(0.85f, 0.15f, 0.0f, 0.50f), 14.0f, 14.0f, 20);//オレンジ
		SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							D3DXCOLOR(0.15f, 0.75f, 0.0f, 0.30f), 10.0f, 10.0f, 20);//緑
		SetEffect(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							D3DXCOLOR(0.0f, 0.10f, 0.0f, 0.15f), 5.0f, 5.0f, 20);//緑
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
				fLength = (g_player.part[0].srt.pos.x - pItem->pos.x) * (g_player.part[0].srt.pos.x - pItem->pos.x)
							+ (g_player.part[0].srt.pos.y - pItem->pos.y) * (g_player.part[0].srt.pos.y - pItem->pos.y)
							+ (g_player.part[0].srt.pos.z - pItem->pos.z) * (g_player.part[0].srt.pos.z - pItem->pos.z);
				if(fLength < (g_player.fRadius + pItem->fRadius) * (g_player.fRadius + pItem->fRadius))
				{
					if (g_player.holdItem && (pItem->nType != ITEMTYPE_COIN))
					{//アイテム持っている場合、ほかのアイテムを拾えない

					}
					else
					{
						if (pItem->nType == ITEMTYPE_ICEBLOCK)
						{
							g_player.holdItem = ITEMTYPE_ICEBLOCK;
						}
						else if(pItem->nType == ITEMTYPE_COIN)
						{
							// スコア加算
							ChangeScore2(100);

							// SE再生
							PlaySound(SOUND_LABEL_SE_COIN);
						}

						// アイテム消去
						DeleteItem(nCntItem);
				
					}
				}
			}
		}
	}


	if ((GetTimeOut() == 0) && (g_player.state != FROZEN))
	{
		if (GetKeyboardTrigger(DIK_SPACE) || IsButtonTrigger(0, BUTTON_CIRCLE))
		{//凍結アイテムを使う
			Freeze(OBJECT_ENEMY);
		}
	}

	//凍結状態
	if (g_player.state == FROZEN)
	{
		if (g_player.stateTime == 0)
		{
			g_player.state = NORMAL;
			g_player.part[6].use = false;
		}
		else
		{
			g_player.stateTime--;
			g_player.part[6].use = true;

		}
	}

//運動情報を書き出す
#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_F2))
	{
		WriteAnime();
	}
#endif

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
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;
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

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.part[i].srt.rot.y,
				g_player.part[i].srt.rot.x,
				g_player.part[i].srt.rot.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, g_player.part[i].srt.pos.x,
				g_player.part[i].srt.pos.y,
				g_player.part[i].srt.pos.z);
			D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

			//親が存在する場合は親のワールドマトリクスを合成
			if (g_player.part[i].parent)
			{
				D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &g_player.part[i].parent->mtxWorld);
			}

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

			// マテリアル情報に対するポインタを取得
			pD3DXMat = (D3DXMATERIAL*)g_player.part[i].pMatBuff->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_player.part[i].nNumMat; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, g_pD3DTexturePlayer);

				// 描画
				g_player.part[i].pMesh->DrawSubset(nCntMat);
			}
			g_player.part[i].mtxWorld = mtxWorld;//ワールドマトリクスを保存
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
	fp = fopen("anime.txt", "a+");//"a+"は書き込みのモード。ファイルがないと、自動に作成
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

		if (g_player.state != FROZEN)
		{
			g_cancelTime += dt;//0番キーフレームのtimeを使う
		}

		if (g_cancelTime > 1.0f)//最大時間を超えたら
		{
			g_cancelTime = 1.0f;//最大最大時間にする
		}

		//接続の補間は　[i] * 1.0です、[i + 1] * 0.0ではない
		for (int j = 0; j < 6; j++)//パーツ番号
		{//最初のキーの状態に戻る
			// Scale
			g_player.part[j].srt.scl.x = g_player.part[j].srt.scl.x +	
				(g_anime[0].key[j].scl.x - g_player.part[j].srt.scl.x)	
				* g_cancelTime;											

			g_player.part[j].srt.scl.y = g_player.part[j].srt.scl.y +	
				(g_anime[0].key[j].scl.y - g_player.part[j].srt.scl.y)	
				* g_cancelTime;											

			g_player.part[j].srt.scl.z = g_player.part[j].srt.scl.z +	
				(g_anime[0].key[j].scl.z - g_player.part[j].srt.scl.z)	
				* g_cancelTime;											

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
		for (int j = 0; j < 6; j++)//パーツ番号
		{
			// Scale
			g_player.part[j].srt.scl.x = g_anime[i].key[j].scl.x +				// 前のキーフレーム位置
				(g_anime[i + 1].key[j].scl.x - g_anime[i].key[j].scl.x)			// 前のキーフレームと次のキーフレームの差分
				* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

			g_player.part[j].srt.scl.y = g_anime[i].key[j].scl.y +				// 前のキーフレーム位置
				(g_anime[i + 1].key[j].scl.y - g_anime[i].key[j].scl.y)			// 前のキーフレームと次のキーフレームの差分
				* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

			g_player.part[j].srt.scl.z = g_anime[i].key[j].scl.z +				// 前のキーフレーム位置
				(g_anime[i + 1].key[j].scl.z - g_anime[i].key[j].scl.z)			// 前のキーフレームと次のキーフレームの差分
				* (g_motionTime - i);											// に　全体アニメ時間の小数点以下の割合をかける

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

}




