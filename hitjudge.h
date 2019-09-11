//=============================================================================
//
// �����蔻�菈�� [hitjudge.h]
// Author : HAL�����@GP11C295�@����@�E��
//
//=============================================================================
#ifndef _HITJUDGE_H_
#define _HITJUDGE_H_

#include "main.h"
#include "bullet.h"
#include "enemy.h"
#include "player.h"



//**************************************************************************
// �}�N����`
//**************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//BOOL HitjudgeForModel(MODEL *obj1, MODEL *obj2);

// ���C�ɂ��Փ˔���
// ��ɃX�J�C�h�[���Ƃ̏Փ˔���Ɏg��

// �|���S���̒��_��������
HRESULT FindVerticesOnPoly(LPD3DXMESH pMesh, DWORD dwPolyIndex, D3DXVECTOR3* pvVertices);

// ���ʂɑΏۂ̃��b�V��������H
// ���̋����́H
BOOL Collide(D3DXVECTOR3 vStart, D3DXVECTOR3 vDir, FLOAT* pfDistance, D3DXVECTOR3* pvNormal, LPD3DXMESH *pThing3D, D3DXMATRIX *tempMatrix);

// �h�[���Ƃ̓����蔻���Collide()���g�����肷��
// 1��ڂ̓x�N�g�����Y����
// 2��ڂ�move��0�ɂ���
// D3DXVECTOR3 CollideGeo(D3DXVECTOR3* m_A, D3DXVECTOR3 move, PART* pThingB3D);
D3DXVECTOR3 CollideGeo(D3DXVECTOR3* m_A, D3DXVECTOR3 move, LPD3DXMESH* pThingB3D);
#define HIT_SKYDOME_FIRST (10.0)
#define HIT_SKYDOME_SECOND (9.9)
// ���l�Y����
D3DXVECTOR3 Slip(D3DXVECTOR3 L, D3DXVECTOR3 N);

#endif

