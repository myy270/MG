//=============================================================================
//
// 弾処理 [bullet.cpp]
// Author : 麦英泳
//
//=============================================================================
#include "bullet.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "effect.h"
#include "explosion.h"
#include "player.h"
#include "life.h"
//#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_BULLET			"data/TEXTURE/bullet000.png"	// 読み込むテクスチャファイル名
#define	BULLET_SIZE_X			(50.0f)							// ビルボードの幅
#define	BULLET_SIZE_Y			(50.0f)							// ビルボードの高さ
//#define	VALUE_MOVE_BULLET		(2.0f)							// 移動速度

#define	MAX_BULLET				(128)							// ビルボード最大数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 回転
	D3DXVECTOR3 scale;		// スケール
	D3DXVECTOR3 move;		// 移動量
	float fSizeX;			// 幅
	float fSizeY;			// 高さ
	int nTimer;				// タイマー
	int nIdxShadow;			// 影ID
	bool bUse;				// 使用しているかどうか
} BULLET;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice);
void SetVertexBullet(int nIdxBullet, float fSizeX, float fSizeY);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureBullet = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffBullet = NULL;		// 頂点バッファインターフェースへのポインタ

D3DXMATRIX				g_mtxWorldBullet;				// ワールドマトリックス

BULLET					g_aBullet[MAX_BULLET];			// 弾ワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点情報の作成
	MakeVertexBullet(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
								TEXTURE_BULLET,				// ファイルの名前
								&g_pD3DTextureBullet);	// 読み込むメモリー

	for(int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{//どうせ後もう一度設置するから、ここはどうでもいい
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aBullet[nCntBullet].fSizeX = BULLET_SIZE_X;
		g_aBullet[nCntBullet].fSizeY = BULLET_SIZE_Y;
		g_aBullet[nCntBullet].nTimer = 0;
		g_aBullet[nCntBullet].bUse = false;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBullet(void)
{
	if(g_pD3DTextureBullet != NULL)
	{// テクスチャの開放
		g_pD3DTextureBullet->Release();
		g_pD3DTextureBullet = NULL;
	}

	if(g_pD3DVtxBuffBullet != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffBullet->Release();
		g_pD3DVtxBuffBullet = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBullet(void)
{
	PLAYER *pPlayer;
	D3DXVECTOR3 rotCamera;

	// プレイヤーを取得
	pPlayer = GetPlayer();

	// カメラの回転を取得
	rotCamera = GetRotCamera();

	for(int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if(g_aBullet[nCntBullet].bUse)
		{
			//弾の位置を更新する
			g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
			g_aBullet[nCntBullet].pos.z += g_aBullet[nCntBullet].move.z;

			g_aBullet[nCntBullet].nTimer--;
			if(g_aBullet[nCntBullet].nTimer <= 0)
			{
				//DeleteBullet(nCntBullet);
				DeleteShadow(g_aBullet[nCntBullet].nIdxShadow);
				g_aBullet[nCntBullet].bUse = false;
			}
			else
			{
				// 影の位置更新
				SetPositionShadow(g_aBullet[nCntBullet].nIdxShadow, D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, 0.1f, g_aBullet[nCntBullet].pos.z));

				// エフェクトの設定
				SetEffect(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.65f, 0.05f, 0.85f, 0.50f), 16.0f, 16.0f, 30);//紫
				SetEffect(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.05f, 0.85f, 0.65f, 0.30f), 12.0f, 12.0f, 30);//シアン
				SetEffect(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXCOLOR(0.05f, 0.45f, 0.45f, 0.20f), 6.0f, 6.0f, 30);//シアン


				if (g_aBullet[nCntBullet].pos.x < -640.0f
					|| g_aBullet[nCntBullet].pos.x > 640.0f
					|| g_aBullet[nCntBullet].pos.z < -640.0f
					|| g_aBullet[nCntBullet].pos.z > 640.0f)
				{
					// 爆発の生成
					SetExplosion(g_aBullet[nCntBullet].pos, 40.0f, 40.0f);//一つの引数を省略した

					DeleteBullet(nCntBullet);

					// SE再生
					//PlaySound(SOUND_LABEL_SE_EXPLOSION);
				}

				float fSizeX = 8.0f + (g_aBullet[nCntBullet].pos.y - 4.0f) * 0.05f;
				if (fSizeX < 8.0f)
				{
					fSizeX = 8.0f;
				}
				float fSizeY = 8.0f + (g_aBullet[nCntBullet].pos.y - 4.0f) * 0.05f;
				if (fSizeY < 8.0f)
				{
					fSizeY = 8.0f;
				}

				SetVertexShadow(g_aBullet[nCntBullet].nIdxShadow, fSizeX, fSizeY);//影の大きさを設定

				float colA = (200.0f - (g_aBullet[nCntBullet].pos.y - 4.0f)) / 400.0f;
				if (colA < 0.0f)
				{
					colA = 0.0f;
				}
				SetColorShadow(g_aBullet[nCntBullet].nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));//影の透明値を設定
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView,mtxScale,mtxTranslate;

	// ライティングを無効に
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// αテストを有効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for(int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if(g_aBullet[nCntBullet].bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldBullet);

			// ビューマトリックスを取得
			mtxView = GetMtxView();

			g_mtxWorldBullet._11 = mtxView._11;
			g_mtxWorldBullet._12 = mtxView._21;
			g_mtxWorldBullet._13 = mtxView._31;
			g_mtxWorldBullet._21 = mtxView._12;
			g_mtxWorldBullet._22 = mtxView._22;
			g_mtxWorldBullet._23 = mtxView._32;
			g_mtxWorldBullet._31 = mtxView._13;
			g_mtxWorldBullet._32 = mtxView._23;
			g_mtxWorldBullet._33 = mtxView._33;

			// スケールを反映
			D3DXMatrixScaling(&mtxScale, g_aBullet[nCntBullet].scale.x, g_aBullet[nCntBullet].scale.y, g_aBullet[nCntBullet].scale.z);
			D3DXMatrixMultiply(&g_mtxWorldBullet, &g_mtxWorldBullet, &mtxScale);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldBullet, &g_mtxWorldBullet, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBullet);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffBullet, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureBullet);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntBullet * 4), NUM_POLYGON);//第二引数を注意する
		}
	}

	// ライティングを有効に
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// αテストを無効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if( FAILED( pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_BULLET,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,							// 頂点バッファの使用法　
												FVF_VERTEX_3D,								// 使用する頂点フォーマット
												D3DPOOL_MANAGED,							// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffBullet,						// 頂点バッファインターフェースへのポインタ
												NULL)))										// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pVtx += 4)
		{
			// 頂点座標の設定　順位が間違ってる　どうせ後もう一度設置するから、ここはどうでもいい
			pVtx[0].vtx = D3DXVECTOR3(-BULLET_SIZE_X / 2, -BULLET_SIZE_Y / 2, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(BULLET_SIZE_X / 2, -BULLET_SIZE_Y / 2, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(-BULLET_SIZE_X / 2, BULLET_SIZE_Y / 2, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(BULLET_SIZE_X / 2, BULLET_SIZE_Y / 2, 0.0f);

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
		g_pD3DVtxBuffBullet->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBullet(int nIdxBullet, float fSizeX, float fSizeY)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxBullet * 4);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-fSizeX / 2, fSizeY / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(fSizeX / 2, -fSizeY / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX / 2, fSizeY / 2, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffBullet->Unlock();
	}
}

//=============================================================================
// 弾の設定
//=============================================================================
int SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fSizeX, float fSizeY, int nTimer)
{
	int nIdxBullet = -1;

	for(int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if(!g_aBullet[nCntBullet].bUse)
		{
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aBullet[nCntBullet].scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].fSizeX = fSizeX;
			g_aBullet[nCntBullet].fSizeY = fSizeY;
			g_aBullet[nCntBullet].nTimer = nTimer;
			g_aBullet[nCntBullet].bUse = true;

			// 影の設定
			g_aBullet[nCntBullet].nIdxShadow = SetShadow(pos, 8.0f, 8.0f);		// 影の設定

			// 頂点座標の設定
			SetVertexBullet(nCntBullet, fSizeX, fSizeY);

			nIdxBullet = nCntBullet;

			break;
		}
	}

	return nIdxBullet;
}

//=============================================================================
// 弾の削除
//=============================================================================
void DeleteBullet(int nIdxBullet)
{
	if(nIdxBullet >= 0 && nIdxBullet < MAX_BULLET)
	{
		DeleteShadow(g_aBullet[nIdxBullet].nIdxShadow);
		g_aBullet[nIdxBullet].bUse = false;
	}
}

