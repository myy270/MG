//=============================================================================
//
// 爆発処理 [explosion.cpp]
// Author : 麦英泳
//
//=============================================================================
#include "explosion.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_EXPLOSION		"data/TEXTURE/explosion000.png"	// 読み込むテクスチャファイル名
#define	BULLET_SIZE_X			(50.0f)							// ビルボードの幅　BULLET?
#define	BULLET_SIZE_Y			(50.0f)							// ビルボードの高さ
#define	VALUE_MOVE_EXPLOSION	(2.0f)							// 移動速度

#define	MAX_EXPLOSION			(128)							// ビルボード最大数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 回転
	D3DXVECTOR3 scale;		// スケール
	D3DXCOLOR col;			// 色
	float fSizeX;			// 幅
	float fSizeY;			// 高さ
	int nCounter;			// カウンター
	int nPattern;			// パターンNo.
	int nType;				// 種類
	bool bUse;				// 使用しているかどうか
} EXPLOSION;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice);
void SetVertexExplosion(int nIdxBullet, float fSizeX, float fSizeY);
void SetColorExplosion(int nIdxExplosion, D3DXCOLOR col);
void SetTextureExplosion(int nIdxExplosion, int nPattern);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureExplosion = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffExplosion = NULL;	// 頂点バッファインターフェースへのポインタ

D3DXMATRIX				g_mtxWorldExplosion;			// ワールドマトリックス

EXPLOSION				g_aExplosion[MAX_EXPLOSION];	// 爆発ワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点情報の作成
	MakeVertexExplosion(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_EXPLOSION,			// ファイルの名前
								&g_pD3DTextureExplosion);	// 読み込むメモリー

	for(int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aExplosion[nCntExplosion].fSizeX = BULLET_SIZE_X;
		g_aExplosion[nCntExplosion].fSizeY = BULLET_SIZE_Y;
		g_aExplosion[nCntExplosion].nCounter = 0;
		g_aExplosion[nCntExplosion].nPattern = 0;
		g_aExplosion[nCntExplosion].nType = EXPLOSIONTYPE_BULLET_PLAYER;
		g_aExplosion[nCntExplosion].bUse = false;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitExplosion(void)
{
	if(g_pD3DTextureExplosion != NULL)
	{// テクスチャの開放
		g_pD3DTextureExplosion->Release();
		g_pD3DTextureExplosion = NULL;
	}

	if(g_pD3DVtxBuffExplosion != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffExplosion->Release();
		g_pD3DVtxBuffExplosion = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateExplosion(void)
{
	D3DXVECTOR3 rotCamera;

	// カメラの回転を取得
	rotCamera = GetRotCamera();

	for(int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if(g_aExplosion[nCntExplosion].bUse)
		{
			g_aExplosion[nCntExplosion].nCounter--;
			if((g_aExplosion[nCntExplosion].nCounter % 4) == 0)//4フレームごと変化する
			{
				g_aExplosion[nCntExplosion].nPattern++;
				if(g_aExplosion[nCntExplosion].nPattern >= 8)
				{
					g_aExplosion[nCntExplosion].bUse = false;
				}
				else
				{
					// テクスチャ座標の設定
					SetTextureExplosion(nCntExplosion, g_aExplosion[nCntExplosion].nPattern);
				}
			}

			// 頂点座標の設定　段々大きくする
			g_aExplosion[nCntExplosion].fSizeX += 0.50f;
			g_aExplosion[nCntExplosion].fSizeY += 0.50f;
			SetVertexExplosion(nCntExplosion, g_aExplosion[nCntExplosion].fSizeX, g_aExplosion[nCntExplosion].fSizeY);

			if(g_aExplosion[nCntExplosion].nPattern >= 2)
			{
				// 頂点カラーの設定　段々透明する
				g_aExplosion[nCntExplosion].col.a -= 0.02f;
				if(g_aExplosion[nCntExplosion].col.a < 0.0f)
				{
					g_aExplosion[nCntExplosion].col.a = 0.0f;
				}
				SetColorExplosion(nCntExplosion, g_aExplosion[nCntExplosion].col);
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView,mtxScale,mtxTranslate;

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);				// Z比較なし

	for(int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if(g_aExplosion[nCntExplosion].bUse)
		{

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldExplosion);

			// ビューマトリックスを取得
			mtxView = GetMtxView();

			g_mtxWorldExplosion._11 = mtxView._11;
			g_mtxWorldExplosion._12 = mtxView._21;
			g_mtxWorldExplosion._13 = mtxView._31;
			g_mtxWorldExplosion._21 = mtxView._12;
			g_mtxWorldExplosion._22 = mtxView._22;
			g_mtxWorldExplosion._23 = mtxView._32;
			g_mtxWorldExplosion._31 = mtxView._13;
			g_mtxWorldExplosion._32 = mtxView._23;
			g_mtxWorldExplosion._33 = mtxView._33;

			// スケールを反映
			D3DXMatrixScaling(&mtxScale, g_aExplosion[nCntExplosion].scale.x, g_aExplosion[nCntExplosion].scale.y, g_aExplosion[nCntExplosion].scale.z);
			D3DXMatrixMultiply(&g_mtxWorldExplosion, &g_mtxWorldExplosion, &mtxScale);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, g_aExplosion[nCntExplosion].pos.x, g_aExplosion[nCntExplosion].pos.y, g_aExplosion[nCntExplosion].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldExplosion, &g_mtxWorldExplosion, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldExplosion);

			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffExplosion, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureExplosion);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntExplosion * 4), NUM_POLYGON);

			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		}
	}

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);				// Z比較あり
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_EXPLOSION,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,							// 頂点バッファの使用法　
												FVF_VERTEX_3D,								// 使用する頂点フォーマット
												D3DPOOL_MANAGED,							// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffExplosion,					// 頂点バッファインターフェースへのポインタ
												NULL)))										// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pVtx += 4)
		{
			// 頂点座標の設定　順位が間違ってる　どうせ後もう一度設置するから、ここはどうでもいい
			pVtx[0].vtx = D3DXVECTOR3(-BULLET_SIZE_X / 2, -BULLET_SIZE_Y / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(BULLET_SIZE_X / 2, -BULLET_SIZE_Y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-BULLET_SIZE_X / 2, BULLET_SIZE_Y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(BULLET_SIZE_X / 2, BULLET_SIZE_Y / 2, 0.0f);

			// 法線の設定
			pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].vtx = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].vtx = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].vtx = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
		g_pD3DVtxBuffExplosion->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexExplosion(int nIdxExplosion, float fSizeX, float fSizeY)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxExplosion * 4);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffExplosion->Unlock();
	}
}

