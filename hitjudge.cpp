//=============================================================================
//
// �����蔻�菈�� [hitjudge.cpp]
// Author : HAL�����@GP11C295�@����@�E��
//
//=============================================================================
#include "player.h"
#include "hitjudge.h"
#include "enemy.h"
#include "field_star.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


//=============================================
// OBJECT3D�\���̓��m�́@���̓����蔻��
//==============================================
//BOOL HitjudgeForModel(MODEL *obj1, MODEL *obj2)
//{
//	//���g�̏���p��
//	float	obj1rad = obj1->m_Radius.x;
//	D3DXVECTOR3 obj1pos = obj1->pos;
//
//	//�Ώۂ̒e�̏���p��.
//	D3DXVECTOR3 obj2pos = obj2->pos;
//	float	obj2rad = obj2->m_Radius.x;
//	//�o���̒��S���m�̋���
//	D3DXVECTOR3 vec = obj2pos - obj1pos;
//	float length = D3DXVec3Length(&vec);
//	//�����Ɣ��a�̑��a�`�F�b�N
//	if (length < (obj2rad +  obj1rad))
//	{//������
//
//		return TRUE;//���������̂Ŏ��g�̏����I��
//		//�����Œe�𖢎g�p�ɂ��ďI�����Ȃ��Ɗђʒe�ɂȂ�
//
//	}
//	return FALSE;	//�������Ă��Ȃ�
//}

//���C�ɂ��Փ˔���@���C�����胁�b�V���ƌ�������ꍇ�́ApfDistance�ɋ������ApvNormal�ɏՓ˖ʂ̖@��������true��Ԃ�
BOOL Collide(D3DXVECTOR3 vStart, D3DXVECTOR3 vDir, FLOAT* pfDistance, D3DXVECTOR3* pvNormal, PART *pThing3D, D3DXMATRIX *tempMatrix)
{
	BOOL boHit = false;
	D3DXMATRIX mWorld;
	D3DXVec3Normalize(&vDir, &vDir);

	// ���C�𓖂Ă郁�b�V���������Ă������]���Ă���ꍇ�ł��Ώۂ̃��[���h�s��̋t�s���p����ΐ��������C��������
	D3DXMatrixInverse(&mWorld, NULL, tempMatrix);
	D3DXVec3TransformCoord(&vStart, &vStart, &mWorld);

	DWORD dwPolyIndex;

	D3DXIntersect(pThing3D->pMesh, &vStart, &vDir, &boHit, &dwPolyIndex, NULL, NULL, pfDistance, NULL, NULL);
	if (boHit)
	{
		//�������Ă���|���S���̒��_��������
		D3DXVECTOR3 vVertex[3];
		FindVerticesOnPoly(pThing3D->pMesh, dwPolyIndex, vVertex);
		D3DXPLANE p;
		//���̒��_���畽�ʕ������𓾂�
		D3DXPlaneFromPoints(&p, &vVertex[0], &vVertex[1], &vVertex[2]);
		//���ʕ������̌W�����@���̐���
		pvNormal->x = p.a;
		pvNormal->y = p.b;
		pvNormal->z = p.c;

		return TRUE;
	}
	return FALSE;
}

//
//HRESULT FindVerticesOnPoly(LPD3DXMESH pMesh,DWORD dwPolyIndex,D3DXVECTOR3* pvVertices )
//���̃|���S���̒��_��������
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


D3DXVECTOR3 CollideGeo(SRT* m_A, SRT* m_B, D3DXVECTOR3 move, PART* pThingB3D)
{
	//MODEL *Player = GetPlayer(0);

	//�����蔻��
	FLOAT fDistance = 0.0f;
	D3DXVECTOR3	 vNormal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMATRIX tempMatrix;
	D3DXMatrixIdentity(&tempMatrix);

	if (Collide(m_A->pos, move, &fDistance, &vNormal, pThingB3D, &tempMatrix) == TRUE && fDistance <= HIT_SKYDOME_FIRST)
	{
		//�������ԂȂ̂ŁA���点��
		move = Slip(move, vNormal);//����x�N�g�����v�Z
	
		//����x�N�g����̒n�ʓˋN�Ƃ̃��C���� �Q�d�ɔ���	
		if (Collide(m_A->pos, move, &fDistance, &vNormal, pThingB3D, &tempMatrix) && fDistance <= HIT_SKYDOME_SECOND)
		{
			//�Q�i�ڂ̓������ԂȂ̂ŁA���点�� �����炭�オ�����		
			move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����x�N�g�����v�Z
		}
	}	
	
	return move;
}

//
//D3DXVECTOR3 Slip(D3DXVECTOR3 L,D3DXVECTOR3 N)
// L:���˃x�N�g���i���C�j N:�|���S���̖@��,k
D3DXVECTOR3 Slip(D3DXVECTOR3 L, D3DXVECTOR3 N)
{
	D3DXVECTOR3 S; //����x�N�g���i��������j

	//����x�N�g�� S=L-(N * L)/(|N|^2)*N
	S = L - ((D3DXVec3Dot(&N, &L)) / (powf(D3DXVec3Length(&N), 2))) * N;

	return S;
}

//=============================================================================
// hitjudge�擾�֐�
//=============================================================================
//HITJUDGE *GetHitjudge(int no)
//{
//	return (&Hitjudge[no]);
//}