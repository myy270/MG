//=============================================================================
//
// パーティクル処理 [snow.cpp]
// Author : 
//
//=============================================================================
#include "snow.h"
#include "input.h"
#include"camera.h"
#include "shadow.h"
#include "main.h"
#include "player.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_SNOW	"data/TEXTURE/effect000.jpg"	// 読み込むテクスチャファイル名
#define	SNOW_SIZE_X		(5.0f)							// ビルボードの幅
#define	SNOW_SIZE_Y		(5.0f)							// ビルボードの高さ
#define	VALUE_MOVE_SNOW	(2.0f)							// 移動速度

#define	MAX_SNOW			(2028)						// ビルボード最大数



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexSnow(LPDIRECT3DDEVICE9 pDevice);
void SetVertexSnow(int nIdxSnow, float fSizeX, float fSizeY);
void SetColorSnow(int nIdxSnow, D3DXCOLOR col);
					
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureSnow = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffSnow = NULL;	// 頂点バッファインターフェースへのポインタ

D3DXMATRIX				g_mtxWorldSnow;				// ワールドマトリックス

PARTICLE				g_Snow[MAX_SNOW];		// パーティクルワーク
D3DXVECTOR3				g_posBase;						// ビルボード発生位置
bool					g_bPause = false;				// ポーズON/OFF
bool                    g_Snowuse = false;
float					g_fWidthBase = 5.0f;			// 基準の幅
float					g_fHeightBase = 10.0f;			// 基準の高さ

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitSnow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点情報の作成
	MakeVertexSnow(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_SNOW,			// ファイルの名前
								&g_pD3DTextureSnow);	// 読み込むメモリー

	for(int nCntSnow = 0; nCntSnow < MAX_SNOW; nCntSnow++)
	{
		g_Snow[nCntSnow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Snow[nCntSnow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Snow[nCntSnow].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_Snow[nCntSnow].move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_Snow[nCntSnow].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Snow[nCntSnow].fSizeX = SNOW_SIZE_X;
		g_Snow[nCntSnow].fSizeY = SNOW_SIZE_Y;
		g_Snow[nCntSnow].nIdxShadow = -1;
		g_Snow[nCntSnow].nLife = 0;
		g_Snow[nCntSnow].bUse = false;
		g_Snow[nCntSnow].g_nAlpha = 0x0;
	}

	g_posBase = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitSnow(void)
{
	if(g_pD3DTextureSnow != NULL)
	{// テクスチャの開放
		g_pD3DTextureSnow->Release();
		g_pD3DTextureSnow = NULL;
	}

	if(g_pD3DVtxBuffSnow != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffSnow->Release();
		g_pD3DVtxBuffSnow = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateSnow(void)
{
	

	if(GetKeyboardTrigger(DIK_4))
	{
		g_Snowuse = g_Snowuse ? false: true;
	}

	
		for(int nCntSnow = 0; nCntSnow < MAX_SNOW; nCntSnow++)
		{
			if(g_Snow[nCntSnow].bUse)
			{// 使用中
				g_Snow[nCntSnow].pos.x += g_Snow[nCntSnow].move.x;
				g_Snow[nCntSnow].pos.z += g_Snow[nCntSnow].move.z;

				g_Snow[nCntSnow].pos.y += g_Snow[nCntSnow].move.y;
				if(g_Snow[nCntSnow].pos.y <= g_Snow[nCntSnow].fSizeY / 2)
				{// 着地した
					g_Snow[nCntSnow].bUse = FALSE;
				}

				g_Snow[nCntSnow].move.x += (0.0f - g_Snow[nCntSnow].move.x) * 0.015f;
				g_Snow[nCntSnow].move.y -= 0.00625f;            
				g_Snow[nCntSnow].move.z += (0.0f - g_Snow[nCntSnow].move.z) * 0.015f;

				

				g_Snow[nCntSnow].nLife--;
				if(g_Snow[nCntSnow].nLife <= 0)
				{
					g_Snow[nCntSnow].bUse = false;
					
				}
				else
				{
					//
					//if(g_Snow[nCntSnow].nLife <= 20)
					//{
					//	// α値設定
					//	g_Snow[nCntSnow].col.a -= 0.05f;
					//	if(g_Snow[nCntSnow].col.a < 0.0f)
					//	{
					//		g_Snow[nCntSnow].col.a = 0.0f;
					//	}
					//}

					// 色の設定
					/*SetColorParticle(nCntSnow, g_Snow[nCntSnow].col);*/
				}
			}

		}

		if (g_Snowuse == true)
		{
		D3DXVECTOR3 playerp = GetPositionPlayer();
		D3DXVECTOR3 pos;
		D3DXVECTOR3 move;
		float fAngle, fLength;
		int nLife;
		float fSize;
		float ALpha;
		ALpha = (float)((rand() % 6)+5) / 10.0f;
		pos = D3DXVECTOR3(playerp.x, 1500.0f, playerp.z);                    //雪発生の原点を定義
		fAngle = (float)(rand() % 628-314 ) / 100.0f;            //発散方向　　　　　　　
		fLength = rand() % (int)(g_fWidthBase * 500) / 100.0f - g_fWidthBase;//幅　　
		nLife = rand() % 100 + 150000;                             //寿命　　　　　　　
		fSize = rand() % 10 + 2.0f;                                   //大きさ
		move.x = sinf(fAngle) * fLength;
		move.y = 0.00625f;                                        //落ちる速度　　　　　　　　　　
		move.z = cosf(fAngle) * fLength;
		SetParticle(pos, move, D3DXCOLOR(0.5f, 0.5f, 0.5f, ALpha), fSize, fSize, nLife);

		
	}
	
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawSnow(void)
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

	
	
	

	for(int nCntSnow = 0; nCntSnow < MAX_SNOW; nCntSnow++)
	{
		if(g_Snow[nCntSnow].bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldSnow);

			// ビューマトリックスを取得
			mtxView = GetMtxView();

			g_mtxWorldSnow._11 = mtxView._11;
			g_mtxWorldSnow._12 = mtxView._21;
			g_mtxWorldSnow._13 = mtxView._31;
			g_mtxWorldSnow._21 = mtxView._12;
			g_mtxWorldSnow._22 = mtxView._22;
			g_mtxWorldSnow._23 = mtxView._32;
			g_mtxWorldSnow._31 = mtxView._13;
			g_mtxWorldSnow._32 = mtxView._23;
			g_mtxWorldSnow._33 = mtxView._33;

			// スケールを反映
			D3DXMatrixScaling(&mtxScale, g_Snow[nCntSnow].scale.x, g_Snow[nCntSnow].scale.y, g_Snow[nCntSnow].scale.z);
			D3DXMatrixMultiply(&g_mtxWorldSnow, &g_mtxWorldSnow, &mtxScale);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, g_Snow[nCntSnow].pos.x, g_Snow[nCntSnow].pos.y, g_Snow[nCntSnow].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldSnow, &g_mtxWorldSnow, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldSnow);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffSnow, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);
			pDevice->SetRenderState(D3DRS_ALPHAREF, (g_Snow[nCntSnow].g_nAlpha));

			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureSnow);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntSnow * 4), NUM_POLYGON);
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
HRESULT MakeVertexSnow(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_SNOW,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,							// 頂点バッファの使用法　
												FVF_VERTEX_3D,								// 使用する頂点フォーマット
												D3DPOOL_MANAGED,							// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffSnow,					// 頂点バッファインターフェースへのポインタ
												NULL)))										// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffSnow->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntSnow = 0; nCntSnow < MAX_SNOW; nCntSnow++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-SNOW_SIZE_X / 2, -SNOW_SIZE_Y / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(SNOW_SIZE_X / 2, -SNOW_SIZE_Y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-SNOW_SIZE_X / 2, SNOW_SIZE_Y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(SNOW_SIZE_X / 2, SNOW_SIZE_Y / 2, 0.0f);

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
		g_pD3DVtxBuffSnow->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexSnow(int nIdxSnow, float fSizeX, float fSizeY)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffSnow->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxSnow * 4);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffSnow->Unlock();
	}
}

