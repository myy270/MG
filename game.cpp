//=============================================================================
//
// ゲーム画面処理 [game.cpp]
// Author : 麦英泳
//
//=============================================================================
#include "game.h"
#include "light.h"
#include "camera.h"
#include "meshfield.h"
#include "meshwall.h"
#include "player.h"
#include "enemy.h"
#include "shadow.h"
#include "bullet.h"
#include "effect.h"
#include "explosion.h"
#include "life.h"
#include "timer.h"
//#include "score.h"
#include "item.h"
//#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TIMESET			(999)	//タイマーの時間






//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGame(void)
{
	// ライトの初期化
	InitLight();

	// カメラの初期化
	InitCamera();

	// 地面の初期化
	InitMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 16, 16, 80.0f, 80.0f);//1280*1280

	// 壁の初期化 

	//北壁の地面
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, 640.0f), D3DXVECTOR3(D3DX_PI * 0.50f, 0.0f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 48, 16, 80.0f, 80.0f);
	//南壁の地面
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, -640.0f), D3DXVECTOR3(D3DX_PI * 0.50f, D3DX_PI, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 48, 16, 80.0f, 80.0f);
	//西壁の地面　反時計回転90度
	InitMeshWall(D3DXVECTOR3(-640.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI * 0.50f, 0.0f, D3DX_PI * 0.50f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 16, 80.0f, 80.0f);
	//東壁の地面　時計回転90度
	InitMeshWall(D3DXVECTOR3(640.0f, 0.0f, 0.0f), D3DXVECTOR3(D3DX_PI * 0.50f, D3DX_PI * 0.50f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 16, 80.0f, 80.0f);

	//北壁
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, 640.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 2, 80.0f, 80.0f);
	//南壁　時計回転180度
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, -640.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 2, 80.0f, 80.0f);
	//西壁　反時計回転90度
	InitMeshWall(D3DXVECTOR3(-640.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.50f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 2, 80.0f, 80.0f);
	//東壁　時計回転90度
	InitMeshWall(D3DXVECTOR3(640.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.50f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 2, 80.0f, 80.0f);


	//北壁の屋上
	InitMeshWall(D3DXVECTOR3(0.0f, 160.0f, 640.0f), D3DXVECTOR3(D3DX_PI * 0.50f, 0.0f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 48, 16, 80.0f, 80.0f);
	////南壁の屋上
	InitMeshWall(D3DXVECTOR3(0.0f, 160.0f, -640.0f), D3DXVECTOR3(D3DX_PI * 0.50f, D3DX_PI, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 48, 16, 80.0f, 80.0f);
	////西壁の屋上　反時計回転90度
	InitMeshWall(D3DXVECTOR3(-640.0f, 160.0f, 0.0f), D3DXVECTOR3(D3DX_PI * 0.50f, 0.0f, D3DX_PI * 0.50f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 16, 16, 80.0f, 80.0f);
	////東壁の屋上　時計回転90度
	InitMeshWall(D3DXVECTOR3(640.0f, 160.0f, 0.0f), D3DXVECTOR3(D3DX_PI * 0.50f, D3DX_PI * 0.50f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 16, 16, 80.0f, 80.0f);

	//壁(裏側用)
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, 640.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);
	InitMeshWall(D3DXVECTOR3(-640.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.50f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);
	InitMeshWall(D3DXVECTOR3(640.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.50f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);
	InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, -640.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);

	// 影の初期化
	InitShadow();

	// プレイヤーの初期化
	InitPlayer();

	InitEnemy();

	// 弾の初期化
	InitBullet();

	// 爆発の初期化
	InitExplosion();

	// エフェクトの初期化
	InitEffect();

	// ライフの初期化
	InitLife();

	// タイマーの初期化
	InitTimer();
	ResetTimer(TIMESET);

	// スコアの初期化
	//InitScore();

	// アイテムの初期化
	InitItem();
	for(int nCntCoin = 0; nCntCoin < 99; nCntCoin++)
	{
		float fPosX, fPosY, fPosZ;

		fPosX = (float)(rand() % 12000) / 10.0f - 600.0f;//-600.0f~600.0f
		//fPosY = (float)(rand() % 1400) / 10.0f + 10.0f;//10.0f~150.0f
		fPosY = 15.0f;
		fPosZ = (float)(rand() % 12000) / 10.0f - 600.0f;
		SetItem(D3DXVECTOR3(fPosX, fPosY, fPosZ),  D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_COIN, true);
	}

	// BGM再生 ちゃんとloopできるにする!　元の罠
	//PlaySound(SOUND_LABEL_BGM000, XAUDIO2_LOOP_INFINITE);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGame(void)
{
	// ライトの終了処理
	UninitLight();

	// カメラの終了処理
	UninitCamera();

	// 地面の終了処理
	UninitMeshField();

	// 壁の終了処理
	UninitMeshWall();

	// 影の終了処理
	UninitShadow();

	// プレイヤーの終了処理
	UninitPlayer();

	UninitEnemy();

	// 弾の終了処理
	UninitBullet();

	// 爆発の終了処理
	UninitExplosion();

	// エフェトの終了処理
	UninitEffect();

	// ライフの終了処理
	UninitLife();

	// タイマーの終了処理
	UninitTimer();

	// スコアの終了処理
	//UninitScore();

	// アイテムの終了処理
	UninitItem();

	// BGM停止 !!元の罠
	//StopSound(SOUND_LABEL_BGM000);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGame(void)
{
	// ライト処理の更新
	UpdateLight();

	// カメラ処理の更新
	UpdateCamera();

	// 地面処理の更新
	UpdateMeshField();

	// 壁処理の更新
	UpdateMeshWall();

	// 影処理の更新
	UpdateShadow();

	// プレイヤー処理の更新
	UpdatePlayer();

	UpdateCamera2();	//カメラがプレイヤーの最新位置に従う、プレイヤーが前後フレームにちらつきのBUGを修正

	UpdateEnemy();

	// 弾処理の更新
	UpdateBullet();

	// 爆発処理の更新
	UpdateExplosion();

	// エフェクト処理の更新
	UpdateEffect();

	// ライフ処理の更新
	UpdateLife();

	// タイマー処理の更新
	UpdateTimer();

	// スコア処理の更新
	//UpdateScore();

	// アイテム処理の更新
	UpdateItem();


}

//=============================================================================
// 描画処理 描画順注意
//=============================================================================
void DrawGame(void)
{
	// カメラの設定
	SetCamera();

	// 地面処理の描画
	DrawMeshField();

	// 影処理の描画
	//DrawShadow();

	// プレイヤー処理の描画
	DrawPlayer();

	DrawEnemy();


	//if () 
	//{
	//// アイテム処理の描画
	////DrawItem();
	//}

	// 弾処理の描画
	DrawBullet();

	// エフェクト処理の描画
	//DrawEffect();

	// 壁処理の描画
	//DrawMeshWall();

	// 爆発処理の描画
	DrawExplosion();

	// ライフ処理の描画
	//DrawLife();

	// タイマー処理の描画
	DrawTimer();

	// スコア処理の描画
	//DrawScore();
}

