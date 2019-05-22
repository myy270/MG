//=============================================================================
//
// スコア処理 [score.cpp]
// Author : 麦英泳
//
//=============================================================================
#include "score.h"
#include "player.h"
#include "camera.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_SCORE		"data/TEXTURE/number000.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_FRAME_SCORE	"data/TEXTURE/frame_score.png"	// 読み込むテクスチャファイル名
#define	SCORE_SIZE_X		(35.0f)							// スコアの数字の幅
#define	SCORE_SIZE_Y		(50.0f)							// スコアの数字の高さ
#define	SCORE_INTERVAL_X	(0.0f)							// スコアの数字の表示間隔

#define	NUM_PLACE			(5)								// スコアの桁数

#define	SCORE_POS_X			(SCREEN_WIDTH - (SCORE_INTERVAL_X + SCORE_SIZE_X) * NUM_PLACE - 20.0f)	// 敵のスコアの表示基準位置Ｘ座標 20は位置を開ける
#define	SCORE_POS_Y			(25.0f)																	// スコアの表示基準位置Ｙ座標

#define	SCORE_POS_X2		(20.0f)// プレイヤーのスコア

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);// 敵の
void SetTextureScore(int idx, int number);// 敵の

HRESULT MakeVertexScore2(LPDIRECT3DDEVICE9 pDevice);// プレイヤーの
void SetTextureScore2(int idx, int number);// プレイヤーの

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureScore[2] = {};	// テクスチャへのポインタ

LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffScore = NULL;		// 敵の頂点バッファインターフェースへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffScore2 = NULL;		// プレイヤーの頂点バッファインターフェースへのポインタ

int						g_score;						// 敵のスコア

int						g_score2;						// プレイヤーのスコア

