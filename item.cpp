//=============================================================================
//
// アイテム処理 [item.cpp]
// Author : 麦英泳
//
//=============================================================================
#include "item.h"
#include "shadow.h"
#include "input.h"
#include "player.h"
#include "enemy.h"
#include "timer.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VALUE_ROTATE_ITEM		(D3DX_PI * 0.025f)			// 回転速度
#define	ITEM_RADIUS				(10.0f)						// 半径

#define	ITEMLOGO_SIZE_X			(65.0f)							// ライフの数字の幅
#define	ITEMLOGO_SIZE_Y			(65.0f)							// ライフの数字の高さ

#define	ITEMLOGO_POS_X			(20.0f)							// ライフの表示基準位置Ｘ座標
#define	ITEMLOGO_POS_Y			(95.0f)							// ライフの表示基準位置Ｙ座標

#define	DROP_TIME				(420)							// 落下アイテムの間隔時間　1秒＝60
#define	DROP_HIGHT				(1800.0f)						// 落下アイテムの初期高さ
#define	DROP_SPEED				(15.0f)							// 落下アイテムの落下速度


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexItemLogo(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureItem[ITEMTYPE_MAX];	// テクスチャ読み込み場所
LPD3DXMESH			g_pMeshItem[ITEMTYPE_MAX];			// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		g_pD3DXMatBuffItem[ITEMTYPE_MAX];	// メッシュのマテリアル情報を格納
DWORD				g_aNumMatItem[ITEMTYPE_MAX];			// 属性情報の総数

D3DXMATRIX			g_mtxWorldItem;				// ワールドマトリックス

ITEM				g_aItem[MAX_ITEM];			// アイテムワーク

bool g_dropItem;//アイテム落下するか

bool g_dropReady;//落下するアイテムはもう生成したか

int g_itemIndex;//落下するアイテムのインデクス

LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffItemLogo = NULL;		// 頂点バッファインターフェースへのポインタ



const char *c_aFileNameItem[ITEMTYPE_MAX] =
{
	"data/MODEL/coin.x",			// コイン
	"data/MODEL/iceBlock.x",		// アイスブロック

};

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	MakeVertexItemLogo(pDevice);

	for(int nCntItemType = 0; nCntItemType < ITEMTYPE_MAX; nCntItemType++)
	{
		g_pD3DTextureItem[nCntItemType] = NULL;
		g_pMeshItem[nCntItemType] = NULL;
		g_pD3DXMatBuffItem[nCntItemType] = NULL;

		// Xファイルの読み込み
		if(FAILED(D3DXLoadMeshFromX(c_aFileNameItem[nCntItemType],
									D3DXMESH_SYSTEMMEM,
									pDevice,
									NULL,
									&g_pD3DXMatBuffItem[nCntItemType],
									NULL,
									&g_aNumMatItem[nCntItemType],
									&g_pMeshItem[nCntItemType])))
		{
			//return E_FAIL;//コインが次のステージに残すbug
		}

#if 0
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,									// デバイスへのポインタ
									TEXTURE_ITEM,						// ファイルの名前
									&g_pD3DTextureItem[nCntItemType]);	// 読み込むメモリー
#endif
	}

	for(int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].fRadius = 0.0f;
		g_aItem[nCntItem].nIdxShadow = -1;
		g_aItem[nCntItem].nType = ITEMTYPE_COIN;
		g_aItem[nCntItem].bUse = false;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitItem(void)
{
	for(int nCntItemType = 0; nCntItemType < ITEMTYPE_MAX; nCntItemType++)
	{
		if(g_pD3DTextureItem[nCntItemType] != NULL)
		{// テクスチャの開放
			g_pD3DTextureItem[nCntItemType]->Release();
			g_pD3DTextureItem[nCntItemType] = NULL;
		}

		if(g_pMeshItem[nCntItemType] != NULL)
		{// メッシュの開放
			g_pMeshItem[nCntItemType]->Release();
			g_pMeshItem[nCntItemType] = NULL;
		}

		if(g_pD3DXMatBuffItem[nCntItemType] != NULL)
		{// マテリアルの開放
			g_pD3DXMatBuffItem[nCntItemType]->Release();
			g_pD3DXMatBuffItem[nCntItemType] = NULL;
		}
	}

	if (g_pD3DVtxBuffItemLogo != NULL)
	{// テクスチャの開放
		g_pD3DVtxBuffItemLogo->Release();
		g_pD3DVtxBuffItemLogo = NULL;
	}


	
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateItem(void)
{

#ifdef _DEBUG
	if (GetKeyboardPress(DIK_3))
	{
		g_dropItem = true;
	}
#endif

	if ((GetTimer() % DROP_TIME == 0)&&(GetTimer() != 0))
	{
		g_dropItem = true;
	}

	
	DropItem();
	


	for(int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if(g_aItem[nCntItem].bUse)
		{
			g_aItem[nCntItem].rot.y += VALUE_ROTATE_ITEM;//毎フレーム自回転4.5度
			if(g_aItem[nCntItem].rot.y > D3DX_PI)
			{
				g_aItem[nCntItem].rot.y -= D3DX_PI * 2.0f;
			}

			// 影の位置設定
			SetPositionShadow(g_aItem[nCntItem].nIdxShadow, D3DXVECTOR3(g_aItem[nCntItem].pos.x, 0.1f, g_aItem[nCntItem].pos.z));

			float fSizeX = 20.0f + (g_aItem[nCntItem].pos.y - 10.0f) * 0.05f;
			if(fSizeX < 20.0f)
			{
				fSizeX = 20.0f;
			}
			float fSizeY = 20.0f + (g_aItem[nCntItem].pos.y - 10.0f) * 0.05f;
			if(fSizeY < 20.0f)
			{
				fSizeY = 20.0f;
			}

			SetVertexShadow(g_aItem[nCntItem].nIdxShadow, fSizeX, fSizeY);

			float colA = (200.0f - (g_aItem[nCntItem].pos.y - 10.0f)) / 400.0f;
			if(colA < 0.0f)
			{
				colA = 0.0f;
			}
			SetColorShadow(g_aItem[nCntItem].nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));
		}
	}


}

