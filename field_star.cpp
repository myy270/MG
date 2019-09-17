//=============================================================================
//
// ���^�n�ʂ̏��� [field_star.cpp]
// Author : HAL�����@GP11C295�@����@�E��
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

//*************�L�����N�^�[�f�[�^�ϐ��̗p��*****************************
MODEL	FieldStar[NUM_FIELD];			//�v���C���[�L�����N�^�\����

using namespace warpzoneNS;
extern PLAYER g_player;
extern ENEMY g_enemy;
//extern int g_next_stage;
extern STAGE_CLEAR g_stage_clear;

//*********************���f���f�[�^�t�@�C�����z��********************
const char* FieldStarModelData[] = 
{
	"data/MODEL/star.x",
	"data/MODEL/wrap2.x"
};


//=============================================================================
// ����������
//=============================================================================
HRESULT InitFieldStar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3	temp;
	D3DXMATRIX mtxScl,/*mtxRot,*/ mtxTranslate;

	// �L�����N�^�̈ʒu�E��]�E�X�P�[���Ȃǂ̏����ݒ�
	for (int i = 0; i < NUM_FIELD; i++)
	{

		initModelPos(&FieldStar[i].pos, i);
		FieldStar[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//

		FieldStar[i].use = TRUE;
		FieldStar[i].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&FieldStar[i].mtxWorld);

		// �X�P�[�����s��ɂ��ă��[���h�s��i�n�߂͒P�ʍs��j�Ə�Z
		temp = FieldStar[i].scl;
		D3DXMatrixScaling(&mtxScl, temp.x, temp.y, temp.z);
		D3DXMatrixMultiply(&FieldStar[i].mtxWorld, &FieldStar[i].mtxWorld, &mtxScl);

		// ��]���s��ɂ��ă��[���h�s��Ə�Z
		temp = FieldStar[i].rot;
		D3DXMatrixRotationYawPitchRoll(&FieldStar[i].mtxRot, temp.y, temp.x, temp.z);
		D3DXMatrixMultiply(&FieldStar[i].mtxWorld, &FieldStar[i].mtxWorld, &FieldStar[i].mtxRot);

		// �ړ����s��ɂ��ă��[���h�s��Ə�Z
		temp =FieldStar[i].pos;
		D3DXMatrixTranslation(&mtxTranslate, temp.x, temp.y, temp.z);
		D3DXMatrixMultiply(&FieldStar[i].mtxWorld, &FieldStar[i].mtxWorld, &mtxTranslate);

		// �����������[���h�}�g���b�N�X��DirectX�փZ�b�g
		pDevice->SetTransform(D3DTS_WORLD, &FieldStar[i].mtxWorld);

		//���f���f�[�^�̏����ݒ�
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


	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		TEXTURE_STAR,						// �t�@�C���̖��O
		&FieldStar[0].model3d.pD3DTextureModel);	// �ǂݍ��ރ������[
		
	return S_OK;
}

//=============================================================================
// �I������
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
// �X�V����
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
// �`�揈��
//=============================================================================
void DrawFieldStarModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl,/*mtxRot,*/ mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	// ���ݐݒ肳��Ă���}�e���A�����擾���ĕۑ�
	pDevice->GetMaterial(&matDef);

	//*************************�S�ẴL�����N�^�[��\��************************
	for(int i=0; i<NUM_FIELD; i++)
	{
		D3DXVECTOR3	temp;

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&FieldStar[i].mtxWorld);

		// �X�P�[�����s��ɂ��ă��[���h�s��i�n�߂͒P�ʍs��j�Ə�Z
		temp = FieldStar[i].scl;
		D3DXMatrixScaling(&mtxScl, temp.x, temp.y, temp.z);
		D3DXMatrixMultiply(&FieldStar[i].mtxWorld, &FieldStar[i].mtxWorld, &mtxScl);

		// ��]���s��ɂ��ă��[���h�s��Ə�Z
		temp = FieldStar[i].rot;
		D3DXMatrixRotationYawPitchRoll(&FieldStar[i].mtxRot, temp.y, temp.x, temp.z);
		D3DXMatrixMultiply(&FieldStar[i].mtxWorld, &FieldStar[i].mtxWorld, &FieldStar[i].mtxRot);

		// �ړ����s��ɂ��ă��[���h�s��Ə�Z
		temp =FieldStar[i].pos;
		D3DXMatrixTranslation(&mtxTranslate, temp.x, temp.y, temp.z);
		D3DXMatrixMultiply(&FieldStar[i].mtxWorld, &FieldStar[i].mtxWorld, &mtxTranslate);

		// �����������[���h�}�g���b�N�X��DirectX�փZ�b�g
		pDevice->SetTransform(D3DTS_WORLD, &FieldStar[i].mtxWorld);

		// ���f���̃}�e���A�����ɑ΂���|�C���^���擾
		pD3DXMat = (D3DXMATERIAL*)FieldStar[i].model3d.pMatBuff->GetBufferPointer();

		//���f���̏��ɏ]���ă��f�����\������I�u�W�F�N�g�̐������J��Ԃ�
		for (int nCntMat = 0; nCntMat < (int)FieldStar[i].model3d.nNumMat; nCntMat++)
		{
			// �I�u�W�F�N�g�̃}�e���A���̐ݒ�
			pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

			// �I�u�W�F�N�g�̃e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, FieldStar[i].model3d.pD3DTextureModel);

			// �I�u�W�F�N�g�̕`��
			FieldStar[i].model3d.pMesh->DrawSubset(nCntMat);
		}
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
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

	 if (D3D_OK != D3DXLoadMeshFromX(modeldata,			// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
		 D3DXMESH_SYSTEMMEM,		// ���b�V���̍쐬�I�v�V�������w��
		 pDevice,				// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
		 NULL,					// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
		 &model3d->pMatBuff,	// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^
		 NULL,			 // �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
		 &model3d->nNumMat,		// D3DXMATERIAL�\���̂̐�
		 &model3d->pMesh))	// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
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