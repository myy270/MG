//=============================================================================
//
// 星型地面の処理 [field_star.cpp]
// Author : HAL東京　GP11C295　樋沼　勇太
//
//=============================================================================
#include "player.h"
#include "input.h"
#include "enemy.h"
#include "bullet.h"
#include "Hitjudge.h"
#include "field_star.h"
#include "fade.h"
#include "main.h"

#define TEXTURE_STAR  "data/TEXTURE/field003.jpg"

//*************キャラクターデータ変数の用意*****************************
MODEL	FieldStar[NUM_FIELD];			//プレイヤーキャラクタ構造体

using namespace warpzoneNS;
extern PLAYER g_player;
extern ENEMY g_enemy;
//extern int g_next_stage;
extern STAGE_CLEAR g_stage_clear;

//*********************モデルデータファイル名配列********************
const char* FieldStarModelData[] = 
{
	"data/MODEL/star.x",
	"data/MODEL/wrap2.x"
};


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitFieldStar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3	temp;
	D3DXMATRIX mtxScl,/*mtxRot,*/ mtxTranslate;

	// キャラクタの位置・回転・スケールなどの初期設定
	for (int i = 0; i < NUM_FIELD; i++)
	{

		initModelPos(&FieldStar[i].pos, i);
		FieldStar[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//

		FieldStar[i].use = TRUE;
		FieldStar[i].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&FieldStar[i].mtxWorld);

		// スケールを行列にしてワールド行列（始めは単位行列）と乗算
		temp = FieldStar[i].scl;
		D3DXMatrixScaling(&mtxScl, temp.x, temp.y, temp.z);
		D3DXMatrixMultiply(&FieldStar[i].mtxWorld, &FieldStar[i].mtxWorld, &mtxScl);

		// 回転を行列にしてワールド行列と乗算
		temp = FieldStar[i].rot;
		D3DXMatrixRotationYawPitchRoll(&FieldStar[i].mtxRot, temp.y, temp.x, temp.z);
		D3DXMatrixMultiply(&FieldStar[i].mtxWorld, &FieldStar[i].mtxWorld, &FieldStar[i].mtxRot);

		// 移動を行列にしてワールド行列と乗算
		temp =FieldStar[i].pos;
		D3DXMatrixTranslation(&mtxTranslate, temp.x, temp.y, temp.z);
		D3DXMatrixMultiply(&FieldStar[i].mtxWorld, &FieldStar[i].mtxWorld, &mtxTranslate);

		// 完成したワールドマトリックスをDirectXへセット
		pDevice->SetTransform(D3DTS_WORLD, &FieldStar[i].mtxWorld);

		//モデルデータの初期設定
		for (int i = 0; i < NUM_FIELD; i++)
		{
			if (i == 0)
			{
				initModeldata(&FieldStar[i].model3d, FieldStarModelData[0]);
			}
			else
			{
				initModeldata(&FieldStar[i].model3d, FieldStarModelData[1]);
			}
		}
	}


	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
		TEXTURE_STAR,						// ファイルの名前
		&FieldStar[0].model3d.pD3DTextureModel);	// 読み込むメモリー
		
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitFieldStar(void)
{


	for(int i=0; i< NUM_SKYMODEL; i++)
	{
		if( NULL !=FieldStar[i].model3d.pD3DTextureModel)
		{
			FieldStar[i].model3d.pD3DTextureModel->Release();
			FieldStar[i].model3d.pD3DTextureModel = NULL;
		}

		if( NULL !=FieldStar[i].model3d.pMesh)
		{
			FieldStar[i].model3d.pMesh->Release();
			FieldStar[i].model3d.pMesh = NULL;
		}

		if( NULL !=FieldStar[i].model3d.pMatBuff)
		{
			FieldStar[i].model3d.pMatBuff->Release();
			FieldStar[i].model3d.pMatBuff = NULL;
		}
	}


}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateFieldStar(void)
{
	if (GetMode() == MODE_GAME)
	{
		for (int i = 1; i < NUM_FIELD; i++)
		{
			playerWarp(i);
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawFieldStarModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl,/*mtxRot,*/ mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	// 現在設定されているマテリアルを取得して保存
	pDevice->GetMaterial(&matDef);

	//*************************全てのキャラクターを表示************************
	for(int i=0; i<NUM_FIELD; i++)
	{
		D3DXVECTOR3	temp;

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&FieldStar[i].mtxWorld);

		// スケールを行列にしてワールド行列（始めは単位行列）と乗算
		temp = FieldStar[i].scl;
		D3DXMatrixScaling(&mtxScl, temp.x, temp.y, temp.z);
		D3DXMatrixMultiply(&FieldStar[i].mtxWorld, &FieldStar[i].mtxWorld, &mtxScl);

		// 回転を行列にしてワールド行列と乗算
		temp = FieldStar[i].rot;
		D3DXMatrixRotationYawPitchRoll(&FieldStar[i].mtxRot, temp.y, temp.x, temp.z);
		D3DXMatrixMultiply(&FieldStar[i].mtxWorld, &FieldStar[i].mtxWorld, &FieldStar[i].mtxRot);

		// 移動を行列にしてワールド行列と乗算
		temp =FieldStar[i].pos;
		D3DXMatrixTranslation(&mtxTranslate, temp.x, temp.y, temp.z);
		D3DXMatrixMultiply(&FieldStar[i].mtxWorld, &FieldStar[i].mtxWorld, &mtxTranslate);

		// 完成したワールドマトリックスをDirectXへセット
		pDevice->SetTransform(D3DTS_WORLD, &FieldStar[i].mtxWorld);

		// モデルのマテリアル情報に対するポインタを取得
		pD3DXMat = (D3DXMATERIAL*)FieldStar[i].model3d.pMatBuff->GetBufferPointer();

		//モデルの情報に従ってモデルを構成するオブジェクトの数だけ繰り返す
		for (int nCntMat = 0; nCntMat < (int)FieldStar[i].model3d.nNumMat; nCntMat++)
		{
			// オブジェクトのマテリアルの設定
			pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

			// オブジェクトのテクスチャの設定
			pDevice->SetTexture(0, FieldStar[i].model3d.pD3DTextureModel);

			// オブジェクトの描画
			FieldStar[i].model3d.pMesh->DrawSubset(nCntMat);
		}
	}

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);

}