//=============================================================================
// 描画処理
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;

	D3DMATERIAL9 matDef;
	pDevice->GetMaterial(&matDef);

	for(int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if(g_aItem[nCntItem].bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldItem);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aItem[nCntItem].rot.y, g_aItem[nCntItem].rot.x, g_aItem[nCntItem].rot.z);
			D3DXMatrixMultiply(&g_mtxWorldItem, &g_mtxWorldItem, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, g_aItem[nCntItem].pos.x, g_aItem[nCntItem].pos.y, g_aItem[nCntItem].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldItem, &g_mtxWorldItem, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldItem);

			D3DXMATERIAL *pD3DXMat = (D3DXMATERIAL*)g_pD3DXMatBuffItem[g_aItem[nCntItem].nType]->GetBufferPointer();

			for(int nCntMat = 0; nCntMat < (int)g_aNumMatItem[g_aItem[nCntItem].nType]; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);//ポインターが配列になる

				// テクスチャの設定
				pDevice->SetTexture(0, g_pD3DTextureItem[g_aItem[nCntItem].nType]);

				// 描画
				g_pMeshItem[g_aItem[nCntItem].nType]->DrawSubset(nCntMat);
			}
		}
	}
	
	pDevice->SetMaterial(&matDef);

	//アイテムUIの描画
	{
		//プレイヤーの方
		if (GetPlayer()->holdItem != ITEMTYPE_COIN)
		{
			if (GetPlayer()->holdItem == ITEMTYPE_ICEBLOCK)
			{
				//頂点バッファの中身を埋める
				VERTEX_2D *pVtx;

				// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
				g_pD3DVtxBuffItemLogo->Lock(0, 0, (void**)&pVtx, 0);

				// 頂点座標の設定
				pVtx[0].vtx = D3DXVECTOR3(ITEMLOGO_POS_X, ITEMLOGO_POS_Y, 0.0f);
				pVtx[1].vtx = D3DXVECTOR3(ITEMLOGO_POS_X + ITEMLOGO_SIZE_X, ITEMLOGO_POS_Y, 0.0f);
				pVtx[2].vtx = D3DXVECTOR3(ITEMLOGO_POS_X, ITEMLOGO_POS_Y + ITEMLOGO_SIZE_Y, 0.0f);
				pVtx[3].vtx = D3DXVECTOR3(ITEMLOGO_POS_X + ITEMLOGO_SIZE_X, ITEMLOGO_POS_Y + ITEMLOGO_SIZE_Y, 0.0f);

				// 頂点データをアンロックする
				g_pD3DVtxBuffItemLogo->Unlock();


				//ItemLogoの描画
				// 頂点バッファをデバイスのデータストリームにバインド
				pDevice->SetStreamSource(0, g_pD3DVtxBuffItemLogo, 0, sizeof(VERTEX_2D));

				// 頂点フォーマットの設定
				pDevice->SetFVF(FVF_VERTEX_2D);

				// テクスチャの設定
				pDevice->SetTexture(0, NULL);

				// ポリゴンの描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
			}
		}

		//エネミーの方
		if (GetEnemy()->holdItem != ITEMTYPE_COIN)
		{
			if (GetEnemy()->holdItem == ITEMTYPE_ICEBLOCK)
			{
				//頂点バッファの中身を埋める
				VERTEX_2D *pVtx;

				// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
				g_pD3DVtxBuffItemLogo->Lock(0, 0, (void**)&pVtx, 0);

				// 頂点座標の設定
				pVtx[0].vtx = D3DXVECTOR3(SCREEN_WIDTH - ITEMLOGO_POS_X - ITEMLOGO_SIZE_X, ITEMLOGO_POS_Y, 0.0f);
				pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH - ITEMLOGO_POS_X, ITEMLOGO_POS_Y, 0.0f);
				pVtx[2].vtx = D3DXVECTOR3(SCREEN_WIDTH - ITEMLOGO_POS_X - ITEMLOGO_SIZE_X, ITEMLOGO_POS_Y + ITEMLOGO_SIZE_Y, 0.0f);
				pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH - ITEMLOGO_POS_X, ITEMLOGO_POS_Y + ITEMLOGO_SIZE_Y, 0.0f);

				// 頂点データをアンロックする
				g_pD3DVtxBuffItemLogo->Unlock();


				//ItemLogoの描画
				// 頂点バッファをデバイスのデータストリームにバインド
				pDevice->SetStreamSource(0, g_pD3DVtxBuffItemLogo, 0, sizeof(VERTEX_2D));

				// 頂点フォーマットの設定
				pDevice->SetFVF(FVF_VERTEX_2D);

				// テクスチャの設定
				pDevice->SetTexture(0, NULL);

				// ポリゴンの描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
			}
		}
	}
}

