//=============================================================================
//
// ��A�����H���� [field_sky.h]
// Author : HAL�����@GP11C295�@����@�E��
//
//=============================================================================
#ifndef _FIELD_STAR_H_
#define _FIELD_STAR_H_

#include "main.h"

//*************�L�����N�^�[�f�[�^�ϐ��̗p��*****************************
#define		NUM_FIELD	(6)

//*************���f���[�f�[�^�ϐ��̗p��*****************************
#define		NUM_SKYMODEL	(2)

namespace warpzoneNS
{
	// warpzone �̒��S���W
	// 2�����x�N�g���ŋ����𒊏o�A���ȉ��̋����Ńt���O�I��
	const D3DXVECTOR3 warp0 = D3DXVECTOR3(0, 0, 0); // �n�ʂ̐�
	const D3DXVECTOR3 warp1 = D3DXVECTOR3(333, 0, 476);
	const D3DXVECTOR3 warp2 = D3DXVECTOR3(-330, 0, 476);
	const D3DXVECTOR3 warp3 = D3DXVECTOR3(-558, 0, -176);
	const D3DXVECTOR3 warp4 = D3DXVECTOR3(-14, 0, -572);
	const D3DXVECTOR3 warp5 = D3DXVECTOR3(539, 0, -191);

	// warpzone����warp���鋗���i�L�����̒��S-warpzone�̒��S�j 2�����x�N�g���̋���
	const float into_warpzone = 10;
}

struct MODEL3D
{
	//x�t�@�C�����
	LPD3DXBUFFER		pMatBuff;			// ���b�V���̃}�e���A�������i�[
	DWORD				nNumMat;			// �}�e���A�����̑���
	LPD3DXMESH			pMesh;				// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 pD3DTextureModel;
};

struct MODEL
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scl;
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxRot;
	bool use;
	MODEL3D model3d;

};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitFieldStar(void);
void initModelPos(D3DXVECTOR3* pos, int i); // ���[�v�]�[���̍��W���Z�b�g
HRESULT initModeldata(MODEL3D* model3d, const char* modeldata); // ���f���̓ǂݍ���

void UninitFieldStar(void);
void UpdateFieldStar(void);
void DrawFieldStarModel(void);

void playerWarp(int i);
bool checkClearStage(int i);
float distanceVec2(D3DXVECTOR2 A, D3DXVECTOR2 B);

// �N���A���Ăяo���A�����mode�������ɓ����
void returnClearTrue(MODE mode);

#endif