//=============================================================================
// 頂点カラーの設定
//=============================================================================
void SetColorExplosion(int nIdxExplosion, D3DXCOLOR col)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxExplosion * 4);

		// 頂点座標の設定
		pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = col;

		// 頂点データをアンロックする
		g_pD3DVtxBuffExplosion->Unlock();
	}
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureExplosion(int nIdxExplosion, int nPattern)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxExplosion * 4);

		// 頂点座標の設定
		pVtx[0].tex = D3DXVECTOR2(nPattern * 0.125f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((nPattern + 1) * 0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(nPattern * 0.125f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((nPattern + 1) * 0.125f, 1.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffExplosion->Unlock();
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
int SetExplosion(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nType)
{
	int nIdxExplosion = -1;

	for(int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if(!g_aExplosion[nCntExplosion].bUse)
		{
			g_aExplosion[nCntExplosion].pos = pos;
			g_aExplosion[nCntExplosion].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aExplosion[nCntExplosion].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_aExplosion[nCntExplosion].fSizeX = fSizeX;
			g_aExplosion[nCntExplosion].fSizeY = fSizeY;
			g_aExplosion[nCntExplosion].nCounter = 0;
			g_aExplosion[nCntExplosion].nPattern = 0;
			g_aExplosion[nCntExplosion].nType = nType;
			g_aExplosion[nCntExplosion].bUse = true;

			// 頂点座標の設定
			SetVertexExplosion(nCntExplosion, fSizeX, fSizeY);

			if(g_aExplosion[nCntExplosion].nType == EXPLOSIONTYPE_BULLET_PLAYER)
			{
				g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); 
			}
			else if(g_aExplosion[nCntExplosion].nType == EXPLOSIONTYPE_BULLET_ENEMY)
			{
				g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f); 
			}
			SetColorExplosion(nCntExplosion, g_aExplosion[nCntExplosion].col);

			// テクスチャ座標の設定
			SetTextureExplosion(nCntExplosion, 0);

			nIdxExplosion = nCntExplosion;

			break;
		}
	}

	return nIdxExplosion;
}
