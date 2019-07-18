//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 麦英泳
//
//=============================================================================
#include "camera.h"
#include "player.h"
#include "input.h"
#include "debugproc.h"
#include "enemy.h"
#include "score.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VIEW_ANGLE			(D3DXToRadian(45.0f))	// 視野角
#define	VIEW_NEAR_Z			(10.0f)					// ビュー平面のNearZ値
#define	VIEW_FAR_Z			(10000.0f)				// ビュー平面のFarZ値
#define	VALUE_MOVE_CAMERA	(2.0f)					// カメラの移動量
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)		// カメラの回転量

#define	RATE_CHASE_CAMERA_P	(0.35f)					// カメラの視点への補正係数
#define	RATE_CHASE_CAMERA_R	(0.20f)					// カメラの注視点への補正係数

#define	CHASE_HEIGHT_P_NEAR		(136.0f)				// 追跡時の視点の高さ
#define	CHASE_HEIGHT_P_FAR		(1700.0f)				// 追跡時の視点の高さ

#define	RADIUS_NEAR		(356.0f)				// 視点と注視点のxoz面の距離
#define	RADIUS_FAR		(350.0f)				// 視点と注視点のxoz面の距離


#define	CHASE_HEIGHT_R		(10.0f)					// 追跡時の注視点の高さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
D3DXVECTOR3		g_posCameraP;				// カメラの視点
D3DXVECTOR3		g_posCameraR;				// カメラの注視点
D3DXVECTOR3		g_posCameraU;				// カメラの上方向

D3DXVECTOR3		g_rotCamera;				// カメラの回転
float			g_fLengthIntervalCamera;	// カメラの視点と注視点の距離
D3DXMATRIX		g_mtxView;					// ビューマトリックス
D3DXMATRIX		g_mtxProjection;			// プロジェクションマトリックス

float g_chaseHightP;// 追跡時の視点の高さ

CAMERA_MODE g_cameraMode;

PLAY_MODE g_playMode;

bool g_cutScene;//カットシーンかどうか

//=============================================================================
// カメラの初期化
//=============================================================================
HRESULT InitCamera(void)
{
	g_cutScene = false;


	/*if (GetCursorIdx() == 0)
	{*/
		g_cameraMode = CAMERA_MODE_NEAR;//デフォルト設定
		g_playMode = PLAY_MODE_SINGLE;//デフォルト設定

	//}
	//else if (GetCursorIdx() == 1)
	//{
	//	g_cameraMode = CAMERA_MODE_FAR;//デフォルト設定
	//	g_playMode = PLAY_MODE_DOUBLE;//デフォルト設定
	//}


	if (g_cameraMode == CAMERA_MODE_NEAR)
	{
		g_chaseHightP = CHASE_HEIGHT_P_NEAR;		
	}
	else if (g_cameraMode == CAMERA_MODE_FAR)
	{
		g_chaseHightP = CHASE_HEIGHT_P_FAR;
	}

	g_posCameraP = D3DXVECTOR3(0.0f, 100.0f, - RADIUS_NEAR);
	g_posCameraR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_posCameraU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	g_rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	float vx,vz;
	vx = g_posCameraP.x - g_posCameraR.x;
	vz = g_posCameraP.z - g_posCameraR.z;
	g_fLengthIntervalCamera = sqrtf(vx * vx + vz * vz);//= g_posCameraP.z

	return S_OK;
}

//=============================================================================
// カメラの終了処理
//=============================================================================
void UninitCamera(void)
{
}

//=============================================================================
// カメラの更新処理　UpdateCamera()がUpdatePlayer()の前にある
//=============================================================================
void UpdateCamera(void)
{
	
	D3DXVECTOR3 rotPlayer;
	D3DXVECTOR3 movePlayer;


	//カメラモード変換
	{
		if ((GetKeyboardTrigger(DIK_LSHIFT) || IsButtonTrigger(0, BUTTON_CROSS)) && (g_playMode == PLAY_MODE_SINGLE))
		{//シングルモードだけ、カメラの切替可能にする

			g_cameraMode = (CAMERA_MODE)!g_cameraMode;

		}

		//{//これを消すと、カメラが自由に移動できる
		//	if (g_cameraMode == CAMERA_MODE_NEAR)
		//	{
		//		g_chaseHightP = CHASE_HEIGHT_P_NEAR;
		//		g_fLengthIntervalCamera = RADIUS_NEAR;

		//		if (g_cutScene)
		//		{//勝利時のカットシーン
		//			g_chaseHightP = 100.0f;
		//			g_fLengthIntervalCamera = 200.0f;
		//		}

		//	}
		//	else if (g_cameraMode == CAMERA_MODE_FAR)
		//	{
		//		g_chaseHightP = CHASE_HEIGHT_P_FAR;
		//		g_fLengthIntervalCamera = RADIUS_FAR;
		//	}
		//}
	}

#ifdef _DEBUG
	if (GetKeyboardPress(DIK_Q))
	{// Y軸左回転
		g_rotCamera.y -= VALUE_ROTATE_CAMERA;
		if (g_rotCamera.y > D3DX_PI)
		{
			g_rotCamera.y -= D3DX_PI * 2.0f;
		}
		if (g_rotCamera.y < -D3DX_PI)
		{
			g_rotCamera.y += D3DX_PI * 2.0f;
		}
	}

	if (GetKeyboardPress(DIK_E))
	{// Y軸右回転
		g_rotCamera.y += VALUE_ROTATE_CAMERA;
		if (g_rotCamera.y > D3DX_PI)
		{
			g_rotCamera.y -= D3DX_PI * 2.0f;
		}
		if (g_rotCamera.y < -D3DX_PI)
		{
			g_rotCamera.y += D3DX_PI * 2.0f;
		}
	}

	if (GetKeyboardPress(DIK_R))
	{//zoom
		g_fLengthIntervalCamera -= VALUE_MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_T))
	{//zoom
		g_fLengthIntervalCamera += VALUE_MOVE_CAMERA;
	}


	if (GetKeyboardPress(DIK_Y))
	{// 追跡時の視点の高さ
		g_chaseHightP -= VALUE_MOVE_CAMERA;
	}

	if (GetKeyboardPress(DIK_U))
	{// 追跡時の視点の高さ
		g_chaseHightP += VALUE_MOVE_CAMERA;
	}

