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


//*************キャラクターデータ変数の用意*****************************
PLAYER	FieldStar[NUM_SKY];			//プレイヤーキャラクタ構造体

//*********************モデルデータファイル名配列********************
const char* FieldStarModelData[] = 
{
	"data/MODEL/sample_field.x",
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
	for (int i = 0; i < NUM_SKY; i++)
	{

			FieldStar[i].part[0].srt.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//
			FieldStar[i].part[0].srt.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//

			FieldStar[i].part[0].use = TRUE;
			FieldStar[i].part[0].srt.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&FieldStar[i].part[0].mtxWorld);

			// スケールを行列にしてワールド行列（始めは単位行列）と乗算
			temp = FieldStar[i].part[0].srt.scl;
			D3DXMatrixScaling(&mtxScl, temp.x, temp.y, temp.z);
			D3DXMatrixMultiply(&FieldStar[i].part[0].mtxWorld, &FieldStar[i].part[0].mtxWorld, &mtxScl);

			// 回転を行列にしてワールド行列と乗算
			temp = FieldStar[i].part[0].srt.rot;
			D3DXMatrixRotationYawPitchRoll(&FieldStar[i].part[0].mtxRot, temp.y, temp.x, temp.z);
			D3DXMatrixMultiply(&FieldStar[i].part[0].mtxWorld, &FieldStar[i].part[0].mtxWorld, &FieldStar[i].part[0].mtxRot);

			// 移動を行列にしてワールド行列と乗算
			temp =FieldStar[i].part[0].srt.pos;
			D3DXMatrixTranslation(&mtxTranslate, temp.x, temp.y, temp.z);
			D3DXMatrixMultiply(&FieldStar[i].part[0].mtxWorld, &FieldStar[i].part[0].mtxWorld, &mtxTranslate);

			// 完成したワールドマトリックスをDirectXへセット
			pDevice->SetTransform(D3DTS_WORLD, &FieldStar[i].part[0].mtxWorld);


		//モデルデータの初期設定
		for (int i = 0; i < NUM_SKYMODEL; i++)
		{
			FieldStar[i].part[0].pD3DTextureModel = NULL;
			FieldStar[i].part[0].pMesh = NULL;
			FieldStar[i].part[0].pMatBuff = NULL;
			FieldStar[i].part[0].nNumMat = 0;


			if (D3D_OK != D3DXLoadMeshFromX(FieldStarModelData[0],			// 読み込むモデルファイル名(Xファイル)
												D3DXMESH_SYSTEMMEM,		// メッシュの作成オプションを指定
												pDevice,				// IDirect3DDevice9インターフェイスへのポインタ
												NULL,					// 隣接性データを含むバッファへのポインタ
												&FieldStar[0].part[0].pMatBuff,	// マテリアルデータを含むバッファへのポインタ
												NULL,				// エフェクトインスタンスの配列を含むバッファへのポインタ
												&FieldStar[0].part[0].nNumMat,		// D3DXMATERIAL構造体の数
												&FieldStar[0].part[0].pMesh))	// ID3DXMeshインターフェイスへのポインタのアドレス
			{
				return E_FAIL;
			}
			
		}
	}


	// テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
	//	TEXTURE_SKY,						// ファイルの名前
	//	&FieldStar[0].part[0].pD3DTextureModel);	// 読み込むメモリー
		
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitFieldStar(void)
{


	for(int i=0; i< NUM_SKYMODEL; i++)
	{
		if( NULL !=FieldStar[i].part[0].pD3DTextureModel)
		{
			FieldStar[i].part[0].pD3DTextureModel->Release();
			FieldStar[i].part[0].pD3DTextureModel = NULL;
		}

		if( NULL !=FieldStar[i].part[0].pMesh)
		{
			FieldStar[i].part[0].pMesh->Release();
			FieldStar[i].part[0].pMesh = NULL;
		}

		if( NULL !=FieldStar[i].part[0].pMatBuff)
		{
			FieldStar[i].part[0].pMatBuff->Release();
			FieldStar[i].part[0].pMatBuff = NULL;
		}
	}


}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateFieldStar(void)
{

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
	for(int i=0; i<NUM_SKY; i++)
	{
		D3DXVECTOR3	temp;

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&FieldStar[i].part[0].mtxWorld);

		// スケールを行列にしてワールド行列（始めは単位行列）と乗算
		temp = FieldStar[i].part[0].srt.scl;
		D3DXMatrixScaling(&mtxScl, temp.x, temp.y, temp.z);
		D3DXMatrixMultiply(&FieldStar[i].part[0].mtxWorld, &FieldStar[i].part[0].mtxWorld, &mtxScl);

		// 回転を行列にしてワールド行列と乗算
		temp = FieldStar[i].part[0].srt.rot;
		D3DXMatrixRotationYawPitchRoll(&FieldStar[i].part[0].mtxRot, temp.y, temp.x, temp.z);
		D3DXMatrixMultiply(&FieldStar[i].part[0].mtxWorld, &FieldStar[i].part[0].mtxWorld, &FieldStar[i].part[0].mtxRot);

		// 移動を行列にしてワールド行列と乗算
		temp =FieldStar[i].part[0].srt.pos;
		D3DXMatrixTranslation(&mtxTranslate, temp.x, temp.y, temp.z);
		D3DXMatrixMultiply(&FieldStar[i].part[0].mtxWorld, &FieldStar[i].part[0].mtxWorld, &mtxTranslate);

		// 完成したワールドマトリックスをDirectXへセット
		pDevice->SetTransform(D3DTS_WORLD, &FieldStar[i].part[0].mtxWorld);

		// モデルのマテリアル情報に対するポインタを取得
		pD3DXMat = (D3DXMATERIAL*)FieldStar[i].part[0].pMatBuff->GetBufferPointer();

		//モデルの情報に従ってモデルを構成するオブジェクトの数だけ繰り返す
		for (int nCntMat = 0; nCntMat < (int)FieldStar[i].part[0].nNumMat; nCntMat++)
		{
			// オブジェクトのマテリアルの設定
			pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

			// オブジェクトのテクスチャの設定
			pDevice->SetTexture(0, FieldStar[i].part[0].pD3DTextureModel);

			// オブジェクトの描画
			FieldStar[i].part[0].pMesh->DrawSubset(nCntMat);
		}
	}

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);

}