void playerWarp( int i)
{
	D3DXVECTOR2 A = D3DXVECTOR2(g_player.part[0].srt.pos.x, g_player.part[0].srt.pos.z);
	D3DXVECTOR2 B = D3DXVECTOR2(FieldStar[i].pos.x, FieldStar[i].pos.z);
	if (distanceVec2(A, B) <= into_warpzone /*&& checkClearStage(i) == TRUE*/)
	{

		if (i == 1)
		{
			SetFade(FADE_OUT);
		}
		
		
	}
}

bool checkClearStage(int i)
{
	if (g_stage_clear.stage01 == TRUE && i == STAGE01)
	{
		return FALSE;
	}

	return TRUE;
}

float distanceVec2(D3DXVECTOR2 A, D3DXVECTOR2 B)
{
	D3DXVECTOR2 dis;
	dis = B - A;
	return D3DXVec2Length(&dis);
}

 void initModelPos(D3DXVECTOR3* pos, int i)
{
	switch(i)
	{
	case 0:
		*pos = warp0;
		break;
	case 1:
		*pos = warp1;
		break;
	case 2:
		*pos = warp2;
		break;
	case 3:
		*pos = warp3;
		break;
	case 4:
		*pos = warp4;
		break;
	case 5:
		*pos = warp5;
		break;
	}
}

HRESULT initModeldata(MODEL3D* model3d, const char* modeldata)
 {
	 LPDIRECT3DDEVICE9 pDevice = GetDevice();

	 model3d->pD3DTextureModel = NULL;
	 model3d->pMesh = NULL;
	 model3d->pMatBuff = NULL;
	 model3d->nNumMat = 0;

	 if (D3D_OK != D3DXLoadMeshFromX(modeldata,			// 読み込むモデルファイル名(Xファイル)
		 D3DXMESH_SYSTEMMEM,		// メッシュの作成オプションを指定
		 pDevice,				// IDirect3DDevice9インターフェイスへのポインタ
		 NULL,					// 隣接性データを含むバッファへのポインタ
		 &model3d->pMatBuff,	// マテリアルデータを含むバッファへのポインタ
		 NULL,			 // エフェクトインスタンスの配列を含むバッファへのポインタ
		 &model3d->nNumMat,		// D3DXMATERIAL構造体の数
		 &model3d->pMesh))	// ID3DXMeshインターフェイスへのポインタのアドレス
	 {
		 return E_FAIL;
	 }
	 return S_OK;
 }

void returnClearTrue(MODE mode)
{
	if (mode = STAGE01)
	{
		g_stage_clear.stage01 = TRUE;
	}

}