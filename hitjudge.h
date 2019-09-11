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

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


#define HIT_WALL_FIRST (10.0)
#define HIT_WALL_SECOND (9.9)


void AnimePosAndHitjudge(D3DXVECTOR3 *af_vec, D3DXMATRIX world, D3DXMATRIX buff, D3DXVECTOR3 bf_vec, D3DXVECTOR3 move_vec, float motionTime, float part, PART opponent, float length);


// ����̓����蔻��
// m_A �O�t���[���̃x�N�g��
// move ���������Ƃ̃t���[��
// part �Ώۂ�part ������ �i��@&g_enemy.part[i]�j ���̂����Ƃ��������Ȃ�Ai �͓��̂̔ԍ�������

// �}�N���ɂ͕���̒���(float length �̒l)��ǉ����Ă���
// ���剻����Ȃ� #define HIT_GIANT_SLASH(10.0) �ɂ���Ƃ�
BOOL CollideAttack(D3DXVECTOR3* m_A, D3DXVECTOR3 move, PART* part, float length);
#define HIT_THROW_SWORD (1.0)

// ���[�J�����W�����[���h���W�ɕϊ�����
// world_pos ��Ԃ�l�ɂ���

D3DXVECTOR3 ReturnLocalToWorldVec(D3DXMATRIX world, D3DXMATRIX buff, D3DXVECTOR3 local_pos );


//////////////////////���g��Ȃ�////////////////////////////////

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

D3DXVECTOR3 CollideGeo(D3DXVECTOR3* m_A, D3DXVECTOR3 move, LPD3DXMESH* pThingB3D);
#define HIT_SKYDOME_FIRST (10.0)
#define HIT_SKYDOME_SECOND (9.9)
// ���l�Y����
D3DXVECTOR3 Slip(D3DXVECTOR3 L, D3DXVECTOR3 N);


// ���l�Y����
D3DXVECTOR3 Slip(D3DXVECTOR3 L, D3DXVECTOR3 N);
VOID RenderRay(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vStart, D3DXVECTOR3 vDir);

#endif