#endif

	PrintDebugProc("\n");

	PrintDebugProc("chaseHightP:%f\n", g_chaseHightP);

	PrintDebugProc("\n");

	PrintDebugProc("LengthIntervalCamera:%f\n", g_fLengthIntervalCamera);

	PrintDebugProc("\n");

}


void UpdateCamera2(void)
{
	D3DXVECTOR3 posPlayer;

	// モデルの現在の位置取得
	posPlayer = GetPositionPlayer();

	if (g_cameraMode == CAMERA_MODE_NEAR)
	{
		// 視点の目的位置
		g_posCameraP.x = posPlayer.x - sinf(g_rotCamera.y) * g_fLengthIntervalCamera;
		g_posCameraP.y = posPlayer.y + g_chaseHightP;
		g_posCameraP.z = posPlayer.z - cosf(g_rotCamera.y) * g_fLengthIntervalCamera;

		// 注視点の目的位置
		g_posCameraR.x = posPlayer.x;
		g_posCameraR.y = posPlayer.y;
		g_posCameraR.z = posPlayer.z;

		if (GetWinner() == OBJECT_ENEMY)
		{
			// 視点の目的位置
			g_posCameraP.x = GetPositionEnemy().x - sinf(g_rotCamera.y) * g_fLengthIntervalCamera;
			g_posCameraP.y = GetPositionEnemy().y + g_chaseHightP;
			g_posCameraP.z = GetPositionEnemy().z - cosf(g_rotCamera.y) * g_fLengthIntervalCamera;

			// 注視点の目的位置
			g_posCameraR.x = GetPositionEnemy().x;
			g_posCameraR.y = GetPositionEnemy().y;
			g_posCameraR.z = GetPositionEnemy().z;

		}

	}
	else if (g_cameraMode == CAMERA_MODE_FAR)
	{
		// 視点の目的位置 
		g_posCameraP.x = -sinf(g_rotCamera.y) * g_fLengthIntervalCamera; //- sinf(g_rotCamera.y)の-が回転の方向を決める；
		g_posCameraP.y = g_chaseHightP;
		g_posCameraP.z = -cosf(g_rotCamera.y) * g_fLengthIntervalCamera;//- cosf(g_rotCamera.y)の-が最初カメラの向きを決める

		// 注視点の目的位置
		g_posCameraR.x = 0.0f;
		g_posCameraR.y = 0.0f;
		g_posCameraR.z = 0.0f;

	}

	PrintDebugProc("[camera pos：(%f : %f : %f)]\n", g_posCameraP.x,
		g_posCameraP.y,
		g_posCameraP.z);

	PrintDebugProc("[camera at：(%f : %f : %f)]\n", g_posCameraR.x,
		g_posCameraR.y,
		g_posCameraR.z);

}

//=============================================================================
// カメラの設定処理
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_mtxView, 
						&g_posCameraP,		// カメラの視点
						&g_posCameraR,		// カメラの注視点
						&g_posCameraU);		// カメラの上方向

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_mtxView);


	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxProjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&g_mtxProjection,
								VIEW_ANGLE,										// 視野角
								((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT),	// アスペクト比
								VIEW_NEAR_Z,									// ビュー平面のNearZ値
								VIEW_FAR_Z);									// ビュー平面のFarZ値

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_mtxProjection);
}

//=============================================================================
// カメラの向きの取得
//=============================================================================
D3DXVECTOR3 GetRotCamera(void)
{
	return g_rotCamera;
}

//=============================================================================
// ビューマトリックスの取得
//=============================================================================
D3DXMATRIX GetMtxView(void)
{
	return g_mtxView;
}


void SetChaseHightP(float hight)
{
	g_chaseHightP = hight;
}

void SetLengthIntervalCamera(float length)
{
	g_fLengthIntervalCamera = length;
}

CAMERA_MODE GetCameraMode()
{
	 return g_cameraMode;
}

void SetCameraMode(CAMERA_MODE val)
{
	g_cameraMode = val;
}

void SetPlayMode(PLAY_MODE val)
{
	g_playMode = val;
}

PLAY_MODE GetPlayMode()
{
	return g_playMode;
}

bool GetCutScene()
{
	return g_cutScene;
}


void WinScene()
{//カットシーン
	if (!g_cutScene)
	{//勝利時の第一画面は必ずカットシーン
		SetCameraMode(CAMERA_MODE_NEAR);
		SetChaseHightP(100.0f);
		SetLengthIntervalCamera(200.0f);

		g_cutScene = true;
	}

}
