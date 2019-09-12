//=============================================================================
//
// パーティクル処理 [rain.cpp]
// Author : 
//
//=============================================================================
#include "rain.h"
#include "input.h"
#include"camera.h"
#include "shadow.h"
#include "main.h"
#include "player.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_RAIN	"data/TEXTURE/ame1.jpg"	// 読み込むテクスチャファイル名
#define	RAIN_SIZE_X		(5.0f)							// ビルボードの幅
#define	RAIN_SIZE_Y		(5.0f)							// ビルボードの高さ
#define	VALUE_MOVE_RAIN	(2.0f)							// 移動速度

#define	MAX_RAIN			(1024)						// ビルボード最大数



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexRain(LPDIRECT3DDEVICE9 pDevice);
void SetVertexRain(int nIdxRain, float fSizeX, float fSizeY);
void SetColorRain(int nIdxRain, D3DXCOLOR col);
					
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureRain = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffRain = NULL;	// 頂点バッファインターフェースへのポインタ

D3DXMATRIX				g_mtxWorldRain;				// ワールドマトリックス

PARTICLE				g_aRain[MAX_RAIN];		// パーティクルワーク
D3DXVECTOR3				g_posBaseRain;						// ビルボード発生位置

bool                    g_ameuse = false;               //ame ON/OFF
float					g_fWidthBaseRain = 5.0f;			// 基準の幅
float					g_fHeightBaseRain = 10.0f;			// 基準の高さ
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitRain(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点情報の作成
	MakeVertexRain(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_RAIN,			// ファイルの名前
								&g_pD3DTextureRain);	// 読み込むメモリー

	for(int nCntRain = 0; nCntRain < MAX_RAIN; nCntRain++)
	{
		g_aRain[nCntRain].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRain[nCntRain].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRain[nCntRain].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aRain[nCntRain].move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aRain[nCntRain].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aRain[nCntRain].fSizeX = RAIN_SIZE_X;
		g_aRain[nCntRain].fSizeY = RAIN_SIZE_Y;
		g_aRain[nCntRain].nIdxShadow = -1;
		g_aRain[nCntRain].nLife = 0;
		g_aRain[nCntRain].bUse = false;
		g_aRain[nCntRain].g_nAlpha = 0x0;
	}

	g_posBaseRain = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitRain(void)
{
	if(g_pD3DTextureRain != NULL)
	{// テクスチャの開放
		g_pD3DTextureRain->Release();
		g_pD3DTextureRain = NULL;
	}

	if(g_pD3DVtxBuffRain != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffRain->Release();
		g_pD3DVtxBuffRain = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateRain(void)
{
	

	if(GetKeyboardTrigger(DIK_6))
	{
		g_ameuse = g_ameuse ? false: true;
	}

	
		for(int nCntRain = 0; nCntRain < MAX_RAIN; nCntRain++)
		{
			if(g_aRain[nCntRain].bUse)
			{// 使用中
				g_aRain[nCntRain].pos.x += g_aRain[nCntRain].move.x;
				g_aRain[nCntRain].pos.z += g_aRain[nCntRain].move.z;

				g_aRain[nCntRain].pos.y += g_aRain[nCntRain].move.y;
				if(g_aRain[nCntRain].pos.y <= g_aRain[nCntRain].fSizeY / 2)
				{// 着地した
					g_aRain[nCntRain].bUse = FALSE;
				}
				g_aRain[nCntRain].move.y -= 0.00625f;
				/*g_aRain[nCntRain].move.x += (0.0f - g_aRain[nCntRain].move.x) * 0.015f;
				g_aRain[nCntRain].move.y -= 0.00625f;            
				g_aRain[nCntRain].move.z += (0.0f - g_aRain[nCntRain].move.z) * 0.015f;*/

				// アルファテストの閾値変更
				if (GetKeyboardPress(DIK_I))
				{
					g_aRain[nCntRain].g_nAlpha-=1;
					if (g_aRain[nCntRain].g_nAlpha < 0)
					{
						g_aRain[nCntRain].g_nAlpha = 0;
					}
				}
				if (GetKeyboardPress(DIK_K))
				{
					g_aRain[nCntRain].g_nAlpha+=1;
					if (g_aRain[nCntRain].g_nAlpha > 255)
					{
						g_aRain[nCntRain].g_nAlpha = 255;
					}
				}

				g_aRain[nCntRain].nLife--;
				if(g_aRain[nCntRain].nLife <= 0)
				{
					g_aRain[nCntRain].bUse = false;
					
				}
				
			}

		}
		

		
	
	if (g_ameuse==true)
	{
		
		D3DXVECTOR3 pos;
		D3DXVECTOR3 move;
		float fAngle, fLength;
		int nLife;
		float fSize;
		float ALpha;
		float bei;

		ALpha = 0.9f;
		bei = (float)(rand() % 25) / 10;
		pos.y =  1600.0f;                    //雪発生の原点を定義
		pos.x = (float)(rand() % 1000 - (rand() % 1000));
		pos.z = (float)(rand() % 1000 - (rand() % 600));

		fAngle = 90.0f;
		fLength = rand() % (int)(g_fWidthBaseRain * 600) / 100.0f - g_fWidthBaseRain;//幅　　
		nLife = rand() % 100 + 15000;                             //寿命　　　　　　　
		fSize = (float)(rand() % 10 + 2);                                   //大きさ

		move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);                                     //落ちる速度　　　　　　　　　　

		SetRain(pos, move, D3DXCOLOR(0.6f, 0.6f, 0.6f, ALpha), fSize, fSize, nLife, bei);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawRain(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView,mtxScale,mtxTranslate;

	// ライティングを無効に
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// パーティクルっぽく設定をする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	

	// ブレンドを表現したい設定になるようにする
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		// αソースカラーの指定
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	// αソースカラーの指定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		// αデスティネーションカラーの指定
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);//奥行きを考えない

	
	
	

	for(int nCntRain = 0; nCntRain < MAX_RAIN; nCntRain++)
	{
		if(g_aRain[nCntRain].bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldRain);

			// ビューマトリックスを取得
			mtxView = GetMtxView();

			g_mtxWorldRain._11 = mtxView._11;
			g_mtxWorldRain._12 = mtxView._21;
			g_mtxWorldRain._13 = mtxView._31;
			g_mtxWorldRain._21 = mtxView._12;
			g_mtxWorldRain._22 = mtxView._22;
			g_mtxWorldRain._23 = mtxView._32;
			g_mtxWorldRain._31 = mtxView._13;
			g_mtxWorldRain._32 = mtxView._23;
			g_mtxWorldRain._33 = mtxView._33;

			// スケールを反映
			D3DXMatrixScaling(&mtxScale, g_aRain[nCntRain].scale.x, g_aRain[nCntRain].scale.y, g_aRain[nCntRain].scale.z);
			D3DXMatrixMultiply(&g_mtxWorldRain, &g_mtxWorldRain, &mtxScale);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, g_aRain[nCntRain].pos.x, g_aRain[nCntRain].pos.y, g_aRain[nCntRain].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldRain, &g_mtxWorldRain, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldRain);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffRain, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);
			pDevice->SetRenderState(D3DRS_ALPHAREF, (g_aRain[nCntRain].g_nAlpha));

			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureRain);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntRain * 4), NUM_POLYGON);
		}
	}

	// ライティングを有効に
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// 通常ブレンドに戻す
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexRain(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_RAIN,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,							// 頂点バッファの使用法　
												FVF_VERTEX_3D,								// 使用する頂点フォーマット
												D3DPOOL_MANAGED,							// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffRain,					// 頂点バッファインターフェースへのポインタ
												NULL)))										// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffRain->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntRain = 0; nCntRain < MAX_RAIN; nCntRain++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-RAIN_SIZE_X / 2, -RAIN_SIZE_Y / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(RAIN_SIZE_X / 2, -RAIN_SIZE_Y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-RAIN_SIZE_X / 2, RAIN_SIZE_Y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(RAIN_SIZE_X / 2, RAIN_SIZE_Y / 2, 0.0f);
			
			// 法線の設定
			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			// 反射光の設定
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// 頂点データをアンロックする
		g_pD3DVtxBuffRain->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexRain(int nIdxRain, float fSizeX, float fSizeY)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffRain->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxRain * 4);

		// 頂点座標の設定
		
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffRain->Unlock();
	}
}

