//=============================================================================
//
// タイマー処理 [timer.cpp]
// Author : 麦英泳
//
//=============================================================================
#include "timer.h"
#include "fade.h"
#include "score.h"
#include "input.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TIMER		"data/TEXTURE/number000.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_FRAME_TIMER	"data/TEXTURE/frame_timer.png"	// 読み込むテクスチャファイル名
#define	TIMER_SIZE_X		(35.0f)							// タイマーの数字の幅
#define	TIMER_SIZE_Y		(50.0f)							// タイマーの数字の高さ
#define	TIMER_INTERVAL_X	(0.0f)							// タイマーの数字の表示間隔

#define	NUM_PLACE			(3)			// タイマーの桁数

#define	TIMER_POS_X			(SCREEN_WIDTH / 2 - ((TIMER_SIZE_X * NUM_PLACE + TIMER_INTERVAL_X * (NUM_PLACE - 1)) / 2) )	// タイマーの表示基準位置Ｘ座標
#define	TIMER_POS_Y			(25.0f)																						// タイマーの表示基準位置Ｙ座標

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice);
void SetTextureTimer(int idx, int number);



//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureTimer[2] = {};		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffTimer = NULL;		// 頂点バッファインターフェースへのポインタ

D3DXVECTOR3				g_posTimer;
D3DXVECTOR3				g_rotTimer;

int						g_nTimer;						// タイマーの制限時間
bool					g_bEnableTimer;					// タイマー動作ON/OFF

bool g_timeOut;//時間切れかどうか
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_timeOut = 0;

	g_posTimer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotTimer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// タイマーの初期化
	g_nTimer = 999 * 60;
	g_bEnableTimer = true;

	// 頂点情報の作成
	MakeVertexTimer(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
								TEXTURE_TIMER,			// ファイルの名前
								&g_pD3DTextureTimer[0]);	// 読み込むメモリー
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
								TEXTURE_FRAME_TIMER,			// ファイルの名前
								&g_pD3DTextureTimer[1]);	// 読み込むメモリー

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTimer(void)
{
	if(g_pD3DTextureTimer[0] != NULL)
	{// テクスチャの開放
		g_pD3DTextureTimer[0]->Release();
		g_pD3DTextureTimer[0] = NULL;
	}
	if(g_pD3DTextureTimer[1] != NULL)
	{// テクスチャの開放
		g_pD3DTextureTimer[1]->Release();
		g_pD3DTextureTimer[1] = NULL;
	}

	if(g_pD3DVtxBuffTimer != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffTimer->Release();
		g_pD3DVtxBuffTimer = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTimer(void)
{

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_SUBTRACT))
	{
		g_nTimer = 300;
	}
#endif

	if(g_bEnableTimer)
	{
		g_nTimer--;

		if((g_nTimer < 0) && (g_timeOut == 0))
		{
			g_timeOut = 1;

			SetFade(FADE_OUT);

		}

		if (g_nTimer < 0)
		{
			g_nTimer = 0;
		}
		else if((g_nTimer / 60) >= (int)(powf(10.0f, (float)NUM_PLACE)))//最大値を超えれば 元罠
		{
			g_nTimer = ((int)(powf(10.0f, (float)NUM_PLACE)) - 1) * 60;//最大値になる　元罠
		}
	}

	for(int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
	{
		int number;
		int timer;
		
		timer = g_nTimer + 59;
		//スコアの考え方と一緒
		number = ((timer / 60) % (int)(powf(10.0f, (float)(NUM_PLACE - nCntPlace)))) / (int)(powf(10.0f, (float)(NUM_PLACE - nCntPlace - 1)));
		SetTextureTimer(nCntPlace, number);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pD3DVtxBuffTimer, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureTimer[0]);

	// ポリゴンの描画
	for(int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * 4), NUM_POLYGON);
	}

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureTimer[1]);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (NUM_PLACE * 4), NUM_POLYGON);
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (NUM_VERTEX * NUM_PLACE + 4),	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,								// 頂点バッファの使用法　
												FVF_VERTEX_2D,									// 使用する頂点フォーマット
												D3DPOOL_MANAGED,								// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffTimer,							// 頂点バッファインターフェースへのポインタ
												NULL)))											// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(TIMER_POS_X + nCntPlace * (TIMER_SIZE_X + TIMER_INTERVAL_X), TIMER_POS_Y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(TIMER_POS_X + nCntPlace * (TIMER_INTERVAL_X + TIMER_SIZE_X) + TIMER_SIZE_X, TIMER_POS_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(TIMER_POS_X + nCntPlace * (TIMER_SIZE_X + TIMER_INTERVAL_X), TIMER_POS_Y + TIMER_SIZE_Y, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(TIMER_POS_X + nCntPlace * (TIMER_INTERVAL_X + TIMER_SIZE_X) + TIMER_SIZE_X, TIMER_POS_Y + TIMER_SIZE_Y, 0.0f);

			// rhwの設定
			pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

			// 反射光の設定
			pVtx[0].diffuse = D3DCOLOR_RGBA(0, 255, 255, 255);
			pVtx[1].diffuse = D3DCOLOR_RGBA(0, 255, 255, 255);
			pVtx[2].diffuse = D3DCOLOR_RGBA(0, 255, 255, 255);
			pVtx[3].diffuse = D3DCOLOR_RGBA(0, 255, 255, 255);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		}

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(TIMER_POS_X - 17.5f, TIMER_POS_Y - 25, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(TIMER_POS_X + (TIMER_INTERVAL_X + TIMER_SIZE_X) * (NUM_PLACE - 1) + TIMER_SIZE_X + 17.5f, TIMER_POS_Y - 25, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(TIMER_POS_X - 17.5f, TIMER_POS_Y + 55, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(TIMER_POS_X + (TIMER_INTERVAL_X + TIMER_SIZE_X) * (NUM_PLACE - 1) + TIMER_SIZE_X + 17.5f, TIMER_POS_Y + 55, 0.0f);

		// rhwの設定
		pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = 1.0f;

		// 反射光の設定
		pVtx[0].diffuse = D3DCOLOR_RGBA(0, 255, 255, 255);//シアン
		pVtx[1].diffuse = D3DCOLOR_RGBA(0, 255, 255, 255);
		pVtx[2].diffuse = D3DCOLOR_RGBA(0, 255, 255, 255);
		pVtx[3].diffuse = D3DCOLOR_RGBA(0, 255, 255, 255);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffTimer->Unlock();
	}

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureTimer(int idx, int number)
{
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pD3DVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (idx * 4);

	// 頂点座標の設定
	pVtx[0].tex = D3DXVECTOR2(number * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(number * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 1.0f);

	// 頂点データをアンロックする
	g_pD3DVtxBuffTimer->Unlock();
}

//=============================================================================
// タイマーの開始
//=============================================================================
void EnableTimer(bool bEnable)
{
	g_bEnableTimer = bEnable;
}

//=============================================================================
// タイマーのリセット
//=============================================================================
void ResetTimer(int nTime)
{
	g_nTimer = nTime * 60;//秒数*フレーム
}

int GetTimer()
{
	return g_nTimer;

}

bool GetTimeOut()
{
	return g_timeOut;

}
