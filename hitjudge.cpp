//=============================================================================
//
// 当たり判定処理 [hitjudge.cpp]
// Author : HAL東京　GP11C295　樋沼　勇太
//
//=============================================================================
#include "player.h"
#include "hitjudge.h"
#include "enemy.h"
//#include "field_star.h"

// 壁の当たり判定
D3DXVECTOR3 CollideGeo(D3DXVECTOR3* m_A, D3DXVECTOR3 move, LPD3DXMESH* pThingB3D)
{
	//当たり判定
	FLOAT fDistance = 0.0f;
	D3DXVECTOR3	 vNormal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMATRIX tempMatrix;
	D3DXMatrixIdentity(&tempMatrix);

	if (Collide(*m_A, move, &fDistance, &vNormal, pThingB3D, &tempMatrix) == TRUE && fDistance <= HIT_WALL_FIRST)
	{
		//当たり状態なので、滑らせる
		move = Slip(move, vNormal);//滑りベクトルを計算

		//滑りベクトル先の地面突起とのレイ判定 ２重に判定	
		if (Collide(*m_A, move, &fDistance, &vNormal, pThingB3D, &tempMatrix) && fDistance <= HIT_WALL_SECOND)
		{
			//２段目の当たり状態なので、滑らせる おそらく上がる方向		
			move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//滑りベクトルを計算
		}
	}

	return move;
}

void AnimePosAndHitjudge(D3DXVECTOR3 *af_vec, D3DXMATRIX world, D3DXMATRIX buff, D3DXVECTOR3 bf_vec, D3DXVECTOR3 move_vec, float motionTime, float part , PART opponent,  float length)
{
	D3DXVECTOR3 move;
	D3DXVECTOR3 current_pos = *af_vec;

	// Position
	FrameFeedVec(af_vec, bf_vec, move_vec, motionTime);

	move = ReturnLocalToWorldVec(world, buff, current_pos);
	current_pos = ReturnLocalToWorldVec(world, buff, *af_vec);
	move = move - current_pos;

	for (int i = 0; i < part; i++)
	{
		CollideAttack(&current_pos, move, &opponent, length);
	}
}

D3DXVECTOR3 ReturnLocalToWorldVec(D3DXMATRIX world, D3DXMATRIX buff, D3DXVECTOR3 local_pos)
{
	D3DXMatrixIdentity(&world);
	D3DXMatrixMultiply(&world, &world, &buff);
	D3DXVec3TransformCoord(&local_pos, &local_pos, &world);

	return local_pos;
}

// 武器の当たり判定
// ヘッダーのコメントみて
// sword_pos, sword_move, enemymesh
BOOL CollideAttack(D3DXVECTOR3* m_A, D3DXVECTOR3 move, PART* part, float length)
{
	//当たり判定
	FLOAT fDistance = 0.0f;
	D3DXVECTOR3	 vNormal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (Collide(*m_A, move, &fDistance, &vNormal, &part->pMesh, &part->mtxWorld) == TRUE && fDistance <= length)
	{
		return TRUE;
	}

	return FALSE;
}


///////////////////////////////////↓　使わない///////////////////////////////////////

//=============================================
// OBJECT3D構造体同士の　球体当たり判定
//==============================================
//BOOL HitjudgeForModel(MODEL *obj1, MODEL *obj2)
//{
//	//自身の情報を用意
//	float	obj1rad = obj1->m_Radius.x;
//	D3DXVECTOR3 obj1pos = obj1->pos;
//
//	//対象の弾の情報を用意.
//	D3DXVECTOR3 obj2pos = obj2->pos;
//	float	obj2rad = obj2->m_Radius.x;
//	//双方の中心同士の距離
//	D3DXVECTOR3 vec = obj2pos - obj1pos;
//	float length = D3DXVec3Length(&vec);
//	//距離と半径の総和チェック
//	if (length < (obj2rad +  obj1rad))
//	{//あたり
//
//		return TRUE;//あたったので自身の処理終了
//		//ここで弾を未使用にして終了しないと貫通弾になる
//
//	}
//	return FALSE;	//あたっていない
//}