//=============================================================================
// 頂点カラーの設定
//=============================================================================
void SetColorRain(int nIdxRain, D3DXCOLOR col)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffRain->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxRain * 4);

		// 頂点座標の設定
		pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = col;

		// 頂点データをアンロックする
		g_pD3DVtxBuffRain->Unlock();
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
int SetRain(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fSizeX, float fSizeY, int nLife,float beilv)
{
	int nIdxRain = -1;

	for(int nCntRain = 0; nCntRain < MAX_RAIN; nCntRain++)
	{
		if(!g_aRain[nCntRain].bUse)
		{
			g_aRain[nCntRain].pos = pos;
			g_aRain[nCntRain].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aRain[nCntRain].scale = D3DXVECTOR3(1.0f, 1.0f*beilv, 1.0f);
			g_aRain[nCntRain].move = move;
			g_aRain[nCntRain].col = col;
			g_aRain[nCntRain].fSizeX = fSizeX;
			g_aRain[nCntRain].fSizeY = fSizeY;
			g_aRain[nCntRain].nLife = nLife;
			g_aRain[nCntRain].bUse = true;
			// 頂点座標の設定
		
			SetVertexRain(nCntRain, fSizeX, fSizeY);
			SetColorRain(nCntRain, col);
			nIdxRain = nCntRain;


			break;
		}
	}

	return nIdxRain;
}