//=============================================================================
// アイテムの設定
//=============================================================================
int SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType,bool shadow)
{
	int itemIndex = -1;
	for(int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if(!g_aItem[nCntItem].bUse)
		{
			g_aItem[nCntItem].pos = pos;
			g_aItem[nCntItem].rot = rot;
			g_aItem[nCntItem].fRadius = ITEM_RADIUS;
			g_aItem[nCntItem].nType = nType;
			g_aItem[nCntItem].bUse = true;

			if (shadow)
			{
				// 影の設定
				g_aItem[nCntItem].nIdxShadow = SetShadow(g_aItem[nCntItem].pos, g_aItem[nCntItem].fRadius * 2.0f, g_aItem[nCntItem].fRadius * 2.0f);
			}

			itemIndex = nCntItem;
			break;
		}
	}
	return itemIndex;
}

//=============================================================================
// アイテムの削除
//=============================================================================
void DeleteItem(int nIdxItem)
{
	if(nIdxItem >= 0 && nIdxItem < MAX_ITEM)
	{
		DeleteShadow(g_aItem[nIdxItem].nIdxShadow);
		g_aItem[nIdxItem].bUse = false;
	}
}

//=============================================================================
// アイテムの取得
//=============================================================================
ITEM *GetItem(void)
{
	return &g_aItem[0];
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexItemLogo(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,		// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,							// 頂点バッファの使用法　
		FVF_VERTEX_2D,								// 使用する頂点フォーマット
		D3DPOOL_MANAGED,							// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffItemLogo,							// 頂点バッファインターフェースへのポインタ
		NULL)))										// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffItemLogo->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntPlace = 0; nCntPlace < 1; nCntPlace++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(ITEMLOGO_POS_X, ITEMLOGO_POS_Y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(ITEMLOGO_POS_X + ITEMLOGO_SIZE_X, ITEMLOGO_POS_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(ITEMLOGO_POS_X, ITEMLOGO_POS_Y + ITEMLOGO_SIZE_Y, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(ITEMLOGO_POS_X + ITEMLOGO_SIZE_X, ITEMLOGO_POS_Y + ITEMLOGO_SIZE_Y, 0.0f);

			// rhwの設定
			pVtx[0].rhw =
				pVtx[1].rhw =
				pVtx[2].rhw =
				pVtx[3].rhw = 1.0f;

			// 反射光の設定
			pVtx[0].diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// 頂点データをアンロックする
		g_pD3DVtxBuffItemLogo->Unlock();
	}

	return S_OK;
}


void Freeze(OBJECT target)
{
	if (target == OBJECT_ENEMY)
	{
		if (GetPlayer()->holdItem == ITEMTYPE_ICEBLOCK)
		{
			if (GetEnemy()->state == NORMAL)
			{
				GetEnemy()->state = FROZEN;
				GetEnemy()->stateTime = 180;//3秒

				GetPlayer()->holdItem = ITEMTYPE_COIN;
			}

		}
	}
	else if (target == OBJECT_PLAYER)
	{
		if (GetEnemy()->holdItem == ITEMTYPE_ICEBLOCK)
		{
			if (GetPlayer()->state == NORMAL)
			{
				GetPlayer()->state = FROZEN;
				GetPlayer()->stateTime = 180;//3秒

				GetEnemy()->holdItem = ITEMTYPE_COIN;
			}

		}
	}
	
}

void DropItem()
{

	if (g_dropItem)
	{
		if (!g_dropReady)
		{
			float fPosX, fPosY, fPosZ;

			fPosX = (float)(rand() % 12000) / 10.0f - 600.0f;//-600.0f~600.0f
			fPosY = DROP_HIGHT;//アイテムの投下高さ
			fPosZ = (float)(rand() % 12000) / 10.0f - 600.0f;
			g_itemIndex = SetItem(D3DXVECTOR3(fPosX, fPosY, fPosZ), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_ICEBLOCK, false);
			g_dropReady = true;
		}
		else
		{
			if (g_itemIndex != -1)
			{
				(GetItem() + g_itemIndex)->pos.y -= DROP_SPEED;

				if ((GetItem() + g_itemIndex)->pos.y <= 15.0f)
				{//アイテムの着地高さ
					(GetItem() + g_itemIndex)->pos.y = 15.0f;

					g_dropItem = false;
					g_dropReady = false;
				}
			}
		}
	}

}

