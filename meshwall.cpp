//=============================================================================
//
// メッシュ壁の処理 [meshwall.cpp]
// Author : 麦英泳
//
//=============================================================================
#include "meshwall.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_MESH_WALL		(128)							// 壁の総数
#define	TEXTURE_FILENAME	"data/TEXTURE/ice2.png"		// 読み込むテクスチャファイル名
#define	TEXTURE_FILENAME2	"data/TEXTURE/field002.jpg"		// 読み込むテクスチャファイル名

#define	VALUE_MOVE_WALL		(5.0f)							// 移動速度
#define	VALUE_ROTATE_WALL	(D3DX_PI * 0.001f)				// 回転速度

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pD3DTexture = NULL;		// テクスチャ読み込み場所
LPDIRECT3DTEXTURE9 g_pD3DTexture2 = NULL;		// テクスチャ読み込み場所

typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pD3DVtxBuff;		// 頂点バッファインターフェースへのポインタ
	LPDIRECT3DINDEXBUFFER9 pD3DIdxBuff;			// インデックスバッファインターフェースへのポインタ

	D3DXMATRIX mtxWorld;						// ワールドマトリックス
	D3DXVECTOR3 pos;							// ポリゴン表示位置の中心座標
	D3DXVECTOR3 rot;							// ポリゴンの回転角
	int nNumBlockX, nNumBlockY;					// ブロック数
	int nNumVertex;								// 総頂点数	
	int nNumVertexIndex;						// 総インデックス数
	int nNumPolygon;							// 総ポリゴン数
	float fSizeBlockX, fSizeBlockY;				// ブロックサイズ
} MESH_WALL;

MESH_WALL g_aMeshWall[MAX_MESH_WALL];			// メッシュ壁ワーク
int g_nNumMeshField = 0;						// メッシュ壁の数

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col,
						int nNumBlockX, int nNumBlockY, float fSizeBlockX, float fSizeBlockY)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MESH_WALL *pMesh;

	if(g_nNumMeshField >= MAX_MESH_WALL)
	{
		return E_FAIL;
	}

	// テクスチャの読み込み
	if(!g_pD3DTexture)
	{
		D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
									TEXTURE_FILENAME,		// ファイルの名前
									&g_pD3DTexture);		// 読み込むメモリー
	}

	if (!g_pD3DTexture2)
	{
		D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
			TEXTURE_FILENAME2,		// ファイルの名前
			&g_pD3DTexture2);		// 読み込むメモリー
	}


	pMesh = &g_aMeshWall[g_nNumMeshField];
	g_nNumMeshField++;

	// ポリゴン表示位置の中心座標を設定
	pMesh->pos = pos;

	pMesh->rot = rot;

	// ブロック数の設定
	pMesh->nNumBlockX = nNumBlockX;
	pMesh->nNumBlockY = nNumBlockY;

	// 頂点数の設定
	pMesh->nNumVertex = (nNumBlockX + 1) * (nNumBlockY + 1);

	// インデックス数の設定
	pMesh->nNumVertexIndex = (nNumBlockX + 1) * 2 * nNumBlockY + (nNumBlockY - 1) * 2;

	// ポリゴン数の設定
	pMesh->nNumPolygon = pMesh->nNumVertexIndex - 2;

	// ブロックサイズの設定
	pMesh->fSizeBlockX = fSizeBlockX;
	pMesh->fSizeBlockY = fSizeBlockY;

	// オブジェクトの頂点バッファを生成
    if(FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * pMesh->nNumVertex,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,					// 頂点バッファの使用法　
												FVF_VERTEX_3D,						// 使用する頂点フォーマット
												D3DPOOL_MANAGED,					// リソースのバッファを保持するメモリクラスを指定
												&pMesh->pD3DVtxBuff,				// 頂点バッファインターフェースへのポインタ
												NULL)))								// NULLに設定
	{
        return E_FAIL;
	}

	// オブジェクトのインデックスバッファを生成
    if(FAILED( pDevice->CreateIndexBuffer(sizeof(WORD) * pMesh->nNumVertexIndex,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,					// 頂点バッファの使用法　
												D3DFMT_INDEX16,						// 使用するインデックスフォーマット
												D3DPOOL_MANAGED,					// リソースのバッファを保持するメモリクラスを指定
												&pMesh->pD3DIdxBuff,				// インデックスバッファインターフェースへのポインタ
												NULL)))								// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;
#if 0
		const float texSizeX = 1.0f / pMesh->nNumBlockX;
		const float texSizeY = 1.0f / pMesh->nNumBlockY;
#else
		const float texSizeX = 1.0f;
		const float texSizeY = 1.0f;