//レイによる衝突判定　レイが相手メッシュと交差する場合は、pfDistanceに距離を、pvNormalに衝突面の法線を入れてtrueを返す
BOOL Collide(D3DXVECTOR3 vStart, D3DXVECTOR3 vDir, FLOAT* pfDistance, D3DXVECTOR3* pvNormal, LPD3DXMESH *pThing3D, D3DXMATRIX *tempMatrix)
{
	BOOL boHit = false;
	D3DXMATRIX mWorld;
	D3DXVec3Normalize(&vDir, &vDir);

	// レイを当てるメッシュが動いていたり回転している場合でも対象のワールド行列の逆行列を用いれば正しくレイが当たる
	D3DXMatrixInverse(&mWorld, NULL, tempMatrix);
	D3DXVec3TransformCoord(&vStart, &vStart, &mWorld);

	DWORD dwPolyIndex;

	D3DXIntersect(*pThing3D, &vStart, &vDir, &boHit, &dwPolyIndex, NULL, NULL, pfDistance, NULL, NULL);
	if (boHit)
	{
		//交差しているポリゴンの頂点を見つける
		D3DXVECTOR3 vVertex[3];
		FindVerticesOnPoly(*pThing3D, dwPolyIndex, vVertex);
		D3DXPLANE p;
		//その頂点から平面方程式を得る
		D3DXPlaneFromPoints(&p, &vVertex[0], &vVertex[1], &vVertex[2]);
		//平面方程式の係数が法線の成分
		pvNormal->x = p.a;
		pvNormal->y = p.b;
		pvNormal->z = p.c;

		return TRUE;
	}
	return FALSE;
}

//
//HRESULT FindVerticesOnPoly(LPD3DXMESH pMesh,DWORD dwPolyIndex,D3DXVECTOR3* pvVertices )
//そのポリゴンの頂点を見つける
HRESULT FindVerticesOnPoly(LPD3DXMESH pMesh, DWORD dwPolyIndex, D3DXVECTOR3* pvVertices)
{
	//DWORD i, k;
	DWORD dwStride = pMesh->GetNumBytesPerVertex();
	DWORD dwVertexNum = pMesh->GetNumVertices();
	DWORD dwPolyNum = pMesh->GetNumFaces();
	WORD* pwPoly = NULL;
	pMesh->LockIndexBuffer(D3DLOCK_READONLY, (VOID**)&pwPoly);

	BYTE *pbVertices = NULL;
	FLOAT* pfVetices = NULL;
	LPDIRECT3DVERTEXBUFFER9 VB = NULL;
	pMesh->GetVertexBuffer(&VB);
	if (SUCCEEDED(VB->Lock(0, 0, (VOID**)&pbVertices, 0)))
	{
		pfVetices = (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3]];
		pvVertices[0].x = pfVetices[0];
		pvVertices[0].y = pfVetices[1];
		pvVertices[0].z = pfVetices[2];

		pfVetices = (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3 + 1]];
		pvVertices[1].x = pfVetices[0];
		pvVertices[1].y = pfVetices[1];
		pvVertices[1].z = pfVetices[2];

		pfVetices = (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3 + 2]];
		pvVertices[2].x = pfVetices[0];
		pvVertices[2].y = pfVetices[1];
		pvVertices[2].z = pfVetices[2];

		pMesh->UnlockIndexBuffer();
		VB->Unlock();
		VB->Release();
	}
	return S_OK;
}

//
//D3DXVECTOR3 Slip(D3DXVECTOR3 L,D3DXVECTOR3 N)
// L:入射ベクトル（レイ） N:ポリゴンの法線,k
D3DXVECTOR3 Slip(D3DXVECTOR3 L, D3DXVECTOR3 N)
{
	D3DXVECTOR3 S; //滑りベクトル（滑る方向）

	//滑りベクトル S=L-(N * L)/(|N|^2)*N
	S = L - ((D3DXVec3Dot(&N, &L)) / (powf(D3DXVec3Length(&N), 2))) * N;

	return S;
}

//レイを視認できるようにレイをレンダリングする
// 使えないなう
VOID RenderRay(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vStart, D3DXVECTOR3 vDir)
{
	pDevice->SetFVF(D3DFVF_XYZ);
	D3DXVECTOR3 vPnt[2];
	vPnt[0] = vStart;
	vPnt[1] = vDir * 100;
	vPnt[1].y = vPnt[0].y;

	D3DXMATRIX mWorld;
	D3DXMatrixIdentity(&mWorld);
	pDevice->SetTransform(D3DTS_WORLD, &mWorld);
	//レイのマテリアル設定　（白に設定）
	D3DMATERIAL9 mtrl;
	ZeroMemory(&mtrl, sizeof(mtrl));
	mtrl.Diffuse.a = 255;
	mtrl.Diffuse.r = 255;
	mtrl.Diffuse.g = 255;
	mtrl.Diffuse.b = 255;
	mtrl.Ambient = mtrl.Diffuse;
	pDevice->SetMaterial(&mtrl);
	//レイのレンダリング
	pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, vPnt, sizeof(D3DXVECTOR3));

	//　レイのレンダリング
	//RenderRay(pDevice, g_player.part[SWORD_R].srt.pos, g_player.part[SWORD_R].srt.rot);

}
