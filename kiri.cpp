//=============================================================================
//
// ビルボード処理 [kiri.cpp]
// Author : 
//
//=============================================================================
#include "kiri.h"
#include "input.h"
#include "camera.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_KIRI		"data/TEXTURE/fog1.png"	// 読み込むテクスチャファイル名
#define	KIRI_SIZE_X		(20.0f)							// ビルボードの幅
#define	KIRI_SIZE_Y		(20.0f)							// ビルボードの高さ
#define	VALUE_MOVE_KIRI	(0.30f)							// 移動速度
#define	VALUE_JUMP				(10.0f)							// ジャンプ力
#define	VALUE_GRAVITY			(0.45f)							// 重力
#define	RATE_REGIST				(0.075f)						// 抵抗係数
#define	RATE_REFRECT			(-0.90f)						// 反射係数
#define SCROOL_SPEED (0.000025f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexKiri(LPDIRECT3DDEVICE9 pDevice);
void SetVertexKiri(float fSizeX, float fSizeY);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureKiri = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffKiri = NULL;	// 頂点バッファインターフェースへのポインタ

D3DXMATRIX				g_mtxWorldKiri;			// ワールドマトリックス
D3DXVECTOR3				g_posKiri;					// 位置
D3DXVECTOR3				g_sclKiri;					// スケール
D3DXVECTOR3				g_moveKiri;				// 移動量
int						g_nIdxShadowKiri;			// 影ID
bool					g_bEnableGravity = false;		// 重力を有効にするかどうか
bool                    g_kiriuse = false;
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitKiri(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	// 頂点情報の作成
	MakeVertexKiri(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_KIRI,			// ファイルの名前
								&g_pD3DTextureKiri);	// 読み込むメモリー

	g_posKiri = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_sclKiri = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_moveKiri = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	
	g_bEnableGravity = false;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitKiri(void)
{
	if(g_pD3DTextureKiri != NULL)
	{// テクスチャの開放
		g_pD3DTextureKiri->Release();
		g_pD3DTextureKiri = NULL;
	}

	if(g_pD3DVtxBuffKiri != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffKiri->Release();
		g_pD3DVtxBuffKiri = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateKiri(void)
{
	if (GetKeyboardTrigger(DIK_5))
	{
		g_kiriuse = g_kiriuse ? false : true;
	}
	if (g_kiriuse == true)
	{
		D3DXVECTOR3 camerap = GetCameraPosition();
		g_posKiri = D3DXVECTOR3(0.0f, float(camerap.y), float(camerap.z + 11.0f));

		VERTEX_3D *pVtx;
		
		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffKiri->Lock(0, 0, (void**)&pVtx, 0);
		//テクスチャをずらす
		pVtx[0].tex.x += -SCROOL_SPEED;
		pVtx[1].tex.x += -SCROOL_SPEED;
		pVtx[2].tex.x += -SCROOL_SPEED;
		pVtx[3].tex.x += -SCROOL_SPEED;
		// 頂点データをアンロックする
		g_pD3DVtxBuffKiri->Unlock();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawKiri(void)
{
	
	if (g_kiriuse == true)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		D3DXMATRIX mtxView, mtxScale, mtxTranslate;

		// ラインティングを無効にする
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		// ビューマトリックスを取得
		mtxView = GetMtxView();

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_mtxWorldKiri);

		// ポリゴンを正面に向ける
		g_mtxWorldKiri._11 = mtxView._11;
		g_mtxWorldKiri._12 = mtxView._21;
		g_mtxWorldKiri._13 = mtxView._31;
		g_mtxWorldKiri._21 = mtxView._12;
		g_mtxWorldKiri._22 = mtxView._22;
		g_mtxWorldKiri._23 = mtxView._32;
		g_mtxWorldKiri._31 = mtxView._13;
		g_mtxWorldKiri._32 = mtxView._23;
		g_mtxWorldKiri._33 = mtxView._33;



		// スケールを反映
		D3DXMatrixScaling(&mtxScale, g_sclKiri.x,
			g_sclKiri.y,
			g_sclKiri.z);
		D3DXMatrixMultiply(&g_mtxWorldKiri,
			&g_mtxWorldKiri, &mtxScale);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, g_posKiri.x,
			g_posKiri.y,
			g_posKiri.z);
		D3DXMatrixMultiply(&g_mtxWorldKiri,
			&g_mtxWorldKiri, &mtxTranslate);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldKiri);

		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffKiri, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureKiri);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

		// ラインティングを有効にする
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexKiri(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
												FVF_VERTEX_3D,				// 使用する頂点フォーマット
												D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffKiri,	// 頂点バッファインターフェースへのポインタ
												NULL)))						// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffKiri->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-KIRI_SIZE_X / 2, -KIRI_SIZE_Y / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-KIRI_SIZE_X / 2, KIRI_SIZE_Y / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(KIRI_SIZE_X / 2, -KIRI_SIZE_Y / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(KIRI_SIZE_X / 2, KIRI_SIZE_Y / 2, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffKiri->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexKiri(float fSizeX, float fSizeY)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffKiri->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffKiri->Unlock();
	}
}