//=============================================================================
// 頂点カラーの設定
//=============================================================================
void SetColorSnow(int nIdxSnow, D3DXCOLOR col)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffSnow->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxSnow * 4);

		// 頂点座標の設定
		pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = col;

		// 頂点データをアンロックする
		g_pD3DVtxBuffSnow->Unlock();
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
int SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fSizeX, float fSizeY, int nLife)
{
	int nIdxSnow = -1;

	for(int nCntSnow = 0; nCntSnow < MAX_SNOW; nCntSnow++)
	{
		if(!g_Snow[nCntSnow].bUse)
		{
			g_Snow[nCntSnow].pos = pos;
			g_Snow[nCntSnow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Snow[nCntSnow].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_Snow[nCntSnow].move = move;
			g_Snow[nCntSnow].col = col;
			g_Snow[nCntSnow].fSizeX = fSizeX;
			g_Snow[nCntSnow].fSizeY = fSizeY;
			g_Snow[nCntSnow].nLife = nLife;
			g_Snow[nCntSnow].bUse = true;
			// 頂点座標の設定
		
			SetVertexSnow(nCntSnow, fSizeX, fSizeY);
			SetColorSnow(nCntSnow, col);
			nIdxSnow = nCntSnow;


			break;
		}
	}

	return nIdxSnow;
}