#endif

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		pMesh->pD3DVtxBuff->Lock( 0, 0, (void**)&pVtx, 0 );

		for(int nCntVtxY = 0; nCntVtxY < (pMesh->nNumBlockY + 1); nCntVtxY++)
		{
			for(int nCntVtxX = 0; nCntVtxX < (pMesh->nNumBlockX + 1); nCntVtxX++)
			{
				// 頂点座標の設定
				pVtx[nCntVtxY * (pMesh->nNumBlockX + 1) + nCntVtxX].vtx.x = -(pMesh->nNumBlockX / 2.0f) * pMesh->fSizeBlockX + nCntVtxX * pMesh->fSizeBlockX;
				pVtx[nCntVtxY * (pMesh->nNumBlockX + 1) + nCntVtxX].vtx.y = pMesh->nNumBlockY * pMesh->fSizeBlockY - nCntVtxY * pMesh->fSizeBlockY;
				pVtx[nCntVtxY * (pMesh->nNumBlockX + 1) + nCntVtxX].vtx.z = 0.0f;

				// 法線の設定
				pVtx[nCntVtxY * (pMesh->nNumBlockX + 1) + nCntVtxX].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

				// 反射光の設定
				pVtx[nCntVtxY * (pMesh->nNumBlockX + 1) + nCntVtxX].diffuse = col;

				// テクスチャ座標の設定
				pVtx[nCntVtxY * (pMesh->nNumBlockX + 1) + nCntVtxX].tex.x = texSizeX * nCntVtxX;
				pVtx[nCntVtxY * (pMesh->nNumBlockX + 1) + nCntVtxX].tex.y = texSizeY * nCntVtxY;
			}
		}

		// 頂点データをアンロックする
		pMesh->pD3DVtxBuff->Unlock();
	}

	{//インデックスバッファの中身を埋める
		WORD *pIdx;

		// インデックスデータの範囲をロックし、頂点バッファへのポインタを取得
		pMesh->pD3DIdxBuff->Lock( 0, 0, (void**)&pIdx, 0 );

		int nCntIdx = 0;
		for(int nCntVtxY = 0; nCntVtxY < pMesh->nNumBlockY; nCntVtxY++)
		{
			if(nCntVtxY > 0)
			{// 縮退ポリゴンのためのダブりの設定
				pIdx[nCntIdx] = (nCntVtxY + 1) * (pMesh->nNumBlockX + 1);
				nCntIdx++;
			}

			for(int nCntVtxX = 0; nCntVtxX < (pMesh->nNumBlockX + 1); nCntVtxX++)
			{
				pIdx[nCntIdx] = (nCntVtxY + 1) * (pMesh->nNumBlockX + 1) + nCntVtxX;
				nCntIdx++;
				pIdx[nCntIdx] = nCntVtxY * (pMesh->nNumBlockX + 1) + nCntVtxX;
				nCntIdx++;
			}

			if(nCntVtxY < (pMesh->nNumBlockY - 1))
			{// 縮退ポリゴンのためのダブりの設定
				pIdx[nCntIdx] = nCntVtxY * (pMesh->nNumBlockX + 1) + pMesh->nNumBlockX;
				nCntIdx++;
			}
		}

		// インデックスデータをアンロックする
		pMesh->pD3DIdxBuff->Unlock();
	}



	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMeshWall(void)
{
	MESH_WALL *pMesh;
	int nCntMeshField;

	for(nCntMeshField = 0; nCntMeshField < g_nNumMeshField; nCntMeshField++)
	{
		pMesh = &g_aMeshWall[nCntMeshField];

		if(pMesh->pD3DVtxBuff)
		{// 頂点バッファの開放
			pMesh->pD3DVtxBuff->Release();
			pMesh->pD3DVtxBuff = NULL;
		}

		if(pMesh->pD3DIdxBuff)
		{// インデックスバッファの開放
			pMesh->pD3DIdxBuff->Release();
			pMesh->pD3DIdxBuff = NULL;
		}
	}

	if(g_pD3DTexture)
	{// テクスチャの開放
		g_pD3DTexture->Release();
		g_pD3DTexture = NULL;
	}

	if (g_pD3DTexture2)
	{// テクスチャの開放
		g_pD3DTexture2->Release();
		g_pD3DTexture2 = NULL;
	}


	//壁の数をリセット　元の罠
	g_nNumMeshField = 0;
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMeshWall(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTranslate;

	MESH_WALL *pMesh;
	int nCntMeshField;

	// ライティングを無効に
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	for(nCntMeshField = 0; nCntMeshField < g_nNumMeshField; nCntMeshField++)
	{
		pMesh = &g_aMeshWall[nCntMeshField];

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&pMesh->mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, pMesh->rot.y, pMesh->rot.x, pMesh->rot.z);
		D3DXMatrixMultiply(&pMesh->mtxWorld, &pMesh->mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, pMesh->pos.x, pMesh->pos.y, pMesh->pos.z);
		D3DXMatrixMultiply(&pMesh->mtxWorld, &pMesh->mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &pMesh->mtxWorld);

		// 頂点バッファをレンダリングパイプラインに設定
		pDevice->SetStreamSource(0, pMesh->pD3DVtxBuff, 0, sizeof(VERTEX_3D));

		// インデックスバッファをレンダリングパイプラインに設定
		pDevice->SetIndices(pMesh->pD3DIdxBuff);

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		pDevice->SetTexture(0, g_pD3DTexture);

		// ポリゴンの描画
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, pMesh->nNumVertex, 0, pMesh->nNumPolygon);
	}

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// ライティングを有効に
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