OBJECT g_winner;
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitScore(void)
{


	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_winner = OBJECT_MAX;

	// スコアの初期化
	g_score = 0;
	g_score2 = 0;
	
	// 頂点情報の作成
	MakeVertexScore(pDevice);

	MakeVertexScore2(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
								TEXTURE_SCORE,			// ファイルの名前
								&g_pD3DTextureScore[0]);	// 読み込むメモリー

	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
								TEXTURE_FRAME_SCORE,		// ファイルの名前
								&g_pD3DTextureScore[1]);	// 読み込むメモリー

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitScore(void)
{
	if(g_pD3DTextureScore[0] != NULL)
	{// テクスチャの開放
		g_pD3DTextureScore[0]->Release();
		g_pD3DTextureScore[0] = NULL;
	}

	if(g_pD3DTextureScore[1] != NULL)
	{// テクスチャの開放
		g_pD3DTextureScore[1]->Release();
		g_pD3DTextureScore[1] = NULL;
	}

	if(g_pD3DVtxBuffScore != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffScore->Release();
		g_pD3DVtxBuffScore = NULL;
	}

	if (g_pD3DVtxBuffScore2 != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffScore2->Release();
		g_pD3DVtxBuffScore2 = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateScore(void)
{
	for(int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
	{
		int number;
		//上から認識する; (NUM_PLACE - nCntPlace)の桁を認識する;　
		//分子の(g_score % (int)(powf(10.0f, (float)(NUM_PLACE - nCntPlace))))の結果は(NUM_PLACE - nCntPlace)の桁以降の数字である
		// % と / をちゃんと見分ける
		number = (g_score % (int)(powf(10.0f, (float)(NUM_PLACE - nCntPlace)))) / (int)(powf(10.0f, (float)(NUM_PLACE - nCntPlace - 1)));
		SetTextureScore(nCntPlace, number);


		//プレイヤーの
		number = (g_score2 % (int)(powf(10.0f, (float)(NUM_PLACE - nCntPlace)))) / (int)(powf(10.0f, (float)(NUM_PLACE - nCntPlace - 1)));
		SetTextureScore2(nCntPlace, number);

	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pD3DVtxBuffScore, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureScore[0]);

	// ポリゴンの描画
	for(int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * 4), NUM_POLYGON);
	}

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureScore[1]);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (NUM_PLACE * 4), NUM_POLYGON);

	

	//プレイヤーの
	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pD3DVtxBuffScore2, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureScore[0]);

	// ポリゴンの描画
	for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * 4), NUM_POLYGON);
	}

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureScore[1]);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (NUM_PLACE * 4), NUM_POLYGON);

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (NUM_VERTEX * NUM_PLACE + 4),	// 頂点データ用に確保するバッファサイズ(バイト単位) +4はフレームの頂点
												D3DUSAGE_WRITEONLY,								// 頂点バッファの使用法　
												FVF_VERTEX_2D,									// 使用する頂点フォーマット
												D3DPOOL_MANAGED,								// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffScore,							// 頂点バッファインターフェースへのポインタ
												NULL)))											// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += 4)
		{//数字の頂点
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(SCORE_POS_X + nCntPlace * (SCORE_SIZE_X + SCORE_INTERVAL_X), SCORE_POS_Y, 0.0f);//1 2 3 4 5 6 7 8 の格式 罠
			pVtx[1].vtx = D3DXVECTOR3(SCORE_POS_X + nCntPlace * (SCORE_INTERVAL_X + SCORE_SIZE_X) + SCORE_SIZE_X, SCORE_POS_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(SCORE_POS_X + nCntPlace * (SCORE_SIZE_X + SCORE_INTERVAL_X), SCORE_POS_Y + SCORE_SIZE_Y, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(SCORE_POS_X + nCntPlace * (SCORE_INTERVAL_X + SCORE_SIZE_X) + SCORE_SIZE_X, SCORE_POS_Y + SCORE_SIZE_Y, 0.0f);

			// rhwの設定
			pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

			// 反射光の設定
			pVtx[0].diffuse = D3DCOLOR_RGBA(255, 170, 192, 255);//ピンク
			pVtx[1].diffuse = D3DCOLOR_RGBA(255, 170, 192, 255);
			pVtx[2].diffuse = D3DCOLOR_RGBA(255, 170, 192, 255);
			pVtx[3].diffuse = D3DCOLOR_RGBA(255, 170, 192, 255);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		}

		{//フレームの頂点
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(SCORE_POS_X - 15, SCORE_POS_Y-25, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(SCORE_POS_X + (SCORE_INTERVAL_X + SCORE_SIZE_X) * NUM_PLACE + 15, SCORE_POS_Y - 25, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(SCORE_POS_X - 15, SCORE_POS_Y + 55, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(SCORE_POS_X + (SCORE_INTERVAL_X + SCORE_SIZE_X) * NUM_PLACE + 15, SCORE_POS_Y + 55, 0.0f);

			// rhwの設定
			pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

			// 反射光の設定
			pVtx[0].diffuse = D3DCOLOR_RGBA(255, 170, 192, 255);//ピンク
			pVtx[1].diffuse = D3DCOLOR_RGBA(255, 170, 192, 255);
			pVtx[2].diffuse = D3DCOLOR_RGBA(255, 170, 192, 255);
			pVtx[3].diffuse = D3DCOLOR_RGBA(255, 170, 192, 255);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// 頂点データをアンロックする
		g_pD3DVtxBuffScore->Unlock();
	}

	return S_OK;
}

HRESULT MakeVertexScore2(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (NUM_VERTEX * NUM_PLACE + 4),	// 頂点データ用に確保するバッファサイズ(バイト単位) +4はフレームの頂点
												D3DUSAGE_WRITEONLY,								// 頂点バッファの使用法　
												FVF_VERTEX_2D,									// 使用する頂点フォーマット
												D3DPOOL_MANAGED,								// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffScore2,							// 頂点バッファインターフェースへのポインタ
												NULL)))											// NULLに設定
	{
        return E_FAIL;
	}

	{
		//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffScore2->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += 4)
		{//数字の頂点
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(SCORE_POS_X2 + nCntPlace * (SCORE_SIZE_X + SCORE_INTERVAL_X), SCORE_POS_Y, 0.0f);//1 2 3 4 5 6 7 8 の格式 罠
			pVtx[1].vtx = D3DXVECTOR3(SCORE_POS_X2 + nCntPlace * (SCORE_INTERVAL_X + SCORE_SIZE_X) + SCORE_SIZE_X, SCORE_POS_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(SCORE_POS_X2 + nCntPlace * (SCORE_SIZE_X + SCORE_INTERVAL_X), SCORE_POS_Y + SCORE_SIZE_Y, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(SCORE_POS_X2 + nCntPlace * (SCORE_INTERVAL_X + SCORE_SIZE_X) + SCORE_SIZE_X, SCORE_POS_Y + SCORE_SIZE_Y, 0.0f);

			// rhwの設定
			pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

			// 反射光の設定
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);//オレンジ
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		}

		{//フレームの頂点
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(SCORE_POS_X2 - 15, SCORE_POS_Y-25, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(SCORE_POS_X2 + (SCORE_INTERVAL_X + SCORE_SIZE_X) * NUM_PLACE + 15, SCORE_POS_Y - 25, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(SCORE_POS_X2 - 15, SCORE_POS_Y + 55, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(SCORE_POS_X2 + (SCORE_INTERVAL_X + SCORE_SIZE_X) * NUM_PLACE + 15, SCORE_POS_Y + 55, 0.0f);

			// rhwの設定
			pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

			// 反射光の設定
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);//オレンジ
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// 頂点データをアンロックする
		g_pD3DVtxBuffScore2->Unlock();
	}

	return S_OK;
}


//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureScore(int idx, int number)
{
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pD3DVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (idx * 4);

	// 頂点座標の設定
	pVtx[0].tex = D3DXVECTOR2(number * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(number * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 1.0f);

	// 頂点データをアンロックする
	g_pD3DVtxBuffScore->Unlock();
}

void SetTextureScore2(int idx, int number)
{
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pD3DVtxBuffScore2->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (idx * 4);

	// 頂点座標の設定
	pVtx[0].tex = D3DXVECTOR2(number * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(number * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 1.0f);

	// 頂点データをアンロックする
	g_pD3DVtxBuffScore2->Unlock();
}
//=============================================================================
// スコアの変更
//=============================================================================
void ChangeScore(int value)
{
	g_score += value;
	if(g_score < 0)
	{
		g_score = 0;
	}
	else if(g_score >= (int)(powf(10.0f, (float)NUM_PLACE )))//ｘのｙ乗　!!!　罠
	{
		g_score = (int)(powf(10.0f, (float)NUM_PLACE)) - 1;
	}
}

//プレイヤーの
void ChangeScore2(int value)
{
	g_score2 += value;
	if (g_score2 < 0)
	{
		g_score2 = 0;
	}
	else if (g_score2 >= (int)(powf(10.0f, (float)NUM_PLACE)))//ｘのｙ乗　!!!　罠
	{
		g_score2 = (int)(powf(10.0f, (float)NUM_PLACE)) - 1;
	}

}

void compScore()
{
	if (g_score2 >= g_score)
	{//プレイヤー勝つ場合

		WinScene();//カットシーンする
		g_winner = OBJECT_PLAYER;
	}
	else
	{//プレイヤー負ける

		if (GetPlayMode() == PLAY_MODE_DOUBLE)
		{//2pの場合、2pにカットシーン
			WinScene();//カットシーンする
			g_winner = OBJECT_ENEMY;
		}


	}

}

OBJECT GetWinner()
{
	return g_winner;

}